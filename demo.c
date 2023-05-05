/******
Demo for ssd1306 i2c driver for  Raspberry Pi 
******/

#include "ssd1306_i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Returns hostname for the local computer
void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

void checkHostEntry(struct hostent * hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}

// Converts space-delimited IPv4 addresses
// to dotted-decimal format
void checkIPbuffer(char *IPbuffer)
{
    if (NULL == IPbuffer)
    {
        perror("inet_ntoa");
        exit(1);
    }
}

void main() {

	char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;
 
    // To retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);
 
    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);
 
    // To convert an Internet network
    // address into ASCII string
    IPbuffer = inet_ntoa(*((struct in_addr*)
                        host_entry->h_addr_list[0]));

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
	ssd1306_drawString(IPbuffer);
	ssd1306_display();
}
