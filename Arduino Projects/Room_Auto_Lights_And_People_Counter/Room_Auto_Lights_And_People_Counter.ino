/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
  const int ledPin =  8;      // the number of the LED pin
  int ledState = LOW;             // ledState used to set the LED 
  int previousLedState = HIGH;

  const int lightIntensity = 40; // light intensity on the sensor (room lights)
  const int laserIntensity = 100; // laser intensity on the light sensor (presence)
  
  const long maxCiclesWait = 10; // miliseconds to wait until reset
  long ciclesWaiting = 0;
  
  unsigned int peopleCount = 0; // people inside the room
  
  boolean sensor1Activated = 0; // use only 0 or 1
  boolean sensor2Activated = 0; // use only 0 or 1
  
  int firstSensorActivated = 0; // 1 or 2 ( 0 if reset)
  
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0 and 1:
  int sensor1Value = analogRead(A0);
  int sensor2Value = analogRead(A1);
  
  previousLedState = ledState;
  
  // Checks sensor 1
  if (sensor1Value <= laserIntensity && sensor1Activated == false && sensor2Value > laserIntensity){
    sensor1Activated = true;
    if (firstSensorActivated == 0){
      firstSensorActivated = 1;
    }
  }
  
  // Checks sensor 2
  if (sensor2Value <= laserIntensity && sensor2Activated == false && sensor1Value > laserIntensity){
    sensor2Activated = true;
    if (firstSensorActivated == 0){
      firstSensorActivated = 2;
    }
  }
  
  // counts miliseconds waiting
  
  if ((sensor1Activated || sensor2Activated) && ciclesWaiting <= maxCiclesWait){
    ciclesWaiting++;
  }else if (ciclesWaiting > maxCiclesWait){
    firstSensorActivated = 0;
    sensor1Activated = false;
    sensor2Activated = false;
    ciclesWaiting = 0;
  }
  
  //Checks if someone enters or leaves the room
  if (sensor1Activated && sensor2Activated){
 //   switch (firstSensorActivated){
 //     case 1:
    if (firstSensorActivated == 1){
        peopleCount = peopleCount + 1;
 //     case 2:
    }else if (firstSensorActivated == 2 && peopleCount != 0){
        peopleCount = peopleCount - 1;
    }
    firstSensorActivated = 0;
    sensor1Activated = false;
    sensor2Activated = false;
    ciclesWaiting = 0;
  }

  //Checks if there is need to turn on the lights
  if (peopleCount == 0){
    ledState = LOW;
  }else if (peopleCount > 0){
    ledState = HIGH;
  } else {
    peopleCount = 0;
  }
  
  
  
  // print out the value you read:
  Serial.println("----------------------------------");
  Serial.print("sensor1Value = ");
  Serial.print(sensor1Value);
  Serial.print("\t");
  Serial.println(sensor1Activated);
  
  Serial.print("sensor2Value = ");
  Serial.print(sensor2Value);
  Serial.print("\t");
  Serial.println(sensor2Activated);
  
  Serial.print("firstSensorActivated = ");
  Serial.println(firstSensorActivated);
  
 // Serial.print("ledState = ");
 // Serial.println(ledState);
  Serial.print("peopleCount = ");
  Serial.println(peopleCount);
  
  Serial.print("ciclesWaiting = ");
  Serial.println(ciclesWaiting);
  
  if (previousLedState != ledState){
    digitalWrite(ledPin, ledState);
  }
  delay(1);        // delay in between reads for stability
}
