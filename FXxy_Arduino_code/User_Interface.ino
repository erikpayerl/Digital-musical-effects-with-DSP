//////////////////////////////////////////////////////////////////////////////
// DIGITALA MUSIKEFFEKTER MED DSP
// * File name: User_interface.ino
// *                                                                          
// * Description:  Interface code for presenting effects and sending parameters to DSP.
// * 
// * 
// * Erik Payerl, Erik Sandgren, Gustaf Johansson  
// * Rickard Dahl, Omid Fassihi - 2014-05-24
// * 
//////////////////////////////////////////////////////////////////////////////

#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// Defines value of colors RGB values
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF


// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
void (*screens[9])();
char* rectText[4];
bool axis;
int rectNr;
float textSize;
char* axisText[2];
int startmode=0;
//void drawUI(String[4] rectText, bool axis, int rectNr, float textSize, String[2] axisText);

//For icons found at the home screen
int ikonhSize=96;
int ikonvSize=74;

int ikonhOff=6;
int ikonvOff=5;

int ikonhAv=10;
int ikonvAv=82;


//Icons for effect menus
int rectWidth=50;
int rectHeight=50;

//Screen size
int screenWidth=320;
int screenHeight=240;

//Variables used for identification of the previous effect and chosen effect 
int lastScreen=0;
int chosenScreen;

int pointHeight=19;
int pointWidth=20;

int distH = 125;
int distW = 150;
int distPrad = 8;

int x=0;

int gridHeight1=19;
int gridWidth1=20;
int axisHeight = screenHeight - 10;
int axisWidth = 10;

// Equalizer band heights and bandwiths and colors.
int eqBH[8] = { screenHeight/2+30, screenHeight/2+30, screenHeight/2+30, screenHeight/2+30, screenHeight/2+30, screenHeight/2+30, screenHeight/2+30, screenHeight/2+30 };
int eqBW = (screenWidth - 21 - axisWidth)/8;
int eqColors[8] = {GREEN, WHITE, RED, WHITE, GREEN, WHITE, RED, WHITE };

//int lastEff=0;
int h=screenHeight-gridHeight1;
int w=0;
int hline = rectHeight + (axisHeight-rectHeight)/2;
int wline = (screenWidth-axisWidth)/2;
int hQ = screenWidth/2;


//Variables for sending parameters
unsigned long timeN = 0;
unsigned long timeN2 = 0;
byte h2Q = 128;
byte fc = 128;
byte opmode = 0;
byte CHOSEN_EFFECT;
byte START_OF_MESSAGE = 255;
int bandWidth = 40;

int kvotYint=0;
int kvotXint=0;
int xscreen=0;
int Kold;
char ftype;

void setup(void) {
  
  Serial.begin(9600); //Serial communication through UART is set to 9600 baud.
  
  //screens vector is initialized with pointers to screen drawing functions
  screens[0] = startscreen;
  screens[1] = filtUI;
  screens[2] = eqUI;
  screens[3] = distUI;
  screens[4] = ekoUI;
  screens[5] = reveUI;
  screens[6] = tremUI;
  screens[7] = vibrUI;
  screens[8] = flanUI;

  
  //Wait for touchscreen to start
  tft.begin(); 
  if (!ts.begin()) {
    while (1);
  }
  
  //Serial.println("Touchscreen started");
tft.setRotation(1);  // Rotates the screen, which makes (x,y)=(0,0) appear in left upper corner by the USB-plug. Worth noting is that the x-axis represents height while the y-axis represents width
  startscreen();
}


