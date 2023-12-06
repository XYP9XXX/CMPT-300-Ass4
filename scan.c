#include <malloc.h>
#include "scan.h"
List SCAN(List sequence) {
    // Get the array passed in
    int* fcfs = sequence.array;

    // Get the length of passed in array
    int length = sequence.length;

    // Get the array passed in
    int* array = (int*) malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        array[i] = sequence.array[i];
    }

    // Set the header track
    int header = array[0];

    // Create variable for current track and temo for swap
    int curr_track;
    int temp;

    // Create a array which is used to record which elements are already been visited.
    int visited[length];

    // Create list object for return
    List list;
    list.length = length;
    list.count_tracks = 0;
    list.longest_delay = 0;

    // Create the order array
    int* order = (int*) malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        visited[i] = 0;
    }

    // Using bubble sort algorithm re-order the array.
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] > array[j]) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    if (header == array[length - 1]){
        list.count_tracks = header - array[0];
    }else{
        list.count_tracks = header + array[length-1];
    }

    // Index for sequence array
    int index = 0;

    // Index for order array, start at zero.
    int order_index = 0;

    // Find the position of header.
    for (int i = 0; i < length; i++) {
        if (header == array[i]) {
            index = i;
            break;
        }
    }

    // Start traversing the tracks in the direction from small to large
    for (int i = index; i >=0; i--) {
        curr_track = array[i];
        order[order_index] = array[i];
//        list.count_tracks += abs_diff(header, curr_track);
        header = curr_track;
        order_index++;
    }

    // When reach the end of track, go back.
    for (int i = index + 1; i < length; i++) {
        curr_track = array[i];
        order[order_index] = array[i];
//        list.count_tracks += abs_diff(header, curr_track);
        header = curr_track;
        order_index++;
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++)
        {
            if (fcfs[i] == order[j] && j > i)
            {
                if ((j - i) > list.longest_delay) {
                    list.longest_delay = j - i;
                }
            } else {
                continue;
            }
        }
    }

    list.array = order;

    // Return the target list.
    return list;
}