 #include "Flowmeter.h"
// default: 6
//0.468
#define CALIBRATION_COEFFICIENT 0.16
// previos reading 0.34

using namespace std;
 volatile int Flowmeter::flow_count;

Flowmeter::Flowmeter(byte pin) {
  this->pin = pin;
  this->calibration_coefficient = CALIBRATION_COEFFICIENT; 
  this->currentTime = millis();
  this->cloopTime = currentTime;
  init();
}
void Flowmeter::init() {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH); // Optional Internal Pull-Up
  attachInterrupt(1, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  


}

 void Flowmeter::flow() {
  flow_count++;
}

void Flowmeter::run(Clara &clara) { // Has to be passed as a reference! See p. 255 in "Grundkurs C++"
   currentTime = millis();
   double delta_t; 
   double delta_V;
   
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {  
      delta_t = (currentTime - cloopTime)/1000; // delta t in 
      cloopTime = currentTime; // Updates cloopTime
      //Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      flow_frequency = flow_count / delta_t;
     // Serial.println(flow_frequency);
      l_hour = (flow_frequency * 60 / calibration_coefficient); // (Pulse frequency x 60 min) / calibration_coefficient = flowrate in L/hour
      l_min = l_hour  / 60.0; // flowrate in l/min
      flow_count = 0; // Reset Counter  

     
      clara.set_flow(l_min);
     // Serial.println(l_min);

   }
   // After 50 days, the millis()-function starts from 0 again
   else if(currentTime < cloopTime){
    currentTime = millis();
    cloopTime = currentTime;
   }

    

}