void loop()
{
 TS_Point p; 
 
 //Wait for input
 if (ts.bufferEmpty()) {
    return;
  }
  // Retrieve a point  
   p = ts.getPoint();
   // Scale from ~0->4000 to tft.width using the calibration #'s defined above as TS_MINX and TS_MAXX and TS_MINY and TS_MAXY
      p.x = map(p.x, TS_MINX, TS_MAXX, screenHeight, 0);
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, screenWidth);    
    
	
	// These conditions check for inputs at the home screen
  if(lastScreen==0)
  {
    if (p.y>6 && p.y<102 && p.x>5 && p.x<79)
    {
      chosenScreen=1;
      ftype = 'L'; 
    }
    else if(p.y>112 && p.y<208 && p.x>5 && p.x<79)
    {
      chosenScreen=2;
    }
    else if(p.y>218 && p.y<314 && p.x>5 && p.x<79)
    {
      chosenScreen=3;
    }
    else if(p.y>6 && p.y<102 && p.x>161 && p.x<235)
    {
      chosenScreen=4;
  
    }
    else if(p.y>112 && p.y<208 && p.x>161 && p.x<235)
    {
      chosenScreen=5;
    }
    else if(p.y>218 && p.y<314 && p.x>161 && p.x<235)
    {
      chosenScreen=6;
    }
    else if(p.y>6 && p.y<102 && p.x>83 && p.x<157)
    {
      chosenScreen=7;
    }
    else if(p.y>218 && p.y<314 && p.x>83 && p.x<157)
    {
      chosenScreen=8;
    }
    else
    {
      chosenScreen=0;
    }
    
   // screens vector is accessed to fetch function pointer which is dereferenced to draw the chosenscreen
    if(ts.touched())
     (*screens[chosenScreen])();
  }
// These conditions check for input within respective effect  
  else if (p.x > 0 && p.x < rectHeight && ts.touched()) 
  {
      if(p.y > 0*(screenWidth-rectWidth)/4 && p.y <0*(screenWidth-rectWidth)/4+rectWidth)
      {
        if(lastScreen == 1) {
        ftype = 'L'; 
        filtUI();
        }
      }
      else if(p.y > 1*(screenWidth-rectWidth)/4 && p.y <1*(screenWidth-rectWidth)/4+rectWidth )//&& lastScreen !=2
      {
          if(lastScreen == 1){
            ftype = 'H';
            filtUI();
          }
      }
      else if(p.y > 2*(screenWidth-rectWidth)/4 && p.y <2*(screenWidth-rectWidth)/4+rectWidth)
      {
        if(lastScreen == 1) {
          ftype = 'B';
          filtUI();
        }
      }
      else if(p.y > 3*(screenWidth-rectWidth)/4 && p.y <3*(screenWidth-rectWidth)/4+rectWidth)
      {
    }
      else if(p.y > 4*(screenWidth-rectWidth)/4 && p.y <4*(screenWidth-rectWidth)/4+rectWidth)
      {
        chosenScreen = 0;
        if (ts.touched())
          (*screens[chosenScreen])();
        
      }
    }
	//These conditions initialize parameter send depending on effect and input coordinates
    else if(p.x > hline-30 && p.x < screenHeight-gridHeight1 && p.y > axisWidth+bandWidth && p.y < screenWidth-20-bandWidth && lastScreen==1)
    {
       drawFilterLineAndSend(p, ftype);
    }
    else if(p.x > rectHeight && p.x < hline+20 && p.y > axisWidth+10 && p.y < screenWidth-20 && lastScreen==1 && ts.touched())
    {
       qslide(p);
    }
    else if(p.x > rectHeight+distPrad+18 && p.x < screenHeight-9 && p.y > axisWidth+distPrad && p.y < screenWidth-28 && lastScreen==2 && ts.touched())
    {
       CHOSEN_EFFECT = 5;
       drawAndSendBands(p);
    }
    else if(p.x > rectHeight+distPrad+18 && p.x < screenHeight-gridHeight1-distPrad && p.y > axisWidth+distPrad && p.y < screenWidth-20-distPrad && ts.touched())
    {
        if(lastScreen==3)
        {
          CHOSEN_EFFECT = 1;
          drawAndSendP(p);
         }
        else if(lastScreen==4)
        {
          if(ftype == 'R')
           CHOSEN_EFFECT = 4;
          else if(ftype == 'E')
            CHOSEN_EFFECT = 3;
          drawAndSendP(p);
        }
        else if(lastScreen==5)
        {
           CHOSEN_EFFECT = 2;
           drawAndSendP(p);
        }
        else if(lastScreen==6)
        {
          CHOSEN_EFFECT=6;
          drawAndSendP(p);
        }
        else if(lastScreen==7)
        {
          CHOSEN_EFFECT=7;
          drawAndSendP(p);
        }  
    }
    //if (chosenScreen != lastScreen && ts.touched() && (p.y>6 && p.y<102 || p.y>112 && p.y<208 || p.y>218 && p.y<314) && (p.x > 5 && p.x < 90) || (p.x > 150 && p.x < 235))    
}
  
