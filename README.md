# ESP8266-OLEDricity
Show electricity prices with 1.3" OLED display.


# Find RPi
sudo nmap --open -sS -p 22 10.55.134.0/24

# Flash from RPi
esptool.py --chip esp8266 --port /dev/ttyS0 write_flash -z 0x00000 firmware.bin

# Listen from RPi
minicom -D /dev/ttyACM0 -b 115200

