#ifndef TINV_SETTINGS_H
#define TINV_SETTINGS_H

#ifdef __cplusplus

extern "C" {
#endif

//
// Includes
//
#include "driverlib.h"
#include "device.h"
#include <stdint.h>

//
// Macro Definitions
//

//
// defines
//

//
// Device Related Defines
//
#define TINV_CPU_SYS_CLOCK       (200 * 1000000)
#define TINV_PWMSYSCLOCK_FREQ    (100 * 1000000)
#define TINV_ECAPSYSCLOCK_FREQ   (200 * 1000000)

#define TINV_ACQPS_SYS_CLKS     ((float32_t)100.0 * (float32_t)0.000000001 *   \
                                 (float32_t)TINV_CPU_SYS_CLOCK)

//
// Project Options
//

//
// Incremental Build options for System check-out
//
// BUILD 1   Open Loop Check the Inverter
// BUILD 2   Closed Current Loop Inverter forced sine angle
// BUILD 3   Closed Current loop with grid connected PLL
//
#define TINV_INCR_BUILD 1

//
// TINV_RECTIFIER_MODE setting
//
// 0 = Inverter
// 1 = TINV_RECTIFIER_MODE
//
#define TINV_RECTIFIER_MODE 0

//
// Check system under DC condition 0 is FALSE, 1 is TRUE
//
#define TINV_DC_CHECK 0

#define TINV_AC_FREQ             60
#define TINV_VDC_NOMINAL         800

//
// 1 for SDFM sensing
// 0 otherwise
//
#define TINV_SDFM_SENSING        1

//
// Default Ref Values
//
#define TINV_VREF_DEFAULT    ((float32_t)0.835)
#define TINV_IREF_DEFAULT    ((float32_t)0.2)

#define TINV_DLOG_SIZE      100
#define TINV_DLOG_TRIGGER   0.01
#define TINV_DLOG_SCALE     20

#define TINV_ADC_PU_SCALE_FACTOR       ((float32_t)(3.3 / (2^12)))
#define TINV_HI_RES_SHIFT              ((float32_t)(2^16))
#define TINV_ADC_PU_PPB_SCALE_FACTOR   ((float32_t)(1 / (2^11)))
#define TINV_SD_PU_SCALE_FACTOR        ((float32_t)(1 / (2^15)))
#define TINV_SD32_PU_SCALE_FACTOR      ((float32_t)(1.0 /                      \
                                       ((float32_t)TINV_SDFM_OSR *             \
                                       TINV_SDFM_OSR * TINV_SDFM_OSR)))

//
// Power Stage Related Values determined by physcial design*/
//
#define TINV_INV_PWM_SWITCHING_FREQUENCY  ((float32_t)20 * 1000)
#define TINV_LCL_RESONANCE_FREQ           ((float32_t)5.952013574504279)
#define TINV_INV_DEADBAND_US              ((float32_t)1)
#define TINV_INV_PWM_PERIOD               (TINV_PWMSYSCLOCK_FREQ) /            \
                                          (TINV_INV_PWM_SWITCHING_FREQUENCY)
#define TINV_INV_DEADBAND_PWM_COUNT       (int16_t)((float32_t)                \
                                          TINV_INV_DEADBAND_US *               \
                                          (float32_t)TINV_PWMSYSCLOCK_FREQ *   \
                                          (float32_t)0.000001)

//
// Set PWM deadband in usec
//
#define TINV_GATE_DRIVE_PWM_SWITCHING_FREQUENCY ((float32_t)500 * 1000)
#define TINV_GATE_DRIVE_PWM_DEADBAND_US         ((float32_t)0.5)
#define TINV_GATE_DRIVE_PWM_PERIOD     (TINV_PWMSYSCLOCK_FREQ) /               \
                                       (TINV_GATE_DRIVE_PWM_SWITCHING_FREQUENCY)
#define TINV_GATE_DRIVE_DEADBAND_PWM_COUNT   (int16_t)((float32_t)             \
                                             TINV_GATE_DRIVE_PWM_DEADBAND_US * \
                                             (float32_t)TINV_PWMSYSCLOCK_FREQ *\
                                             (float)0.000001)

