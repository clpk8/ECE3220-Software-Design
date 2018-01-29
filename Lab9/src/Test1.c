/* ECE3220 Lab9_example.c
 * Author: Luis Rivera
 *
 * This program shows how to use wiringPi on the Raspberri Pi 3 to turn on and off
 * an LED on the auxiliary board.

  Compile using -lwiringPi
	gcc Lab9_example.c -o Lab9_example -lwiringPi
		or
	add wiringPi to the linker (-l), if using Eclipse
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// standard symbolic constants and types (e.g. NULL); usleep
#include <wiringPi.h>	// needed for the wiringPi functions


#define LED1  8		// wiringPi number corresponding to GPIO2.
					//Check Figures 2 and 3 in the Lab9 guide.
#define LED2  9 //yellow
#define LED3  7 //green
#define LED4  21//blue
#define P1    27
#define P2    0
#define P3    1

int main(int argc, char **argv)
{
	wiringPiSetup();	// wiringPiSetupGpio() could be used. The numbers for the ports would
						// need to match the RPi GPIO pinout.

	pinMode(LED1, OUTPUT);	// Configure GPIO2, which is the one connected to the red LED.
	pinMode(LED2, OUTPUT);	// Configure GPIO2, which is the one connected to the red LED.
	pinMode(LED3, OUTPUT);	// Configure GPIO2, which is the one connected to the red LED.
	pinMode(LED4, OUTPUT);	// Configure GPIO2, which is the one connected to the red LED.
	pinMode(P1, INPUT);
	pinMode(P2, INPUT);
	pinMode(P3, INPUT);
	int choice;
	int i = 0;
	do{
    			digitalWrite(LED1, LOW);
    			digitalWrite(LED2, LOW);
    			digitalWrite(LED3, LOW);
    			digitalWrite(LED4, LOW);
		if(digitalRead(P1) == 1){
			choice = 1;
			}
		else if(digitalRead(P2) == 1){
			choice = 2;
			}
		else{
			choice = 3;
		}


		switch(choice){
			case 1:{
				while(1){
						digitalWrite(LED1, HIGH);
						digitalWrite(LED2, HIGH);
						sleep(1);
						digitalWrite(LED1, LOW);
						digitalWrite(LED2, LOW);
						digitalWrite(LED3, HIGH);
						digitalWrite(LED4, HIGH);
						sleep(1);
						digitalWrite(LED3, LOW);
						digitalWrite(LED4, LOW);

				}

				break;
			}
			case 2:{
				digitalWrite(LED3, HIGH);
				digitalWrite(LED4, HIGH);
				break;
			}
			case 3:{
			digitalWrite(LED1, HIGH);
			digitalWrite(LED2, HIGH);
			digitalWrite(LED3, HIGH);
			digitalWrite(LED4, HIGH);
			break;
			}
			default:{
				digitalWrite(LED1, LOW);
	    		digitalWrite(LED2, LOW);
	    		digitalWrite(LED3, LOW);
	    		digitalWrite(LED4, LOW);
	    		break;
			}

		}
	}while(digitalRead(P3) == 0);

    return 0;
}


