#include <NewPing.h>


#define TRIGGER_PIN 5
#define ECHO_PIN 6
#define EMPTY_DISTANCE 20 // need to change to actual distance once calculated
#define MEASURE_SAMPLE_DELAY 5
#define MEASURE_SAMPLES 25
#define MEASURE_DELAY 250
#define USONIC_DIV 58.0

int RetainerPin1 = 13;
int RetainerPin2 = 12;
int CatcherPin = 11;
int MagazinePin = 10;
int buttonPin = 7;
int ReadyPin = 9;
int InUsePin = 8;
double G_r = 2.1;
double G_Percentage = 0.0;

double full_roll = 0.0;
double current_roll = 0.0;
double fixed_distance = 200;
double ping_value = 0.0;

int buttonState = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, EMPTY_DISTANCE);


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  //ping_value = sonar.ping_cm();
  ping_value = singleMeasurement();
  full_roll = fixed_distance - ping_value;
  pinMode(RetainerPin1, OUTPUT);
  pinMode(RetainerPin2, OUTPUT);
  pinMode(MagazinePin, OUTPUT);
  pinMode(CatcherPin, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ReadyPin, OUTPUT);
  pinMode(InUsePin, OUTPUT);
   // Reset the trigger pin and wait a half a second
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(500);

  
}
// the loop function runs over and over again forever
void loop() {
  Lock_And_Release();
  
}

