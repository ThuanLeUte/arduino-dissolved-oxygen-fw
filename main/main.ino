/**
 * @file       main.ino
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2022-03-17
 * @author     Thuan Le
 * @brief      Main file
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "sys_iot.h"

/* Private defines ---------------------------------------------------- */
#define FW_VERSION  "1.0.0.0"

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void setup()
{
  sys_iot_run(1000);
}

void loop()
{
  sys_iot_poll();
}

/* Private function definitions --------------------------------------- */
/* End of file -------------------------------------------------------- */
