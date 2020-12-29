//
// Included Files
//
#ifndef _main_
#define _main_
#include "svm_gen.h"
#include "tida_01606_share.h"


float biendo, dc;

#define freq_svm 20000
#define freq_voltage 50
#define isPWM 1
#define isADC 1
#define isRelay 1
#define isFan 0
#define isEnPWM 1
#define phaseRelay 4
#define ACTIVE_ADC 1


//
// These are defined by the linker (see F2837xd_flash.cmd)
//


int stt;

int counter1, counter2;

const float sin_tab[2048];
float adcA1;
float adcA2;
float adcA3;

float adcB1;
float adcB2;
float adcB3;
float adcB4;

float adcC1;
float adcC2;
float adcC3;

float adcD1;
float adcD2;
float adcD3;



INPUT_SVM input;
INPUT_SVM *pinput = &input;

SECTOR_SECLECT current_sector;
SECTOR_SECLECT *psector= &current_sector ;

TIME_VECTOR time_vector;
TIME_VECTOR *ptime_v = &time_vector;

TIME_VECTOR_OUT time_vector_out;
TIME_VECTOR_OUT *ptime_out = &time_vector_out;

EPWM_COUNTER epwm_counter;
EPWM_COUNTER *pepwm_count = &epwm_counter;


// function prototype
void
configureDAC(void);

__interrupt void epwmQ1ISR(void);

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

    // configu cla
//    CLA_confiClaMemory();
//    CLA_initCpu1Cla1();

    Interrupt_register(INT_EPWM1, &epwmQ1ISR);


    tida01606_setupGPIO( isPWM,
                         isADC,
                         isRelay,
                         isFan,
                         isEnPWM);
    tida01606_setupADC();
    //
    // Configure the DAC module
    //
    configureDAC();

#ifdef ACTIVE_ADC


/*    tida_01606_setup_SDFM(TINV_INV_PWM_PERIOD,
                       TINV_PWM_CLK_IN_SDFM_OSR,
                       TINV_SD_CLK_COUNT,
                       TINV_SDFM_OSR);
                       */

#endif

    counter1 = 100;
    counter2 = 0;
    biendo = 25;
    dc = 60;
    stt  = 0;
    pinput->udc = 20/1.732;// udc chuan hoa

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    tida01606_setupGateDrivePwm(TINV_GATE_DRIVE_PWM_BASE,
                                TINV_GATE_DRIVE_PWM_PERIOD,
                                TINV_GATE_DRIVE_DEADBAND_PWM_COUNT,
                                TINV_GATE_DRIVE_DEADBAND_PWM_COUNT);
    tida01606_setupTINV6EPWM(TINV_INV_PWM_PERIOD,
                             TINV_INV_DEADBAND_PWM_COUNT,
                             TINV_INV_DEADBAND_PWM_COUNT);


    tida016060_enable_disable_Relay(phaseRelay);
    /*
    // COPY FLASH TO RAM
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (uint32_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
    */
    //
    // Enable ePWM interrupts
    // PIE level
    //
    Interrupt_enable(INT_EPWM1);



    tida_01606_setupTrigger(TINV_INV_PWM_Q1A_BASE);


    // enable global interupt(intm) and realtime interrupt
    EINT;
    ERTM;
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    while(1)
    {

    }

}

__interrupt void epwmQ1ISR(void){
    GPIO_togglePin(35);
    adcA1 = ADC_readResult( ADCARESULT_BASE , ADC_SOC_NUMBER0 );
    adcA2 = ADC_readResult( ADCARESULT_BASE , ADC_SOC_NUMBER3 );
    adcA3 = ADC_readResult( ADCARESULT_BASE , ADC_SOC_NUMBER6 );

    adcB1 = ADC_readResult( ADCBRESULT_BASE , ADC_SOC_NUMBER10 );
    adcB2 = ADC_readResult( ADCBRESULT_BASE , ADC_SOC_NUMBER11 );
    adcB3 = ADC_readResult( ADCBRESULT_BASE , ADC_SOC_NUMBER12 );
    adcB4 = ADC_readResult( ADCBRESULT_BASE , ADC_SOC_NUMBER13 );

    adcC1 = ADC_readResult( ADCCRESULT_BASE , ADC_SOC_NUMBER1 );
    adcC2 = ADC_readResult( ADCCRESULT_BASE , ADC_SOC_NUMBER4 );
    adcC3 = ADC_readResult( ADCCRESULT_BASE , ADC_SOC_NUMBER7 );

    adcD1 = ADC_readResult( ADCDRESULT_BASE , ADC_SOC_NUMBER2 );
    adcD2 = ADC_readResult( ADCDRESULT_BASE , ADC_SOC_NUMBER5 );
    adcD3 = ADC_readResult( ADCDRESULT_BASE , ADC_SOC_NUMBER8 );

    switch (stt){
    case 1: DAC_setShadowValue(DACA_BASE, adcA1);
    break;
    case 2: DAC_setShadowValue(DACA_BASE, adcA2);
    break;
    case 3: DAC_setShadowValue(DACA_BASE, adcA3);
    break;
    case 4: DAC_setShadowValue(DACA_BASE, adcB1);
    break;
    case 5: DAC_setShadowValue(DACA_BASE, adcB2);
    break;
    case 6: DAC_setShadowValue(DACA_BASE, adcB3);
    break;
    case 7: DAC_setShadowValue(DACA_BASE, adcB4);
    break;
    case 8:DAC_setShadowValue(DACA_BASE, adcC1);
    break;
    case 9:DAC_setShadowValue(DACA_BASE, adcC2);
    break;
    case 10:DAC_setShadowValue(DACA_BASE, adcC3);
    break;
    case 11: DAC_setShadowValue(DACA_BASE, adcD1);
    break;
    case 12: DAC_setShadowValue(DACA_BASE, adcD2);
    break;
    case 13:DAC_setShadowValue(DACA_BASE, adcD3);
    break;
    default : DAC_setShadowValue(DACA_BASE, adcA3);
    break;
    }
    DAC_setShadowValue(DACA_BASE, adcA3);

    pinput->udc = dc/1.732;
    pinput->ua = biendo*sin_tab[(int)(counter1*5.12f)];
    pinput->ub = biendo*sin_tab[(int)(counter2*5.12f)];

//    EPWM_setCounterCompareValue(TINV_INV_PWM_Q1A_BASE, EPWM_COUNTER_COMPARE_A, duty);

//    svm_gen( pinput, psector, ptime_v, ptime_out, pepwm_count);
    counter1++;
    counter2++;
    if((int)(counter1*5.12f) > 2047) counter1 = 0;
    if((int)(counter2*5.12f) > 2047) counter2 = 0;
    GPIO_togglePin(35);

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(TINV_INV_PWM_Q1A_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);

}


void
configureDAC(void)
{
    //
    // Set VDAC as the DAC reference voltage.
    // Edit here to use ADC VREF as the reference voltage.
    //
    DAC_setReferenceVoltage(DACA_BASE, DAC_REF_ADC_VREFHI);

    //
    // Enable the DAC output
    //
    DAC_enableOutput(DACA_BASE);

    //
    // Set the DAC shadow output to 0
    //
    DAC_setShadowValue(DACA_BASE, 0);
    DAC_tuneOffsetTrim(DACA_BASE, 3.255f);

    //
    // Delay for buffered DAC to power up
    //
    DEVICE_DELAY_US(10);
}