//
// Hardware Settings
//
#define TINV_LI_INDUCTOR_VALUE  ((float32_t)0.000342)
#define TINV_VAC_MAX_SENSE      ((float32_t)650.0)
#define TINV_VDCBUS_MAX_SENSE   ((float32_t)1000.0)
#define TINV_IL_MAX_SENSE       ((float32_t)25.0)
#define TINV_IL_TRIP_LIMIT      ((float32_t)16.0)
#define TINV_IG_MAX_SENSE       ((float32_t)25.0)
#define TINV_IG_TRIP_LIMIT      ((float32_t)16.0)

//
// Control Loop Design
//

#define TINV_CONTROL_RUNNING_ON C28x_CORE
#define TINV_ISR1_RUNNING_ON TINV_CONTROL_RUNNING_ON
#define TINV_ISR2_RUNNING_ON TINV_CONTROL_RUNNING_ON

#define TINV_ISR_CONTROL_FREQUENCY   ((float32_t)                              \
                                      (TINV_INV_PWM_SWITCHING_FREQUENCY) /     \
                                      (TINV_CNTRL_ISR_FREQ_RATIO))
#define TINV_CNTRL_ISR_FREQ_RATIO    1
#define TINV_VOLTAGE_LOOP_RUN_RATIO  1

//
// SFRA Options
// 1 FRA for the Voltage Loop
// 2 FRA for the Current Loop
//
#define TINV_SFRA_DISABLE 0
#define TINV_SFRA_VOLTAGE 1
#define TINV_SFRA_CURRENT 2

#if TINV_INCR_BUILD == 1
#define TINV_SFRA_TYPE         TINV_SFRA_DISABLE
#elif TINV_INCR_BUILD == 2 || TINV_INCR_BUILD == 3
#define TINV_SFRA_TYPE         TINV_SFRA_CURRENT
#endif
#define TINV_SFRA_ISR_FREQ       TINV_ISR_CONTROL_FREQUENCY

#define TINV_PI ((float32_t)3.141592653589)

//
// PI Controller Settings from SFRA tool chain*/
//
#define TINV_PI_KP ((float32_t)0.1401211)
#define TINV_PI_KI ((float32_t)0.0784877)
//#define TINV_PI_KP ((float32_t)0.0019246)
//#define TINV_PI_KI ((float32_t)0.0783520)

//
// ADC Reading Default Calibrations
//
#define TINV_CURRENT_OFFSET          ((float32_t)1.7)
#define TINV_CURRENT_SCALE           ((float32_t)1.5)
#define TINV_VOLTAGE_OFFSET          ((float32_t)1.65)
#define TINV_VOLTAGE_SCALE           ((float32_t)(-0.6))
#define TINV_VBUS_SCALE              ((float32_t)0.706)

//
// SDFM Sensing Parameters*/
//
#define TINV_SDCLK_FREQ            (float32_t)(20 * 1000000)
#define TINV_SD_CLK_COUNT          TINV_ECAPSYSCLOCK_FREQ / TINV_SDCLK_FREQ
#define TINV_PWM_CLK_IN_SDFM_CLK   (int16_t)((float32_t)TINV_PWMSYSCLOCK_FREQ /\
                                   (float32_t)TINV_SDCLK_FREQ)
#define TINV_PWM_CLK_IN_SDFM_OSR   (int16_t)((float32_t)                       \
                                             TINV_PWM_CLK_IN_SDFM_CLK *        \
                                             (float32_t)TINV_SDFM_OSR)
#define TINV_SDFM_FILTER_TYPE      3
#define TINV_SDFM_OSR              100
#define TINV_SDFM_CMPSS_OSR        32
#define TINV_SDFM_CMPSS_MAX_VAL    TINV_SDFM_CMPSS_OSR * TINV_SDFM_CMPSS_OSR * \
                                   TINV_SDFM_CMPSS_OSR
