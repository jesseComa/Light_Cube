//pins
int trigger;
int echo;
int pinRed;
int pinBlue;
int pinGreen;
int button1;
int button2;
 //values that are used for the ultrasonic sensor
long duration;
int distance;
float intensity;

//values used to determine the color of the cube
int count;
int colorPallet;
int RedValue;
int BlueValue;
int GreenValue;

void setup() {
  //pin values for buttons, rgb LED and ultrasonic sensor
  button1 = 12;
  button2 = 13;
  trigger = 4;
  echo = 7;
  pinRed = 3;
  pinBlue = 5;
  pinGreen = 6;

  //echo pin set to input to take in data from the 
  //ultrasonic sensor
  pinMode(echo, INPUT);
  //trigger set to output to let ultrasonic sensor know when
  //a distance value is wanted
  pinMode(trigger, OUTPUT);
  //pins for led are set to output so the arduino can provide power to light it
  pinMode(pinRed, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  
  //initial values for colors so that they arent garbage values
  count = 0;
  colorPallet = 0;
  RedValue = 255;
  BlueValue = 255;
  GreenValue = 255;
}

void loop() {
/*****************
 * This section of code is to determine the distance that a person or object
 * is to the cube
 */
//sets the trigger low state so it does not activate the ultrasonic sensor
digitalWrite(trigger, LOW);
//delays for 2 microseconds
delayMicroseconds(2);
// sets the trigger on HIGH state for 10 micro seconds
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
//sets the trigger on low state
digitalWrite(trigger, LOW);
// Reads the pulse sent back ny the echo pin
//the pulse width is the amount of time the sound wave traveled from the 
//sensor to the object and back to the sensor.
duration = pulseIn(echo, HIGH);
// Calculating the distance between the object and sensor
//takes duration of flight and divides by 2 since we want one way, not round trip.
//then multiplies by the speed of sound in cm per microsecond
distance= duration*0.034/2;

//this is to scale the values on the sensor so that high values
//will give a distance of 100 which is used by the intensity calculation
if(distance > 100)
{
  distance = 100;
}
//takes the distance and subtracts 2cm because the sensor has trouble reading very close
//then divides by 100. This allows me to have a number from 0 to 1 that can scale the
//colors by different intensities
intensity = float(distance - 2) /100;

/**********************
 * This section of code is for dealing with button presses and color changing
 */
 //checks if button has been pressed
if(digitalRead(button1) == HIGH)
{
  //adds to count and delays a bit to act as a debounce
  count ++;
  delay(60);
}
//checks if the 2nd button has been pressed
else if(digitalRead(button2)==HIGH)
{
  //if the second button was pressed subtract from count and debounce button
  count --;
  delay(60);
}
//colorpallet is used to determine what color the light is
//by taking count moduloud 7, I will only have numbers from 0 to 6
colorPallet = count % 7;
//switch goes through and depending on what the colorPallet number is, the brightness for each color in the rgb is changed
switch (colorPallet) {
  case 0:
    RedValue = 255;
    BlueValue = 255;
    GreenValue = 255;
    break;
  case 1:
    RedValue = 255;
    BlueValue = 0;
    GreenValue = 0;
    break;
      case 2:
        RedValue = 255;
    BlueValue = 255;
    GreenValue = 0;
    break;
      case 3:
        RedValue = 0;
    BlueValue = 255;
    GreenValue = 0;
    break;
      case 4:
        RedValue = 0;
    BlueValue = 255;
    GreenValue = 255;
    break;
      case 5:
        RedValue = 0;
    BlueValue = 0;
    GreenValue = 255;
    break;
          case 6:
        RedValue = 255;
    BlueValue = 0;
    GreenValue = 255;
    break;
  default:
    RedValue = 255;
    BlueValue = 255;
    GreenValue = 255;
}
//outputs the selected color and brightness of the rgb led by changing the intensity of the red, green and blue leds
analogWrite(pinRed, RedValue * intensity);
analogWrite(pinBlue, BlueValue * intensity);
analogWrite(pinGreen, GreenValue * intensity);
}

