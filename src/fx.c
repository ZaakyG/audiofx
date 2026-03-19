#ifndef FX_H
#define FX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"

int volumeReduction(int16_t *samples, long num_samples, int factor){
    printf("Reducing volume by %d\n", factor);
    for (int i=0; i<num_samples; i++){
        samples[i] = samples[i]/factor;
    } 
}


#endif
