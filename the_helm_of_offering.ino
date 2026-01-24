// === Pin declarations ===
const int UltrasonicPin   = 5;
const int BuzzerPin       = 6;
const int ButtonPin       = 7;
const int MotorPin        = 8;
const int D_Pin           = 10;
const int RightLED_Pin    = 11;
const int LeftLED_Pin     = 12;
const int A_SensorPin     = A0;


// === Variables for logic and state control ===
int LDRValue              = 0;
int cm                    = 0;
int buttonState           = 0;
const int threshold       = 400;
const int numberOfTests   = 10;
int randNumber;
int averageReading;
const unsigned long ultrasonicCooldown = 3000;
unsigned long lastLaserTime            = 0;

bool isButtonPressed      = false;
bool isLaserReceived      = false;
bool muteUltrasonic       = false;
bool isPlayerSelected;


// This function triggers the ultrasonic sensor and returns
// the time (in microseconds) it takes for the echo to return.
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);   // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Set trigger pin HIGH for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  pinMode(echoPin, INPUT);
  // Measure echo return time in microseconds
  return pulseIn(echoPin, HIGH);
}


// Converts ultrasonic sensor readings into distance-based beep patterns
// — the closer the object, the faster the beeps.
void giveUltrasonicFeedback()
{
  cm = 0.01723 * readUltrasonicDistance(UltrasonicPin, UltrasonicPin);
  Serial.print("Ultrasonic: ");
  Serial.println(cm);
  Serial.println(" ");

  if (cm < 25)
  {
    tone(BuzzerPin, 1000, 20);
    delay(50);
  }
  else if (cm < 50)
  {
    tone(BuzzerPin, 1000, 25);
    delay(100);
  }
  else if (cm <= 75)
  {
    tone(BuzzerPin, 1000, 25);
    delay(150);
    tone(BuzzerPin, 1000, 25);
    delay(500);
  }
  else if (cm <= 100)
  {
    tone(BuzzerPin, 1000, 25);
    delay(200);
    tone(BuzzerPin, 1000, 25);
    delay(600);
  }
  else if (cm <= 125)
  {
    tone(BuzzerPin, 1000, 25);
    delay(250);
    tone(BuzzerPin, 1000, 25);
    delay(750);
  }
  else if (cm <= 150)
  {
    tone(BuzzerPin, 1000, 25);
    delay(400);
    tone(BuzzerPin, 1000, 25);
    delay(900);
  }
}


// Reads ambient light intensity through the LDR.
// If a strong laser or light is detected (above threshold), the ultrasonic
// feedback is muted and a tone is played as an alert.
void giveLightFeedback()
{
  LDRValue = analogRead(A1);
  Serial.print("LDR: ");
  Serial.println(LDRValue);

  if (LDRValue <= 800)
  {
    // light/laser not detected right now
    if (isLaserReceived) {
      // just transitioned from laser-detected to not-detected:
      // start cooldown from this moment
      lastLaserTime = millis();
    }
    isLaserReceived = false; 
  }
  else
  {
    // laser/light detected
    tone(BuzzerPin, 50, 500);
    isLaserReceived = true; 
    lastLaserTime = millis();      // keep updating while laser is present
  }
}


// Uses touch input from the analog sensor to randomly determine
// whether the player becomes the “sacrificial” player. Visual (LED)
// and physical (motor) indicators are used to show the result.
void playerSelection()
{
  digitalWrite(D_Pin, HIGH);
  int totalReading = 0;

  // Perform a series of sensor readings and calculate an average value
  for (int test = 0; test < 10; test++) 
  {
    int reading = analogRead(A_SensorPin);
    totalReading += reading;
    delay(100);  // Short delay between each reading

    if (test > 5)
    {
      averageReading = totalReading / numberOfTests;
      Serial.print("Reading: ");
      Serial.println(averageReading);
    }
  }

  // Determine if both contacts are connected based on the average reading
  if (averageReading < threshold) 
  {
    Serial.println("A connected.");

    if (!isPlayerSelected)
    {
      // Generate a random number between 0 and 10
      randNumber = random(0, 11); 
      Serial.print("Random Number: ");
      Serial.println(randNumber);
      
      // Players have about a 20% chance (values 8–10) of being “selected”
      if (randNumber >= 8)
      {
        isPlayerSelected = true;

        // Indicate selection: LEDs on briefly + motor pulse
        digitalWrite(LeftLED_Pin, HIGH);
        digitalWrite(RightLED_Pin, HIGH);
        delay(10);

        digitalWrite(MotorPin, HIGH);
        delay(1200);
        digitalWrite(MotorPin, LOW);
      }
      else
      {
        // Rapid LED flashes to indicate the player was not selected
        for (int i = 0; i < 2; i++) {
          digitalWrite(LeftLED_Pin, HIGH);
          digitalWrite(RightLED_Pin, HIGH);
          delay(25);
          digitalWrite(LeftLED_Pin, LOW);
          digitalWrite(RightLED_Pin, LOW);
          delay(25);
        }

        isPlayerSelected = false;
      }
    }
  } 
  else 
  {
    // Debug output if contacts are not connected
    Serial.println("A not connected.");
  }

  // Reset digital contact pin
  digitalWrite(D_Pin, LOW);
}


void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(MotorPin, OUTPUT);
  pinMode(D_Pin, OUTPUT);
  pinMode(LeftLED_Pin, OUTPUT);
  pinMode(RightLED_Pin, OUTPUT);

  digitalWrite(D_Pin, LOW);  // Default state
  randomSeed(analogRead(A0));
  isPlayerSelected = false;
}


// === Main game loop ===
void loop()
{
  giveLightFeedback();

  if (!isLaserReceived && !muteUltrasonic && (millis() - lastLaserTime >= ultrasonicCooldown))
  {
    giveUltrasonicFeedback();
  }

  Serial.print("isPlayerSelected: ");
  Serial.println(isPlayerSelected);

  delay(10);  // Can be adjusted depending on gameplay timing

  if (!isPlayerSelected)
  {
    playerSelection();
  }

  delay(10);
}