void startscreen()
{
	// This condition is needed for the homescreen to clear the old interface when navigating between effects
  if (lastScreen !=0 || startmode==0)
  {
    tft.fillScreen(BLACK);
    startmode=1;
  }
  lastScreen=0; // Ifall vi skall använda lastScreen=0 vid "escape"
    
    // Draw the respective rectangels which tell the user where to press to access an effect
  for(int j=0;j<2;j++)
  {    
    for(int i=0;i<3;i++)
    {

        tft.drawRect(ikonhOff+i*(ikonhSize+ikonhAv),ikonvOff+j*(ikonvAv+ikonvSize),ikonhSize,ikonvSize,GREEN);
      }
  }
  
  tft.drawRect(ikonhOff,83,ikonhSize,ikonvSize,GREEN); //Vibrato
  tft.drawRect(ikonhOff+2*(ikonhSize+ikonhAv),83,ikonhSize,ikonvSize,GREEN); //Flanger
  
  //Filter
  tft.setCursor(20,35);
  tft.setTextSize(2); tft.setTextColor(RED);
  tft.print("Filter");
  //EQ
  tft.setCursor(148,35);
  tft.print("EQ");
  //Fuzz
  tft.setCursor(243,35);
  tft.print("Fuzz");
  //Vibrato
  tft.setCursor(14,113);
  tft.print("Vibrato");
  //Flanger
  tft.setCursor(226,113);
  tft.print("Flanger");
  //Eko
  tft.setCursor(37,191);
  tft.print("Eko");
  //Reverb
  tft.setCursor(125,191);
  tft.print("Reverb");
  //Tremolo
  tft.setCursor(225,191);
  tft.print("Tremolo");  
  
  //Product title
  tft.setCursor((screenWidth/3)+7,(screenHeight/2.5)+5);
  tft.setTextSize(4); tft.setTextColor(RED);
  tft.print("FXxy");
  
  //Send "unprocessed" sound
  sendParams(4, 0, 0, 1, 25, 0);  
}

