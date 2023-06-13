#include <Servo.h>
/*
  NERF GUN SENTRY TURRET:
    *property of kang records*

  INSTRUCTIONS:
    LEDS:
      armed led : ~10
      trigger led : ~11
    TRIGGERSERVO:
      Y : ~9
      R : 5V
      Br: GND
    MOTORSERVO
      Y : ~5
      R : 5V
      Br: GND
    ROTATIONSERVO
      Y : ~3
      R : 5V
      Br: GND


*/
Servo servo;
Servo servo2;
Servo servo3;

//LEDS
int armedLED = 10;
int triggerLED = 11;
//SERVOS
int triggerServo = 9;
int motorServo = 4;
int rotationServo = 3;
//direction
int currentRotation = 90;



// code to extract String of data from P5JS
const char marker = '\n';  //This is the end of message marker
char serialbuf[32];        //This gives the incoming serial some room. Change it if you want a longer incoming.

int val01;
int val02;


//Code to delay trigger without delay
int triggerArmed = 0;
// constants won't change. Used here to set a pin number:
//const int ledPin =  LED_BUILTIN;// the number of the LED pin
// Variables will change:
int trigger2State = 0;  // triggerState used to set the 2nd trigger
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated
// constants won't change:
const long interval = 1700;  // interval at which to blink (milliseconds)

void setup() {
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(triggerServo, OUTPUT);
  pinMode(motorServo, OUTPUT);
  pinMode(rotationServo, OUTPUT);

  servo.attach(triggerServo);
  servo2.attach(motorServo);
  servo3.attach(rotationServo);

  //led test
  analogWrite(triggerLED, 255);  //10 written with 255
  analogWrite(armedLED, 255);
  delay(1000);
  analogWrite(triggerLED, 0);
  analogWrite(armedLED, 0);

  //face straight ahead
  //servo3.write(0);

  servo2.write(0);
  servo.write(100);
}

void loop() {
  //3
  delay(1000);
  analogWrite(triggerLED, 0);  //RED
  servo.write(100);            //reset trigger
  servo2.write(0);             //reset motor
  servo3.write(0);             //spin

  //S1
  delay(5000);
  analogWrite(triggerLED, 255);  //RED
  servo2.write(100);             //motor shoot
  servo3.write(20);              //spin

  //2
  delay(2000);
  servo.write(0);  //trigger shoot
}
