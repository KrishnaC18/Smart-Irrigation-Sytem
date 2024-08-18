#include "DHT.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int relay_Pin = 2;
const int DHT11_Sesnor = 9;
const int moisture_sensor = A0;

#define DHTTYPE DHT11
int moisture_sensor_value;
float humudity_value,temprature_value;
DHT dht(DHT11_Sesnor, DHTTYPE);
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
    lcd.print("");
    delay(3000);
  lcd.clear();
  dht.begin();
  delay(2000);
}
void loop(){
  readDTH11_Sesnor();
  moisture_level_detected();
  water_motor_start();
}
void readDTH11_Sesnor()
{
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humudity_value = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temprature_value = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(humudity_value) || isnan(temprature_value)) {
    Serial.println(("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print((" Humidity: "));
  Serial.print(humudity_value);
  Serial.print(("%"));
  lcd.clear();
  lcd.print("Humidity %:");
  lcd.setCursor(0,1);
  lcd.print(humudity_value);
  Serial.print("\n");
  delay(1000);
  Serial.print(("Temperature:"));
  Serial.print(temprature_value);
  Serial.print(("C "));
  lcd.clear();
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print(temprature_value);
  Serial.print("\n");
  delay(1000);
}
void moisture_level_detected()
{
  moisture_sensor_value = analogRead(moisture_sensor);
  Serial.println("Moisture Level : ");
  Serial.println(moisture_sensor_value);
  lcd.clear();
  lcd.print("Soil Moisture:");
  lcd.setCursor(0,1);
  lcd.print(moisture_sensor_value);
  delay(2000);
}
void water_motor_start()
{
  if(moisture_sensor_value > 700 ){
    digitalWrite(relay_Pin, HIGH);
    delay(2000);
  }
  else{
    digitalWrite(relay_Pin, LOW);
    delay(2000);
  }
}
