const int ACCpin = A0;
const int LED1 = 2;
const int LED2 = 4;
float ACC;
float ACCDC;
int rest;
int MAX = 6;
int ACCMAX = 0;
int ACCMIN = 0;
int dACC;
int timestart;
int timeelapsed;
unsigned long time;

void setup() {
  Serial.begin(9600);
  pinMode(ACCpin, INPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void loop() {
  // start timer count in seconds
  time = millis() / 1000;
  rest = analogRead(ACCpin);
  ACC = analogRead(ACCpin);
  ACCDC = ACC - rest;
  Serial.print("ACCDC: ");
  Serial.println(ACCDC);

  // if acceleration trips a maximum magnitude, start fall timer
  if (abs(ACCDC) > MAX) {
    digitalWrite(LED1, HIGH);
    timestart = time;
  }
  // initiate timer that starts after fall
  timeelapsed = time - timestart;
  Serial.print(" , ");
  Serial.print("Timer: ");
  Serial.println(timeelapsed);

  /* for 10 seconds after a potential fall has been detected,
      sense for stillness of movement that eliminates walking
      as a potential cause of  acceleration */

  /*while (timeelapsed < 10) {
      if (ACCDC > ACCMAX) {
        ACCMAX = ACCDC;
        //Serial.print(" , ");
        //Serial.print("Max ACC: ");
        //Serial.println(ACCMIN);
      }

      if (ACCDC < ACCMIN) {
        ACCMIN = ACCDC;
        //Serial.print("Min ACC: ");
        //Serial.println(ACCMIN);
      }
      // if the person is at rest for 10 seconds after jolt,
      //   second LED alert will turn on
      dACC = ACCMAX - ACCMIN;
      if (dACC < 100) {
        digitalWrite(LED2, HIGH);
      }
    }
  */
delay(10);
}
