enum States{Idle, Retainer_Release, Catcher_Extend, Magazine_Retrace, Retainer_Extend,Sensor} state;
int RetainerPin1 = 13;
int RetainerPin2 = 12;
int CatcherPin = 11;
int MagazinePin = 10;

void Solenoid_On(int solenoidPin, int Delay)
{
  digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
  delay(Delay);                      //Wait 1 Second    
}

void Solenoid_Off(int solenoidPin)
{
  digitalWrite(solenoidPin, LOW);    //Switch Solenoid OFF
}


void Lock_And_Release()
{
  switch(state)
  {
    case Idle:
      state = Retainer_Release;
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
      break;

  }
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RetainerPin1, OUTPUT);
  pinMode(RetainerPin2, OUTPUT);
  pinMode(MagazinePin, OUTPUT);
  pinMode(CatcherPin, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  Lock_And_Release();
  delay(20);
  
}
