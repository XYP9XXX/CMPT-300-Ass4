#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "utils.h"
int isElementInArray(int array[], int size, int element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return 1;
        }
    }
    return 0;
}

// Helper function that print all array in a list.
void print_list(List list) {
    int* array = list.array;
    int length = list.length;
    for (int i = 0; i < length; i++) {
        printf("%d  ", array[i]);
    }
}

// Function that generate a list consist with a size 50 random array.
List generate_random_list () {
    List list;
    int size = 0;
    int random_number;
    list.length = RANDOM_ARR_SIZE;
    srand((unsigned)time(NULL));
    int* array = (int*) malloc(list.length * sizeof(int));
    for (size_t i = 0; i < list.length; i++)
    {
        random_number = rand() % SIZE;
        if (!isElementInArray(array, size, random_number)) {
            array[i] = random_number;
            size++;
        } else{
            i--;
        }
    }
    list.array = array;
    return list;
}

double count_average_delay(List FCFS, List Another_Algorighm) {
    // Get two arrays, one is the FCFS algorithm and the other is another algorithm(SSTF or SCAN).
    int* fcfs = FCFS.array;
    int* another = Another_Algorighm.array;

    // Get the length of each array
    int length_fcfs = FCFS.length;
    int length_another = Another_Algorighm.length;

    // Create variables for number of delay and the total delay and average delay;
    double delay_count = 0;
    double delay_length = 0;
    double delay_avg = 0;

    // Create and set default values for the array which is used to record which elements are already been visited.
    int visited[length_another];
    for (int i = 0; i < length_another; i++) {
        visited[i] = 0;
    }

    // Traverse two arrays and record delay time and total delay length
    for (int i = 0; i < length_fcfs; i++) {
        for (int j = 0; j < length_another; j++)
        {
            if (fcfs[i] == another[j] && !visited[j] && j > i)
            {
                visited[j] = 1;
                delay_count++;
                delay_length += (j - i);
            } else {
                continue;
            }
        }
    }
    if (delay_count != 0) {
        delay_avg = delay_length / delay_count;
        return delay_avg;
    } else {
        return 0;
    }
}

int isNumbersAndCommasOnly(const char *str) {
    while (*str) {
        if (!isdigit(*str) && *str != ',') {
            return 0; // False, if character is not a digit or a comma
        }
        str++;
    }
    return 1; // True, if all characters are digits or commas
}