#define TINV_SDFM_CMPSS_MAX_VAL_DIV_2   ((uint16_t)TINV_SDFM_CMPSS_MAX_VAL / 2)

//
// SDFM Clock Generation
// ECAP1 is used to come out at OUTPUTXBAR1, on pin 24
//
#define TINV_SDFM_CLK_SOURCE_BASE                ECAP1_BASE
#define TINV_SDFM_CLK_GPIO                       24
#define TINV_SDFM_CLK_PIN_CONFIG                 GPIO_24_OUTPUTXBAR1
#define TINV_SDFM_CLK_OUTPUTXBAR                 XBAR_OUTPUT1
#define TINV_SDFM_CLK_OUTPUTXBAR_MUX             XBAR_MUX00
#define TINV_SDFM_CLK_OUTPUTXBAR_MUX_CONFIG      XBAR_OUT_MUX00_ECAP1_OUT

//
// USER CODE START (section: User_Section)
// User defined includes, defines, global variables and functions
// PWM pin, ADC, SDFM, Relay Selection related variables
//
#define TINV_C28X_ISR1_PIE_GROUP_NO INTERRUPT_ACK_GROUP3

#define TINV_C28X_ISR1_TRIG_BASE EPWM1_BASE
#define TINV_C28X_ISR1_TRIG      INT_EPWM1

#define TINV_C28X_ISR2_FREQUENCY 1000
#define TINV_C28X_ISR2_TRIG_BASE CPUTIMER2_BASE
#define TINV_C28X_ISR2_TRIG      INT_TIMER2

//
// Protection Settings
// set 1 to enable the appropriate protection scheme
//
#define TINV_BOARD_PROTECTION_LA_SENSE 0
#define TINV_BOARD_PROTECTION_LB_SENSE 0
#define TINV_BOARD_PROTECTION_LC_SENSE 0
#define TINV_BOARD_PROTECTION_SIC_A    0
#define TINV_BOARD_PROTECTION_SIC_B    0
#define TINV_BOARD_PROTECTION_SIC_C    0

#define TINV_SPLL_SRF 1
#define TINV_SPLL_DDSRF 2
#define TINV_SPLL_TYPE TINV_SPLL_DDSRF

//
// Pin Settings
//

//
// Phase A PWM
//
#define TINV_INV_PWM_Q1A_BASE             EPWM1_BASE
#define TINV_INV_PWM_Q1A_GPIO             0
#define TINV_INV_PWM_Q1A_GPIO_PIN_CONFIG  GPIO_0_EPWM1A

#define TINV_INV_PWM_Q3A_BASE             EPWM1_BASE
#define TINV_INV_PWM_Q3A_GPIO             1
#define TINV_INV_PWM_Q3A_GPIO_PIN_CONFIG  GPIO_1_EPWM1B

#define TINV_INV_PWM_Q2A_BASE             EPWM2_BASE
#define TINV_INV_PWM_Q2A_GPIO             2
#define TINV_INV_PWM_Q2A_GPIO_PIN_CONFIG  GPIO_2_EPWM2A

#define TINV_INV_PWM_Q4A_BASE             EPWM2_BASE
#define TINV_INV_PWM_Q4A_GPIO             3
#define TINV_INV_PWM_Q4A_GPIO_PIN_CONFIG  GPIO_3_EPWM2B

//
// Phase B PWM
//
#define TINV_INV_PWM_Q1B_BASE             EPWM3_BASE
#define TINV_INV_PWM_Q1B_GPIO             4
#define TINV_INV_PWM_Q1B_GPIO_PIN_CONFIG  GPIO_4_EPWM3A

#define TINV_INV_PWM_Q3B_BASE             EPWM3_BASE
#define TINV_INV_PWM_Q3B_GPIO             5
#define TINV_INV_PWM_Q3B_GPIO_PIN_CONFIG  GPIO_5_EPWM3B

