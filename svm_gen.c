/*
 * svm_gen.c
 *
 *  Created on: Dec 21, 2020
 *      Author: Tinh_deptrai
 */


#include "svm_gen.h"

int16_t svm_gen(INPUT_SVM *input,
                 SECTOR_SECLECT* csector,
                 TIME_VECTOR *time_vector,
                 TIME_VECTOR_OUT *time_out,
                 EPWM_COUNTER *epwm_counter )
{
    // ham chon sector
    int i = Seclect_sector_subsector(input, csector);
    if ( i < 0) return -1;
    // ham tinh toan ta tb tc
    i = Calculate_time_vector( input, time_vector, csector);
    if ( i < 0) return -1;
    // ham tinh toan thoi gian out
    i = Calculate_time_out(csector, time_vector, time_out);
    if ( i < 0) return -1;
    // nam thoi gian cho thanh ghi
    Assign_ePWM_counter(time_out, epwm_counter);
    return 1;
}


int16_t Seclect_sector_subsector(INPUT_SVM *input, SECTOR_SECLECT* csector)
{
    // tinh toan x y z de chonj sector
    float x = input->ub;
    float y = 0.8660254f*input->ua - 0.5f*input->ub;
    float z =-0.8660254f*input->ua - 0.5f*input->ua;
    // xac dinh sector
    int sector = 0;
    if(x>=0)
        sector = sector +1;
    if(y>=0)
        sector = sector +2;
    if(z>=0)
        sector = sector + 4;
    if( sector <= 0) return -1; // error here
    // tao uac va ubc de chon subsector
    float uac = 0;
    float ubc = 0;
    switch(sector){
    case 3:
        uac = input->ua;
        ubc = input->ub;
        break;
    case 1:
        uac = 0.5*input->ua + 0.8660254f*input->ub;
        ubc =-0.8660254f*input->ua + 0.5*input->ub;
        break;
    case 5:
        uac =-0.5*input->ua + 0.8660254f*input->ub;
        ubc =-0.8660254f*input->ua - 0.5*input->ub;
        break;
    case 4:
        uac =-input->ua;
        ubc =-input->ub;
        break;
    case 6:
        uac =-0.5f*input->ua - 0.8660254f*input->ub;
        ubc = 0.8660254f*input->ua - 0.5f*input->ub;
        break;
    case 2:
        uac = 0.5f*input->ua - 0.8660254f*input->ub;
        ubc = 0.8660254f*input->ua + 0.5f*input->ub;
        break;
    default: uac = 0;ubc = 0;
    break;
    }

    // tinh toan l1 l2 l3 cac duong phan chia mat phang

    float l1 = ubc - 1.7320508f*uac + input->udc;
    float l2 = ubc - 0.5f*input->udc;
    float l3 = ubc + 1.7320508f*uac - input->udc;

    //
    int sub_sector = -1;
    if( l3 < 0)
        sub_sector = 1;
    else if (l1 <= 0 )
        sub_sector = 3;
    else if ( l2 >= 0)
        sub_sector = 4;
    else
        sub_sector = 2;
    if(sub_sector <= 0) return -1; // error here

    csector->sector = sector ;
    csector->subsector = sub_sector;
    return 1;
}