/*
	Shell function for drawing user interfaces.
	Parameters:
	Vector with text strings to be drawn
	Number of rectangles to be drawn
	Whether coordinate axis should be drawn
	Text size
	Vector with text strings to draw at end of axis
*/
void drawUI(char* rectText[], int rectNr, bool axis, float textSize, char* axisText[]) {
    tft.fillScreen(BLACK);
    tft.setCursor(rectWidth/3+4*(screenWidth-rectWidth)/4, rectHeight/2.5);.
    tft.setTextColor(WHITE);  tft.setTextSize(1.5);
    tft.print("ESC");
    
    for(int i = 0; i < rectNr; i++) {
      tft.drawRect(i*(screenWidth-rectWidth)/4,0,rectWidth,rectHeight,WHITE);
      tft.fillRect(rectWidth/3+i*(screenWidth-rectWidth)/4, rectHeight/2.5,20,20,BLACK);
      tft.setCursor(rectWidth/3+i*(screenWidth-rectWidth)/4, rectHeight/2.5); 
      tft.setTextColor(RED);  tft.setTextSize(textSize);
      tft.print(rectText[i]);
    }
    tft.drawRect(4*(screenWidth-rectWidth)/4,0,rectWidth,rectHeight,GREEN);
    
    for(int i2 = rectNr; i2 < 4; i2++) 
      tft.fillRect(i2*(screenWidth-rectWidth)/4,0,rectWidth,rectHeight,BLACK); 
    
    if(axis) {
            // DRAW X-AXIS
        tft.drawLine(gridWidth1/2,axisHeight,gridWidth1/2,rectHeight+18,BLUE);
        tft.fillTriangle(gridWidth1/2,rectHeight+3,
        gridWidth1/4,rectHeight+18,
        (3*gridWidth1)/4,rectHeight+18,BLUE);
        tft.setCursor((3*gridWidth1)/4, rectHeight+3);
        tft.setTextColor(CYAN);  tft.setTextSize(2);
        tft.print(axisText[0]); 
        // DRAW Y-AXIS
        tft.drawLine(gridWidth1/2,axisHeight,screenWidth-(gridWidth1/2),axisHeight,BLUE);
        tft.fillTriangle(screenWidth-5,screenHeight-10,
        screenWidth-20,screenHeight-5,
        screenWidth-20,screenHeight-15,BLUE);
        tft.setCursor(screenWidth-20, screenHeight-30);
        tft.setTextColor(CYAN);  tft.setTextSize(2);
        tft.print(axisText[1]); 
    }
 
  
}
/*
	Function used to send parameters via UART to DSP when changing effects or parameters.
*/
void sendParams(byte CHOSEN_EFFECT, byte p1, byte p2, byte opmode, unsigned long messageDelay, unsigned long wordDelay ) {
    if(timeN == 0 || millis() > timeN + messageDelay) {
   Serial.write(START_OF_MESSAGE);
   timeN2 = millis();
    while(millis() < timeN2 + wordDelay);
   Serial.write(CHOSEN_EFFECT);
   timeN2 = millis();
    while(millis() < timeN2 + wordDelay);
   Serial.write(p1);
   timeN2 = millis();
    while(millis() < timeN2 + wordDelay);
   Serial.write(p2);
   timeN2 = millis();
    while(millis() < timeN2 + wordDelay);
   Serial.write(opmode);
   
   timeN = millis();
   }    
}
/*
	Function that draws filter UI, utilizes shell function drawUI() above.
*/
void filtUI() {

  int K;
  
  if (lastScreen!=1)
  {
    lastScreen=1;
    CHOSEN_EFFECT = 0;
    char* rectText[] = {"LP","HP","BP", ""};
    char* axisText[] = {"","f"};
    drawUI(rectText, 3, true, 2, axisText); 
    
    // DRAW Q-SLIDE
    tft.drawLine(axisWidth+10, rectHeight+50, screenWidth-20, rectHeight+50, RED);
    tft.fillTriangle(screenWidth-5, rectHeight+50, screenWidth-20, rectHeight+55, screenWidth-20, rectHeight+45, RED);
    tft.fillRect(hQ, rectHeight+40, 3, 20, MAGENTA);
    tft.setCursor(screenWidth-15, rectHeight+30);
    tft.setTextColor(CYAN);  tft.setTextSize(2);
    tft.print("Q"); 

   }
    // Draw ideal filter response
    tft.drawLine(wline, rectHeight + (axisHeight-rectHeight)/2, wline, axisHeight-3, WHITE); // VERTIKAL
    if(ftype == 'L') {
     // LOWPASS
     K = 0;
     
     sendParams(CHOSEN_EFFECT, 128, 128, K, 10, 0);
     
    tft.drawLine(wline-bandWidth, hline, wline+bandWidth, hline, BLACK);
    tft.drawLine(wline-bandWidth, hline, wline-bandWidth, axisHeight-3, BLACK);
    tft.drawLine(wline+bandWidth, hline, wline+bandWidth, axisHeight-3, BLACK);
    tft.drawLine(wline, rectHeight + (axisHeight-rectHeight)/2, screenWidth, rectHeight + (axisHeight-rectHeight)/2, BLACK); 
    tft.drawLine(gridWidth1/2+1, rectHeight + (axisHeight-rectHeight)/2, wline, rectHeight + (axisHeight-rectHeight)/2, WHITE); // HORISONTAL
    }
    else if(ftype == 'H') {
      // HIGHPASS
    K = 1;
    sendParams(CHOSEN_EFFECT, fc, h2Q, K, 10, 0);
    tft.drawLine(wline-bandWidth, hline, wline+bandWidth, hline, BLACK);
    tft.drawLine(wline-bandWidth, hline, wline-bandWidth, axisHeight-3, BLACK);
    tft.drawLine(wline+bandWidth, hline, wline+bandWidth, axisHeight-3, BLACK);
    tft.drawLine(gridWidth1/2+1, rectHeight + (axisHeight-rectHeight)/2, wline, rectHeight + (axisHeight-rectHeight)/2, BLACK);
    tft.drawLine(wline, rectHeight + (axisHeight-rectHeight)/2, screenWidth, rectHeight + (axisHeight-rectHeight)/2, WHITE); // HORISONTAL
    }
    else if(ftype == 'B') {
      // BANDPASS
     K = 2;
     sendParams(CHOSEN_EFFECT, fc, h2Q, K, 10, 0);
     tft.drawLine(gridWidth1/2+1, rectHeight + (axisHeight-rectHeight)/2, screenWidth, rectHeight + (axisHeight-rectHeight)/2, BLACK);
     tft.drawLine(wline, rectHeight + (axisHeight-rectHeight)/2, wline, axisHeight, BLACK);
     tft.drawLine(wline+bandWidth, hline, wline-bandWidth, hline, WHITE);
     tft.drawLine(wline-bandWidth, hline, wline-bandWidth, axisHeight-3, WHITE);
     tft.drawLine(wline+bandWidth, hline, wline+bandWidth, axisHeight-3, WHITE); 
    }
    
    tft.drawRect((0)*(screenWidth-rectWidth)/4,0,rectWidth,rectHeight,GREEN);
    tft.drawRect((1)*(screenWidth-rectWidth)/4,0,rectWidth,rectHeight,GREEN);
    tft.drawRect((2)*(screenWidth-rectWidth)/4,0,rectWidth,rectHeight,GREEN);
    tft.drawRect((K)*(screenWidth-rectWidth)/4,0,rectWidth,rectHeight,WHITE);
    
    xscreen=1; 
    loop();
}

