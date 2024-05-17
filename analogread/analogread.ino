int sensorValue=0;
int ledDimming=0;
int pwmPin=13;
void setup() {
  // put your setup code here, to run once:
  pinMode(A1,INPUT);
  Serial.begin(9600);
  pinMode(pwmPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue=analogRead(A1);
  Serial.println(sensorValue);
  delay(1);
  if(sensorValue>30){
    sensorValue=30;
  }
  else if(sensorValue<5){
    sensorValue=5;
  }
  int ledBlink=map(sensorValue, 5, 30, 0, 255);
  analogWrite(13,ledBlink);
}
