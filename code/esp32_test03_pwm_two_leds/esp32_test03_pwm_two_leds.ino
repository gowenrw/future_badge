// the number of the LED pin
const int LED01Pin = 12;  // 12 corresponds to GPIO12
const int LED02Pin = 13; // 13 corresponds to GPIO13

// setting PWM properties
const int freq = 5000;
const int PWMChannel0 = 0;
const int PWMChannel1 = 1;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites per channel
  ledcSetup(PWMChannel0, freq, resolution);
  ledcSetup(PWMChannel1, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED01Pin, PWMChannel0);
  ledcAttachPin(LED02Pin, PWMChannel1);

  // setup the serial output baud rate
  Serial.begin(115200);
}
 
void loop(){
  // increase the LED brightness
  //for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
  //  ledcWrite(ledChannel, dutyCycle);
  //  delay(15);
  //}
  
  // Set Delay Time [in ms]
  int DelayTime = 10;

  // Iterate 0 to 254
  for(int i=0; i<255; i++){
    // Set the LED01 value to iteration value using esp pwm channel write
    // Start off and slowly get brighter to full on
    ledcWrite(PWMChannel0, i);
    // Set the LED02 value to 255-iteration value using esp pwm channel write
    // Start on and slowly get dimmer to full off
    ledcWrite(PWMChannel1, (255 - i));
    // Print current LED value to serial console for troubleshooting
    Serial.print(" Iteration=");
    Serial.println(i);
    // Pause the loop to display LED
    delay(DelayTime);
  }
  
  // Iterate 255 to 1
  for(int i=255; i>0; i--){
    // Set the LED01 value to iteration value using esp pwm channel write
    // Start on and slowly get dimmer to full off
    ledcWrite(PWMChannel0, i);
    // Set the LED02 value to 255-iteration value using esp pwm channel write
    // Start off and slowly get brighter to full on
    ledcWrite(PWMChannel1, (255 - i));
    // Print current LED value to serial console for troubleshooting
    Serial.print(" Iteration=");
    Serial.println(i);
    // Pause the loop to display LED
    delay(DelayTime);
  }



}