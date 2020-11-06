#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char sb = 1;
static int x = 500;
static char dim_state = 0;

char toggle_red()		/* always toggle! */
{
 static char state = 0;

 switch (state) {
 case 0:
  red_on = 1;
  state = 1;
  break;
 case 1:
  red_on = 1;
  state = 0;
  break;
}
 led_changed = 1;
 led_update();
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

void two_beats(){
  static char two_state = 0;
  switch(two_state){
  case 0:
    turn_on_green();
    buzzer_set_period(0);
    two_state = 1;
    break;
  case 1:
    green_on = 1;
    red_on = 1;
    buzzer_set_period(1000);
    two_state = 2;
    led_changed = 1;
    led_update();
    break;
  case 2:
    turn_on_red();
    buzzer_set_period(0);
    two_state = 3;
    break;
  case 3:
    green_on = 1;
    red_on = 1;
    buzzer_set_period(1000);
    two_state = 0;
    led_changed = 1;
    led_update();
    break;
  }
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

void dimmer()
{
  switch(dim_state){
  case 0: //25 %
    toggle_25();
    toggle_25();
    toggle_25();
    toggle_25();
    dim_state = 1;
    break;
  case 1: //50 %
    // toggle_red();
    // toggle_red();
    dim_state = 2;
    break;
  case 2: //75 %
    toggle_75();
    toggle_75();
    toggle_75();
    toggle_75();
    dim_state = 0;
    break;
  }
}

void toggle_25()
{
  switch(dim_state){
  case 0:
    red_on = 1;
    green_on = 1;
    dim_state = 1;
    break;
  case 1:
    red_on = 0;
    green_on = 0;
    dim_state = 2;
    break;
  case 2:
    red_on = 0;
    green_on = 0;
    dim_state = 3;
    break;
  case 3:
    red_on = 0;
    green_on =0;
    dim_state = 0;
  }
  led_changed = 1;
  led_update();
}

void toggle_75()
{
  switch(dim_state){
  case 0:
    red_on = 1;
    green_on = 1;
    dim_state = 1;
    break;
  case 1:
    red_on = 1;
    green_on = 1;
    dim_state = 2;
    break;
  case 2:
    red_on = 1;
    green_on = 1;
    dim_state = 3;
    break;
  case 3:
    red_on = 0;
    green_on = 0;
    dim_state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}
void song(){
  static char state = 0;
  switch(state){
    case 0:
      buzzer_set_period(2000000/2500);
      state++;
      break;
  case 1:
    buzzer_set_period(200000/500);
    state++;
    break;
  }
}

/*
void song(){
  static char note = 0;
 
  int a = 440;
  int c = 524;
  int d = 588;
  int e = 668;
  int f = 699;
  int g = 784;

  switch(note){
  case 0: buzzer_set_period(2000000/a); note++; break;
  case 1:buzzer_set_period(0); note++; break;
  case 2:buzzer_set_period(0); note++; break;
  case 3:buzzer_set_period(2000000/c); note++; break;
  case 4: buzzer_set_period(0); note++; break;
  case 5:buzzer_set_period(2000000/d); note++; break;
  case 6:buzzer_set_period(2000000/d); note++; break;
  case 7: buzzer_set_period(2000000/c); note++; break;
  case 8: buzzer_set_period(0); note++; break;
  case 9: buzzer_set_period(2000000/d); note++; break;
  case 10: buzzer_set_period(2000000/c); note++; break;
  case 11:buzzer_set_period(2000000/d); note++; break;
  case 12:buzzer_set_period(2000000/e); note++; break;
  case 13: buzzer_set_period(0); note = 0; break;
  }
    /* int notes [] = {a,0,0,c,0,d,d,c,0,d,c,d,e,0,d,c,a,0,g,a,0,c,0,a,g,f,d,0,a,c,0,d,0,d,c,0,d,0,c,0,d,e,0,c,c,a,0,g,0,a,c,a,g,0,0,f,d,0};
  int i = 0;
  while(i < sizeof(notes)){
    buzzer_set_period(2000000/(notes[i]));
    __delay_cycles(2000000);
    i++;
  }
  buzzer_set_period(0);  
} */
