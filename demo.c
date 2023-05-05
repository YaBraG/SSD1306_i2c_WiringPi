/******
Demo for ssd1306 i2c driver for  Raspberry Pi 
******/

#include "ssd1306_i2c.h"

#include <stdio.h>

#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>



void main() {

	 int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;
    
    /* I want IP address attached to "eth0" */
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
    
    ioctl(fd, SIOCGIFADDR, &ifr);
    
    close(fd);
    

	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

	ssd1306_display(); //Adafruit logo is visible
	ssd1306_clearDisplay();
	delay(1000);

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
	ssd1306_drawString(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	ssd1306_display();
}
