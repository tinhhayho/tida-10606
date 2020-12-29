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

        //
        // Setup GPIO for SD
        // SD Filter 1 - Data 1
        //
        GPIO_setPadConfig(TINV_GPIO_IGA_SDFM_DATA, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(TINV_GPIO_IGA_SDFM_DATA, GPIO_QUAL_SYNC);
        GPIO_setDirectionMode(TINV_GPIO_IGA_SDFM_DATA, GPIO_DIR_MODE_IN);
        GPIO_setPinConfig(TINV_GPIO_IGA_SDFM_DATA_PIN_CONFIG);

        //
        // SD Filter 1 - Clock 1
        //
        GPIO_setPadConfig(TINV_GPIO_IGA_SDFM_CLOCK, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(TINV_GPIO_IGA_SDFM_CLOCK, GPIO_QUAL_SYNC);
        GPIO_setDirectionMode(TINV_GPIO_IGA_SDFM_CLOCK, GPIO_DIR_MODE_IN);
        GPIO_setPinConfig(TINV_GPIO_IGA_SDFM_CLOCK_PIN_CONFIG);

        //
        // SD Filter 2 - Data 1
        //
        GPIO_setPadConfig(TINV_GPIO_IGB_SDFM_DATA, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(TINV_GPIO_IGB_SDFM_DATA, GPIO_QUAL_SYNC);
        GPIO_setDirectionMode(TINV_GPIO_IGB_SDFM_DATA, GPIO_DIR_MODE_IN);
        GPIO_setPinConfig(TINV_GPIO_IGB_SDFM_DATA_PIN_CONFIG);

        //
        // SD Filter 2 - Clock 1
        //
        GPIO_setPadConfig(TINV_GPIO_IGB_SDFM_CLOCK, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(TINV_GPIO_IGB_SDFM_CLOCK, GPIO_QUAL_SYNC);
        GPIO_setDirectionMode(TINV_GPIO_IGB_SDFM_CLOCK, GPIO_DIR_MODE_IN);
        GPIO_setPinConfig(TINV_GPIO_IGB_SDFM_CLOCK_PIN_CONFIG);

        //
        // SD Filter 3 - Data 1
        //
        GPIO_setPadConfig(TINV_GPIO_IGC_SDFM_DATA, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(TINV_GPIO_IGC_SDFM_DATA, GPIO_QUAL_SYNC);
        GPIO_setDirectionMode(TINV_GPIO_IGC_SDFM_DATA, GPIO_DIR_MODE_IN);
        GPIO_setPinConfig(TINV_GPIO_IGC_SDFM_DATA_PIN_CONFIG);

        //
        // SD Filter 3 - Clock 1
        //
        GPIO_setPadConfig(TINV_GPIO_IGC_SDFM_CLOCK, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(TINV_GPIO_IGC_SDFM_CLOCK, GPIO_QUAL_SYNC);
        GPIO_setDirectionMode(TINV_GPIO_IGC_SDFM_CLOCK, GPIO_DIR_MODE_IN);
        GPIO_setPinConfig(TINV_GPIO_IGC_SDFM_CLOCK_PIN_CONFIG);
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
    // set ADCCLK divider to /4
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
    ///
    ADC_setupSOC(TINV_IL_B_ADC_BASE,
                 TINV_IL_B_ADC_SOC_NO,
                 TINV_IL_B_ADC_TRIG_SOURCE,
                 TINV_IL_B_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///
    ADC_setupSOC(TINV_IL_C_ADC_BASE,
                 TINV_IL_C_ADC_SOC_NO,
                 TINV_IL_C_ADC_TRIG_SOURCE,
                 TINV_IL_C_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///___________________________________________________________________________

    ADC_setupSOC(TINV_VGRID_A_ADC_BASE,
                 TINV_VGRID_A_ADC_SOC_NO,
                 TINV_VGRID_A_ADC_TRIG_SOURCE,
                 TINV_VGRID_A_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///
    ADC_setupSOC(TINV_VGRID_B_ADC_BASE,
                 TINV_VGRID_B_ADC_SOC_NO,
                 TINV_VGRID_B_ADC_TRIG_SOURCE,
                 TINV_VGRID_B_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///
    ADC_setupSOC(TINV_VGRID_C_ADC_BASE,
                 TINV_VGRID_C_ADC_SOC_NO,
                 TINV_VGRID_C_ADC_TRIG_SOURCE,
                 TINV_VGRID_C_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///________________________________________________________________________

    ADC_setupSOC(TINV_VINV_A_ADC_BASE,
                 TINV_VINV_A_ADC_SOC_NO,
                 TINV_VINV_A_ADC_TRIG_SOURCE,
                 TINV_VINV_A_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///
    ADC_setupSOC(TINV_VINV_B_ADC_BASE,
                 TINV_VINV_B_ADC_SOC_NO,
                 TINV_VINV_B_ADC_TRIG_SOURCE,
                 TINV_VINV_B_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///
    ADC_setupSOC(TINV_VINV_C_ADC_BASE,
                 TINV_VINV_C_ADC_SOC_NO,
                 TINV_VINV_C_ADC_TRIG_SOURCE,
                 TINV_VINV_C_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///

    ADC_setupSOC(TINV_VBUS_ADC_BASE,
                 TINV_VBUS_ADC_SOC_NO,
                 TINV_VBUS_ADC_TRIG_SOURCE,
                 TINV_VBUS_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///______________________________________________________________________________________________________________

    ADC_setupSOC(TINV_HAL_TEMP_A_ADC_BASE,
                 TINV_HAL_TEMP_A_ADC_SOC_NO,
                 TINV_HAL_TEMP_A_ADC_TRIG_SOURCE,
                 TINV_HAL_TEMP_A_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///
    ADC_setupSOC(TINV_HAL_TEMP_B_ADC_BASE,
                 TINV_HAL_TEMP_B_ADC_SOC_NO,
                 TINV_HAL_TEMP_B_ADC_TRIG_SOURCE,
                 TINV_HAL_TEMP_B_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///
    ADC_setupSOC(TINV_HAL_TEMP_C_ADC_BASE,
                 TINV_HAL_TEMP_C_ADC_SOC_NO,
                 TINV_HAL_TEMP_C_ADC_TRIG_SOURCE,
                 TINV_HAL_TEMP_C_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///
    ADC_setupSOC(TINV_HAL_TEMP_AMB_ADC_BASE,
                 TINV_HAL_TEMP_AMB_ADC_SOC_NO,
                 TINV_HAL_TEMP_AMB_ADC_TRIG_SOURCE,
                 TINV_HAL_TEMP_AMB_ADC_PIN,
                 TINV_ACQPS_SYS_CLKS);
    ///

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
    EPWM_setCounterCompareValue(base1A, EPWM_COUNTER_COMPARE_A, 200);
    EPWM_setCounterCompareShadowLoadMode(base1A, EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);

    //
    // Action Qualifier SubModule Registers
    //
    EPWM_setActionQualifierAction(base1A, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(base1A, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH,
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
    EPWM_setCounterCompareValue(base2A, EPWM_COUNTER_COMPARE_A, 450);
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
    // set deadband
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
    //
    EPWM_setDeadBandCounterClock(base2A, EPWM_DB_COUNTER_CLOCK_FULL_CYCLE);
    EPWM_setRisingEdgeDelayCount(base2A, pwm_dbred_ticks);
    EPWM_setFallingEdgeDelayCount(base2A, pwm_dbfed_ticks);
    EPWM_setDeadBandDelayMode(base2A, EPWM_DB_RED, 1);
    EPWM_setDeadBandDelayMode(base2A, EPWM_DB_FED, 1);
    EPWM_setDeadBandOutputSwapMode(base2A,EPWM_DB_OUTPUT_A ,1);
    EPWM_setDeadBandOutputSwapMode(base2A,EPWM_DB_OUTPUT_B ,1);
    EPWM_setRisingEdgeDeadBandDelayInput(base2A, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(base2A, EPWM_DB_INPUT_EPWMA);
    EPWM_setDeadBandDelayPolarity(base2A, EPWM_DB_FED,
                                  EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandDelayPolarity(base2A, EPWM_DB_RED,
                                  EPWM_DB_POLARITY_ACTIVE_HIGH);

}



void CLA_confiClaMemory(void) {
    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
    EALLOW;

#ifdef _FLASH
    //
    // Copy over code from FLASH to RAM
    //
    memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
           (uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

    //
    // Initialize and wait for CLA1ToCPUMsgRAM
    //
    MemCfg_initSections(MEMCFG_SECT_MSGCLA1TOCPU);
    while (!MemCfg_getInitStatus(MEMCFG_SECT_MSGCLA1TOCPU)){};

    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfg_initSections(MEMCFG_SECT_MSGCPUTOCLA1);
    while (!MemCfg_getInitStatus(MEMCFG_SECT_MSGCPUTOCLA1)){};

    //
    // Select LS4RAM and LS5RAM to be the programming space for the CLA
    // First configure the CLA to be the master for LS4 and LS5 and then
    // set the space to be a program block
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS4,MEMCFG_CLA_MEM_PROGRAM);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5,MEMCFG_CLA_MEM_PROGRAM);

    //
    // Next configure LS0RAM and LS1RAM as data spaces for the CLA
    // First configure the CLA to be the master for LS0(1) and then
    // set the spaces to be code blocks
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);

    EDIS;
}

void CLA_initCpu1Cla1(void){
    //
     // Compute all CLA task vectors
     // On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
     // opposed to offsets used on older Type-0 CLAs
     //
     EALLOW;
     CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_1,(uint16_t)&Cla1Task1);
     CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_2,(uint16_t)&Cla1Task2);
     CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_3,(uint16_t)&Cla1Task3);
     CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_4,(uint16_t)&Cla1Task4);
     CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_5,(uint16_t)&Cla1Task5);
     CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_6,(uint16_t)&Cla1Task6);
     CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_7,(uint16_t)&Cla1Task7);
     CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_8,(uint16_t)&Cla1Task8);

     //
     // Enable the IACK instruction to start a task on CLA in software
     // for all  8 CLA tasks. Also, globally enable all 8 tasks (or a
     // subset of tasks) by writing to their respective bits in the
     // MIER register
     //
     CLA_enableIACK(CLA1_BASE);
     CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_ALL);

     //
     // Configure the vectors for the end-of-task interrupt for all
     // 8 tasks
     //
     Interrupt_register(INT_CLA1_1, &cla1Isr1);
     Interrupt_register(INT_CLA1_1, &cla1Isr2);
     Interrupt_register(INT_CLA1_1, &cla1Isr3);
     Interrupt_register(INT_CLA1_1, &cla1Isr4);
     Interrupt_register(INT_CLA1_1, &cla1Isr5);
     Interrupt_register(INT_CLA1_1, &cla1Isr6);
     Interrupt_register(INT_CLA1_1, &cla1Isr7);
     Interrupt_register(INT_CLA1_1, &cla1Isr8);

     //
     // Enable CLA interrupts at the group and subgroup levels
     //
     Interrupt_enable(INT_CLA1_1);
     Interrupt_enable(INT_CLA1_2);
     Interrupt_enable(INT_CLA1_3);
     Interrupt_enable(INT_CLA1_4);
     Interrupt_enable(INT_CLA1_5);
     Interrupt_enable(INT_CLA1_6);
     Interrupt_enable(INT_CLA1_7);
     Interrupt_enable(INT_CLA1_8);
}



void tida_01606_setup_SDFM(uint16_t PWM_ticks,
                           uint16_t PWM_ticks_in_sdfm_osr,
                           uint16_t SD_clk_ecap_sys_ticks,
                           uint16_t sdfmosr){
    //
    // setup CAP to generate CLK for SDFM
    //
    tida_01606_configuECapforSDFMclk(SD_clk_ecap_sys_ticks);

    //
    // setup PWM11 for syncing the SD filter windows with motor control PWMs
    //
    tida_01606_configurePWMsyncSDFM(PWM_ticks, PWM_ticks_in_sdfm_osr);
    //
    // Input Control Module
    //
    // Configure Input Control Mode
    //
    SDFM_setupModulatorClock(TINV_IGA_SDFM_BASE, TINV_IGA_SDFM_FILTER,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);
    SDFM_setupModulatorClock(TINV_IGB_SDFM_BASE, TINV_IGB_SDFM_FILTER,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);
    SDFM_setupModulatorClock(TINV_IGC_SDFM_BASE, TINV_IGC_SDFM_FILTER,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_enableFilter(TINV_IGA_SDFM_BASE, TINV_IGA_SDFM_FILTER);
    SDFM_enableFilter(TINV_IGB_SDFM_BASE, TINV_IGB_SDFM_FILTER);
    SDFM_enableFilter(TINV_IGC_SDFM_BASE, TINV_IGC_SDFM_FILTER);

    //
    // Sinc filter Module
    //
    // Configure Data filter modules filter type, OSR value and enable /
    // disable data filter 16 bit data representation is chosen for OSR 128
    // using Sinc3, from the table in the TRMthe max value represented for
    // OSR 128 using sinc 3 is +/-2097152 2^21 the max value represented
    // for OSR 64 using sinc 3 is +/-262144 2^18 to represent this in
    // 16 bit format where the first bit is sign shift by 6 bits
    //
    SDFM_setFilterType(TINV_IGA_SDFM_BASE,
                       TINV_IGA_SDFM_FILTER,
                       SDFM_FILTER_SINC_3);
    SDFM_setFilterType(TINV_IGB_SDFM_BASE,
                       TINV_IGB_SDFM_FILTER,
                       SDFM_FILTER_SINC_3);
    SDFM_setFilterType(TINV_IGC_SDFM_BASE,
                       TINV_IGC_SDFM_FILTER,
                       SDFM_FILTER_SINC_3);

    SDFM_setOutputDataFormat(TINV_IGA_SDFM_BASE, TINV_IGA_SDFM_FILTER,
                             SDFM_DATA_FORMAT_32_BIT);
    SDFM_setOutputDataFormat(TINV_IGB_SDFM_BASE, TINV_IGB_SDFM_FILTER,
                             SDFM_DATA_FORMAT_32_BIT);
    SDFM_setOutputDataFormat(TINV_IGC_SDFM_BASE, TINV_IGC_SDFM_FILTER,
                             SDFM_DATA_FORMAT_32_BIT);

    SDFM_setFilterOverSamplingRatio(TINV_IGA_SDFM_BASE,
                                    TINV_IGA_SDFM_FILTER, sdfmosr - 1);
    SDFM_setFilterOverSamplingRatio(TINV_IGB_SDFM_BASE,
                                    TINV_IGB_SDFM_FILTER, sdfmosr - 1);
    SDFM_setFilterOverSamplingRatio(TINV_IGC_SDFM_BASE,
                                    TINV_IGC_SDFM_FILTER, sdfmosr - 1);

    //
    // Comparator Module
    //
    // Comparator HLT and LLT
    // Configure Comparator module's comparator filter type and comparator's
    // OSR value, higher threshold, lower threshold
    //
    SDFM_setComparatorFilterType(TINV_IGA_SDFM_BASE, TINV_IGA_SDFM_FILTER,
                                 SDFM_FILTER_SINC_3);
    SDFM_setCompFilterOverSamplingRatio(TINV_IGA_SDFM_BASE,
                                        TINV_IGA_SDFM_FILTER,
                                        TINV_SDFM_CMPSS_OSR - 1);

    SDFM_setComparatorFilterType(TINV_IGB_SDFM_BASE,
                                 TINV_IGB_SDFM_FILTER,
                                 SDFM_FILTER_SINC_3);
    SDFM_setCompFilterOverSamplingRatio(TINV_IGB_SDFM_BASE,
                                        TINV_IGB_SDFM_FILTER,
                                        TINV_SDFM_CMPSS_OSR - 1);

    SDFM_setComparatorFilterType(TINV_IGC_SDFM_BASE,
                                 TINV_IGC_SDFM_FILTER,
                                 SDFM_FILTER_SINC_3);
    SDFM_setCompFilterOverSamplingRatio(TINV_IGC_SDFM_BASE,
                                        TINV_IGC_SDFM_FILTER,
                                        TINV_SDFM_CMPSS_OSR - 1);

    //
    // EXTERNAL RESET
    //
    // PWM11.CMPC, PWM11.CMPD, PWM12.CMPC and PWM12.CMPD signals cannot
    // synchronize the filters. This option is not being used in this example
    //     SDFM_enableExternalReset(TINV_IGA_SDFM_BASE,TINV_IGA_SDFM_FILTER);
    //     SDFM_enableExternalReset(TINV_IGB_SDFM_BASE,TINV_IGB_SDFM_FILTER);
    //     SDFM_enableExternalReset(TINV_IGC_SDFM_BASE,TINV_IGC_SDFM_BASE);
    //

    //
    // Enable master filter bit of the SDFM module 1
    //
    SDFM_enableMasterFilter(TINV_IGA_SDFM_BASE);
    SDFM_enableMasterInterrupt(TINV_IGA_SDFM_BASE);
    SDFM_enableMasterFilter(TINV_IGB_SDFM_BASE);
    SDFM_enableMasterInterrupt(TINV_IGB_SDFM_BASE);
    SDFM_enableMasterFilter(TINV_IGC_SDFM_BASE);
    SDFM_enableMasterInterrupt(TINV_IGC_SDFM_BASE);

}


void tida_01606_setupTrigger(uint32_t base){
    //
    // Select SOC from counter at ctr =CMPBD
    //
    EPWM_setADCTriggerSource(base, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPB );

    //
    // write value to CMPB
    //
    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_B,
                                ((int16_t)((float32_t)TINV_INV_PWM_PERIOD *
                                 (float32_t)0.5) -
                                 (int16_t)TINV_ACQPS_SYS_CLKS * 2));

    //
    // Generate pulse on 1st even
    //
    EPWM_setADCTriggerEventPrescale(base, EPWM_SOC_A, 1);

    //
    // Enable SOC on A group
    //
    EPWM_enableADCTrigger(base, EPWM_SOC_A);
}

void tida_01606_configurePWMsyncSDFM(uint16_t PWM_ticks,
                                     uint16_t PWM_ticks_in_sdfm_osr){
    tida_01606_configurePWM1chUpCnt(EPWM11_BASE, PWM_ticks);

    //
    // EPWM1 SYNCOUT on ZRO is passed through EPWM5
    //
    EPWM_setSyncOutPulseMode(EPWM5_BASE, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    EPWM_setSyncOutPulseMode(EPWM7_BASE, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);

    EPWM_setSyncOutPulseMode(EPWM10_BASE, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);

    EPWM_setPhaseShift(EPWM11_BASE, 2);
    EPWM_enablePhaseShiftLoad(EPWM11_BASE);
    EPWM_setCountModeAfterSync(EPWM11_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);

    //
    // CMPC and CMPD are used to send the SDFM Sync pulse to the filters
    //
    EPWM_setCounterCompareValue(EPWM11_BASE, EPWM_COUNTER_COMPARE_C,
                                ((EPWM_getTimeBasePeriod(EPWM11_BASE))) -
                                (PWM_ticks_in_sdfm_osr * 1.5));

    EPWM_setCounterCompareValue(EPWM11_BASE, EPWM_COUNTER_COMPARE_D,
                                ((EPWM_getTimeBasePeriod(EPWM11_BASE))) -
                                (PWM_ticks_in_sdfm_osr * 1.5));

    //
    // CMPA is used to read the SDFM registers
    //
    EPWM_setCounterCompareValue(EPWM11_BASE, EPWM_COUNTER_COMPARE_A,
                                ((EPWM_getTimeBasePeriod(EPWM11_BASE))) +
                                (PWM_ticks_in_sdfm_osr * 1.5 + 10));
}


void tida_01606_configurePWM1chUpCnt(uint32_t base1,
                                     uint16_t period)
{
    //
    // Time Base SubModule Registers
    //
    EPWM_setPeriodLoadMode(base1, EPWM_PERIOD_DIRECT_LOAD);
    EPWM_setTimeBasePeriod(base1, period - 1);
    EPWM_setTimeBaseCounter(base1, 0);
    EPWM_setPhaseShift(base1, 0);
    EPWM_setTimeBaseCounterMode(base1, EPWM_COUNTER_MODE_UP);
    EPWM_setClockPrescaler(base1, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
}

void tida_01606_configuECapforSDFMclk(uint16_t SD_clk_ecap_sys_ticks){
    //
    // Use CAP as source for the SD Clock
    // OUTPUTXBAR1 -> GPIO24
    //

    //
    // Select ECAP O on Mux0
    //
    XBAR_setOutputMuxConfig(TINV_SDFM_CLK_OUTPUTXBAR,
                            TINV_SDFM_CLK_OUTPUTXBAR_MUX_CONFIG);

    //
    // Enable MUX0 for ECAP1.OUT
    //
    XBAR_enableOutputMux(TINV_SDFM_CLK_OUTPUTXBAR,
                         TINV_SDFM_CLK_OUTPUTXBAR_MUX);

    GPIO_setDirectionMode(TINV_SDFM_CLK_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(TINV_SDFM_CLK_GPIO, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(TINV_SDFM_CLK_PIN_CONFIG);

    //
    // Setup APWM mode on CAP peripheral, set period and compare registers
    //
    ECAP_enableAPWMMode(TINV_SDFM_CLK_SOURCE_BASE);

    //
    // Enable APWM mode
    //
    ECAP_setAPWMPeriod(TINV_SDFM_CLK_SOURCE_BASE, SD_clk_ecap_sys_ticks - 1);
    ECAP_setAPWMCompare(TINV_SDFM_CLK_SOURCE_BASE, SD_clk_ecap_sys_ticks >> 1);

    //
    // set next duty cycle to 50%
    //
    ECAP_setAPWMShadowPeriod(TINV_SDFM_CLK_SOURCE_BASE,
                             SD_clk_ecap_sys_ticks - 1);
    ECAP_setAPWMShadowCompare(TINV_SDFM_CLK_SOURCE_BASE,
                              SD_clk_ecap_sys_ticks >> 1);

    ECAP_clearInterrupt(TINV_SDFM_CLK_SOURCE_BASE, 0xFF);
    ECAP_clearGlobalInterrupt(TINV_SDFM_CLK_SOURCE_BASE);

    //
    // Start counters
    //
    ECAP_startCounter(TINV_SDFM_CLK_SOURCE_BASE);
}


















// end of file