/*
	Function that draws the equalizer interface, utilizes shell function drawUI().
*/
void eqUI ()
{
   if(lastScreen==0)
  {
    char* rectText[] = {"EQ","","", ""};
    char* axisText[] = {"G","f"};
    CHOSEN_EFFECT = 5; // EFFECT INDEX
    sendParams(CHOSEN_EFFECT, 0, 128, opmode, 50, 0);
    drawUI(rectText, 1, true, 2, axisText ); 
  }
  lastScreen = 2;
  
  //Draws "bands"
  for(int i = 0; i < 8; i++)
    tft.fillRect(i*eqBW+axisWidth+1, eqBH[i], eqBW, screenHeight-axisWidth-eqBH[i], eqColors[i]);
    

}

/*
	Function that draws the equalizer interface, utilizes shell function drawUI().
*/

void distUI()
{
  if(lastScreen==0)
  {
    char* rectText[] = {"FUZZ","","", ""};
    char* axisText[] = {"G","D"};
    CHOSEN_EFFECT = 1;
    sendParams(CHOSEN_EFFECT, 128, 128, opmode, 4, 0);
    
    drawUI(rectText, 1, true, 1.5, axisText); 
    
  }
    lastScreen=3;
     //tft.drawRect(i*(screenWidth-rectWidth)/4,0,rectWidth,rectHeight,GREEN); 
}

/*
	Functions that draws standard interface for most effects, utilizes shell function drawUI().
*/

void reveUI()
{
    if(lastScreen==0)
  {
    char* rectText[] = {"Rev","","", ""};
    char* axisText[] = {"d","f"};
    CHOSEN_EFFECT = 4;
    sendParams(CHOSEN_EFFECT, 128, 128, opmode, 4, 0);
    drawUI( rectText, 1, true, 1.5, axisText ); 
  }
  lastScreen = 4;
}

