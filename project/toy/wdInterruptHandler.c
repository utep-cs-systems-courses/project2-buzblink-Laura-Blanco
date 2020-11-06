#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

char bstate;
void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char count = 0;
  switch(bstate){
  case 1: //button 1
    if(++count == 62){ //every 1/4 second
     buzzer_set_period(0); //clear buzzer before hand
     two_beats();
     count = 0;
   }
   break;
  case 2: //button 2
    if(++count == 2){
      buzzer_set_period(0); //clear buzzer 
     dimmer();
     count = 0;
    }
    break;
  case 3: //button 3
    if((++count % 25) == 0)//10 steps every second 
      buzzer_advance();
    if((count == 250)){  //every second
      main_siren();
      count = 0;
    }
    break;
  case 4: //button 4
    buzzer_set_period(0); //turns off everything
    red_on = 0;
    green_on = 0;
    led_changed = 1;
    led_update();
    count = 0;
    break;
  }
}
