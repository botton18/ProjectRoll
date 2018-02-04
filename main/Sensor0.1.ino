#include <NewPing.h>

//defined values set at 0 for now, to be changed when we know values
// PARAMETERS:
// true means new roll
// false means state controller
// RETURNS:
//return true if empty
//else return false;



long measure()
{
  long measureSum = 0;
  for (int i = 0; i < MEASURE_SAMPLES; i++)
  {
    delay(MEASURE_SAMPLE_DELAY);
    measureSum += singleMeasurement();
  }
  return measureSum / MEASURE_SAMPLES;
}

long singleMeasurement()
{
  long duration = 0;
  // Measure: Put up Trigger...
  digitalWrite(TRIGGER_PIN, HIGH);
  // ... wait for 11 µs ...
  delayMicroseconds(11);
  // ... put the trigger down ...
  digitalWrite(TRIGGER_PIN, LOW);
  // ... and wait for the echo ...
  duration = pulseIn(ECHO_PIN, HIGH);
  return (long) (((float) duration / USONIC_DIV) * 10.0);
}


bool StateSensor() {
  double ping_value_local = singleMeasurement();
  Serial.print("Ping:");
  Serial.print(ping_value_local);
  Serial.print("\n");
  current_roll = fixed_distance - ping_value_local;
  Serial.print("Full Roll in main loop: ");
  Serial.print(full_roll);
  Serial.print("\n");  // roll_area
  G_Percentage = pow(current_roll, 2)/ pow(full_roll,2);
  G_Percentage = G_Percentage * 100;
  Serial.print("Percentage:");
  Serial.print(G_Percentage);
  Serial.print("\n");
  if(G_Percentage < 10)
  {
    return true;
  }
  else
  {
    return false;
  }

}


