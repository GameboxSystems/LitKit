# LitKit

![LitKit](/images/LitKit.jpg)
![LitKitTop](/images/LitKitTop.png)

LitKit is a tiny little Attiny85 addressable RGB LED board that features only three required parts to be funtional: Attiny85, 0.1uF cermaic 0805 cap, and a 100 ohm 0805 resistor. That's all!

Also features WS2812B 3535 on PCB, V+/GND/Data to daisy chain WS2812B LEDs to the main board, and solder pads for connecting a button.

To flash the board simply place the populated board on top a USBTinyISP boards ISP port, press down to ensure contact and flash! ISP Programming holes are measured to tension fit LitKit in place when pressed into place.

## Getting Started


### Prerequisites
Required:

* Populated LitKit Board
* Arduino IDE
* USBTinyISP Board
	* [Board tested working can be found here](https://www.ebay.com/itm/USB-Tiny-AVR-5V-ATtiny44-USBTinyISP-Programmer-For-Arduino-Bootloader/183986605082?hash=item2ad674cc1a:g:sEQAAOSwufJdm9h0) 

Recommended:

* 500mA + 3.3v-5v power source
* Any type of Addressable WS2812B LED array (Neopixel, LED strip, etc.)
* [Adafruit Neopixel Arduino Library](https://github.com/adafruit/Adafruit_NeoPixel)

## Software setup

* Install Arduino IDE (Tested with Arduino up to 1.8.13 from arduino.cc)
* Install TinyISP driver from https://learn.adafruit.com/usbtinyisp/download
* Open Arduino IDE
* Open File->Preferences
* Add https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json to "Additional Boards Manager URLs"
* Run Tools->Board->Boards Manager
* Install "attiny" board package
* Select ATtiny25/45/85 at Tools->Board->ATtiny Microcontroller
* Select ATtiny85 at Tools->Board->Processor
* Select Internal 16 MHz at Tools->Clock
* Select USBtinyISP at Tools->Programmer

## Examples

### Run as multi file arduino sketch

* Copy src/LitKit.c and src/LitKit.h to selected example folder
* Rename LitKit.c to LitKit.ino
* Open exampleX.ino in Arduino IDE


### Flashing LitKit with USBTinyISP

*COMING SOON*

### Daisy Chaining Litkit -> LED Array

*COMING SOON*

## Currently Known Issues

N/A

## Built With

* Eagle

## Versions

v1.0 - Initial release

## Contributing

Please feel free to issue a PR or edit code freely. Would love to have people contribute ideas!


## Authors

* **Postman** - *Engineer at Gamebox Systems*
* **Knk**

## License

This project is licensed under the GPL-3.0 license, see attached license for info.
