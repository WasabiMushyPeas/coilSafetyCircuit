# Coil Safety Circuit
------

## Introduction
### V1
If you would like to see the introduction and the instructions for v1 you can scroll up and read the deprecated section. This section will only cover v2

### ESP32c3 (Seeed Studio XIAO)

This project is a wireless fencing scorekeeper using the [ESP32c3 microcontroller](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html). The ESP32c3 is a low-cost, low-power microcontroller with built-in WiFi and Bluetooth. The ESP32c3 is a new chip from Espressif. The ESP32c3 is a 32-bit microcontroller with a 160 MHz clock speed, 400 KB of SRAM, and 4 KB of Flash. The ESP32c3 is a low-cost, low-power microcontroller with built-in WiFi and Bluetooth.

### Why V2?
version 2.0 of the "Wireless Fencing Scorekeeper" project eliminates the need for a fencing floor reel, body cord, and the strip end of V1's PCB.

### How?
The v2 PCB allows both sword modules to connect to each other via the [ESP-NOW](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html) protocol. This allows for touches and bell guard hits to be transmitted from one sword to the other in 10ms or less. 



# Wireless Fencing Scorekeeper using ESP32c3 :warning: **(Deprecated and Incomplete)** :warning:
------

## Introduction

### Fencing
This project is ment to replace the [body cord](https://en.wikipedia.org/wiki/Body_cord) and use of the floor reel (Ex. [Favero Floor Reel](https://www.absolutefencinggear.com/favero-floor-reel.html)) comming from the scoring box. The scoring box is a device that is used to detect when a fencer has hit their opponent. The scoring box in normal wired fencing is connected to the fencers by a body cord which in turn is connected to the fencers sword. This device plugs directly into the sword and strip transmitting a hit wirelessly from the sword to the strip. This eliminates the need for a body cord and the use of the extendable part of the floor reel. This device is also able to be used with a body cord if the user wishes to do so. 

:warning: **This device was designed only for épée**, using a different sword my require modifications to the PCB and code!

### Wireless
This project uses the [ESP-NOW](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html) protocol to transmit the hit from the sword to the strip. ESP-NOW is a protocol developed by Espressif to allow for low power wireless communication between ESP32 and ESP8266 microcontrollers. 

### PCB
This project has to PCB designs one for the sword and one for the strip. The PCBs are designed to be as small as possible to fit inside the sword and strip. They are designed to be powered by a 3.7V LiPo battery. They are also designed to be as cheap as possible to make the project as cheap as possible. The PCBs are designed in [KiCad](https://kicad.org/) and the files for both the strip end and sword end can be found [here](https://github.com/WasabiMushyPeas/FencingProject/tree/main/PCB).



## Hardware


### Parts List
parts to upgrade 1 strip

| Part | Quantity | Price |
| ---- | -------- | ----- |
| [Seeed XIAO ESP32c3](https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/113991054/16652880) | 4 | $4.99 |
| [3.7V LiPo Battery](https://www.digikey.com/en/products/detail/mikroelektronika/MIKROE-2759/7707764) | 2 | $7 |
| [PCB Strip End](https://www.pcbway.com/) | 2 | $5 |
| [PCB Sword End](https://www.pcbway.com/) | 2 | $5 |
| [3D Printed Sword End](https://www.thingiverse.com/thing:4841186) | 2 | $0 |
| [3D Printed Strip End](https://www.thingiverse.com/thing:4841186) | 2 | $0 |
| [3 LEDs (your choice)](https://www.digikey.com/en/products/filter/led-indication-discrete/105?s=N4IgjCBcpgbFoDGUBmBDANgZwKYBoQB7KAbRAGYBOcgJkpAF0CAHAFyhAGVWAnASwB2AcxABfAuTD1oIZJHTZ8RUuADs5AAywAHCAIAWVQFZt2%2BAeNmjekEbtUbR1Tv2PK%2BmtYIn1qm4ZNKPwJYMDAjchtYDX0NGiiaUy8QWBo4VwJVMDpaGzhKGPNwWAKjCAMy7XJg4oLVegJ8jW0auBaaeMaacn07PM9qyK6I7XLwT1ih8aNuouz9VNaaEv0psHJyQLyNmI1t-UpKTvAew%2BT1g8o506Dt0NU9xsHKMZo4xbyH2CzPt%2B1jsCqP6tLKHBpqSSwVxMEBsDjcfjCMQEAC08Rkcl4AFclMRIGRrAxRMSgA) | 10×3 | ≈ $1×3 |
| [100Ω resistor](https://www.digikey.com/en/products/detail/nte-electronics-inc/SR1-0805-110/11648171) | 100 | $2 |
| [1k resistor](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0805FTD1K00/2240229) | 100 | $2.97 |
| [220k resistor](https://www.digikey.com/en/products/detail/yageo/RC0805JR-07220KL/728284) | 100 | $1.20 |
| [Linear Voltage Regulator](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0805FTD1M00/2240231) | 10 | $3.18 |
| [DIP Switch](https://www.digikey.com/en/products/detail/panasonic-electronic-components/EVP-ATFAA1B54/1054589) | 5 | $6.95 |
| [Load Driver](https://www.digikey.com/en/products/detail/texas-instruments/TPS22810TDBVRQ1/8604617) | 10 | $6.32 |
| [0.1µf capacitor](https://www.digikey.com/en/products/detail/kyocera-avx/08053C104KAT2A/1116281) | 50 | $1.67 |
| [1µf capacitor](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21B105KAFNNNE/3886724) | 50 | $1.78 |
| Total | | ≈ $50 |


## Software

### Web App
see website [at](https://github.com/WasabiMushyPeas/FencingWebsite)

### Local Code
Both the strip end and sword end have local code that is used to control the LEDs and send the hit and other information to the other end. The code for both ends is written in arduino and can be found [here](https://github.com/WasabiMushyPeas/FencingProject/tree/main/Arduino/touchOverWifi/src)

:warning: **No code written in C yet**


## Installation


## Usage


## Diagrams



