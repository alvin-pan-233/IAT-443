#include <Adafruit_CircuitPlayground.h>

//-----------------Defined Classes
// the smooth class is studied from IAT 320 lecture by Mark Nazemi
class Smooth {
  private:
    float *window;
    size_t window_size;
    int window_pos;
    float window_sum;
  public:
    Smooth(size_t n) {
      window_size = n;
      window_pos = 0;
      window = new float[window_size]();
      window_sum = 0;
    }
    ~Smooth() {
      delete[] window;
    }
    float update(float x) {
      window_sum = window_sum - window[window_pos] + x;
      window[window_pos] = x;
      window_pos = (window_pos + 1) % window_size;
      return window_sum / window_size;
    }
};

//-----------------Globals
float xvel, smooth_xvel, yvel, smooth_yvel, zvel, smooth_zvel;  //accelerometer's x,y,z value

float brightness, smooth_brightness;  //light sensor

int leftbut, smooth_leftbut; //left button / touch sensor
int rigbut, smooth_rigbut; //right button

//set up the smoothed value
Smooth sx(10);
Smooth sy(10);
Smooth sz(10);

Smooth sl(1); //smooth left-button
Smooth sr(1); //smooth right-button
Smooth sb(10); //smooth brightness

//-----------------Set up
void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

//-----------------Loop
void loop() {
  leftbut = CircuitPlayground.leftButton();
  rigbut = CircuitPlayground.rightButton();

  brightness = CircuitPlayground.lightSensor();

  /*
  xvel = CircuitPlayground.motionX();
  yvel = CircuitPlayground.motionY();
  zvel = CircuitPlayground.motionZ();
    
  smooth_xvel = sx.update(xvel);
  smooth_yvel = sy.update(yvel);
  smooth_zvel = sz.update(zvel);
  */

  //smooth the sensor data using the smooth class
  smooth_leftbut = sl.update(leftbut);
  smooth_rigbut = sr.update(rigbut);
  smooth_brightness = sb.update(brightness);

  //send sensor data to Processing
  Serial.print(smooth_leftbut);
  Serial.print(" ");
  Serial.print(smooth_rigbut);
  Serial.print(" "); 
  Serial.println(brightness);
  /*
  Serial.print(" ");
  Serial.print(smooth_xvel);
  Serial.print(" ");
  Serial.print(smooth_yvel);
  Serial.print(" ");
  Serial.println(smooth_zvel);
  */
  delay(100);
}
