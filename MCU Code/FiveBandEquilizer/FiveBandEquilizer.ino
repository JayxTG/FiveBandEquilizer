// Define the pins for the columns (A0 to A4)
const int analogPins[5] = {A0, A1, A2, A3, A4};

// Define the digital pins for controlling rows and columns of the LED matrix
const int rowPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int colPins[5] = {10, 11, 12, 13, A5}; // Assuming you're using these pins for columns

void setup() {
  // Initialize analog pins as inputs
  for (int i = 0; i < 5; i++) {
    pinMode(analogPins[i], INPUT);
  }
  
  // Initialize row and column pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);  // Ensure all rows are off initially
  }
  for (int i = 0; i < 5; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH); // Ensure all columns are off initially
  }
}

void loop() {
  int analogValues[5];
  int mappedValues[5];
  
  // Read and map analog values
  for (int i = 0; i < 5; i++) {
    analogValues[i] = analogRead(analogPins[i]);
    mappedValues[i] = map(analogValues[i], 0, 1023, 0, 8);
  }
  
  // Update the LED matrix
  updateMatrix(mappedValues);
  
  // Small delay to stabilize readings
  delay(100);
}

void clearMatrix() {
  // Turn off all rows
  for (int i = 0; i < 8; i++) {
    digitalWrite(rowPins[i], LOW);
  }
  // Turn off all columns
  for (int i = 0; i < 5; i++) {
    digitalWrite(colPins[i], HIGH);
  }
}

void updateMatrix(int values[5]) {
  clearMatrix();
  
  for (int col = 0; col < 5; col++) {
    // Turn on the appropriate column
    digitalWrite(colPins[col], LOW);
    
    // Light up the appropriate number of LEDs in this column
    for (int row = 0; row < values[col]; row++) {
      digitalWrite(rowPins[row], HIGH);
    }
    
    // Small delay for persistence of vision effect
    delay(2);
    
    // Turn off the column
    digitalWrite(colPins[col], HIGH);
    
    // Turn off all rows for the next cycle
    for (int row = 0; row < values[col]; row++) {
      digitalWrite(rowPins[row], LOW);
    }
  }
}