#define TINV_INV_PWM_Q2B_BASE             EPWM4_BASE
#define TINV_INV_PWM_Q2B_GPIO             6
#define TINV_INV_PWM_Q2B_GPIO_PIN_CONFIG  GPIO_6_EPWM4A

#define TINV_INV_PWM_Q4B_BASE             EPWM4_BASE
#define TINV_INV_PWM_Q4B_GPIO             7
#define TINV_INV_PWM_Q4B_GPIO_PIN_CONFIG  GPIO_7_EPWM4B

//
// Phase C PWM
//
#define TINV_INV_PWM_Q1C_BASE             EPWM7_BASE
#define TINV_INV_PWM_Q1C_GPIO             12
#define TINV_INV_PWM_Q1C_GPIO_PIN_CONFIG  GPIO_12_EPWM7A

#define TINV_INV_PWM_Q3C_BASE             EPWM7_BASE
#define TINV_INV_PWM_Q3C_GPIO             13
#define TINV_INV_PWM_Q3C_GPIO_PIN_CONFIG  GPIO_13_EPWM7B

#define TINV_INV_PWM_Q2C_BASE             EPWM8_BASE
#define TINV_INV_PWM_Q2C_GPIO             14
#define TINV_INV_PWM_Q2C_GPIO_PIN_CONFIG  GPIO_14_EPWM8A

#define TINV_INV_PWM_Q4C_BASE             EPWM8_BASE
#define TINV_INV_PWM_Q4C_GPIO             15
#define TINV_INV_PWM_Q4C_GPIO_PIN_CONFIG  GPIO_15_EPWM8B

#define TINV_GATE_DRIVE_PWM_BASE          EPWM6_BASE

#define TINV_GATE_DRIVE_PWMXA_GPIO              10
#define TINV_GATE_DRIVE_PWMXA_GPIO_PIN_CONFIG   GPIO_10_EPWM6A

#define TINV_GATE_DRIVE_PWMXB_GPIO              11
#define TINV_GATE_DRIVE_PWMXB_GPIO_PIN_CONFIG   GPIO_11_EPWM6B

#define TINV_ADC_SOC_TRIG             ADC_TRIGGER_EPWM1_SOCA

#define TINV_IL_A_ADC_BASE            ADCA_BASE
#define TINV_IL_A_ADCRESULT_BASE      ADCARESULT_BASE
#define TINV_IL_A_ADC_PIN             ADC_CH_ADCIN14
#define TINV_IL_A_ADC_TRIG_SOURCE     TINV_ADC_SOC_TRIG
#define TINV_IL_A_ADC_SOC_NO          ADC_SOC_NUMBER0

#define TINV_VGRID_A_ADC_BASE         ADCA_BASE
#define TINV_VGRID_A_ADCRESULT_BASE   ADCARESULT_BASE
#define TINV_VGRID_A_ADC_PIN          ADC_CH_ADCIN2
#define TINV_VGRID_A_ADC_TRIG_SOURCE  TINV_ADC_SOC_TRIG
#define TINV_VGRID_A_ADC_SOC_NO       ADC_SOC_NUMBER3

#define TINV_VINV_A_ADC_BASE          ADCA_BASE
#define TINV_VINV_A_ADCRESULT_BASE    ADCARESULT_BASE
#define TINV_VINV_A_ADC_PIN           ADC_CH_ADCIN4
#define TINV_VINV_A_ADC_TRIG_SOURCE   TINV_ADC_SOC_TRIG
#define TINV_VINV_A_ADC_SOC_NO        ADC_SOC_NUMBER6

#define TINV_IL_B_ADC_BASE            ADCC_BASE
#define TINV_IL_B_ADCRESULT_BASE      ADCCRESULT_BASE
#define TINV_IL_B_ADC_PIN             ADC_CH_ADCIN4
#define TINV_IL_B_ADC_TRIG_SOURCE     TINV_ADC_SOC_TRIG
#define TINV_IL_B_ADC_SOC_NO          ADC_SOC_NUMBER1

