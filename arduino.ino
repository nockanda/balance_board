#include <SoftwareSerial.h>
#include "HX711.h"

//저울1번꺼
const int DT1 = 2;
const int SCK1 = 3;
//저울2번꺼
const int DT2 = 4;
const int SCK2 = 5;

HX711 scale1; //저울1번꺼
HX711 scale2; //저울2번꺼

SoftwareSerial HC06(6,7);

void setup() {
  Serial.begin(9600);
  HC06.begin(9600);
  scale1.begin(DT1, SCK1);
  scale2.begin(DT2, SCK2);

  scale1.set_scale(-10500);
  scale2.set_scale(-11600);
  scale1.tare();
  scale2.tare();
}

void loop() {
  float weight1 = scale1.get_units()*-0.453592;
  float weight2 = scale2.get_units()*-0.453592;
  //Serial.print("첫번째 저울의 무게값=");
  //Serial.print(weight1,1);
  //Serial.print("kg, 두번째 저울의 무게값=");
  //Serial.print(weight2,1);
  //Serial.println("kg");

  if(weight1 < 0) weight1 = 0;
  if(weight2 < 0) weight2 = 0;

  if(weight1 > 1 && weight2 > 1){

    float balance1 = weight1/(weight1+weight2);
    float balance2 = 1 - balance1;
    
    
    HC06.print(balance1); 
  }
  delay(500);
}