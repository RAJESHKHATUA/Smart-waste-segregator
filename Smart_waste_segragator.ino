// ---------------------------------------------------------------- //
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// ---------------------------------------------------------------- //
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
#define echoPin 6  // attach pin D6 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D7 Arduino to pin Trig of HC-SR04
#define trigPin2 10//attach pin D10 Arduino to pin Trig of HC-SR04 2
#define echoPin2 8//attach pin D8 Arduino to pin Trig of HC-SR04 2

int sensorPin = A0;
int sensorValue;
int limit = 1000;

// defines variables
int moisture_detected = 0;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <Servo.h>
Servo myservo;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
    pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  

  //lcd.clear();
  myservo.attach(9);
  myservo.write(90);

  pinMode(13, OUTPUT);
}

int measure_distance(int trig, int echo)
{
    // Clears the trigPin condition
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  int dist = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return dist;
}

void loop() {
  lcd.setCursor(0, 0);
lcd.print("WASTE SEGREGATOR");


  sensorValue = analogRead(sensorPin);
  Serial.println("Analog Value : ");
  Serial.println(sensorValue);

  if (sensorValue < limit) {
    digitalWrite(13, HIGH);
    moisture_detected = 1;
  }
  else {
    digitalWrite(13, LOW);
    moisture_detected = 0;
  }

  distance = measure_distance(trigPin, echoPin);
  Serial.print(distance);
  Serial.println(" cm");
  //print first distance
  int distance2 = measure_distance(trigPin2, echoPin2);
  // Displays the distance on the Serial Monitor
  Serial.print("Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  lcd.setCursor(0, 1);
  if (distance2 < 8)
  { lcd.print(" - Dustbin Full- ");//Dustbin Full indication
  delay(1000);
  Serial.print("dustbin full");
    //lcd.print("Distance:");
    //lcd.print(distance);
  }

    //lcd.print("cm        ");
  //lcd.print("Distance:");
  //lcd.print(distance);

  //lcd.print("cm        ");
  delay(1000);

lcd.setCursor(0, 1);
  if (distance < 15)//object detected...open and close
  {
    if (moisture_detected)
    {
      lcd.print(" - WET DETECTED - ");
      myservo.write(30);
      Serial.println("30");
    }
    else
    {
      lcd.print(" - DRY DETECTED - ");
      myservo.write(150);
      Serial.println("150");
    }
    delay(1000);
    myservo.write(90);
    Serial.println("90");
    delay(2000);
  }
  else
  {
    lcd.print("  -  No Input -  ");
  }
}
