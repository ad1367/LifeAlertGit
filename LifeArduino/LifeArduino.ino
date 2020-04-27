const int ACCpin = A0;
const int outputpin = 1;
float ACC = 0;
float ACCDC = 0;
float ACCDC1 = 0;
int count1 = 0;
int count2 = 0;
// create variable for the count1 window of time range
int countrange1 = 100;
//int countrange2 = countrange1/2 + countrange1;
// find the value of acc at rest for DC offset fix
int rest = 271;
float ACCSUM1 = 0;
float ACCSUM2 = 0;
float ACCAVE1 = 0;
float ACCAVE2 = 0;
float MAX = 0;
float MIN = -MAX;
float ACC1MIN = 0;
float ACC1MAX = 0;
float dACC = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ACCpin, INPUT);
  
}

void loop() {
  rest = analogRead(ACCpin);
  ACC = analogRead(ACCpin);
  ACCDC = ACC - rest;
  Serial.print("ACCDC = ");
  Serial.println(ACCDC);

  //Double count, stagger to account for different sampling window
  count1 = count1 + 1;
  ACCSUM1 = ACCSUM1 + ACCDC;
  
  //count2 = count2 + 1 + (countrange1) / 2;
  //ACCSUM2 = ACCSUM2 + ACCDC;

  if (count1 < countrange1) {
    count1 = 0;
    ACC1MIN = min(ACCDC,500);
    ACC1MAX = max(ACCDC,2000);
    dACC= ACC1MAX - ACC1MIN;
    Serial.print("Acceleration Sum: ");
    Serial.print(ACCSUM1);
    //reset ACCSUM
    ACCSUM1 = 0;
  }
  
 // if (count2 > countrange2) {
  //count2 = 0;
  //Serial.print("Ave 2 = ");
  //Serial.println(ACCSUM2);
  //}

  if (ACCSUM1 > MAX or ACCSUM1 < MIN) {
    digitalWrite(outputpin, HIGH);
 
  }
  else {
    digitalWrite(outputpin, LOW);
  }
 
  
  delay(10);

  ACCAVE2 = 0;
}
