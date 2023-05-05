/******
Demo for ssd1306 i2c driver for  Raspberry Pi 
******/

#include "ssd1306_i2c.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

void main() {

	int n;
    struct ifreq ifr;
    char array[] = "eth0";
 
    n = socket(AF_INET, SOCK_DGRAM, 0);
    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);

	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

	ssd1306_display(); //Adafruit logo is visible
	ssd1306_clearDisplay();
	delay(5000);

	char text[100];
	sprintf(text, "1306 %dx%d\ni2c driver\nwith wiringPi", WIDTH, HEIGHT);
	ssd1306_drawString(text);
	ssd1306_display();
	delay(5000);

	// ssd1306_dim(1);
	// ssd1306_startscrollright(00,0xFF);
	// delay(5000);

	// ssd1306_clearDisplay();
	// ssd1306_fillRect(10,10, 50, 20, WHITE);
	// ssd1306_fillRect(80, 10, 130, 50, WHITE);
	// ssd1306_display();
	// delay(5000);

	ssd1306_clearDisplay();
	ssd1306_drawString("IP Address is %s - %s\n" , array , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr));
	ssd1306_display();
}
