int delay_scroll = 200; 
int delay_player = 30;

unsigned long last_time_player = 0;
unsigned long last_time_scroll = 0;

int player_x = STRIP_WIDTH /2; 
int player_y = STRIP_HEIGHT-1;
int player_col = 100;
int health = 100;


void init_level()
{
  for(byte y=0; y<NUM_PIXELS; y++) display[y] = 0;
}

void show_world()
{  
  
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
        g = 0;
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

void update_level()
{
  for (int j=NUM_PIXELS-LEVEL_WIDTH; j>=0;j--)
  {
    display[j+LEVEL_WIDTH+1]=display[j];
  }

  for (byte j=0; j<=LEVEL_WIDTH;j++)
  {
    display[j] = random(1,16);
  }
}


void move_player()
{
  int move_x = !digitalRead(RIGHT) - !digitalRead(LEFT);
  int move_y = !digitalRead(DOWN) - !digitalRead(UP);

  if (move_x == 0 && move_y == 0) return;
  
  player_x += move_x;
  player_y += move_y;
  
  if (player_x < 0) player_x = 0;
  if (player_y < 0) player_y = 0;
  if (player_x > LEVEL_WIDTH)  player_x = LEVEL_WIDTH;
  if (player_y > LEVEL_HEIGHT) player_y = LEVEL_HEIGHT;

}

void display_player()
{
  pixels.setPixelColor( at_pixel(player_x,player_y), pixels.Color(100-health,health,0)); 
}

void check_collision()
{
  int hitzone;

  if (player_y % 2 == 0) hitzone = display[at_pixel(LEVEL_WIDTH-player_x,LEVEL_HEIGHT-player_y)];
  if (player_y % 2 != 0) hitzone = display[at_pixel(player_x,LEVEL_HEIGHT-player_y)];
  
  if (hitzone == 1){
    player_col=random(1,200); 
    health-=4;
    tone(8, NOTE_C4, 50);
    if (health <0) health = 0;
  }
  
}

void loop_game_01()
{

  if (!digitalRead(FIRE)) Serial.println("fire!");
  
  if (millis() > last_time_player + delay_player)
  {
    move_player();
    delay_scroll=player_y*10;
    check_collision();
    last_time_player = millis();
  }

  if (millis() > last_time_scroll + delay_scroll)
  {
    update_level();
    check_collision();
    last_time_scroll = millis();
  } 
  
  show_world();
  display_player();

}
