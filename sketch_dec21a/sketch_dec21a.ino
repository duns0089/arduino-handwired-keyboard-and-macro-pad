// https://github.com/datulab/arduino-keyboard
// https://www.youtube.com/watch?v=Iq3oY91x9Vk

#include <Keyboard.h>

const byte inputs[] = { 21, 20, 19, 18, 15, 14, 16, 10 };  // Columns
const byte outputs[] = { 1, 9, 0, 8, 2, 7, 3, 6, 4, 5 };   // Rows
#define inCount sizeof(inputs) / sizeof(inputs[0])
#define outCount sizeof(outputs) / sizeof(outputs[0])

const char keymap[outCount][inCount] = {
  // 21   20   19   18   15   14   16   10
  { '`', '\\', '=', '-', '0', '9', '8', '7' },  // 1
  { 'N', '6', '5', '4', '3', '2', '1', 'E' },   // 9
  { 'B', 'N', ']', '[', 'p', 'o', 'i', 'u' },   // 0
  { 'N', 'y', 't', 'r', 'e', 'w', 'q', 'T' },   // 8
  { 'E', 'N', 'N', '\'', ';', 'l', 'k', 'j' },  // 2
  { 'N', 'h', 'g', 'f', 'd', 's', 'a', 'C' },   // 7
  { 'F', 'N', 'R', '/', '.', ',', 'm', 'n' },   // 3
  { 'N', 'b', 'v', 'c', 'x', 'z', 'N', 'L' },   // 6
  { 'R', 'N', 'W', 'F', 'N', 'N', 'N', 'S' },   // 4
  { 'N', 'N', 'N', 'N', 'L', 'N', 'W', 'L' },   // 5
};

// q, x, s, d, f = broken

// Press speed and delay configuration
int postOutputToLowDelayMicroseconds = 5;
int postOutputToHighDelayMicroseconds = 500;

int repeatsBeforeSecondPress = 90; // 350;  // Number of repeats a switch encounters when a key is held down before the second press is lodged
int repeatPressDelay = 6; // 15;           // Number of repeats a switch encounters between each press that is lodged

int currentKeyRepeatCount[outCount][inCount] = { 0 };
bool firstKeyPressFinished[outCount][inCount] = { false };


void setup() {
  for (int i = 0; i < inCount; i++) {
    pinMode(inputs[i], INPUT_PULLUP);
  }

  for (int i = 0; i < outCount; i++) {
    pinMode(outputs[i], OUTPUT);
    digitalWrite(outputs[i], HIGH);
  }

  Serial.begin(9600);
  Serial.println("Connected");
  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < outCount; i++) {
    digitalWrite(outputs[i], LOW);
    delayMicroseconds(postOutputToLowDelayMicroseconds);

    for (int j = 0; j < inCount; j++) {

      // Key pressed, if statement entered numerous times for key held down
      if (digitalRead(inputs[j]) == LOW) {
        // Serial.print("col: ");  // prints every time :(
        // Serial.print(inputs[j]);
        // Serial.print(" row: ");
        // Serial.print(outputs[i]);
        // Serial.print(" key: ");
        // Serial.println(keymap[i][j]);

        // 3 cases
        // first press
        if (currentKeyRepeatCount[i][j] == 0) {
          Serial.println(keymap[i][j]);
          Keyboard.write(keymap[i][j]);
        }
        // time for second press - spam mode
        else if (firstKeyPressFinished[i][j] && currentKeyRepeatCount[i][j] > repeatPressDelay) {
          Serial.println(keymap[i][j]);
          Keyboard.write(keymap[i][j]);
          currentKeyRepeatCount[i][j] = 1;  // start repeat count again
        }
        // ready for spam mode
        else if (currentKeyRepeatCount[i][j] > repeatsBeforeSecondPress) {
          firstKeyPressFinished[i][j] = true;  // ready for spam
        }
        currentKeyRepeatCount[i][j]++;
      }

      else if (currentKeyRepeatCount[i][j] != 0) {
        currentKeyRepeatCount[i][j] = 0;
        firstKeyPressFinished[i][j] = false;
      }
    }
    digitalWrite(outputs[i], HIGH);
    delayMicroseconds(postOutputToHighDelayMicroseconds);
  }
}



// PRINT KEYMAP
// for (int i = 0; i < outCount; i++) {
//   for (int j = 0; j < inCount; j++) {
//     // Serial.print(keymap[i][j]);
//     Serial.print(firstKeyPressFinished[i][j]);
//     Serial.print(", ");
//   }
//   Serial.print("\n");
// }
// Serial.print("\n\n\n");
