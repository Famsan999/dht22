
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22 
#define BUZZER 8

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

float set_temp = 40.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // ใช้ .begin() หรือ .init() ตามเวอร์ชัน Library ของคุณ
  // ถ้า .begin() ผ่านแล้วก็ใช้ตัวนี้ยาวๆ ได้เลยครับ
  lcd.begin();           
  lcd.backlight();
  
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW); 

  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(1500);
  lcd.clear();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // ตรวจสอบค่า Error
  if (isnan(temperature) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    return; 
  }

  // แสดงผลบรรทัดบน
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.write(223); 
  lcd.print("C    ");

  // แสดงผลบรรทัดล่าง
  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(humidity, 1);
  lcd.print("%      ");

  // เงื่อนไข Buzzer
  if (temperature >= set_temp) {
    digitalWrite(BUZZER, HIGH);
    lcd.setCursor(13, 1); 
    lcd.print("!!!"); 
  } else {
    digitalWrite(BUZZER, LOW);
    lcd.setCursor(13, 1);
    lcd.print("   ");
  }

  delay(2000); 
} // <--- ตรวจสอบว่ามีปีกกาปิดอันนี้อยู่ที่บรรทัดสุดท้ายเสมอ     










