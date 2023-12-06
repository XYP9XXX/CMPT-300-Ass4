//
// Created by lizuoqiu on 12/5/23.
//

#ifndef CMPT_300_ASS4_LIST_H
#define CMPT_300_ASS4_LIST_H
#include "globalConfig.h"
typedef struct MY_LIST List;
struct MY_LIST {
    int* array;
    int length;
    int count_tracks;
    int longest_delay;
};
#endif //CMPT_300_ASS4_LIST_H
