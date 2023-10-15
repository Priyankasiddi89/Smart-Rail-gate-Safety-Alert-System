#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'A','1','2','3'},
  {'B','4','5','6'},
  {'C','7','8','9'},
  {'D','*','0','#'}
};
byte rowPins[ROWS] = {A0, 13,12,11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A1, 10, 9, 8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
String tn="";
int buz=A5;

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("WELCOME");
  pinMode(buz,OUTPUT);
  delay(2000);
   lcd.clear();
  lcd.print("TRAIN No:");
}
  
void loop(){

 
  
  char customKey = customKeypad.getKey();
  
  if (customKey){
    lcd.print(customKey);
    tn +=char(customKey);
    if(customKey=='#')
    {
   // Serial.println(customKey);
    lcd.clear();
    lcd.print("Sending:"+ tn);
    delay(3000);
     lcd.clear();
  lcd.print("TRAIN No:");
  Serial.println(tn +",0,0");
  tn="";
    }
  }

  if(Serial.available())
  {
    int x=Serial.read();
    if(x=='1')
    {
    lcd.setCursor(0,1);
    lcd.print("Signal Received");
    digitalWrite(buz,1);
    delay(3000);
    digitalWrite(buz,0);
    lcd.setCursor(0,1);
    lcd.print("               ");
     lcd.clear();
  lcd.print("TRAIN No:");
    }
  }
}
