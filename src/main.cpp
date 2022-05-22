#include <Arduino.h>

int PIN_temp_sens;
int temp_sens_value;
int PIN_heater;

bool is_temp_sens_value_at_treshold(float val)
{
  return (temp_sens_value = val);
}

void setup()
{
  analogSetAttenuation(ADC_0db); // 100mV-950mV
  // analogSetAttenuation(ADC_2_5db); 100mV - 1250mV
  // analogSetAttenuation(ADC_6db); 150mV - 1750mV
  // analogSetAttenuation(ADC_11db); 150mV - 2450 mV

  Serial.begin(115200);
  pinMode(PIN_temp_sens, INPUT);
  pinMode(PIN_heater, OUTPUT);
  Serial.println("Started");

  for (int i = 0; i < 10; i++)
  {
    temp_sens_value += analogRead(PIN_temp_sens);
  }
  temp_sens_value /= 10;

  Serial.print("init_pot: ");
  Serial.println(temp_sens_value);
}

void loop()
{
  temp_sens_value = (analogRead(PIN_temp_sens) + 9 * temp_sens_value) / 10;

  if (is_temp_sens_value_at_treshold(1950))
  {
    digitalWrite(PIN_heater, LOW);
  }
  else
  {
    digitalWrite(PIN_heater, HIGH);
  }
}
