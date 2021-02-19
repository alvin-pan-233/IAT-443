import processing.serial.*;

Serial myPort; //set up the port to recevive data Arduino data

String data; 
float b, x, y, z; //sensor data & its types 

PImage park1, park2, tree; //array to store images
int pixcells =2;  //pixcelzted the image

void setup() {
  size(800, 500); //screen size

  printArray(Serial.list()); //print the list of my computer port
  myPort = new Serial(this, Serial.list()[2], 9600); //open the port
  myPort.bufferUntil('\n'); //load the port 
  
  tree = loadImage("tree.jpg"); //load the image
  park1 = loadImage("park1.jpg"); //load the image
  park2= loadImage("park2.jpg"); //load the image

  background(0);
}

void draw() {
  //load all the sensor data
  while (myPort.available() > 0) {
    data = myPort.readStringUntil('\n');
  }
  if (data != null) {
    float[] nums = float(split(trim(data), ' ')); //split the date

    // ex 6.
    /*
    v = map(nums[0], 50, 80, 0, 2);
     x = map(nums[1], -10, 10, 0, 128);
     y = map(nums[2], -10, 10, 0, 128);
     z = map(nums[3], -10, 10, 0, 128);
     //background(color(v*x,v*y,v*z));
     background(color(x,y,z));
     */
    // ex 7.
    b = map(nums[0], 0, 255, 0, 255);
    x = map(nums[1], -10, 10, 0, 255);
    y = map(nums[2], -10, 10, 0, 255);
    z = map(nums[3], -10, 10, 0, 255);
    //background(color(x, y, z));
    
    for (int x = 0; x < park1.width; x++) {
      for (int y = 0; y < park1.height; y++) {
        int loc = x + y *park1.width;
        
        color tempC = park1.pixels[loc];
        fill(tempC);
        noStroke();
        rect(x, y, pixcells, pixcells);

      }
    }
  }
}
