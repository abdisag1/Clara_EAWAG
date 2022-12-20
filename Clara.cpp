
/** Author Abdisa Gemechu 
 *  contact myabdisa@gmail.com 
 * This is the main function of the system .
*/
#include "Clara.h"
using namespace std;
// init-methods
Clara::Clara() {
  this->state ;
  this->voltage ;
  this->batterypercentage;
  this->flow = 0;
  this->eflow = 0;
  this->wata_ready;
  init();
}
void Clara::init() {
}


// flow-methods
float Clara:: get_voltage() {
  return voltage;
}
void Clara:: set_voltage(float voltage) {
  this->voltage = voltage;
}
float Clara:: get_batterypercentage() {
  return batterypercentage;
}
void Clara:: set_batterypercentage(float batterypercentage) {
  this->batterypercentage = batterypercentage;
}

int Clara::get_liquidlevel_1(){
  return liquidlevel_1;
}
void Clara::set_liquidlevel_1(int liquidlevel_1){
  this->liquidlevel_1 = liquidlevel_1;
}

int Clara::get_liquidlevel_2(){
  return liquidlevel_2;
}
void Clara::set_liquidlevel_2(int liquidlevel_2){
  this->liquidlevel_2 = liquidlevel_2;
}
int Clara::get_liquidlevel_3(){
  return liquidlevel_3;
}
void Clara::set_liquidlevel_3(int liquidlevel_3){
  this->liquidlevel_3 = liquidlevel_3;
}



double Clara::get_flow() {
  return flow;
}
void Clara::set_flow(double flow) {
  this->flow = flow;
}

int Clara::get_state() {
  return state;
}
void Clara::set_state(int state) {
  this->state = state;
}

    
void Clara:: Open_Valve(int v_state,int pin){
 this->v_state = v_state;
 this->pin =pin;
  if (v_state==1){
     digitalWrite(this->pin, HIGH);
    }
  }
  
  
  void Clara:: Close_Valve(int v_state,int pin){
  this->v_state = v_state;
  if (v_state==1){
    digitalWrite(this->pin, LOW);
    }
  }

  
  
  void Clara:: Start_wata(int wa_state,int pin){
 this->v_state = wa_state;
 this->pin =pin;
  if (wa_state==1){
     digitalWrite(this->pin, HIGH);
    }
  }

  void Clara:: Stop_wata(int wa_state,int pin){
 this->v_state = wa_state;
 this->pin =pin;
  if (wa_state==1){
     digitalWrite(this->pin, HIGH);
    }
  }

 void Clara ::timerCallback(){ //This is the interrupt request
timer++; //the above timer creates a delay of 1 milisecond
}

  

void Clara:: Disinfection(){
  
  long RestTime =  watamin;
  while (RestTime>0){
    // LCD-Display-Start
    String DisTime = String(RestTime/1000);
   // LCDWrite("Disinfect. Time", "Left: "+DisTime+" s"); 
  // Serial.println(DisTime);
    // LCD-Display-Stop
    RestTime = RestTime - 1000;
    delay(1000);
    }
  
  }
