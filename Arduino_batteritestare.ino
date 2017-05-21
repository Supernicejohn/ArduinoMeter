#include <LiquidCrystal.h>
// Open Source
// ! Only 0-5 Volt input, failure to comply to this restriction may lead to destruction of an arduino. How sad. ! //
const int VoltagePin = 0;
// Connect screen to the following pins
LiquidCrystal lcd(12,11,5,4,3,2);
void setup() {
  lcd.begin(16,2);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
  pinMode(VoltagePin,INPUT);
}
void writeValue(double v){
  Serial.println(v);
  lcd.setCursor(0,0);
  lcd.print(v);
  
} 
const double waitTime = 0;
const boolean useAverage = true;
double voltages[256]; //array to even out any eventual voltage fluctuations.
int vIndex = 0; // index in said array
boolean done = true; // if all values are filled in then we can show an average.
double actualVoltage = 0;

void loop() { // from what I read, this'll loop 256 times in 256/10000th of a second, say 0.03s. Use waitTime to slow down.
  delay(waitTime);
  if (vIndex > 255){
    vIndex = 0;
    done = true; // permanently set done to true.
  }
  double rawValue = analogRead(VoltagePin); // get voltage 0-1023
  voltages[vIndex] = rawValue; 
  voltages[vIndex] *= 0.0048828125;// translate raw into actual voltage.
  for (int i=0; i<256; i++){
    if (done){
      actualVoltage += voltages[i];
    }
  }
  if (useAverage) {
    actualVoltage = actualVoltage/256; // get final voltage, the average of all voltages in the array.
  } else {
    actualVoltage = voltages[vIndex];
  }
  if (done){
    writeValue(actualVoltage); // send value to screen, for debugging purposes.
  }
  vIndex += 1;
}
