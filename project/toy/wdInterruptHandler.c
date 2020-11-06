#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "led.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char count = 0;
  /* if ((++count % 25) == 0) { //10 steps every second 
    buzzer_advance();
  } /*
  /* if(count == 250){
    main_siren();
    count = 0;
  } */
  if(++count == 2){
    dimmer();
    count = 0;
  }
}
