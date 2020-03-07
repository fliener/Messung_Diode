#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/rom_map.h"
#include "utils/locator.h"
#include "utils/lwiplib.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "httpserver_raw/httpd.h"
#include "drivers/pinout.h"
#include "io.h"

//*****************************************************************************
#include <driverlib/pwm.h>
#include <driverlib/pwm.c>
#include <driverlib/adc.c>
#include <driverlib/adc.h>
#include <driverlib/pin_map.h>

#define TASKSTACKSIZE   2048
int Arr_Strom[25];
float Arr_Spannung[25];
float Voltage;
int Current;
uint32_t ulTempValueC;
uint32_t ulTempValueF;
uint32_t adcGetValues;
uint32_t ulADC0Value[8];
uint32_t ON=0;
uint32_t OFF=250;
uint32_t ui32Loop;
uint32_t ui32Lupe;
uint32_t i;
uint32_t volatile help;
uint32_t volatile hilfe;
uint32_t end = 101;
double ulTempAvg;

void Funktion_ADC(void);


void ADC0IntHandler(void)
{
    // Clear interrupt Flag
    ADCIntClear(ADC0_BASE, 0);

    ADCSequenceDataGet(ADC0_BASE, 0, ulADC0Value);

    adcGetValues=1;
}
//*****************************************************************************


double A_Aray[]={3.1,32,0.4, 21, 11, 2.2, 3.089, 0.00021};

// Defines for setting up the system clock.
#define SYSTICKHZ               100
#define SYSTICKMS               (1000 / SYSTICKHZ)

#define SYSTICK_INT_PRIORITY    0x80// Interrupt priority definitions.  The top 3 bits of these values are
#define ETHERNET_INT_PRIORITY   0xC0// significant with lower values indicating higher priority interrupts.

extern void httpd_init(void);// External Application references.

// SSI tag indices for each entry in the g_pcSSITags array.
#define SSI_INDEX_0_Var  0
#define SSI_INDEX_1_Var  1
#define SSI_INDEX_2_Var  2
#define SSI_INDEX_3_Var  3
#define SSI_INDEX_4_Var  4
#define SSI_INDEX_5_Var  5
#define SSI_INDEX_6_Var  6
#define SSI_INDEX_7_Var  7
#define SSI_INDEX_8_Var  8
#define SSI_INDEX_9_Var  9
#define SSI_INDEX_10_Var  10
#define SSI_INDEX_11_Var  11
#define SSI_INDEX_12_Var  12
#define SSI_INDEX_13_Var  13
#define SSI_INDEX_14_Var  14
#define SSI_INDEX_15_Var  15
#define SSI_INDEX_16_Var  16
#define SSI_INDEX_17_Var  17
#define SSI_INDEX_18_Var  18
#define SSI_INDEX_19_Var  19
#define SSI_INDEX_20_Var  20
#define SSI_INDEX_21_Var  21
#define SSI_INDEX_22_Var  22
#define SSI_INDEX_23_Var  23
#define SSI_INDEX_24_Var  24
#define SSI_INDEX_Spann_0  25
#define SSI_INDEX_Spann_1  26
#define SSI_INDEX_Spann_2  27
#define SSI_INDEX_Spann_3  28
#define SSI_INDEX_Spann_4  29
#define SSI_INDEX_Spann_5  30
#define SSI_INDEX_Spann_6  31
#define SSI_INDEX_Spann_7  32
#define SSI_INDEX_Spann_8  33
#define SSI_INDEX_Spann_9  34
#define SSI_INDEX_Spann_10  35
#define SSI_INDEX_Spann_11  36
#define SSI_INDEX_Spann_12  37
#define SSI_INDEX_Spann_13  38
#define SSI_INDEX_Spann_14  39
#define SSI_INDEX_Spann_15  40
#define SSI_INDEX_Spann_16  41
#define SSI_INDEX_Spann_17  42
#define SSI_INDEX_Spann_18  43
#define SSI_INDEX_Spann_19  44
#define SSI_INDEX_Spann_20  45
#define SSI_INDEX_Spann_21  46
#define SSI_INDEX_Spann_22  47
#define SSI_INDEX_Spann_23  48
#define SSI_INDEX_Spann_24  49


