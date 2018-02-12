/**
 * This is a library to interface with a TMP100.
**/

#include "Arduino.h"
#include "Wire.h"
#include "PetersonAlchemy_TMP100.h"

#define TMP100_POINTER_REGISTER_TEMPERATURE   (0x00)
#define TMP100_POINTER_REGISTER_CONFIGURATION (0x01)

/***************************************************************************
 CONSTRUCTOR
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Instantiates a new PetersonAlchemy_TMP100 class
*/
/**************************************************************************/
PetersonAlchemy_TMP100::PetersonAlchemy_TMP100(uint8_t addr, int32_t sensorID) {
  _addr = addr;
  _tmp100SensorID = sensorID;
}

/***************************************************************************
 PUBLIC FUNCTIONS
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Setups the HW
*/
/**************************************************************************/
boolean PetersonAlchemy_TMP100::begin()
{
  _i2c = &Wire;
  _i2c->begin();

  // Enable I2C
  // Wire.begin();
  //
  // Wire.beginTransmission(_addr);
  // Wire.write(TMP100_POINTER_REGISTER_CONFIGURATION);
  // // TODO: change this to be configurable
  // // set continuous conversion, comparator mode, 12-bit resolution
  // Wire.write(0x60);
  // Wire.endTransmission();
  // // TODO: sample code had a delay of 300 at the end of the transmission
  return init();
}

/**************************************************************************/
/*!
    @brief  Setups the HW
    @param  theWire A TwoWire object that can identify specific I2C
      parameters, like the pins to use.
*/
/**************************************************************************/
boolean PetersonAlchemy_TMP100::begin(TwoWire *theWire)
{
  _i2c = theWire;
  _i2c->begin();

  return init();
}

/**************************************************************************/
/*!
    @brief  Convert a temperature in Celsius to Fahrenheit
    @param  tempC Temperature in Celsius
    @returns Temperature in Fahrenheit
*/
/**************************************************************************/
float PetersonAlchemy_TMP100::toFahrenheit(float tempCelsius) {
  return (tempCelsius * 1.8) + 32.0;
}

/**************************************************************************/
/*!
    @brief   SparkFun compatibility: return the temperature in Celcius.
    @returns Temperature in Celcius
*/
/**************************************************************************/
float PetersonAlchemy_TMP100::readTempC(void) {
  int16_t temperature;

  temperature = read16(TMP100_POINTER_REGISTER_TEMPERATURE);

  // TODO: need to add support for resolution other than 12 bits
  temperature >>= 4;
  return temperature * 0.0625;
}

/**************************************************************************/
/*!
    @brief   SparkFun compatibility: return the temperature in Fahrenheit.
    @returns Temperature in Celcius
*/
/**************************************************************************/
float PetersonAlchemy_TMP100::readTempF(void) {
  return toFahrenheit(readTempC());
}

/**************************************************************************/
/*!
    @brief Get the sensed data.
    @param event Pointer to store the event information.
*/
/**************************************************************************/
bool PetersonAlchemy_TMP100::getEvent(sensors_event_t *event) {
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _tmp100SensorID;
  event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  event->timestamp = 0;
  event->temperature = readTempC();
  
  return true;
}

/**************************************************************************/
/*!
    @brief  Get information about the sensor.
*/
/**************************************************************************/
void PetersonAlchemy_TMP100::getSensor(sensor_t *sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  strncpy (sensor->name, "TMP100", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _tmp100SensorID;
  sensor->type        = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  sensor->min_delay   = 0;
  sensor->min_value   = -55.0F;
  sensor->max_value   = 125.0F;
  sensor->resolution  = 0.0625F;  // TODO: make this customizeable
}

/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

 /**************************************************************************/
 /*!
   @brief  Initialize the TMP100 operation mode
   */
boolean PetersonAlchemy_TMP100::init() {
  // TODO: change this to be configurable
  // set continuous conversion, comparator mode, 12-bit resolution
  write8(TMP100_POINTER_REGISTER_CONFIGURATION, 0x60);

  return true;
}

/**************************************************************************/
/*!
  @brief  Writes a register and an 8 bit value over I2C (From Adafruit)
  @param  reg I2C register to write the value to
  @param  value The 8-bit value we're writing to the register
*/
void PetersonAlchemy_TMP100::write8(uint8_t reg, uint8_t value) {
  _i2c->beginTransmission(_addr);
  _i2c->write(reg);
  _i2c->write(value);
  _i2c->endTransmission();
}

/**************************************************************************/
/*!
    @brief  Reads a 16 bit value over I2C, big-endian (From Adafruit)
    @param  reg I2C register to read from
    @returns 16-bit value containing 2-byte data read
*/
/**************************************************************************/
uint16_t PetersonAlchemy_TMP100::read16(uint8_t reg) {
  uint16_t ret;

  _i2c->beginTransmission(_addr);
  _i2c->write(reg);
  _i2c->endTransmission();

  _i2c->requestFrom(_addr, 2);
  ret = _i2c->read(); // read the top 8 bits
  ret <<= 8; // shift 8 bits to the left
  ret |= _i2c->read(); // merge the top 8 bits with the bottom 8 bits
  return ret;
}
