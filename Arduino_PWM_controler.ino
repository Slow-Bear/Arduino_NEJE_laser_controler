#include <LiquidCrystal_I2C.h>
//https://github.com/johnrickman/LiquidCrystal_I2C

#include <ResponsiveAnalogRead.h>
//https://github.com/dxinteractive/ResponsiveAnalogRead


#include <PWM.h>
//https://code.google.com/archive/p/arduino-pwm-frequency-library/downloads first download location
//https://github.com/terryjmyers/PWM ghithun location


const int FRQ_PIN = 9;
const int ANALOG_PIN = A0;
const int TMP = A1;
const int Butt = 4;
ResponsiveAnalogRead aA0(ANALOG_PIN, true);
ResponsiveAnalogRead TEMP(TMP, true);
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int buff=0;
int buff_tmp=0;

void setup() {
 // pinMode(FRQ_PIN, OUTPUT);
//digitalWrite(FRQ_PIN. LOW);
pinMode(Butt,INPUT_PULLUP);
digitalWrite(Butt, HIGH);
lcd.init();
lcd.backlight();
lcd.setCursor(2,0);
lcd.print("Arduino PWM ");
lcd.setCursor(4,1);
lcd.print("controller");
delay (2000);

//max frequency 33000

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Set frequency ");

unsigned int FREQ_VAL = 0;
while (digitalRead(Butt) == HIGH){
  aA0.update();
  if (buff != aA0.getValue() )
  {
    lcd.setCursor(0,1);
    lcd.print("FRQ: ");
    FREQ_VAL = aA0.getValue()*50;
    lcd.print(FREQ_VAL);
    lcd.print("Hz");
    buff=aA0.getValue();
  }
}
//int32_t frequency = 20000; //frequency (in Hz)

int32_t frequency = ( aA0.getValue()*50); //frequency (in Hz)
//initialize all timers except for 0, to save time keeping functions
InitTimersSafe(); 

//sets the frequency for the specified pin
bool success = SetPinFrequencySafe(FRQ_PIN, frequency);
 if(success) {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH); 
 };   

aA0.update();
aA0.getValue();
lcd.clear();
lcd.print("Duty check");
 lcd.setCursor(0,1);
  lcd.print("DUTY:       ");
  lcd.print(25*aA0.getValue()/255);
  lcd.print("%");
while ( (25*aA0.getValue()/255)  > 10 )
{
  aA0.update();
 if ( buff != aA0.getValue() ){
  lcd.setCursor(0,1);
  lcd.print("DUTY:       ");
  lcd.print(25*aA0.getValue()/255);
  lcd.print("%");
  buff=aA0.getValue();
 }
};
/*
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temp check");
lcd.setCursor(0,1);
lcd.print("Temp: ");
TEMP.update();
lcd.print(TEMP.getValue());
lcd.print("*C");*/
delay (3000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Press button to ");
lcd.setCursor (0,1);
lcd.print("continue");
while (digitalRead(Butt) == HIGH){
  //wait for the buton to be pressed
}
lcd.clear();
 lcd.setCursor(0,1);
  lcd.print("DUTY:       ");
  lcd.print(25*aA0.getValue()/255);
  lcd.print("%");
  lcd.setCursor(0,0);
  lcd.print("FRQ: ");
  lcd.print(aA0.getValue()*50);
  lcd.print(" Hz");
}
//========================================================================================
//========================================================================================
void loop() {
  // put your main code here, to run repeatedly:
  aA0.update();
  TEMP.update();
 pwmWrite(FRQ_PIN, (aA0.getValue()/4));

 if ( buff != aA0.getValue() ){
  lcd.setCursor(0,1);
  lcd.print("DUTY:       ");
  lcd.print(25*aA0.getValue()/255);
  lcd.print("%");
  buff=aA0.getValue();
 }

 /*if ( buff_tmp !=  TEMP.getValue() ){
  lcd.setCursor(0,0);
  lcd.print("TEMP:     ");
  lcd.print(TEMP.getValue());
  lcd.print("*C");
  buff_tmp=TEMP.getValue();
 }*/
}
