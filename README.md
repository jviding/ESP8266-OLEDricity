# ESP8266-OLEDricity
Show electricity prices with 1.3" OLED display.

## Find RPi

\$ sudo nmap --open -sS -p 22 10.55.134.0/24

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

ESP8266 NodeMCUv2:
1) Wire / I2C
- SCL = D1 / GPIO5
- SDA = D2 / GPIO4
2) Display ctrl
- pinBanner = D5 / GPIO14
- pinChart  = D0 / GPIO16