int16_t Calculate_time_vector(INPUT_SVM *input,
                               TIME_VECTOR *time_vector,
                               SECTOR_SECLECT *csector){
    // tinh toan thoi gian cua vector
    float ua_c, ub_c, ta_temp, tb_temp, tc_temp;
    ua_c = input->ua/input->udc;
    ub_c = input->ub/input->udc;

    ta_temp  = 1.7320508f*ua_c -  ub_c;
    tb_temp  = 1.7320508f*ua_c  + ub_c;
    tc_temp  = 2*ub_c;
        float ta, tb, tc;
        // lua chon theo sub_sector truoc roi sau do moi chon theo sector
        // co nhieu phuong phap thuc hien, day chi la vidu do minh nghi ra
        switch( csector->subsector){
        case 1:
            // lua chon theo sector do day
              switch(csector->sector){
              case 3:
                  ta = ta_temp;
                  tb =-tb_temp + 1;
                  tc = tc_temp;
                  break;
              case 1:
                  ta =-ta_temp;
                  tb =-tc_temp + 1;
                  tc = tb_temp;
                  break;
              case 5:
                  ta = tc_temp;
                  tb = ta_temp + 1;
                  tc =-tb_temp;
                  break;
              case 4:
                  ta =-tc_temp;
                  tb = tb_temp + 1;
                  tc =-ta_temp;
                  break;
              case 6:
                  ta =-tb_temp;
                  tb = tc_temp + 1;
                  tc = ta_temp;
                  break;
              case 2:
                  ta = tb_temp;
                  tb =-ta_temp + 1;
                  tc =-tc_temp;
                  break;
              default: ta = -1; tb = -1; tc = -1;
                  break ;
              }
              break;
              //------------------------------------------------------------------
        case 2:
            // lua chon theo sector do day
              switch(csector->sector){
              case 3:
                  ta =-tc_temp + 1;
                  tb = tb_temp - 1;
                  tc =-ta_temp + 1;
                  break;
              case 1:
                  ta =-tb_temp + 1;
                  tb = tc_temp - 1;
                  tc = ta_temp + 1;
                  break;
              case 5:
                  ta = tb_temp + 1;
                  tb =-ta_temp - 1;
                  tc =-tc_temp + 1;
                  break;
              case 4:
                  ta = ta_temp + 1;
                  tb =-tb_temp - 1;
                  tc = tc_temp + 1;
                  break;
              case 6:
                  ta =-ta_temp + 1;
                  tb =-tc_temp - 1;
                  tc = tb_temp + 1;
                  break;
              case 2:
                  ta = tc_temp + 1;
                  tb = ta_temp - 1;
                  tc =-tb_temp + 1;
                  break;
              default: ta = -1; tb = -1; tc = -1;
                  break;
              }
              break;
              //------------------------------------------------------------------
        case 3:
            // lua chon theo sector do day
              switch(csector->sector){
              case 3:
                  ta =-tb_temp + 2;
                  tb = tc_temp;
                  tc = ta_temp - 1;
                  break;
              case 1:
                  tc =-tc_temp + 2;
                  tb =-ta_temp;
                  ta = tb_temp - 1;
                  break;
              case 5:
                  ta = ta_temp + 2;
                  tb =-tb_temp;
                  tc = tc_temp - 1;
                  break;
              case 4:
                  tc = tb_temp + 2;
                  ta =-ta_temp - 1;
                  tb =-tc_temp;
                  break;
              case 6:
                  ta = tc_temp + 2;
                  tb = ta_temp;
                  tc =-tb_temp - 1;
                  break;
              case 2:
                  tc =-ta_temp + 2;
                  ta =-tc_temp - 1;
                  tb = tb_temp;
                  break;
              default: ta = -1; tb = -1; tc = -1;
                  break;
        }
              break;
              //------------------------------------------------------------------
        case 4:
            // lua chon theo sector do day
              switch(csector->sector){
              case 3:
                  ta = tc_temp - 1;
                  tb = ta_temp;
                  tc =-tb_temp + 2;
                  break;
              case 1:
                  tb = tb_temp;
                  tc =-ta_temp - 1;
                 ta =-tc_temp + 2;
                  break;
              case 5:
                  tb = tc_temp ;
                  ta =-tb_temp - 1;
                  tc = ta_temp + 2;
                  break;
              case 4:
                  tc =-tc_temp - 1;
                  ta = tb_temp + 2;
                  tb =-ta_temp;
                  break;
              case 6:
                  ta = ta_temp - 1;
                  tb =-tb_temp;
                  tc = tc_temp + 2;
                  break;
              case 2:
                  ta =-ta_temp + 2;
                  tb =-tc_temp;
                  tc = tb_temp - 1;
                  break;
              default: ta = -1; tb = -1; tc = -1;
                  break;
              }
              break;
              //------------------------------------------------------------------
        default : ta = tb = tc = -1;
        break;
              }
        if( (ta < 0)||(tb < 0)||(tc < 0)) return -1;
        time_vector->ta = ta;
        time_vector->tb = tb;
        time_vector->tc = tc;
        return 1;
}



