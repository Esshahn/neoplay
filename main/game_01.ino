int delay_scroll = 200; 
int delay_player = 30;

unsigned long last_time_player = 0;
unsigned long last_time_scroll = 0;

int player_x = STRIP_WIDTH /2; 
int player_y = STRIP_HEIGHT-1;
int health = 100;

byte border_counter = 0;

void intro_01()
{
  if ( check_fire_player_1() ) game_state = 11;
  clear_pixels();

  border_counter++;

  for (byte y=0; y<=LEVEL_HEIGHT; y++)
  {
  for (byte x=0; x<=LEVEL_WIDTH; x++)
  {
    if (y == 0 || y == LEVEL_HEIGHT || x == 0 || x == LEVEL_WIDTH)
    {
      if (x%2 == y%2 && border_counter < 128) draw_point(x,y,rgb2int(0,50,0));
      if (x%2 != y%2 && border_counter >= 128) draw_point(x,y,rgb2int(0,50,0));
    }
  }
  }
}

void init_display_01()
{
  for(byte y=0; y<NUM_PIXELS; y++) display[y] = 0;
}



void show_world_01()
{  

  // maps every entry in the display array to an LED
  
  byte y = 0;
  byte x = 0;
  for(byte j=0; j<NUM_PIXELS;j++)
  {
         
      int r = 0;
      int g = 0;
      int b = 0;

      if (display[j] == 1)
      {
        r = 0;
        g = 30;
        b = 10;
      }
  
      pixels.setPixelColor( at_pixel(x,y) , pixels.Color(r,g,b));

      x++;
      if(x == 11)
      {
        y++;
        x = 0;
      }

  } 
  
}

void update_level_01()
{
  shift_display_down();

  // generate a random pattern on the first line of the display
  for (byte j=0; j<=LEVEL_WIDTH;j++) display[j] = random(1,16);

}



void read_position_player_1_01()
{
  player_x += !digitalRead(RIGHT) - !digitalRead(LEFT);
  player_y += !digitalRead(DOWN) - !digitalRead(UP);
  player_x = constrain(player_x,0,LEVEL_WIDTH);
  player_y = constrain(player_y,0,LEVEL_HEIGHT);
}

void display_player_01()
{
  pixels.setPixelColor( at_pixel(player_x,player_y), pixels.Color(100-health,health,0)); 
}

void check_collision_01()
{

  int collision_object;

  // needed because of how the LED strips are soldered together
  if (player_y % 2 == 0)
  {
    collision_object = display[at_pixel(LEVEL_WIDTH-player_x,LEVEL_HEIGHT-player_y)];
  } else {
    collision_object = display[at_pixel(player_x,LEVEL_HEIGHT-player_y)];
  }
  
  if (collision_object == 1)
  {
    health-=4;
    tone(8, NOTE_C4, 50);
    if (health <0) health = 0;
  }
  
}

void loop_01()
{

  if ( check_fire_player_1() ) tone(8, NOTE_D8, 50);
  
  if (millis() > last_time_player + delay_player)
  {
    read_position_player_1_01();
    delay_scroll=player_y*10;
    check_collision_01();
    last_time_player = millis();
  }

  if (millis() > last_time_scroll + delay_scroll)
  {
    update_level_01();
    check_collision_01();
    last_time_scroll = millis();
  } 
  
  show_world_01();
  display_player_01();

}
