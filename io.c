#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "utils/ustdlib.h"
#include "io.h"

//*****************************************************************************
//
// Hardware connection for the user LED.
//
//*****************************************************************************
#define LED_PORT_BASE GPIO_PORTN_BASE
#define LED_PIN GPIO_PIN_0

//*****************************************************************************
//
// Hardware connection for the animation LED.
//
//*****************************************************************************
#define LED_ANIM_PORT_BASE GPIO_PORTN_BASE
#define LED_ANIM_PIN GPIO_PIN_1

//*****************************************************************************
//
// The system clock speed.
//
//*****************************************************************************
extern uint32_t g_ui32SysClock;
//*****************************************************************************
volatile int g_ulAnimSpeed;
volatile float g_ulAnimSpeed2;
//*****************************************************************************
void io_init(void){}
void io_set_led(bool bOn){}
//*****************************************************************************

void post_to_server(char * pcBuf, int iBufLen)
{
    snprintf(pcBuf, iBufLen, "%d", g_ulAnimSpeed);
}

void post_to_server2(char * pcBuf, int iBufLen)
{
    snprintf(pcBuf, iBufLen, "%f", g_ulAnimSpeed2);
}
