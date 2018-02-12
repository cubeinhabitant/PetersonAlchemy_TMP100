# Peterson Alchemy TMP100 Driver

Arduino driver library for using a Texas Instruments TMP100. The TMP100 is a digital temperature sensor that you can communicate with via an I2C interface. This driver provides methods to easily retrieve the temperature from the chip.

## Getting Started

The drive can be installed in the Arduino IDE. The project includes some example programs showing how the drive API can be used. There are two compatibility modes implemented. The driver supports the Adafruit Unified Sensor Library (https://github.com/adafruit/Adafruit_Sensor). There is also support for a subset of the SparkFun TMP102 library (https://github.com/sparkfun/SparkFun_TMP102_Arduino_Library).

### Prerequisites

If using the Adafruit Unified Sensor Library support the "Adafruit Unified Sensor" library must be installed. This can be installed in the Arduino IDE by choosing "Sketch" > "Include Library" > "Manage Libraries..." and choosing the "Adafruit Unified Sensor" library.

### Installing

This driver can be installed in the Arduino IDE by downloading the ZIP file. In the Arduino IDE, choose "Sketch" > "Include Library" > "Add .ZIP Library..." and choose the ZIP file downloaded.

### Usage

Check the examples in the library for examples showing how to use the driver.

* SimpleRead - Read the temperature using the SparkFun TMP102 methods.
* SimpleReadU - Read the temperature using the Adafruit Unified Sensor Library.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **Jesse Peterson** - *Initial work* - [cubeinhabitant](https://github.com/cubeinhabitant)

## License

This project is licensed under the BSD License - see the [LICENSE.md](LICENSE.md) file for details
