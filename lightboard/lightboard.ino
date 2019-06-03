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
int state = 0;
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);


void setup() {
  matrix.begin();
  Serial.begin(9600);
}
void loop() {

  for (int i = 0; i < 5; i++) {
    eyeData = Serial.read();
    uData = Serial.read();
    uPower = Serial.read();
    lData = Serial.read();
    lPower = Serial.read();
  }
  if (state == 0) {
    matrix.drawLine(55, 21, 55, 27, matrix.Color333(7, 7, 0)); // right eyebrowup
    matrix.drawLine(55, 4, 55, 10, matrix.Color333(7, 7, 0)); // left eyebrowup
    matrix.drawLine(44, 5, 44, 9, matrix.Color333(0, 0, 7)); // left eyelid
    matrix.drawLine(43, 4, 43, 10, matrix.Color333(0, 0, 7));
    matrix.drawLine(44, 22, 44, 26, matrix.Color333(0, 0, 7)); // right eyelid
    matrix.drawLine(43, 21, 43, 27, matrix.Color333(0, 0, 7));
    matrix.drawCircle(40, 21, 1, matrix.Color333(7, 7, 0)); //look left_right
    matrix.drawCircle(40, 4, 1, matrix.Color333(7, 7, 0)); //look left_left
    matrix.drawRect(27, 15, 10, 2, matrix.Color333(7, 0, 0)); // nose
    matrix.drawLine(15, 8, 15, 23, matrix.Color333(0, 0, 7)); //  mouth
    matrix.drawCircle(40, 7, 5, matrix.Color333(0, 0, 7)); //left eye
    matrix.drawCircle(40, 24, 5, matrix.Color333(0, 0, 7)); //right eye
    delay(1000);
    matrix.drawLine(55, 21, 55, 27, matrix.Color333(0, 0, 0)); // right eyebrowup
    matrix.drawLine(55, 4, 55, 10, matrix.Color333(0, 0, 0)); // left eyebrowup
    matrix.drawCircle(40, 21, 1, matrix.Color333(0, 0, 0)); //look left_right
    matrix.drawCircle(40, 4, 1, matrix.Color333(0, 0, 0)); //look left_left
    state = 1;
  }
  if (state == 1) {
    matrix.drawCircle(40, 24, 5, matrix.Color333(0, 0, 7)); //right eye
    matrix.drawCircle(40, 24, 1, matrix.Color333(0, 7, 0)); //right pupil
    matrix.drawCircle(40, 7, 5, matrix.Color333(0, 0, 7)); //left eye
    matrix.drawCircle(40, 7, 1, matrix.Color333(0, 7, 0)); //left pupil
    matrix.drawRect(27, 15, 10, 2, matrix.Color333(7, 0, 0)); // nose
     matrix.drawLine(15, 8, 15, 23, matrix.Color333(0, 0, 0)); //  mouth
    matrix.drawCircle(15, 15, 8, matrix.Color333(7, 0, 0)); //left pupil
    matrix.fillRect(16, 7 ,10, 17, matrix.Color333(0, 0, 0)); //smile
    matrix.fillCircle(40, 7, 4, matrix.Color333(0, 0, 7)); //left eye
    matrix.fillCircle(40, 24, 4, matrix.Color333(0, 0, 7)); //right eye

    delay(1000);
    matrix.drawCircle(40, 24, 1, matrix.Color333(0, 0, 0)); //right pupil
    matrix.drawCircle(40, 7, 1, matrix.Color333(0, 0, 0)); //left pupil


    state = 2;
  }
  if (state == 2) {
    matrix.drawLine(44, 5, 44, 9, matrix.Color333(0, 0, 7)); // left eyelid
    matrix.drawLine(43, 4, 43, 10, matrix.Color333(0, 0, 7));
    matrix.drawLine(44, 22, 44, 26, matrix.Color333(0, 0, 7)); // right eyelid
    matrix.drawLine(43, 21, 43, 27, matrix.Color333(0, 0, 7));
    matrix.drawCircle(40, 27, 1, matrix.Color333(7, 7, 0)); //look right_right
    matrix.drawCircle(40, 10, 1, matrix.Color333(7, 7, 0)); //look right_left
    matrix.drawLine(15, 8, 15, 23, matrix.Color333(0, 0, 0)); //  mouth
    matrix.drawLine(49, 4, 49, 10, matrix.Color333(7, 0, 0)); // left eyebrow
    matrix.drawLine(49, 21, 49, 27, matrix.Color333(7, 0, 0)); // right eyebrow
    matrix.drawRect(27, 15, 10, 2, matrix.Color333(7, 0, 0)); // nose
    matrix.drawCircle(40, 7, 5, matrix.Color333(0, 0, 7)); //left eye
    matrix.drawCircle(40, 24, 5, matrix.Color333(0, 0, 7)); //right eye
    matrix.fillCircle(40, 7, 5, matrix.Color333(0, 0, 0)); //left eye
    matrix.fillCircle(40, 24, 5, matrix.Color333(0, 0, 0)); //right eye
  }

}
 
