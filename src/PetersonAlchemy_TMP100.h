/*!
 * @file PetersonAlchemy_TMP100.h
 *
 * This library is designed to work with the TMP100 temperature sensor.
 * Peterson Alchemy provides a TMP100 breakout board that is compatible
 * with this library.
 *
 * Written by Jesse Peterson
 */

 #ifndef PETERSONALCHEMY_TMP100
 #define PETERSONALCHEMY_TMP100

 #include <Arduino.h>
 #include <Adafruit_Sensor.h>
 #include <Wire.h>

// I2C address options
// '0' below means pin logic level 0
// '1' below means pin logic level 1
// 'F' below means "float" where the pin is left unconnected
#define TMP100_ADD1_0_ADD0_0  (0x48) // ADD1 0, ADD0 0
#define TMP100_ADD1_0_ADD0_F  (0x49) // ADD1 0, ADD0 Float
#define TMP100_ADD1_0_ADD0_1  (0x4A) // ADD1 0, ADD0 1
#define TMP100_ADD1_1_ADD0_0  (0x4C) // ADD1 1, ADD0 0
#define TMP100_ADD1_1_ADD0_F  (0x4D) // ADD1 1, ADD0 Float
#define TMP100_ADD1_1_ADD0_1  (0x4E) // ADD1 1, ADD0 1
#define TMP100_ADD1_F_ADD0_0  (0x4B) // ADD1 1, ADD0 0
#define TMP100_ADD1_F_ADD0_1  (0x4F) // ADD1 1, ADD0 1

/***/
/*!
 * @brief Class that provides a driver interface for a TMP100 temperature
 * sensor.
 */
/***/
class PetersonAlchemy_TMP100 : public Adafruit_Sensor {
public:
  PetersonAlchemy_TMP100(uint8_t addr, int32_t sensorID = -1);
  boolean begin(void);
  boolean begin(TwoWire *theWire);

  /* TMP100 functions */
  float toFahrenheit(float tempCelsius);

  /* SparkFun TMP102 compatibility. Subset of their API. */
  float readTempC(void);  // Returns the temperature in degrees C
  float readTempF(void);  // Converts readTempC result to degrees F
  // void sleep(void);       // Switch sensor to low power mode
  // void wakeup(void);      // Wakeup and start running in normal power mode

  /* Unified Sensor API functions */
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);

private:
  TwoWire *_i2c;

  uint8_t _addr;
  int32_t _tmp100SensorID;

  boolean  init();

  /* Commonly found in the Adafruit libraries */
  void     write8 (uint8_t reg, uint8_t value);
  uint16_t read16 (uint8_t reg);
};

 #endif // PETERSONALCHEMY_TMP100
