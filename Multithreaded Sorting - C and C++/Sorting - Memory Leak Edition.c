#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

//global variables
int p = 0;
int* array_to_sort;

//array structure to store array pointer and length
typedef struct {
    int* array;
    int length;
    int start;
    int end;
} array_info;

//structure to pass array of arrays into recursive thread function
typedef struct {
    array_info** array;
    int start;
    int end;
} big_array_info;

//comparator for qsort
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

//to be called by sorting threads from main
void* thread_sort(void* args) {
    //get data from arguments struct
    array_info* data = args;
    int start = data->start;
    int end = data->end;

    //sort section of array
    qsort(&array_to_sort[start], end - start, sizeof(int), cmpfunc);

    int length = end - start;
    pthread_t pid = pthread_self();
    printf("Thread %lu sorted %i numbers.\n", pid, length);
    printf("[");
    for (int i = start; i < end - 1; ++i) {
        printf("%i", array_to_sort[i]);
        printf(", ");
    }
    printf("%i", array_to_sort[end - 1]);
    printf("]\n");

    return 0;
}

array_info* merge_left_and_right(array_info* left, array_info* right) {
    //get array sizes from argument struct
    int left_size = left->length;
    int right_size = right->length;

    //allocate memory for merged list and info struct
    int* result = malloc((left_size + right_size) * sizeof(int));
    array_info* return_value = malloc(sizeof(array_info));
    return_value->array = result;
    return_value->length = left_size + right_size;

    //declare counters i, l, r to track location in each array
    int i = 0;
    int l = 0;
    int r = 0;

    //loop through arrays until we reach both their ends
    while (l != left_size || r != right_size) {
        if (l == left_size) {               
            result[i] = right->array[r];
            r++;
        } else if (r == right_size) {       
            result[i] = left->array[l];
            l++;
        } else if (left->array[l] < right->array[r]) {
            result[i] = left->array[l];
            l++;
        } else {
            result[i] = right->array[r];
            r++;
        }
        i++;
    }
    return return_value;
}

//divide and conquer. Recursively divide list of arrays into pairs to merge
void* merge_arrays_recurse(void* args) {
    //get data from arguments
    big_array_info* arguments = args;
    array_info** arrays = arguments->array;
    int start = arguments->start;
    int end = arguments->end;

    //if we have a single array, return that array and its size
    if (start == end) {
        array_info* track = malloc(sizeof(array_info));
        track->length = arrays[start]->length;
        track->array = arrays[start]->array;
        return track;
    }

    //calculated the midway point of our two array[] halves
    int mid = start + (end - start) / 2;

    //prepare left thread and generate arguments for it
    pthread_t left_thread;
    big_array_info* left_args = malloc(sizeof(array_info));
    left_args->array = arrays;
    left_args->start = start;
    left_args->end = mid;

    //prepare right thread and generate arguments for it
    pthread_t right_thread;
    big_array_info* right_args = malloc(sizeof(array_info));
    right_args->array = arrays;
    right_args->start = mid + 1;
    right_args->end = end;

    //start both threads
    pthread_create(&left_thread, NULL, merge_arrays_recurse, left_args);
    pthread_create(&right_thread, NULL, merge_arrays_recurse, right_args);

    //join left thread and store return value in "temp_left"
    void* temp_left;
    pthread_join(left_thread, &temp_left);
    array_info* left = temp_left;

    //join right thread and store return value in "temp_right"
    void* temp_right;
    pthread_join(right_thread, &temp_right);
    array_info* right = temp_right;
    
    //merge individual arrays together two at a time
    array_info* track = malloc(sizeof(array_info));
    track = merge_left_and_right(left, right);
    return track;
}

//start recursion and return sorted, merged array
int* merge_arrays(array_info* arrays[]) {
    if (arrays == NULL) {
        return NULL;
    }

    //store argument data in struct
    big_array_info* args = malloc(sizeof(big_array_info));
    args->array = arrays;
    args->start = 0;
    args->end = p - 1;

    //call recursive function and store return value
    array_info* return_data = merge_arrays_recurse(args);
    return return_data->array;
}

int main (int argc, char* argv[]) {

    //Check if enough arguments are specified
    if(argc < 4) {
        printf("Insufficient arguments.\n");
        return -1;
    }

    //get arguments from command line
    int n = atoi(argv[1]);
    int u = atoi(argv[2]);
    p = atoi(argv[3]);

    //seed random number generator
    srand(time(0));

    //Array to sort with threads
    array_to_sort = malloc(sizeof(int) * n);

    //Generate random array elements between 1 and u
    for (int i = 0; i < n; ++i) {
        array_to_sort[i] = (rand() % u) + 1;
    }

    //Print unsorted array
    printf("Array before sorting: [");
    for (int i = 0; i < n - 1; ++i) {
        printf("%i", array_to_sort[i]);
        printf(", ");
    }
    printf("%i", array_to_sort[n - 1]);
    printf("]\n\n");

    //array to track threads
    pthread_t threads[p];
    array_info* argument_pointers[p];

    //generate threads for each section 
    for (int i = 0; i < p; ++i) {
        //store aguments in struct to pass to thread
        array_info* args = malloc(sizeof(array_info));
        argument_pointers[i] = args;
        args->array = array_to_sort;

        //start and end ints: index of each threads regions of influence
        int start = (n / p) * i;
        int end = start + (n / p);

        //Extra elements(if array not divisible by p) go into the last subarray
        if (i == p - 1) {
            end = n;
        }
        args->start = start;
        args->end = end;

        //creates threads and stores if in array for later joins
        pthread_t tid;
        pthread_create(&tid, NULL, thread_sort, args);
        threads[i] = tid;
    }

    //join threads
    for (int i = 0; i < p; ++i) {
        pthread_join(threads[i], NULL);
    }

    //make subarrays from array
    array_info* subarrays[p];
    for (int i = 0; i < p; ++i) {
        array_info* data = argument_pointers[i];
        int length = data->end - data->start;
        int* subarray = malloc(sizeof(int) * length);
        for (int j = 0; j < length; ++j) {
            subarray[j] = array_to_sort[data->start + j];
        }
        subarrays[i] = malloc(sizeof(array_info));
        subarrays[i]->array = subarray;
        subarrays[i]->length = length;
    }

    //call merging function
    int* answer = merge_arrays(subarrays);

    //Print sorted array
    printf("\nArray after sorting: [");
    for (int i = 0; i < n - 1; ++i) {
        printf("%i", answer[i]);
        printf(", ");
    }
    printf("%i", answer[n - 1]);
    printf("]\n");

  
    return 0;
}