/********/
/*!
 *  @file SimpleReadU
 *  @author Jesse Peterson
 *  @license BSD (see license.txt)
 *  
 *  This is an example for the Peterson Alchemy TMP100 breakout board using the
 *  Adafruit Unified Sensor interface.
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // give some time to open the serial monitor
  delay(5000);

  Serial.println("Peterson Alchemy TMP100 Unified Sensor test!");

  if (!tmp100.begin()) {
    Serial.println("Couldn't begin");
    while (1);
  }

  Serial.println("TMP100 started.");

  // Print temperature sensor details.
  sensor_t sensor;
  tmp100.getSensor(&sensor);
  Serial.println("--------------------------");
  Serial.print  ("Sensor:      "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:  "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:   "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:   "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:   "); Serial.print(sensor.min_value); Serial.println(" *C"); 
  Serial.print  ("Resolution:  "); Serial.print(sensor.resolution); Serial.println(" *C"); 
}

void loop() {
  // put your main code here, to run repeatedly:

  // Dealy between measurements.
  delay(1000);
  
  /* Get a new sensor event */ 
  sensors_event_t event; 
  tmp100.getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.print(" *C, ");
    Serial.print(tmp100.toFahrenheit(event.temperature));
    Serial.println(" *F");
  }
}
