
//Completed by Max Salgannik, Phine Kim, Yolmorakatpanhcharong Lim
#include <Wire.h>
#define ENABLE 5
#define DIRA 3
#define DIRB 4
#include <LiquidCrystal.h>
#include <DS3232RTC.h>

// initialize the library with the numbers of the interface pins
DS3232RTC myRTC;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define buttonpin 2
int i;
volatile byte dirFlag=LOW;


void setup() {
  
myRTC.begin();
setSyncProvider(myRTC.get);
    if(timeStatus() != timeSet)
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time");
//---set pin direction
lcd.begin(16, 2);
pinMode(ENABLE,OUTPUT);
pinMode(DIRA,OUTPUT);
pinMode(DIRB,OUTPUT);
pinMode(buttonpin, INPUT_PULLUP);
Serial.begin(9600);
attachInterrupt (digitalPinToInterrupt(buttonpin), directFan, RISING);
}

void loop() {
setSyncProvider(myRTC.get);
lcd.setCursor(0,1);

while (second() <= 30)
{
  SpinFan();
}
while (second() >= 30)
{
   analogWrite(ENABLE,0); //0 speed
  lcd.print("TIME: ");
  lcd.print(hour(), DEC);
    printDigits(minute());
    printDigits(second());
lcd.setCursor(0,2);
lcd.print("Fan Off");
delay(1000);
lcd.clear();

}
}

void SpinFan(){
//---PWM example, full speed then slow, CW
while (second() >= 0 && second() <= 5)
{
  digitalWrite(DIRA,dirFlag); //one way
digitalWrite(DIRB,!dirFlag);
  analogWrite(ENABLE,255); //enable on
  lcd.print("TIME: ");
lcd.print(hour(), DEC);
    printDigits(minute());
    printDigits(second());
lcd.setCursor(0,2);
lcd.print("Speed: Full  ");

  if (dirFlag == LOW && !dirFlag == HIGH) {

lcd.print("CW");

}
else if (dirFlag == HIGH && !dirFlag == LOW){
lcd.print("CCW");
}
delay(1000);
lcd.clear();
}
while (second() > 5 && second() <= 10)
{
  digitalWrite(DIRA,dirFlag); //one way
digitalWrite(DIRB,!dirFlag);
  analogWrite(ENABLE,180); //3/4 speed
  lcd.print("TIME: ");
lcd.print(hour(), DEC);
    printDigits(minute());
    printDigits(second());


lcd.setCursor(0,2);
lcd.print("Speed: 3/4  ");

  if (dirFlag == LOW && !dirFlag == HIGH) {

lcd.print("CW");

}
else if (dirFlag == HIGH && !dirFlag == LOW){
lcd.print("CCW");
}
delay(1000);
lcd.clear();


}
while (second() > 10 && second() <= 15)
{
  digitalWrite(DIRA,dirFlag); //one way
digitalWrite(DIRB,!dirFlag);
  analogWrite(ENABLE,128); //half speed
  lcd.print("TIME: ");
lcd.print(hour(), DEC);
    printDigits(minute());
    printDigits(second());



lcd.setCursor(0,2);
lcd.print("Speed: 1/2  ");
if (dirFlag == LOW && !dirFlag == HIGH) {

lcd.print("CW");

}
else if (dirFlag == HIGH && !dirFlag == LOW){
lcd.print("CCW");
}
delay(1000);
lcd.clear();

}
while (second() > 15 && second() <= 20)
{
  digitalWrite(DIRA,dirFlag); //one way
digitalWrite(DIRB,!dirFlag);
  analogWrite(ENABLE,0); //0 speed
  lcd.print("TIME: ");
lcd.print(hour(), DEC);
    printDigits(minute());
    printDigits(second());


 
lcd.setCursor(0,2);
lcd.print("Speed: 0  ");
 if (dirFlag == LOW && !dirFlag == HIGH) {

lcd.print("CW");

}
else if (dirFlag == HIGH && !dirFlag == LOW){
lcd.print("CCW");
}
delay(1000);
lcd.clear();

}
while (second() > 20 && second() <= 25)
{
  digitalWrite(DIRA,dirFlag); //one way
digitalWrite(DIRB,!dirFlag);
  analogWrite(ENABLE,128); //half speed
  lcd.print("TIME: ");
lcd.print(hour(), DEC);
lcd.print(":");
    printDigits(minute());
    printDigits(second());

 
lcd.setCursor(0,2);
lcd.print("Speed: 1/2  ");
if (dirFlag == LOW && !dirFlag == HIGH) {

lcd.print("CW");

}
else if (dirFlag == HIGH && !dirFlag == LOW){
lcd.print("CCW");
}
delay(1000);
lcd.clear();

}
while (second() > 25 && second() <= 30)
{
  digitalWrite(DIRA,dirFlag); //one way
digitalWrite(DIRB,!dirFlag);
  analogWrite(ENABLE,180); //3/4 speed 
  lcd.print("TIME: ");
lcd.print(hour(), DEC);
    printDigits(minute());
    printDigits(second());


lcd.setCursor(0,2);
lcd.print("Speed: 3/4  ");
  if (dirFlag == LOW && !dirFlag == HIGH) {

lcd.print("CW");

}
else if (dirFlag == HIGH && !dirFlag == LOW){
lcd.print("CCW");
}
delay(1000);
lcd.clear();

}
}
void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    lcd.print(':');
    if(digits < 10)
        lcd.print('0');
    lcd.print(digits);
}
void directFan () {
  dirFlag = !dirFlag;
  }
