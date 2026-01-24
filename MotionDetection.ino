#include<Wire.h>
#include<MPU6050.h>
#include <math.h>

MPU6050 mpu;
int buzzerPin = 13;
int threshold = 0.15;
float accel_data[2]; 
bool moving; 
unsigned int counter = 0;
unsigned int timer = 0;

void addNewData(float newdata)
{
  // Shifts the old data from index 1 to 0 
   accel_data[0] = accel_data[1];

   // Adds new data to index 1 
   accel_data[1] = newdata;
}

void setup() {
 Serial.begin(115200);
 pinMode(buzzerPin, OUTPUT);

 Serial.println("Initialize MPU6050");

 while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
   Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
   delay(500);
 }

  // If you want, you can set accelerometer offsets
  // mpu.setAccelOffsetX();
  // mpu.setAccelOffsetY();
  // mpu.setAccelOffsetZ();
 
 checkSettings();
 
}

void checkSettings()
{
 Serial.println();
 
 Serial.print(" * Sleep Mode:            ");
 Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
 
 Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
 
 Serial.print(" * Accelerometer:         ");
 switch(mpu.getRange()){
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
 } 

 Serial.print(" * Accelerometer offsets: ");
 Serial.print(mpu.getAccelOffsetX());
 Serial.print(" / ");
 Serial.print(mpu.getAccelOffsetY());
 Serial.print(" / ");
 Serial.println(mpu.getAccelOffsetZ());
 
 Serial.println();
}

void loop() {
 	Vector rawAccel = mpu.readRawAccel();
 	Vector normAccel = mpu.readNormalizeAccel();

 	Serial.print(" Xraw = ");
 	Serial.print(rawAccel.XAxis);
 	Serial.print(" Yraw = ");
 	Serial.print(rawAccel.YAxis);
 	Serial.print(" Zraw = ");

 	Serial.println(rawAccel.ZAxis);
 	Serial.print(" Xnorm = ");
 	Serial.print(normAccel.XAxis);
 	Serial.print(" Ynorm = ");
 	Serial.print(normAccel.YAxis);
 	Serial.print(" Znorm = ");
 	Serial.println(normAccel.ZAxis);
 	
  float ax_g = rawAccel.XAxis / 16384;
  float ay_g = rawAccel.YAxis / 16384;
  float az_g = rawAccel.ZAxis / 16384; 

  
  Serial.print("Acceleration on X Axis = ");
  Serial.println(ax_g);
  Serial.print("Acceleration on Y Axis = ");
  Serial.println(ay_g);
  Serial.print("Acceleration on Z Axis = ");
  Serial.println(az_g);

  float accel_Total = sqrt(ax_g * ax_g + ay_g * ay_g);
  Serial.print("Total Acceleration = ");
  Serial.println(accel_Total);

  addNewData(accel_Total);
  
  //Serial.print("First in the Array = ");
  //Serial.println(accel_data[0]);
  //Serial.print("Second in the Array = ");
  //Serial.println(accel_data[1]);

  float difference = abs(accel_data[1] - accel_data[0]);
  Serial.print("The Difference is ");
  Serial.println(difference);
  

  // If the difference between the data in the array is more than 0.1 meaning the player is moving 
  if(difference > 0.1)
  {
    moving = true; 
    counter = 0; // resets the timer
  }
  else // if the value is less than 0.1 than the player is moving 
  {
    moving = false;
    counter++; // A Pseduo timer that goes up everytime the player isn't moving 
  }

  Serial.print("Counter = ");
  Serial.println(counter);

  if(counter >= 7)
  {
    tone(buzzerPin, 1000, 500);
  }
  

  


  Serial.print("Is player moving? = ");
  Serial.println(moving);

  timer++;
  Serial.print("Timer: ");
  Serial.println(timer);

  if(timer >= 360 && timer <= 400)
  {
    tone(buzzerPin, 500, 500);
  
  }

 	delay(500);

  
}