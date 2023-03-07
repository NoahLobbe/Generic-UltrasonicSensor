/*
 * Datasheet for Ultrasonic sensor:
 * https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
 */

//Set pin definitions and constants
#define TRIGGER_PIN 2
#define ECHO_PIN  3
#define SPEED_OF_SOUND_MM_PER_S 340000

void setup() {
  //tell the Arduino what is connected to it
  //eg. output on TRIGGER_PIN, and input on ECHO_PIN
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIGGER_PIN, LOW); //don’t start getting distance yet to ensure accurate results in main loop

  Serial.begin(9600); //connect serial communication with computer
}

void loop() {
  //send a 10uS trigger pulse
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* Normally speed = distance/time -> distance = speed * time
   * However the soundwave must bounce BACK, therefore takeing twice as long, therefore:
   * 2*distance = speed * time
   *   distance = 0.5 * speed * time
   */
  //Time (in microseconds, uS) how long the ECHO pin pulse is HIGH
  uint16_t duration_uS = pulseIn(ECHO_PIN, HIGH, 0);

  //conversions done inline to prevent inaccuracies through rounding
  uint16_t distance_mm = 0.5 * SPEED_OF_SOUND_MM_PER_S * duration_uS * 1e-6; 

  //display results; helps debugging/calibration
  Serial.print("\nuS: "); 
  Serial.print(duration_uS); 
  Serial.print(" distance (mm): ");
  Serial.print(distance_mm);

  delay(60); //to prevent sensor's sound waves from interfering with itself
}
