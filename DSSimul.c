#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 200;
#define RANDOM_ARR_SIZE 50;

typedef struct MY_LIST List;
struct MY_LIST
{
    int* array;
    int length;
    int count_tracks;
    int longest_delay;
};


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

// Helper function used to calculate the absolute distance between two tracks.
int abs_diff(int x, int y) {
    return x > y ? x - y : y - x;
}

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


int main(int argc, char *argv[]) {
    List list;
    List sstf;
    List scan;
    if (argc == 1) {
        list = generate_random_list();
        printf("The original request list of track numbers is: \n");
        print_list(list);
        printf("\n---------------------\n");

        sstf = SSTF(list);
        printf("order of SSTF algorithm is:\n");
        print_list(sstf);
        printf("\nTotal number of tracks traversed by SSFT algorithm is %d,", sstf.count_tracks);
        printf("\n---------------------\n");

        scan = SCAN(list);
        printf("order of SCAN algorithm is:\n");
        print_list(scan);
        printf("\nTotal number of tracks traversed by SCAN algorithm is: %d", scan.count_tracks);
        printf("\n---------------------\n");

        printf("The longest delay for SSFT is: %d\n", sstf.longest_delay);
        printf("The longest delay for SCAN is: %d", scan.longest_delay);
        printf("\n---------------------\n");

        printf("Average delay of SSTF is: %f \n", count_average_delay(list, sstf));
        printf("Average delay of SCAN is: %f \n", count_average_delay(list, scan));
    } else {
        char* raw = argv[1];
        char* temp = malloc(strlen(raw));
        strcpy(temp, raw);
        temp = strtok(temp, ",");
        int size = 0;
        while (temp != NULL){
            int element = atoi(temp);
            if(element < 0 || element > 199){
                printf("please name the track number within range [0,199]");
                exit(0);
            }
            size ++;
            temp = strtok(NULL, ",");
        }
        if(size < 3) {
            printf("please list at least 3 tracks");
            exit(0);
        }
        char* splitTemp = malloc(strlen(raw));
        splitTemp = strcpy(splitTemp, raw);
        splitTemp = strtok(splitTemp, ",");

        int request[size];
        for (int i = 0; i < size; i++)
        {
            int item = atoi(splitTemp);
            for(int j = 0; j<i; j++){
                if(request[j] == item){
                    printf("you cannot use duplicate track number");
                    exit(0);
                }
            }
            request[i] = item;
            splitTemp = strtok(NULL, ",");
        }
        list.array = request;
        list.length = size;
        printf("The original request list of track numbers is: \n");
        print_list(list);
        printf("\n---------------------\n");

        sstf = SSTF(list);
        printf("order of SSTF algorithm is:\n");
        print_list(sstf);
        printf("\nTotal number of tracks traversed by SSFT algorithm is %d,", sstf.count_tracks);
        printf("\n---------------------\n");

        scan = SCAN(list);
        printf("order of SCAN algorithm is:\n");
        print_list(scan);
        printf("\nTotal number of tracks traversed by SCAN algorithm is: %d", scan.count_tracks);
        printf("\n---------------------\n");

        printf("The longest delay for SSFT is: %d\n", sstf.longest_delay);
        printf("The longest delay for SCAN is: %d", scan.longest_delay);
        printf("\n---------------------\n");

        printf("Average delay of SSTF is: %f \n", count_average_delay(list, sstf));
        printf("Average delay of SCAN is: %f \n", count_average_delay(list, scan));
    }
    return 0;
}