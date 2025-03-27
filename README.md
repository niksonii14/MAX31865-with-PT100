# MAX31865-with-PT100

![IMG_9642](https://github.com/user-attachments/assets/609891ca-98bd-48d7-a10d-a84689e06e8d)

I am using 3 wire connection for PT100.
In my case, this black wire is (+) and red wires are (-). please consider the image given below.
![image](https://github.com/user-attachments/assets/d8b04e5a-61e3-4c7f-9b17-a2a9129e8038)

connection:
MAX_CS → ESP32 GPIO5
MAX_MOSI → ESP32 GPIO23
MAX_MISO → ESP32 GPIO19
MAX_SCK → ESP32 GPIO18
VIN → 3.3V (Do NOT connect to 5V)
GND → GND

