#include <LiquidCrystal.h>
int pot_input;
int motor_signal;
float temp;
const int fsr = 5; //voltage Full scale resulation
int ad_result;    // Analog to Digital conversion Result
float v_out;       
float port_read; //Read value from the port
float rps;       // Round per Second
float rpm;     // Round per Minute
float adc_resulation; // Analog to Digital conversion Resluation
const int rs = A4 , en = 12 , d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  DDRD = B00000000; //Port initialization 
  PORTD = B00000000;
  pinMode(A0, INPUT); //potenimeter input
  pinMode(11, OUTPUT); // Encoder Input
  pinMode(A5,OUTPUT); // Fan 
  digitalWrite(A1, HIGH); //Temperature sensor pin 
  digitalWrite(A3, LOW);  //Temperature sensor pin 
  pinMode(A2, INPUT);    // Temperature sensor Input 
  lcd.begin(16, 2);

}

void loop() {

  Encoder_Drive();
  Encoder_Cooling();
  Encoder_Rpm();
  Display();
}

void Encoder_Drive() {
  pot_input = analogRead(A0);
  motor_signal = map(pot_input, 0, 1023, 70, 255);
  analogWrite(13, motor_signal);
}

void Encoder_Cooling() {
  ad_result = analogRead(A2);
  adc_resulation = fsr / (1023.0);
  v_out = adc_resulation * ad_result;
  temp = v_out * 100.0;
  if(temp>=25){
    digitalWrite(A5,HIGH); // Turning of Fan
  }
}
void Encoder_Rpm() {
  port_read = PIND;
  rps = (port_read * 4.0) / 22.0;
  rpm = rps * 60.0;
}
void Display() {
  lcd.setCursor(0, 0);
  lcd.print("Rps:");
  lcd.print(rps);
  lcd.print("Rpm:");
  lcd.print(rpm);
  lcd.setCursor(0, 1);
  lcd.print("Temperature:");
  lcd.print(temp);
}
