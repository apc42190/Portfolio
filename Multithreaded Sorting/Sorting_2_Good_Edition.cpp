//Author: Aaron Cope
//Build Info: compile using following command: g++ Sorting_2_Good_Edition.cpp -lpthread
//Run Info: run using ./a.out arg1 arg2 arg3
/*Arguments: arg1: 'n' - number of integers to generate and sort.
             arg2: 'u' - upper bound for random numbers
             arg3: 'p' - number of segments to divide numbers into for sorting */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <algorithm>
#include <memory>

//Global Variables
std::vector<int> numbers_to_sort;
pthread_mutex_t thread_mutex;

//struct to hold arguments for sorting threads
typedef struct {
    int start;
    int end;
} sort_arguments;

//struct to hold arguments for merging threads
typedef struct {
    std::vector<sort_arguments*> start_and_end;
    int i;
} merge_arguments;

//function for sorting threads to run
void* thread_sort(void* args) {
    //get arguments and cast to correct type
    sort_arguments* data = (sort_arguments*)args;
    int start = data->start;
    int end = data->end;

    //sort vector between specified locations
    std::sort(numbers_to_sort.begin() + start, numbers_to_sort.begin() + end);

    //lock thread before printing
    pthread_mutex_lock(&thread_mutex);

    //print sorted segment
    std::cout << "Sorted " << end - start << " numbers: [";
    for (int i = start; i < end - 1; ++i) {
        std::cout << numbers_to_sort[i] << ", ";
    }
    std::cout << numbers_to_sort[end - 1] << "]\n";

    //unlock thread now that printing is done
    pthread_mutex_unlock(&thread_mutex);

    //exit thread
    pthread_exit(0);
}

void* merge_vectors(void* args) {

    //get data from arguments
    merge_arguments* data = (merge_arguments*)args;
    int i = data->i;
    std::vector<sort_arguments*> start_and_end = data->start_and_end;

    //get start and finish locations of each side
    int left_start = start_and_end[i]->start;
    int left_end = start_and_end[i]->end;
    int right_start = start_and_end[i + 1]->start;
    int right_end = start_and_end[i + 1]->end;

    //merge left and right segments
    std::vector<int> result((left_end - left_start) + (right_end - right_start));
    merge(numbers_to_sort.begin() + left_start, numbers_to_sort.begin() + left_end, numbers_to_sort.begin() + right_start, numbers_to_sort.begin() + right_end, result.begin());

    //lock thread before printing
    pthread_mutex_lock(&thread_mutex);

    //print out merged segment
    std::cout << "Merged " << left_end - left_start << " and " << right_end - right_start << " numbers: [";
    for (size_t i = 0; i < result.size() - 1; ++i) {
        std::cout << result[i] << ", ";
    }
    std::cout << result[result.size() - 1] << "]\n";

    //unlock thread after printing
    pthread_mutex_unlock(&thread_mutex);

    //transer merged segment to array
    for (size_t i = 0; i < result.size(); ++i) {
        numbers_to_sort[left_start + i] = result[i];
    }

    //update new segment start and end
    start_and_end[i]->start = left_start;
    start_and_end[i]->end = right_end;

    pthread_exit(0);
}


int main (int argc, char* argv[]) {
    //Make sure enough arguments have been specified
    if (argc < 4) {
        std::cout << "Error: Insufficient Arguments Provided.\n";
        return -1;
    }

    //get parameters from command line
    int n = atoi(argv[1]);
    int u = atoi(argv[2]);
    int p = atoi(argv[3]);

    //seed random number generator
    srand(time(NULL));

    //generate random numbers for array
    for (int i = 0; i < n; ++i) {
        numbers_to_sort.push_back((rand() % u) + 1);
    }

    //print numbers before sorting
    std::cout << "Numbers before sorting: [";
    for(size_t i = 0; i < numbers_to_sort.size() - 1; ++i) {
        std::cout << numbers_to_sort[i] << ", ";
    }
    std::cout << numbers_to_sort.back() << "]\n";

    //arrays to track thread info for later joining
    std::vector<pthread_t> sorting_threads;
    std::vector<sort_arguments*> start_and_end;

    //create threads
    for (int i = 0; i < p; ++i) {
        //determine region of vector to sort
        int start_index = (n / p) * i;
        int end_index = start_index + (n / p);
        if (i == p - 1) end_index = n;

        //pack arguments to thread in stuct and store in start_and_end
        sort_arguments* arg = new sort_arguments;
        arg->start = start_index;
        arg->end = end_index;
        start_and_end.push_back(arg);

        //create thread and store id in vector
        pthread_t tid;
        pthread_create(&tid, NULL, thread_sort, arg);
        sorting_threads.push_back(tid);
    }

    //join threads
    for(pthread_t tid : sorting_threads) {
        pthread_join(tid, NULL);
    }

    //merge threads
    while(start_and_end.size() != 1) {
        //vectors to store thread arguments(for later deallocation) as well as thread ids
        std::vector<merge_arguments*> args;
        std::vector<pthread_t> threads_merge;

        //loop through by twos, to get pairs of array segments
        for(int i = 0; i < start_and_end.size(); i += 2) {

            //will only take branch if odd number of threads
            if (i + 1 == start_and_end.size()) break;

            //prepare arguments for thread
            merge_arguments* arg = new merge_arguments;
            arg->i = i;
            arg->start_and_end = start_and_end;

            //create threads
            pthread_t tid;
            pthread_create(&tid, NULL, merge_vectors, arg);
            threads_merge.push_back(tid);
        }

        //join threads
        for (pthread_t tid : threads_merge) {
            pthread_join(tid, NULL);
        }

        //free merging argument data
        for (merge_arguments* arg : args) {
            std::cout << arg->start_and_end[arg->i]->start << "\n";
            delete arg;
        }

        //remove every second element from start_and_end
        int count = 0;
        for(size_t i = 0; i < start_and_end.size(); ++i) {
            if (count % 2 != 0) {
                start_and_end.erase(start_and_end.begin() + i);
                i--;
            }
            count++;
        }
    }

    //print numbers after sorting
    std::cout << "Numbers after sorting: [";
    for(size_t i = 0; i < numbers_to_sort.size() - 1; ++i) {
        std::cout << numbers_to_sort[i] << ", ";
    }
    std::cout << numbers_to_sort.back() << "]\n";

    //free sorting argument memory
    for (sort_arguments* arg : start_and_end) {
        delete arg;
    }

    return 0;
}