#define TINV_VGRID_B_ADC_BASE         ADCC_BASE
#define TINV_VGRID_B_ADCRESULT_BASE   ADCCRESULT_BASE
#define TINV_VGRID_B_ADC_PIN          ADC_CH_ADCIN2
#define TINV_VGRID_B_ADC_TRIG_SOURCE  TINV_ADC_SOC_TRIG
#define TINV_VGRID_B_ADC_SOC_NO       ADC_SOC_NUMBER4

#define TINV_VINV_B_ADC_BASE          ADCC_BASE
#define TINV_VINV_B_ADCRESULT_BASE    ADCCRESULT_BASE
#define TINV_VINV_B_ADC_PIN           ADC_CH_ADCIN3
#define TINV_VINV_B_ADC_TRIG_SOURCE   TINV_ADC_SOC_TRIG
#define TINV_VINV_B_ADC_SOC_NO        ADC_SOC_NUMBER7

#define TINV_IL_C_ADC_BASE            ADCD_BASE
#define TINV_IL_C_ADCRESULT_BASE      ADCDRESULT_BASE
#define TINV_IL_C_ADC_PIN             ADC_CH_ADCIN2
#define TINV_IL_C_ADC_TRIG_SOURCE     TINV_ADC_SOC_TRIG
#define TINV_IL_C_ADC_SOC_NO          ADC_SOC_NUMBER2

#define TINV_VGRID_C_ADC_BASE         ADCD_BASE
#define TINV_VGRID_C_ADCRESULT_BASE   ADCDRESULT_BASE
#define TINV_VGRID_C_ADC_PIN          ADC_CH_ADCIN0
#define TINV_VGRID_C_ADC_TRIG_SOURCE  TINV_ADC_SOC_TRIG
#define TINV_VGRID_C_ADC_SOC_NO       ADC_SOC_NUMBER5

#define TINV_VINV_C_ADC_BASE          ADCD_BASE
#define TINV_VINV_C_ADCRESULT_BASE    ADCDRESULT_BASE
#define TINV_VINV_C_ADC_PIN           ADC_CH_ADCIN1
#define TINV_VINV_C_ADC_TRIG_SOURCE   TINV_ADC_SOC_TRIG
#define TINV_VINV_C_ADC_SOC_NO        ADC_SOC_NUMBER8

#define TINV_VBUS_ADC_BASE            ADCD_BASE
#define TINV_VBUS_ADCRESULT_BASE      ADCDRESULT_BASE
#define TINV_VBUS_ADC_PIN             ADC_CH_ADCIN5
#define TINV_VBUS_ADC_TRIG_SOURCE     TINV_ADC_SOC_TRIG
#define TINV_VBUS_ADC_SOC_NO          ADC_SOC_NUMBER9

#define TINV_HAL_TEMP_A_ADC_BASE          ADCB_BASE
#define TINV_HAL_TEMP_A_ADCRESULT_BASE    ADCBRESULT_BASE
#define TINV_HAL_TEMP_A_ADC_PIN           ADC_CH_ADCIN0
#define TINV_HAL_TEMP_A_ADC_TRIG_SOURCE   TINV_ADC_SOC_TRIG
#define TINV_HAL_TEMP_A_ADC_SOC_NO        ADC_SOC_NUMBER10

#define TINV_HAL_TEMP_B_ADC_BASE          ADCB_BASE
#define TINV_HAL_TEMP_B_ADCRESULT_BASE    ADCBRESULT_BASE
#define TINV_HAL_TEMP_B_ADC_PIN           ADC_CH_ADCIN1
#define TINV_HAL_TEMP_B_ADC_TRIG_SOURCE   TINV_ADC_SOC_TRIG
#define TINV_HAL_TEMP_B_ADC_SOC_NO        ADC_SOC_NUMBER11

#define TINV_HAL_TEMP_C_ADC_BASE          ADCB_BASE
#define TINV_HAL_TEMP_C_ADCRESULT_BASE    ADCBRESULT_BASE
#define TINV_HAL_TEMP_C_ADC_PIN           ADC_CH_ADCIN2
#define TINV_HAL_TEMP_C_ADC_TRIG_SOURCE   TINV_ADC_SOC_TRIG
#define TINV_HAL_TEMP_C_ADC_SOC_NO        ADC_SOC_NUMBER12

