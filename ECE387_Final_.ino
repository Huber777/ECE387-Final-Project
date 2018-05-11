//count down
int start= 14;
int hours=15;
int minutes=16;
int seconds=17;
int pressure=22;
int timing=26;
int hourcount=0;
int mincount=0;
int secondcount=0;
long totalTime=0;
int displayHour=0;
int displayMin=0;
int displaySec=0;
int lastTime=0;
int currentTime=0;
int timeD=0;
int de1=0;
int de2=0;
int de3=0;
int de4=0;
int de5=0;
int de6=0;
int yali=0;
int jishi=0;
//int de9=0;
int dehour=0;
int demin=0;
int desec=0;
int switchs=1;

//initail force sensor value
int FSR = 0;
//initail feed quantity value
int feedQty = 0;

//Include LCD library
#include <LiquidCrystal.h>
//Include Stepper motor library
#include <Stepper.h>

//initailize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 13, 5 , 4, 3, 2);

// change this to fit the number of steps per revolution for your motor
const int stepsPerRevolution = 64;  

// initialize the stepper library on pins 8 through 11:
int in1Pin = 8;
int in2Pin = 9;
int in3Pin = 10;
int in4Pin = 11;
Stepper myStepper(stepsPerRevolution,in1Pin, in2Pin, in3Pin, in4Pin);

void setup() {
  //set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  //print a message to the LCD.
  lcd.setCursor(1,0);
  lcd.print("QTY:");
   // set the speed at 100 rpm:
  myStepper.setSpeed(100);
  // initialize the serial port:
  Serial.begin(9600);
  // set the force resistor pin:
  pinMode(7, OUTPUT);
  // button
  pinMode(start, INPUT);
  pinMode(hours, INPUT);
  pinMode(minutes, INPUT);
  pinMode(seconds,INPUT);
  pinMode(pressure,INPUT);
  pinMode(timing,INPUT);
  yali=digitalRead(pressure);
  jishi=digitalRead(timing);
  while (yali==0&&jishi==0)
  {
  yali=digitalRead(pressure);
  jishi=digitalRead(timing);
    }
}

void loop() {
 /* yali=digitalRead(pressure);
  jishi=digitalRead(timing);
  while (yali==0&&jishi==0)
  {
  yali=digitalRead(pressure);
  jishi=digitalRead(timing);
    }
 */

  if (jishi==1)
  {  Serial.print("countdown");
  while (digitalRead(start)==0)
{
  de1=digitalRead(hours);
  delay(50);
  de2=digitalRead(hours);
  if (de1=de2)
  {
    dehour=de1;
    }
    else
    {
      dehour=0;
      }
  if (dehour==1)
  {hourcount=hourcount+1;
    lcd.setCursor(4,1);
    lcd.print(hourcount);
    lcd.setCursor(6,1);
    lcd.print(":");
  }
  de3=digitalRead(minutes);
  delay(50);
  de4=digitalRead(minutes);
  if (de3=de4)
  {
    demin=de3;
    }
    else
    {
      demin=0;
      }
   if (demin==1)
  {mincount=mincount+1;
    lcd.setCursor(7,1);
    lcd.print(mincount);
    lcd.setCursor(9,1);
    lcd.print(":");
  }
  de5=digitalRead(seconds);
  delay(50);
  de6=digitalRead(seconds);
  if (de5=de6)
  {
    desec=de5;
    }
    else
    {
      desec=0;
      }
  if (desec==1)
  {secondcount=secondcount+1;
   lcd.setCursor(10,1);
   lcd.print(secondcount);
  } 
  } 
  totalTime = secondcount*1+mincount*60+hourcount*60*60+1;
  Serial.println(totalTime);
  while (totalTime>0)
  {
    /*lastTime=currentTime;
    currentTime=millis();
    timeD=currentTime-lastTime;
    if (timeD>1000)
    {
    totalTime =totalTime-1;
    }
    */
     totalTime =totalTime-1;
    displayHour=totalTime/3600;
    displayMin=(totalTime%3600)/60;
    displaySec=((totalTime%3600)%60);
//    Serial.print (displayHour);
//    Serial.print (":");
//    Serial.print (displayMin);
//    Serial.print (":");
//    Serial.println (displaySec);
    delay(1000);
    
    //LCD
    lcd.setCursor(4,1);
    lcd.print(displayHour);
    lcd.setCursor(6,1);
    lcd.print(":");
    lcd.setCursor(7,1);
    lcd.print(displayMin);
    lcd.setCursor(9,1);
    lcd.print(":");
    lcd.setCursor(10,1);
    lcd.print(displaySec);
    }

  //
  myStepper.step(stepsPerRevolution*50);
  delay(500);
  }

  
  
  
if(yali==1)
{

//midterm
Serial.println("pressure");
int FSRValue = analogRead(FSR);



  Serial.println(FSRValue);
  delay(1000);
  if (FSRValue>50){
  //  Serial.print("aaa");
    digitalWrite(7,HIGH);
    //count the feedQty
    feedQty++;
     // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution*20);
  delay(100);
  //set the cursor to colum 0,line 1
  //(note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(6, 0);
  //Print a message to second line of LCD
  lcd.print(feedQty);

  
  }
  else
  {
  //no force on the sensor, the light goes off 
  //and the stepper motor stop rotate
  digitalWrite(7,LOW);
  myStepper.step(0);
  }
}
  }

