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
// tira gabinete
int tira1 = 18;
// tira escritorio
int tira2 = 19;
// microfono
int microfono = 34;
// rele
int rele = 5;
// boton 1
int boton1 = 32;
// boton 2
int boton2 = 33;
// boton 3
int boton3 = 27;
// boton 4
int boton4 = 14;
// boton 5
int boton5 = 12;
// boton 6
int boton6 = 13;
// Definir el número de pin del botón táctil
int boton7 = 15;
// nombre de la red
String nombreRed = "Totalplay-2DA1-2";
// contraseña de la red
String contraRed = "irvyn2703";

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
int encenderG = 1;
int encenderE = 1;
// color de la tira
int rojoG = 255;
int verdeG = 0;
int azulG = 0;
int brilloG = 255;
int rojoE = 255;
int verdeE = 0;
int azulE = 0;
int brilloE = 255;

//variables para el rele
int estadoRele = 0;
//variables para efectode musica 1
int tiempoActualMusica = 0;
int tiempoPrevioMusica = 0;
int intervaloMusica = 50;
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
  pinMode(boton7, INPUT);

  pixelsG.begin();
  pixelsE.begin();

  pixelsG.show();
  pixelsE.show();
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
  if (encenderG == 0){
    pixelsG.clear();
    pixelsG.show();
  }else if (estadoG == 0 && encenderG == 1){
    pixelsG.fill(pixelsG.Color(rojoG, verdeG, azulG), 0, numLeds);
    pixelsG.setBrightness(brilloG);
    pixelsG.show();
  }else if (estadoG == 1 && encenderG == 1){
    // metodo de musica
    pixelsG.setBrightness(brilloG);
    efectoMusica(pixelsG,1); // <------------------------ falta
  }else if (estadoG == 2 && encenderG == 1)
  {
    // metodo llenar tira leds
    pixelsG.setBrightness(brilloG);
    efectoMusica(pixelsG,2);
  }else if (estadoG == 3 && encenderG == 1)
  {
    // metodo llenar tira leds
    pixelsG.setBrightness(brilloG);
    llenarTira(pixelsG);
  }else if (estadoG == 4 && encenderG == 1)
  {
    // encender y apagar
    repirar(pixelsG);
  }
  
  //tira escritorio
  if (encenderE == 0){
    pixelsE.clear();
    pixelsE.show();
  }else if (estadoE == 0 && encenderE == 1){
    pixelsE.fill(pixelsE.Color(rojoE, verdeE, azulE), 0, numLeds);
    pixelsE.setBrightness(brilloE);
    pixelsE.show();
  }else if (estadoE == 1 && encenderE == 1){
    // metodo de musica
    pixelsE.setBrightness(brilloE);
    efectoMusica(pixelsE,3); // <------------------------ falta
  }else if (estadoE == 2 && encenderE == 1)
  {
    // metodo llenar tira leds
    pixelsE.setBrightness(brilloE);
    efectoMusica(pixelsE,4);
  }else if (estadoE == 3 && encenderE == 1)
  {
    // metodo llenar tira leds
    pixelsE.setBrightness(brilloE);
    llenarTira(pixelsE);
  }else if (estadoE == 4 && encenderE == 1)
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

  // leer estado de los botones
  int botonEstado1 = digitalRead(boton1); // encender y apagar tira 1
  int botonEstado2 = digitalRead(boton2); // encender y apagar tira 2
  int botonEstado3 = digitalRead(boton3); // encender y apagar rele
  int botonEstado4 = digitalRead(boton4); // cambiar efecto 1
  int botonEstado5 = digitalRead(boton5); // cambiar efecto 2
  int botonEstado6 = digitalRead(boton6); // apagar todo
  int botonEstado7 = digitalRead(boton7); // encender todo

  // realizar acciones en función del estado de los botones
  if (botonEstado1 == HIGH) {
    encedeApagarTiraG();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado2 == HIGH) {
    encedeApagarTiraE();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado3 == HIGH) {
    encedeApagarFoco();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado4 == HIGH) {
    cambiarEfectoG();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado5 == HIGH) {
    cambiarEfectoE();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado6 == HIGH) {
    encenderG = 0;
    encenderE = 0;
    estadoRele = 0;
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado7 == HIGH) {
    encenderG = 1;
    encenderE = 1;
    estadoRele = 1;
    Serial.println("Botón táctil tocado!");
    delay(500);
  }
}

// metodos simples --------------------------------------------
void encedeApagarTiraG(){
  if (encenderG == 1)
  {
    encenderG = 0;
  }else{
    encenderG = 1;
  }
}

void encedeApagarTiraE(){
  if (encenderE == 1)
  {
    encenderE = 0;
  }else{
    encenderE = 1;
  }
}

void encedeApagarFoco(){
  if (estadoRele == 1)
  {
    estadoRele = 0;
  }else{
    estadoRele = 1;
  }
}

void cambiarEfectoG(){
  estadoG++;
  if (estadoG > 4)
  {
    estadoG = 0;
  } 
}

void cambiarEfectoE(){
  estadoE++;
  if (estadoE > 4)
  {
    estadoE = 0;
  } 
}

int leerMicro(){
  // Leer el nivel de audio desde el micrófono
  int nivelAudio = analogRead(microfono);

  // Convertir el nivel de audio en la cantidad de LED que se deben encender
  int cantidadLEDs = map(nivelAudio, 0, 1023, 0, numLeds);
  Serial.println("microfono: " + cantidadLEDs);

  return cantidadLEDs;
}
//-----------------------------------metodos de los efectos --------------------------------
void efectoMusica(Adafruit_NeoPixel &miPixels,int num){
  tiempoActualMusica = millis();
  if (tiempoActualMusica - tiempoPrevioMusica >= intervaloMusica){
    int encenderLeds = leerMicro();
    if (num == 1)
    {
      //tiraG efecto 1
      miPixels.fill(pixels.Color(rojoG, verdeG, azulG), 0, encenderLeds);
      miPixels.fill(pixels.Color(0,0,0), encenderLeds, numLeds);
    }
    if (num == 2)
    {
      //tiraG efecto 2
    }
    if (num == 3)
    {
      //tiraE efecto 1
    }
    if (num == 2)
    {
      //tiraE efecto 2
    }
  }
}