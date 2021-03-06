
/*

  INCLUDES

*/

#include <Adafruit_NeoPixel.h>
#include "pitches.h" // the notes


/*

  DEFINES

*/


// Values for Arduino Uno

// GROUND blue         
#define FIRE            13  // red
#define RIGHT           12  // white
#define LEFT            11  // orange
#define DOWN            10  // greeen
#define UP              9   // yellow
#define BUZZER          8   // white
#define LED_PLAYER_1    7   // red
#define LED_PLAYER_2    6   // yellow
#define BUTTON_PLAYERS  5   // yellow
#define BUTTON_RESET    4   // yellow
#define PIN             2   // green


// Values for Arduino Due
/*
#define FIRE            13
#define RIGHT           12
#define LEFT            11
#define DOWN            10
#define UP              9
#define BUZZER          8
#define LED_PLAYER_1    7
#define LED_PLAYER_2    6
#define BUTTON_PLAYERS  5
#define BUTTON_RESET    4
#define PIN             2
*/

#define STRIP_HEIGHT    10
#define STRIP_WIDTH     10
#define NUM_PIXELS      121
#define LEVEL_WIDTH     10
#define LEVEL_HEIGHT    10

/* 

  GLOBAL VARIABLES

*/

 
int players = 1;
int display[NUM_PIXELS];
int game_state = 0;
bool button_players_last_state = 0;
bool button_reset_last_state = 0;
bool button_fire_player_1_last_state = 0;
bool button_fire_player_2_last_state = 0;
unsigned long debounce_button_players_time = 0;
unsigned long debounce_button_reset_time = 0;
unsigned long debounce_button_fire_player_1_time = 0;
unsigned long debounce_button_fire_player_2_time = 0;
unsigned long debounce_delay = 10;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  
  Serial.begin(9600);

  randomSeed(analogRead(0));

  /*
  
    SETUP the connections

  */
  pinMode(FIRE, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(LED_PLAYER_1, OUTPUT);
  pinMode(LED_PLAYER_2, OUTPUT);
  pinMode(BUTTON_PLAYERS, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);

  digitalWrite(LED_PLAYER_1, HIGH);
  if (players == 2) digitalWrite(LED_PLAYER_2, HIGH);

  pixels.begin(); // This initializes the NeoPixel library.
  clear_all();

  //play_start_sound();

}


void set_number_of_players()
{ 
    if (players == 1)
    {
      players = 2;
      digitalWrite(LED_PLAYER_1, HIGH);
      digitalWrite(LED_PLAYER_2, HIGH);
    } else {
      players = 1;
      digitalWrite(LED_PLAYER_1, HIGH);
      digitalWrite(LED_PLAYER_2, LOW);
    }
}

void check_players_button()
{
  /*
  
    Checks if the PLAYERS button has been pressed
    and uses debouncing with milliseconds to avoid
    unprecize button press recognition

   */
  bool button_players_state = digitalRead(BUTTON_PLAYERS);

  if (button_players_state == 0)
  {
    debounce_button_players_time = millis();
    button_players_last_state = 0;
  } 

  if (button_players_state == 1 && button_players_last_state == 0)
  {
    if (debounce_button_players_time + debounce_delay < millis())
    {
      set_number_of_players();
      button_players_last_state = 1;
    }
  }
}

void check_reset_button()
{
   /*
  
    Checks if the RESET button has been pressed
    and uses debouncing with milliseconds to avoid
    unprecize button press recognition

   */
  bool button_reset_state = digitalRead(BUTTON_RESET);

  if (button_reset_state == 0)
  {
    debounce_button_reset_time = millis();
    button_reset_last_state = 0;
  } 

  if (button_reset_state == 1 && button_reset_last_state == 0)
  {
    if (debounce_button_reset_time + debounce_delay < millis())
    {
      reset();
      button_reset_last_state = 1;
    }
  } 
}

bool check_fire_player_1()
{
  bool button_fire_player_1_state = !digitalRead(FIRE);
  if (button_fire_player_1_state == 0)
  {
    button_fire_player_1_last_state = 0;
    return false;
  } 

  if (button_fire_player_1_state == 1 && button_fire_player_1_last_state == 0)
  {
    button_fire_player_1_last_state = 1;
    return true;
  }

  return false;
}



void reset()
{
 // tone(8, NOTE_C4, 50);
}

void loop()
{

  if (game_state == 0) loop_intro();
  if (game_state == 10) intro_01();
  if (game_state == 11) loop_01();

  check_players_button();
  check_reset_button();

  pixels.show();

}
