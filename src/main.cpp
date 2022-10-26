#include <Arduino.h>


const int leftSwitchPin = 25;
const int rightSwitchPin = 21;

const int leftCtlPin = 12;
const int rightCtlPin = 14;

const int pwmChannel = 0;
const int pwmPin =  13;

const int pwmFreq = 20000;
const int pwmResolution = 8;

int pwmDutyCycle = 0;

const int minDutyCycle = 200;
const int maxDutyCycle = 255;
const int rangeDutyCycle = maxDutyCycle - minDutyCycle;

int speedPin = 35;
int speedVal = 0;
const int maxSpeedVal = 4096;

int direction = 1;

int leftSwitchVal = 0;
int rightSwitchVal = 0;


void setup() {
  Serial.begin(115200);

  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(pwmPin, pwmChannel);

  pinMode(leftSwitchPin, INPUT_PULLUP);
  pinMode(rightSwitchPin, INPUT_PULLUP);

  pinMode(speedPin, INPUT);

  pinMode(leftCtlPin, OUTPUT);
  pinMode(rightCtlPin, OUTPUT);
}


void loop() {
  leftSwitchVal = digitalRead(leftSwitchPin) == LOW;
  rightSwitchVal = digitalRead(rightSwitchPin) == LOW;

  speedVal = analogRead(speedPin);

  pwmDutyCycle = speedVal < 10 ? 0 : (
    minDutyCycle +
    speedVal * 100 / maxSpeedVal *
    rangeDutyCycle / 100
  );

  ledcWrite(pwmChannel, pwmDutyCycle);

  Serial.print("Duty cycle: ");
  Serial.print(pwmDutyCycle);

  Serial.print("   |   Direction: ");
  Serial.print(direction);

  Serial.print("   |   Left switch: ");
  Serial.print(leftSwitchVal? "on" : "off");
  Serial.print("   |   Right switch: ");
  Serial.println(rightSwitchVal ? "on" : "off");

  if (direction == 0) {
    digitalWrite(leftCtlPin, HIGH);
    digitalWrite(rightCtlPin, LOW);
  } else {
    digitalWrite(leftCtlPin, LOW);
    digitalWrite(rightCtlPin, HIGH);
  }

  if (leftSwitchVal) {
    direction = 0;
  } else if (rightSwitchVal) {
    direction = 1;
  }

  delay(50);
}
