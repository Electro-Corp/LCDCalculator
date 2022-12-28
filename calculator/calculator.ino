#include <Keyboard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/*
 * ARDUINO CALCULATOR WITH LCD DISPLAY
 * by me
 * (real)
*/
// nums
const int firstDigitRead = A0;
const int secondDigitRead = A1;
// operand
const int operandButton = 2;  
int cOperand = 0; // + - * /
// calc
const int calcButton = 3;
int result = 0;
// screen
LiquidCrystal_I2C lcd(0x27,16,2);
// misc
float prevFNum = 0;
float prevSNum = 0;
float firstNum = 0;
float secondNum  = 0;
void setup() {
  // for debug
  pinMode(operandButton, INPUT);
  Serial.begin(9600);
  //lcd.init()
  lcd.begin();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  render();
  
}

void loop() {
  firstNum = analogRead(firstDigitRead);
  secondNum = analogRead(secondDigitRead);
  //Serial.println(firstNum);
  if(digitalRead(operandButton) == HIGH){
    if(cOperand != 3){
      cOperand++;
    }else{
      cOperand = 0;
    }
    //Serial.println(cOperand);
    while(digitalRead(operandButton) != LOW){}
  }

  if(abs(prevFNum - firstNum) > 2 || abs(prevSNum - secondNum) > 2){
    render();
    prevFNum = firstNum;
    prevSNum = secondNum;
  }
}
void render(){
    lcd.clear();
    char* goofyAh = malloc(sizeof(char) * 5);
    itoa(firstNum, goofyAh,10);
    lcd.print(goofyAh);
    switch(cOperand){
      case 0:
        result = firstNum + secondNum;
        lcd.print("+");
        break;
      case 1:
        result = firstNum - secondNum;
        lcd.print("-");
        break;
      case 2:
        result = firstNum * secondNum;
        lcd.print("*");
        break;
      case 3:
        result = firstNum / secondNum;
        lcd.print("/");
        break;
    }
    itoa(secondNum, goofyAh,10);
    lcd.print(goofyAh);
    lcd.print("=");
    itoa(result, goofyAh,10);
    lcd.print(goofyAh);
}
