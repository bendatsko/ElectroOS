# ElectroOS

ElectroOS is C++-based embedded software for an ultra low-noise 5V power supply at the University of Michigan's Flynn Research Group. More comprehensive system details can be found in the [full documentation](https://drive.google.com/drive/u/0/folders/1_AaNE1AWDB-emdoWApCKo6zqOy2tdl2Q).

## Installation

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and [PlatformIO](https://platformio.org/) for VSCode.
2. Install the [Sparkfun Pro Micro](https://learn.sparkfun.com/tutorials/qwiic-pro-micro-usb-c-atmega32u4-hookup-guide/all#installing-drivers-windows) board on your device through the Arduino IDE following this setup guide exactly. You should be able to upload the "Blink" example program to the board through the Arduino IDE.
3. Install Arduino plugins [FreeRTOS](https://www.arduino.cc/reference/en/libraries/freertos/), [ArduinoQueue](https://www.arduino.cc/reference/en/libraries/arduinoqueue/), and [SparkFun Micro OLED Breakout] in the Arduino IDE. (https://www.arduino.cc/reference/en/libraries/sparkfun-micro-oled-breakout/).
4. Open the folder containing this README document (should be `ElectroOS`) as a project in PlatformIO.
5. Once loaded, click `Upload` to send the code to the board. If uploads continually fail, look at the Sparkfun Pro Micro documentation's section on enabling bootloader mode.


## Architecture
![](https://raw.githubusercontent.com/bendatsko/ElectroOS/main/architecture.png?token=GHSAT0AAAAAACLCB2AZFQOW7LN6EVHKNW6GZMNJCHQ)


## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

