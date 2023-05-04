SSD1306 i2c driver for wiringPi
-----------------------------------

Based on Adafruit SSD1306 Arduino library. Some functions came from Adafruit GF$

Tested on Banana Pi M5(BPI S905x3) with 0.42 White OLED

Required WiringPi http://wiringpi.com/ and WiringPi i2c lib. 

How to run demo:
gcc -g demo.c ssd1306_i2c.c -lwiringPi -o demo -lpthread -lrt -lm -lcrypt 

./demo

