#include <NewPing.h>

//defined values set at 0 for now, to be changed when we know values

#define TRIGGER_PIN 5
#define ECHO_PIN 6
#define EMPTY_DISTANCE 20 // need to change to actual distance once calculated

//double G_R = 6.0;
double G_r = 2.1;
double G_Percentage = 0.0;
//double G_ = 0.0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, EMPTY_DISTANCE);

// PARAMETERS:
// true means new roll
// false means state controller
// RETURNS:
//return true if empty
//else return false;
bool StateSensor(bool b) {
  double roll_area = 0.0, roll_area2 = 0.0;
  double ping_value = sonar.ping_cm();
  Serial.print("Ping:");
  Serial.print(ping_value);
  if(b) 
    roll_area = pow(ping_value, 2) - pow(G_r, 2); //reset previous value

  roll_area2 = pow(ping_value, 2) - pow(G_r, 2); // calculates current roll area
  G_Percentage = (roll_area2 / roll_area) * 100; // calculates percentage of roll remaining
  Serial.print("roll_area:");
  Serial.print(roll_area);
  Serial.print("roll_area2:");
  Serial.print(roll_area2);
  Serial.print("G_Percentage");
  Serial.print(G_Percentage);
  if (G_Percentage < 10.0) // returns true, toilet paper roll < 10%
    return true;
  else
    return false;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // temp, not sure what bps to set to
  // roll_area
}

void loop() {
  // put your main code here, to run repeatedly:
  StateSensor(true);
  delay(2000);
  StateSensor(false);
  delay(2000);
  StateSensor(false);
  delay(2000);
  StateSensor(true);
  delay(2000);
}

