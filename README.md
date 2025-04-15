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

# Dual MAX31865-with-PT100
![60055ea1-b279-4c69-9e8d-cc6507981403](https://github.com/user-attachments/assets/34ef40b7-f7c8-416c-beaa-4b92ee60cc1a)


two_pt100_3.ino is the code for dual MAX3185 with pt100.
you only need to add extra connection for chip select (MAX_CS) for another MAX3185. All other connections remain common between two MAX3185.

![Screenshot (83)](https://github.com/user-attachments/assets/87b620aa-7fc4-4aa3-826d-bffd5f502132)
