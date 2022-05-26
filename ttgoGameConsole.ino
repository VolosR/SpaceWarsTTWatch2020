
#include "buttons2.h"
#include "rocket.h"
#include "brod1.h"
#include "bulet.h"
#include "ebullet.h"
#include "life.h"
#include "rover.h"
#include "earth.h"
#include "ex.h"
#include "ex2.h"
#include "ricon.h"
#include "background.h"
#include "sens.h"
#include "buum.h"
#include "gameover.h"

#include "config.h"

TTGOClass *ttgo;




#define BUZZER_PIN 27
#define BUZZER_CHANNEL 0

#define TFT_GREY 0x5AEB
#define lightblue 0x2D18
#define orange 0xFB60
#define purple 0xFB9B

TFT_eSPI tft = TFT_eSPI();  
int brojac=0;// Invoke custom library
float buletX[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};
float buletY[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};

float EbuletX[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};
float EbuletY[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};

float rocketX[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};
float rocketY[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};
float rocketSpeed=0.22;
int rockets=3;

int counter=0;
int rcounter=0;
int Ecounter=0;
int level=1;
float x=10;
float y=20;

float ey=18;
float ex=170;

float es=0.1;

float bx=-50;
float by=0;

int pom=0; //pressdebounce for fire
int pom2=0; //pressdebounce for rockets
float sped=0.46;
int blinkTime=0;
int eHealth=50;
int mHealth=eHealth;
int lives=4;
int ly[4]={0,0,0,0};
int ri[3]={0,0,0};
int fireTime=100;
int fireCount=0;
float EbulletSpeed=0.3;
int rDamage=8; //rocket damage
int tr=0;

int pom3=0;
bool sound=1; //sound on or off

int fase=0; //fase 0=start screen,//fase 1=playing fase //fase 3=game over

float spaceX[30];
float spaceY[30];


int up=0;
int down=0;
int left=0;
int right=0;
int fire=0;
int rockett=0;

int timeB=0;
int timeR=0;


void setup(void) {

  pinMode(TP_INT, INPUT);
  
ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

         
 ttgo->tft->fillScreen(TFT_BLACK);
 ttgo->tft->setSwapBytes(true);
// ttgo->tft->pushImage(0, 0,  240, 240, background);



  for(int i=0;i<30;i++){
    spaceX[i]=random(5,235);
    spaceY[i]=random(18,124);
  }
  
}

void restart()
  {
counter=0;
rcounter=0;
Ecounter=0;
level=1;
 x=10;
 y=20;
 ey=18;
 ex=170;
 es=0.1;
 bx=-50;
 by=0;

          rockets=3;
          rDamage=8;
          lives=4;
          brojac=0;
          ri[0]=0; ri[1]=0; ri[2]=0;
          ly[0]=0; ly[1]=0; ly[2]=0; ly[3]=0;
          ey=44;
          sped=0.46;
          eHealth=50;
          mHealth=eHealth;
          EbulletSpeed=0.3;
          rocketSpeed=0.22;
          
  
  for(int i=0;i<10;i++)
  {
    buletX[i]=-20;
    EbuletX[i]=-20;
    rocketX[i]=-20;
    
  }

    
   }





   void newLevel()
{
  level++;
  sped=sped+0.05;
  EbulletSpeed=EbulletSpeed+0.04;
  eHealth=50+(level*5);
  mHealth=eHealth;
  es=0.05+(0.035*level);
 
  rockets=3;
  rDamage=8+(level*2);
  rocketSpeed=0.22+(level*0.02);
  ri[0]=0; ri[1]=0; ri[2]=0;
  
  ey=44;
  
  for(int i=0;i<10;i++)
  {
    buletX[i]=-20;
    EbuletX[i]=-20;
    rocketX[i]=-20;
    
    }

   ttgo->tft->fillScreen(TFT_BLACK);
   ttgo->tft->setCursor(0,0,4);
       ttgo->tft->print("Level "+String(level));
        ttgo->tft->setCursor(0,22,2);
        
        ttgo->tft->println("Enemy speed : "+String(es));
        ttgo->tft->println("Enemy health : "+String(eHealth));
        ttgo->tft->println("Enemy bullet speed : "+String(EbulletSpeed));
        ttgo->tft->println("Remaining lives: "+String(lives));
        ttgo->tft->println("My speed : "+String(sped));
       ttgo->tft->println("Rocket damage : "+String(rDamage));
        ttgo->tft->println("Rocket speed : "+String(rocketSpeed));

        ttgo->tft->pushImage(170, 5,  55, 54, earth[level-1]); 
        ttgo->tft->pushImage(170, 61,  72, 72, sens); 
        delay(800);
       while((digitalRead(TP_INT) == HIGH))
{
  
  }
        

      

        ttgo->tft->fillScreen(TFT_BLACK);
    
 
  ttgo->tft->drawLine(0,16,240,16,lightblue);
  ttgo->tft->drawLine(0,124,240,124,lightblue);
  ttgo->tft->drawLine(0,125,240,125,lightblue);


   ttgo->tft->pushImage(49, 131,  48, 48, buttons[0]);
    ttgo->tft->pushImage(49, 185,  48, 48, buttons[1]);  //................................................................................
    ttgo->tft->pushImage(0, 155,  48, 48, buttons[2]); 
     ttgo->tft->pushImage(98, 155,  48, 48, buttons[3]); 
     ttgo->tft->pushImage(190, 131,  48, 48, buttons[4]); 
      ttgo->tft->pushImage(190, 185,  48, 48, buttons[5]); 
    
   

  ttgo->tft->setCursor(200,0,2);
        ttgo->tft->print(brojac);

         ttgo->tft->fillRect(120,3,70,7,TFT_GREEN);
         ttgo->tft->drawRect(119,2,72,9,TFT_GREY);
  
  }



