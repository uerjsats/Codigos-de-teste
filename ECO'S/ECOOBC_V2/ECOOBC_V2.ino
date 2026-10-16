#include <HardwareSerial.h>
#include <RadioLib.h>

HardwareSerial controleSerial(1);
HardwareSerial suprimentoSerial(2);

#define baudRate 9600

#define CONTROLE_RX 33
#define CONTROLE_TX 34
#define SUPRIMENTO_RX 19
#define SUPRIMENTO_TX 20

SX1262 radio = new Module(8, 14, 12, 13);

const float FREQUENCIA = 915.0; 
const float BANDWIDTH = 125.0; 
const uint8_t SPREADING_FACTOR = 7; 
const uint8_t CODING_RATE = 5;
const int8_t POTENCIA_TX = 10; 

volatile bool comandoRecebido = false; 

void quandoReceber()
{
  comandoRecebido = true; 
}


void setup() {
  Serial.begin(115200);
  controleSerial.begin(baudRate, SERIAL_8N1, CONTROLE_RX, CONTROLE_TX);
  suprimentoSerial.begin(baudRate, SERIAL_8N1, SUPRIMENTO_RX, SUPRIMENTO_TX);

  pinMode(35, OUTPUT); 
  digitalWrite(35, LOW);
  delay(100); 

  int estado = radio.begin(FREQUENCIA, BANDWIDTH, SPREADING_FACTOR, CODING_RATE);

  if (estado == RADIOLIB_ERR_NONE)
  {
    Serial.println("Sucesso!"); 
  }
  else 
  {
    Serial.print("Falha, código de erro: ");
    Serial.println(estado); 
  }

  radio.setOutputPower(POTENCIA_TX); 

  radio.setPacketReceivedAction(quandoReceber); 

  radio.startReceive(); 


}

void loop()
{

  if(comandoRecebido)
  {
    comandoRecebido = false; 
    String comandoRadio = ""; 
    int estado = radio.readData(comandoRadio); 
    if (estado == RADIOLIB_ERR_NONE)
    {
      comandoRadio.trim(); 
      if(comandoRadio == "1" || comandoRadio == "3")
    {
      controleSerial.print(comandoRadio);
    }
    else if(comandoRadio == "2")
    {
      suprimentoSerial.print(comandoRadio);
    }

    }
  }
  
  if(controleSerial.available())
  {
    String resposta = controleSerial.readStringUntil('\n');
    resposta.trim();
    int estadoTX = radio.transmit("3:" + resposta);
    if (estadoTX == RADIOLIB_ERR_NONE)
    {
      Serial.println("Sucesso!"); 
    }
    radio.startReceive(); 
  }

  if(suprimentoSerial.available())
  {
    String resposta = suprimentoSerial.readStringUntil('\n');
    resposta.trim();
    int estadoTX = radio.transmit("1:" + resposta);
    if (estadoTX == RADIOLIB_ERR_NONE)
    {
      Serial.println("Sucesso!"); 
    }
    radio.startReceive(); 
  }
  radio.startReceive(); 
}