// This array holds all the strings that are to be recognized as SSI tag
// names by the HTTPD server.  The server will call SSIHandler to request a
// replacement string whenever the pattern <!--#tagname--> (where tagname
// appears in the following array) is found in ".ssi", ".shtml" or ".shtm"
// files that it serves.
static const char *g_pcConfigSSITags[] =
{
    "LEDtxt",        // SSI_INDEX_0_Var
    "1_Var",         // SSI_INDEX_1_Var
    "2_Var",         // SSI_INDEX_2_Var
    "3_Var",         // SSI_INDEX_3_Var
    "4_Var",         // SSI_INDEX_4_Var
    "5_Var",         // SSI_INDEX_5_Var
    "6_Var",         // SSI_INDEX_6_Var
    "7_Var",         // SSI_INDEX_7_Var
    "8_Var",         // SSI_INDEX_8_Var
    "9_Var",         // SSI_INDEX_9_Var
    "10_Var",         // SSI_INDEX_10_Var
    "11_Var",         // SSI_INDEX_11_Var
    "12_Var",         // SSI_INDEX_12_Var
    "13_Var",         // SSI_INDEX_13_Var
    "14_Var",         // SSI_INDEX_14_Var
    "15_Var",         // SSI_INDEX_15_Var
    "16_Var",         // SSI_INDEX_16_Var
    "17_Var",         // SSI_INDEX_17_Var
    "18_Var",         // SSI_INDEX_18_Var
    "19_Var",         // SSI_INDEX_19_Var
    "20_Var",         // SSI_INDEX_20_Var
    "21_Var",         // SSI_INDEX_21_Var
    "22_Var",         // SSI_INDEX_22_Var
    "23_Var",         // SSI_INDEX_23_Var
    "24_Var",         // SSI_INDEX_24_Var
    "Spann_0",         // SSI_INDEX_Spann_0
    "Spann_1",         // SSI_INDEX_Spann_1
    "Spann_2",         // SSI_INDEX_Spann_2
    "Spann_3",         // SSI_INDEX_Spann_3
    "Spann_4",         // SSI_INDEX_Spann_4
    "Spann_5",         // SSI_INDEX_Spann_5
    "Spann_6",         // SSI_INDEX_Spann_6
    "Spann_7",         // SSI_INDEX_Spann_7
    "Spann_8",         // SSI_INDEX_Spann_8
    "Spann_9",         // SSI_INDEX_Spann_9
    "Spann_10",         // SSI_INDEX_Spann_10
    "Spann_11",         // SSI_INDEX_Spann_11
    "Spann_12",         // SSI_INDEX_Spann_12
    "Spann_13",         // SSI_INDEX_Spann_13
    "Spann_14",         // SSI_INDEX_Spann_14
    "Spann_15",         // SSI_INDEX_Spann_15
    "Spann_16",         // SSI_INDEX_Spann_16
    "Spann_17",         // SSI_INDEX_Spann_17
    "Spann_18",         // SSI_INDEX_Spann_18
    "Spann_19",         // SSI_INDEX_Spann_19
    "Spann_20",         // SSI_INDEX_Spann_20
    "Spann_21",         // SSI_INDEX_Spann_21
    "Spann_22",         // SSI_INDEX_Spann_22
    "Spann_23",         // SSI_INDEX_Spann_23
    "Spann_24",         // SSI_INDEX_Spann_24
};

// The number of individual SSI tags that the HTTPD server can expect to
// find in our configuration pages.

#define NUM_CONFIG_SSI_TAGS     (sizeof(g_pcConfigSSITags) / sizeof (char *))

// Prototype for the main handler used to process server-side-includes for the
// application's web-based configuration screens.
static int32_t SSIHandler(int32_t iIndex, char *pcInsert, int32_t iInsertLen);

// Timeout for DHCP address request (in seconds).
#ifndef DHCP_EXPIRE_TIMER_SECS
#define DHCP_EXPIRE_TIMER_SECS  45
#endif

uint32_t g_ui32IPAddress;// The current IP address.
uint32_t g_ui32SysClock;// The system clock frequency.  Used by the SD card driver.