void loop() {

  if(fase==0)
  {
    restart();
    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->setSwapBytes(true);
    ttgo->tft->pushImage(0, 0,  240, 240, background);
    
     while((digitalRead(TP_INT) == HIGH))
{
  
  }
  
    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->setCursor(0,0,4);
        ttgo->tft->print("Level "+String(level));
        ttgo->tft->setCursor(0,22,2);
        
        ttgo->tft->println("Enemy speed : "+String(es));
        ttgo->tft->println("Enemy health : "+String(eHealth));
        ttgo->tft->println("Enemy bullet speed : "+String(EbulletSpeed));
        ttgo->tft->println("Remaining lives: "+String(lives));
        ttgo->tft->println("My speed : "+String(sped));
        ttgo->tft->println("Rocket damage : "+String(rDamage));
        ttgo->tft->println("Rocket speed : "+String(rocketSpeed));

        ttgo->tft->pushImage(170, 5,  55, 54, earth[level-1]); 
        ttgo->tft->pushImage(170, 61,  72, 72, sens); 
        delay(1600);
      while((digitalRead(TP_INT) == HIGH))
{
  
  }
        

        

        ttgo->tft->fillScreen(TFT_BLACK);
 
  ttgo->tft->drawLine(0,16,240,16,lightblue);
  ttgo->tft->drawLine(0,124,240,124,lightblue);
ttgo->tft->drawLine(0,125,240,125,lightblue);

 

    ttgo->tft->pushImage(49, 131,  48, 48, buttons[0]);
    ttgo->tft->pushImage(49, 185,  48, 48, buttons[1]);  //................................................................................
    ttgo->tft->pushImage(0, 155,  48, 48, buttons[2]); 
     ttgo->tft->pushImage(98, 155,  48, 48, buttons[3]); 
     ttgo->tft->pushImage(190, 131,  48, 48, buttons[4]); 
      ttgo->tft->pushImage(190, 185,  48, 48, buttons[5]); 

        ttgo->tft->setCursor(200,0,2);
        ttgo->tft->print(brojac);

         ttgo->tft->fillRect(120,3,70,7,TFT_GREEN);
         ttgo->tft->drawRect(119,2,72,9,TFT_GREY);
        
         
         fase=1;
    }

if(fase==1){
  
  int16_t xt, yt;
    if (ttgo->getTouch(xt, yt)) {
       if(yt>120 && yt<185 && xt>49 && xt<98) //upclicked
       {up=1;
       xt=0;
       yt=0;}

       if(yt>185  && xt>49 && xt<98) //down clicked
       {down=1;
         xt=0;
       yt=0;}

          if(xt>0 && xt<48 && yt>155 && yt<203) // left clicked
       {left=1;
         xt=0;
       yt=0;}

            if(xt>0 && xt<48 && yt>120 && yt<155) // left and  up clicked
       {left=1;
       up=1;
         xt=0;
       yt=0;}

           if(xt>0 && xt<48 && yt>203 && yt<250) // left and  down clicked
       {left=1;
       down=1;
         xt=0;
       yt=0;}

         if(xt>98 && xt<146 && yt>155 && yt<203 ) // right clicked
       {right=1;
         xt=0;
       yt=0;}

         if(xt>98 && xt<146 && yt>120 && yt<155 ) // right  and  up clicked
       {right=1;
       up=1;
         xt=0;
       yt=0;}

           if(xt>98 && xt<146 && yt>204 && yt<250) // right  and  down clicked
       {right=1;
       down=1;
         xt=0;
       yt=0;}

           if(yt>120 && yt<185 && xt>190) //fire
       {
        if(timeB==0){
          timeB=1;
        
        fire=1;
        }
       }

              if(yt>186 && xt>190) // rocket
       {
        if(timeR==0){
          timeR=1;
        
        rockett=1;
        
        }
       }
       
       }


if(timeB>0)
timeB++;

if(timeB>40)
timeB=0;

if(timeR>0)
timeR++;

if(timeR>80)
timeR=0;
  
  //playing fase
if(down==1 and y<84){ //Move down
y=y+sped;
down=0;
}

if(up==1 and y>18){ //Move up
y=y-sped;
up=0;
}

if(right==1 and x<125){ //Move right
  x=x+sped;
  right=0;
}

if(left==1 and  x>0) {//Move right
     x=x-sped;
     left=0;
}


    if(fire==1 ) //fire button A button
    { 
  
  
    buletX[counter]=x+34;
    buletY[counter]=y+15;
    counter=counter+1;
    fire=0; 
   }

   



        if(rockett==1 && rockets>0) //Rocket button B button
    { 
    rockets--;
    rocketX[rcounter]=x+34;
    rocketY[rcounter]=y+14;
    rcounter=rcounter+1;
    ri[rockets]=-100;
     ttgo->tft->fillRect(70+(rockets*14),0,8,14,TFT_BLACK);
    rockett=0;
   }
   
  
  
  for(int i=0;i<30;i++){ //drawStars.....................
  ttgo->tft->drawPixel(spaceX[i],spaceY[i],TFT_BLACK);
  spaceX[i]=spaceX[i]-0.5;
  ttgo->tft->drawPixel(spaceX[i],spaceY[i],TFT_GREY);
  if(spaceX[i]<0){
    ttgo->tft->drawPixel(spaceX[i],spaceY[i],TFT_BLACK);
  
  spaceX[i]=244;
  }}
  
  
 
  ttgo->tft->pushImage(x, y,  49, 40, brod1);
  ttgo->tft->pushImage(ex, ey,  55, 54, earth[level-1]); 
  
  for(int i=0;i<10;i++){ //firing buletts
  if(buletX[i]>0){
  ttgo->tft->pushImage(buletX[i], buletY[i],  8, 8, bulet);
   buletX[i]=buletX[i]+0.6;
  }
  if(buletX[i]>240)
  buletX[i]=-30;
  }

  for(int i=0;i<10;i++){ //firing rockets
  if(rocketX[i]>0){
  ttgo->tft->pushImage(rocketX[i], rocketY[i],  24, 12, rocket);
   rocketX[i]=rocketX[i]+rocketSpeed;
  }
  if(rocketX[i]>240)
  rocketX[i]=-30;
  }
  
  //delay(1);
  

  for(int j=0;j<10;j++) //did my bulet hit enemy
  {
    if(buletX[j]>ex+20 && buletY[j]>ey+2 && buletY[j]<ey+52 )
      {
        ttgo->tft->pushImage(buletX[j], buletY[j],  12, 12, ex2);
         delay(12);
           ttgo->tft->fillRect(buletX[j], buletY[j],12,12,TFT_BLACK);
        buletX[j]=-50;
        brojac=brojac+1;
        ttgo->tft->setCursor(200,0,2);
        ttgo->tft->print(brojac);
        eHealth--; 
        tr=map(eHealth,0,mHealth,0,70);
        ttgo->tft->fillRect(120,3,70,7,TFT_BLACK);
        ttgo->tft->fillRect(120,3,tr,7,TFT_GREEN);
         
         if(eHealth<=0){
          ttgo->tft->pushImage(ex, ey,  55, 55, buum);
          
         delay(700);
         newLevel();}
         
         blinkTime=1;

         
         
        }
    
    }


      for(int j=0;j<10;j++) //did my ROCKET hit enemy
  {
    if(rocketX[j]+18>ex && rocketY[j]>ey+2 && rocketY[j]<ey+52 )
      {
        ttgo->tft->pushImage(rocketX[j], rocketY[j],  24, 24, explosion);
           delay(40);
         ttgo->tft->fillRect(rocketX[j], rocketY[j],24,24,TFT_BLACK);
        //delay(30);
        
        rocketX[j]=-50;
        brojac=brojac+12;
       ttgo->tft->setCursor(200,0,2);
        ttgo->tft->print(brojac);
        eHealth=eHealth-rDamage; 
         tr=map(eHealth,0,mHealth,0,70);
        ttgo->tft->fillRect(120,3,70,7,TFT_BLACK);
        ttgo->tft->fillRect(120,3,tr,7,TFT_GREEN);
         
         if(eHealth<=0){
          ttgo->tft->pushImage(ex, ey,  55, 55, buum);
          
         delay(700);
         newLevel();}
         
         blinkTime=1;

      
        }
    
    }


      for(int j=0;j<10;j++) //Am I hit
  {
    if(EbuletX[j]<x+30 && EbuletX[j]>x+4 && EbuletY[j]>y+4 && EbuletY[j]<y+36 )
      {
        EbuletX[j]=-50;
         ly[lives-1]=-40;
         ttgo->tft->fillRect((lives-1)*14,0,14,14,TFT_BLACK);
         lives--;
         if(lives==0){
           ttgo->tft->pushImage(x, y,  55, 55, buum);
          
         delay(500);
          ttgo->tft->fillScreen(TFT_BLACK);
          fase=2;}

         
        
         blinkTime=1;
        delay(4);
         
        }
    
    }

  ey=ey+es;
  if(ey>70)
  es=es*-1;

  if(ey<18)
  es=es*-1;





  for(int i=0;i<10;i++){   //enemy shoots
  if(EbuletX[i]>-10){
 ttgo->tft->pushImage(EbuletX[i], EbuletY[i],  7, 7, ebullet);
   EbuletX[i]=EbuletX[i]-EbulletSpeed;
  }
  
  }

  for(int i=0;i<4;i++)  //draw lifes
  ttgo->tft->pushImage(i*14, ly[i],  12, 11, life); 
  for(int i=0;i<3;i++)  //draw lifes
  ttgo->tft->pushImage(70+(i*14),ri[i] ,  8, 14, ricon); 

  
  fireCount++;
  if(fireTime==fireCount)
  {
    EbuletX[Ecounter]=ex+5;
    EbuletY[Ecounter]=ey+24;
    fireCount=0;
    fireTime=random(150-(level*10),400-(level*20));
    Ecounter++;
    }
if(counter==9)
  counter=0;

  if(rcounter==3)
  rcounter=0;

if(Ecounter==9)
  Ecounter=0;
}
if(fase==2) //game over fase
{
  
       ttgo->tft->fillScreen(TFT_BLACK);
       ttgo->tft->pushImage(0, 0,  240, 240, gameover);
       ttgo->tft->setCursor(20,150,4);
       ttgo->tft->print("Score : "+String(brojac));
       ttgo->tft->setCursor(20,176,4);
       ttgo->tft->print("Level : "+String(level));
       while((digitalRead(TP_INT) == HIGH))
       {
  
       }
       fase=0;
  }
}



  
