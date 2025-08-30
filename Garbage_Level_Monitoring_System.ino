
#define BLYNK_TEMPLATE_ID   "TMPL3lpqAwNYn"
#define BLYNK_TEMPLATE_NAME "Garbage Level Monitoring System"
#define BLYNK_AUTH_TOKEN    "11oMoHriu8mBk86wvCUoXJvuqQbiTGJy"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";      
char pass[] = "";     

#define TRIG_PIN 5
#define ECHO_PIN 18

const int tankDepth = 400;   
int distance, fillPercent;

#define VPIN_LEVEL   V1   
#define VPIN_STATUS  V2   

BlynkTimer timer;


int readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms
  int cm = duration * 0.034 / 2;
  return cm;
}

// Check tank and send data
void checkTankLevel() {
  distance = readDistanceCM();

  // Clamp values
  if (distance <= 0 || distance > tankDepth) {
    Serial.println("Sensor error!");
    Blynk.virtualWrite(VPIN_STATUS, "Sensor Error");
    return;
  }

  
  fillPercent = ((tankDepth - distance) * 100) / tankDepth;
  if (fillPercent < 0) fillPercent = 0;
  if (fillPercent > 100) fillPercent = 100;

  Blynk.virtualWrite(VPIN_LEVEL, fillPercent);


  String status;
  if (fillPercent < 30) {
    status = "LOW";
  } else if (fillPercent < 80) {
    status = "MEDIUM";
  } else {
    status = "FULL";
    
    Blynk.logEvent("tank_full", "🚨 Tank is FULL – Please clean/empty!");
  }

  
  Blynk.virtualWrite(VPIN_STATUS, status);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Level: ");
  Serial.print(fillPercent);
  Serial.print("% | Status: ");
  Serial.println(status);
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(5000L, checkTankLevel);
}

void loop() {
  Blynk.run();
  timer.run();
}
