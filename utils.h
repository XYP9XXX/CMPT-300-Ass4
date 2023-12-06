//
// Created by lizuoqiu on 12/5/23.
//

#ifndef CMPT_300_ASS4_UTILS_H
#define CMPT_300_ASS4_UTILS_H
#include "list.h"


int isElementInArray(int array[], int size, int element);
void print_list(List list);
List generate_random_list ();
double count_average_delay(List FCFS, List Another_Algorighm);
int isNumbersAndCommasOnly(const char *str);
#endif //CMPT_300_ASS4_UTILS_H
