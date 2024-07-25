# Coil Safety Circuit

## Introduction
This safety circuit uses an ESP32 C6 to detect temperature fluctuations or moisture build up on an electromagnet. It can shut off the coils via relay if needed. The ESP32 also hosts a network and webpage to monitor the status of the coils and set the temperature shut off threshold.

## Specifications
- **Power Supply:** USB-C cable to micro controller
- **Max Continuous Coil Power:** 65v 5A
- **Max Burst Coil Power:** 65v 35A
- **Pump Power:** 12v 5A
- **Temperature Sensors:** 4 thermistors with an accuracy of ±0.25°C


## Webpage

![screenshot](/Pictures/website.png)

This picture shows the default settings and appearance of the ESP32 webpage. The user can change the state of the coils and the pump with the three buttons in the top row. If a button is coloured red then that setting or component is off (no relay is open). All coils are off by default and the pump remains on. The user can also turn on and off temperature and moisture shut off with the buttons on the bottom row. It is also possible to change the temperature shut off threshold by clicking the plus or minus buttons on the temperature shut off button until the desired temperature is shown. The middle row show the current temperature average of all the thermistors and whether the moisture sensors are detecting water (0 being to water 1 being water). If the middle row cell is clicked or hovered over it displays more information about the sensors.

:warning: **Warning:** if the ESP32 crashes or loses power everything will be reset to default settings. :warning:

- **Default Settings:** Coils 1 and 2 are off, the pump is on, temperature shut off is on, moisture shut off is off, and the temperature shut off threshold is 60°C.

## Network

The webpage can be accessed by connect to the ESP32 network and typing the IP address of the ESP32 into a web browser. The IP address is displayed on the serial monitor when the ESP32 is booting up.

The network name is:
```
ESP32-Access-Point
```

The password is:
```
rydberg12
```

The default IP address is:

```
192.168.4.1
```

## LED Indicators
- **Green LED:** Normal operation and coils are off
- **Red LED:** Temperature shut off is active
- **Orange LED:** Moisture shut off is active
- **Blue LED:** Coils are on
- **No LED:** Something is very wrong with the ESP32


## Parts List

| Part                                                                                                               | Quantity | Price  |
| ------------------------------------------------------------------------------------------------------------------ | -------- | ------ |
| [ESP32 C6 DEV](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-C6-DEVKITM-1-N4/18667011)        | 1        | $8.00  |
| [Thermistor](https://www.digikey.com/en/products/detail/adafruit-industries-llc/4890/13982731)                     | 4        | $4.75  |
| [Water Sensor](https://www.digikey.com/en/products/detail/adafruit-industries-llc/4965/14302510)                   | 2        | $3.90  |
| [Coil Relay](https://www.digikey.com/en/products/detail/american-zettler/AZDC007-1AE-12D/22050421)                 | 2        | $11.78 |
| [Pump Relay](https://www.digikey.com/en/products/detail/american-zettler/AZ943-1CH-12DE/12171590)                  | 1        | $0.95  |
| [Barrel Connector](https://www.digikey.com/en/products/detail/cui-devices/PJ-037AH/1644547)                        | 1        | $0.74  |
| [Barrel Connector Cable](https://www.digikey.com/en/products/detail/tensility-international-corp/10-01062/3507709) | 1        | $1.93  |
| [2 Pin Terminal](https://www.digikey.com/en/products/detail/cui-devices/TB002-500-02BE/10064069)                   | 3        | $1.68  |
| [6 Pin Terminal](https://www.digikey.com/en/products/detail/cui-devices/TB003-500-P06BE/100640891)                 | 1        | $0.80  |
| [8 Pin Terminal](https://www.digikey.com/en/products/detail/cui-devices/TB001-500-08BE/10064064)                   | 1        | $1.29  |
| [10k Resistor](https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERA-6AEB103V/1465773)    | 10       | $0.99  |
| [DC to DC Converter](https://www.digikey.com/en/products/detail/gaptec-electronic/1S4E-0312S1U/13692037)           | 3        | $8.31  |
| [PCB](https://jlcpcb.com/)                                                                                         | 1        | ~$5    |
| Total (without taxes + shipping)                                                                                   |          | $49.82 |

## Notes

Some things that need to be done:
- Thermistors need to be calibrated
- Code has not been tested with the PCB yet
- PCB has not been tested yet

Some things that could be added or changed:
- Better website with websockets
- A way to save settings and not reset on power loss
- When connected to the network the control page should pop up automatically using captive portals
- Add a way for ESP32 to get power from the pump power supply
- connect the ESP32 to the lab warning system and trigger when the coils get too hot or wet