// This function is called by the HTTP server whenever it encounters an SSI
// tag in a web page.  The iIndex parameter provides the index of the tag in
// the g_pcConfigSSITags array. This function writes the substitution text
// into the pcInsert array, writing no more than iInsertLen characters.

//*****************************************************************************
static int32_t SSIHandler(int32_t iIndex, char *pcInsert, int32_t iInsertLen)
{
    // Which SSI tag have we been passed?
    switch(iIndex)
    {
        case SSI_INDEX_0_Var:
            g_ulAnimSpeed=Arr_Strom[2];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_1_Var:
            g_ulAnimSpeed=Arr_Strom[3];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_2_Var:
        g_ulAnimSpeed=Arr_Strom[4];
        post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_3_Var:
            g_ulAnimSpeed=Arr_Strom[5];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_4_Var:
            g_ulAnimSpeed=Arr_Strom[6];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_5_Var:
            g_ulAnimSpeed=Arr_Strom[7];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_6_Var:
            g_ulAnimSpeed=Arr_Strom[8];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_7_Var:
            g_ulAnimSpeed=Arr_Strom[9];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_8_Var:
            g_ulAnimSpeed=Arr_Strom[10];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_9_Var:
            g_ulAnimSpeed=Arr_Strom[11];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_10_Var:
            g_ulAnimSpeed=Arr_Strom[12];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_11_Var:
            g_ulAnimSpeed=Arr_Strom[13];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_12_Var:
            g_ulAnimSpeed=Arr_Strom[14];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_13_Var:
            g_ulAnimSpeed=Arr_Strom[15];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_14_Var:
            g_ulAnimSpeed=Arr_Strom[16];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_15_Var:
            g_ulAnimSpeed=Arr_Strom[17];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_16_Var:
            g_ulAnimSpeed=Arr_Strom[18];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_17_Var:
            g_ulAnimSpeed=Arr_Strom[19];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_18_Var:
            g_ulAnimSpeed=Arr_Strom[20];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_19_Var:
            g_ulAnimSpeed=Arr_Strom[21];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_20_Var:
            g_ulAnimSpeed=Arr_Strom[22];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_21_Var:
            g_ulAnimSpeed=Arr_Strom[23];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_22_Var:
            g_ulAnimSpeed=Arr_Strom[24];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_23_Var:
            g_ulAnimSpeed=Arr_Strom[0];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_24_Var:
            g_ulAnimSpeed=Arr_Strom[1];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_0:
            g_ulAnimSpeed2=Arr_Spannung[2];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_1:
            g_ulAnimSpeed2=Arr_Spannung[3];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_2:
            g_ulAnimSpeed2=Arr_Spannung[4];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_3:
            g_ulAnimSpeed2=Arr_Spannung[5];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_4:
            g_ulAnimSpeed2=Arr_Spannung[6];
            post_to_server2(pcInsert, iInsertLen);
            break;

        case SSI_INDEX_Spann_5:
            g_ulAnimSpeed2=Arr_Spannung[7];
            post_to_server2(pcInsert, iInsertLen);
            break;

        case SSI_INDEX_Spann_6:
            g_ulAnimSpeed2=Arr_Spannung[8];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_7:
            g_ulAnimSpeed2=Arr_Spannung[9];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_8:
            g_ulAnimSpeed2=Arr_Spannung[10];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_9:
            g_ulAnimSpeed2=Arr_Spannung[11];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_10:
            g_ulAnimSpeed2=Arr_Spannung[12];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_11:
            g_ulAnimSpeed2=Arr_Spannung[13];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_12:
            g_ulAnimSpeed2=Arr_Spannung[14];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_13:
            g_ulAnimSpeed2=Arr_Spannung[15];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_14:
            g_ulAnimSpeed2=Arr_Spannung[16];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_15:
            g_ulAnimSpeed2=Arr_Spannung[17];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_16:
            g_ulAnimSpeed2=Arr_Spannung[18];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_17:
            g_ulAnimSpeed2=Arr_Spannung[19];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_18:
            g_ulAnimSpeed2=Arr_Spannung[20];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_19:
            g_ulAnimSpeed2=Arr_Spannung[21];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_20:
            g_ulAnimSpeed2=Arr_Spannung[22];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_21:
            g_ulAnimSpeed2=Arr_Spannung[23];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_22:
            g_ulAnimSpeed2=Arr_Spannung[24];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_23:
            g_ulAnimSpeed2=Arr_Spannung[0];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_24:
            g_ulAnimSpeed2=Arr_Spannung[1];
            post_to_server2(pcInsert, iInsertLen);
            break;

        default:
            usnprintf(pcInsert, iInsertLen, "??");
            break;

    }

    // Tell the server how many characters our insert string contains.
    return(strlen(pcInsert));
}
//*****************************************************************************

