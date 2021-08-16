/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSP_EXP432E401Y
 *  by the SysConfig tool.
 */

#include <stddef.h>
#include <stdint.h>

#ifndef DeviceFamily_MSP432E401Y
#define DeviceFamily_MSP432E401Y
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"


/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOMSP432E4.h>

#define CONFIG_GPIO_COUNT 4

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[CONFIG_GPIO_COUNT] = {
    /* CONFIG_GPIO_0 : LaunchPad Button USR_SW1 (Left) */
    GPIOMSP432E4_PJ0 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING,
    /* CONFIG_GPIO_1 : LaunchPad Button USR_SW2 (Right) */
    GPIOMSP432E4_PJ1 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING,
    /* CONFIG_LED_0_GPIO : LaunchPad LED D1 */
    GPIOMSP432E4_PN1 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_LED_1_GPIO : LaunchPad LED D2 */
    GPIOMSP432E4_PN0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
};

/*
 *  ======== gpioCallbackFunctions ========
 *  Array of callback function pointers
 *
 *  NOTE: Unused callback entries can be omitted from the callbacks array to
 *  reduce memory usage by enabling callback table optimization
 *  (GPIO.optimizeCallbackTableSize = true)
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    /* CONFIG_GPIO_0 : LaunchPad Button USR_SW1 (Left) */
    NULL,
    /* CONFIG_GPIO_1 : LaunchPad Button USR_SW2 (Right) */
    NULL,
    /* CONFIG_LED_0_GPIO : LaunchPad LED D1 */
    NULL,
    /* CONFIG_LED_1_GPIO : LaunchPad LED D2 */
    NULL,
};

const uint_least8_t CONFIG_GPIO_0_CONST = CONFIG_GPIO_0;
const uint_least8_t CONFIG_GPIO_1_CONST = CONFIG_GPIO_1;
const uint_least8_t CONFIG_LED_0_GPIO_CONST = CONFIG_LED_0_GPIO;
const uint_least8_t CONFIG_LED_1_GPIO_CONST = CONFIG_LED_1_GPIO;

/*
 *  ======== GPIOMSP432E4_config ========
 */
const GPIOMSP432E4_Config GPIOMSP432E4_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = CONFIG_GPIO_COUNT,
    .numberOfCallbacks = 4,
    .intPriority = (~0)
};


/*
 *  =============================== Power ===============================
 */

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerMSP432E4.h>
#include <ti/devices/msp432e4/inc/msp432.h>

extern void PowerMSP432E4_sleepPolicy(void);

const PowerMSP432E4_Config PowerMSP432E4_config = {
    .policyFxn             = PowerMSP432E4_sleepPolicy,
    .enablePolicy          = true
};


/*
 *  =============================== Button ===============================
 */
#include <ti/drivers/apps/Button.h>

#define CONFIG_BUTTON_COUNT 2
Button_Object ButtonObjects[CONFIG_BUTTON_COUNT];

static const Button_HWAttrs ButtonHWAttrs[CONFIG_BUTTON_COUNT] = {
    /* CONFIG_BUTTON_0 */
    /* LaunchPad Button USR_SW1 (Left) */
    {
        .gpioIndex = CONFIG_GPIO_0
    },
    /* CONFIG_BUTTON_1 */
    /* LaunchPad Button USR_SW2 (Right) */
    {
        .gpioIndex = CONFIG_GPIO_1
    },
};

const Button_Config Button_config[CONFIG_BUTTON_COUNT] = {
    /* CONFIG_BUTTON_0 */
    /* LaunchPad Button USR_SW1 (Left) */
    {
        .object = &ButtonObjects[CONFIG_BUTTON_0],
        .hwAttrs = &ButtonHWAttrs[CONFIG_BUTTON_0]
    },
    /* CONFIG_BUTTON_1 */
    /* LaunchPad Button USR_SW2 (Right) */
    {
        .object = &ButtonObjects[CONFIG_BUTTON_1],
        .hwAttrs = &ButtonHWAttrs[CONFIG_BUTTON_1]
    },
};

const uint_least8_t CONFIG_BUTTON_0_CONST = CONFIG_BUTTON_0;
const uint_least8_t CONFIG_BUTTON_1_CONST = CONFIG_BUTTON_1;
const uint_least8_t Button_count = CONFIG_BUTTON_COUNT;


/*
 *  =============================== LED ===============================
 */
#include <ti/drivers/apps/LED.h>

#define CONFIG_LED_COUNT 2
LED_Object LEDObjects[CONFIG_LED_COUNT];

static const LED_HWAttrs LEDHWAttrs[CONFIG_LED_COUNT] = {
    /* CONFIG_LED_0 */
    /* LaunchPad LED D1 */
    {
        .type = LED_GPIO_CONTROLLED,
        .index = CONFIG_LED_0_GPIO,
    },
    /* CONFIG_LED_1 */
    /* LaunchPad LED D2 */
    {
        .type = LED_GPIO_CONTROLLED,
        .index = CONFIG_LED_1_GPIO,
    },
};

const LED_Config LED_config[CONFIG_LED_COUNT] = {
    /* CONFIG_LED_0 */
    /* LaunchPad LED D1 */
    {
        .object = &LEDObjects[CONFIG_LED_0],
        .hwAttrs = &LEDHWAttrs[CONFIG_LED_0]
    },
    /* CONFIG_LED_1 */
    /* LaunchPad LED D2 */
    {
        .object = &LEDObjects[CONFIG_LED_1],
        .hwAttrs = &LEDHWAttrs[CONFIG_LED_1]
    },
};

const uint_least8_t CONFIG_LED_0_CONST = CONFIG_LED_0;
const uint_least8_t CONFIG_LED_1_CONST = CONFIG_LED_1;
const uint_least8_t LED_count = CONFIG_LED_COUNT;


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    Power_init();

    /* Grant the DMA access to all FLASH memory */
    FLASH_CTRL->PP |= FLASH_PP_DFA;

    /* Region start address - match FLASH start address */
    FLASH_CTRL->DMAST = 0x00000000;

    /*
     * Access to FLASH is granted to the DMA in 2KB regions.  The value
     * assigned to DMASZ is the amount of 2KB regions to which the DMA will
     * have access.  The value can be determined via the following:
     *     2 * (num_regions + 1) KB
     *
     * To grant full access to entire 1MB of FLASH:
     *     2 * (511 + 1) KB = 1024 KB (1 MB)
     */
    FLASH_CTRL->DMASZ = 511;

    Board_initHook();
}