void ekoUI()
{
    if(lastScreen==0)
  {
    char* rectText[] = {"Eko","","", ""};
    char* axisText[] = {"d","f"};
    CHOSEN_EFFECT = 3;
    sendParams(CHOSEN_EFFECT, 128, 128, opmode, 4, 0);
    drawUI( rectText, 1, true, 1.5, axisText ); 
  }
  
  lastScreen = 4;
}

void tremUI()
{
  int K;
    if(lastScreen==0)
  {
    char* rectText[] = {"Tr","","", ""};
    char* axisText[] = {"d","f"};
    CHOSEN_EFFECT=2;
    sendParams(CHOSEN_EFFECT, 128, 128, opmode, 4, 0);
    drawUI( rectText, 1, true, 1.5, axisText ); 
  }
  lastScreen = 5;
}

void vibrUI()
{
  if (lastScreen==0)
  {
    char* rectText[] = {"Vib","","", ""};
    char* axisText[] = {"d","f"};
    CHOSEN_EFFECT=6;
    sendParams(CHOSEN_EFFECT,128,128,opmode,4,0);
    drawUI( rectText, 1, true, 1.5, axisText );
   }
  lastScreen = 6;
}

void flanUI()
{
  if (lastScreen==0)
  {
    char* rectText[] = {"Fla","","", ""};
    char* axisText[] = {"d","f"};
    CHOSEN_EFFECT=7;
    sendParams(CHOSEN_EFFECT,128,128,opmode,4,0);
    drawUI( rectText, 1, true, 1.5, axisText );
   }
  lastScreen = 7;
}
/*

This function can be used when a grid is wanted.

void grid_1_complete()
{
    if(xscreen==0)
    {
      tft.fillRect(102,95,120,43,BLACK);
      tft.fillRect(screenWidth/15,screenHeight/1.5,270,40,BLACK);
      xscreen++;
    }
    for(int j=0;j<16;j++)
    {
      for(int i=0;i<10;i++)
      {
        tft.drawRect(j*gridWidth1,rectHeight+i*gridHeight1,gridWidth1,gridHeight1,WHITE);
      }
    }
}
*/
/*
	Function called when user changes filter response, the presented response is changed and this information is sent to the DSP.
*/
void drawFilterLineAndSend(TS_Point p, char ftype) {
   CHOSEN_EFFECT = 0;
   tft.drawLine(wline, hline, wline, axisHeight-3, BLACK);
   if(ftype == 'L') {
       opmode = 0;
       if(p.y > wline) {
         tft.drawLine(wline, hline, p.y, hline, WHITE); 
         tft.drawLine(p.y, hline, p.y, axisHeight-3, WHITE);
       }
       else {
         tft.drawLine(p.y, hline, wline, hline, BLACK);
         tft.drawLine(p.y, hline, p.y, axisHeight-3, WHITE);
       }
   }
   else if(ftype == 'H') {
     opmode = 1;
     if(p.y > wline) {
       tft.drawLine(wline, hline, p.y, hline, BLACK); 
       tft.drawLine(p.y, hline, p.y, axisHeight-3, WHITE);
     }
     else {
       tft.drawLine(p.y, hline, wline, hline, WHITE);
       tft.drawLine(p.y, hline, p.y, axisHeight-3, WHITE);
     }
   }
    else if(ftype == 'B') {
      opmode = 2;
      tft.drawLine(wline-bandWidth, hline, wline+bandWidth, hline, BLACK);
      tft.drawLine(wline-bandWidth, hline, wline-bandWidth, axisHeight-3, BLACK);
      tft.drawLine(wline+bandWidth, hline, wline+bandWidth, axisHeight-3, BLACK);
      tft.drawLine(p.y-bandWidth, hline, p.y+bandWidth, hline, WHITE);
      tft.drawLine(p.y-bandWidth, hline, p.y-bandWidth, axisHeight-3, WHITE);
      tft.drawLine(p.y+bandWidth, hline, p.y+bandWidth, axisHeight-3, WHITE);
    }
   
   wline = p.y;
   fc = map(p.y, axisWidth+2, screenWidth-2, 0, 254);
   
   if(timeN == 0 || millis() > timeN + 5) {
   Serial.write(START_OF_MESSAGE);
   Serial.write(CHOSEN_EFFECT);
   Serial.write(fc);
   Serial.write(h2Q);
   Serial.write(opmode);
   
   timeN = millis();
   }
}
/*
	Function that is called when user changes value of Q-slide. The new value is drawn on the slide and sent to the DSP.
*/

