#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char sb = 1;
static int x = 500;

char toggle_red()		/* always toggle! */
{
 static char state = 0;

 switch (state) {
 case 0:
  red_on = 1;
  state = 1;
  break;
 case 1:
  red_on = 0;
  state = 0;
  break;
}
 return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
char changed = 0;
if (red_on) {
  green_on ^= 1;
  changed = 1;
}
return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
 char changed = 0;

  
 static enum {R=0, G=1} color = G;
 switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
 }

 led_changed = changed;
 led_update();
}

void go_down()               /* will set sb to move frequency down */
{
  sb = 0;
  turn_on_red();
}

void go_up()                // will set sb to move frequency up
{
  sb = 1;
  turn_on_green();
}

void turn_on_red()      /* turns red light on and green off */
{
  red_on = 1;
  green_on = 0;
  led_changed = 1;
  led_update();
}

void turn_on_green()     /*turns on green light and red off */
{
  green_on = 1;
  red_on = 0;
  led_changed = 1;
  led_update();
}

void buzzer_advance()
{
  if(sb){
    x += 225;  
  }
  else{
    x -= 450;
  }
  buzzer_set_period(2000000/x); //set buzzer frequency
}

void main_siren() //state machine for siren
{
  static char state = 0;
  switch(state){
  case 0:
  case 1: //for two states it will do the same thing (go up)
    go_up();
    state++;
    break;
  case 2:
    go_down();
    state = 0;
  default:
    break;
  }
}



