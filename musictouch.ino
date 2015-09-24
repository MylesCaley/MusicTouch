/*  draw text's APP
    drawChar(INT8U ascii,INT16U poX, INT16U poY,INT16U size, INT16U fgcolor);
    drawString(char *string,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
*/

#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>
#include <SeeedTouchScreen.h> 
#include <Adafruit_NeoPixel.h>



#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // mega
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 54   // can be a digital pin, this is A0
#define XP 57   // can be a digital pin, this is A3 

#elif defined(__AVR_ATmega32U4__) // leonardo
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 18   // can be a digital pin, this is A0
#define XP 21   // can be a digital pin, this is A3 

#else //168, 328, something else
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3 

#endif

//Measured ADC values for (0,0) and (210-1,320-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 240 -1
//TS_MAXY corresponds to ADC value when Y = 320 -1

#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2


#define MUSIC_CONTROL_SWITCH 3
#define LED_CONTROL 10
#define MUSIC_SELECTION_SWITCH_1 0
#define MUSIC_SELECTION_SWITCH_2 1
#define MUSIC_SELECTION_SWITCH_3 A4
#define MUSIC_SELECTION_SWITCH_4 A5
#define SWOUT0 2
#define SWOUT1 8
#define SWOUT2 9
#define SWOUT3 4

//or better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// The 2.8" TFT Touch shield has 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(31, LED_CONTROL, NEO_GRB + NEO_KHZ800);

uint8_t currently_selected;

void setup()
{
    TFT_BL_ON;      // turn on the background light
    Tft.TFTinit();  // init TFT library     
    displayMessage();  
    pinMode(MUSIC_CONTROL_SWITCH, INPUT); 
    pinMode(MUSIC_SELECTION_SWITCH_1, INPUT_PULLUP);
    pinMode(MUSIC_SELECTION_SWITCH_2, INPUT_PULLUP);
    pinMode(MUSIC_SELECTION_SWITCH_3, INPUT_PULLUP);
    pinMode(MUSIC_SELECTION_SWITCH_4, INPUT_PULLUP);

    digitalWrite(SWOUT0, LOW);
    digitalWrite(SWOUT1, LOW);
    digitalWrite(SWOUT2, LOW);
    digitalWrite(SWOUT3, LOW);
    pinMode(SWOUT0, INPUT);
    pinMode(SWOUT1, INPUT);
    pinMode(SWOUT2, INPUT);
    pinMode(SWOUT3, INPUT);
      
    pinMode(LED_CONTROL, OUTPUT);
    digitalWrite(MUSIC_CONTROL_SWITCH, HIGH);
    strip.begin();
    allOn();
    strip.show();
    //Serial.begin(9600);
}

void allOn()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(  0,   0, 30));
  }
  strip.setPixelColor(15, strip.Color(  0,   0, 0));
}

void allOnRed()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(  0,   0, 0));
  }
  strip.show();
  //strip.setPixelColor(15, strip.Color(  0,   0, 0));
}



void displayMessage()
{
  Tft.fillScreen();
  Tft.drawString("PRESS TO",15,70,4,WHITE);
  Tft.drawString("STIFLE",38,130,4,WHITE); 
  Tft.drawString("CREATIVITY",0,190,4,WHITE);
}

void on_1()
{
  allOn();
    strip.setPixelColor(0, strip.Color(  40,   0, 0));
    strip.setPixelColor(1, strip.Color(  40,   0, 0));
    strip.setPixelColor(2, strip.Color(  40,   0, 0));
    strip.setPixelColor(3, strip.Color(  40,   0, 0));
    strip.setPixelColor(4, strip.Color(  40,   0, 0));
    strip.setPixelColor(5, strip.Color(  40,   0, 0));
    strip.setPixelColor(6, strip.Color(  40,   0, 0));
    strip.setPixelColor(7, strip.Color(  40,   0, 0));
    strip.show();
    currently_selected = 1;
}

void on_2()
{
  allOn();
    
    strip.setPixelColor(9, strip.Color(  40,   0, 0));
    strip.setPixelColor(10, strip.Color(  40,   0, 0));
    strip.setPixelColor(11, strip.Color(  40,   0, 0));
    strip.setPixelColor(12, strip.Color(  40,   0, 0));
    strip.setPixelColor(13, strip.Color(  40,   0, 0));
    //strip.setPixelColor(14, strip.Color(  40,   0, 0));
    strip.show();
    currently_selected = 2;
}

