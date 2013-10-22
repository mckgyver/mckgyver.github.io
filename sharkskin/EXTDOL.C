//Michael McKinley
//Senior Honors Thesis
//UMASS AMHERST May 2009

//EXTDOL
//Open Loop Extruder
//This program is designed to control heater pins on a plastic extruder die
//
//Output: UMASS (as defined below)
//esc key exits the program



#include <stdio.h>
#include <conio.h>
#include <bios.h>


#define ESCAPE_KEY 0x011b
void quit_pgm(void)
{
 exit(0);
}

void U();
void M();
void A();
void S();

int port=0x378;
int choice=2;
int holdTime=100;
int repeats=1;

void SelPort()  //set the parallel port address
{
	clrscr();
	printf("SELECT P-Port Address\n");
	printf("1-0x3bc (956), 2-0x378 (888), 3-0x278 (632)\n");
	printf("Current: %d\n",port);

	choice=toupper(getch());
	if(choice=='1') port=0x3bc;
	if(choice=='2') port=0x378;
	if(choice=='3') port=0x278;
	if(choice<'1' || choice>'3')
	{
		printf("\n \n INVALID SELECTION \n port address unchanged");
		delay(2000);
	}


	printf("\n Set Pixel Length (>=1ms) Current:100ms \n");
	scanf("%d",&holdTime);
	printf("\n Repeats? (>=1) \n");
	scanf("%d",&repeats);

}
int i=0;

int pin3;  int pin2;  int pin1;
char surf3; char surf2; char surf1;
char edgeSurf=176;

long duty=50;
long ontime;
long offtime;

int output=0;
int pixelLength;
//long holdTime=10; //defined above
int h=0;

void print(pin3,pin2,pin1,pixelLength)         //on screen graphic of print sequence
{
	while(h<pixelLength)
	{
		i++;
		output=(pin3*4)+(pin2*2)+(pin1*1);
		outportb(port,output);
		if(pin3>0) surf3=255; else surf3=176;
		if(pin2>0) surf2=255; else surf2=176;
		if(pin1>0) surf1=255; else surf1=176;

		printf("\n%5d  %c%c%c%c%c  %d",i,edgeSurf,surf1,surf2,surf3,edgeSurf,output);
		ontime=(duty%100)*holdTime;
		offtime=holdTime-ontime;
		printf(" %5d %5d %d %d",duty,holdTime,ontime,offtime);
		delay(ontime);
		outportb(port,0);
		//delay(offtime);
		h++;
	}
	h=0;
}

void endr()
{
if(bioskey(1))
		{
			switch(bioskey(0))
			{
				case ESCAPE_KEY:quit_pgm();
				default:break;
			}
		}
}

int repeat=1; //select # of times to repeat text output
void main()
{
	clrscr();
	SelPort();
	while (repeat<=repeats)
	{
	endr();
	U();
	endr();
	M();
	endr();
	A();
	endr();
	S();
	endr();
	S();
	endr();
	repeat++;
	}
	getch();
}

void U()
{
	print(1,1,1,2);
	print(0,0,1,2);
	print(1,1,1,2);
	print(0,0,0,2);

}

void M()
{
	print(0,0,1,1);
	print(0,1,1,1);
	print(1,1,0,1);
	print(1,0,0,1);
	print(0,1,0,2);
	print(1,0,0,1);
	print(1,1,0,1);
	print(0,1,1,1);
	print(0,0,1,1);
	print(0,0,0,2);
}

void A()
{
	print(0,0,1,1);
	print(0,1,1,1);
	print(1,1,0,1);
	print(1,0,0,2);
	print(1,1,0,1);
	print(0,1,1,1);
	print(0,0,1,1);
	print(0,0,0,2);
}

void S()
{
	print(0,0,1,2);
	print(1,1,1,2);
	print(1,0,0,2);
	print(0,0,0,2);
}