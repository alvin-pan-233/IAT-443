import processing.serial.*;

Serial myPort; //set up the port to recevive data Arduino data

String data; 
float bs, lb, rb, x, y, z; //sensor data & its types 

PImage park1, park2, tree; //array to store images
int pixcells =2;  //pixcelzted the image

void setup() {
  size(800, 500); //screen size

  printArray(Serial.list()); //print the list of my computer port
  myPort = new Serial(this, Serial.list()[2], 9600); //open the port
  myPort.bufferUntil('\n'); //load the port 
  
  //tree = loadImage("tree.jpg"); //load the image
  
  park1 = loadImage("park1.jpg"); //load the image
  park1.loadPixels();
  
  //park2= loadImage("park2.jpg"); //load the image
  
  background(0);
  loadPixels();
}

void draw() {
  //load all the sensor data
  while (myPort.available() > 0) {
    data = myPort.readStringUntil('\n');
  }
  if (data != null) {
    float[] nums = float(split(trim(data), ' ')); //split the date

    //pixelate the image
    for (int x = 0; x < park1.width; x++) {
      for (int y = 0; y < park1.height; y++) {
          
        //map the light sensor data to the color range
        bs = map(nums[2], 0, 999, 0, 100); 
        //println(bs);
        
        int loc = x + y * park1.width; //get the pixel location
        
        //get the r,g,b data
        float r = red(park1.pixels[loc]);
        float g = green(park1.pixels[loc]);
        float b = blue(park1.pixels[loc]);
        
        /*
        color tempC = park1.pixels[loc];
        fill(tempC);
        noStroke();
        rect(x, y, b, b);
        */
        
        //-----------------Light sensor
        color park1C = color(r,g,b,bs);
        //tint(255,bs); 
        pixels[y*width + x] = park1C;
      }
    }
    
    //-----------------touch sensor
    
    //map the button sensor data
    lb = map(nums[0], 0, 1, 0, 1);
    rb = map(nums[1], 0, 1, 0, 1);
    
    //adding 'stars' to the image
    /*
    if(lb == 1){
      fill(255);
      noStroke();
      ellipse(random(park1.width),random(park1.height), 30, 30);
    }
    */
    //adding 'nose' to the image
    if(lb == 1 == true){
      filter(THRESHOLD);
    }
    //adding blur effect to the image
    if(rb == 1 == true){
      filter(BLUR,5);
    }
  }
  updatePixels();
}
