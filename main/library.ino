/*

  General library
  Contains code that may be used by any game in the package

  www.awsm.de



 */



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


void clear_all()
{
  for(int i=0; i<NUM_PIXELS; i++)
  {
    display[i] = 0;
    pixels.setPixelColor( i, pixels.Color(0,0,0)); 
  } 
}

