#include<Adafruit_SSD1306.h>
#include<Adafruit_GFX.h>
#include<SPI.h>
#include<Wire.h>

#define OLED_RESET 4
#define led1 10
#define led2 11
#define buzzer 12
#define gas_sensor_co A0
#define gas_sensor_mq4 A1
#define gas_sensor_mq7 A2
#define gas_sensor_mq1 A3

Adafruit_SSD1306 display(OLED_RESET);



int sensor_value4;
int sensor_value3;
int sensor_value2;
int sensor_value1;

int v1;
int v2;
int v3;
int v4;

void setup()
{
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  pinMode(gas_sensor_co, INPUT);
  pinMode(gas_sensor_mq4, INPUT);
  pinMode(gas_sensor_mq7, INPUT);
  pinMode(gas_sensor_mq1, INPUT);
  delay(500);

}



void loop()
{
  display.clearDisplay();
  display.setCursor(0, 5);

  sensor_value1 = analogRead(gas_sensor_co);
  sensor_value2 = analogRead(gas_sensor_mq4);
  sensor_value3 = analogRead(gas_sensor_mq7);
  sensor_value4 = analogRead(gas_sensor_mq1);

  v1 = map(sensor_value1, 0, 1023, 0, 100);
  v2 = map(sensor_value2, 0, 1023, 0, 100);
  v3 = map(sensor_value3, 0, 1023, 0, 100);
  v4 = map(sensor_value4, 0, 1023, 0, 100);

  /* display.println("The Rate Of CO2:");
    display.print(v1);*/
  display.println("The Rate Of Carbon monoxide:");
  display.print(v2);
  display.println("The Rate Of methane:");
  display.print(v3);
  display.println("The Rate Of Benzene:");
  display.print(v4);

  if (v3 > 10)
  {
    Serial.println("Oxygen level decremented by 2%...Alert!!!");

  }
  else if (v3 > 20)
  {
    Serial.println("Oxygen level decremented by 4%...careful!!!");
    digitalWrite(led1, HIGH);

  }

  else if (v3 > 30)
  {
    Serial.println("ALERT.....");
    digitalWrite(led2, HIGH);

  }

  if (v4 > 10)
  {
    Serial.println("CarbonDioxide Detected As Bad condition...");
  }

  if (v2 > 0.02)
  {
    Serial.println("CarbonMonoxide Detected ... Take Health Care..");
    digitalWrite(buzzer, HIGH);
  }



}
