#define RASPBERRY 

#include "NanoShield_ADC.h"

#define ADC_VREF 6.144

float adc2volts(float adc, float vref);
NanoShield_ADC ads1115(0x48);


void setup(void) 
{
  Serial.begin(115200);
  Serial.println("ADC Nanoshield Test - Voltage Measurement");
  Serial.println("");
  ads1115.begin();
}

void loop(void) 
{
  int16_t adc0, adc1, adc2, adc3;

  adc0 = ads1115.readADC_SingleEnded(0);
  adc1 = ads1115.readADC_SingleEnded(1);
  adc2 = ads1115.readADC_SingleEnded(2);
  adc3 = ads1115.readADC_SingleEnded(3);
  Serial.print("A0 voltage: "); Serial.print(adc2volts(adc0, ADC_VREF)); Serial.println("V");
  Serial.print("A1 voltage: "); Serial.print(adc2volts(adc1, ADC_VREF)); Serial.println("V");
  Serial.print("A2 voltage: "); Serial.print(adc2volts(adc2, ADC_VREF)); Serial.println("V");
  Serial.print("A3 voltage: "); Serial.print(adc2volts(adc3, ADC_VREF)); Serial.println("V");
  Serial.println("");
  
  delay(1000);
}

float adc2volts(float adc, float vref)
{
  return adc * vref / 32767;
}

int main(){

	setup();
	while(1){
		loop();
	}
	return 0;
}

