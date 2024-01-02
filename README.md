# weather-station
Reimplementation and extension [weatherstation](https://github.com/fandonov/weatherstation) uisng a Nodemcu esp32.

## sensors
 - master node
   - BME280 sensor
   - DS3231-mini rtc
   - MQ-7 CO sensor

 - slave node
   - GUVA-S12SD analog UV sensor
   - BME280 sensor

## other hardware
- generic SPI SD card adapter
- ssd1306 display
## features
### software features
 - logging of sensor data on a set interval
    - data from slave device - Temperature, Humidity, Pressure, UV index
    - data from master device - Temperature, Humidity, Pressure, Altitude.
 - clock syncing with ntp
 - clock with daylight savings/timezone adjustments
 - moon rise/set calculation using [MoonRise.h](https://www.arduino.cc/reference/en/libraries/moonrise/)
 - moon angle and illuminated surface using [moonPhase.h](https://www.arduino.cc/reference/en/libraries/moonphase/)
 - sun rise/set calculation [SunRise.h](https://www.arduino.cc/reference/en/libraries/sunrise/)
 - showing curated information for the sensors on display
 - short term weather forecast using [zambretti algorithm](https://github.com/fandonov/weatherstation/blob/master/weather-station.ino) 
   (modified to have persistent data of past predictions with a file on the sd card)
 - persistent configuration of some parameters via a json file
 - battery % reporting from slave device

### network features
 - connects to a wireless network with provided credentials
 - creates its own hotspot with baked in password and ssid if it cant find
   it/connect
 - very simple configuration page to edit some of the settings.
   changing a setting would require a restart to take effect
 - a simple dashboard to show information from sensors every few seconds.
 - ntp client to syncronise clocks if connected to a network

### display
 - CO ppm
 - Atmospheric readings inside  (temp,pressure,altitude,humidity)
 - Atmospheric readings outside (temp,pressure,humidity, uv idx)
 - Time and Date, current IP of device
 - Time and Date adjusted with Daylight savings and Timezone, current IP of device
 - Time of Sunrise, Sunset, Moonrise, Moonset moon phase angle and illumination %
 - Weather forecast and Pressure trend

## Requirements
TODO add requirements
