# Clara EAWAG Readme

- This document serves as a guide for understanding the code used in the first prototype for the Wataclara protype. A prototype that is installed in Referal hospital The code is written for an Arduino-System, using C++. It is not following a school of clean C++-Code however, so that it still uses syntax from C for example. Rather than being particularly cleanly written, the development of the code was focused on the usage of widely used syntax, a simple extensibility, conciseness, and simplicity in general.
Concerning this guide, the focus does not lay on a thorough description of the code to entirely replace the lecture of the code while working on it. The hope however is that it can reduce the study of the relevant parts of the code to a minimum to facilitate especially the extension of the system.
- The document also serves as manual to help further development of the prototype.



## Flow chart of the system
<details><summary>Click to see the flow chart</summary>
<p>

![flowchart](/flowchart.jpg)

</p>
</details>


## schematic diagram of the system
<details><summary>Click to see the schematic diagram</summary>
<p>

![claraplusschematic](/Readme.PNG)

</p>
</details>



***
## some explanations about how the system works 

***

***
## 	OBJECT-ORIENTED PROGRAMMING AS PARADIGM
- The CLARA-system makes two demands which are usually hard to meet with classical procedural programming. The first of these demands is the demand for integrating many different parts that integrate with each other, for example levelsensors, pumps, the flowmeter, or the Echopi monitoring. The second is the demand for multitasking, so that for example the Echopi device can still send a message while the pump is pumping. Both these demands can be met in an easier way with object-oriented programming (OOP).<br />
- The introduction of OOP is going beyond the scope of this document. Two  resources that explain the usage of OOP especially with regards to the Arduino can be found at The Robotics Backend (2020) and adafruit (2020). While The Robotics Backend (2020) has an emphasis on integrating many different parts with each other, adafruit (2020) is having an emphasis of multitasking with the Arduino. Understanding the content of these two resources is vital and a prerequisite for understanding the rest of this document.

***

***
## ARCHITECTURE

- To account for the multitasking aspect (see section 3.1) it is important to understand that this implies that the delay()- function cannot be used when implementing multitasking. The reason for this is simply that it blocks all other code from being executed during the time of its activity.<br />
- As an alternative, for example for the pumping process, the time when the pump starts pumping is saved as a variable. Then in a for loop in every iteration it is checked whether the difference of the current time minus the start time of the pumping process is bigger than the time desired to pump. If so, the process is finished.To continue the example of the pump, this means that an object for the pump is created when the program starts running. This object has a method named run(). In the loop()-function of the main program this run()-method is then called to check whether or not it is necessary to pump chlorine. For this, of course, it is necessary to know how much water is flowing through the flowmeter. As this information is an attribute of the flowmeter-object, it is necessary to have one object which provides methods to get attributes from all the other objects to interlink the objects . This object is the clara-object which is always passed as a reference in the run-method of all the other objects.<br />
- Finally, this leads to the following code interlinking the objects for the pump and the flowmeter, as well as the clara-object. The constructor of the flowmeter and the pump further take the pins for these electronical components as arguments. Note that this is only an excerpt of the main code and that additional objects are used.

```
Clara clara;
Flowmeter flowmeter_used(pin3);
Pump pump_used(pin12);
void loop() {
  flowmeter_used.run(clara);
  pump_used.run(clara);
}

```

***