#define TINV_HAL_TEMP_AMB_ADC_BASE         ADCB_BASE
#define TINV_HAL_TEMP_AMB_ADCRESULT_BASE   ADCBRESULT_BASE
#define TINV_HAL_TEMP_AMB_ADC_PIN          ADC_CH_ADCIN3
#define TINV_HAL_TEMP_AMB_ADC_TRIG_SOURCE  TINV_ADC_SOC_TRIG
#define TINV_HAL_TEMP_AMB_ADC_SOC_NO       ADC_SOC_NUMBER13

#define TINV_IREF_ADC_BASE            ADCA_BASE
#define TINV_IREF_ADCRESULT_BASE      ADCARESULT_BASE
#define TINV_IREF_ADC_SOC_NO          ADC_SOC_NUMBER14
#define TINV_IREF_ADC_PIN             ADC_CH_ADCIN3
#define TINV_IREF_ADC_TRIG_SOURCE     TINV_ADC_SOC_TRIG

#define TINV_II_SENSE_CMPSS_BASE                 CMPSS1_BASE
#define TINV_II_SENSE_CMPSS_ASYSCTRL_CMPHPMUX    ASYSCTL_CMPHPMUX_SELECT_1
#define TINV_II_SENSE_CMPSS_ASYSCTRL_CMPLPMUX    ASYSCTL_CMPLPMUX_SELECT_1
#define TINV_II_SENSE_CMPSS_ASYSCTRL_MUX_VALUE   0

#define TINV_II_SENSE_XBAR_MUX            XBAR_MUX00
#define TINV_II_SENSE_XBAR_MUX_VAL        XBAR_EPWM_MUX00_CMPSS1_CTRIPH_OR_L

#define TINV_IO_SDFM_SENSE_XBAR_MUX_VAL   XBAR_EPWM_MUX20_SD1FLT3_COMPH_OR_COMPL
#define TINV_IO_SDFM_SENSE_XBAR_MUX       XBAR_MUX20

#define TINV_IGA_SDFM_BASE                    SDFM1_BASE
#define TINV_IGA_SDFM_FILTER                  SDFM_FILTER_1
#define TINV_GPIO_IGA_SDFM_DATA               48
#define TINV_GPIO_IGA_SDFM_DATA_PIN_CONFIG    GPIO_48_SD1_D1
#define TINV_GPIO_IGA_SDFM_CLOCK              49
#define TINV_GPIO_IGA_SDFM_CLOCK_PIN_CONFIG   GPIO_49_SD1_C1

#define TINV_IGB_SDFM_BASE                    SDFM1_BASE
#define TINV_IGB_SDFM_FILTER                  SDFM_FILTER_2
#define TINV_GPIO_IGB_SDFM_DATA               50
#define TINV_GPIO_IGB_SDFM_DATA_PIN_CONFIG    GPIO_50_SD1_D2
#define TINV_GPIO_IGB_SDFM_CLOCK              51
#define TINV_GPIO_IGB_SDFM_CLOCK_PIN_CONFIG   GPIO_51_SD1_C2

#define TINV_IGC_SDFM_BASE                    SDFM1_BASE
#define TINV_IGC_SDFM_FILTER                  SDFM_FILTER_3
#define TINV_GPIO_IGC_SDFM_DATA               52
#define TINV_GPIO_IGC_SDFM_DATA_PIN_CONFIG    GPIO_52_SD1_D3
#define TINV_GPIO_IGC_SDFM_CLOCK              53
#define TINV_GPIO_IGC_SDFM_CLOCK_PIN_CONFIG   GPIO_53_SD1_C3

#define TINV_GPIO_RDY                      26
#define TINV_GPIO_RDY_PIN_CONFIG           GPIO_27_GPIO27

