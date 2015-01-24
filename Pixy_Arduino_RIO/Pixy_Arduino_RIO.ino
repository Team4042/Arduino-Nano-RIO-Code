#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;
int digitalPinOut = 3;
//Length of 5
int serialArrayRIO[5];
int signature, x, y, area;

void setup()
{

  Serial.begin(9600);
  Serial.print("Starting...\n");

  signature = A0;
  x = A1;
  y = A2;
  area = A3;
  
  pinMode(signature, OUTPUT);
  pinMode(x, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(area, OUTPUT);
  
  pixy.init();
}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  
  blocks = pixy.getBlocks();
  
  if (blocks)
  {
    i++;
    if (i%50==0)
    {
      for (j=0; j<blocks; j++)
      {
        serialArrayRIO[0] = pixy.blocks[j].signature;
        serialArrayRIO[1] = pixy.blocks[j].x;
        serialArrayRIO[2] = pixy.blocks[j].y;
        serialArrayRIO[3] = (pixy.blocks[j].width * pixy.blocks[j].height)/4;
        
        analogWrite(signature, serialArrayRIO[0]);
        analogWrite(x, serialArrayRIO[1]);
        analogWrite(y, serialArrayRIO[2]);
        analogWrite(area, serialArrayRIO[3]);
      }
    }
  }  
}

