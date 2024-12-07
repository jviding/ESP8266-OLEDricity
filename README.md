# ESP8266-OLEDricity
Show electricity prices with 1.3" OLED display.

## Components

1) ESP8266-12E
2) 1.3" OLED display, 64x128
3) 0.91" OLED display, 32x128
4) 4x RGB led, common cathode
5) AMS1117 3.3V
6) 5x MOSFET, 2N7000
7) Caps (100uF elec, 10uF tantal)
8) Resistors, 10k ohm, 100ohm
9) USB breakout, with Vcc & GND
10) Prototype board, wires, connectors
11) Button

## Find RPi

\$ sudo nmap --open -sS -p 22 10.55.134.0/24

## Testing vs. production

Main.cpp includes a testing library with various tests.
Don't include it if building for prod, to save memory.

## Flash

Using USB:
\$ esptool.py --chip esp8266 --port /dev/ttyUSB0 write_flash -z 0x00000 firmware.bin

Using Serial:
\$ esptool.py --chip esp8266 --port /dev/ttyS0 write_flash -z 0x00000 firmware.bin

Serial pins (ESP8266 to RPi):
1) Vcc    - 3.3V
2) GND    - GND
3) U0TXD  - RX
4) U0RXD  - TX
5) EN     - Pull-up 10k
6) GPIO15 - Pull-down 10k
7) GPIO0  - Pull-down 10k

For normal boot operation, switch GPIO0 to Pull-up 10k.

## Debug

Listen for Serial:
\$ minicom -D /dev/ttyACM0 -b 115200

## Pins

ESP8266:
1) I2C (Display comm.)
- SCL = GPIO5 (D1)
- SDA = GPIO4 (D2)
2) Display ctrl
- pinBanner = GPIO0 (D3)
- pinChart  = GPIO2 (D4)
3) Led ctrl
- red   = GPIO16 (D0)
- green = GPIO14 (D5)
- blue  = GPIO12 (D6)
4) Button
- button = GPIO13 (D7)

Note 1: Connect display SCL to MOSFET drain.
Master I2C transmits by pulling signal down.

Note 2: Add 10k pull-up for display SCL.
Prevent floating while MOSFET is closed.

Note 3: Program assumes an N-channel MOSFET.
Tested with 2N700 during development.


## Further development

ToDo:
- Enable joining a WiFi that is not password protected
- Check Banner shows negative prices correct
- POST response, layout?
- Disconnect from WiFi for duration of wait

Ideas:
- Chart: Follow actual price with the Y-horizontal?
- Banner: Toggle Day Average, time now, or similar?
- Show errors and/or codes on displays?
- Allow changing API endpoint? (Store to EEPROM)
- Enable software updates, from remote?

3D model:
- Narrow Banner (and Chart?) gap 0.5mm both sides
