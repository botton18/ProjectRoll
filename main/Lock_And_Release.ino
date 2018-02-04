enum States{Idle, Ready, Retainer_Release, Catcher_Extend, Magazine_Retrace, Retainer_Extend} state;

void Solenoid_On(int solenoidPin, int Delay)
{
  digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
  delay(Delay);                      //Wait 1 Second    
}

void Solenoid_Off(int solenoidPin)
{
  digitalWrite(solenoidPin, LOW);    //Switch Solenoid OFF
}

void LED_ON(int Pin)
{
  digitalWrite(Pin, HIGH);
}

void LED_OFF(int Pin)
{
  digitalWrite(Pin,LOW);
}
void Lock_And_Release()
{
  switch(state)
  {
    case Idle:
      if(StateSensor())
      {
        state = Ready;
      }
      else
      {
        state = Idle;
      }
      break;

    case Ready:
      buttonState = digitalRead(buttonPin);
      if(buttonState == HIGH)
      {
        state = Retainer_Release;
        Serial.print("In BUTTON STATE HIGH:");
        Serial.print("\n");
      }
      else
      {
        state = Ready;
      }
      break;

    case Retainer_Release:
      state = Catcher_Extend;
      break;

    case Catcher_Extend:
      state = Magazine_Retrace;
      break;

    case Magazine_Retrace:
      state = Retainer_Extend;
      break;
      
    case Retainer_Extend:
      state = Idle;
      break;

  }
  switch(state)
  {
    case Idle:
      Solenoid_Off(CatcherPin);
      Solenoid_Off(MagazinePin);
      Solenoid_Off(RetainerPin1);
      Solenoid_Off(RetainerPin2);
      LED_OFF(ReadyPin);
      LED_ON(InUsePin);
      break;

    case Ready:
      //READY LED on
      LED_ON(ReadyPin);
      LED_OFF(InUsePin);
      break;

    case Retainer_Release:
      Solenoid_On(RetainerPin1, 0);
      Solenoid_On(RetainerPin2, 100);
      break;

    case Catcher_Extend:
      Solenoid_On(CatcherPin, 0);
      break;

    case Magazine_Retrace:
      Solenoid_On(MagazinePin, 0);
      break;
      
    case Retainer_Extend:
      Solenoid_Off(RetainerPin1);
      Solenoid_Off(RetainerPin2);
      ping_value = singleMeasurement();
      full_roll = fixed_distance - ping_value;
      Serial.print("PingValue IN RETAINER EXTEND:");
      Serial.print(ping_value);
      Serial.print("\n");
      break;
      
  }
}



// the loop function runs over and over again forever
