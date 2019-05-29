#include <Servo.h>

Servo myservo [7];
int pos = 0;    
void setup() {
  for (int i=0; i<7; i++) {
    myservo[i].attach(i+3); 
  }
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    for (int i=0; i<7; i++) { 
      myservo[i].write(pos);      
    }        
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    for (int i=0; i<7; i++) {
      myservo[i].write(pos);      
    }        
    delay(15);                       
  }
}
