#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  //設定LCD位置0x27,設定LCD大小為16*2
#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


/*
 * HC-SR04 example sketch
 *
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 *
 * by Isaac100
 */

const int trigPin = 9;
const int echoPin = 10;

float duration, distance;




void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
 
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(7,OUTPUT);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);
   
}

void loop() {
  /*lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  delay(1000);*/
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  
  //delay(3000);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  
  if (distance>2 && distance<2000) {
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance<40){
      lcd.home();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Too Close!");
      lcd.setCursor(0,1);
      lcd.print(distance);
      lcd.setCursor(5,1);
      lcd.print("cm");
      Serial.println("Too Close!");
      digitalWrite(7,HIGH);
      delay(500);
      digitalWrite(7,LOW);
      delay(500);
    } else {
      lcd.home();
      lcd.clear();
      lcd.setCursor(8, 0);
      lcd.print("OK");
      lcd.setCursor(0, 0);
      lcd.print(distance);
      lcd.setCursor(5,0);
      lcd.print("cm");
      // Reading temperature or humidity takes about 250 milliseconds!
      // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
      float h = dht.readHumidity();
      // Read temperature as Celsius (the default)
      float t = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      float f = dht.readTemperature(true);

      // Check if any reads failed and exit early (to try again).
      if (isnan(h) || isnan(t) || isnan(f)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }

      // Compute heat index in Fahrenheit (the default)
      float hif = dht.computeHeatIndex(f, h);
      // Compute heat index in Celsius (isFahreheit = false)
      float hic = dht.computeHeatIndex(t, h, false);

      Serial.print(F(" Humidity: "));
      Serial.print(h);
      Serial.print(F("%  Temperature: "));
      Serial.print(t);
      Serial.print(F("C "));
      Serial.print(f);
      Serial.print(F("F  Heat index: "));
      Serial.print(hic);
      Serial.print(F("C "));
      Serial.print(hif);
      Serial.println(F("F"));
      lcd.setCursor(0,1);
      lcd.print(t);
      lcd.setCursor(4,1);
      lcd.print("c");
      lcd.setCursor(7,1);
      lcd.print(h);
      lcd.setCursor(9,1);
      lcd.print("%");
      lcd.setCursor(10,1);
      lcd.print("  ");
      delay(500);
      
    }
  } else {
    Serial.println("Error Data");
    delay(500);
    
  }
  
}
