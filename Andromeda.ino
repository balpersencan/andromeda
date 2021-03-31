int stepsPerRevolution = 800;
#include <SoftwareSerial.h>
// Include the AccelStepper Library
#include <AccelStepper.h>
#define motorInterfaceType 1
AccelStepper stepper1 = AccelStepper(motorInterfaceType, 2, 3);
SoftwareSerial HM10(8, 9); // RX = 8, TX = 9
char appData;  
String inData = "";
String Motoronoff = "";
void setup()
{
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  pinMode(2, OUTPUT); // dir 
  pinMode(3, OUTPUT); // Step
  pinMode(4, OUTPUT); // MC0
  pinMode(5, OUTPUT); // MC1
  pinMode(6, OUTPUT); // MC2
  pinMode(7, OUTPUT); // Lazer
  pinMode(10, OUTPUT); // Shutter
  pinMode(11, OUTPUT); // Autofocus
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);  
  digitalWrite(7, LOW); // Lzr off
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  stepper1.setMaxSpeed(200);
  stepper1.setSpeed(200 );
  
}


void loop()
{
  HM10.listen();  // listen the HM10 port
  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    Serial.write(appData);
  }

 
  if (Serial.available()) {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }
  if ( inData == "K") {
    Serial.println("LED OFF");
    digitalWrite(7, LOW); // switch OFF LED
    delay(0);
     inData="";
     if ( Motoronoff == "E") {
    goto Motor;
  }
  }
  if ( inData == "L") {
    Serial.println("LED ON");
    digitalWrite(7, HIGH); // switch OFF LED
    delay(0);
     inData="";
 if ( Motoronoff == "E") {
    goto Motor;
  }
  }
  
  if ( inData == "M") {
   Motor:
   Motoronoff="E";
   HM10.println("M");
  Serial.println("Motor On");
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
   
  stepper1.runSpeed();

  // Step the motor with a constant speed as set by setSpeed():

  
  Serial.println(String(inData));//Write out the assembled command
  if ( inData == "F") {
    Serial.println("Focusing");
     
  digitalWrite(11, HIGH);

    delay(1000);
     inData="";
      digitalWrite(11, LOW);
         if ( Motoronoff == "E") {
    goto Motor;
  
  }
  }
    if ( inData == "S") {
    Serial.println("Shutter On");
     
  digitalWrite(10, HIGH);

    delay(100);
     inData="";
      digitalWrite(10, LOW);
      if ( Motoronoff == "E") {
    goto Motor;
  }
  }
    inData="M";
  }
// Döngü Başı
  if ( inData == "N") {
    Serial.println("Motor Off ");
     
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(3, LOW);
    delay(0);
     inData="";
     Motoronoff="H";
   
  }
  //Döngü Sonu
  // Döngü Başı


  //Döngü Sonu

    // Döngü Başı
  

  //Döngü Sonu
}
