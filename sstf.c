#include <malloc.h>
#include "sstf.h"
int abs_diff(int x, int y);
List SSTF(List sequence) {
    // Get the array passed in
    int* array = sequence.array;

    // Get the length of passed in array
    int length = sequence.length;

    // Create a array which is used to record which elements are already been visited.
    int visited[length];

    // Create list object for return
    List list;
    list.length = length;
    list.count_tracks = 0;
    list.longest_delay = 0;

    // Create the order array
    int* order = (int*) malloc(length * sizeof(int));

    // Min refers to min distance, min_index refers to min distance come from which element
    int min, min_index;

    // Initialize the visited array. They are all zero at the beginning, indicating that no elements are visited.
    for (int i = 0; i < length; i++) {
        visited[i] = 0;
    }

    // Set the header element(which should be the first element of the array by definition)
    int current = array[0];

    // Each loop puts one element in.
    for (int i = 0; i < length; i++) {
        // Set min distance to the range of tracks first.
        min = SIZE;
        for (int j = 0; j < length; j++) {
            // If distance between element i/j less than min distance, update it.
            if (!visited[j] && abs_diff(array[j], current) < min) {
                min = abs_diff(array[j], current);
                min_index = j;
            }
        }
        list.count_tracks += abs_diff(current, array[min_index]);
        visited[min_index] = 1;
        order[i] = array[min_index];
        current = array[min_index];
    }
    list.array = order;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++)
        {
            if (array[i] == order[j] && j > i)
            {
                if ((j - i) > list.longest_delay) {
                    list.longest_delay = j - i;
                }
            } else {
                continue;
            }
        }
    }

    // Return the target list
    return list;
}
// Helper function used to calculate the absolute distance between two tracks.
int abs_diff(int x, int y) {
    return x > y ? x - y : y - x;
}