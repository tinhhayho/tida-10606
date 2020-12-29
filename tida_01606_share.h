/*
 * tida_01606_share.h
 *
 *  Created on: Dec 26, 2020
 *      Author: Tinh_deptrai
 */

#ifndef TIDA_01606_SHARE_H_
#define TIDA_01606_SHARE_H_

#include <stdint.h>




typedef struct {
    // vgrid
    float Vgrid_A ;
    float Vgrid_B ;
    float Vgrid_C ;
    // igrid
    float Igrid_A ;
    float Igrid_B ;
    float Igrid_C ;
    // i inverter
    float Iinv_A ;
    float Iinv_B ;
    float Iinv_C ;
    // v inverter
    float Vinv_A ;
    float Vinv_B ;
    float Vinv_C ;
    // v bus
    float Vbus   ;
    // temparature
    float temp_A ;
    float temp_B ;
    float temp_C ;
    float temp_Amp;
} CONTROL_VALUE;

typedef struct {
    // VGRID
    float Vgrid_A_rms;
    float Vgrid_B_rms;
    float Vgrid_C_rms;
    // IGRID
    float Igrid_A_rms;
    float Igrid_B_rms;
    float Igrid_C_rms;
    // V inverter
    float Vinv_A_rms;
    float Vinv_B_rms;
    float Vinv_C_rms;
    // I inverter
    float Iinv_A_rms;
    float Iinv_B_rms;
    float Iinv_C_rms;

} RMS_VALUE;
extern CONTROL_VALUE control_value;
extern RMS_VALUE rms_value;







#endif /* TIDA_01606_SHARE_H_ */
