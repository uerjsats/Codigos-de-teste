#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_INA219.h>


Adafruit_INA219 ina219;

SoftwareSerial suprimentoSerial(8, 9);

struct bateria{

  float tensao = 0.0f;
  float corrente = 0.0f;
  float power = 0.0f;

};

bateria dados;

/*void dadosBateria()
{
  
  dados.tensao = ina219.getBusVoltage_V();
  dados.corrente = ina219.getCurrent_mA() / 1000.0f;

  //Os dados zerados, são artificiais pela falta de sensor de temperatura
  String resposta = "1:0:0:" + String(dados.tensao, 1) + ":" + String(dados.corrente, 2);
  suprimentoSerial.println(resposta);

}*/

void setup() 
{
  Serial.begin(115200);
  suprimentoSerial.begin(9600);
}

void loop() 
{

  //dadosBateria();
  suprimentoSerial.println("1:0:0:3.3:5.2");
  delay(2000);

}