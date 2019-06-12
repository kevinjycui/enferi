#include <gamma.h>
#include <RGBmatrixPanel.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>


int matrixW = 64;
int matrixH = 31;

int eyeData;
int uData;
int uPower;
int lData;
int lPower;

#define CLK 11
#define LAT 10
#define OE 9
#define A A0
#define B A1
#define C A2
#define D A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void setup() {
  matrix.begin();
  Serial.begin(9600);
}
void eyeReset() {
  matrix.drawLine(44, 5, 44, 9, matrix.Color333(0, 0, 7)); // left eyelid
  matrix.drawLine(43, 4, 43, 10, matrix.Color333(0, 0, 7));
  matrix.drawLine(44, 22, 44, 26, matrix.Color333(0, 0, 7)); // right eyelid
  matrix.drawLine(43, 21, 43, 27, matrix.Color333(0, 0, 7));
  matrix.drawCircle(40, 7, 5, matrix.Color333(0, 0, 7)); //left eye
  matrix.drawCircle(40, 24, 5, matrix.Color333(0, 0, 7)); //right eye
}
void eyeNeutral() {
  matrix.drawLine(44, 5, 44, 9, matrix.Color333(0, 0, 7)); // left eyelid
  matrix.drawLine(43, 4, 43, 10, matrix.Color333(0, 0, 7));
  matrix.drawLine(44, 22, 44, 26, matrix.Color333(0, 0, 7)); // right eyelid
  matrix.drawLine(43, 21, 43, 27, matrix.Color333(0, 0, 7));
  matrix.drawCircle(40, 7, 5, matrix.Color333(0, 0, 7)); //left eye
  matrix.drawCircle(40, 24, 5, matrix.Color333(0, 0, 7)); //right eye
  matrix.drawCircle(40, 24, 1, matrix.Color333(0, 7, 0)); //right pupil
  matrix.drawCircle(40, 7, 1, matrix.Color333(0, 7, 0)); //left pupil
}
void eyeBlink() {
  matrix.fillCircle(40, 7, 4, matrix.Color333(0, 0, 7)); //left eye
  matrix.fillCircle(40, 24, 4, matrix.Color333(0, 0, 7)); //right eye
}
void rightWink() {
  matrix.fillCircle(40, 24, 4, matrix.Color333(0, 0, 7)); //right eye
  matrix.drawCircle(40, 7, 1, matrix.Color333(0, 7, 0)); //left pupil
}
void leftWink() {
  matrix.fillCircle(40, 7, 4, matrix.Color333(0, 0, 7)); //left eye
  matrix.drawCircle(40, 24, 1, matrix.Color333(0, 7, 0)); //right pupil
}
void eyeLeft() {
  matrix.drawLine(44, 5, 44, 9, matrix.Color333(0, 0, 7)); // left eyelid
  matrix.drawLine(43, 4, 43, 10, matrix.Color333(0, 0, 7));
  matrix.drawLine(44, 22, 44, 26, matrix.Color333(0, 0, 7)); // right eyelid
  matrix.drawLine(43, 21, 43, 27, matrix.Color333(0, 0, 7));
  matrix.drawCircle(40, 21, 1, matrix.Color333(0, 7, 0)); //look left_right
  matrix.drawCircle(40, 4, 1, matrix.Color333(0, 7, 0)); //look left_left

}
void eyeRight() {
  matrix.drawLine(44, 5, 44, 9, matrix.Color333(0, 0, 7)); // left eyelid
  matrix.drawLine(43, 4, 43, 10, matrix.Color333(0, 0, 7));
  matrix.drawLine(44, 22, 44, 26, matrix.Color333(0, 0, 7)); // right eyelid
  matrix.drawLine(43, 21, 43, 27, matrix.Color333(0, 0, 7));
  matrix.drawCircle(40, 27, 1, matrix.Color333(0, 7, 0)); //look right_right
  matrix.drawCircle(40, 10, 1, matrix.Color333(0, 7, 0)); //look right_left
}
void mouthNeutral() {
  matrix.drawLine(15, 8, 15, 23, matrix.Color333(7, 0, 0)); //  mouth
}
void smile() {
  matrix.drawCircle(15, 15, 8, matrix.Color333(7, 0, 0)); //circle
  matrix.fillRect(16, 7 , 10, 17, matrix.Color333(0, 0, 0)); //smile
}
void eyebrowNeutral() {
  matrix.drawLine(52, 4, 52, 10, matrix.Color333(7, 0, 0)); // left eyebrow
  matrix.drawLine(52, 21, 52, 27, matrix.Color333(7, 0, 0)); // right eyebrow
}
void eyebrowDown() {
  matrix.drawLine(50, 4, 50, 10, matrix.Color333(7, 0, 0)); // left eyebrow
  matrix.drawLine(50, 21, 50, 27, matrix.Color333(7, 0, 0)); // right eyebrow
}
void eyebrowUp() {
  matrix.drawLine(54, 4, 54, 10, matrix.Color333(7, 0, 0)); // left eyebrow
  matrix.drawLine(54, 21, 54, 27, matrix.Color333(7, 0, 0)); // right eyebrow
}
void Nose() {
  matrix.drawRect(27, 15, 10, 2, matrix.Color333(7, 0, 0)); // nose
}
void loop() {

  eyeData = Serial.read();
  uData = Serial.read();
  lData = Serial.read();

  matrix.fillScreen(0);
  Nose();
  eyeReset();

  if (eyeData == '0') {
    eyeNeutral();
  }
  else if (eyeData == '1') {
    eyeBlink();
  }
  else if (eyeData == '2') {
    leftWink();
  }
  else if (eyeData == '3') {
    rightWink();
  }
  else if (eyeData == '4') {
    eyeRight();
  }
  else if (eyeData == '5') {
    eyeLeft();
  }

  if (uData == '0') {
    eyebrowNeutral();
  }
  else if (uData == '1') {
    eyebrowUp();
  }
  else if (uData == '2') {
    eyebrowDown();
  }
  else {
    eyebrowNeutral();
  }
  if (lData == '0') {
    mouthNeutral();
  }
  else if (lData == '1') {
    smile();
  }
  else if (lData == '2') {
    mouthNeutral();
    smile();
  }

  delay(1000);

}
