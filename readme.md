Service used to grab data from COM port and write it to custom HWInfo sensors in windows registry

Before running install.bat don't forget to edit paths to JAVA library

prunsrv.exe provided by [Apache Commons](https://commons.apache.org/proper/commons-daemon/index.html)

------------

### Support dual BME280 sensor

#### hardware
[BME280-5V](https://aliexpress.ru/item/32848964559.html)
[WeMos D1 mini Pro](https://aliexpress.ru/item/32651747570.html)
[TCA9548A](https://aliexpress.ru/item/4001042335251.html)

#### Soldering
![soldering](https://day.ainenya.dev/LlHaHps8uQ.png "soldering")

#### Arduino IDE
1. Add support **WeMos D1 mini Pro**
File -> Preferences -> Additional Boards Manager URLs: 

`http://arduino.esp8266.com/stable/package_esp8266com_index.json`

2. Install **BME280** library: 
Tools -> Manage Libraries:

`Adafruit BME280 Library`

3. Pick port and flash
