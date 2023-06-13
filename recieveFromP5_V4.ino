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
const char marker = '\n'; //This is the end of message marker
char serialbuf[32]; //This gives the incoming serial some room. Change it if you want a longer incoming.

int val01;
int val02;


//Code to delay trigger without delay
int triggerArmed= 0;
// constants won't change. Used here to set a pin number:
//const int ledPin =  LED_BUILTIN;// the number of the LED pin
// Variables will change:
int trigger2State = 0;             // triggerState used to set the 2nd trigger
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change:
const long interval = 1700;           // interval at which to blink (milliseconds)

void setup() {
  Serial.begin(57600);
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
  servo3.write(90);

  servo2.write(0);
  servo.write(100);

}

void loop() {
  // Read serial input:
  if (Serial.available() > 0) {
    static int bufpos = 0; //starts the buffer back at the first position in the incoming serial.read
    char inchar = Serial.read(); //assigns one byte (as serial.read()'s only input one byte at a time
    if (inchar != marker) { //if the incoming character is not the byte that is the incoming end marker
      serialbuf[bufpos] = inchar; //the buffer position in the array get assigned to the current read
      bufpos++; //once that has happend the buffer advances, doing this over and over again until the end of package marker is read.
    }

    else { //once the end of package marker has been read
      serialbuf[bufpos] = 0; //restart the buff
      bufpos = 0; //restart the position of the buff
      int val01 = atoi(subStr(serialbuf, ",", 1)); // recieve the 1st value and convert it to integer
      int val02 = atoi(subStr(serialbuf, ",", 2));
     
      //Output message

      if (val01 == 1 ){ ///ONTARGET
        analogWrite(armedLED, 0);
        analogWrite(triggerLED, 255);  //RED

        delay(40);
        servo2.write(100);//motorpower srvo
        delay(40);

        triggerArmed= 1;

      } else if (val01 == 0 ){ ///OFFTARGET
        analogWrite(armedLED, 255); //YELLOW
        analogWrite(triggerLED, 0);
        

        //servo.write(100); //Trigger unarmed
        delay(40);
        servo2.write(0);//motorpower srvo
        delay(40);

        triggerArmed= 0;

      }
      
      //ROTATION CORRECTION
      if (val02 > 20){
        delay(20);
        currentRotation = currentRotation +10;
         servo3.write(currentRotation);
         delay(80);
      }
      if (val02 < -20){
        delay(20);
        currentRotation = currentRotation -10;
        servo3.write(currentRotation);
        delay(80);
      }
      //}
      
    //below is for servo
    }
  //serial available then in here

  } else {
    servo2.write(0);
    servo.write(100);
  }


// above is code that needs to be running all the time.
//below is the triggering of second trigger
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (triggerArmed == 1) {
      trigger2State = 0; //FIRE
    } else {
      //trigger2State = 100; //UNARMED
    }

    // set the LED with the ledState of the variable:
    //digitalWrite(ledPin, ledState);
    servo.write(trigger2State);
  }

}


// function needed to extract the string of data from processing/P5JS.
char* subStr (char* input_string, char *separator, int segment_number) {
  char *act, *sub, *ptr;
  static char copy[20];
  int i;
  strcpy(copy, input_string);
  for (i = 1, act = copy; i <= segment_number; i++, act = NULL) {
    sub = strtok_r(act, separator, &ptr);
    if (sub == NULL) break;
  }
  return sub;
}