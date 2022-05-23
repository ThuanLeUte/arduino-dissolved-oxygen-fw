/**
 * @file       sys_iot.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2022-03-17
 * @author     Thuan Le
 * @brief      System file to handle IoT
 * @note       None
 * @example    None
 */

/* Private defines ---------------------------------------------------- */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLt4xb5aOZ"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN  "q8aek7zucOIf210wT6ypKdA_OmrZdD0Q"

/* Includes ----------------------------------------------------------- */
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "sys_do.h"

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "DitMeMay";
char pass[] = "hiepdeptraioiladeptrai";

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void sys_iot_update_periodic(void)
{
  sys_do_data_t do_data = { 0 };

  sys_do_read_data(&do_data);

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, do_data.dissolved_oxygen);
  Blynk.virtualWrite(V2, do_data.bat_voltage);
}

void sys_iot_run(uint32_t ms)
{
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(ms, sys_iot_update_periodic);
}

void sys_iot_poll(void)
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  
  for (uint8_t j = 0; j < 60; j++)
  {
    delay(1000);
  }
}

/* Private function definitions --------------------------------------- */
/* End of file -------------------------------------------------------- */
