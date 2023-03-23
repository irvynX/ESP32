#if defined(ESP32)
// Librerias para ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
WiFiMulti wifiMulti;

#elif defined(ESP8266)
// Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
ESP8266WiFiMulti wifiMulti;

#endif

#include <HTTPClient.h>

const uint32_t TiempoEsperaWifi = 5000;

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500;

WiFiServer servidor(80);

// globales
// numero de leds
int numLeds = 30;
// numero de reloj
int numLedsR = 70;
// tira gabinete
int tira1 = 4;
// tira escritorio
int tira2 = 18;
// tira reloj
int tira3 = 19;
// microfono
int microfono = 34
// rele
int rele = 27;
// boton 1
int boton1 = 0;
// boton 2
int boton2 = 2;
// boton 3
int boton3 = 5;
// boton 4
int boton4 = 12;
// boton 5
int boton5 = 13;
// boton 6
int boton6 = 15;
// nombre de la red
String nombreRed = "Totalplay-2DA1-2"
// contraseña de la red
String contraRed = "irvyn2703"

//variables para las tiras led
//cada estado indica el efecto
//      0 = apagado
//      1 = encendido
//      2 = musica
//      3 = musica 2
//      4 = recorrer tira
//      5 = encender y apagar
int estadoG = 0;
int estadoE = 0;
int estadoR = 0;
// color de la tira
int rojoG = 255;
int verdeG = 0;
int azulG = 0;
int rojoE = 255;
int verdeE = 0;
int azulE = 0;
int rojoR = 255;
int verdeR = 0;
int azulR = 0;

//variables para el rele
int estadoRele = 0;

//variables para suspender


/*#include <esp_sleep.h>

// Definir el número de pin del botón táctil
const int BUTTON_PIN = 14;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // Configurar el botón táctil para generar una interrupción cuando se presiona
  attachInterrupt(BUTTON_PIN, buttonInterrupt, FALLING);
}

void loop() {
  // Configurar la ESP32 para entrar en modo de sueño profundo
  esp_sleep_enable_touchpad_wakeup();
  esp_deep_sleep_start();
}

void buttonInterrupt() {
  // Código para manejar la interrupción del botón táctil
}
*/

// pratiras led
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

// gabinete
Adafruit_NeoPixel pixelsG(numLeds, tira1, NEO_GRB + NEO_KHZ800);
// escritorio
Adafruit_NeoPixel pixelsE(numLeds, tira2, NEO_GRB + NEO_KHZ800);
// reloj
Adafruit_NeoPixel pixelsR(numLedsR, tira3, NEO_GRB + NEO_KHZ800);


void setup() {
  // wifi
  Serial.begin(115200);
  Serial.println("\nIniciando Wifi");

  wifiMulti.addAP(nombreRed,contraRed);

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a Wifi ..");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED)
  {
  }
  Serial.println(".. Conectado");
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
  Serial.print(" ID:");
  Serial.println(WiFi.localIP());

  servidor.begin();

  MDNS.addService("http", "tcp", 80);

  // preparar entradas
  pinMode(microfono, INPUT);
  pinMode(rele, OUTPUT);
  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  pinMode(boton3, INPUT);
  pinMode(boton4, INPUT);
  pinMode(boton5, INPUT);
  pinMode(boton6, INPUT);

  pixelsG.begin();
  pixelsE.begin();
  pixelsR.begin();

  pixelsG.show();
  pixelsE.show();
  pixelsR.show();
}

void loop() {
  WiFiClient cliente = servidor.available();
  // usuario en la pagina web
  if (cliente)
  {
    Serial.println("Nuevo Cliente");
    TiempoActual = millis();
    TiempoAnterior = TiempoActual;
    String LineaActual = "";

    while (cliente.connected() && TiempoActual - TiempoAnterior <= TiempoCancelacion)
    {
      if (cliente.available())
      {
        TiempoActual = millis();
        char Letra = cliente.read();
        if (Letra == '\n')
        {
          if (LineaActual.length() == 0)
          {
            ResponderCliente(cliente); // <---------------------------falta
            break;
          }
          else
          {
            VerificarMensaje(LineaActual); // <---------------------------falta
            LineaActual = "";
          }
        }
        else if (Letra != '\r')
        {
          LineaActual += Letra;
        }
      }
    }

    cliente.stop();
    Serial.println("Cliente Desconectado");
    Serial.println();
  }

  // no hay usuarios en la red
  //tira gabinete
  if (estadoG == 0){
    pixelsG.clear();
    pixelsG.show();
  }else if (estadoG == 1){
    pixelsG.fill(pixelsG.Color(rojoG, verdeG, azulG), 0, numLeds);
    pixelsG.show();
  }else if (estadoG == 2){
    // metodo de musica
    efectoMusica(pixelsG,1); // <------------------------ falta
  }else if (estadoG == 3)
  {
    // metodo llenar tira leds
    efectoMusica(pixelsG,2);
  }else if (estadoG == 4)
  {
    // metodo llenar tira leds
    llenarTira(pixelsG);
  }else if (estadoG == 5)
  {
    // encender y apagar
    repirar(pixelsG);
  }
  
  //tira escritorio
  if (estadoE == 0){
    pixelsE.clear();
    pixelsE.show();
  }else if (estadoG == 1){
    pixelsE.fill(pixelsE.Color(rojoE, verdeE, azulE), 0, numLeds);
    pixelsE.show();
  }else if (estadoG == 2){
    // metodo de musica
    efectoMusica(pixelsE,1); // <------------------------ falta
  }else if (estadoG == 3)
  {
    // metodo llenar tira leds
    efectoMusica(pixelsE,2);
  }else if (estadoG == 4)
  {
    // metodo llenar tira leds
    llenarTira(pixelsE);
  }else if (estadoG == 5)
  {
    // encender y apagar
    repirar(pixelsE);
  }

  // rele
  if (estadoRele == 0){
    digitalWrite(rele, LOW);
  }else
  {
    digitalWrite(rele, HIGH);
  }

  // suspender
  if (estadoRele == 0 && estadoE == 0 && estadoG == 0 && estadoR == 0){

  }
  
  
}