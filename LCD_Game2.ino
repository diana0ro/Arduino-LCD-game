#include <LiquidCrystal.h>
const int rs = 9, en = 8, d4 = 4, d5 = 3, d6 = 2, d7 = 1;
const char Hero='o';
char Obs1[16]="                ";
char Obs2[16]="                ";
char spaces[]={' ', '*'};
int positionCounter;
long int timerStart;
long int currentTime;
int position_y;
int points=0;
long timerLength[]={500,400,300,200,100};
bool continue_move=true;
int speed_to_be;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void add_obstacles(){
  Obs1[15]=(Obs2[14]=='*' || (Obs1[12]=='*' && Obs1[13]=='*')) ? spaces[0]:spaces[random(2)];
  Obs2[15]=(Obs1[14]=='*' || Obs1[15]=='*') ? spaces[0]:(Obs2[12]==' ' && Obs2[13]==' ')?spaces[1]:spaces[random(2)];
 }
void showing_obstacles(){
for(int i=15;i>=0;i--)
{lcd.setCursor(i,0); 
 lcd.print(Obs1[i]);
 lcd.setCursor(i,1); 
 lcd.print(Obs2[i]);
 }
}

void moving_screen(){
  for(int i=1;i<16;i++){
  Obs1[i-1]=Obs1[i];
  Obs2[i-1]=Obs2[i];
  }
}

void show_hero(int y){
 lcd.setCursor(0,y);
 lcd.print(Hero);
 }
 
void moving_hero(int y){
  if(y==1)
   {lcd.setCursor(0,0);
   lcd.print(' ');
   lcd.setCursor(0,1);
   lcd.print(Hero);
   }
   else if(y==0)
    {lcd.setCursor(0,1);
    lcd.print(' ');
    lcd.setCursor(0,0);
    lcd.print(Hero);
    }
} 
   
void game_over(){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Game over");
lcd.setCursor(0,1);
lcd.print("Score:");
lcd.setCursor(7,1);
lcd.print(points/2);
delay(2000);
}  

void start_again(){
points=0;
position_y=1;
for(int i=1;i<16;i++){
 Obs1[i]=' ';
 Obs2[i]=' ';};
 lcd.clear();
 continue_move=true;
}
  
void setup() {
lcd.begin(16,2);
timerStart=millis();
pinMode(13,INPUT_PULLUP);
pinMode(12,INPUT_PULLUP);
position_y=1;
speed_to_be=0;
}

void loop(){
currentTime=millis();
switch(continue_move){
case true :{if((currentTime-timerStart)>timerLength[speed_to_be]){
 timerStart=currentTime;
 points++;
 add_obstacles();
 moving_screen();
 showing_obstacles();
 position_y=(digitalRead(13)==LOW)?1:(digitalRead(12)==LOW)?0:position_y;
 show_hero(position_y);
 continue_move=(position_y==0&&(Obs1[0]=='*'))? false:(position_y==1 && Obs2[0]=='*')?false:true;
 }}break;
case false: {
 game_over(); 
 start_again();
 }break;}
speed_to_be=(points<20)?0:(points<30)?1:(points<45)?2:(points<60)?3:4;
}
 
