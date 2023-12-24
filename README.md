# ElectroOS
Operating system for "Electro" low-noise power supply. This README document provides a *brief* program overview (setup, architecture, usage, maintainability suggestions, and a changelog). More comprehensive system details can be found in the [full documentation](https://drive.google.com/drive/u/0/folders/1_AaNE1AWDB-emdoWApCKo6zqOy2tdl2Q).

# Setup
**1. In Arduino IDE**
- Install the board manager and board drivers (if necessary). Details available [here](https://learn.sparkfun.com/tutorials/qwiic-pro-micro-usb-c-atmega32u4-hookup-guide/all#installing-drivers-windows).
- Install necessary plugins in Arduino IDE ("Sparkfun AVR Boards" in board manager, "Sparkfun Micro OLED" in plugins).   
- Test board connection by uploading "Blink" sample code to the board. If the upload fails verify that (a) the USB-C cabel you are using transmits both power AND data and (b) that the Sparkfun Pro Micro is installed properly. It should show up in device manager under the "ports" section under the name "SparkFun Pro Micro".

**2. PlatformIO Initialization**
- Install PlatformIO for Visual Studio Code and open the project folder (i.e. the "ElectroOS" folder). PlatformIO should automatically import the project configuration and select the port that the board is connected to.
- Verify that the setup is working properly by clicking "build" and then "upload". If the firmware is successfully flashed to the board, you're all set with setup.

# Program Structure
