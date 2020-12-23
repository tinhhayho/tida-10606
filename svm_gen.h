/*
 * svm_gen.h
 *
 *  Created on: Dec 21, 2020
 *      Author: Tinh_deptrai
 *      input : uapha , ubeta, udc ( da chuan hoa)
 *      output: time counter for epwm
 */

#ifndef SVM_GEN_H_
#define SVM_GEN_H_
#include "tida01606_define.h"

#define code1

static char sector[20], time_[20], timeout_[20], comp[20];


typedef struct {
    float ua;
    float ub;
    float udc;
}  INPUT_SVM;

typedef struct {
    uint16_t sector ;
    uint16_t subsector;
} SECTOR_SECLECT;

typedef struct {
    float ta;
    float tb;
    float tc;
} TIME_VECTOR;

typedef struct {
    float t1out;
    float t2out;
    float t3out;
    float t4out;
    float t5out;
    float t6out;
} TIME_VECTOR_OUT;

typedef struct {
    uint16_t epwm1a;
    uint16_t epwm2a;
    uint16_t epwm1b;
    uint16_t epwm2b;
    uint16_t epwm1c;
    uint16_t epwm2c;
} EPWM_COUNTER;




extern int16_t svm_gen(INPUT_SVM *input,
                 SECTOR_SECLECT* csector,
                 TIME_VECTOR *time_vector,
                 TIME_VECTOR_OUT *time_out,
                 EPWM_COUNTER* epwm_counter );


extern int16_t Seclect_sector_subsector(INPUT_SVM *input,
                                  SECTOR_SECLECT* csector);

extern int16_t Calculate_time_vector(INPUT_SVM *input,
                               TIME_VECTOR *time_vector,
                               SECTOR_SECLECT *csector);


extern int16_t Calculate_time_out(SECTOR_SECLECT *csector,
                            TIME_VECTOR *time,
                            TIME_VECTOR_OUT *time_out);

extern uint16_t Assign_ePWM_counter(TIME_VECTOR_OUT *time_out,
                             EPWM_COUNTER *counter);


#endif /* SVM_GEN_H_ */