void qslide(TS_Point p) {
   CHOSEN_EFFECT = 0;
   tft.fillRect(hQ, rectHeight+40, 3, 20, BLACK);
   tft.drawLine(hQ, rectHeight+50, hQ+3, rectHeight+50, RED);
   tft.fillRect(p.y, rectHeight+40, 3, 20, MAGENTA);
   hQ = p.y;
   h2Q = map(p.y, axisWidth+10, screenWidth-20, 0, 254);
   
   
   if(timeN == 0 || millis() > timeN + 10) {
   Serial.write(START_OF_MESSAGE);
   Serial.write(CHOSEN_EFFECT);
   Serial.write(fc);
   Serial.write(h2Q);
   Serial.write(opmode);
   
   timeN = millis();
   }
}

/*
	Function that is called when user changes position of marker in the coordinate system that most effects use for interfacing. The new marker is drawn, and the new parameters sent to the DSP.
*/

void drawAndSendP(TS_Point p) {
  byte p1, p2;
  opmode = 0;
  tft.fillCircle(distW, distH, distPrad,BLACK); 
  tft.fillCircle(p.y, p.x, distPrad, YELLOW);
  distW = p.y;
  distH = p.x;
  p1 = map(p.x, rectHeight+distPrad+18, screenHeight-gridHeight1-distPrad, 254, 0);
  p2 = map(p.y, axisWidth+distPrad, screenWidth-20-distPrad, 0, 254);

if(timeN == 0 || millis() > timeN + 40) {  
  Serial.write(START_OF_MESSAGE);
  Serial.write(CHOSEN_EFFECT);
  Serial.write(p2);
  Serial.write(p1);
  Serial.write(opmode);
  
  timeN = millis();
}
}

/*
	Function called when user changes height of the bands in the equalizers interface. Draws the new height of the band and sends this to the DSP.
*/

void drawAndSendBands(TS_Point p) {
  p.y = map(p.y,0,320,axisWidth+1,screenWidth-28);
  int i = p.y/(eqBW);
  int bandSend;
  
  if(p.x < eqBH[i])
        tft.fillRect(i*eqBW+axisWidth+1, p.x, eqBW, eqBH[i]-p.x, eqColors[i]);
      else
        tft.fillRect(i*eqBW+axisWidth+1, eqBH[i], eqBW, p.x-eqBH[i], BLACK);
   eqBH[i] = p.x;
   
   bandSend = map(p.x, rectHeight+distPrad+18, screenHeight-gridHeight1-distPrad, 254, 0);
if(timeN == 0 || millis() > timeN + 50) {     
  Serial.write(START_OF_MESSAGE);
  Serial.write(CHOSEN_EFFECT);
  Serial.write(i);
  Serial.write(bandSend);  
  Serial.write(23);

  timeN = millis();  
}
}

/*
Function used for changing the marker in a grid system. Can be used if wanted.
void grid_1(TS_Point p)
{
      tft.fillRect((kvotYint-1)*gridWidth1,rectHeight+kvotXint*gridHeight1,pointWidth,pointHeight,BLACK);
      tft.drawRect((kvotYint-1)*gridWidth1,rectHeight+kvotXint*gridHeight1,pointWidth,pointHeight,WHITE);
   //Serial.println(h);
   kvotXint=((h-rectHeight)/gridHeight1)+1;
   //Serial.println(kvotXint);
   kvotYint=(w/gridWidth1)+1;
   //Serial.println(w);
   //Serial.println(kvotYint);
   tft.fillRect((kvotYint-1)*gridWidth1,rectHeight+kvotXint*gridHeight1,pointWidth,pointHeight,GREEN);
   w=p.y;
   h=p.x;
}

*/

