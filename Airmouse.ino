#include <Wire.h>
#include <Mouse.h>
#include <MPU6050.h>
#include <Keyboard.h>

MPU6050 mpu;

const int buttonPin15 = 15;
const int buttonPin14 = 14;
const int buttonPin16 = 16;
const int buttonPin10 = 10;
const int buttonPin9 = 9;

unsigned long debounceDelay = 200;
unsigned long lastButtonPress = 0;
bool buttonFlag = true;

void setup() {
  Wire.begin();
  mpu.initialize();
  pinMode(buttonPin15, INPUT_PULLUP);
  pinMode(buttonPin14, INPUT_PULLUP);
  pinMode(buttonPin16, INPUT_PULLUP);
  pinMode(buttonPin10, INPUT_PULLUP);
  pinMode(buttonPin9, INPUT_PULLUP);
  Keyboard.begin();
  Serial.begin(9600);
  delay(2000);  // Give some time for sensor to stabilize
}

void loop() {
  unsigned currentTime = millis();
  int16_t ax, ay, az;
  int sensorValueX = analogRead(A0);
  int sensorValueY = analogRead(A1);
  Serial.println(sensorValueX);
  Serial.println(sensorValueY);
  Serial.println("sensorValueY");
  mpu.getAcceleration(&ax, &ay, &az);

  int mappedY = map(ay, -16384, 16383, -5, 5);  // Map ay to cursor movement in X direction
  int mappedX = map(az, 16384, -16383, -5, 5);  // Map ax to cursor movement in Y direction
  //uses sideways setting mode
  Mouse.move(mappedX, mappedY);
  /*
  Serial.print("X: ");
  Serial.print(mappedX);
  Serial.print(" | Z: ");
  Serial.println(mappedY);

  Serial.print("aX: ");
  Serial.print(ax);
  Serial.print(" | aY: ");
  Serial.print(ay);
  Serial.print(" | aZ: ");
  Serial.println(az);
  */

  delay(20);  // Adjust delay as needed to control mouse sensitivity
  if (currentTime - lastButtonPress >= debounceDelay) {
  lastButtonPress = currentTime;
  buttonFlag = true;
  }
  if (digitalRead(buttonPin15) == LOW && (buttonFlag == true)) {
    Keyboard.write('c');
    buttonFlag = false;
  }
  if (digitalRead(buttonPin14) == LOW && (buttonFlag == true)) {
    Keyboard.write('q');
    buttonFlag = false;
  }
  if (digitalRead(buttonPin16) == LOW && (buttonFlag == true)) {
    Keyboard.write('e');
    buttonFlag = false;
  }
  if (digitalRead(buttonPin10) == LOW && (buttonFlag == true)) {
    Keyboard.write('x');
    buttonFlag = false;
  }

  if (digitalRead(buttonPin9) == LOW) {
    Mouse.click();
  }

  if (sensorValueX > 600) {
    Keyboard.write('w');
  }

  if (sensorValueX < 400) {
    Keyboard.write('s');
  }

  if (sensorValueY > 600) {
    Keyboard.write('d');
  }

  if (sensorValueY < 400) {
    Keyboard.write('a');
  }


}