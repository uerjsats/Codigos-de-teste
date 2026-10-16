#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu; 

unsigned long tempoInicial;

const int IN1 = 9; 
const int IN2 = 8; 
const int IN3 = 7; 
const int IN4 = 5; 

SoftwareSerial controleSerial(12, 13);

void setup() 
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  Serial.begin(115200);
  controleSerial.begin(115200);
  Wire.begin(); 

  if (mpu.begin())
  {
    Serial.println("MPU6050 inicializado com sucesso!"); 
  }
}

void loop() {

  sensors_event_t a, g, temp; 

  mpu.getEvent(&a, &g, &temp); 

  if(controleSerial.available() > 0)
  {
    char dado_recebido = controleSerial.read(); 

    if (dado_recebido == '1')
    {
      controleSerial.setTimeout(10);

      String lixo = controleSerial.readStringUntil('\n');
      float ax = a.acceleration.x;
      float ay = a.acceleration.y;
      float az = a.acceleration.z; 
      float gx = g.gyro.x;
      float gy = g.gyro.y;
      float gz = g.gyro.z;
      String resposta = String(ax) + ":" + String(ay) + ":" + String(az) + ":" + String(gx) + ":" + String(gy) + ":" + String(gz); 
      controleSerial.print("1:");
      controleSerial.println(resposta);
      Serial.println(resposta);
    }

    else if (dado_recebido == '3')
    {
      pinMode(IN1, HIGH);
      pinMode(IN2, LOW);
      pinMode(IN3, HIGH);
      pinMode(IN4, LOW);
      delay(3000); 

      pinMode(IN1, LOW);
      pinMode(IN2, HIGH);
      pinMode(IN3, HIGH);
      pinMode(IN4, LOW);
      delay(3000); 
    }

  }
}