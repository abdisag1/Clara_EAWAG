#include "Display.h"
#include <LiquidCrystal_I2C.h>

using namespace std;

int state = 2;


Display::Display(byte pin) {
  this-> pin = pin;
  this-> text = "";

  init();

}



void Display::init() { // put your setup code here, to run once:
  // put your setup code here, to run once:
 

  Serial.begin(9600);

}

void Display::run(Clara &clara, LiquidCrystal_I2C &lcd) { // Has to be passed as a reference! See p. 255 in "Grundkurs C++"

  state = clara.get_state();
  float cl_pumped = clara.pump_count * clara.volume_per_pump;
  String flow_string = String(clara.get_flow()) + " l/min"; // Has to be replaced of course
  String chlorine_left = String(cl_pumped); // Has to be replaced of course
  String state_display = String("Normal");
  String battery_level = String(clara.get_voltage());

//inital welcome screen
if (state ==1) { 
    String message1 = "Clara Begins";
    String message2 = "Add 120ml of bine";
    String message3 = "& add Water Until 2L";
    String message4 = "into the Prod bottle";
     
    LCDWrite(message1,message2,message3,message4, lcd);
    delay(6000);
    clara.set_state(4);
    //Serial.println("1 sec");
  }


  else if (state == 2) {
    cl_pumped = clara.pump_count * clara.volume_per_pump;

    flow_string = String(clara.get_flow()) + " l/min"; // Has to be replaced of course
    chlorine_left = String(cl_pumped); // Has to be replaced of course
    state_display = String("In Production");
    battery_level = String(clara.get_voltage());

    LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + chlorine_left + " L" , "Battery.V: " + battery_level, "State: " + state_display, lcd);



  }

  else if (state == 3) {
    cl_pumped = clara.pump_count * clara.volume_per_pump;

    flow_string = String(clara.get_flow()) + " l/min"; // Has to be replaced of course
    chlorine_left = String(cl_pumped); // Has to be replaced of course
    state_display = String("Ready for Prod");
    battery_level = String(clara.get_voltage());

    LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + chlorine_left + " L" , "Battery.V: " + battery_level, "State: " + state_display, lcd);

    


  }


  else if (state == 4) {


    cl_pumped = clara.pump_count * clara.volume_per_pump;
    flow_string = String(clara.get_flow()) + " l/min"; // Has to be replaced of course
    chlorine_left = String(cl_pumped); // Has to be replaced of course
    state_display = String("Normal");
    battery_level = String(clara.get_voltage());


    LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + chlorine_left + " L" , "Battery.V: " + battery_level, "State: " + state_display, lcd);



  }
  else if (state == 5) {
    cl_pumped = clara.pump_count * clara.volume_per_pump;
    flow_string = String(clara.get_flow()) + " l/min";
    chlorine_left = String(cl_pumped); // Has to be replaced of course
    state_display = String("Settling");
    battery_level = String(clara.get_voltage());
    LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + chlorine_left + " L" , "Battery.V: " + battery_level, "State: " + state_display, lcd);
  }
  else if (state == 6) {
    cl_pumped = clara.pump_count * clara.volume_per_pump;
    flow_string = String(clara.get_flow()) + " l/min";
    chlorine_left = String(cl_pumped); // Has to be replaced of course

    state_display = String("Valve is opened");
    battery_level = String(clara.get_voltage());
    LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + chlorine_left + " L" , "Battery.V: " + battery_level, "State: " + state_display, lcd);
  }


}

void Display::LCDWrite(String text1, String text2, String text3, String text4, LiquidCrystal_I2C &lcd) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
  lcd.setCursor(0, 2);
  lcd.print(text3);
  lcd.setCursor(0, 3);
  lcd.print(text4);
}