## The classes and files that are on the code are:
****
## Table of contents
- **[arduino_claraplus_newproto.ino](#arduino_claraplus_new_proto.ino)**
- **[Clara.cpp and Clara.h](#the-clara-class-clara.cpp-and-clara.h)**
- **[Display.cpp and Display.h](#the-display-class-display.h-and-display.cpp)**
- **[Echophi.h and Echophi.cpp](#the-echophi-class-echophi.cpp-and-echophi.h)**
- **[Flowmeter.cpp and Flowmeter.h](#the-flowmeter-class--flowmeter.h-and-flowmeter.cpp)**
- **[Levelsensor.h and Levelsensor.cpp](#the-levelsensor-class-levelsensors.h-and-levelsensor.cpp)**
- **[Pump.cpp and Pump.h](#the-pump-class-pump.h-and-pump.cpp)**
- **[Voltagesensor.cpp and Voltagesensor.h](#the-class-voltagesensor-voltagesensor.h-and-voltagesensor.cpp)**
- **[wata.cpp and wata.h](#wata.cpp-and-wata.h)**
***

***
## arduino_claraplus_new_proto.ino
- Following the lines of the code, first, all the other six classes are included in the main-file using the #include-preprocessor directive. In a second step, the external dependencies are included and, after the pins get assigned a variable name each, the eight objects are constructed. Finally, in the loop-section of the main file, the run()-method is called in every iteration. A little detail here is that the construction of the objects was not possible to do in the setup-section of the Arduino-code for an unknow reason. Therefore, the setup-section is now only containing the initialising of the LCD-display and the serial-monitor <br />
- Also assignment for the pins of the arduino is also done here

***
## The Clara Class Clara.cpp and Clara.h
- The Clara-class is the one class that holds everything together. The run()-method of the object flowmeter_used will use the set_flow()-method of the clara-object to save the current flow as an attribute within the clara-object. As this object is then passed as a reference to the pump-object, the pump-object can then use the get_flow()-method to check what the flow set by the flowmeter is. This information is then used to calculate the total volume of water flowing through the system since the last time the chlorine-solution has been pumped. In this way the clara-class functions as a "communication medium" between the two other classes.
***
| return type   | method        |description  |
| ------------- | ------------- | ----------- |
|               | Clara() | it creates new clara object |
|               | init() | initialize new clara object |
| float         | get_voltage | returns the value of the voltage |
| void         |set_voltage(float volatge)  | sets the value of the voltage
| float         |get_batterypercentage()| returns the value of the battery percentage|
| float         |get_liquidlevel_1()| returns the value of the upper level sensor|
| void         |set_liquidlevel_1(int liquidlevel_1)| sets the value of the upper level sensor|
| float         |get_liquidlevel_2()| returns the value of the lower level sensor|
| void         |set_liquidlevel_2(int liquidlevel_2)| sets the value of the lower level sensor|
| double         |get_flow()| returns the value of the battery percentage|
| void         |set_flow(double flow)| returns the value of the battery percentage|


***

***
## The Flowmeter class  flowmeter.h and flowmeter.cpp
- The Flowmeter-class also has only a run()-method.  this method is updating the flow-attribute of the clara-object once every second using the method set_flow() . To get the information when it is necessary to update the flow-attribute, the flowmeter-class uses an attribute to save the time when the flow-attribute was last updated. The same technique is also used to pump for a certain duration .<br />
- Behind the scenes, the flowmeter is sending a signal every time the wheel spins for a defined angle. These signals, known as "interrupts", are the reason no continuous signal comes from the flowmeter so that one can only calculate average flows by utilising the interrupts per time interval. Further information about flowmeters in general can be found in codebender_cc (2020).
API for the Flowmeter-class.
***
| return type   | method        |description  |
| ------------- | ------------- | ----------- |
|               | Pump() | it creates a new Pump-object |
|   |init()|  is initiating a new Pump-object |
|void|run(Clara & clara| is updating the flow-attribute of the clara-object once a second|
***
***

***
## The Levelsensor Class Levelsensors.h and Levelsensor.cpp

- The init() method will create new levelsensor object for us and it will create inturrupt using timer1 of the arduino. which is better alternative to use than the internal delay() method. by using the three timers we can create three independant interupts.<br />
- Like the other classes befoure the Levelsensor-class also has a run()-method. The run() method inside this class will read the values of the two level sensors form A0 and A1, which are the values of levelsensor on the top and the level sensor at the bottom respectively. <br />
- one problem that we found while testing the level sensors is that they are sensetive in reading zero'. it reads '0' with just small contact. thus the solution was to read the values of each level sensor every 500 ms and store it in an array which can store 20 samples. then we compare the values of these twenty samples if each value is equal to 0. if it is equal to "0" then we say the level sensor.


***



***
## The Pump Class pump.h and pump.cpp
- The pump-class also utilises the run()-method. This method is using the clara.get_flow()-method to check the current flow in the system. The run()-method is integrating the flow through the system to get the volume which was passing through it since the last time the system was pumping. 
 ***
| return type   | method        |description  |
| ------------- | ------------- | ----------- |
|               | Flowmeter() | it creates a new Flowmeter-object |
|   |init()|  is initiating a new Pump-object |
|void|run(Clara & clara| Is checking if it is necessary to pump and if so, does pump|
***
***
***
# The class voltagesensor voltagesensor.h and voltagesensor.cpp
- Like the other classes the voltagesensor-class also utilises the run() method. this method is updating the voltagesensor-attribute of the clara-object each 500ms using the method set_voltage().it reads the value from the analog sensor using the "A2" pin of the arduino and convert it to digital(ADC). <br />

 ***
| return type   | method        |description  |
| ------------- | ------------- | ----------- |
|               | Voltagesensor() | it creates a new Voltagesensor-object |
|   |init()|  is initiating a new Voltagesensor-object |
|void|run(Clara & clara| updates the value of the voltage each 500ms|
***
***



***
## wata.cpp and wata.h
This class contains the major operations of our system.
```
void Wata::init() {
   TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  pinMode(this->pin10, OUTPUT);
    pinMode(this->pin12, OUTPUT);
  Serial.begin(9600);

}
```
- The above code is used to initialize the classes that will be used in our code. it will create a delay using the internal timer module interrupt. if you want to readmore about arduino timer interupts ([Aruino Interupts](https://www.instructables.com/Arduino-Timer-Interrupts/)) <br />
So I used timer2 to create a delay of 1 millisecond. The advantage of using interupt rather than the predefined *delay()* function is that, when you use the delay the system will stop for the specified time. for example if you use *delay(2000)* the system will freeze for 2 seconds. but our system have to to apply multiproccessing since there are may sensors attached to it. thus we have to create a delay using interupt, arduino have three timers timer2 to was used to control the valve and the wata production, whereas timer1 was to read the values from the level sensors and timer0 was to send data to the ecophi monitoring each 4 minuites.
```
ISR(TIMER2_COMPA_vect) {   //This is the interrupt request
  wa_timer++;
} 
```
- The above method is increments wa_timer variable each microsecond. so from the milliseconds we can calculate minuite and hour. 
```
 if ((wa_timer_hr >= 2)&&(wa_state == HIGH)) {  //creates a delay of two hours
        wa_timer_hr = 0;
        digitalWrite(this->pin10,LOW);
      wa_state = LOW;
      clara.wata_ready=1;
      //Serial.println("wata production is complete");
      clara.set_state(4);    
    }
if ((clara.liquidlevel_1==1)&& (clara.wata_ready==0)){
  digitalWrite(this->pin10, HIGH); //start the wata production
 
 wa_state= HIGH;
 flag = true;
  clara.wata_ready=0;
 //Serial.println("wata is in production");
 
 clara.set_state(2);

   //display ont the lcd the process is abour to start
  
  
  }


```
What this part of code does it:
- The lower if condition checks if the liquidlevel in the upper tank is one and checks if the previous sodium hypochlorite is pumped. if this conditions are true it starts the wata production by setting the pin that controls the relay for the wata to HIGH.and it resets the vaue of clara.wata_ready to 0. which means the wata is not ready yet. The clara.set_state(2) method will change the value of our global state variable to 2, which makes the display to show a message that says "In production" notifing that the wata production is on progress. <br />
- The upper if condition checks if the wata state is high two hours wata to be ready and sent the pin to LOW. and the clara.wata_ready is set to 1. which we will use to open the valve if the wata is ready.that value of the clara.state(4) method will change the value of the our global state variable to 4, which makes the display to display the default values that will be displayed ( the flow at the top of the lcd and the amount that have been pumped at the bottom of the lcd display).







***

***
## The display class display.h and display.cpp
- The Display-class only has one public method: The run()-method. This method is used to display the current state of the prototype and fetches all relevant information for what to display from the clara-object. For this, the run()-method of the object display_used (the only instance of the Display-class) uses the method get_state() from the clara-object. The value of state is fetched from by get_state() method.
```
if (state ==1){
//display a message that says "wata production begins" for 5 seconds and then change the state to 2;
}
else if (state ==2){
//displays the message "In Production" at the top of the 16*2 lcd  display and the flow at the bottom of the display
  String flow_string = String(clara.get_flow())+" l/min";
 LCDWrite("In Production","Flow: "+flow_string,lcd);
}
else if (state ==3){
  String flow_strings = String(clara.get_flow())+" l/min";
 LCDWrite("Ready for Production","Flow: "+flow_strings,lcd);
}
else if (state ==4) {
// The default that will be displayed on the 16*2 lcd display at the top the current flow will be displayed and at the bottom the amount of chlorine that is pumped is displayed.
      float cl_pumped=clara.pump_count * clara.volume_per_pump;
        String flow_string = String(clara.get_flow())+" l/min"; // Has to be replaced of course
        String chlorine_pumped = String(cl_pumped); // Has to be replaced of course
        LCDWrite("Flow: "+flow_string,"Volume: "+chlorine_pumped+" L",lcd);
       
}
```

***
***
# The Echophi class Echophi.cpp and Echophi.h
- The purpose of this class to to send a data to a remote monitoring server. A data will be sent every 4 minutes. just like the levelsensor-class the Echophi-class also creates its own unique timer using timer0 of the ardunio. so by using the interupt we can create a delay we want to acheive in our case it is 4 minutes. The run() method will send the values of the parameters like flow,batterylevel,amount of chlorine that have been pumped and the state of the level sensor every 4 minutes.

***
| return type   | method        |description  |
| ------------- | ------------- | ----------- |
|               | Echophi() | it creates a new Echophi-object |
|   |init()|  is initiating a new Echophi-object |
|void|run(Clara & clara| is updating the Echophi-attribute of the clara-object|
***


***





***
## probable bugs and Optimizations that should be done
- one of the things that should be optimized in the next design is : we didn't set a condition a way to control the valve. i.e not to open the valve when the lower tank doesn't have enough space.
- after the sodiumhypochlorite is produced and the valve is opened for 10 min. the system is restarting this problem have to be solved.
 

***









