# Heat Pump Controller

This is a board that will allow access to LG Therma V heatpump over WiFi. Functionality is limited - power monitoring (with PZEM004), put the pump in heat/cool/DHW mode, monitor the temperatures of the input and output water and control the DHW tank electric heating.

Future versions may extract pump data by sniffing the communication between the pump and the controller used for setting it up.

The following external components are used:
* 3 x Omron G3MB-202P - for selecting the cool/heat/DHW mode of the pump
* 1 x Omron G3MB-202P - for controlling the UFH circulation pump
* 1 x Omron G3MB-202P - for controlling one additional circulation pump
* high power AC SSR for turning on the DHW electric heating
* DS18B20 sensors for:
** Monitoring the DHW tank reservoir
** Heat pump heating/cooling agent input and output temperature
** Heating buffer tank temperature

## Building the project

The project uses a common set of tools that are availabe in another repo - https://github.com/funnybrum/esp8266-base. Clone the esp8266-base repo in the lib folder:

```
cd lib
git clone git@github.com:funnybrum/esp8266-base.git
```