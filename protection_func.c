/*
 * protection_func.c
 *
 *  Created on: Dec 28, 2020
 *      Author: Tinh_deptrai
 */

#include "tida01606_define.h"



void tida_01606_setup_protection(uint32_t ePWM1_base,
                                 uint32_t ePWM2_base,
                                 uint32_t ePWM3_base,
                                 uint32_t ePWM4_base,
                                 uint32_t ePWM5_base,
                                 uint32_t ePWM6_base,
                                 float current_limit,
                                 float current_max){
    //
    // disable X-Bar ePWM first
    //
    XBAR_disableEPWMMux(XBAR_TRIP4, (XBAR_MUX06 | XBAR_MUX08 | XBAR_MUX14));

}


