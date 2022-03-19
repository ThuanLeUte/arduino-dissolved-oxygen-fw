/**
 * @file       sys_do.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2022-03-17
 * @author     Thuan Le
 * @brief      System file to handle read Dissolved oxygen in water
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
/* Private defines ---------------------------------------------------- */
#define DO_PIN    (33)
#define VREF      (3300)    // VREF (mv)
#define ADC_RES   (4095)    // ADC Resolution

#define TWO_POINT_CALIBRATION (0)
#define CAL1_V                (888)  // mv
#define CAL1_T                (25)   // ℃
#define CAL2_V                (1300) // mv
#define CAL2_T                (15)   // ℃

const uint16_t DO_TABLE[41] =
{
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410
};

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
typedef struct
{
  uint8_t temperature;
  uint16_t adc_raw;
  uint16_t adc_voltage;
  uint16_t dissolved_oxygen;
}
sys_do_data_t;

/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
int16_t sys_do_read_do(uint32_t voltage_mv, uint8_t temperature_c)
{
#if TWO_POINT_CALIBRATION == 00
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_TABLE[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_TABLE[temperature_c] / V_saturation);
#endif
}

void sys_do_read_data(sys_do_data_t *do_data)
{
  do_data->temperature      = (uint8_t)CAL1_T;
  do_data->adc_raw          = analogRead(DO_PIN);
  do_data->adc_voltage      = uint32_t(VREF) * do_data->adc_raw / ADC_RES;
  do_data->dissolved_oxygen = sys_do_read_do(do_data->adc_raw, do_data->temperature);

  Serial.print("Temperature:\t" + String(do_data->temperature) + "\t");
  Serial.print("ADC RAW:\t" + String(do_data->adc_raw) + "\t");
  Serial.print("ADC Voltage:\t" + String(do_data->adc_raw) + "\t");
  Serial.println("DO:\t" + String(do_data->dissolved_oxygen) + "\t");
}

/* Private function definitions --------------------------------------- */
/* End of file -------------------------------------------------------- */