int16_t Calculate_time_out(SECTOR_SECLECT *csector,
                            TIME_VECTOR *time,
                            TIME_VECTOR_OUT *time_out){
// warning khong sao do bien truyen vao la bien global
    float t1, t2, t3, t4, t5, t6;
    switch(csector->subsector){
    case 1:
        t1 = time->tb*0.125f;
        t2 = time->tb*0.125f + time->ta*0.25f;
        t3 = time->ta*0.25f + time->tb*0.125f + time->tc*0.25f;
        t4 = time->ta*0.25f + time->tb*0.375f + 0.25f*time->tc;
        t5 = time->ta*0.5f + time->tb*0.375f + 0.25f*time->tc;
        t6 = 0.5f*time->ta + 0.375f*time->tb + 0.5f*time->tc;
        switch(csector->sector){
        case 3:
            time_out->t1out = t4;
            time_out->t2out = t1;
            time_out->t3out = t5;
            time_out->t4out = t2;
            time_out->t5out = t6;
            time_out->t6out = t3;
            break;
        case 1:
            time_out->t1out = t5;
            time_out->t2out = t2;
            time_out->t3out = t4;
            time_out->t4out = t1;
            time_out->t5out = t6;
            time_out->t6out = t3;
            break;
        case 5:
            time_out->t1out = t6;
            time_out->t2out = t3;
            time_out->t3out = t4;
            time_out->t4out = t1;
            time_out->t5out = t5;
            time_out->t6out = t2;
            break;
        case 4:
            time_out->t1out = t6;
            time_out->t2out = t3;
            time_out->t3out = t5;
            time_out->t4out = t2;
            time_out->t5out = t4;
            time_out->t6out = t1;
            break;
        case 6:
            time_out->t1out = t5;
            time_out->t2out = t2;
            time_out->t3out = t6;
            time_out->t4out = t3;
            time_out->t5out = t4;
            time_out->t6out = t1;
            break;
        case 2:
            time_out->t1out = t4;
            time_out->t2out = t1;
            time_out->t3out = t6;
            time_out->t4out = t3;
            time_out->t5out = t5;
            time_out->t6out = t2;
        default:
            time_out->t1out = -1;
            time_out->t2out = -1;
            time_out->t3out = -1;
            time_out->t4out = -1;
            time_out->t5out = -1;
            time_out->t6out = -1;
            break;
        }
        break;
      //----------------------------------------------------------------------------
    case 2:
        t1 = 0;
        t2 = time->ta*0.25;
        t3 = time->ta*0.25 + 0.25*time->tc;
        t4 = time->ta*0.25 + 0.25*time->tc + 0.5*time->tb;
        t5 = time->ta*0.5  + 0.25*time->tc + 0.5*time->tb;
        t6 = 0.5;
        switch(csector->sector){
        case 3:
            time_out->t1out = t3;
            time_out->t2out = t1;
            time_out->t3out = t5;
            time_out->t4out = t2;
            time_out->t5out = t6;
            time_out->t6out = t4;
            break;
        case 1:
            time_out->t1out = t5;
            time_out->t2out = t2;
            time_out->t3out = t3;
            time_out->t4out = t1;
            time_out->t5out = t6;
            time_out->t6out = t4;
            break;
        case 5:
            time_out->t1out = t6;
            time_out->t2out = t4;
            time_out->t3out = t3;
            time_out->t4out = t1;
            time_out->t5out = t5;
            time_out->t6out = t2;
            break;
        case 4:
            time_out->t1out = t6;
            time_out->t2out = t4;
            time_out->t3out = t5;
            time_out->t4out = t2;
            time_out->t5out = t3;
            time_out->t6out = t1;
            break;
        case 6:
            time_out->t1out = t5;
            time_out->t2out = t2;
            time_out->t3out = t6;
            time_out->t4out = t4;
            time_out->t5out = t3;
            time_out->t6out = t1;
            break;
        case 2:
            time_out->t1out = t3;
            time_out->t2out = t1;
            time_out->t3out = t6;
            time_out->t4out = t4;
            time_out->t5out = t5;
            time_out->t6out = t2;
        default:
            time_out->t1out = -1;
            time_out->t2out = -1;
            time_out->t3out = -1;
            time_out->t4out = -1;
            time_out->t5out = -1;
            time_out->t6out = -1;
            break;
        }
        break;
        //----------------------------------------------------------------------------
    case 3:
        switch(csector->sector){
        case 3:
            time_out->t1out = 0.25*time->ta;
            time_out->t2out = 0;
            time_out->t3out = 0.5;
            time_out->t4out = 0.25*time->ta + 0.5*time->tc;
            time_out->t5out = 0.5;
            time_out->t6out = 0.25*time->ta + 0.5*time->tc + 0.5*time->tb;
            break;
        case 1:
            time_out->t1out = 0.25*time->tc + 0.5*time->tb;
            time_out->t2out = 0;
            time_out->t3out = 0.25*time->tc;
            time_out->t4out = 0;
            time_out->t5out = 0.5;
            time_out->t6out = 0.25*time->tc + 0.5*time->tb + 0.5*time->ta;
            break;
        case 5:
            time_out->t1out = 0.5;
            time_out->t2out = 0.25f*time->ta + 0.5f*time->tc + 0.5f*time->tb;
            time_out->t3out = 0.25*time->ta;
            time_out->t4out = 0;
            time_out->t5out = 0.5;
            time_out->t6out = 0.25f*time->ta + 0.5f*time->tc;
            break;
        case 4:
            time_out->t1out = 0.5;
            time_out->t2out = 0.25f*time->tc + 0.5f*time->tb +0.5f*time->ta;
            time_out->t3out = 0.25f*time->tc + 0.5f*time->tb;
            time_out->t4out = 0;
            time_out->t5out = 0.25*time->tc;
            time_out->t6out = 0;
            break;
        case 6:
            time_out->t1out = 0.5;
            time_out->t2out = 0.25f*time->ta + 0.5f*time->tc;
            time_out->t3out = 0.5;
            time_out->t4out = 0.25f*time->ta + 0.5f*time->tc + 0.5f*time->tb;
            time_out->t5out = 0.25*time->ta;
            time_out->t6out = 0;
            break;
        case 2:
            time_out->t1out = 0.25*time->tc;
            time_out->t2out = 0;
            time_out->t3out = 0.5;
            time_out->t4out = 0.25f*time->tc + 0.5f*time->tb + 0.5f*time->ta;
            time_out->t5out = 0.25f*time->tc + 0.5f*time->tb;
            time_out->t6out = 0;
        default:
            time_out->t1out = -1;
            time_out->t2out = -1;
            time_out->t3out = -1;
            time_out->t4out = -1;
            time_out->t5out = -1;
            time_out->t6out = -1;
            break;
        }

        break;

        //----------------------------------------------------------------------------
    case 4:
        switch(csector->sector){
        case 3:
            time_out->t1out = 0.25f*time->tc;
            time_out->t2out = 0;
            time_out->t3out = 0.25f*time->tc + 0.5f*time->tb;
            time_out->t4out = 0;
            time_out->t5out = 0.5;
            time_out->t6out = 0.25f*time->tc + 0.5f*time->tb + 0.5f*time->ta;
            break;
        case 1:
            time_out->t1out = 0.5;
            time_out->t2out = 0.25f*time->ta + 0.5f*time->tc;
            time_out->t3out = 0.25f*time->ta;
            time_out->t4out = 0;
            time_out->t5out = 0.5f;
            time_out->t6out = 0.25f*time->ta + 0.5f*time->tc + 0.5f*time->tb;
            break;
        case 5:
            time_out->t1out = 0.5;
            time_out->t2out = 0.25f*time->tc + 0.5f*time->tb + 0.5f*time->ta;
            time_out->t3out = 0.25f*time->tc;
            time_out->t4out = 0;
            time_out->t5out = 0.25f*time->tc + 0.5f*time->tb;
            time_out->t6out = 0;
            break;
        case 4:
            time_out->t1out = 0.5;
            time_out->t2out = 0.25f*time->ta + 0.5f*time->tc + 0.5f*time->tb;
            time_out->t3out = 0.5;
            time_out->t4out = 0.25f*time->ta + 0.5f*time->tc;
            time_out->t5out = 0.25f*time->ta;
            time_out->t5out = 0;
            break;
        case 6:
            time_out->t1out = 0.25f*time->tc + 0.25f*time->tb;
            time_out->t2out = 0;
            time_out->t3out = 0.5;
            time_out->t4out = 0.25f*time->tc + 0.5f*time->tb + 0.5f*time->ta;
            time_out->t5out = 0.25f*time->tc;
            time_out->t5out = 0;
            break;
        case 2:
            time_out->t1out = 0.25*time->ta;
            time_out->t2out = 0;
            time_out->t3out = 0.5;
            time_out->t4out = 0.25f*time->ta + 0.5f*time->tc + 0.5f*time->tb;
            time_out->t5out = 0.5;
            time_out->t6out = 0.25f*time->ta + 0.5f*time->tc;
        default:
            time_out->t1out = -1;
            time_out->t2out = -1;
            time_out->t3out = -1;
            time_out->t4out = -1;
            time_out->t5out = -1;
            time_out->t6out = -1;
            break;
        }

        break;


        //----------------------------------------------------------------------------
    default:
        time_out->t1out = -1;
        time_out->t2out = -1;
        time_out->t3out = -1;
        time_out->t4out = -1;
        time_out->t5out = -1;
        time_out->t6out = -1;
        break;

    }
    if((time_out->t1out == -1)||(time_out->t2out == -1)
            ||(time_out->t3out == -1)||(time_out->t4out == -1)
            ||(time_out->t5out == -1)||(time_out->t6out == -1)) return -1;
    else return 1;
}


