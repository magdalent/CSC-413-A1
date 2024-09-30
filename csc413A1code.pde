import processing.serial.*; 

Serial myPort;

int x, y, b; // Joystick X (A0), Y (A1), and button state (digital pin 2)
int prevX, prevY; // To store the previous joystick position
String val;
int threshold = 18; // Threshold to detect joystick movement

void setup() {
  size(900, 900);  // Window size
  background(102); // Set background color

  // Open the port (replace with your correct port)
  myPort = new Serial(this, "/dev/cu.usbmodem14201", 9600);  
  myPort.bufferUntil('\n'); 
  
  // Initialize previous position to center of the screen
  prevX = width / 2;
  prevY = height / 2;
}

void draw() {
  stroke(255); // Set line color to white
  fill(255);   // Set fill color to white
  
  // Map joystick values (0-1023) to the screen size
  int mappedX = int(map(x, 0, 1023, 0, width));
  int mappedY = int(map(y, 0, 1023, 0, height));

  // If the joystick button is pressed (b == 1), clear the screen and display a message
  if (b == 0) { 
     background(102); // Clear the screen by resetting the background
    ; // Display "Drawing cleared" message
  } else {
    // If the button is not pressed, check for joystick movement and draw continuous lines
    if (abs(x - 512) > threshold || abs(y - 512) > threshold) {
      line(prevX, prevY, mappedX, mappedY); 

      // Update previous position
      prevX = mappedX;
      prevY = mappedY;
    }
  }

  println("X: " + x + " | Y: " + y + " | Button: " + b);
}

// The serialEvent function is placed outside of setup and draw
void serialEvent(Serial myPort) {
  // Read the data until a newline appears
  val = myPort.readStringUntil('\n');

  if (val != null) {
    println("Received: " + val);  // Print the received data to check it
    val = trim(val);

    // Split the string based on commas
    int[] vals = int(splitTokens(val, ","));

    if (vals.length == 3) {  
      x = vals[0]; // Update joystick X
      y = vals[1]; // Update joystick Y
      b = vals[2]; // Update button state
    } 
  }
}