const float sin_tab[] =
{           /*  RealSINVAL                                          Index        */
                      0.0        ,               /*                     0        */
                0.0030695        ,               /*                     1        */
                0.0061389        ,               /*                     2        */
                0.0092083        ,               /*                     3        */
                0.0122775        ,               /*                     4        */
                0.0153467        ,               /*                     5        */
                0.0184157        ,               /*                     6        */
                0.0214846        ,               /*                     7        */
                0.0245532        ,               /*                     8        */
                0.0276216        ,               /*                     9        */
                0.0306898        ,               /*                    10        */
                0.0337576        ,               /*                    11        */
                0.0368252        ,               /*                    12        */
                0.0398924        ,               /*                    13        */
                0.0429592        ,               /*                    14        */
                0.0460256        ,               /*                    15        */
                0.0490916        ,               /*                    16        */
                0.0521571        ,               /*                    17        */
                0.0552222        ,               /*                    18        */
                0.0582867        ,               /*                    19        */
                0.0613507        ,               /*                    20        */
                 0.064414        ,               /*                    21        */
                0.0674768        ,               /*                    22        */
                 0.070539        ,               /*                    23        */
                0.0736004        ,               /*                    24        */
                0.0766612        ,               /*                    25        */
                0.0797213        ,               /*                    26        */
                0.0827806        ,               /*                    27        */
                0.0858391        ,               /*                    28        */
                0.0888968        ,               /*                    29        */
                0.0919537        ,               /*                    30        */
                0.0950097        ,               /*                    31        */
                0.0980649        ,               /*                    32        */
                0.1011191        ,               /*                    33        */
                0.1041723        ,               /*                    34        */
                0.1072246        ,               /*                    35        */
                0.1102758        ,               /*                    36        */
                 0.113326        ,               /*                    37        */
                0.1163752        ,               /*                    38        */
                0.1194232        ,               /*                    39        */
                0.1224702        ,               /*                    40        */
                0.1255159        ,               /*                    41        */
                0.1285605        ,               /*                    42        */
                0.1316039        ,               /*                    43        */
                0.1346461        ,               /*                    44        */
                0.1376869        ,               /*                    45        */
                0.1407265        ,               /*                    46        */
                0.1437647        ,               /*                    47        */
                0.1468016        ,               /*                    48        */
                0.1498371        ,               /*                    49        */
                0.1528712        ,               /*                    50        */
                0.1559039        ,               /*                    51        */
                0.1589351        ,               /*                    52        */
                0.1619648        ,               /*                    53        */
                0.1649929        ,               /*                    54        */
                0.1680196        ,               /*                    55        */
                0.1710446        ,               /*                    56        */
                 0.174068        ,               /*                    57        */
                0.1770898        ,               /*                    58        */
                0.1801099        ,               /*                    59        */
                0.1831283        ,               /*                    60        */
                 0.186145        ,               /*                    61        */
                0.1891599        ,               /*                    62        */
                0.1921731        ,               /*                    63        */
                0.1951844        ,               /*                    64        */
                0.1981939        ,               /*                    65        */
                0.2012015        ,               /*                    66        */
                0.2042073        ,               /*                    67        */
                0.2072111        ,               /*                    68        */
                0.2102129        ,               /*                    69        */
                0.2132128        ,               /*                    70        */
                0.2162107        ,               /*                    71        */
                0.2192065        ,               /*                    72        */
                0.2222003        ,               /*                    73        */
                 0.225192        ,               /*                    74        */
                0.2281815        ,               /*                    75        */
                0.2311689        ,               /*                    76        */
                0.2341542        ,               /*                    77        */
                0.2371372        ,               /*                    78        */
                 0.240118        ,               /*                    79        */
                0.2430965        ,               /*                    80        */
                0.2460727        ,               /*                    81        */
                0.2490466        ,               /*                    82        */
                0.2520182        ,               /*                    83        */
                0.2549874        ,               /*                    84        */
                0.2579542        ,               /*                    85        */
                0.2609185        ,               /*                    86        */
                0.2638805        ,               /*                    87        */
                0.2668399        ,               /*                    88        */
                0.2697968        ,               /*                    89        */
                0.2727511        ,               /*                    90        */
                0.2757029        ,               /*                    91        */
                0.2786521        ,               /*                    92        */
                0.2815987        ,               /*                    93        */
                0.2845426        ,               /*                    94        */
                0.2874838        ,               /*                    95        */
                0.2904224        ,               /*                    96        */
                0.2933581        ,               /*                    97        */
                0.2962912        ,               /*                    98        */
                0.2992214        ,               /*                    99        */
                0.3021488        ,               /*                   100        */
                0.3050734        ,               /*                   101        */
                0.3079951        ,               /*                   102        */
                0.3109139        ,               /*                   103        */
                0.3138297        ,               /*                   104        */
                0.3167426        ,               /*                   105        */
                0.3196526        ,               /*                   106        */
                0.3225595        ,               /*                   107        */
                0.3254633        ,               /*                   108        */
                0.3283642        ,               /*                   109        */
                0.3312619        ,               /*                   110        */
                0.3341565        ,               /*                   111        */
                0.3370479        ,               /*                   112        */
                0.3399362        ,               /*                   113        */
                0.3428212        ,               /*                   114        */
                0.3457031        ,               /*                   115        */
                0.3485816        ,               /*                   116        */
                0.3514569        ,               /*                   117        */
                0.3543289        ,               /*                   118        */
                0.3571976        ,               /*                   119        */
                0.3600628        ,               /*                   120        */
                0.3629247        ,               /*                   121        */
                0.3657832        ,               /*                   122        */
                0.3686382        ,               /*                   123        */
                0.3714897        ,               /*                   124        */
                0.3743378        ,               /*                   125        */
                0.3771823        ,               /*                   126        */
                0.3800233        ,               /*                   127        */
                0.3828607        ,               /*                   128        */
                0.3856944        ,               /*                   129        */
                0.3885246        ,               /*                   130        */
                0.3913511        ,               /*                   131        */
                0.3941739        ,               /*                   132        */
                0.3969929        ,               /*                   133        */
                0.3998083        ,               /*                   134        */
                0.4026199        ,               /*                   135        */
                0.4054277        ,               /*                   136        */
                0.4082316        ,               /*                   137        */
                0.4110317        ,               /*                   138        */
                 0.413828        ,               /*                   139        */
                0.4166203        ,               /*                   140        */
                0.4194087        ,               /*                   141        */
                0.4221932        ,               /*                   142        */
                0.4249737        ,               /*                   143        */
                0.4277502        ,               /*                   144        */
                0.4305226        ,               /*                   145        */
                 0.433291        ,               /*                   146        */
                0.4360554        ,               /*                   147        */
                0.4388156        ,               /*                   148        */
                0.4415716        ,               /*                   149        */
                0.4443236        ,               /*                   150        */
                0.4470713        ,               /*                   151        */
                0.4498148        ,               /*                   152        */
                0.4525541        ,               /*                   153        */
                0.4552891        ,               /*                   154        */
                0.4580198        ,               /*                   155        */
                0.4607462        ,               /*                   156        */
                0.4634683        ,               /*                   157        */
                 0.466186        ,               /*                   158        */
                0.4688993        ,               /*                   159        */
                0.4716082        ,               /*                   160        */
                0.4743127        ,               /*                   161        */
                0.4770126        ,               /*                   162        */
                0.4797081        ,               /*                   163        */
                0.4823991        ,               /*                   164        */
                0.4850855        ,               /*                   165        */
                0.4877674        ,               /*                   166        */
                0.4904446        ,               /*                   167        */
                0.4931173        ,               /*                   168        */
                0.4957852        ,               /*                   169        */
                0.4984486        ,               /*                   170        */
                0.5011072        ,               /*                   171        */
                0.5037611        ,               /*                   172        */
                0.5064102        ,               /*                   173        */
                0.5090546        ,               /*                   174        */
                0.5116942        ,               /*                   175        */
                 0.514329        ,               /*                   176        */
                0.5169589        ,               /*                   177        */
                 0.519584        ,               /*                   178        */
                0.5222041        ,               /*                   179        */
                0.5248193        ,               /*                   180        */
                0.5274296        ,               /*                   181        */
                 0.530035        ,               /*                   182        */
                0.5326353        ,               /*                   183        */
                0.5352306        ,               /*                   184        */
                0.5378209        ,               /*                   185        */
                0.5404061        ,               /*                   186        */
                0.5429862        ,               /*                   187        */
                0.5455612        ,               /*                   188        */
                 0.548131        ,               /*                   189        */
                0.5506957        ,               /*                   190        */
                0.5532552        ,               /*                   191        */
                0.5558095        ,               /*                   192        */
                0.5583585        ,               /*                   193        */
                0.5609023        ,               /*                   194        */
                0.5634408        ,               /*                   195        */
                 0.565974        ,               /*                   196        */
                0.5685019        ,               /*                   197        */
                0.5710244        ,               /*                   198        */
                0.5735415        ,               /*                   199        */
                0.5760532        ,               /*                   200        */
                0.5785595        ,               /*                   201        */
                0.5810604        ,               /*                   202        */
                0.5835558        ,               /*                   203        */
                0.5860456        ,               /*                   204        */
                  0.58853        ,               /*                   205        */
                0.5910088        ,               /*                   206        */
                 0.593482        ,               /*                   207        */
                0.5959497        ,               /*                   208        */
                0.5984117        ,               /*                   209        */
                0.6008681        ,               /*                   210        */
                0.6033188        ,               /*                   211        */
                0.6057639        ,               /*                   212        */
                0.6082032        ,               /*                   213        */
                0.6106368        ,               /*                   214        */
                0.6130647        ,               /*                   215        */
                0.6154868        ,               /*                   216        */
                0.6179031        ,               /*                   217        */
                0.6203135        ,               /*                   218        */
                0.6227181        ,               /*                   219        */
                0.6251169        ,               /*                   220        */
                0.6275097        ,               /*                   221        */
                0.6298967        ,               /*                   222        */
                0.6322777        ,               /*                   223        */
                0.6346528        ,               /*                   224        */
                0.6370218        ,               /*                   225        */
                0.6393849        ,               /*                   226        */
                 0.641742        ,               /*                   227        */
                 0.644093        ,               /*                   228        */
                0.6464379        ,               /*                   229        */
                0.6487768        ,               /*                   230        */
                0.6511095        ,               /*                   231        */
                0.6534361        ,               /*                   232        */
                0.6557565        ,               /*                   233        */
                0.6580708        ,               /*                   234        */
                0.6603789        ,               /*                   235        */
                0.6626807        ,               /*                   236        */
                0.6649763        ,               /*                   237        */
                0.6672656        ,               /*                   238        */
                0.6695487        ,               /*                   239        */
                0.6718254        ,               /*                   240        */
                0.6740958        ,               /*                   241        */
                0.6763599        ,               /*                   242        */
                0.6786176        ,               /*                   243        */
                0.6808689        ,               /*                   244        */
                0.6831138        ,               /*                   245        */
                0.6853522        ,               /*                   246        */
                0.6875842        ,               /*                   247        */
                0.6898097        ,               /*                   248        */
                0.6920287        ,               /*                   249        */
                0.6942412        ,               /*                   250        */
                0.6964471        ,               /*                   251        */
                0.6986465        ,               /*                   252        */
                0.7008393        ,               /*                   253        */
                0.7030255        ,               /*                   254        */
                0.7052051        ,               /*                   255        */
                 0.707378        ,               /*                   256        */
                0.7095443        ,               /*                   257        */
                0.7117039        ,               /*                   258        */
                0.7138568        ,               /*                   259        */
                0.7160029        ,               /*                   260        */
                0.7181423        ,               /*                   261        */
                 0.720275        ,               /*                   262        */
                0.7224008        ,               /*                   263        */
                0.7245199        ,               /*                   264        */
                0.7266321        ,               /*                   265        */
                0.7287375        ,               /*                   266        */
                 0.730836        ,               /*                   267        */
                0.7329276        ,               /*                   268        */
                0.7350123        ,               /*                   269        */
                0.7370901        ,               /*                   270        */
                0.7391609        ,               /*                   271        */
                0.7412248        ,               /*                   272        */
                0.7432817        ,               /*                   273        */
                0.7453316        ,               /*                   274        */
                0.7473745        ,               /*                   275        */
                0.7494103        ,               /*                   276        */
                0.7514391        ,               /*                   277        */
                0.7534608        ,               /*                   278        */
                0.7554754        ,               /*                   279        */
                0.7574829        ,               /*                   280        */
                0.7594832        ,               /*                   281        */
                0.7614764        ,               /*                   282        */
                0.7634624        ,               /*                   283        */
                0.7654412        ,               /*                   284        */
                0.7674128        ,               /*                   285        */
                0.7693772        ,               /*                   286        */
                0.7713344        ,               /*                   287        */
                0.7732842        ,               /*                   288        */
                0.7752268        ,               /*                   289        */
                0.7771621        ,               /*                   290        */
                  0.77909        ,               /*                   291        */
                0.7810106        ,               /*                   292        */
                0.7829239        ,               /*                   293        */
                0.7848297        ,               /*                   294        */
                0.7867282        ,               /*                   295        */
                0.7886193        ,               /*                   296        */
                0.7905029        ,               /*                   297        */
                0.7923791        ,               /*                   298        */
                0.7942478        ,               /*                   299        */
                0.7961091        ,               /*                   300        */
                0.7979628        ,               /*                   301        */
                 0.799809        ,               /*                   302        */
                0.8016477        ,               /*                   303        */
                0.8034789        ,               /*                   304        */
                0.8053024        ,               /*                   305        */
                0.8071184        ,               /*                   306        */
                0.8089268        ,               /*                   307        */
                0.8107275        ,               /*                   308        */
                0.8125206        ,               /*                   309        */
                0.8143061        ,               /*                   310        */
                0.8160839        ,               /*                   311        */
                 0.817854        ,               /*                   312        */
                0.8196164        ,               /*                   313        */
                 0.821371        ,               /*                   314        */
                 0.823118        ,               /*                   315        */
                0.8248571        ,               /*                   316        */
                0.8265885        ,               /*                   317        */
                0.8283122        ,               /*                   318        */
                 0.830028        ,               /*                   319        */
                 0.831736        ,               /*                   320        */
                0.8334361        ,               /*                   321        */
                0.8351284        ,               /*                   322        */
                0.8368129        ,               /*                   323        */
                0.8384894        ,               /*                   324        */
                0.8401581        ,               /*                   325        */
                0.8418188        ,               /*                   326        */
                0.8434716        ,               /*                   327        */
                0.8451165        ,               /*                   328        */
                0.8467534        ,               /*                   329        */
                0.8483823        ,               /*                   330        */
                0.8500032        ,               /*                   331        */
                0.8516161        ,               /*                   332        */
                 0.853221        ,               /*                   333        */
                0.8548179        ,               /*                   334        */
                0.8564067        ,               /*                   335        */
                0.8579874        ,               /*                   336        */
                  0.85956        ,               /*                   337        */
                0.8611246        ,               /*                   338        */
                 0.862681        ,               /*                   339        */
                0.8642293        ,               /*                   340        */
                0.8657695        ,               /*                   341        */
                0.8673015        ,               /*                   342        */
                0.8688253        ,               /*                   343        */
                 0.870341        ,               /*                   344        */
                0.8718485        ,               /*                   345        */
                0.8733477        ,               /*                   346        */
                0.8748387        ,               /*                   347        */
                0.8763215        ,               /*                   348        */
                 0.877796        ,               /*                   349        */
                0.8792622        ,               /*                   350        */
                0.8807202        ,               /*                   351        */
                0.8821698        ,               /*                   352        */
                0.8836112        ,               /*                   353        */
                0.8850442        ,               /*                   354        */
                0.8864689        ,               /*                   355        */
                0.8878852        ,               /*                   356        */
                0.8892932        ,               /*                   357        */
                0.8906928        ,               /*                   358        */
                 0.892084        ,               /*                   359        */
                0.8934668        ,               /*                   360        */
                0.8948411        ,               /*                   361        */
                0.8962071        ,               /*                   362        */
                0.8975646        ,               /*                   363        */
                0.8989136        ,               /*                   364        */
                0.9002542        ,               /*                   365        */
                0.9015863        ,               /*                   366        */
                0.9029099        ,               /*                   367        */
                 0.904225        ,               /*                   368        */
                0.9055315        ,               /*                   369        */
                0.9068296        ,               /*                   370        */
                0.9081191        ,               /*                   371        */
                   0.9094        ,               /*                   372        */
                0.9106724        ,               /*                   373        */
                0.9119362        ,               /*                   374        */
                0.9131914        ,               /*                   375        */
                 0.914438        ,               /*                   376        */
                 0.915676        ,               /*                   377        */
                0.9169053        ,               /*                   378        */
                 0.918126        ,               /*                   379        */
                0.9193381        ,               /*                   380        */
                0.9205415        ,               /*                   381        */
                0.9217362        ,               /*                   382        */
                0.9229223        ,               /*                   383        */
                0.9240996        ,               /*                   384        */
                0.9252683        ,               /*                   385        */
                0.9264282        ,               /*                   386        */
                0.9275794        ,               /*                   387        */
                0.9287219        ,               /*                   388        */
                0.9298556        ,               /*                   389        */
                0.9309805        ,               /*                   390        */
                0.9320967        ,               /*                   391        */
                0.9332041        ,               /*                   392        */
                0.9343027        ,               /*                   393        */
                0.9353925        ,               /*                   394        */
                0.9364735        ,               /*                   395        */
                0.9375456        ,               /*                   396        */
                 0.938609        ,               /*                   397        */
                0.9396635        ,               /*                   398        */
                0.9407091        ,               /*                   399        */
                0.9417459        ,               /*                   400        */
                0.9427738        ,               /*                   401        */
                0.9437928        ,               /*                   402        */
                0.9448029        ,               /*                   403        */
                0.9458041        ,               /*                   404        */
                0.9467964        ,               /*                   405        */
                0.9477798        ,               /*                   406        */
                0.9487543        ,               /*                   407        */
                0.9497198        ,               /*                   408        */
                0.9506764        ,               /*                   409        */
                 0.951624        ,               /*                   410        */
                0.9525627        ,               /*                   411        */
                0.9534923        ,               /*                   412        */
                 0.954413        ,               /*                   413        */
                0.9553247        ,               /*                   414        */
                0.9562274        ,               /*                   415        */
                0.9571211        ,               /*                   416        */
                0.9580058        ,               /*                   417        */
                0.9588815        ,               /*                   418        */
                0.9597481        ,               /*                   419        */
                0.9606057        ,               /*                   420        */
                0.9614542        ,               /*                   421        */
                0.9622936        ,               /*                   422        */
                 0.963124        ,               /*                   423        */
                0.9639454        ,               /*                   424        */
                0.9647576        ,               /*                   425        */
                0.9655608        ,               /*                   426        */
                0.9663548        ,               /*                   427        */
                0.9671398        ,               /*                   428        */
                0.9679156        ,               /*                   429        */
                0.9686823        ,               /*                   430        */
                0.9694399        ,               /*                   431        */
                0.9701884        ,               /*                   432        */
                0.9709277        ,               /*                   433        */
                0.9716579        ,               /*                   434        */
                0.9723789        ,               /*                   435        */
                0.9730907        ,               /*                   436        */
                0.9737934        ,               /*                   437        */
                0.9744869        ,               /*                   438        */
                0.9751713        ,               /*                   439        */
                0.9758464        ,               /*                   440        */
                0.9765124        ,               /*                   441        */
                0.9771691        ,               /*                   442        */
                0.9778166        ,               /*                   443        */
                 0.978455        ,               /*                   444        */
                0.9790841        ,               /*                   445        */
                 0.979704        ,               /*                   446        */
                0.9803146        ,               /*                   447        */
                0.9809161        ,               /*                   448        */
                0.9815082        ,               /*                   449        */
                0.9820912        ,               /*                   450        */
                0.9826648        ,               /*                   451        */
                0.9832293        ,               /*                   452        */
                0.9837844        ,               /*                   453        */
                0.9843303        ,               /*                   454        */
                0.9848669        ,               /*                   455        */
                0.9853943        ,               /*                   456        */
                0.9859123        ,               /*                   457        */
                0.9864211        ,               /*                   458        */
                0.9869205        ,               /*                   459        */
                0.9874107        ,               /*                   460        */
                0.9878916        ,               /*                   461        */
                0.9883631        ,               /*                   462        */
                0.9888254        ,               /*                   463        */
                0.9892783        ,               /*                   464        */
                0.9897219        ,               /*                   465        */
                0.9901562        ,               /*                   466        */
                0.9905812        ,               /*                   467        */
                0.9909968        ,               /*                   468        */
                0.9914031        ,               /*                   469        */
                   0.9918        ,               /*                   470        */
                0.9921876        ,               /*                   471        */
                0.9925659        ,               /*                   472        */
                0.9929348        ,               /*                   473        */
                0.9932943        ,               /*                   474        */
                0.9936445        ,               /*                   475        */
                0.9939854        ,               /*                   476        */
                0.9943168        ,               /*                   477        */
                0.9946389        ,               /*                   478        */
                0.9949516        ,               /*                   479        */
                 0.995255        ,               /*                   480        */
                 0.995549        ,               /*                   481        */
                0.9958335        ,               /*                   482        */
                0.9961088        ,               /*                   483        */
                0.9963746        ,               /*                   484        */
                 0.996631        ,               /*                   485        */
                0.9968781        ,               /*                   486        */
                0.9971157        ,               /*                   487        */
                 0.997344        ,               /*                   488        */
                0.9975629        ,               /*                   489        */
                0.9977723        ,               /*                   490        */
                0.9979724        ,               /*                   491        */
                0.9981631        ,               /*                   492        */
                0.9983443        ,               /*                   493        */
                0.9985162        ,               /*                   494        */
                0.9986786        ,               /*                   495        */
                0.9988317        ,               /*                   496        */
                0.9989753        ,               /*                   497        */
                0.9991095        ,               /*                   498        */
                0.9992343        ,               /*                   499        */
                0.9993497        ,               /*                   500        */
                0.9994557        ,               /*                   501        */
                0.9995522        ,               /*                   502        */
                0.9996394        ,               /*                   503        */
                0.9997171        ,               /*                   504        */
                0.9997854        ,               /*                   505        */
                0.9998443        ,               /*                   506        */
                0.9998937        ,               /*                   507        */
                0.9999338        ,               /*                   508        */
                0.9999644        ,               /*                   509        */
                0.9999856        ,               /*                   510        */
                0.9999974        ,               /*                   511        */
                0.9999997        ,               /*                   512        */
                0.9999926        ,               /*                   513        */
                0.9999762        ,               /*                   514        */
                0.9999502        ,               /*                   515        */
                0.9999149        ,               /*                   516        */
                0.9998702        ,               /*                   517        */
                 0.999816        ,               /*                   518        */
                0.9997524        ,               /*                   519        */
                0.9996794        ,               /*                   520        */
                 0.999597        ,               /*                   521        */
                0.9995051        ,               /*                   522        */
                0.9994038        ,               /*                   523        */
                0.9992932        ,               /*                   524        */
                0.9991731        ,               /*                   525        */
                0.9990436        ,               /*                   526        */
                0.9989046        ,               /*                   527        */
                0.9987563        ,               /*                   528        */
                0.9985986        ,               /*                   529        */
                0.9984314        ,               /*                   530        */
                0.9982549        ,               /*                   531        */
                0.9980689        ,               /*                   532        */
                0.9978735        ,               /*                   533        */
                0.9976688        ,               /*                   534        */
                0.9974546        ,               /*                   535        */
                 0.997231        ,               /*                   536        */
                0.9969981        ,               /*                   537        */
                0.9967557        ,               /*                   538        */
                 0.996504        ,               /*                   539        */
                0.9962428        ,               /*                   540        */
                0.9959723        ,               /*                   541        */
                0.9956924        ,               /*                   542        */
                0.9954031        ,               /*                   543        */
                0.9951045        ,               /*                   544        */
                0.9947964        ,               /*                   545        */
                 0.994479        ,               /*                   546        */
                0.9941523        ,               /*                   547        */
                0.9938161        ,               /*                   548        */
                0.9934706        ,               /*                   549        */
                0.9931157        ,               /*                   550        */
                0.9927515        ,               /*                   551        */
                0.9923779        ,               /*                   552        */
                 0.991995        ,               /*                   553        */
                0.9916027        ,               /*                   554        */
                0.9912011        ,               /*                   555        */
                0.9907901        ,               /*                   556        */
                0.9903699        ,               /*                   557        */
                0.9899402        ,               /*                   558        */
                0.9895013        ,               /*                   559        */
                 0.989053        ,               /*                   560        */
                0.9885954        ,               /*                   561        */
                0.9881285        ,               /*                   562        */
                0.9876523        ,               /*                   563        */
                0.9871668        ,               /*                   564        */
                 0.986672        ,               /*                   565        */
                0.9861678        ,               /*                   566        */
                0.9856544        ,               /*                   567        */
                0.9851317        ,               /*                   568        */
                0.9845998        ,               /*                   569        */
                0.9840585        ,               /*                   570        */
                 0.983508        ,               /*                   571        */
                0.9829482        ,               /*                   572        */
                0.9823792        ,               /*                   573        */
                0.9818009        ,               /*                   574        */
                0.9812133        ,               /*                   575        */
                0.9806165        ,               /*                   576        */
                0.9800105        ,               /*                   577        */
                0.9793952        ,               /*                   578        */
                0.9787707        ,               /*                   579        */
                 0.978137        ,               /*                   580        */
                 0.977494        ,               /*                   581        */
                0.9768419        ,               /*                   582        */
                0.9761805        ,               /*                   583        */
                  0.97551        ,               /*                   584        */
                0.9748302        ,               /*                   585        */
                0.9741413        ,               /*                   586        */
                0.9734432        ,               /*                   587        */
                0.9727359        ,               /*                   588        */
                0.9720195        ,               /*                   589        */
                0.9712939        ,               /*                   590        */
                0.9705592        ,               /*                   591        */
                0.9698153        ,               /*                   592        */
                0.9690623        ,               /*                   593        */
                0.9683001        ,               /*                   594        */
                0.9675288        ,               /*                   595        */
                0.9667484        ,               /*                   596        */
                0.9659589        ,               /*                   597        */
                0.9651603        ,               /*                   598        */
                0.9643526        ,               /*                   599        */
                0.9635358        ,               /*                   600        */
                  0.96271        ,               /*                   601        */
                 0.961875        ,               /*                   602        */
                 0.961031        ,               /*                   603        */
                 0.960178        ,               /*                   604        */
                0.9593159        ,               /*                   605        */
                0.9584448        ,               /*                   606        */
                0.9575646        ,               /*                   607        */
                0.9566754        ,               /*                   608        */
                0.9557772        ,               /*                   609        */
                  0.95487        ,               /*                   610        */
                0.9539538        ,               /*                   611        */
                0.9530286        ,               /*                   612        */
                0.9520945        ,               /*                   613        */
                0.9511513        ,               /*                   614        */
                0.9501992        ,               /*                   615        */
                0.9492382        ,               /*                   616        */
                0.9482682        ,               /*                   617        */
                0.9472893        ,               /*                   618        */
                0.9463014        ,               /*                   619        */
                0.9453046        ,               /*                   620        */
                 0.944299        ,               /*                   621        */
                0.9432844        ,               /*                   622        */
                0.9422609        ,               /*                   623        */
                0.9412286        ,               /*                   624        */
                0.9401874        ,               /*                   625        */
                0.9391373        ,               /*                   626        */
                0.9380784        ,               /*                   627        */
                0.9370107        ,               /*                   628        */
                0.9359341        ,               /*                   629        */
                0.9348487        ,               /*                   630        */
                0.9337545        ,               /*                   631        */
                0.9326515        ,               /*                   632        */
                0.9315397        ,               /*                   633        */
                0.9304191        ,               /*                   634        */
                0.9292898        ,               /*                   635        */
                0.9281517        ,               /*                   636        */
                0.9270049        ,               /*                   637        */
                0.9258493        ,               /*                   638        */
                 0.924685        ,               /*                   639        */
                 0.923512        ,               /*                   640        */
                0.9223303        ,               /*                   641        */
                0.9211399        ,               /*                   642        */
                0.9199409        ,               /*                   643        */
                0.9187331        ,               /*                   644        */
                0.9175168        ,               /*                   645        */
                0.9162917        ,               /*                   646        */
                 0.915058        ,               /*                   647        */
                0.9138158        ,               /*                   648        */
                0.9125649        ,               /*                   649        */
                0.9113054        ,               /*                   650        */
                0.9100373        ,               /*                   651        */
                0.9087606        ,               /*                   652        */
                0.9074754        ,               /*                   653        */
                0.9061816        ,               /*                   654        */
                0.9048793        ,               /*                   655        */
                0.9035685        ,               /*                   656        */
                0.9022491        ,               /*                   657        */
                0.9009213        ,               /*                   658        */
                 0.899585        ,               /*                   659        */
                0.8982402        ,               /*                   660        */
                0.8968869        ,               /*                   661        */
                0.8955252        ,               /*                   662        */
                 0.894155        ,               /*                   663        */
                0.8927764        ,               /*                   664        */
                0.8913894        ,               /*                   665        */
                 0.889994        ,               /*                   666        */
                0.8885902        ,               /*                   667        */
                0.8871781        ,               /*                   668        */
                0.8857576        ,               /*                   669        */
                0.8843287        ,               /*                   670        */
                0.8828915        ,               /*                   671        */
                 0.881446        ,               /*                   672        */
                0.8799922        ,               /*                   673        */
                0.8785301        ,               /*                   674        */
                0.8770598        ,               /*                   675        */
                0.8755811        ,               /*                   676        */
                0.8740942        ,               /*                   677        */
                0.8725991        ,               /*                   678        */
                0.8710958        ,               /*                   679        */
                0.8695842        ,               /*                   680        */
                0.8680645        ,               /*                   681        */
                0.8665365        ,               /*                   682        */
                0.8650004        ,               /*                   683        */
                0.8634562        ,               /*                   684        */
                0.8619038        ,               /*                   685        */
                0.8603433        ,               /*                   686        */
                0.8587747        ,               /*                   687        */
                 0.857198        ,               /*                   688        */
                0.8556133        ,               /*                   689        */
                0.8540204        ,               /*                   690        */
                0.8524196        ,               /*                   691        */
                0.8508107        ,               /*                   692        */
                0.8491937        ,               /*                   693        */
                0.8475688        ,               /*                   694        */
                0.8459359        ,               /*                   695        */
                 0.844295        ,               /*                   696        */
                0.8426462        ,               /*                   697        */
                0.8409894        ,               /*                   698        */
                0.8393247        ,               /*                   699        */
                0.8376521        ,               /*                   700        */
                0.8359716        ,               /*                   701        */
                0.8342833        ,               /*                   702        */
                 0.832587        ,               /*                   703        */
                 0.830883        ,               /*                   704        */
                 0.829171        ,               /*                   705        */
                0.8274513        ,               /*                   706        */
                0.8257238        ,               /*                   707        */
                0.8239885        ,               /*                   708        */
                0.8222455        ,               /*                   709        */
                0.8204947        ,               /*                   710        */
                0.8187361        ,               /*                   711        */
                0.8169699        ,               /*                   712        */
                0.8151959        ,               /*                   713        */
                0.8134143        ,               /*                   714        */
                 0.811625        ,               /*                   715        */
                0.8098281        ,               /*                   716        */
                0.8080235        ,               /*                   717        */
                0.8062114        ,               /*                   718        */
                0.8043916        ,               /*                   719        */
                0.8025642        ,               /*                   720        */
                0.8007293        ,               /*                   721        */
                0.7988869        ,               /*                   722        */
                0.7970369        ,               /*                   723        */
                0.7951794        ,               /*                   724        */
                0.7933144        ,               /*                   725        */
                 0.791442        ,               /*                   726        */
                 0.789562        ,               /*                   727        */
                0.7876747        ,               /*                   728        */
                0.7857799        ,               /*                   729        */
                0.7838777        ,               /*                   730        */
                0.7819682        ,               /*                   731        */
                0.7800512        ,               /*                   732        */
                0.7781269        ,               /*                   733        */
                0.7761953        ,               /*                   734        */
                0.7742564        ,               /*                   735        */
                0.7723102        ,               /*                   736        */
                0.7703567        ,               /*                   737        */
                0.7683959        ,               /*                   738        */
                0.7664279        ,               /*                   739        */
                0.7644527        ,               /*                   740        */
                0.7624703        ,               /*                   741        */
                0.7604807        ,               /*                   742        */
                0.7584839        ,               /*                   743        */
                  0.75648        ,               /*                   744        */
                 0.754469        ,               /*                   745        */
                0.7524509        ,               /*                   746        */
                0.7504256        ,               /*                   747        */
                0.7483933        ,               /*                   748        */
                 0.746354        ,               /*                   749        */
                0.7443076        ,               /*                   750        */
                0.7422542        ,               /*                   751        */
                0.7401938        ,               /*                   752        */
                0.7381264        ,               /*                   753        */
                0.7360521        ,               /*                   754        */
                0.7339708        ,               /*                   755        */
                0.7318826        ,               /*                   756        */
                0.7297876        ,               /*                   757        */
                0.7276856        ,               /*                   758        */
                0.7255768        ,               /*                   759        */
                0.7234612        ,               /*                   760        */
                0.7213387        ,               /*                   761        */
                0.7192095        ,               /*                   762        */
                0.7170735        ,               /*                   763        */
                0.7149307        ,               /*                   764        */
                0.7127812        ,               /*                   765        */
                0.7106249        ,               /*                   766        */
                 0.708462        ,               /*                   767        */
                0.7062924        ,               /*                   768        */
                0.7041161        ,               /*                   769        */
                0.7019333        ,               /*                   770        */
                0.6997437        ,               /*                   771        */
                0.6975477        ,               /*                   772        */
                 0.695345        ,               /*                   773        */
                0.6931358        ,               /*                   774        */
                  0.69092        ,               /*                   775        */
                0.6886978        ,               /*                   776        */
                 0.686469        ,               /*                   777        */
                0.6842338        ,               /*                   778        */
                0.6819921        ,               /*                   779        */
                 0.679744        ,               /*                   780        */
                0.6774895        ,               /*                   781        */
                0.6752287        ,               /*                   782        */
                0.6729614        ,               /*                   783        */
                0.6706879        ,               /*                   784        */
                 0.668408        ,               /*                   785        */
                0.6661218        ,               /*                   786        */
                0.6638293        ,               /*                   787        */
                0.6615306        ,               /*                   788        */
                0.6592256        ,               /*                   789        */
                0.6569144        ,               /*                   790        */
                0.6545971        ,               /*                   791        */
                0.6522736        ,               /*                   792        */
                0.6499439        ,               /*                   793        */
                0.6476081        ,               /*                   794        */
                0.6452662        ,               /*                   795        */
                0.6429182        ,               /*                   796        */
                0.6405642        ,               /*                   797        */
                0.6382041        ,               /*                   798        */
                0.6358381        ,               /*                   799        */
                 0.633466        ,               /*                   800        */
                0.6310879        ,               /*                   801        */
                 0.628704        ,               /*                   802        */
                0.6263141        ,               /*                   803        */
                0.6239182        ,               /*                   804        */
                0.6215166        ,               /*                   805        */
                 0.619109        ,               /*                   806        */
                0.6166956        ,               /*                   807        */
                0.6142765        ,               /*                   808        */
                0.6118515        ,               /*                   809        */
                0.6094207        ,               /*                   810        */
                0.6069843        ,               /*                   811        */
                0.6045421        ,               /*                   812        */
                0.6020942        ,               /*                   813        */
                0.5996406        ,               /*                   814        */
                0.5971814        ,               /*                   815        */
                0.5947165        ,               /*                   816        */
                0.5922461        ,               /*                   817        */
                0.5897701        ,               /*                   818        */
                0.5872885        ,               /*                   819        */
                0.5848014        ,               /*                   820        */
                0.5823088        ,               /*                   821        */
                0.5798106        ,               /*                   822        */
                0.5773071        ,               /*                   823        */
                0.5747981        ,               /*                   824        */
                0.5722836        ,               /*                   825        */
                0.5697638        ,               /*                   826        */
                0.5672386        ,               /*                   827        */
                0.5647081        ,               /*                   828        */
                0.5621722        ,               /*                   829        */
                0.5596311        ,               /*                   830        */
                0.5570847        ,               /*                   831        */
                 0.554533        ,               /*                   832        */
                0.5519761        ,               /*                   833        */
                 0.549414        ,               /*                   834        */
                0.5468467        ,               /*                   835        */
                0.5442743        ,               /*                   836        */
                0.5416967        ,               /*                   837        */
                0.5391141        ,               /*                   838        */
                0.5365264        ,               /*                   839        */
                0.5339336        ,               /*                   840        */
                0.5313357        ,               /*                   841        */
                0.5287329        ,               /*                   842        */
                0.5261251        ,               /*                   843        */
                0.5235123        ,               /*                   844        */
                0.5208946        ,               /*                   845        */
                 0.518272        ,               /*                   846        */
                0.5156445        ,               /*                   847        */
                0.5130122        ,               /*                   848        */
                 0.510375        ,               /*                   849        */
                 0.507733        ,               /*                   850        */
                0.5050863        ,               /*                   851        */
                0.5024347        ,               /*                   852        */
                0.4997785        ,               /*                   853        */
                0.4971175        ,               /*                   854        */
                0.4944518        ,               /*                   855        */
                0.4917815        ,               /*                   856        */
                0.4891066        ,               /*                   857        */
                 0.486427        ,               /*                   858        */
                0.4837429        ,               /*                   859        */
                0.4810542        ,               /*                   860        */
                0.4783609        ,               /*                   861        */
                0.4756632        ,               /*                   862        */
                 0.472961        ,               /*                   863        */
                0.4702543        ,               /*                   864        */
                0.4675432        ,               /*                   865        */
                0.4648277        ,               /*                   866        */
                0.4621078        ,               /*                   867        */
                0.4593836        ,               /*                   868        */
                 0.456655        ,               /*                   869        */
                0.4539221        ,               /*                   870        */
                 0.451185        ,               /*                   871        */
                0.4484436        ,               /*                   872        */
                0.4456979        ,               /*                   873        */
                0.4429481        ,               /*                   874        */
                0.4401941        ,               /*                   875        */
                 0.437436        ,               /*                   876        */
                0.4346737        ,               /*                   877        */
                0.4319073        ,               /*                   878        */
                0.4291369        ,               /*                   879        */
                0.4263624        ,               /*                   880        */
                 0.423584        ,               /*                   881        */
                0.4208015        ,               /*                   882        */
                 0.418015        ,               /*                   883        */
                0.4152246        ,               /*                   884        */
                0.4124303        ,               /*                   885        */
                0.4096322        ,               /*                   886        */
                0.4068301        ,               /*                   887        */
                0.4040242        ,               /*                   888        */
                0.4012146        ,               /*                   889        */
                0.3984011        ,               /*                   890        */
                0.3955839        ,               /*                   891        */
                0.3927629        ,               /*                   892        */
                0.3899383        ,               /*                   893        */
                  0.38711        ,               /*                   894        */
                 0.384278        ,               /*                   895        */
                0.3814424        ,               /*                   896        */
                0.3786032        ,               /*                   897        */
                0.3757605        ,               /*                   898        */
                0.3729142        ,               /*                   899        */
                0.3700644        ,               /*                   900        */
                0.3672111        ,               /*                   901        */
                0.3643544        ,               /*                   902        */
                0.3614942        ,               /*                   903        */
                0.3586306        ,               /*                   904        */
                0.3557637        ,               /*                   905        */
                0.3528933        ,               /*                   906        */
                0.3500197        ,               /*                   907        */
                0.3471428        ,               /*                   908        */
                0.3442625        ,               /*                   909        */
                0.3413791        ,               /*                   910        */
                0.3384924        ,               /*                   911        */
                0.3356026        ,               /*                   912        */
                0.3327096        ,               /*                   913        */
                0.3298134        ,               /*                   914        */
                0.3269141        ,               /*                   915        */
                0.3240118        ,               /*                   916        */
                0.3211064        ,               /*                   917        */
                 0.318198        ,               /*                   918        */
                0.3152866        ,               /*                   919        */
                0.3123722        ,               /*                   920        */
                0.3094548        ,               /*                   921        */
                0.3065346        ,               /*                   922        */
                0.3036115        ,               /*                   923        */
                0.3006855        ,               /*                   924        */
                0.2977566        ,               /*                   925        */
                 0.294825        ,               /*                   926        */
                0.2918906        ,               /*                   927        */
                0.2889534        ,               /*                   928        */
                0.2860136        ,               /*                   929        */
                 0.283071        ,               /*                   930        */
                0.2801257        ,               /*                   931        */
                0.2771778        ,               /*                   932        */
                0.2742274        ,               /*                   933        */
                0.2712743        ,               /*                   934        */
                0.2683186        ,               /*                   935        */
                0.2653605        ,               /*                   936        */
                0.2623998        ,               /*                   937        */
                0.2594367        ,               /*                   938        */
                0.2564711        ,               /*                   939        */
                0.2535031        ,               /*                   940        */
                0.2505327        ,               /*                   941        */
                  0.24756        ,               /*                   942        */
                0.2445849        ,               /*                   943        */
                0.2416075        ,               /*                   944        */
                0.2386279        ,               /*                   945        */
                0.2356459        ,               /*                   946        */
                0.2326618        ,               /*                   947        */
                0.2296755        ,               /*                   948        */
                 0.226687        ,               /*                   949        */
                0.2236964        ,               /*                   950        */
                0.2207037        ,               /*                   951        */
                0.2177089        ,               /*                   952        */
                 0.214712        ,               /*                   953        */
                0.2117131        ,               /*                   954        */
                0.2087123        ,               /*                   955        */
                0.2057094        ,               /*                   956        */
                0.2027046        ,               /*                   957        */
                0.1996979        ,               /*                   958        */
                0.1966894        ,               /*                   959        */
                 0.193679        ,               /*                   960        */
                0.1906667        ,               /*                   961        */
                0.1876527        ,               /*                   962        */
                0.1846369        ,               /*                   963        */
                0.1816193        ,               /*                   964        */
                   0.1786        ,               /*                   965        */
                0.1755791        ,               /*                   966        */
                0.1725565        ,               /*                   967        */
                0.1695323        ,               /*                   968        */
                0.1665064        ,               /*                   969        */
                0.1634791        ,               /*                   970        */
                0.1604501        ,               /*                   971        */
                0.1574197        ,               /*                   972        */
                0.1543878        ,               /*                   973        */
                0.1513544        ,               /*                   974        */
                0.1483196        ,               /*                   975        */
                0.1452834        ,               /*                   976        */
                0.1422458        ,               /*                   977        */
                0.1392069        ,               /*                   978        */
                0.1361666        ,               /*                   979        */
                0.1331251        ,               /*                   980        */
                0.1300824        ,               /*                   981        */
                0.1270384        ,               /*                   982        */
                0.1239932        ,               /*                   983        */
                0.1209469        ,               /*                   984        */
                0.1178994        ,               /*                   985        */
                0.1148508        ,               /*                   986        */
                0.1118011        ,               /*                   987        */
                0.1087503        ,               /*                   988        */
                0.1056986        ,               /*                   989        */
                0.1026458        ,               /*                   990        */
                0.0995921        ,               /*                   991        */
                0.0965374        ,               /*                   992        */
                0.0934818        ,               /*                   993        */
                0.0904254        ,               /*                   994        */
                0.0873681        ,               /*                   995        */
                  0.08431        ,               /*                   996        */
                 0.081251        ,               /*                   997        */
                0.0781913        ,               /*                   998        */
                0.0751309        ,               /*                   999        */
                0.0720698        ,               /*                  1000        */
                 0.069008        ,               /*                  1001        */
                0.0659455        ,               /*                  1002        */
                0.0628824        ,               /*                  1003        */
                0.0598187        ,               /*                  1004        */
                0.0567545        ,               /*                  1005        */
                0.0536897        ,               /*                  1006        */
                0.0506244        ,               /*                  1007        */
                0.0475587        ,               /*                  1008        */
                0.0444925        ,               /*                  1009        */
                0.0414259        ,               /*                  1010        */
                0.0383588        ,               /*                  1011        */
                0.0352915        ,               /*                  1012        */
                0.0322238        ,               /*                  1013        */
                0.0291557        ,               /*                  1014        */
                0.0260875        ,               /*                  1015        */
                0.0230189        ,               /*                  1016        */
                0.0199502        ,               /*                  1017        */
                0.0168812        ,               /*                  1018        */
                0.0138121        ,               /*                  1019        */
                0.0107429        ,               /*                  1020        */
                0.0076736        ,               /*                  1021        */
                0.0046042        ,               /*                  1022        */
//                0.0015347        ,               /*                  1023        */
                0.00             ,               /*                  1023        */
                -0.001535        ,               /*                  1024        */
                -0.004604        ,               /*                  1025        */
                -0.007674        ,               /*                  1026        */
                -0.010743        ,               /*                  1027        */
                -0.013812        ,               /*                  1028        */
                -0.016881        ,               /*                  1029        */
                 -0.01995        ,               /*                  1030        */
                -0.023019        ,               /*                  1031        */
                -0.026087        ,               /*                  1032        */
                -0.029156        ,               /*                  1033        */
                -0.032224        ,               /*                  1034        */
                -0.035291        ,               /*                  1035        */
                -0.038359        ,               /*                  1036        */
                -0.041426        ,               /*                  1037        */
                -0.044492        ,               /*                  1038        */
                -0.047559        ,               /*                  1039        */
                -0.050624        ,               /*                  1040        */
                 -0.05369        ,               /*                  1041        */
                -0.056755        ,               /*                  1042        */
                -0.059819        ,               /*                  1043        */
                -0.062882        ,               /*                  1044        */
                -0.065946        ,               /*                  1045        */
                -0.069008        ,               /*                  1046        */
                 -0.07207        ,               /*                  1047        */
                -0.075131        ,               /*                  1048        */
                -0.078191        ,               /*                  1049        */
                -0.081251        ,               /*                  1050        */
                 -0.08431        ,               /*                  1051        */
                -0.087368        ,               /*                  1052        */
                -0.090425        ,               /*                  1053        */
                -0.093482        ,               /*                  1054        */
                -0.096537        ,               /*                  1055        */
                -0.099592        ,               /*                  1056        */
                -0.102646        ,               /*                  1057        */
                -0.105699        ,               /*                  1058        */
                 -0.10875        ,               /*                  1059        */
                -0.111801        ,               /*                  1060        */
                -0.114851        ,               /*                  1061        */
                -0.117899        ,               /*                  1062        */
                -0.120947        ,               /*                  1063        */
                -0.123993        ,               /*                  1064        */
                -0.127038        ,               /*                  1065        */
                -0.130082        ,               /*                  1066        */
                -0.133125        ,               /*                  1067        */
                -0.136167        ,               /*                  1068        */
                -0.139207        ,               /*                  1069        */
                -0.142246        ,               /*                  1070        */
                -0.145283        ,               /*                  1071        */
                 -0.14832        ,               /*                  1072        */
                -0.151354        ,               /*                  1073        */
                -0.154388        ,               /*                  1074        */
                 -0.15742        ,               /*                  1075        */
                 -0.16045        ,               /*                  1076        */
                -0.163479        ,               /*                  1077        */
                -0.166506        ,               /*                  1078        */
                -0.169532        ,               /*                  1079        */
                -0.172556        ,               /*                  1080        */
                -0.175579        ,               /*                  1081        */
                  -0.1786        ,               /*                  1082        */
                -0.181619        ,               /*                  1083        */
                -0.184637        ,               /*                  1084        */
                -0.187653        ,               /*                  1085        */
                -0.190667        ,               /*                  1086        */
                -0.193679        ,               /*                  1087        */
                -0.196689        ,               /*                  1088        */
                -0.199698        ,               /*                  1089        */
                -0.202705        ,               /*                  1090        */
                -0.205709        ,               /*                  1091        */
                -0.208712        ,               /*                  1092        */
                -0.211713        ,               /*                  1093        */
                -0.214712        ,               /*                  1094        */
                -0.217709        ,               /*                  1095        */
                -0.220704        ,               /*                  1096        */
                -0.223696        ,               /*                  1097        */
                -0.226687        ,               /*                  1098        */
                -0.229675        ,               /*                  1099        */
                -0.232662        ,               /*                  1100        */
                -0.235646        ,               /*                  1101        */
                -0.238628        ,               /*                  1102        */
                -0.241608        ,               /*                  1103        */
                -0.244585        ,               /*                  1104        */
                 -0.24756        ,               /*                  1105        */
                -0.250533        ,               /*                  1106        */
                -0.253503        ,               /*                  1107        */
                -0.256471        ,               /*                  1108        */
                -0.259437        ,               /*                  1109        */
                  -0.2624        ,               /*                  1110        */
                 -0.26536        ,               /*                  1111        */
                -0.268319        ,               /*                  1112        */
                -0.271274        ,               /*                  1113        */
                -0.274227        ,               /*                  1114        */
                -0.277178        ,               /*                  1115        */
                -0.280126        ,               /*                  1116        */
                -0.283071        ,               /*                  1117        */
                -0.286014        ,               /*                  1118        */
                -0.288953        ,               /*                  1119        */
                -0.291891        ,               /*                  1120        */
                -0.294825        ,               /*                  1121        */
                -0.297757        ,               /*                  1122        */
                -0.300685        ,               /*                  1123        */
                -0.303611        ,               /*                  1124        */
                -0.306535        ,               /*                  1125        */
                -0.309455        ,               /*                  1126        */
                -0.312372        ,               /*                  1127        */
                -0.315287        ,               /*                  1128        */
                -0.318198        ,               /*                  1129        */
                -0.321106        ,               /*                  1130        */
                -0.324012        ,               /*                  1131        */
                -0.326914        ,               /*                  1132        */
                -0.329813        ,               /*                  1133        */
                 -0.33271        ,               /*                  1134        */
                -0.335603        ,               /*                  1135        */
                -0.338492        ,               /*                  1136        */
                -0.341379        ,               /*                  1137        */
                -0.344263        ,               /*                  1138        */
                -0.347143        ,               /*                  1139        */
                 -0.35002        ,               /*                  1140        */
                -0.352893        ,               /*                  1141        */
                -0.355764        ,               /*                  1142        */
                -0.358631        ,               /*                  1143        */
                -0.361494        ,               /*                  1144        */
                -0.364354        ,               /*                  1145        */
                -0.367211        ,               /*                  1146        */
                -0.370064        ,               /*                  1147        */
                -0.372914        ,               /*                  1148        */
                 -0.37576        ,               /*                  1149        */
                -0.378603        ,               /*                  1150        */
                -0.381442        ,               /*                  1151        */
                -0.384278        ,               /*                  1152        */
                 -0.38711        ,               /*                  1153        */
                -0.389938        ,               /*                  1154        */
                -0.392763        ,               /*                  1155        */
                -0.395584        ,               /*                  1156        */
                -0.398401        ,               /*                  1157        */
                -0.401215        ,               /*                  1158        */
                -0.404024        ,               /*                  1159        */
                 -0.40683        ,               /*                  1160        */
                -0.409632        ,               /*                  1161        */
                 -0.41243        ,               /*                  1162        */
                -0.415225        ,               /*                  1163        */
                -0.418015        ,               /*                  1164        */
                -0.420801        ,               /*                  1165        */
                -0.423584        ,               /*                  1166        */
                -0.426362        ,               /*                  1167        */
                -0.429137        ,               /*                  1168        */
                -0.431907        ,               /*                  1169        */
                -0.434674        ,               /*                  1170        */
                -0.437436        ,               /*                  1171        */
                -0.440194        ,               /*                  1172        */
                -0.442948        ,               /*                  1173        */
                -0.445698        ,               /*                  1174        */
                -0.448444        ,               /*                  1175        */
                -0.451185        ,               /*                  1176        */
                -0.453922        ,               /*                  1177        */
                -0.456655        ,               /*                  1178        */
                -0.459384        ,               /*                  1179        */
                -0.462108        ,               /*                  1180        */
                -0.464828        ,               /*                  1181        */
                -0.467543        ,               /*                  1182        */
                -0.470254        ,               /*                  1183        */
                -0.472961        ,               /*                  1184        */
                -0.475663        ,               /*                  1185        */
                -0.478361        ,               /*                  1186        */
                -0.481054        ,               /*                  1187        */
                -0.483743        ,               /*                  1188        */
                -0.486427        ,               /*                  1189        */
                -0.489107        ,               /*                  1190        */
                -0.491782        ,               /*                  1191        */
                -0.494452        ,               /*                  1192        */
                -0.497117        ,               /*                  1193        */
                -0.499778        ,               /*                  1194        */
                -0.502435        ,               /*                  1195        */
                -0.505086        ,               /*                  1196        */
                -0.507733        ,               /*                  1197        */
                -0.510375        ,               /*                  1198        */
                -0.513012        ,               /*                  1199        */
                -0.515645        ,               /*                  1200        */
                -0.518272        ,               /*                  1201        */
                -0.520895        ,               /*                  1202        */
                -0.523512        ,               /*                  1203        */
                -0.526125        ,               /*                  1204        */
                -0.528733        ,               /*                  1205        */
                -0.531336        ,               /*                  1206        */
                -0.533934        ,               /*                  1207        */
                -0.536526        ,               /*                  1208        */
                -0.539114        ,               /*                  1209        */
                -0.541697        ,               /*                  1210        */
                -0.544274        ,               /*                  1211        */
                -0.546847        ,               /*                  1212        */
                -0.549414        ,               /*                  1213        */
                -0.551976        ,               /*                  1214        */
                -0.554533        ,               /*                  1215        */
                -0.557085        ,               /*                  1216        */
                -0.559631        ,               /*                  1217        */
                -0.562172        ,               /*                  1218        */
                -0.564708        ,               /*                  1219        */
                -0.567239        ,               /*                  1220        */
                -0.569764        ,               /*                  1221        */
                -0.572284        ,               /*                  1222        */
                -0.574798        ,               /*                  1223        */
                -0.577307        ,               /*                  1224        */
                -0.579811        ,               /*                  1225        */
                -0.582309        ,               /*                  1226        */
                -0.584801        ,               /*                  1227        */
                -0.587288        ,               /*                  1228        */
                 -0.58977        ,               /*                  1229        */
                -0.592246        ,               /*                  1230        */
                -0.594717        ,               /*                  1231        */
                -0.597181        ,               /*                  1232        */
                -0.599641        ,               /*                  1233        */
                -0.602094        ,               /*                  1234        */
                -0.604542        ,               /*                  1235        */
                -0.606984        ,               /*                  1236        */
                -0.609421        ,               /*                  1237        */
                -0.611851        ,               /*                  1238        */
                -0.614276        ,               /*                  1239        */
                -0.616696        ,               /*                  1240        */
                -0.619109        ,               /*                  1241        */
                -0.621517        ,               /*                  1242        */
                -0.623918        ,               /*                  1243        */
                -0.626314        ,               /*                  1244        */
                -0.628704        ,               /*                  1245        */
                -0.631088        ,               /*                  1246        */
                -0.633466        ,               /*                  1247        */
                -0.635838        ,               /*                  1248        */
                -0.638204        ,               /*                  1249        */
                -0.640564        ,               /*                  1250        */
                -0.642918        ,               /*                  1251        */
                -0.645266        ,               /*                  1252        */
                -0.647608        ,               /*                  1253        */
                -0.649944        ,               /*                  1254        */
                -0.652274        ,               /*                  1255        */
                -0.654597        ,               /*                  1256        */
                -0.656914        ,               /*                  1257        */
                -0.659226        ,               /*                  1258        */
                -0.661531        ,               /*                  1259        */
                -0.663829        ,               /*                  1260        */
                -0.666122        ,               /*                  1261        */
                -0.668408        ,               /*                  1262        */
                -0.670688        ,               /*                  1263        */
                -0.672961        ,               /*                  1264        */
                -0.675229        ,               /*                  1265        */
                 -0.67749        ,               /*                  1266        */
                -0.679744        ,               /*                  1267        */
                -0.681992        ,               /*                  1268        */
                -0.684234        ,               /*                  1269        */
                -0.686469        ,               /*                  1270        */
                -0.688698        ,               /*                  1271        */
                 -0.69092        ,               /*                  1272        */
                -0.693136        ,               /*                  1273        */
                -0.695345        ,               /*                  1274        */
                -0.697548        ,               /*                  1275        */
                -0.699744        ,               /*                  1276        */
                -0.701933        ,               /*                  1277        */
                -0.704116        ,               /*                  1278        */
                -0.706292        ,               /*                  1279        */
                -0.708462        ,               /*                  1280        */
                -0.710625        ,               /*                  1281        */
                -0.712781        ,               /*                  1282        */
                -0.714931        ,               /*                  1283        */
                -0.717073        ,               /*                  1284        */
                -0.719209        ,               /*                  1285        */
                -0.721339        ,               /*                  1286        */
                -0.723461        ,               /*                  1287        */
                -0.725577        ,               /*                  1288        */
                -0.727686        ,               /*                  1289        */
                -0.729788        ,               /*                  1290        */
                -0.731883        ,               /*                  1291        */
                -0.733971        ,               /*                  1292        */
                -0.736052        ,               /*                  1293        */
                -0.738126        ,               /*                  1294        */
                -0.740194        ,               /*                  1295        */
                -0.742254        ,               /*                  1296        */
                -0.744308        ,               /*                  1297        */
                -0.746354        ,               /*                  1298        */
                -0.748393        ,               /*                  1299        */
                -0.750426        ,               /*                  1300        */
                -0.752451        ,               /*                  1301        */
                -0.754469        ,               /*                  1302        */
                 -0.75648        ,               /*                  1303        */
                -0.758484        ,               /*                  1304        */
                -0.760481        ,               /*                  1305        */
                 -0.76247        ,               /*                  1306        */
                -0.764453        ,               /*                  1307        */
                -0.766428        ,               /*                  1308        */
                -0.768396        ,               /*                  1309        */
                -0.770357        ,               /*                  1310        */
                 -0.77231        ,               /*                  1311        */
                -0.774256        ,               /*                  1312        */
                -0.776195        ,               /*                  1313        */
                -0.778127        ,               /*                  1314        */
                -0.780051        ,               /*                  1315        */
                -0.781968        ,               /*                  1316        */
                -0.783878        ,               /*                  1317        */
                 -0.78578        ,               /*                  1318        */
                -0.787675        ,               /*                  1319        */
                -0.789562        ,               /*                  1320        */
                -0.791442        ,               /*                  1321        */
                -0.793314        ,               /*                  1322        */
                -0.795179        ,               /*                  1323        */
                -0.797037        ,               /*                  1324        */
                -0.798887        ,               /*                  1325        */
                -0.800729        ,               /*                  1326        */
                -0.802564        ,               /*                  1327        */
                -0.804392        ,               /*                  1328        */
                -0.806211        ,               /*                  1329        */
                -0.808024        ,               /*                  1330        */
                -0.809828        ,               /*                  1331        */
                -0.811625        ,               /*                  1332        */
                -0.813414        ,               /*                  1333        */
                -0.815196        ,               /*                  1334        */
                 -0.81697        ,               /*                  1335        */
                -0.818736        ,               /*                  1336        */
                -0.820495        ,               /*                  1337        */
                -0.822245        ,               /*                  1338        */
                -0.823989        ,               /*                  1339        */
                -0.825724        ,               /*                  1340        */
                -0.827451        ,               /*                  1341        */
                -0.829171        ,               /*                  1342        */
                -0.830883        ,               /*                  1343        */
                -0.832587        ,               /*                  1344        */
                -0.834283        ,               /*                  1345        */
                -0.835972        ,               /*                  1346        */
                -0.837652        ,               /*                  1347        */
                -0.839325        ,               /*                  1348        */
                -0.840989        ,               /*                  1349        */
                -0.842646        ,               /*                  1350        */
                -0.844295        ,               /*                  1351        */
                -0.845936        ,               /*                  1352        */
                -0.847569        ,               /*                  1353        */
                -0.849194        ,               /*                  1354        */
                -0.850811        ,               /*                  1355        */
                 -0.85242        ,               /*                  1356        */
                 -0.85402        ,               /*                  1357        */
                -0.855613        ,               /*                  1358        */
                -0.857198        ,               /*                  1359        */
                -0.858775        ,               /*                  1360        */
                -0.860343        ,               /*                  1361        */
                -0.861904        ,               /*                  1362        */
                -0.863456        ,               /*                  1363        */
                   -0.865        ,               /*                  1364        */
                -0.866537        ,               /*                  1365        */
                -0.868064        ,               /*                  1366        */
                -0.869584        ,               /*                  1367        */
                -0.871096        ,               /*                  1368        */
                -0.872599        ,               /*                  1369        */
                -0.874094        ,               /*                  1370        */
                -0.875581        ,               /*                  1371        */
                 -0.87706        ,               /*                  1372        */
                 -0.87853        ,               /*                  1373        */
                -0.879992        ,               /*                  1374        */
                -0.881446        ,               /*                  1375        */
                -0.882892        ,               /*                  1376        */
                -0.884329        ,               /*                  1377        */
                -0.885758        ,               /*                  1378        */
                -0.887178        ,               /*                  1379        */
                 -0.88859        ,               /*                  1380        */
                -0.889994        ,               /*                  1381        */
                -0.891389        ,               /*                  1382        */
                -0.892776        ,               /*                  1383        */
                -0.894155        ,               /*                  1384        */
                -0.895525        ,               /*                  1385        */
                -0.896887        ,               /*                  1386        */
                 -0.89824        ,               /*                  1387        */
                -0.899585        ,               /*                  1388        */
                -0.900921        ,               /*                  1389        */
                -0.902249        ,               /*                  1390        */
                -0.903568        ,               /*                  1391        */
                -0.904879        ,               /*                  1392        */
                -0.906182        ,               /*                  1393        */
                -0.907475        ,               /*                  1394        */
                -0.908761        ,               /*                  1395        */
                -0.910037        ,               /*                  1396        */
                -0.911305        ,               /*                  1397        */
                -0.912565        ,               /*                  1398        */
                -0.913816        ,               /*                  1399        */
                -0.915058        ,               /*                  1400        */
                -0.916292        ,               /*                  1401        */
                -0.917517        ,               /*                  1402        */
                -0.918733        ,               /*                  1403        */
                -0.919941        ,               /*                  1404        */
                 -0.92114        ,               /*                  1405        */
                 -0.92233        ,               /*                  1406        */
                -0.923512        ,               /*                  1407        */
                -0.924685        ,               /*                  1408        */
                -0.925849        ,               /*                  1409        */
                -0.927005        ,               /*                  1410        */
                -0.928152        ,               /*                  1411        */
                 -0.92929        ,               /*                  1412        */
                -0.930419        ,               /*                  1413        */
                 -0.93154        ,               /*                  1414        */
                -0.932651        ,               /*                  1415        */
                -0.933754        ,               /*                  1416        */
                -0.934849        ,               /*                  1417        */
                -0.935934        ,               /*                  1418        */
                -0.937011        ,               /*                  1419        */
                -0.938078        ,               /*                  1420        */
                -0.939137        ,               /*                  1421        */
                -0.940187        ,               /*                  1422        */
                -0.941229        ,               /*                  1423        */
                -0.942261        ,               /*                  1424        */
                -0.943284        ,               /*                  1425        */
                -0.944299        ,               /*                  1426        */
                -0.945305        ,               /*                  1427        */
                -0.946301        ,               /*                  1428        */
                -0.947289        ,               /*                  1429        */
                -0.948268        ,               /*                  1430        */
                -0.949238        ,               /*                  1431        */
                -0.950199        ,               /*                  1432        */
                -0.951151        ,               /*                  1433        */
                -0.952094        ,               /*                  1434        */
                -0.953029        ,               /*                  1435        */
                -0.953954        ,               /*                  1436        */
                 -0.95487        ,               /*                  1437        */
                -0.955777        ,               /*                  1438        */
                -0.956675        ,               /*                  1439        */
                -0.957565        ,               /*                  1440        */
                -0.958445        ,               /*                  1441        */
                -0.959316        ,               /*                  1442        */
                -0.960178        ,               /*                  1443        */
                -0.961031        ,               /*                  1444        */
                -0.961875        ,               /*                  1445        */
                 -0.96271        ,               /*                  1446        */
                -0.963536        ,               /*                  1447        */
                -0.964353        ,               /*                  1448        */
                 -0.96516        ,               /*                  1449        */
                -0.965959        ,               /*                  1450        */
                -0.966748        ,               /*                  1451        */
                -0.967529        ,               /*                  1452        */
                  -0.9683        ,               /*                  1453        */
                -0.969062        ,               /*                  1454        */
                -0.969815        ,               /*                  1455        */
                -0.970559        ,               /*                  1456        */
                -0.971294        ,               /*                  1457        */
                 -0.97202        ,               /*                  1458        */
                -0.972736        ,               /*                  1459        */
                -0.973443        ,               /*                  1460        */
                -0.974141        ,               /*                  1461        */
                 -0.97483        ,               /*                  1462        */
                 -0.97551        ,               /*                  1463        */
                -0.976181        ,               /*                  1464        */
                -0.976842        ,               /*                  1465        */
                -0.977494        ,               /*                  1466        */
                -0.978137        ,               /*                  1467        */
                -0.978771        ,               /*                  1468        */
                -0.979395        ,               /*                  1469        */
                 -0.98001        ,               /*                  1470        */
                -0.980616        ,               /*                  1471        */
                -0.981213        ,               /*                  1472        */
                -0.981801        ,               /*                  1473        */
                -0.982379        ,               /*                  1474        */
                -0.982948        ,               /*                  1475        */
                -0.983508        ,               /*                  1476        */
                -0.984059        ,               /*                  1477        */
                  -0.9846        ,               /*                  1478        */
                -0.985132        ,               /*                  1479        */
                -0.985654        ,               /*                  1480        */
                -0.986168        ,               /*                  1481        */
                -0.986672        ,               /*                  1482        */
                -0.987167        ,               /*                  1483        */
                -0.987652        ,               /*                  1484        */
                -0.988129        ,               /*                  1485        */
                -0.988595        ,               /*                  1486        */
                -0.989053        ,               /*                  1487        */
                -0.989501        ,               /*                  1488        */
                 -0.98994        ,               /*                  1489        */
                 -0.99037        ,               /*                  1490        */
                 -0.99079        ,               /*                  1491        */
                -0.991201        ,               /*                  1492        */
                -0.991603        ,               /*                  1493        */
                -0.991995        ,               /*                  1494        */
                -0.992378        ,               /*                  1495        */
                -0.992752        ,               /*                  1496        */
                -0.993116        ,               /*                  1497        */
                -0.993471        ,               /*                  1498        */
                -0.993816        ,               /*                  1499        */
                -0.994152        ,               /*                  1500        */
                -0.994479        ,               /*                  1501        */
                -0.994796        ,               /*                  1502        */
                -0.995104        ,               /*                  1503        */
                -0.995403        ,               /*                  1504        */
                -0.995692        ,               /*                  1505        */
                -0.995972        ,               /*                  1506        */
                -0.996243        ,               /*                  1507        */
                -0.996504        ,               /*                  1508        */
                -0.996756        ,               /*                  1509        */
                -0.996998        ,               /*                  1510        */
                -0.997231        ,               /*                  1511        */
                -0.997455        ,               /*                  1512        */
                -0.997669        ,               /*                  1513        */
                -0.997874        ,               /*                  1514        */
                -0.998069        ,               /*                  1515        */
                -0.998255        ,               /*                  1516        */
                -0.998431        ,               /*                  1517        */
                -0.998599        ,               /*                  1518        */
                -0.998756        ,               /*                  1519        */
                -0.998905        ,               /*                  1520        */
                -0.999044        ,               /*                  1521        */
                -0.999173        ,               /*                  1522        */
                -0.999293        ,               /*                  1523        */
                -0.999404        ,               /*                  1524        */
                -0.999505        ,               /*                  1525        */
                -0.999597        ,               /*                  1526        */
                -0.999679        ,               /*                  1527        */
                -0.999752        ,               /*                  1528        */
                -0.999816        ,               /*                  1529        */
                 -0.99987        ,               /*                  1530        */
                -0.999915        ,               /*                  1531        */
                 -0.99995        ,               /*                  1532        */
                -0.999976        ,               /*                  1533        */
                -0.999993        ,               /*                  1534        */
                       -1        ,               /*                  1535        */
                -0.999997        ,               /*                  1536        */
                -0.999986        ,               /*                  1537        */
                -0.999964        ,               /*                  1538        */
                -0.999934        ,               /*                  1539        */
                -0.999894        ,               /*                  1540        */
                -0.999844        ,               /*                  1541        */
                -0.999785        ,               /*                  1542        */
                -0.999717        ,               /*                  1543        */
                -0.999639        ,               /*                  1544        */
                -0.999552        ,               /*                  1545        */
                -0.999456        ,               /*                  1546        */
                 -0.99935        ,               /*                  1547        */
                -0.999234        ,               /*                  1548        */
                -0.999109        ,               /*                  1549        */
                -0.998975        ,               /*                  1550        */
                -0.998832        ,               /*                  1551        */
                -0.998679        ,               /*                  1552        */
                -0.998516        ,               /*                  1553        */
                -0.998344        ,               /*                  1554        */
                -0.998163        ,               /*                  1555        */
                -0.997972        ,               /*                  1556        */
                -0.997772        ,               /*                  1557        */
                -0.997563        ,               /*                  1558        */
                -0.997344        ,               /*                  1559        */
                -0.997116        ,               /*                  1560        */
                -0.996878        ,               /*                  1561        */
                -0.996631        ,               /*                  1562        */
                -0.996375        ,               /*                  1563        */
                -0.996109        ,               /*                  1564        */
                -0.995834        ,               /*                  1565        */
                -0.995549        ,               /*                  1566        */
                -0.995255        ,               /*                  1567        */
                -0.994952        ,               /*                  1568        */
                -0.994639        ,               /*                  1569        */
                -0.994317        ,               /*                  1570        */
                -0.993985        ,               /*                  1571        */
                -0.993645        ,               /*                  1572        */
                -0.993294        ,               /*                  1573        */
                -0.992935        ,               /*                  1574        */
                -0.992566        ,               /*                  1575        */
                -0.992188        ,               /*                  1576        */
                  -0.9918        ,               /*                  1577        */
                -0.991403        ,               /*                  1578        */
                -0.990997        ,               /*                  1579        */
                -0.990581        ,               /*                  1580        */
                -0.990156        ,               /*                  1581        */
                -0.989722        ,               /*                  1582        */
                -0.989278        ,               /*                  1583        */
                -0.988825        ,               /*                  1584        */
                -0.988363        ,               /*                  1585        */
                -0.987892        ,               /*                  1586        */
                -0.987411        ,               /*                  1587        */
                -0.986921        ,               /*                  1588        */
                -0.986421        ,               /*                  1589        */
                -0.985912        ,               /*                  1590        */
                -0.985394        ,               /*                  1591        */
                -0.984867        ,               /*                  1592        */
                 -0.98433        ,               /*                  1593        */
                -0.983784        ,               /*                  1594        */
                -0.983229        ,               /*                  1595        */
                -0.982665        ,               /*                  1596        */
                -0.982091        ,               /*                  1597        */
                -0.981508        ,               /*                  1598        */
                -0.980916        ,               /*                  1599        */
                -0.980315        ,               /*                  1600        */
                -0.979704        ,               /*                  1601        */
                -0.979084        ,               /*                  1602        */
                -0.978455        ,               /*                  1603        */
                -0.977817        ,               /*                  1604        */
                -0.977169        ,               /*                  1605        */
                -0.976512        ,               /*                  1606        */
                -0.975846        ,               /*                  1607        */
                -0.975171        ,               /*                  1608        */
                -0.974487        ,               /*                  1609        */
                -0.973793        ,               /*                  1610        */
                -0.973091        ,               /*                  1611        */
                -0.972379        ,               /*                  1612        */
                -0.971658        ,               /*                  1613        */
                -0.970928        ,               /*                  1614        */
                -0.970188        ,               /*                  1615        */
                 -0.96944        ,               /*                  1616        */
                -0.968682        ,               /*                  1617        */
                -0.967916        ,               /*                  1618        */
                 -0.96714        ,               /*                  1619        */
                -0.966355        ,               /*                  1620        */
                -0.965561        ,               /*                  1621        */
                -0.964758        ,               /*                  1622        */
                -0.963945        ,               /*                  1623        */
                -0.963124        ,               /*                  1624        */
                -0.962294        ,               /*                  1625        */
                -0.961454        ,               /*                  1626        */
                -0.960606        ,               /*                  1627        */
                -0.959748        ,               /*                  1628        */
                -0.958881        ,               /*                  1629        */
                -0.958006        ,               /*                  1630        */
                -0.957121        ,               /*                  1631        */
                -0.956227        ,               /*                  1632        */
                -0.955325        ,               /*                  1633        */
                -0.954413        ,               /*                  1634        */
                -0.953492        ,               /*                  1635        */
                -0.952563        ,               /*                  1636        */
                -0.951624        ,               /*                  1637        */
                -0.950676        ,               /*                  1638        */
                 -0.94972        ,               /*                  1639        */
                -0.948754        ,               /*                  1640        */
                 -0.94778        ,               /*                  1641        */
                -0.946796        ,               /*                  1642        */
                -0.945804        ,               /*                  1643        */
                -0.944803        ,               /*                  1644        */
                -0.943793        ,               /*                  1645        */
                -0.942774        ,               /*                  1646        */
                -0.941746        ,               /*                  1647        */
                -0.940709        ,               /*                  1648        */
                -0.939663        ,               /*                  1649        */
                -0.938609        ,               /*                  1650        */
                -0.937546        ,               /*                  1651        */
                -0.936473        ,               /*                  1652        */
                -0.935392        ,               /*                  1653        */
                -0.934303        ,               /*                  1654        */
                -0.933204        ,               /*                  1655        */
                -0.932097        ,               /*                  1656        */
                -0.930981        ,               /*                  1657        */
                -0.929856        ,               /*                  1658        */
                -0.928722        ,               /*                  1659        */
                -0.927579        ,               /*                  1660        */
                -0.926428        ,               /*                  1661        */
                -0.925268        ,               /*                  1662        */
                  -0.9241        ,               /*                  1663        */
                -0.922922        ,               /*                  1664        */
                -0.921736        ,               /*                  1665        */
                -0.920541        ,               /*                  1666        */
                -0.919338        ,               /*                  1667        */
                -0.918126        ,               /*                  1668        */
                -0.916905        ,               /*                  1669        */
                -0.915676        ,               /*                  1670        */
                -0.914438        ,               /*                  1671        */
                -0.913191        ,               /*                  1672        */
                -0.911936        ,               /*                  1673        */
                -0.910672        ,               /*                  1674        */
                  -0.9094        ,               /*                  1675        */
                -0.908119        ,               /*                  1676        */
                 -0.90683        ,               /*                  1677        */
                -0.905532        ,               /*                  1678        */
                -0.904225        ,               /*                  1679        */
                 -0.90291        ,               /*                  1680        */
                -0.901586        ,               /*                  1681        */
                -0.900254        ,               /*                  1682        */
                -0.898914        ,               /*                  1683        */
                -0.897565        ,               /*                  1684        */
                -0.896207        ,               /*                  1685        */
                -0.894841        ,               /*                  1686        */
                -0.893467        ,               /*                  1687        */
                -0.892084        ,               /*                  1688        */
                -0.890693        ,               /*                  1689        */
                -0.889293        ,               /*                  1690        */
                -0.887885        ,               /*                  1691        */
                -0.886469        ,               /*                  1692        */
                -0.885044        ,               /*                  1693        */
                -0.883611        ,               /*                  1694        */
                 -0.88217        ,               /*                  1695        */
                 -0.88072        ,               /*                  1696        */
                -0.879262        ,               /*                  1697        */
                -0.877796        ,               /*                  1698        */
                -0.876321        ,               /*                  1699        */
                -0.874839        ,               /*                  1700        */
                -0.873348        ,               /*                  1701        */
                -0.871848        ,               /*                  1702        */
                -0.870341        ,               /*                  1703        */
                -0.868825        ,               /*                  1704        */
                -0.867302        ,               /*                  1705        */
                 -0.86577        ,               /*                  1706        */
                -0.864229        ,               /*                  1707        */
                -0.862681        ,               /*                  1708        */
                -0.861125        ,               /*                  1709        */
                 -0.85956        ,               /*                  1710        */
                -0.857987        ,               /*                  1711        */
                -0.856407        ,               /*                  1712        */
                -0.854818        ,               /*                  1713        */
                -0.853221        ,               /*                  1714        */
                -0.851616        ,               /*                  1715        */
                -0.850003        ,               /*                  1716        */
                -0.848382        ,               /*                  1717        */
                -0.846753        ,               /*                  1718        */
                -0.845116        ,               /*                  1719        */
                -0.843472        ,               /*                  1720        */
                -0.841819        ,               /*                  1721        */
                -0.840158        ,               /*                  1722        */
                -0.838489        ,               /*                  1723        */
                -0.836813        ,               /*                  1724        */
                -0.835128        ,               /*                  1725        */
                -0.833436        ,               /*                  1726        */
                -0.831736        ,               /*                  1727        */
                -0.830028        ,               /*                  1728        */
                -0.828312        ,               /*                  1729        */
                -0.826589        ,               /*                  1730        */
                -0.824857        ,               /*                  1731        */
                -0.823118        ,               /*                  1732        */
                -0.821371        ,               /*                  1733        */
                -0.819616        ,               /*                  1734        */
                -0.817854        ,               /*                  1735        */
                -0.816084        ,               /*                  1736        */
                -0.814306        ,               /*                  1737        */
                -0.812521        ,               /*                  1738        */
                -0.810728        ,               /*                  1739        */
                -0.808927        ,               /*                  1740        */
                -0.807118        ,               /*                  1741        */
                -0.805302        ,               /*                  1742        */
                -0.803479        ,               /*                  1743        */
                -0.801648        ,               /*                  1744        */
                -0.799809        ,               /*                  1745        */
                -0.797963        ,               /*                  1746        */
                -0.796109        ,               /*                  1747        */
                -0.794248        ,               /*                  1748        */
                -0.792379        ,               /*                  1749        */
                -0.790503        ,               /*                  1750        */
                -0.788619        ,               /*                  1751        */
                -0.786728        ,               /*                  1752        */
                 -0.78483        ,               /*                  1753        */
                -0.782924        ,               /*                  1754        */
                -0.781011        ,               /*                  1755        */
                 -0.77909        ,               /*                  1756        */
                -0.777162        ,               /*                  1757        */
                -0.775227        ,               /*                  1758        */
                -0.773284        ,               /*                  1759        */
                -0.771334        ,               /*                  1760        */
                -0.769377        ,               /*                  1761        */
                -0.767413        ,               /*                  1762        */
                -0.765441        ,               /*                  1763        */
                -0.763462        ,               /*                  1764        */
                -0.761476        ,               /*                  1765        */
                -0.759483        ,               /*                  1766        */
                -0.757483        ,               /*                  1767        */
                -0.755475        ,               /*                  1768        */
                -0.753461        ,               /*                  1769        */
                -0.751439        ,               /*                  1770        */
                 -0.74941        ,               /*                  1771        */
                -0.747375        ,               /*                  1772        */
                -0.745332        ,               /*                  1773        */
                -0.743282        ,               /*                  1774        */
                -0.741225        ,               /*                  1775        */
                -0.739161        ,               /*                  1776        */
                 -0.73709        ,               /*                  1777        */
                -0.735012        ,               /*                  1778        */
                -0.732928        ,               /*                  1779        */
                -0.730836        ,               /*                  1780        */
                -0.728737        ,               /*                  1781        */
                -0.726632        ,               /*                  1782        */
                 -0.72452        ,               /*                  1783        */
                -0.722401        ,               /*                  1784        */
                -0.720275        ,               /*                  1785        */
                -0.718142        ,               /*                  1786        */
                -0.716003        ,               /*                  1787        */
                -0.713857        ,               /*                  1788        */
                -0.711704        ,               /*                  1789        */
                -0.709544        ,               /*                  1790        */
                -0.707378        ,               /*                  1791        */
                -0.705205        ,               /*                  1792        */
                -0.703026        ,               /*                  1793        */
                -0.700839        ,               /*                  1794        */
                -0.698647        ,               /*                  1795        */
                -0.696447        ,               /*                  1796        */
                -0.694241        ,               /*                  1797        */
                -0.692029        ,               /*                  1798        */
                 -0.68981        ,               /*                  1799        */
                -0.687584        ,               /*                  1800        */
                -0.685352        ,               /*                  1801        */
                -0.683114        ,               /*                  1802        */
                -0.680869        ,               /*                  1803        */
                -0.678618        ,               /*                  1804        */
                 -0.67636        ,               /*                  1805        */
                -0.674096        ,               /*                  1806        */
                -0.671825        ,               /*                  1807        */
                -0.669549        ,               /*                  1808        */
                -0.667266        ,               /*                  1809        */
                -0.664976        ,               /*                  1810        */
                -0.662681        ,               /*                  1811        */
                -0.660379        ,               /*                  1812        */
                -0.658071        ,               /*                  1813        */
                -0.655757        ,               /*                  1814        */
                -0.653436        ,               /*                  1815        */
                -0.651109        ,               /*                  1816        */
                -0.648777        ,               /*                  1817        */
                -0.646438        ,               /*                  1818        */
                -0.644093        ,               /*                  1819        */
                -0.641742        ,               /*                  1820        */
                -0.639385        ,               /*                  1821        */
                -0.637022        ,               /*                  1822        */
                -0.634653        ,               /*                  1823        */
                -0.632278        ,               /*                  1824        */
                -0.629897        ,               /*                  1825        */
                 -0.62751        ,               /*                  1826        */
                -0.625117        ,               /*                  1827        */
                -0.622718        ,               /*                  1828        */
                -0.620314        ,               /*                  1829        */
                -0.617903        ,               /*                  1830        */
                -0.615487        ,               /*                  1831        */
                -0.613065        ,               /*                  1832        */
                -0.610637        ,               /*                  1833        */
                -0.608203        ,               /*                  1834        */
                -0.605764        ,               /*                  1835        */
                -0.603319        ,               /*                  1836        */
                -0.600868        ,               /*                  1837        */
                -0.598412        ,               /*                  1838        */
                 -0.59595        ,               /*                  1839        */
                -0.593482        ,               /*                  1840        */
                -0.591009        ,               /*                  1841        */
                 -0.58853        ,               /*                  1842        */
                -0.586046        ,               /*                  1843        */
                -0.583556        ,               /*                  1844        */
                 -0.58106        ,               /*                  1845        */
                 -0.57856        ,               /*                  1846        */
                -0.576053        ,               /*                  1847        */
                -0.573542        ,               /*                  1848        */
                -0.571024        ,               /*                  1849        */
                -0.568502        ,               /*                  1850        */
                -0.565974        ,               /*                  1851        */
                -0.563441        ,               /*                  1852        */
                -0.560902        ,               /*                  1853        */
                -0.558359        ,               /*                  1854        */
                -0.555809        ,               /*                  1855        */
                -0.553255        ,               /*                  1856        */
                -0.550696        ,               /*                  1857        */
                -0.548131        ,               /*                  1858        */
                -0.545561        ,               /*                  1859        */
                -0.542986        ,               /*                  1860        */
                -0.540406        ,               /*                  1861        */
                -0.537821        ,               /*                  1862        */
                -0.535231        ,               /*                  1863        */
                -0.532635        ,               /*                  1864        */
                -0.530035        ,               /*                  1865        */
                 -0.52743        ,               /*                  1866        */
                -0.524819        ,               /*                  1867        */
                -0.522204        ,               /*                  1868        */
                -0.519584        ,               /*                  1869        */
                -0.516959        ,               /*                  1870        */
                -0.514329        ,               /*                  1871        */
                -0.511694        ,               /*                  1872        */
                -0.509055        ,               /*                  1873        */
                 -0.50641        ,               /*                  1874        */
                -0.503761        ,               /*                  1875        */
                -0.501107        ,               /*                  1876        */
                -0.498449        ,               /*                  1877        */
                -0.495785        ,               /*                  1878        */
                -0.493117        ,               /*                  1879        */
                -0.490445        ,               /*                  1880        */
                -0.487767        ,               /*                  1881        */
                -0.485086        ,               /*                  1882        */
                -0.482399        ,               /*                  1883        */
                -0.479708        ,               /*                  1884        */
                -0.477013        ,               /*                  1885        */
                -0.474313        ,               /*                  1886        */
                -0.471608        ,               /*                  1887        */
                -0.468899        ,               /*                  1888        */
                -0.466186        ,               /*                  1889        */
                -0.463468        ,               /*                  1890        */
                -0.460746        ,               /*                  1891        */
                 -0.45802        ,               /*                  1892        */
                -0.455289        ,               /*                  1893        */
                -0.452554        ,               /*                  1894        */
                -0.449815        ,               /*                  1895        */
                -0.447071        ,               /*                  1896        */
                -0.444324        ,               /*                  1897        */
                -0.441572        ,               /*                  1898        */
                -0.438816        ,               /*                  1899        */
                -0.436055        ,               /*                  1900        */
                -0.433291        ,               /*                  1901        */
                -0.430523        ,               /*                  1902        */
                 -0.42775        ,               /*                  1903        */
                -0.424974        ,               /*                  1904        */
                -0.422193        ,               /*                  1905        */
                -0.419409        ,               /*                  1906        */
                 -0.41662        ,               /*                  1907        */
                -0.413828        ,               /*                  1908        */
                -0.411032        ,               /*                  1909        */
                -0.408232        ,               /*                  1910        */
                -0.405428        ,               /*                  1911        */
                 -0.40262        ,               /*                  1912        */
                -0.399808        ,               /*                  1913        */
                -0.396993        ,               /*                  1914        */
                -0.394174        ,               /*                  1915        */
                -0.391351        ,               /*                  1916        */
                -0.388525        ,               /*                  1917        */
                -0.385694        ,               /*                  1918        */
                -0.382861        ,               /*                  1919        */
                -0.380023        ,               /*                  1920        */
                -0.377182        ,               /*                  1921        */
                -0.374338        ,               /*                  1922        */
                 -0.37149        ,               /*                  1923        */
                -0.368638        ,               /*                  1924        */
                -0.365783        ,               /*                  1925        */
                -0.362925        ,               /*                  1926        */
                -0.360063        ,               /*                  1927        */
                -0.357198        ,               /*                  1928        */
                -0.354329        ,               /*                  1929        */
                -0.351457        ,               /*                  1930        */
                -0.348582        ,               /*                  1931        */
                -0.345703        ,               /*                  1932        */
                -0.342821        ,               /*                  1933        */
                -0.339936        ,               /*                  1934        */
                -0.337048        ,               /*                  1935        */
                -0.334156        ,               /*                  1936        */
                -0.331262        ,               /*                  1937        */
                -0.328364        ,               /*                  1938        */
                -0.325463        ,               /*                  1939        */
                -0.322559        ,               /*                  1940        */
                -0.319653        ,               /*                  1941        */
                -0.316743        ,               /*                  1942        */
                 -0.31383        ,               /*                  1943        */
                -0.310914        ,               /*                  1944        */
                -0.307995        ,               /*                  1945        */
                -0.305073        ,               /*                  1946        */
                -0.302149        ,               /*                  1947        */
                -0.299221        ,               /*                  1948        */
                -0.296291        ,               /*                  1949        */
                -0.293358        ,               /*                  1950        */
                -0.290422        ,               /*                  1951        */
                -0.287484        ,               /*                  1952        */
                -0.284543        ,               /*                  1953        */
                -0.281599        ,               /*                  1954        */
                -0.278652        ,               /*                  1955        */
                -0.275703        ,               /*                  1956        */
                -0.272751        ,               /*                  1957        */
                -0.269797        ,               /*                  1958        */
                 -0.26684        ,               /*                  1959        */
                 -0.26388        ,               /*                  1960        */
                -0.260919        ,               /*                  1961        */
                -0.257954        ,               /*                  1962        */
                -0.254987        ,               /*                  1963        */
                -0.252018        ,               /*                  1964        */
                -0.249047        ,               /*                  1965        */
                -0.246073        ,               /*                  1966        */
                -0.243096        ,               /*                  1967        */
                -0.240118        ,               /*                  1968        */
                -0.237137        ,               /*                  1969        */
                -0.234154        ,               /*                  1970        */
                -0.231169        ,               /*                  1971        */
                -0.228182        ,               /*                  1972        */
                -0.225192        ,               /*                  1973        */
                  -0.2222        ,               /*                  1974        */
                -0.219207        ,               /*                  1975        */
                -0.216211        ,               /*                  1976        */
                -0.213213        ,               /*                  1977        */
                -0.210213        ,               /*                  1978        */
                -0.207211        ,               /*                  1979        */
                -0.204207        ,               /*                  1980        */
                -0.201202        ,               /*                  1981        */
                -0.198194        ,               /*                  1982        */
                -0.195184        ,               /*                  1983        */
                -0.192173        ,               /*                  1984        */
                 -0.18916        ,               /*                  1985        */
                -0.186145        ,               /*                  1986        */
                -0.183128        ,               /*                  1987        */
                 -0.18011        ,               /*                  1988        */
                 -0.17709        ,               /*                  1989        */
                -0.174068        ,               /*                  1990        */
                -0.171045        ,               /*                  1991        */
                 -0.16802        ,               /*                  1992        */
                -0.164993        ,               /*                  1993        */
                -0.161965        ,               /*                  1994        */
                -0.158935        ,               /*                  1995        */
                -0.155904        ,               /*                  1996        */
                -0.152871        ,               /*                  1997        */
                -0.149837        ,               /*                  1998        */
                -0.146802        ,               /*                  1999        */
                -0.143765        ,               /*                  2000        */
                -0.140726        ,               /*                  2001        */
                -0.137687        ,               /*                  2002        */
                -0.134646        ,               /*                  2003        */
                -0.131604        ,               /*                  2004        */
                -0.128561        ,               /*                  2005        */
                -0.125516        ,               /*                  2006        */
                 -0.12247        ,               /*                  2007        */
                -0.119423        ,               /*                  2008        */
                -0.116375        ,               /*                  2009        */
                -0.113326        ,               /*                  2010        */
                -0.110276        ,               /*                  2011        */
                -0.107225        ,               /*                  2012        */
                -0.104172        ,               /*                  2013        */
                -0.101119        ,               /*                  2014        */
                -0.098065        ,               /*                  2015        */
                 -0.09501        ,               /*                  2016        */
                -0.091954        ,               /*                  2017        */
                -0.088897        ,               /*                  2018        */
                -0.085839        ,               /*                  2019        */
                -0.082781        ,               /*                  2020        */
                -0.079721        ,               /*                  2021        */
                -0.076661        ,               /*                  2022        */
                  -0.0736        ,               /*                  2023        */
                -0.070539        ,               /*                  2024        */
                -0.067477        ,               /*                  2025        */
                -0.064414        ,               /*                  2026        */
                -0.061351        ,               /*                  2027        */
                -0.058287        ,               /*                  2028        */
                -0.055222        ,               /*                  2029        */
                -0.052157        ,               /*                  2030        */
                -0.049092        ,               /*                  2031        */
                -0.046026        ,               /*                  2032        */
                -0.042959        ,               /*                  2033        */
                -0.039892        ,               /*                  2034        */
                -0.036825        ,               /*                  2035        */
                -0.033758        ,               /*                  2036        */
                 -0.03069        ,               /*                  2037        */
                -0.027622        ,               /*                  2038        */
                -0.024553        ,               /*                  2039        */
                -0.021485        ,               /*                  2040        */
                -0.018416        ,               /*                  2041        */
                -0.015347        ,               /*                  2042        */
                -0.012278        ,               /*                  2043        */
                -0.009208        ,               /*                  2044        */
                -0.006139        ,               /*                  2045        */
                -0.003069        ,               /*                  2046        */
                -0.000001                        /*                  2047        */
};
#endif


//
// End of File
//
