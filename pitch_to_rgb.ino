#include "math.h"
// float middle_c = log(261.626);
float middle_c = log(8.176);

int r;
int g;
int b;
int rgb;
int rgb_read[] = {0, 0, 0};
int r_read;
int g_read;
int b_read;
float multiplier = 1.05946309436;

long float_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int get_rgb(int pitch, int *rgb) {
  float log_pitch = log(double(pitch)) / middle_c;
  int nearest_int = int(log_pitch);
  log_pitch = (log_pitch - nearest_int) * 6;
  // Serial.print(log_pitch);
  // log_pitch = fmod(log_pitch, middle_c) / middle_c * 6;
  Serial.println(log_pitch);
  // Serial.print(nearest_int);

  if (log_pitch < 1) {
    r = 255;
    g = int(float_map(log_pitch, 0, 1, 0, 255));
    b = 0;
  } else if (log_pitch < 2) {
    r = int(float_map(log_pitch, 1, 2, 255, 0));
    g = 255;
    b - 0;
  } else if (log_pitch < 3) {
    r = 0;
    g = 255;
    b = int(float_map(log_pitch, 2, 3, 0, 255));
  } else if (log_pitch < 4) {
    r = 0;
    g = int(float_map(log_pitch, 3, 4, 255, 0));
    b = 255;
  } else if (log_pitch < 5) {
    r = int(float_map(log_pitch, 4, 5, 0, 255));
    g = 0;
    b = 255;
  } else {
    r = 255;
    g = 0;
    b = int(float_map(log_pitch, 5, 6, 255, 0));
  }
  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;
  // return rgb;
}

int r_pin = 10;
int g_pin = 9;
int b_pin = 11;
int speakerPin = 5;

int pitch = 523.251;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  get_rgb(pitch, rgb_read);
  // r_read = rgb_read / 1000000;
  // g_read = (rgb_read % 1000000) / 1000;
  // b_read = (rgb_read / 1000);
  // Serial.print(rgb_read[0]);
  // Serial.print("   |   ");
  // Serial.print(rgb_read[1]);
  // Serial.print("   |   ");
  // Serial.println(rgb_read[2]);

  analogWrite(r_pin, rgb_read[0]);
  analogWrite(g_pin, rgb_read[1]);
  analogWrite(b_pin, rgb_read[2]);

  tone(speakerPin, pitch);
  // Serial.print(r_read);
  // Serial.print("   |   ");
  // Serial.print(g_read);
  // Serial.print("   |   ");
  // Serial.println(b_read);
  pitch *= multiplier;
  if (pitch > 1046.502) {
    multiplier = 0.943874312682;
  }
  if (pitch < 130.813) {
    multiplier = 1.05946309436;
  }
  delay(200);
}
