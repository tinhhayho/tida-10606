#include "tida01606_define.h"

// co 3 thanh phan gpio chinh
// pwm
// adc
// RDY (gate drive) power good output - active high when both supplies are good
// RST (gate drive) reset gate drive
// relay
// fan

void tida01606_setupGPIO(uint16_t isPWM,
                         uint16_t isADC,
                         uint16_t isRelay,
                         uint16_t isFan,
                         uint16_t isEnPWM)
{
    // gpio must be set
    // pwm nguon luon phai bat
    // PWM HIGH SIDE AND LOW SIDE OF POWER ISOLATION
    GPIO_setPadConfig(10, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_10_EPWM6A);
    GPIO_setPadConfig(11, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_11_EPWM6B);
    // rdy as input
    GPIO_setDirectionMode(TINV_GPIO_RDY, GPIO_DIR_MODE_IN);
    GPIO_setQualificationMode(TINV_GPIO_RDY, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(TINV_GPIO_RDY_PIN_CONFIG);
    // reset as output ( active low)
    GPIO_setDirectionMode(TINV_GPIO_GATE_RST, GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(TINV_GPIO_GATE_RST, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(TINV_GPIO_GATE_RST_PIN_CONFIG);
    GPIO_writePin(TINV_GPIO_GATE_RST, 1);
    //
    if(isEnPWM==1)
    {
        GPIO_setPadConfig(TINV_GPIO_PWM_EN, GPIO_PIN_TYPE_STD);
        GPIO_setDirectionMode(TINV_GPIO_PWM_EN, GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(TINV_GPIO_PWM_EN, GPIO_QUAL_ASYNC);
        GPIO_setPinConfig(GPIO_43_GPIO43);
        GPIO_writePin(TINV_GPIO_PWM_EN, 1);
    }
    if(isPWM == 1)
    {
        // Q1A - Q3A
        GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD); //push-pull output or floating input
        GPIO_setPinConfig(GPIO_0_EPWM1A);
        GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD); //push-pull output or floating input
        GPIO_setPinConfig(GPIO_1_EPWM1B);
        // Q2A - Q4A
        GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD); //push-pull output or floating input
        GPIO_setPinConfig(GPIO_2_EPWM2A);
        GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD); //push-pull output or floating input
        GPIO_setPinConfig(GPIO_3_EPWM2B);
        // Q1B - Q3B
        GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD); //push-pull output or floating input
        GPIO_setPinConfig(GPIO_4_EPWM3A);
        GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD); //push-pull output or floating input
        GPIO_setPinConfig(GPIO_5_EPWM3B);
        // Q2B-Q4B
        GPIO_setPadConfig(6, GPIO_PIN_TYPE_STD); //push-pull output or floating input
        GPIO_setPinConfig(GPIO_6_EPWM4A);
        GPIO_setPadConfig(7, GPIO_PIN_TYPE_STD); //push-pull output or floating input
        GPIO_setPinConfig(GPIO_7_EPWM4B);
        // Q1C-Q3C
        GPIO_setPadConfig(12, GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(GPIO_12_EPWM7A);
        GPIO_setPadConfig(13, GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(GPIO_13_EPWM7B);
        // Q2C-Q4C
        GPIO_setPadConfig(14, GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(GPIO_14_EPWM8A);
        GPIO_setPadConfig(15, GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(GPIO_15_EPWM8B);
    }
    //
    if(isADC==1)
    {
        // nothing here because analog io dont need configure
    }
    //
    if(isRelay ==1)
    {
        GPIO_setDirectionMode(TINV_GPIO_RELAY_A, GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(TINV_GPIO_RELAY_A, GPIO_QUAL_ASYNC);
        GPIO_setPinConfig(TINV_GPIO_RELAY_A_PIN_CONFIG);

        GPIO_setDirectionMode(TINV_GPIO_RELAY_B, GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(TINV_GPIO_RELAY_B, GPIO_QUAL_ASYNC);
        GPIO_setPinConfig(TINV_GPIO_RELAY_B_PIN_CONFIG);

        GPIO_setDirectionMode(TINV_GPIO_RELAY_C, GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(TINV_GPIO_RELAY_C, GPIO_QUAL_ASYNC);
        GPIO_setPinConfig(TINV_GPIO_RELAY_C_PIN_CONFIG);

        GPIO_setDirectionMode(TINV_GPIO_RELAY_N, GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(TINV_GPIO_RELAY_N, GPIO_QUAL_ASYNC);
        GPIO_setPinConfig(TINV_GPIO_RELAY_N_PIN_CONFIG);
    }
    //
    if(isFan ==1)
    {
        GPIO_setDirectionMode(TINV_GPIO_FAN, GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(TINV_GPIO_FAN, GPIO_QUAL_ASYNC);
        GPIO_setPinConfig(TINV_GPIO_FAN_PIN_CONFIG);
    }

}

void tida016060_enable_disable_Relay(uint16_t phase)
{
    switch(phase){
    case 0:
        GPIO_writePin(TINV_GPIO_RELAY_A,0);
        GPIO_writePin(TINV_GPIO_RELAY_B,0);
        GPIO_writePin(TINV_GPIO_RELAY_C,0);
        GPIO_writePin(TINV_GPIO_RELAY_N,0);
        break;
    case 3:
        GPIO_writePin(TINV_GPIO_RELAY_A,1);
        GPIO_writePin(TINV_GPIO_RELAY_B,1);
        GPIO_writePin(TINV_GPIO_RELAY_C,1);
        GPIO_writePin(TINV_GPIO_RELAY_N,0);
        break;
    case 4:
        GPIO_writePin(TINV_GPIO_RELAY_A,1);
        GPIO_writePin(TINV_GPIO_RELAY_B,1);
        GPIO_writePin(TINV_GPIO_RELAY_C,1);
        GPIO_writePin(TINV_GPIO_RELAY_N,1);
        break;
    default:
        GPIO_writePin(TINV_GPIO_RELAY_A,0);
        GPIO_writePin(TINV_GPIO_RELAY_B,0);
        GPIO_writePin(TINV_GPIO_RELAY_C,0);
        GPIO_writePin(TINV_GPIO_RELAY_N,0);
        break;
    }


}

void tida01606_setupADC(void)
{
    //
    // Write ADC configurations and power up the ADC for both ADC A
    //
    uint16_t i;
    //
    // write configurations for ADC-A
    //set ADCCLK divider to /4
    //
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);

    //
    // power up the ADC
    //
    ADC_enableConverter(ADCA_BASE);

    //
    // write configurations for ADC-B
    //set ADCCLK divider to /
    //
    ADC_setPrescaler(ADCB_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCB_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCB_BASE, ADC_PULSE_END_OF_CONV);

    //
    // power up the ADC
    //
    ADC_enableConverter(ADCB_BASE);

    //
    // write configurations for ADC-C
    // External REFERENCE must be provided
    //
    ADC_setPrescaler(ADCC_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCC_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCC_BASE, ADC_PULSE_END_OF_CONV);

    //
    // power up the ADC
    //
    ADC_enableConverter(ADCC_BASE);

    //
    // write configurations for ADC-C
    // External REFERENCE must be provided
    //
    ADC_setPrescaler(ADCD_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCD_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCD_BASE, ADC_PULSE_END_OF_CONV);

    //
    // power up the ADC
    //
    ADC_enableConverter(ADCD_BASE);

    //
    // delay for > 1ms to allow ADC time to power up
    //
    for (i = 0; i < 1000; i++)
    {
        __asm ("   RPT#255 || NOP");
    }

    ADC_setupSOC(TINV_IL_A_ADC_BASE,
                 TINV_IL_A_ADC_SOC_NO,
                 TINV_IL_A_ADC_TRIG_SOURCE,
                 TINV_IL_A_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_IL_B_ADC_BASE,
                 TINV_IL_B_ADC_SOC_NO,
                 TINV_IL_B_ADC_TRIG_SOURCE,
                 TINV_IL_B_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_IL_C_ADC_BASE,
                 TINV_IL_C_ADC_SOC_NO,
                 TINV_IL_C_ADC_TRIG_SOURCE,
                 TINV_IL_C_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);

    ADC_setupSOC(TINV_VGRID_A_ADC_BASE,
                 TINV_VGRID_A_ADC_SOC_NO,
                 TINV_VGRID_A_ADC_TRIG_SOURCE,
                 TINV_VGRID_A_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_VGRID_B_ADC_BASE,
                 TINV_VGRID_B_ADC_SOC_NO,
                 TINV_VGRID_B_ADC_TRIG_SOURCE,
                 TINV_VGRID_B_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_VGRID_C_ADC_BASE,
                 TINV_VGRID_C_ADC_SOC_NO,
                 TINV_VGRID_C_ADC_TRIG_SOURCE,
                 TINV_VGRID_C_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);

    ADC_setupSOC(TINV_VINV_A_ADC_BASE,
                 TINV_VINV_A_ADC_SOC_NO,
                 TINV_VINV_A_ADC_TRIG_SOURCE,
                 TINV_VINV_A_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_VINV_B_ADC_BASE,
                 TINV_VINV_B_ADC_SOC_NO,
                 TINV_VINV_B_ADC_TRIG_SOURCE,
                 TINV_VINV_B_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_VINV_C_ADC_BASE,
                 TINV_VINV_C_ADC_SOC_NO,
                 TINV_VINV_C_ADC_TRIG_SOURCE,
                 TINV_VINV_C_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);

    ADC_setupSOC(TINV_VBUS_ADC_BASE,
                 TINV_VBUS_ADC_SOC_NO,
                 TINV_VBUS_ADC_TRIG_SOURCE,
                 TINV_VBUS_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);

    ADC_setupSOC(TINV_HAL_TEMP_A_ADC_BASE,
                 TINV_HAL_TEMP_A_ADC_SOC_NO,
                 TINV_HAL_TEMP_A_ADC_TRIG_SOURCE,
                 TINV_HAL_TEMP_A_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_HAL_TEMP_B_ADC_BASE,
                 TINV_HAL_TEMP_B_ADC_SOC_NO,
                 TINV_HAL_TEMP_B_ADC_TRIG_SOURCE,
                 TINV_HAL_TEMP_B_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_HAL_TEMP_C_ADC_BASE,
                 TINV_HAL_TEMP_C_ADC_SOC_NO,
                 TINV_HAL_TEMP_C_ADC_TRIG_SOURCE,
                 TINV_HAL_TEMP_C_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ADC_setupSOC(TINV_HAL_TEMP_AMB_ADC_BASE,
                 TINV_HAL_TEMP_AMB_ADC_SOC_NO,
                 TINV_HAL_TEMP_AMB_ADC_TRIG_SOURCE,
                 TINV_HAL_TEMP_AMB_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);

}

void tida01606_setupGateDrivePwm(uint32_t base,
                                 uint16_t pwm_period_ticks,
                                 uint16_t pwm_dbred_ticks,
                                 uint16_t pwm_dbfed_ticks)
 {
     //
     // Time Base SubModule Registers
     //
     EPWM_setPeriodLoadMode(base, EPWM_PERIOD_SHADOW_LOAD);
     EPWM_setTimeBasePeriod(base, pwm_period_ticks);
     EPWM_setTimeBaseCounter(base, 0);
     EPWM_setPhaseShift(base, 0);
     EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP);
     EPWM_setClockPrescaler(base, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

     //
     // Counter Compare Submodule Registers
     //
     EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_A,
                                 pwm_period_ticks >> 1);
     EPWM_setCounterCompareShadowLoadMode(base, EPWM_COUNTER_COMPARE_A,
                                          EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);

     //
     // Action Qualifier SubModule Registers
     //
     EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH,
                                   EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
     EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW,
                                   EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

     EPWM_setDeadBandControlShadowLoadMode(base, EPWM_DB_LOAD_ON_CNTR_ZERO);

     EPWM_setRisingEdgeDelayCountShadowLoadMode(base,
                                                EPWM_RED_LOAD_ON_CNTR_PERIOD);

     EPWM_setFallingEdgeDelayCountShadowLoadMode(base,
                                                 EPWM_FED_LOAD_ON_CNTR_ZERO);

     //
     // Active high complementary PWMs - Set up the deadband
     //
     EPWM_setDeadBandCounterClock(base, EPWM_DB_COUNTER_CLOCK_FULL_CYCLE);
     EPWM_setRisingEdgeDelayCount(base, pwm_dbred_ticks);
     EPWM_setFallingEdgeDelayCount(base, pwm_dbfed_ticks);
     EPWM_setDeadBandDelayMode(base, EPWM_DB_RED, 1);
     EPWM_setDeadBandDelayMode(base, EPWM_DB_FED, 1);
     EPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
     EPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
     EPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED,
                                   EPWM_DB_POLARITY_ACTIVE_LOW);
     EPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED,
                                   EPWM_DB_POLARITY_ACTIVE_HIGH);
 }

//
void tida01606_setupTINV6EPWM(uint16_t pwm_period_ticks,
                              uint16_t pwm_dbred_ticks,
                              uint16_t pwm_dbfed_ticks)
{
    tida01606_setupPhasePWM(TINV_INV_PWM_Q1A_BASE,
                            TINV_INV_PWM_Q2A_BASE,
                            pwm_period_ticks,
                            pwm_dbred_ticks,
                            pwm_dbfed_ticks);
    tida01606_setupPhasePWM(TINV_INV_PWM_Q1B_BASE,
                            TINV_INV_PWM_Q2B_BASE,
                            pwm_period_ticks,
                            pwm_dbred_ticks,
                            pwm_dbfed_ticks);
    tida01606_setupPhasePWM(TINV_INV_PWM_Q1C_BASE,
                            TINV_INV_PWM_Q2C_BASE,
                            pwm_period_ticks,
                            pwm_dbred_ticks,
                            pwm_dbfed_ticks);
    //
    // configure PWM 1 as master and Phase 2 as slaves and
    // let it pass the sync in pulse from PWM1
    //
    EPWM_disablePhaseShiftLoad(TINV_INV_PWM_Q1A_BASE);
    EPWM_setSyncOutPulseMode(TINV_INV_PWM_Q1A_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);

    //
    // Interrupt where we will change the Compare Values
    // Select INT on Time base counter zero event,
    // Enable INT, generate INT on 1rd event
    //
    EPWM_setInterruptSource(TINV_INV_PWM_Q1A_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(TINV_INV_PWM_Q1A_BASE);
    EPWM_setInterruptEventCount(TINV_INV_PWM_Q1A_BASE, 1U);

    EPWM_enablePhaseShiftLoad(TINV_INV_PWM_Q2A_BASE);
    EPWM_setSyncOutPulseMode(TINV_INV_PWM_Q2A_BASE, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    EPWM_setPhaseShift(TINV_INV_PWM_Q2A_BASE, 2);
    EPWM_setCountModeAfterSync(TINV_INV_PWM_Q2A_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);

    EPWM_enablePhaseShiftLoad(TINV_INV_PWM_Q1B_BASE);
    EPWM_setSyncOutPulseMode(TINV_INV_PWM_Q1B_BASE, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    EPWM_setPhaseShift(TINV_INV_PWM_Q1B_BASE, 2);
    EPWM_setCountModeAfterSync(TINV_INV_PWM_Q1B_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);

    EPWM_enablePhaseShiftLoad(TINV_INV_PWM_Q2B_BASE);
    EPWM_setSyncOutPulseMode(TINV_INV_PWM_Q2B_BASE, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    EPWM_setPhaseShift(TINV_INV_PWM_Q2B_BASE, 2);
    EPWM_setCountModeAfterSync(TINV_INV_PWM_Q2B_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);

    EPWM_enablePhaseShiftLoad(TINV_INV_PWM_Q1C_BASE);
    EPWM_setSyncOutPulseMode(TINV_INV_PWM_Q1C_BASE, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    EPWM_setPhaseShift(TINV_INV_PWM_Q1C_BASE, 2);
    EPWM_setCountModeAfterSync(TINV_INV_PWM_Q1C_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);

    EPWM_enablePhaseShiftLoad(TINV_INV_PWM_Q2C_BASE);
    EPWM_setSyncOutPulseMode(TINV_INV_PWM_Q2C_BASE, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    EPWM_setPhaseShift(TINV_INV_PWM_Q2C_BASE, 2);
    EPWM_setCountModeAfterSync(TINV_INV_PWM_Q2C_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);

}
// ham bo tro cho ham tida01606_setupTINV6PWM
void tida01606_setupPhasePWM(uint32_t base1A,
                             uint32_t base2A,
                             uint16_t pwm_period_ticks,
                             uint16_t pwm_dbred_ticks,
                             uint16_t pwm_dbfed_ticks)
{
    //
    // Time Base SubModule Registers
    //
    EPWM_setPeriodLoadMode(base1A, EPWM_PERIOD_SHADOW_LOAD);
    EPWM_setTimeBasePeriod(base1A, pwm_period_ticks >> 1);
    EPWM_setTimeBaseCounter(base1A, 0);
    EPWM_setPhaseShift(base1A, 0);
    EPWM_setTimeBaseCounterMode(base1A, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setClockPrescaler(base1A, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Counter Compare Submodule Registers
    //
    EPWM_setCounterCompareValue(base1A, EPWM_COUNTER_COMPARE_A, 1000);
    EPWM_setCounterCompareShadowLoadMode(base1A, EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);

    //
    // Action Qualifier SubModule Registers
    //
    EPWM_setActionQualifierAction(base1A, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(base1A, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(base1A, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(base1A, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    //
    // Time Base SubModule Registers
    //
    EPWM_setPeriodLoadMode(base2A, EPWM_PERIOD_SHADOW_LOAD);
    EPWM_setTimeBasePeriod(base2A, pwm_period_ticks >> 1);
    EPWM_setTimeBaseCounter(base2A, 0);
    EPWM_setPhaseShift(base2A, 0);
    EPWM_setTimeBaseCounterMode(base2A, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setClockPrescaler(base2A, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Counter Compare Submodule Registers
    //
    EPWM_setCounterCompareValue(base2A, EPWM_COUNTER_COMPARE_A, 1000);
    EPWM_setCounterCompareShadowLoadMode(base2A, EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);

    //
    // Action Qualifier SubModule Registers
    //
    EPWM_setActionQualifierAction(base2A, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(base2A, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(base2A, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(base2A, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierContSWForceShadowMode(base1A,
                                     EPWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO_PERIOD);
    EPWM_setActionQualifierContSWForceShadowMode(base2A,
                                     EPWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO_PERIOD);

    EPWM_setDeadBandControlShadowLoadMode(base1A, EPWM_DB_LOAD_ON_CNTR_ZERO);
    EPWM_setDeadBandControlShadowLoadMode(base2A, EPWM_DB_LOAD_ON_CNTR_ZERO);

    EPWM_setRisingEdgeDelayCountShadowLoadMode(base1A,
                                               EPWM_RED_LOAD_ON_CNTR_PERIOD);
    EPWM_setRisingEdgeDelayCountShadowLoadMode(base2A,
                                               EPWM_RED_LOAD_ON_CNTR_PERIOD);

    EPWM_setFallingEdgeDelayCountShadowLoadMode(base1A,
                                                EPWM_FED_LOAD_ON_CNTR_ZERO);
    EPWM_setFallingEdgeDelayCountShadowLoadMode(base2A,
                                                EPWM_FED_LOAD_ON_CNTR_ZERO);

    //
    // Active high complementary PWMs - Set up the deadband
    //
    EPWM_setDeadBandCounterClock(base1A, EPWM_DB_COUNTER_CLOCK_FULL_CYCLE);
    EPWM_setRisingEdgeDelayCount(base1A, pwm_dbred_ticks);
    EPWM_setFallingEdgeDelayCount(base1A, pwm_dbfed_ticks);
    EPWM_setDeadBandDelayMode(base1A, EPWM_DB_RED, 1);
    EPWM_setDeadBandDelayMode(base1A, EPWM_DB_FED, 1);
    EPWM_setRisingEdgeDeadBandDelayInput(base1A, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(base1A, EPWM_DB_INPUT_EPWMA);
    EPWM_setDeadBandDelayPolarity(base1A, EPWM_DB_FED,
                                  EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandDelayPolarity(base1A, EPWM_DB_RED,
                                  EPWM_DB_POLARITY_ACTIVE_HIGH);

    EPWM_setDeadBandCounterClock(base2A, EPWM_DB_COUNTER_CLOCK_FULL_CYCLE);
    EPWM_setRisingEdgeDelayCount(base2A, pwm_dbred_ticks);
    EPWM_setFallingEdgeDelayCount(base2A, pwm_dbfed_ticks);
    EPWM_setDeadBandDelayMode(base2A, EPWM_DB_RED, 1);
    EPWM_setDeadBandDelayMode(base2A, EPWM_DB_FED, 1);
    EPWM_setRisingEdgeDeadBandDelayInput(base2A, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(base2A, EPWM_DB_INPUT_EPWMA);
    EPWM_setDeadBandDelayPolarity(base2A, EPWM_DB_FED,
                                  EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandDelayPolarity(base2A, EPWM_DB_RED,
                                  EPWM_DB_POLARITY_ACTIVE_HIGH);

}
