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

void getIPAddress(){
    string ipAddress="Unable to get IP Address";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if(strcmp(temp_addr->ifa_name, "en0")){
                    ipAddress=inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr);
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    // Free memory
    freeifaddrs(interfaces);
    return ipAddress;
}

void main() {

	string ips = getIPAddress();

	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

	ssd1306_display(); //Adafruit logo is visible
	ssd1306_clearDisplay();
	delay(2500);

	// char text[100];
	// sprintf(text, "1306 %dx%d\ni2c driver\nwith wiringPi", WIDTH, HEIGHT);
	// ssd1306_drawString(text);
	// ssd1306_display();
	// delay(5000);

	// ssd1306_dim(1);
	// ssd1306_startscrollright(00,0xFF);
	// delay(5000);

	// ssd1306_clearDisplay();
	// ssd1306_fillRect(10,10, 50, 20, WHITE);
	// ssd1306_fillRect(80, 10, 130, 50, WHITE);
	// ssd1306_display();
	// delay(5000);

	ssd1306_clearDisplay();
	ssd1306_drawString(ips);
	ssd1306_display();
}
