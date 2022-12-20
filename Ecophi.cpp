

#include "Clara.h"

#include "Ecophi.h"
#define EcoRX       0  //Serial Receive pin
#define EcoTX        1  //Serial Transmit pin
#define EcoTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW
using namespace std;
int i = 0;
int timer = 0;
int time_now = 0;
int timer_s = 0;
int timer4 = 0;
float flowcommulative = 0;
float flowaverage = 0;
  
Ecophi::Ecophi(byte pin0, byte pin1, byte pin2) {
  this->  pin0;
  this->  pin1;
  this->  pin2;

  init();
}
 

void Ecophi::init() {
// put your setup code here, to run once:
  TCCR0A = (1 << WGM01); //Set the CTC mode
  OCR0A = 0xF9; //Value for ORC0A for 1ms

  TIMSK0 |= (1 << OCIE0A); //Set the interrupt request
 // sei(); //Enable interrupt

  TCCR0B |= (1 << CS01); //Set the prescale 1/64 clock
  TCCR0B |= (1 << CS00);
  Serial.begin(9600);
  pinMode(EcoTxControl, OUTPUT);
  digitalWrite(EcoTxControl, RS485Transmit);  // Init Transceiver
  


}
ISR(TIMER0_COMPA_vect) {   //This is the interrupt request
  timer++;
}


void Ecophi::run(Clara &clara) {
  // Has to be passed as a reference! See p. 255 in "Grundkurs C++"

  if (timer >= 500) {
    timer_s++;
    timer = 0;
    float flownow = clara.get_flow(); //get the flow each second from clara.get_flow()
    flowcommulative += flownow;
    //Serial.println("1 sec");
  }

  if (timer_s >= 60) {
    time_now++;
    timer_s = 0;
   // Serial.println("this is 1 min");
  }


  if (time_now >= 4) {
    time_now = 0;

    flowaverage = flowcommulative / 252; //get the average of the four minutes form the commulative of the each second 164
    float eflow = flowaverage;
    int  elevel = clara.get_liquidlevel_3();
    float evotage = clara.get_voltage();
    int cl_produced = clara.get_liquidlevel_1();
    //float cl_pumped = clara.pump_count * clara.volume_per_pump;
    //Serial.println("this is 4 min");
    //Serial.println(flow);
   // if (Serial.available() > 0) 
   // {
   // Serial.print(";");
    //Serial.print("clara:");
    Serial.print(eflow);
    Serial.print(",");
    Serial.print(evotage);
    Serial.print(",");
    Serial.print(elevel);
    Serial.print(",");
    Serial.print(cl_produced);
    //Serial.print(":");
     // }
    flowcommulative = 0;
    flowaverage = 0;
  }

}
