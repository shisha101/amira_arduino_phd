int redLedPin = 4;
int lightSensorPin = A0;
int analogValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(redLedPin,OUTPUT);
  digitalWrite(redLedPin, HIGH);
}

void loop(){
  analogValue = analogRead(lightSensorPin);
  Serial.print("AnalogValue = ");
  Serial.println(analogValue);
  delay(200);
}
