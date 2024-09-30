int xPin = A0; // X axis
int yPin = A1; // Y axis
int buttonPin = 2; // Button pin

int xVal;
int yVal;
int buttonState;

int upLed = 10;
int downLed = 9;
int leftLed = 11;
int rightLed = 6;

void setup() {
    Serial.begin(9600); // Start Serial communication
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(upLed, OUTPUT);
    pinMode(downLed, OUTPUT);
    pinMode(leftLed, OUTPUT);
    pinMode(rightLed, OUTPUT);
}

void loop() {
    // Read joystick values
    xVal = analogRead(xPin);
    yVal = analogRead(yPin);
    buttonState = digitalRead(buttonPin);

    // Send joystick values to Processing
    Serial.print(xVal);
    Serial.print(",");
    Serial.print(yVal);
    Serial.print(",");
    Serial.println(buttonState);

    // Control LEDs based on joystick movement
    if (yVal <= 480) { // Joystick tilted up
        digitalWrite(upLed, HIGH); // Light up the up LED
        digitalWrite(downLed, LOW); // Turn off down LED
    } else if (yVal >= 560) { // Joystick tilted down
        digitalWrite(downLed, HIGH); // Light up the down LED
        digitalWrite(upLed, LOW); // Turn off up LED
    } else {
        digitalWrite(upLed, LOW); // Turn off up LED
        digitalWrite(downLed, LOW); // Turn off down LED
    }

    if (xVal <= 480) { // Joystick tilted left
        digitalWrite(leftLed, HIGH); // Light up the left LED
        digitalWrite(rightLed, LOW); // Turn off right LED
    } else if (xVal > 540) { // Joystick tilted right
        digitalWrite(rightLed, HIGH); // Light up the right LED
        digitalWrite(leftLed, LOW); // Turn off left LED
    } else {
        digitalWrite(leftLed, LOW); // Turn off left LED
        digitalWrite(rightLed, LOW); // Turn off right LED
    }

    if (buttonState == LOW) {
        digitalWrite(upLed, HIGH);   
        digitalWrite(downLed, HIGH);
        digitalWrite(leftLed, HIGH);
        digitalWrite(rightLed, HIGH);
    }

    delay(50); 
}
