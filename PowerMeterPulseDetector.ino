/*
  Detects pulses from analog input.
  The input will detect LOW when the input voltage is below 2.3 volts, and a HIGH when the input is above 2.4 volts. 
  Whenever a transition from LOW to HIGH is detected a pulse is written to the serial line, and several output pins 
  are set to HIGH. These output pins will be reset to LOW as soon as the input voltage drops to LOW again. 
  
  When booting the output pins will blink 3 times.
  
  Input:
  A0 connects to a photoresitor that is pulled up/down using a xxx Ohm resitor. (the voltage range should be between 0 and 5 volt, 0-2.3 = LOW 2.4-5 = HIGH.
 
  Output:
  Digital pins 2,3 and 13 are configured as output pins.
  Output is written to the Serial line, the output is as follows: 
  "Pulse,[count],[voltage], 
    with count the amount of pulses since start (this will overflow) and 
    voltage the voltage in millivolts where the transition from low to high was detected. (this should be close to 2400).

 Copyright 2014 Oliver May oliver@levvie.be
 You are free to use and distribute this program under the terms of the AGPL.
 */
 
  // Remember the previous state (HIGH or LOW)
  boolean laststate = false;
  
   
  int pulses = 0;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  for (int i = 0; i < 3; i++) {
    digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(250);               // wait for a while
    
    digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(250);              // wait for a while
  }
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);


  if (voltage <= 2.3 && !laststate) {
    laststate = true;
    digitalWrite(2, LOW); 
    digitalWrite(3, LOW); 
    digitalWrite(13, LOW); 
  } else if (voltage > 2.4 && laststate) {
    laststate = false;
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH); 
    digitalWrite(13, HIGH);
    Serial.println("Pulse," + String(pulses, DEC) + "," + String((int) (voltage * 1000), DEC));
    pulses++;
  } 

}