#define TINV_GPIO_GATE_RST                 27
#define TINV_GPIO_GATE_RST_PIN_CONFIG      GPIO_27_GPIO27

#define TINV_GPIO_PWM_EN                   43
#define TINV_GPIO_PWM_EN_CONFIG            GPIO_43_GPIO43

#define TINV_GPIO_RELAY_A                  34
#define TINV_GPIO_RELAY_A_PIN_CONFIG       GPIO_34_GPIO34

#define TINV_GPIO_RELAY_B                  39
#define TINV_GPIO_RELAY_B_PIN_CONFIG       GPIO_39_GPIO39

#define TINV_GPIO_RELAY_C                  44
#define TINV_GPIO_RELAY_C_PIN_CONFIG       GPIO_44_GPIO44

#define TINV_GPIO_RELAY_N                  45
#define TINV_GPIO_RELAY_N_PIN_CONFIG       GPIO_45_GPIO45

#define TINV_GPIO_FLT_A                    40
#define TINV_GPIO_FLT_A_PIN_CONFIG         GPIO_40_GPIO40

#define TINV_GPIO_FLT_B                    33
#define TINV_GPIO_FLT_B_PIN_CONFIG         GPIO_33_GPIO33

#define TINV_GPIO_FLT_C                    32
#define TINV_GPIO_FLT_C_PIN_CONFIG         GPIO_32_GPIO32

#define TINV_GPIO_FAN                      9
#define TINV_GPIO_FAN_PIN_CONFIG           GPIO_9_GPIO9

#define TINV_GPIO_PROFILING1               58
#define TINV_GPIO_PROFILING1_SET           GPIO_GPASET_GPIO58
#define TINV_GPIO_PROFILING1_CLEAR         GPIO_GPACLEAR_GPIO58
#define TINV_GPIO_PROFILING1_PIN_CONFIG    GPIO_58_GPIO58

#define TINV_GPIO_PROFILING2               59
#define TINV_GPIO_PROFILING2_SET           GPIO_GPASET_GPIO59
#define TINV_GPIO_PROFILING2_CLEAR         GPIO_GPACLEAR_GPIO59
#define TINV_GPIO_PROFILING2_PIN_CONFIG    GPIO_59_GPIO59

#define TINV_GPIO_LED1                     31
#define TINV_GPIO_LED1_SET                 GPIO_GPASET_GPIO31
#define TINV_GPIO_LED1_CLEAR               GPIO_GPACLEAR_GPIO31
#define TINV_GPIO_LED1_PIN_CONFIG          GPIO_31_GPIO31

#define TINV_GPIO_LED2                     34
#define TINV_GPIO_LED2_SET                 GPIO_GPASET_GPIO34
#define TINV_GPIO_LED2_CLEAR               GPIO_GPACLEAR_GPIO34
#define TINV_GPIO_LED2_PIN_CONFIG          GPIO_34_GPIO34

#define TINV_SCI_VBUS_CLK          50000000
#define TINV_SFRA_GUI_SCI_BAUDRATE 57600

void tida01606_setupGPIO(uint16_t isPWM,
                         uint16_t isADC,
                         uint16_t isRelay,
                         uint16_t isFan,
                         uint16_t isEnPWM);
void tida016060_enable_disable_Relay(uint16_t phase);
void tida01606_setupADC(void);

void tida01606_setupGateDrivePwm(uint32_t base,
                                 uint16_t pwm_period_ticks,
                                 uint16_t pwm_dbred_ticks,
                                 uint16_t pwm_dbfed_ticks);


void tida01606_setupTINV6EPWM(uint16_t pwm_period_ticks,
                              uint16_t pwm_dbred_ticks,
                              uint16_t pwm_dbfed_ticks);

void tida01606_setupPhasePWM(uint32_t base1A,
                             uint32_t base2A,
                             uint16_t pwm_period_ticks,
                             uint16_t pwm_dbred_ticks,
                             uint16_t pwm_dbfed_ticks);
//
// USER CODE END (section: User_Section)
//
#ifdef __cplusplus
}
#endif

#endif
