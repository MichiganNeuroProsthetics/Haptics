const int input = A0;
const int output = 9;
const int motor2 = 10;
const int slider = A1;
const int button = 7;
const int R = 2;
const int G = 3;
const int B = 4;
int buttonState = 0;
int buttonMode = 0;
int lastState = 0;

inline void writeColors(uint8_t red, uint8_t green, uint8_t blue) {
  digitalWrite(R, red);
  digitalWrite(G, green);
  digitalWrite(B, blue);
}
void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(output, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(input, INPUT);
  pinMode(slider, INPUT);
  pinMode(button, INPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
} 


void loop() {
  //read in button state
  buttonState = digitalRead(button);
  //if the button was pressed
  if (buttonState != lastState) {
    if (buttonState == HIGH){
      //go to the next mode for buzzing
      ++buttonMode;
      //if you are on the last mode
      if (buttonMode == 3) {
        //go to first mode
        buttonMode = 0;
      }
    }
  }
  lastState = buttonState;

  //Mode 0: off
  if (buttonMode == 0) {
    analogWrite(output, 0);
    analogWrite(motor2, 0);
    writeColors(LOW, LOW, LOW); 
  }

  //add code for leds
  
  //Mode 1: slider
  else if (buttonMode == 1) {
   int intensity = analogRead(slider);
   int i = map(intensity, 0, 1023, 0, 100);
   int signal = analogRead(input);
   Serial.println(signal);
   int magnitude = map(signal, 0, 1023, 255, 0);
   magnitude = (magnitude / 100) * i;
   analogWrite(output, magnitude);
   analogWrite(motor2, magnitude);
   writeColors(HIGH, LOW, LOW);
   delay(2);
  }

  //Mode 2: one to one
  else if (buttonMode == 2) {
   int m2 = analogRead(slider);
   int m2out = map(m2, 0, 1023, 255, 0);
   analogWrite(motor2, m2out);
   int signal = analogRead(input);
   Serial.println(signal);
   int magnitude = map(signal, 0, 1023, 255, 0);
   analogWrite(output, magnitude);
   writeColors(LOW, HIGH, LOW);
   delay(2);

   //something like (but not actually its gonna be rly complex)
  }

  //Mode 3:
  else if (buttonMode == 3) {
  }
}

  
