/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
  const int ledPin =  8;      // the number of the LED pin
  int ledState = LOW;             // ledState used to set the LED
  //int previousLedState = LOW;  
  
  int lightIntensity = 40; // maximum light intensity to turn on the lights
  int peopleCount = 1; // people inside the room
  int maxMilisecondsWait = 1000; // miliseconds to wait until reset

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
  //int sensor2Value = analogRead(A1);

  //previousLedState = ledState;
  if (sensorValue <= lightIntensity){
    ledState = HIGH;
  }else{
    ledState = LOW;
  }
    // print out the value you read:
  Serial.println(sensorValue);
  if (previousLedState != ledState){
    digitalWrite(ledPin, ledState);
  }
  delay(1);        // delay in between reads for stability
}