uint16_t Assign_ePWM_counter(TIME_VECTOR_OUT *time_out, EPWM_COUNTER *counter){
    counter->epwm1a = (uint16_t)(time_out->t1out*TINV_INV_PWM_PERIOD/2);
    counter->epwm2a = (uint16_t)(time_out->t2out*TINV_INV_PWM_PERIOD/2);
    counter->epwm1b = (uint16_t)(time_out->t3out*TINV_INV_PWM_PERIOD/2);
    counter->epwm2b = (uint16_t)(time_out->t4out*TINV_INV_PWM_PERIOD/2);
    counter->epwm1c = (uint16_t)(time_out->t5out*TINV_INV_PWM_PERIOD/2);
    counter->epwm2c = (uint16_t)(time_out->t6out*TINV_INV_PWM_PERIOD/2);

    // set epwm counter real
    uint16_t i = EPWM_getCounterCompareValue(TINV_INV_PWM_Q1A_BASE, EPWM_COUNTER_COMPARE_A );
    EPWM_setCounterCompareValue(TINV_INV_PWM_Q1A_BASE, EPWM_COUNTER_COMPARE_A, counter->epwm1a);

     i = EPWM_getCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A );
    EPWM_setCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A, counter->epwm2a);

     i = EPWM_getCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A );
    EPWM_setCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A, counter->epwm1b);

     i = EPWM_getCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A );
    EPWM_setCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A, counter->epwm2b);

     i = EPWM_getCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A );
    EPWM_setCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A, counter->epwm1c);

     i = EPWM_getCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A );
    EPWM_setCounterCompareValue(TINV_INV_PWM_Q2A_BASE, EPWM_COUNTER_COMPARE_A, counter->epwm2c);
    return 1;
}



// end of file

