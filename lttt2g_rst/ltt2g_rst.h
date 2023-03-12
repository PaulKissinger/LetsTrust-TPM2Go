#ifndef _LTT2G_RST_
#define _LTT2G_RST_
/**
  * @brief              LetsTrust-TPM2Go reset handler
  * @details    ltt2g_rst.h implements all LetsTrustTPM2Go_ResetToggle byte commands and the prototype declarations for ltt2g_rst.c.
  * @file               ltt2g_rst.h
  * @date               2023/03/04
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <libusb-1.0/libusb.h>

//-------------"Defines"-------------
#define ERR_BAD_CMD             -2                      ///< Error code for a bad command line argument or option.
#ifndef INT_MAX
#define INT_MAX                 0x7FFFFFF       ///< The maximum value of a signed 32-bit integer.
#endif
#define CY_VENDOR_REQUEST_DEVICE_TO_HOST 0xC0
#define CY_GPIO_SET_VALUE_CMD 0xDB
#define VID_CYPRESS 0x04b4u
#define PID_CYUSBSPI 0x0004u
#define LTTPM2GO_RST_PIN 8
#define LTTPM2GO_RST_LOGIC_LEVEL_HIGH 1
#define LTTPM2GO_RST_LOGIC_LEVEL_LOW 0

//-------------"Macros"-------------
// Return value check
#define RET_VAL_CHECK(x) if (EXIT_SUCCESS != x) { break; } ///< Return value check

//--------------"Enums"--------------

//-------------"Methods"-------------

/**
  * @brief      Set the USB-GPIO for the TPM RST.
  * @param      [in]    *dev_handle                     An libusb_device_handle.
  * @param      [in]    gpioNumber                      An libusb_device_handle.
  * @param      [in]    value                           An libusb_device_handle.
  * @return     One of the listed return codes.
  * @retval     EXIT_SUCCESS                            In case of success.
  * @retval     ERR_BAD_CMD                             In case of bad user input.
  * @retval     LIBUSB_ERROR_TIMEOUT                    In case of an Timeout of the USB-Bridge.
  * @date       2023/03/05
  */
static int LtTpm2Go_SetGpioValue(libusb_device_handle *dev_handle, const int gpioNumber, const int value);

/**
  * @brief      Print the command line usage and switches.
  * @date       2023/03/05
  */
static void print_info();

#endif /* _LTT2G_RST_ */
