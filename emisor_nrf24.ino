/*
EMISOR
 
Envia los mensajes "Apagar" y "Encender" en intervalos de un segundo
 
Escrito por Nano en beneficio de los seres humanos
www.robologs.net
*/
 
//#include <VirtualWire.h>
#include <LowPower.h>
#include "DHT.h"          // DHT & AM2302 library
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
//#include <SPI.h>

// Data pin connected to AM2302
#define DHTPIN 2
#define TEMPMAX 20
#define DHTTYPE DHT22       // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

RF24 radio(9,10);//RF24 (uint8_t _cepin, uint8_t _cspin)
const uint64_t pipe = 0xE8E8F0F0E1LL;

//vector con los datos a enviar
//float datos[3];
float datos;

void setup()
{
  //Iniciamos el Serial
  Serial.begin(9600);
  Serial.write("Sistema encendido\n");
  //vw_setup(2000);
  dht.begin();
//Iniciamos la comunicacion por radio
  radio.begin();
   radio.setChannel(108);  // Above most Wifi Channels
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MIN);
  //  radio.setPALevel(RF24_PA_MAX);  // Uncomment for more power
  radio.openWritingPipe(pipe);
  delay(1000);
   radio.printDetails();
   
}
void loop()
{  
  float temp = dht.readTemperature();
  char msg[24];
  if (isnan(temp) ) {
    Serial.write("Failed to read from DHT");
  }
  else{
   // Serial.write("Temperatura:");
   // Serial.println(temp,DEC);
   /* int temp1 = (int)temp;
    int temp2 = (int)((temp - temp1) * 100.0); // For two decimal points
    sprintf(msg, "%i.%i", temp1,temp2);
    send(msg);*/
    //datos[0]=temp;
    //datos[1]=temp;
   // datos[2]=temp;
   datos=temp;
    if(radio.write(&datos, sizeof(datos)))
    { 
      Serial.println("datos enviados");
      //Serial.println(datos[0]);
      Serial.println(datos);
    }
    else
     { 
      Serial.println("datos NO enviados");
    }
    
  }
  
  
  // Wait 3 seconds
  delay(2000);
 //LowPower.powerDown(SLEEP_4S, ADC_OFF,BOD_OFF);
}
 
//Funcion para enviar el mensaje
/*void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message)); //Envia el mensaje
  vw_wait_tx(); //Espera hasta que se haya acabado de transmitir todo
  
  Serial.println(message); //Muestra el mensaje por Serial
}*/
