#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

char bstate = 0;
void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char count = 0;
  if(bstate == 1 && (++count == 125))){
      dimmer();
      buzzer_set_period(0);
      count = 0;
  }
  if(bstate == 2 && ){
    if(++count == 2){
      song();
      red_on = 0;
      green_on = 0;
      led_changed = 1;
      led_update();
      count = 0;
    }
X4  }
  if(bstate == 3){
   //10 steps every second 
    if((count % 25) == 0){
      buzzer_advance();
    }
    if((count == 250)){
      main_siren();
      count = 0;
    }
  }
  if(bstate == 4){
    buzzer_set_period(0);
    red_on = 0;
    green_on = 0;
    led_changed = 1;
    led_update();
    count = 0;
  }
}
