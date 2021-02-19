#include <Adafruit_CircuitPlayground.h>

// the smooth class is from IAT 320 lecture by Mark Nazemi
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


float xvel, smooth_xvel, yvel, smooth_yvel, zvel, smooth_zvel;

float brightness, smooth_brightness;

int leftbut, smooth_leftbut;

//set up the smoothed value
Smooth sx(10);
Smooth sy(10);
Smooth sz(10);

Smooth sl(5); //smooth left-button
Smooth sb(10); //smooth brightness

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  leftbut = CircuitPlayground.leftButton();
  brightness = CircuitPlayground.lightSensor();
  
  xvel = CircuitPlayground.motionX();
  yvel = CircuitPlayground.motionY();
  zvel = CircuitPlayground.motionZ();
    
  smooth_xvel = sx.update(xvel);
  smooth_yvel = sy.update(yvel);
  smooth_zvel = sz.update(zvel);

  smooth_leftbut = sl.update(leftbut);
  smooth_brightness = sb.update(brightness);

  //Serial.print(smooth_leftbut);
  //Serial.print(" ");
  Serial.print(brightness);
  Serial.print(" ");
  Serial.print(smooth_xvel);
  Serial.print(" ");
  Serial.print(smooth_yvel);
  Serial.print(" ");
  Serial.println(smooth_zvel);

  
  delay(100);
}