// The interrupt handler for the SysTick interrupt.
//*****************************************************************************
void SysTickIntHandler(void)
{
    // Call the lwIP timer handler.
    lwIPTimer(SYSTICKMS);
}
//*****************************************************************************

// Display an lwIP type IP Address.
//*****************************************************************************
void DisplayIPAddress(uint32_t ui32Addr)
{
    char pcBuf[16];

    // Convert the IP Address into a string.
    usprintf(pcBuf, "%d.%d.%d.%d", ui32Addr & 0xff, (ui32Addr >> 8) & 0xff,
            (ui32Addr >> 16) & 0xff, (ui32Addr >> 24) & 0xff);

    // Display the string.
    UARTprintf(pcBuf);
}
//*****************************************************************************

// Required by lwIP library to support any host-related timer functions.
//*****************************************************************************
void lwIPHostTimerHandler(void)
{
    uint32_t ui32NewIPAddress;

    // Get the current IP address.
    ui32NewIPAddress = lwIPLocalIPAddrGet();

    // See if the IP address has changed.
    if(ui32NewIPAddress != g_ui32IPAddress)
    {
        // See if there is an IP address assigned.
        if(ui32NewIPAddress == 0xffffffff)
        {
            // Indicate that there is no link.
            UARTprintf("Waiting for link.\n");
        }
        else if(ui32NewIPAddress == 0)
        {
            // There is no IP address, so indicate that the DHCP process is
            // running.
            UARTprintf("Waiting for IP address.\n");
        }
        else
        {
            // Display the new IP address.
            UARTprintf("IP Address: ");
            DisplayIPAddress(ui32NewIPAddress);
            UARTprintf("\n");
            UARTprintf("Open a browser and enter the IP address.\n");
        }

        // Save the new IP address.
        g_ui32IPAddress = ui32NewIPAddress;
    }

    // If there is not an IP address.
    if((ui32NewIPAddress == 0) || (ui32NewIPAddress == 0xffffffff))
    {
        // Do nothing and keep waiting.
    }
}
//*****************************************************************************

int main(void)
{
    uint32_t ui32User0, ui32User1;
    uint8_t pui8MACArray[8];

    // Make sure the main oscillator is enabled because this is required by
    // the PHY.  The system must have a 25MHz crystal attached to the OSC
    // pins.  The SYSCTL_MOSC_HIGHFREQ parameter is used when the crystal
    // frequency is 10MHz or higher.
    SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);

    // Run from the PLL at 120 MHz.
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 120000000);

    // Configure the device pins.
    PinoutSet(true, false);

    // Configure debug port for internal use.
    UARTStdioConfig(0, 115200, g_ui32SysClock);

    // Clear the terminal and print a banner.
    UARTprintf("\033[2J\033[H");
    UARTprintf("Ethernet IO Example\n\n");

    // Configure SysTick for a periodic interrupt.
    MAP_SysTickPeriodSet(g_ui32SysClock / SYSTICKHZ);
    MAP_SysTickEnable();
    MAP_SysTickIntEnable();

    // Configure the hardware MAC address for Ethernet Controller filtering of
    // incoming packets.  The MAC address will be stored in the non-volatile
    // USER0 and USER1 registers.
    MAP_FlashUserGet(&ui32User0, &ui32User1);

    // Tell the user what we are doing just now.
    UARTprintf("Waiting for IP.\n");

    // Convert the 24/24 split MAC address from NV ram into a 32/16 split
    // MAC address needed to program the hardware registers, then program
    // the MAC address into the Ethernet Controller registers.
    pui8MACArray[0] = ((ui32User0 >>  0) & 0xff);
    pui8MACArray[1] = ((ui32User0 >>  8) & 0xff);
    pui8MACArray[2] = ((ui32User0 >> 16) & 0xff);
    pui8MACArray[3] = ((ui32User1 >>  0) & 0xff);
    pui8MACArray[4] = ((ui32User1 >>  8) & 0xff);
    pui8MACArray[5] = ((ui32User1 >> 16) & 0xff);

    // Initialze the lwIP library, using DHCP.
    // 0xC0A8166F is 192.168.22.111
    // 0xFFFFFF00 is 255.255.255.0
    lwIPInit(g_ui32SysClock, pui8MACArray, 0xC0A8166F, 0xFFFFFF00, 0, IPADDR_USE_STATIC);

    // Initialize a sample httpd server.
    httpd_init();

    // Pass our tag information to the HTTP server.
    http_set_ssi_handler((tSSIHandler)SSIHandler, g_pcConfigSSITags,
            NUM_CONFIG_SSI_TAGS);

    // Initialize IO controls
    io_init();
