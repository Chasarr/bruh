#include <Arduino.h>
#include <Keyboard.h>


#define BTN 3
#define DEBOUNCE_THRESHOLD 50

boolean debounce(const unsigned short int &btnState);

unsigned long int lastPressedTime = 0;
unsigned int lastButtonState = HIGH;


void setup() {
    Serial.begin(115200);
    Keyboard.begin();
    pinMode(BTN, INPUT_PULLUP);
}

void loop() {
    if (debounce(!digitalRead(BTN))) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('c');
        Keyboard.release('c');
        Keyboard.release(KEY_LEFT_CTRL);
    }
}

boolean pressState = false;
boolean alreadyPressed = false;     //Has the pressed button already returned true once?
boolean debounce(const unsigned short int &btnState) {
    //If the button is pressed the first time the time is stored in 'lastPressedTime' variable
    //'pressState' is set to true, which prevents the time from being measured again
    if (btnState == HIGH && !pressState && !alreadyPressed) {
        lastPressedTime = millis();     //millis() returns system timer
        pressState = true;
        return false;
    }
        //If the button keeps being pressed after initial press
    else if (btnState == HIGH && pressState && !alreadyPressed) {
        //Has the code been executed for long enough? Then the code is executed
        if ((millis() - lastPressedTime) > DEBOUNCE_THRESHOLD) {
            alreadyPressed = true;      //Prevents the function to return true until the button is released
            return true;
        } else {
            return false;
        }
    }
        //When the button gets released this code excecutes and resets everything
    else if (btnState == LOW) {
        pressState = false;
        alreadyPressed = false;
    }
    pressState = false;
    return false;
}