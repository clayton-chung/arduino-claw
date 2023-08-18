#include <Servo.h>

#define VCC_PIN 13         // VCC pin connected to pin 13
#define TRIGGER_PIN 12     // Sonar trigger pin connected to pin 12
#define ECHO_PIN 11        // Sonar echo pin connected to pin 11
#define GROUND_PIN 10      // Ground pin connected to pin 10
#define MAX_DISTANCE 15    // Maximum distance in cm. Adjust as needed

Servo myservo;

long duration;
int distance;

int dist_to_close = 8;    // Distance threshold for triggering
int delay_time = 25000;   // Delay time after triggering in microseconds
bool run = true;

void setup() {
  myservo.attach(9);       // Servo control on pin 9
  Serial.begin(9600);  
  pinMode(ECHO_PIN, INPUT);  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(GROUND_PIN, OUTPUT);  
  pinMode(VCC_PIN, OUTPUT);  
  digitalWrite(GROUND_PIN, LOW); 
  digitalWrite(VCC_PIN, HIGH); 
}

void loop() {
  // Sonar measurement
  digitalWrite(TRIGGER_PIN, LOW);  
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > MAX_DISTANCE){  
    distance = MAX_DISTANCE;
  }

  Serial.print("Distance: "); 
  Serial.println(distance);

  // Servo control
  distance = map(distance, dist_to_close, MAX_DISTANCE, 0, 180); 

  if (distance < dist_to_close){
    myservo.write(0);
    Serial.print("Starting delay of ");
    Serial.println(delay_time / 1000);   
    run = false;
    delay(delay_time); // Delay to move the claw
    run = true;
  }

  if (run){
    myservo.write(150);
  }
}
