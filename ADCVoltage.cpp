#define RASPBERRY 

#include "NanoShield_ADC.h"

#define ADC_VREF 6.144

float adc2volts(float adc, float vref);
NanoShield_ADC ads1115((unsigned char)(0x48));


void setup(void) 
{
  printf("ADC Nanoshield Test - Voltage Measurement\n");
  ads1115.begin();
  delay(100);
}

void loop(void) 
{
  uint16_t adc0,adc1,adc2,adc3;
  adc0= ads1115.readADC_SingleEnded(0);

  adc1 = ads1115.readADC_SingleEnded(1);
  adc2 = ads1115.readADC_SingleEnded(2);
  adc3 = ads1115.readADC_SingleEnded(3);
  printf("A0 voltage: %f V\n", adc2volts(adc0, ADC_VREF));// Serial.println("V");
  printf("A1 voltage: %f V\n", adc2volts(adc1, ADC_VREF));// Serial.println("V");
  printf("A2 voltage: %f V\n", adc2volts(adc2, ADC_VREF));// Serial.println("V");
  printf("A3 voltage: %f V\n\n", adc2volts(adc3, ADC_VREF));// Serial.println("V");

}

float adc2volts(float adc, float vref)
{
  return (adc * vref) / 32767;
}

int main(){
	int i;
	setup();
        for(i = 1; i < 2;i++){
                delay(1000);
		loop();
	}
	return 0;
}

