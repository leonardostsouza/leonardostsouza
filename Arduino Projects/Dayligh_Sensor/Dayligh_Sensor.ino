#define LED_PIN 2
#define SENSOR_PIN A5

#define MAX_INTENSITY 40 //Maximum intensity for the lights to be on
#define WAIT_TIME 2000
 
int sensorValue = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  delay(WAIT_TIME);
  // read the input on sensor pin
  sensorValue = analogRead(SENSOR_PIN);

  if (sensorValue <= MAX_INTENSITY){
    digitalWrite(LED_PIN, HIGH);
  }else{
    digitalWrite(LED_PIN, LOW);
  }
  // print out the value you read:
  //Serial.println(sensorValue);
}
