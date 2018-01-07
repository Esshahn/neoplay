
/*

  INTRO

*/

int intro_stepper = 0;
int intro_n = 1;
int intro_e = 1;
int intro_o = 1;

void intro_show_logo()
{

  if (intro_stepper == 1)
  {
    intro_n = 1;
    intro_e = 1;
    intro_o = 1;
  }

  if (intro_stepper == 200)
  {
    intro_n = 0;
    intro_e = 1;
    intro_o = 1;
  }

  if (intro_stepper == 240)
  {
    intro_n = 1;
    intro_e = 0;
    intro_o = 1;
  }

  if (intro_stepper == 280)
  {
    intro_n = 1;
    intro_e = 1;
    intro_o = 0;
  }

  if (intro_stepper == 320) intro_stepper = 0;

  intro_stepper++;

  draw_line(0,1+intro_n, String("000"), rgb2int(0,0,40), 1);
  draw_line(1,1+intro_n, String("0"), rgb2int(0,0,40), 1);
  draw_line(2,1+intro_n, String("000"), rgb2int(0,0,40), 1);

  draw_line(4,1+intro_e, String("000"), rgb2int(20,20,0), 1);
  draw_line(5,1+intro_e, String("000"), rgb2int(20,20,0), 1);
  draw_line(6,1+intro_e, String("0.0"), rgb2int(20,20,0), 1);

  draw_line(8,1+intro_o, String("000"), rgb2int(0,40,0), 1);
  draw_line(9,1+intro_o, String("0.0"), rgb2int(0,40,0), 1);
  draw_line(10,1+intro_o, String("000"), rgb2int(0,40,0), 1);

  if (intro_n == 0) draw_line(3+1,0, String("000"), rgb2int(40,0,0));
  if (intro_e == 0) draw_line(3+1,4, String("000"), rgb2int(40,0,0));
  if (intro_o == 0) draw_line(3+1,8, String("000"), rgb2int(40,0,0));
}



void loop_intro()
{
  if ( check_fire_player_1() ) game_state = 10;
 
  clear_pixels();
  intro_show_logo();
} 
