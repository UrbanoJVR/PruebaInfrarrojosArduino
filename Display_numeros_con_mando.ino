#include "IRLremote.h"

/*
     OJO NOTA IMPORTANTE:

     RECUERDA CONFIGURAR EL MONITOR SERIE A 115200 BAUDIOS!!!!!
*/

const int interruptIR = 0;
uint8_t IRProtocol = 0;  // Variables para recibir los datos
uint16_t IRAddress = 0;
uint32_t IRCommand = 0;

bool audio = true;


void setup() {
  Serial.begin(115200);  // Fijate en la velocidad
  for (int i = 3; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  IRLbegin<IR_ALL>(interruptIR);
  digitalWrite(3, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t oldSREG = SREG;  // Parar las interrupciones
  cli();
  if (IRProtocol)//Entramos si reconoce el protocolo
  {
    Serial.print("Protocol:");
    Serial.println(IRProtocol);
    Serial.print("Address:");
    Serial.println(IRAddress, HEX);
    Serial.print("Command:");
    Serial.println(IRCommand, HEX);
    switch (IRCommand)
    {
      case 0x6897:
        Serial.println("0 (Cero)");
        bip();
        escribirCero();
        break;
      case 0x30CF:
        Serial.println("1");
        bip();
        escribirUno();
        break;
      case 0x18E7:
        Serial.println("2");
        bip();
        escribirDos();
        break;
      case 0x7A85:
        Serial.println("3");
        bip();
        escribirTres();
        break;
      case 0x10EF:
        Serial.println("4");
        bip();
        escribirCuatro();
        break;
      case 0x38C7:
        Serial.println("5");
        bip();
        escribirCinco();
        break;
      case 0x5AA5:
        Serial.println("6");
        bip();
        escribirSeis();
        break;
      case 0x42BD:
        Serial.println("7");
        bip();
        escribirSiete();
        break;
      case 0x4AB5:
        Serial.println("8");
        bip();
        escribirOcho();
        break;
      case 0x52AD:
        Serial.println("9");
        bip();
        escribirNueve();
        break;
      case 0xA25D:
        Serial.println("Apagar");
        bip();
        borrar();
        break;
      case 0x629D:
        Serial.println("Modo");
        break;
      case 0xE01F:
        Serial.println("EQ");
        break;  
      case 0xE21D:
        Serial.println("Mute");
        if(audio){
          //Si el audio está activado lo apagamos y apagamos led azul
          audio = false;
          digitalWrite(3, LOW);
        } else {
          //Si audio desactivado, activamos y encendemos led azul
          audio = true;
          digitalWrite(3, HIGH);
        }
        break;
      case 0xFFFF:
        Serial.println("Desconocido");
        digitalWrite(6, HIGH);
        delay(2500);
        digitalWrite(6, LOW);
      break;
      default:
        break;
    }
    IRProtocol = 0;
  }
  SREG = oldSREG;
}

void IREvent(uint8_t protocol, uint16_t address, uint32_t command)
{
  IRProtocol = protocol;  // Recogemos los valores
  IRAddress = address;
  IRCommand = command;
}

void borrar(){
  for(int i = 6; i < 14; i++){
    digitalWrite(i, LOW);
  }
}

void bip(){
  if(audio){
    //Hacemos sonar el bip y encendemos y apagamos el led amarillo durante 100 ms
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(10000);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
  } else{
    //Solo encendemos led amarillo durante 100 ms
    digitalWrite(4, HIGH);
    delay(10000);
    digitalWrite(4, LOW);
  }
}

void escribirCero(){
  borrar();
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
}

void escribirUno(){
  borrar();
  digitalWrite(10, HIGH);
  digitalWrite(7, HIGH);
}

void escribirDos(){
  borrar();
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
}

void escribirTres(){
  borrar();
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

void escribirCuatro(){
  borrar();
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(7, HIGH);
}

void escribirCinco(){
  borrar();
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

void escribirSeis(){
  borrar();
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
}

void escribirSiete(){
  borrar();
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(7, HIGH);
}

void escribirOcho(){
  borrar();
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
}

void escribirNueve(){
  borrar();
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