//*****************************************************************************
    Funktion_ADC();

    IntPrioritySet(INT_ADC0SS0, 1);
    ADCIntRegister(ADC0_BASE, 0, ADC0IntHandler);
    IntRegister(INT_ADC0SS0, ADC0IntHandler);
    ADCIntEnable(ADC0_BASE, 0);
    IntEnable(INT_ADC0SS0);
    IntMasterEnable();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinConfigure(GPIO_PF2_M0PWM2);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);    //PWM OutputPin PF2 !!!

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenEnable(PWM0_BASE, PWM_GEN_1);

    PWMOutputState(PWM0_BASE, (PWM_OUT_2_BIT | PWM_OUT_3_BIT), true);

    ADCSequenceEnable(ADC0_BASE, 0);
//*****************************************************************************


    // Loop forever, processing the on-screen animation.  All other work is
    // done in the interrupt handlers.

    while(1)
    {

        ON=0;
        OFF=250;
        help=0;
        // Toggle the GPIO
        MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1,
                (MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_1) ^
                 GPIO_PIN_1));

//*****************************************************************************

        for(i=0;i<25;i++)
        {
        ulTempAvg = ((ulADC0Value[0] + ulADC0Value[1] + ulADC0Value[2]+ ulADC0Value[3])/4);
        Voltage = ((ulTempAvg/4095)*3.3);
        Arr_Spannung[i]=Voltage;
        Current = Voltage / 100 * 1000;
        Arr_Strom[i]=Current;

            PWMGenPeriodSet(PWM0_BASE,  PWM_GEN_1, 500);              // 100% (40us) Tpwm_clk=80ns, 80n*500 = 40us (25kHz)
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, ON);               // 50%  (20us)  (PWM0_BASE, PWM_OUT_2, 250)                                        */
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, OFF);              // 25%  (10us)  (PWM0_BASE, PWM_OUT_3, 125)                                        */

       for(ui32Lupe=0;ui32Lupe<2000000;ui32Lupe++)
       {
           help=help+10;
       }

       ON=(ON+20);
       OFF=(OFF-10);
        }

        for(ui32Lupe=0;ui32Lupe<100000000;ui32Lupe++)
        {
            hilfe=hilfe+10;
        }

        if (adcGetValues==1)
        {
            ADCSequenceDisable(ADC0_BASE, 0);
            ADCIntDisable(ADC0_BASE, 0);
            IntDisable(INT_ADC0SS0);

            adcGetValues = 0;

            ADCIntEnable(ADC0_BASE, 0);
            IntEnable(INT_ADC0SS0);
            ADCSequenceEnable(ADC0_BASE, 0);


        }
//*****************************************************************************


    }

    return (0);
}

void Funktion_ADC(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5);

    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 30);

    ADCSequenceDisable(ADC0_BASE, 0);

    ADCHardwareOversampleConfigure(ADC0_BASE, 16);

    ADCReferenceSet(ADC0_BASE, ADC_REF_INT);

    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_ALWAYS, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH8);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH8);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH8);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 3, (ADC_CTL_CH8 | ADC_CTL_IE | ADC_CTL_END));
}

