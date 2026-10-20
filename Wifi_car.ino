
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "WiFi Car"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Your home router's Wi-Fi details
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// L298N direction pins
#define IN1 26
#define IN2 27
#define IN3 25
#define IN4 33

void stopMotors()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left()
{
  // Left side backward, right side forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right()
{
  // Left side forward, right side backward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Forward button: Virtual Pin V0
BLYNK_WRITE(V0)
{
  if (param.asInt()) forward();
  else stopMotors();
}

// Backward button: Virtual Pin V1
BLYNK_WRITE(V1)
{
  if (param.asInt()) backward();
  else stopMotors();
}

// Left button: Virtual Pin V2
BLYNK_WRITE(V2)
{
  if (param.asInt()) left();
  else stopMotors();
}

// Right button: Virtual Pin V3
BLYNK_WRITE(V3)
{
  if (param.asInt()) right();
  else stopMotors();
}

BLYNK_CONNECTED()
{
  // Start in a safe stopped state
  stopMotors();
}

void setup()
{
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();

  // Stop if the connection to Blynk Cloud is lost
  if (!Blynk.connected())
  {
    stopMotors();
  }
}
