/*

  General library
  Contains code that may be used by any game in the package

  www.awsm.de

 */

long rgb2int(byte r, byte g, byte b)
{
  return ((long)r << 16L) | ((long)g << 8L) | (long)b;
}

uint8_t red(uint32_t c) 
{
  return (c >> 16);
}
uint8_t green(uint32_t c) 
{
  return (c >> 8);
}
uint8_t blue(uint32_t c) 
{
  return (c);
}


void draw_line(byte x, byte y, String line, long col, bool orientation = 0 )
{
  String opera = "0";

  for (byte j=0; j<= line.length();j++)
  {
    if (line[j] == opera[0])
    {
      if (orientation == 0)
      {
        draw_point(j+y,x,col);
      } else {
        draw_point(x,j+y,col);
      }
    }
  }
}


void draw_point(byte x, byte y, long col )
{
  pixels.setPixelColor( at_pixel(x,y), pixels.Color(red(col),green(col),blue(col)) );   
}


byte at_pixel(byte x,byte y)
{

  // takes X,Y coordinate and returns the right pixel
  // top left is 0,0

  byte result = (STRIP_HEIGHT+1 - y) * (STRIP_WIDTH+1);
  
  if ( (STRIP_HEIGHT % 2) == 0 )
  {
    if ( (y % 2) != 0) result -= STRIP_WIDTH - x+1;
    if ( (y % 2) == 0) result -= x+1;    
  }

  if ( (STRIP_HEIGHT % 2) != 0 )
  {
    if ( (y % 2) == 0) result -= STRIP_WIDTH - x+1;
    if ( (y % 2) != 0) result -= x+1;    
  }

  return result;
}

void shift_display_down()
{
  // scrolls the display array
  for (int j=NUM_PIXELS-LEVEL_WIDTH; j>=0;j--) display[j+LEVEL_WIDTH+1]=display[j];
}

void clear_pixels()
{
  for(int i=0; i<NUM_PIXELS; i++) pixels.setPixelColor( i, pixels.Color(0,0,0));
}

void clear_all()
{
  for(int i=0; i<NUM_PIXELS; i++)
  {
    display[i] = 0;
    pixels.setPixelColor( i, pixels.Color(0,0,0)); 
  } 
}

