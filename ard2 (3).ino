#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int but=12;
int tn=0;
int buz=8;

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("WELCOME");
  pinMode(buz,OUTPUT);
  pinMode(but,INPUT_PULLUP);
  delay(2000);

}
  
void loop(){

 
 
  if (digitalRead(but)==0){
    tn=49;
    lcd.clear();
    lcd.print("Sending:"+ String(tn));

    Serial.println(String(tn) +",0,0");
    delay(16000);
    Serial.println(String(0) +",0,0");
    lcd.clear();
    lcd.print("TRAIN No:");
    }
  

  if(Serial.available())
  {
    int x=Serial.read();
    lcd.setCursor(0,1);
    lcd.print("Signal Received");
    digitalWrite(buz,1);
    delay(3000);
    digitalWrite(buz,0);
    lcd.setCursor(0,1);
    lcd.print("               ");
     lcd.clear();
  lcd.print("WELCOME");
    }
  }
