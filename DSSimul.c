#include <stdio.h>
#include <stdlib.h>

#define SIZE 200;
#define RANDOM_ARR_SIZE 50;

typedef struct MY_LIST List;
struct MY_LIST
{
    int* array;
    int length;
};


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
    list.length = RANDOM_ARR_SIZE
    int* array = (int*) malloc(list.length * sizeof(int));
    for (size_t i = 0; i < list.length; i++)
    {
        array[i] = rand() % SIZE;
    }
    list.array = array;
    return list;
}

// Helper function used to calculate the absolute distance between two tracks.
int abs_diff(int x, int y) {
    return x > y ? x - y : y - x;
}

List SSFT(List sequence) {
    // Get the array passed in
    int* array = sequence.array;

    // Get the length of passed in array
    int length = sequence.length;

    // Create a array which is used to record which elements are already been visited.
    int visited[length];

    // Create list object for return
    List list;
    list.length = length;

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
        visited[min_index] = 1;
        order[i] = array[min_index];
        current = array[min_index];
    }
    list.array = order;

    // Return the target list
    return list;
}

List SCAN(List sequence) {
    int* array = sequence.array;
    int header = array[0];
    int length = sequence.length;
    int temp;
    int visited[length];
    List list;
    list.length = length;
    int* order = (int*) malloc(length * sizeof(int));
    int min, min_index;
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
    for (int i = index; i < length; i++) {
        order[order_index] = array[i];
        order_index++;
    }

    // When reach the end of track, go back.
    for (int i = index - 1; i >= 0; i--) {
        order[order_index] = array[i];
        order_index++;
    }

    list.array = order;

    // Return the target list.
    return list;
}


int main(int argc, char *argv[]) {
    // int requrest[]= {45, 20, 35, 10, 50, 5, 60};
    List list;
    List sstf;
    List scan;
    if (argc == 1) {
        list = generate_random_list();
        sstf = SSFT(list);
        printf("order of SSTF algorithm is:\n");
        print_list(sstf);
        printf("\n---------------------\n");

        scan = SCAN(list);
        printf("order of SCAN algorithm is:\n");
        print_list(scan);
    } else {
        int request[argc - 1];
        for (size_t i = 0; i < argc; i++)
        {
            request[i - 1] = atoi(argv[i]);
        }
        list.array = request;
        list.length = argc - 1;
        sstf = SSFT(list);
        printf("order of SSTF algorithm is:\n");
        print_list(sstf);
        printf("\n---------------------\n");

        scan = SCAN(list);
        printf("order of SCAN algorithm is:\n");
        print_list(scan);
    }

    // order1 = SSFT(list);
    // printf("order of SSTF algorithm is:\n");
    // print_list(order1);
    return 0;
}