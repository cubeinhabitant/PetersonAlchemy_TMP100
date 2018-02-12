/********/
/*!
 *  @file SimpleRead
 *  @author Jesse Peterson
 *  @license BSD (see license.txt)
 *  
 *  This is an example for the Peterson Alchemy TMP100 breakout board
 *  
 *  @section HISTORY
 *  
 *  v1.0 - First release
 */
/********/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <PetersonAlchemy_TMP100.h>

PetersonAlchemy_TMP100 tmp100 = PetersonAlchemy_TMP100(TMP100_ADD1_0_ADD0_0);
float tempCelsius;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Peterson Alchemy TMP100 test!");

  if (!tmp100.begin()) {
    Serial.println("Couldn't begin");
    while (1);
  }

  Serial.println("TMP100 started.");
}

void loop() {
  // put your main code here, to run repeatedly:
  tempCelsius = tmp100.readTempC();

  Serial.print("Temperature in Celsius: ");
  Serial.print(tempCelsius);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit: ");
  Serial.print(tmp100.toFahrenheit(tempCelsius));
  Serial.println(" F");
  delay(1000);
}
