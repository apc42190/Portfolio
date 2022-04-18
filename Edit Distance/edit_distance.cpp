/*
Name: Aaron Cope
Email: apc42190@csu.fullerton.edu
Compiled with: g++
Environment: Windows 10
Instructions:
    Step 1: g++ edit_distance.cpp -o edit_distance.exe
    Step 2: ./edit_distance.exe
    Step 3: Enter first string
    Step 4: Enter second string
*/

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <iomanip>
#include <algorithm>


int main() {

    //Strings to store user input
    std::string string_1;
    std::string string_2;

    //Get first string
    std::cout << "Enter the first string: ";
    std::cin >> string_1;

    //Get second string
    std::cout << "Enter the second string: ";
    std::cin >> string_2;

    //Matrix dimensions
    int columns = string_1.size() + 1;
    int rows = string_2.size() + 1;
    
    //Vector to start edit distances and matrix to store operations
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns));  
    std::vector<std::vector<char>> arrows(rows, std::vector<char>(columns));  

    //Initialize first row to 0-n
    for (int i = 0; i < columns; ++i) {
        matrix[0][i] = i;
        arrows[0][i] = 'l';
    }

    //Initialize first column to 0-n
    for (int i = 0; i < rows; ++i) {
        matrix[i][0] = i;
        arrows[i][0] = 'u';
    }

    arrows[0][0] = 'e';

    //Fill out matrix
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < columns; ++j) {
            int left = matrix[i][j - 1] + 1;
            int up = matrix[i - 1][j] + 1;
            int sub_or_match = matrix[i - 1][j - 1];
            if (string_1[j - 1] != string_2[i - 1]) {
                sub_or_match++;
            }
            int min = std::min({left, up, sub_or_match});
            matrix[i][j] = min;
            if (min == sub_or_match) {
                arrows[i][j] = 's';
            } else if (min == left) {
                arrows[i][j] = 'l';
            } else if (min == up) {
                arrows[i][j] = 'u';
            }
        }
    }

    //Print edit distance matrix
    for (std::vector<int> vec : matrix) {
        for (int num : vec) {
            std::cout << std::setw(3) << num;
        }
        std::cout << "\n";
    }

    //Get path through matrix and store in stack
    std::stack<char> path;
    int i = rows - 1;
    int j = columns - 1;
    while (i > 0 || j > 0) {
        char ch = arrows[i][j];
        path.push(ch);
        if (ch == 's') {
            i--;
            j--;
        } else if (ch == 'l') {
            j--;
        } else if (ch == 'u') {
            i--;
        }
    }

    //Strings to store alignment
    std::string alignment_1 = "";
    std::string alignment_2 = "";
    std::string errors = "";

    int count_1 = 0;
    int count_2 = 0;

    //Generate alignment using path through matrix
    while (!path.empty()) {
        char ch = path.top();
        path.pop();
        if (ch == 'u') {
            alignment_1 += '_';
            alignment_2 += string_2[count_2];
            count_2++;
            errors += '^';
        } else if (ch == 'l') {
            alignment_1 += string_1[count_1];
            alignment_2 += '_';
            count_1++;
            errors += '^';
        } else if (ch == 's') {
            char ch_1 = string_1[count_1];
            char ch_2 = string_2[count_2];
            alignment_1 += ch_1;
            alignment_2 += ch_2;
            count_1++;
            count_2++;
            if (ch_1 == ch_2) {
                errors += " ";
            } else {
                errors += "^";
            }
        }
    }

    //Print alignment
    std::cout << "\nEdit Distance: " << matrix[rows - 1][columns - 1];
    std::cout << "\n" << alignment_1 << "\n" << alignment_2 << "\n" << errors << "\n";

    return 0;
}