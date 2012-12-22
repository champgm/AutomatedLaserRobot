// Do not remove the include below
#include "NewLaserRobot.h"
#include "SoftwareSerial.h"
#include "Servo.h"




//const int Xbounds[8] ={160,0,0,60,60,115,120,145};
//const int Ybounds[8] ={160,160,140,145,125,120,130,150};

//These are hard-coded boudnaries defined by walls and furniture onto which the laser should not project
const float Xbounds[9] ={-30,30,60,20,25,-10,-20,-20,-25};
const float Ybounds[9] ={50,50,50,100,300,300,200,70,55};

int debug=0;

Servo myservox;  //ROTATION
Servo myservoy;  //TILT

int pos = 0;    // variable to store the servo position
int ledPin=13;

int currentX=0;
int currentY=75;

float H=33.75; //height off of ground
float pi=3.14159;

float holdY=0;

//this is a method to calculate if the line drawn by the laser's current position
//and its newly (randomly) chosen position intersect with any of the lines defined
//by the hard coded boundaries. That is, if it leaves the working area.
boolean doIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
	//it is only necessary to test if numerator1/denominator and numerator2/denominator lie between 0 and 1.
	//If both lie within the range of 0 to 1 then the intersection point is on both lines

	float denominator = (y4-y3)*(x2-x1) - (x4-x3)*(y2-y1);
	float percent2=0;
	float percent1=0;
	float numerator1=0;
	float numerator2=0;
	if(debug>=3){
	Serial.print("CurrentX: ");
	Serial.println(x1);
	Serial.print("CurrentY: ");
	Serial.println(y1);
	Serial.print("NewX: ");
	Serial.println(x2);
	Serial.print("NewY: ");
	Serial.println(y2);

	Serial.print("Border1x: ");
	Serial.println(x3);
	Serial.print("Border1y: ");
	Serial.println(y3);
	Serial.print("Border2x: ");
	Serial.println(x4);
	Serial.print("Border2y: ");
	Serial.println(y4);
	}
	if(denominator!=0){
		numerator1=(x4-x3)*(y1-y3) - (y4-y3)*(x1-x3);
		numerator2=(x2-x1)*(y1-y3) - (y2-y1)*(x1-x3);
		percent1=numerator1/denominator;
		percent2=numerator2/denominator;
	}

	if (percent1<0||percent1>1){
		return false;
	}
	if(percent2<0||percent2>1){
		return false;
	}
	return true;
}
float calculateSv(float Y){
	//Can't make negative floats?
	//degrees = radians*(pi/180)
	holdY=Y;
	double Sv= 0;
	double Bv= 250.79755;
	double Mv= -1.6670657;
	float rad2deg=atan(Y/H)*(180/pi);
	float AX=rad2deg*Mv;
	Sv=AX+Bv;
	return Sv;
}
float calculateSh(float X){
	//Can't make negative floats?
	//degrees = radians*(pi/180)
	float Sh=0;
	float Bh=78.803589;
	float Mh=-2.4749512;
	float squares=sqrt(pow(X,2)+pow(holdY,2));
	float angle=asin(X/squares)*(180/pi);
	float AX=angle*Mh;
	Sh=(AX+Bh);
	return Sh;
}

boolean setRandomPosition(){
	int newX=0;
	int newY=0;
	newX=currentX-(rand()%40)+20;
	newY=currentY-(rand()%80)+40;

	for(int i=0;i<9;i++){
		int iplus1=0;
		if(i==8){
			iplus1=0;
		}else{
			iplus1=i+1;
		}
		if(doIntersect(currentX,currentY,newX,newY,Xbounds[i],Ybounds[i],Xbounds[iplus1],Ybounds[iplus1])){
			if(debug>=1){
			Serial.println("--- LINES INTERSECT");
			}
			return false;
		}
	}
	if(debug>=1){
	Serial.println("+++ LINES DO NOTINTERSECT");
	}
	if(debug>=2){
	Serial.print("CurrentX: ");
	Serial.println(currentX);
	Serial.print("CurrentY: ");
	Serial.println(currentY);
	Serial.print("NewX: ");
	Serial.println(newX);
	Serial.print("NewY: ");
	Serial.println(newY);
	Serial.print("Sv: ");
	Serial.println(calculateSv(newY));
	Serial.print("Sh: ");
	Serial.println(calculateSh(newX));
	}
	currentY=newY;
	currentX=newX;

	myservoy.write(calculateSv(newY));
	myservox.write(calculateSv(newX));

	delay(200+rand()%200);

	return true;
}

void firstLoop(){
	int delaytime=200;
	myservox.write(160);
	myservoy.write(160);
	for(int i=0;i<10;i++){
		myservox.write(160-16*i);
		myservoy.write(160);
		delay(delaytime);
	}
	for(int i=0;i<5;i++){
		myservox.write(0);
		myservoy.write(160-(i*4));
		delay(delaytime);
	}
	for(int i=0;i<5;i++){
		myservox.write(0+(i*6));
		myservoy.write(140+(i*2));
		delay(delaytime);
	}
	for(int i=0;i<5;i++){
		myservox.write(30+(i*6));
		myservoy.write(150-i);
		delay(delaytime);
	}
	for(int i=0;i<10;i++){
		myservox.write(60+(i*4));
		myservoy.write(145-i);
		delay(delaytime);
	}
	for(int i=0;i<5;i++){
		myservox.write(100-(i*4));
		myservoy.write(135-i);
		delay(delaytime);
	}
	for(int i=0;i<15;i++){
		myservox.write(80+(i*2));
		myservoy.write(130-(i*.666));
		delay(delaytime);
	}
	for(int i=0;i<5;i++){
		myservox.write(110-(i*8));
		myservoy.write(120+i);
		delay(delaytime);
	}
	for(int i=0;i<20;i++){
		myservox.write(60+(i*5));
		myservoy.write(125+(i*1.75));
		delay(delaytime);
	}
}

void loop()
{
	//firstLoop();
	setRandomPosition();
	if(debug>=2){
	delay(2000);
	}
}

void setup()
{
		Serial.begin(9600);
		myservox.attach(9);  //ROTATION
		myservoy.attach(11);  //TILT
		pinMode(ledPin, OUTPUT);
		digitalWrite(ledPin,HIGH);
		myservox.write(currentX);
		myservoy.write(currentY);

}




















