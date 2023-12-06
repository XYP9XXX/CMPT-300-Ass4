#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "sstf.h"
#include "scan.h"
#include "utils.h"

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
        if (isNumbersAndCommasOnly(raw) == 0){
            printf("wrong input format, please only contain number and comma as spliting \n");
            exit(0);
        }
        char* temp = malloc(strlen(raw));
        strcpy(temp, raw);
        temp = strtok(temp, ",");
        int size = 0;
        while (temp != NULL){
            int element = atoi(temp);
            if(element < 0 || element > 199){
                printf("please name the track number within range [0,199] \n");
                exit(0);
            }
            size ++;
            temp = strtok(NULL, ",");
        }
        if(size < 3) {
            printf("please list at least 3 tracks \n");
            exit(0);
        }
        char* splitTemp = malloc(strlen(raw));
        splitTemp = strcpy(splitTemp, raw);
        splitTemp = strtok(splitTemp, ",");

        int request[size];
        for (int i = 0; i < size; i++)
        {
            int item = atoi(splitTemp);
            for(int j = 0; j < i; j++){
                if(request[j] == item){
                    printf("you cannot use duplicate track number \n");
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