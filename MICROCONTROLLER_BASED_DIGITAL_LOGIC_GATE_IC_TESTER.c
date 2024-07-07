#include <reg51.h>

sbit RS = P3^2;
sbit rw = P3^3;
sbit EN = P3^4;

void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdstring(unsigned char S[]);
void delay(unsigned int);
void orgg(); 
void andg();
void nandg();
void exorg();
void norg();
void notg();
void good();
void bad();


void main(void) {
    lcdcmd(0x38); // Initialize LCD
	delay(10);
    lcdcmd(0x0F);
	delay(10);
    lcdcmd(0x01);
	delay(10);
    lcdcmd(0x81);
	delay(10);
	
    lcdstring("WELCOME TO IC..");
    lcdcmd(0xC0);
    lcdstring("TESTING PROGRAM");
    delay(100);

    lcdcmd(0x01);
    lcdcmd(0x80);
    //lcdstring("Testing OR gate IC");
    //delay(250); // Wait for 1 second
    orgg(); // Test OR gate IC
	  delay(250);
		andg();
		delay(250);
		nandg();
		delay(250);
		exorg();
		delay(250);
		norg();
		delay(250);
		notg();
		delay(250);
}


void nandg()
{
 unsigned char i, a=0,in[]={0x00,0x0F,0xF0,0xFF}, y1[4], 
   y3[]={0x0F,0x0F,0x0F,0x00};
P1=0x0f;
 for(i=0;i<4;i++) 
 { P0=in[i]; 
  y1[i]=P1;
  if (y1[i]!=y3[i]) 
  break;
  a++;
 }
 lcdcmd(0x01);
 lcdcmd(0x80);
 lcdstring("IC 7400");
 if (a==4)
  good();
 else
  bad();
}

void exorg()
{ unsigned char i, a=0,in[]={0x00,0x0F,0xF0,0xFF}, y1[4], 
   y3[]={0x00,0x0F,0x0F,0x00};
P1=0x0f;
 for(i=0;i<4;i++) 
 { P0=in[i];
  y1[i]=P1;
  if (y1[i]!=y3[i]) 
  break;
  a++; 
}
 lcdcmd(0x01);
 lcdcmd(0x80);
 lcdstring("IC 7486");
 if (a==4)
  good();
 else
  bad(); 
}


void orgg() {
    unsigned char i, a=0, in[]={0x00, 0x0F, 0xF0, 0xFF},y1[4],y3[]={0x00, 0x0F, 0x0F, 0x0F};
    P1=0x0F;
		//P1=0x00;

    for(i = 0; i < 4; i++) {
        P0 = in[i]; // Inputs to OR gate
			  delay(1000);
			  
        y1[i] = P1;
			  delay(1000);

        if(y1[i] != y3[i]) 
            break;
        a++; 
    }

    lcdcmd(0x01);
    lcdcmd(0x80);
    lcdstring("IC 7432"); // Display IC number

    if(a == 4)
        good(); // Display "Good!! IC is OK"
    else
        bad(); // Display "Sorry!! BAD IC"
}

void andg()
{
 unsigned char i , a=0, in[]={0x00,0x0F,0xF0,0xFF}, y1[4], 
   y3[]={0x00,0x00,0x00,0x0F};
P1=0x0f;
 for(i=0;i<4;i++) 
 {
  P0=in[i];//inputs to AND gate
  y1[i]=P1;
  if (y1[i]!=y3[i]) 
  break;
  a++;
 }
lcdcmd(0x01);
 lcdcmd(0x80);
 lcdstring("IC 7408");
 if (a==4)
  good();
 else
  bad();
}



void good() {
    lcdcmd(0xC0);
    lcdstring("Good");
}

void bad() {
    lcdcmd(0xC0);
    lcdstring("Bad");
}

void lcdcmd(unsigned char value) {
    P2 = value;
    RS = 0;
    rw = 0;
    EN = 1;
	  delay(1);
    EN = 0;
}

void lcddata(unsigned char value) {
    P2 = value;
    RS = 1;
    rw = 0;
    EN = 1;
    delay(5);
    EN = 0;
}

void lcdstring(unsigned char *S) {
    while(*S){
			lcddata(*S++);
			delay(50);
		}
		
        
	/*int l=0;
		while(S[l] != '\0') // searching the null terminator in the sentence
    {
        lcddata(S[l]);
        l++;
        delay(50);
    }*/
}

void delay(unsigned int t) {
    unsigned int i, j;
    for(i = 0; i < t; i++)
        for(j = 0; j < 1275; j++);
}

void norg(){ 
	unsigned char a=0;
	unsigned char b=0;
	lcdcmd(0x01);
	lcdcmd(0x80);
	lcdstring("IC 7402");
	 //P0=0xFF;// B inputs to NOR gate
 //P1=0x0F;// A inputs to NOR gate
	/*P0^0=1;
	P0^1=1;
	P0^2=1;
	P0^3=1;
	P0^4=0;
	P0^5=0;
	P0^6=0;
	P0^7=0;
	P1^0=0;
	P1^1=0;
	P1^2=0;
	P1^3=0;*/
	P1=0x00;
	P0=0x0F;
	delay(250);
	a=P0;
	if (a==0x0F){
		b=b+1;
	}
	/*P1^0=1;
	P1^1=1;
	P1^2=1;
	P1^3=1;*/
	P1=0x0F;
	delay(250);
	a=P0;
	if (a==0x00){
		b=b+1;
	}
	/*P0^4=1;
	P0^5=1;
	P0^6=1;
	P0^7=1;*/
	P0=0xFF;
	delay(250);
	a=P0;
	if (a==0xF0){
		b=b+1;
	}
	/*P1^0=0;
	P1^1=0;
	P1^2=0;
	P1^3=0;*/
	P1=0x00;
	delay(250);
	a=P0;
	if (a==0xF0){
		b=b+1;
	}
	lcdcmd(0x01);
  lcdcmd(0x80);
  lcdstring("IC 7402"); // Display IC number
	if(b==4){
		good();
	}else{
		bad();
	}
}
void notg()
{ 
 unsigned char a=0;

  P0=0x5A;
  P1=0x05;
  delay(250);
  if (P0==0x5A && P1==0x05){
	a++;
   }
  P0=~P0;
  P1=~P1;
  delay(250);
  if (P0==0xA5 && P1==0xAF){
	a++;
   }
  
  lcdcmd(0x01);
  lcdcmd(0x80);
  lcdstring("IC 7404");
  if (a==2)
   good();
  else
   bad(); 
}