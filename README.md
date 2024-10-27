# ESP8266-OLEDricity
Show electricity prices with 1.3" OLED display.


## Flashing

Find RPi:
\$ sudo nmap --open -sS -p 22 10.55.134.0/24

USB:
\$ esptool.py --chip esp8266 --port /dev/ttyUSB0 write_flash -z 0x00000 firmware.bin

Serial:
\$ esptool.py --chip esp8266 --port /dev/ttyS0 write_flash -z 0x00000 firmware.bin

Serial pins:

RPi   -   ESP8266

3.3V  -   Vcc
GND   -   GND
RX    -   U0TXD
TX    -   U0RXD
      -   EN      (pull-up 10k)
      -   GPIO 15 (pull-down 10k)
      -   GPIO 0  (pull-down 10k)
      
For normal boot operation, switch GPIO 0 to pull-up.
