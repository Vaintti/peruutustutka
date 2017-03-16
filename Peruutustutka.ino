unsigned long echo = 0;
int ultraSoundSignal = A0; // Ultrasound signal pin
int speakerOut = 11;
unsigned long ultrasoundValue = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ultraSoundSignal, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long ping()
{
  pinMode(ultraSoundSignal, OUTPUT); // Switch signalpin to output
  digitalWrite(ultraSoundSignal, LOW); // Send low pulse
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultraSoundSignal, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultraSoundSignal, LOW); // Holdoff
  pinMode(ultraSoundSignal, INPUT); // Switch signalpin to input
  digitalWrite(ultraSoundSignal, HIGH); // Turn on pullup resistor
  echo = pulseIn(ultraSoundSignal, HIGH); //Listen for echo
  ultrasoundValue = (echo / 58.138); //convert to CM
  return ultrasoundValue;
}

void loop()
{
  int x = 0;
  x = ping();
  Serial.println(x);
  if(x<=100 && x > 10) {
    digitalWrite(LED_BUILTIN, LOW);
    noTone(speakerOut);
    delay(x*5);
    digitalWrite(LED_BUILTIN, HIGH);
    tone(speakerOut, 3000-x*10);
    delay(x*5);
    digitalWrite(LED_BUILTIN, LOW);
    noTone(speakerOut);
  }
  if(x<10) {
    digitalWrite(LED_BUILTIN, HIGH);
    tone(speakerOut, 3000-x*10);
    delay(5);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    noTone(speakerOut);
  }
}
