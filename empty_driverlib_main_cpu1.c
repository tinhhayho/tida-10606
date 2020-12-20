//
// Included Files
//
#include "tida01606_define.h"

#define isPWM 1
#define isADC 0
#define isRelay 1
#define isFan 0
#define isEnPWM 1
#define phaseRelay 4
        int relay1, relay2, relay3, relay4;
/*
#define ACTIVE_ADC 1
*/
//
// Main
//
void main(void)
{
    // initialize device clock and peripherals
    Device_init();
    // disable pin lock and enable pull up resistor
    Device_initGPIO();
    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Assign the interrupt service routines to ePWM interrupts
    //
    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 and GPIO6/7 as
    // ePWM1A/1B, ePWM2A/2B, ePWM3A/3B, ePWM4A/4B pins respectively
    //
    tida01606_setupGPIO( isPWM,
                         isADC,
                         isRelay,
                         isFan,
                         isEnPWM);


#ifdef ACTIVE_ADC
    tida01606_setupADC
#endif
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    tida01606_setupGateDrivePwm(TINV_GATE_DRIVE_PWM_BASE,
                                TINV_GATE_DRIVE_PWM_PERIOD,
                                TINV_GATE_DRIVE_DEADBAND_PWM_COUNT,
                                TINV_GATE_DRIVE_DEADBAND_PWM_COUNT);
    tida01606_setupTINV6EPWM(TINV_INV_PWM_PERIOD,
                             TINV_INV_DEADBAND_PWM_COUNT,
                             TINV_INV_DEADBAND_PWM_COUNT);
    // disable peripheral tb clock
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    tida016060_enable_disable_Relay(phaseRelay);
    // enable global interupt(intm) and realtime interrupt
    //EINT;
    ERTM;
    while(1)
    {
        uint32_t i  = 0;
        for(i = 0; i<0x5FFFFFF;i++)
        {
            ;
        }
        GPIO_writePin(TINV_GPIO_RELAY_B,0);
        for(i = 0; i<0x5FFFFFF;i++)
        {
            ;
        }
        GPIO_writePin(TINV_GPIO_RELAY_B,0);

/*
        relay1 = relay2 = relay3 = relay4  = 0;
        if(relay1)
            GPIO_writePin(TINV_GPIO_RELAY_A,1);
        else
            GPIO_writePin(TINV_GPIO_RELAY_A,0);
        if (relay2)
            GPIO_writePin(TINV_GPIO_RELAY_B,1);
        else
            GPIO_writePin(TINV_GPIO_RELAY_B,0);
        if (relay3)
            GPIO_writePin(TINV_GPIO_RELAY_C,1);
        else
            GPIO_writePin(TINV_GPIO_RELAY_C,0);
        if(relay4)
            GPIO_writePin(TINV_GPIO_RELAY_N,1);
        else
            GPIO_writePin(TINV_GP
            */
    }

}






//
// End of File
//
