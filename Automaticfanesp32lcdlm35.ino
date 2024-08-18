#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h> // Include the WiFi library

const char *ssid = "YourWiFiSSID";     // Your WiFi SSID
const char *password = "YourWiFiPassword"; // Your WiFi password

WiFiClient client;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

const int LM35_PIN = A0;  // LM35 analog pin
const int RELAY_PIN = 2;   // Relay pin
const float TEMP_THRESHOLD = 30.0; // Temperature threshold in Celsius

void setup() {
  Serial.begin(9600);
  lcd.backlight();
  pinMode(RELAY_PIN, OUTPUT);
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  float temperature = readTemperature();
  displayTemperature(temperature);
  controlFan(temperature);
  delay(1000);  // Delay for stability
}

float readTemperature() {
  int sensorValue = analogRead(LM35_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = voltage * 100.0; // LM35 outputs 10mV per degree celsius
  return temperatureC;
}

void displayTemperature(float temperatureC) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C");
  // displaay in serial monitor
 Serial.print("Temperature: "); 
 Serial.print("\tC: ");
 Serial.print(temperatureC);
 delay(1000); 
}
void controlFan(float temperature) {
  if (temperature > TEMP_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the fan
    lcd.setCursor(0, 1);
    lcd.print("Fan: ON ");
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off the fan
    lcd.setCursor(0, 1);
    lcd.print("Fan: OFF ");
  }
  delay(1000);
}