void on_3()
{
  allOn();
    strip.setPixelColor(15, strip.Color(  40,   0, 0));
    strip.setPixelColor(16, strip.Color(  40,   0, 0));
    strip.setPixelColor(17, strip.Color(  40,   0, 0));
    strip.setPixelColor(18, strip.Color(  40,   0, 0));
    strip.setPixelColor(19, strip.Color(  40,   0, 0));
    strip.setPixelColor(20, strip.Color(  40,   0, 0));
    strip.setPixelColor(21, strip.Color(  40,   0, 0));
    strip.setPixelColor(22, strip.Color(  40,   0, 0));
    strip.setPixelColor(23, strip.Color(  40,   0, 0));
    strip.show();
    currently_selected = 3;
}

void on_4()
{
  allOn();
    
    strip.setPixelColor(24, strip.Color(  40,   0, 0));
    strip.setPixelColor(25, strip.Color(  40,   0, 0));
    strip.setPixelColor(26, strip.Color(  40,   0, 0));
    strip.setPixelColor(27, strip.Color(  40,   0, 0));
    strip.setPixelColor(28, strip.Color(  40,   0, 0));
    strip.setPixelColor(29, strip.Color(  40,   0, 0));
    strip.setPixelColor(30, strip.Color(  40,   0, 0));
    strip.setPixelColor(31, strip.Color(  40,   0, 0));
    strip.show();
    currently_selected = 4;
}


void loop()
{
  Point p = ts.getPoint();
  digitalWrite(MUSIC_CONTROL_SWITCH, HIGH);
  
  
   if(digitalRead(MUSIC_SELECTION_SWITCH_1)==LOW)
  {
//    Serial.println("PRESSED 1");
    digitalWrite(SWOUT0, LOW);
    pinMode(SWOUT0, OUTPUT);
    digitalWrite(SWOUT0, LOW);
    delay(40);
    pinMode(SWOUT0, INPUT);
    on_1();
  }
  else if(digitalRead(MUSIC_SELECTION_SWITCH_2)==LOW)
  {
  //  Serial.println("PRESSED 2");
      digitalWrite(SWOUT1, LOW);
    pinMode(SWOUT1, OUTPUT);
    digitalWrite(SWOUT1, LOW);
    delay(40);
    pinMode(SWOUT1, INPUT);
    on_2();
  }
  else if(digitalRead(MUSIC_SELECTION_SWITCH_3)==LOW)
  {
  //  Serial.println("PRESSED 3");
      digitalWrite(SWOUT2, LOW);
    pinMode(SWOUT2, OUTPUT);
    digitalWrite(SWOUT2, LOW);
    delay(40);
    pinMode(SWOUT2, INPUT);
    on_3();
  }
  else if(digitalRead(MUSIC_SELECTION_SWITCH_4)==LOW)
  {
  //  Serial.println("PRESSED 4");
        digitalWrite(SWOUT3, LOW);
    pinMode(SWOUT3, OUTPUT);
    digitalWrite(SWOUT3, LOW);
    delay(40);
    pinMode(SWOUT3, INPUT);
    on_4();
  }


  if (p.z > __PRESURE) 
  {
     delay(250);
     Point p2 = ts.getPoint();
     if (p2.z > __PRESURE)
     {
       digitalWrite(MUSIC_CONTROL_SWITCH, LOW);
       pinMode(MUSIC_CONTROL_SWITCH, OUTPUT); 
       digitalWrite(MUSIC_CONTROL_SWITCH, LOW);
       Serial.print("PRESSED SCREEN !");
       allOnRed();
       for (int i=60; i>0; i--)
       {
           Tft.fillScreen();
  //       String num = String(i);
  //       char c_num[2];
  //       num.toCharArray(c_num,2);
  //       Tft.drawString(c_num,0,110,19,RED);
           Tft.drawNumber(i, 0, 110, 19, RED);
           
           
           //delay 1 minute but check button -- NICE CODE!
           for (int i=60; i>0; i--)
           {
             if (digitalRead(MUSIC_SELECTION_SWITCH_1)==LOW && digitalRead(MUSIC_SELECTION_SWITCH_3)==LOW)
             {
                break;
             }
             delay(1000);
           }
           
       }
       //digitalWrite(MUSIC_CONTROL_SWITCH, HIGH);
       pinMode(MUSIC_CONTROL_SWITCH, INPUT); 
       displayMessage();
       switch (currently_selected)
       {
         case 1:
           on_1();
           break;
         case 2:
           on_2();
            break;
          case 3:
            on_3();
             break;
          case 4:
            on_4();
            break;
       }
       
       
    }
  }
  
  delay(100);
}


