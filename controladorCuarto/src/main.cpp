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

const String pagina1 = R"====(HTTP/1.1 200 OK
Content-Type: text/html
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-KK94CHFLLe+nY2dmCWGMq91rCGa5gtU4mk92HdvYe+M/SXH301p5ILy+dN9+nJOZ" crossorigin="anonymous">
    <title>APP-CUARTO</title>
</head>
<body class="bg-dark text-bg-dark">
    <div class="row">
        <div class="col-12">
            <div class="p-3">
                <form action="" method="get" class="text-center">
                    <div>
                        <h1> FOCO </h1>
                        <div class="btn-group" role="group" aria-label="Basic radio toggle button group">
                            <input type="radio" class="btn-check" name="foco" value="1" id="btnradio1" autocomplete="off" )====";
// ------------------------------- si el foco esta encendido agregamos un checked 
const String pagina2 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio1">ON</label>
                          
                            <input type="radio" class="btn-check" name="foco" value="0" id="btnradio2" autocomplete="off" )====";
// -------------------------------- si el foco esta apagado agregamos un checked
const String pagina3 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio2">OFF</label>
                        </div>
                        <br>
                        <br>
                        <br>
                        <input type="submit" value="enviar" class="btn btn-outline-info">
                    </div>
                </form>
                <br>
                <HR>
                <form action="" method="get" class="text-center">
                    <div>
                        <h1> TIRA LED ESCRITORIO </h1>
                        <div class="btn-group" role="group" aria-label="Basic radio toggle button group">
                            <input type="radio" class="btn-check" name="tiraE" value="1" id="btnradi" autocomplete="off" )====";
// ------------------------------- si la tira led escritorio esta encendida agregamos un checked
const String pagina4 = R"====(>
                            <label class="btn btn-outline-light" for="btnradi">ON</label>
                          
                            <input type="radio" class="btn-check" name="tiraE" value="0" id="btnrad" autocomplete="off" )====";
// ------------------------------ si la tira led escritorio esta apagada agregamos un checked
const String pagina5 = R"====(>
                            <label class="btn btn-outline-light" for="btnrad">OFF</label>
                        </div>
                        <br>
                        <br>
                        <br>
                        <h3> EFECTO </h3>
                        <div class="btn-group-vertical mb-4" role="group" aria-label="Basic radio toggle button group">
                            <input type="radio" class="btn-check" name="efecto" value="0" id="btnradio3" autocomplete="off" )====";
// ------------------------------ si el efecto es el o agregamos un checked
const String pagina6 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio3">ENCENDIDAS</label>
                          
                            <input type="radio" class="btn-check" name="efecto" value="1" id="btnradio4" autocomplete="off" )====";
// ------------------------------ si el efecto es el 1 agregamos un checked
const String pagina7 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio4">MUSICA 1</label>

                            <input type="radio" class="btn-check" name="efecto" value="2" id="btnradio5" autocomplete="off" )====";
// ------------------------------ si el efecto es el 2 agregamos un checked
const String pagina8 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio5">MUSICA 2</label>

                            <input type="radio" class="btn-check" name="efecto" value="3" id="btnradio6" autocomplete="off" )====";
// ------------------------------ si el efecto es el 3 agregamos un checked
const String pagina9 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio6">RECORRER TIRA</label>

                            <input type="radio" class="btn-check" name="efecto" value="4" id="btnradio7" autocomplete="off" )====";
// ------------------------------ si el efecto es el 4 agregamos un checked
const String pagina10 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio7">RESPIRAR</label>
                        </div>
                        <div class="mb-4 align-content-center">
                            <h3>COLOR</h3>
                            <input type="color" class="form-control form-control-color m-auto" value=")====";
// ------------------------------- ingresamos el valor en hexadecimal de la tira led
const String pagina11 = R"====(" title="Choose your color" name="color">
                        </div>
                        <br>
                        <br>
                        <h3>BRILLO</h3>
                        <div class="mb-4">
                            <input type="range" class="form-range w-50 p-3" min="0" max="255" step="5" id="customRange3" name="brillo" value=")====";
// ------------------------------ ingresamos el brillo de nuestra tira led en un rango de 0 a 255
const String pagina12 = R"====(">
                        </div>
                        <br>
                        <input type="submit" value="enviar" class="btn btn-outline-info">
                    </div>
                </form>
                <br>
                <HR>
                <form action="" method="get" class="text-center">
                    <div>
                        <h1> TIRA LED GABINETE </h1>
                        <div class="btn-group" role="group" aria-label="Basic radio toggle button group">
                            <input type="radio" class="btn-check" name="tiraG" value="1" id="G" autocomplete="off" )====";
// ---------------------------- si la tira gabinete esta encendida agregamos checked
const String pagina13 = R"====(>
                            <label class="btn btn-outline-light" for="G">ON</label>
                          
                            <input type="radio" class="btn-check" name="tiraG" value="0" id="G1" autocomplete="off" )====";
// --------------------------- si la tira gabinete esta apagada agregamos checked
const String pagina14 = R"====(>
                            <label class="btn btn-outline-light" for="G1">OFF</label>
                        </div>
                        <br>
                        <br>
                        <br>
                        <h3> EFECTO </h3>
                        <div class="btn-group-vertical mb-4" role="group" aria-label="Basic radio toggle button group">
                            <input type="radio" class="btn-check" name="efecto" value="0" id="btnradio8" autocomplete="off" )====";
// -------------------------- si el efecto es 0 agregamos checked
const String pagina15 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio8">ENCENDIDAS</label>
                          
                            <input type="radio" class="btn-check" name="efecto" value="1" id="btnradio9" autocomplete="off" )====";
// ------------------------- si el efecto es 1 agregamos checked
const String pagina16 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio9">MUSICA 1</label>

                            <input type="radio" class="btn-check" name="efecto" value="2" id="btnradio10" autocomplete="off" )====";
// -------------------------- si el efecto es 2 agregamos checked
const String pagina17 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio10">MUSICA 2</label>

                            <input type="radio" class="btn-check" name="efecto" value="3" id="btnradio11" autocomplete="off" )====";
// -------------------------- si el efcto es 3 agregamos checked
const String pagina18 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio11">RECORRER TIRA</label>

                            <input type="radio" class="btn-check" name="efecto" value="4" id="btnradio12" autocomplete="off" )====";
// -------------------------- si el efcto es 4 agregamos checked
const String pagina19 = R"====(>
                            <label class="btn btn-outline-light" for="btnradio12">RESPIRAR</label>
                        </div>
                        <div class="mb-4">
                            <h3>COLOR</h3>
                            <input type="color" class="form-control form-control-color m-auto" value=")====";
// -------------------------- valor en hexadecimal del color
const String pagina20 = R"====(" title="Choose your color" name="color">
                        </div>
                        <br>
                        <br>
                        <h3>BRILLO</h3>
                        <div class="mb-4">
                            <input type="range" class="form-range w-50 p-3" min="0" max="255" step="5" id="customRange3" name="brillo" value=")====";
// -------------------------- brillo de la tira led
const String pagina21 = R"====(">
                        </div>
                        <br>
                        <input type="submit" value="enviar" class="btn btn-outline-info">
                    </div>
                </form>
                <br>
                <HR>
                <form action="" method="get" class="text-center">
                    <h1> MICROFONO Y HORA </h1>
                    <div class="mb-4">
                        <h3>MULTIPLICADOR DEL MICROFONO</h3>
                        <input type="number" class="form-control w-25 m-auto" name="micro" value=")====";
// -------------------------- multiplicador del mucrofono
const String pagina22 = R"====(">
                    </div>
                    <div class="mb-4">
                        <h3>AUMENTAR O DISMINUIR</h3>
                        <div class="w-25 m-auto">
                            <div class="input-group mb-3">
                                <input type="number" class="form-control w-50 m-auto" placeholder="HH"  name="hora" min="-24" max="24" value=")====";
// -------------------------- hora que se va a sumar o restar al reloj
const String pagina23 = R"====(">
                                <input type="number" class="form-control w-50 m-auto" placeholder="MM" name="minuto" min="-60" max="60" value=")====";
// ------------------------- minutos que se va a sumar o restar al reloj
const String pagina24 = R"====(">
                            </div>                          
                        </div>
                    </div>
                    <br>
                    <input type="submit" value="enviar" class="btn btn-outline-info">
                </form>
            </div>
        </div>
    </div>
</body>
</html>)====";

const uint32_t TiempoEsperaWifi = 5000;

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500;

WiFiServer servidor(80);

// globales
// numero de leds
const int numLeds = 30;
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

// variables para las tiras led
// cada estado indica el efecto
//       0 = apagado
//       1 = encendido
//       2 = musica
//       3 = musica 2
//       4 = recorrer tira
//       5 = encender y apagar
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

// sencibilidaddel microfono
int mulMicrofono = 0;

// variables para el rele
int estadoRele = 0;
// variables para efectode musica 1
int encenderLeds = 0;
int tiempoActualMusica = 0;
int tiempoPrevioMusica = 0;
int intervaloMusica = 50;
int luces[numLeds];
// variables para llenar tira
int tiempoActualLlenar = 0;
int tiempoPrevioLlenar = 0;
int intervaloLlenar = 50;
int ledLlenar = 0;
// variables para respirar
int tiempoActualRes = 0;
int tiempoPrevioRes = 0;
int intervaloRes = 10;
int brillo = 0;
bool respirar = true;
// variables de la pagina
String valorHexa = "#FF0000";
int rojoTemp = 255;
int verdeTemp = 0;
int azulTemp = 0;

// variables para hora
int horaSumar = 0;
int minSumar = 0;

// pratiras led
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

// gabinete
Adafruit_NeoPixel pixelsG(numLeds, tira1, NEO_GRB + NEO_KHZ800);
// escritorio
Adafruit_NeoPixel pixelsE(numLeds, tira2, NEO_GRB + NEO_KHZ800);

void setup()
{
  // wifi
  Serial.begin(115200);
  Serial.println("\nIniciando Wifi");

  wifiMulti.addAP("Totalplay-2DA1-2", "irvyn2703");

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

// metodos simples --------------------------------------------
void encedeApagarTiraG()
{
  if (encenderG == 1)
  {
    encenderG = 0;
  }
  else
  {
    encenderG = 1;
  }
}

void encedeApagarTiraE()
{
  if (encenderE == 1)
  {
    encenderE = 0;
  }
  else
  {
    encenderE = 1;
  }
}

void encedeApagarFoco()
{
  if (estadoRele == 1)
  {
    estadoRele = 0;
  }
  else
  {
    estadoRele = 1;
  }
}

void cambiarEfectoG()
{
  estadoG++;
  if (estadoG > 4)
  {
    estadoG = 0;
  }
}

void cambiarEfectoE()
{
  estadoE++;
  if (estadoE > 4)
  {
    estadoE = 0;
  }
}

void encenderRele(){
  digitalWrite(rele, LOW);
}

void apagarRele(){
  digitalWrite(rele, LOW);
}

int leerMicro()
{
  // Leer el nivel de audio desde el micrófono
  int nivelAudio = analogRead(microfono) * mulMicrofono;

  // Convertir el nivel de audio en la cantidad de LED que se deben encender
  int cantidadLEDs = map(nivelAudio, 0, 1023, 0, numLeds);
  Serial.println("microfono: " + cantidadLEDs);

  return cantidadLEDs;
}

void hexaRGB (String valor){
  String hexColor = "#"; // valor hexadecimal
  hexColor = hexColor + valor;
  long number = (long) strtol(&hexColor[1], NULL, 16); // Convertir hexadecimal a decimal
  int r = (number >> 16) & 255; // Obtener valor de rojo
  int g = (number >> 8) & 255; // Obtener valor de verde
  int b = number & 255; // Obtener valor de azul

  Serial.print(r); // Imprimir valor de rojo en la consola serie
  Serial.print(",");
  Serial.print(g); // Imprimir valor de verde en la consola serie
  Serial.print(",");
  Serial.println(b); // Imprimir valor de azul en la consola serie

  rojoTemp = r;
  verdeTemp = g;
  azulTemp = b;
}

void RGBhexa (int r, int g, int b){
  String hexColor = String(r, HEX) + String(g, HEX) + String(b, HEX); // Convertir RGB a hexadecimal
  Serial.println(hexColor); // Imprimir valor hexadecimal en la consola serie
  valorHexa = "#" + hexColor;
}
//-----------------------------------metodos de los efectos --------------------------------

//-----------------------------------efecto Musica -----------------------------------------
void efectoMusica(Adafruit_NeoPixel &miPixels, int num)
{
  tiempoActualMusica = millis();
  if (tiempoActualMusica - tiempoPrevioMusica >= intervaloMusica){
    encenderLeds = leerMicro();
    for (int i = 0; i < (numLeds - 1); i++)
    {
      luces[i + 1] = luces[i];
    }
    luces[0] = encenderLeds;

    tiempoPrevioMusica = millis();
  }
  if (num == 1)
  {
    // tiraG efecto 1
    miPixels.fill(miPixels.Color(rojoG, verdeG, azulG), 0, encenderLeds);
    miPixels.fill(miPixels.Color(0, 0, 0), encenderLeds, numLeds);
    miPixels.show();
  }
  if (num == 2)
  {
    // tiraG efecto 2
    for (int i = 0; i < (numLeds - 1); i++)
    {
      miPixels.setPixelColor((i + 1), map(luces[i + 1], 0, 30, 0, rojoG), map(luces[i + 1], 0, 30, 0, verdeG), map(luces[i + 1], 0, 30, 0, azulG));
    }
    miPixels.setPixelColor((0), map(luces[0], 0, 30, 0, rojoG), map(luces[0], 0, 30, 0, verdeG), map(luces[0], 0, 30, 0, azulG));
    miPixels.show();
  }
  if (num == 3)
  {
    // tiraE efecto 1
    miPixels.fill(miPixels.Color(rojoE, verdeE, azulE), numLeds / 2, (numLeds / 2) + (encenderLeds / 2));
    miPixels.fill(miPixels.Color(0, 0, 0), (numLeds / 2) + (encenderLeds / 2), numLeds);
    miPixels.fill(miPixels.Color(rojoE, verdeE, azulE), (numLeds / 2) - (encenderLeds / 2), numLeds / 2);
    miPixels.fill(miPixels.Color(0, 0, 0), 0, (numLeds / 2) - (encenderLeds / 2));
    miPixels.show();
  }
  if (num == 4)
  {
    // tiraE efecto 2
    for (int i = 0; i < (numLeds - 1); i++)
    {
      miPixels.setPixelColor((i + 1), map(luces[i + 1], 0, 30, 0, rojoE), map(luces[i + 1], 0, 30, 0, verdeE), map(luces[i + 1], 0, 30, 0, azulE));
    }
    miPixels.setPixelColor((0), map(luces[0], 0, 30, 0, rojoE), map(luces[0], 0, 30, 0, verdeE), map(luces[0], 0, 30, 0, azulE));
    miPixels.show();
  }
}
//-----------------------------------efecto llenar tira -----------------------------------------
void llenarTira(Adafruit_NeoPixel &miPixelsG,Adafruit_NeoPixel &miPixelsE){
  tiempoActualLlenar = millis();
  if (tiempoActualLlenar - tiempoPrevioLlenar >= intervaloLlenar){
    if(estadoG == 3){
      miPixelsG.setPixelColor(ledLlenar - 3, rojoG/8, verdeG/8, azulG/8);
      miPixelsG.setPixelColor(ledLlenar - 2, rojoG/4, verdeG/4, azulG/4);
      miPixelsG.setPixelColor(ledLlenar - 1, rojoG/2, verdeG/2, azulG/2);
      miPixelsG.setPixelColor(ledLlenar, rojoG, verdeG, azulG);
      miPixelsG.show();
    }
    if(estadoE == 3){
      miPixelsE.setPixelColor(ledLlenar - 3, rojoE/8, verdeE/8, azulE/8);
      miPixelsE.setPixelColor(ledLlenar - 2, rojoE/4, verdeE/4, azulE/4);
      miPixelsE.setPixelColor(ledLlenar - 1, rojoE/2, verdeE/2, azulE/2);
      miPixelsE.setPixelColor(ledLlenar, rojoG, verdeG, azulG);
      miPixelsE.show();
    }
    ledLlenar++;
    if (ledLlenar > numLeds)
    {
      ledLlenar = 0;
    }
    tiempoPrevioLlenar = millis();
  }
}

//-----------------------------------efecto llenar tira -----------------------------------------
void repirar(){
  if (tiempoActualRes - tiempoPrevioRes >= intervaloRes)
  {
    if (estadoG == 4)
    {
      pixelsG.setBrightness(brillo);
      pixelsG.show();
    }
    if (estadoE == 4)
    {
      pixelsE.setBrightness(brillo);
      pixelsE.show();
    }
    if (respirar == true)
    {
      brillo++;
      if (brillo > 255)
      {
        respirar = false;
      }
    }
    else
    {
      brillo--;
      if (brillo < 1)
      {
        respirar = true;
      }
    }
  }
}

//----------------------------------- metodos para resporder y leer el cliente -------------------
//----------------------------------- metodo para enviar la pagina al cliente -------------------
void ResponderCliente(WiFiClient &cliente){
  cliente.print(pagina1);
  if(estadoRele == 1){
    cliente.print("checked");
  }
  cliente.print(pagina2);
  if(estadoRele == 0){
    cliente.print("checked");
  }
  cliente.print(pagina3);
  if(encenderE == 1){
    cliente.print("checked");
  }
  cliente.print(pagina4);
  if(encenderE == 0){
    cliente.print("checked");
  }
  cliente.print(pagina5);
  if(estadoE == 0){
    cliente.print("checked");
    cliente.print(pagina6);
    cliente.print(pagina7);
    cliente.print(pagina8);
    cliente.print(pagina9);
  }
  if(estadoE == 1){
    cliente.print(pagina6);
    cliente.print("checked");
    cliente.print(pagina7);
    cliente.print(pagina8);
    cliente.print(pagina9);
  }
  if(estadoE == 2){
    cliente.print(pagina6);
    cliente.print(pagina7);
    cliente.print("checked");
    cliente.print(pagina8);
    cliente.print(pagina9);
  }
  if(estadoE == 3){
    cliente.print(pagina6);
    cliente.print(pagina7);
    cliente.print(pagina8);
    cliente.print("checked");
    cliente.print(pagina9);
  }
  if(estadoE == 4){
    cliente.print(pagina6);
    cliente.print(pagina7);
    cliente.print(pagina8);
    cliente.print(pagina9);
    cliente.print("checked");
  }
  cliente.print(pagina10);
  RGBhexa(rojoE, verdeE, azulE);
  cliente.print(valorHexa);
  cliente.print(pagina11);
  cliente.print(brilloE);
  cliente.print(pagina12);
  if(encenderG == 1){
    cliente.print("checked");
  }
  cliente.print(pagina13);
  if(encenderG == 0){
    cliente.print("checked");
  }
  cliente.print(pagina14);
  if(estadoG == 0){
    cliente.print("checked");
    cliente.print(pagina15);
    cliente.print(pagina16);
    cliente.print(pagina17);
    cliente.print(pagina18);
  }
  if(estadoG == 1){
    cliente.print(pagina15);
    cliente.print("checked");
    cliente.print(pagina16);
    cliente.print(pagina17);
    cliente.print(pagina18);
  }
  if(estadoG == 2){
    cliente.print(pagina15);
    cliente.print(pagina16);
    cliente.print("checked");
    cliente.print(pagina17);
    cliente.print(pagina18);
  }
  if(estadoG == 3){
    cliente.print(pagina15);
    cliente.print(pagina16);
    cliente.print(pagina17);
    cliente.print("checked");
    cliente.print(pagina18);
  }
  if(estadoG == 4){
    cliente.print(pagina15);
    cliente.print(pagina16);
    cliente.print(pagina17);
    cliente.print(pagina18);
    cliente.print("checked");
  }
  cliente.print(pagina19);
  RGBhexa(rojoG, verdeG, azulG);
  cliente.print(valorHexa);
  cliente.print(pagina20);
  cliente.print(brilloG);
  cliente.print(pagina21);
  cliente.print(mulMicrofono);
  cliente.print(pagina22);
  cliente.print(horaSumar);
  cliente.print(pagina23);
  cliente.print(minSumar);
  cliente.print(pagina24);
}

//---------------------------------- verificacion de los mensajes ---------------------------
void VerificarMensaje(String Mensaje)
{
  int mensaje;
  int cont = 0;
  String temp;
  if (Mensaje.indexOf("?foco") >= 0){
    if(Mensaje.indexOf("foco=1") >= 0){
      estadoRele = 1;
    }else{
      estadoRele = 0;
    }
  }else if(Mensaje.indexOf("?tiraE") >= 0){
    if(Mensaje.indexOf("tiraE=1") >= 0){
      encenderE = 1;
    }else{
      encenderE = 0;
    }

    if(Mensaje.indexOf("efecto=0") >= 0){
      estadoE = 0;
    }else if(Mensaje.indexOf("efecto=1") >= 0){
      estadoE = 1;
    }else if(Mensaje.indexOf("efecto=2") >= 0){
      estadoE = 2;
    }else if(Mensaje.indexOf("efecto=3") >= 0){
      estadoE = 3;
    }else{
      estadoE = 4;
    }

    mensaje = Mensaje.indexOf("color=");
    temp = Mensaje[mensaje + 9];
    temp += Mensaje[mensaje + 10];
    temp += Mensaje[mensaje + 11];
    temp += Mensaje[mensaje + 12];
    temp += Mensaje[mensaje + 13];
    temp += Mensaje[mensaje + 14];
    Serial.println(temp);

    mensaje = Mensaje.indexOf("brillo=");
    temp = Mensaje[mensaje + 6];
    if(Mensaje[mensaje + 7] != ' ' || Mensaje[mensaje + 7] != '/n'){
      temp = Mensaje[mensaje + 7];
    }
    if(Mensaje[mensaje + 8] != ' ' || Mensaje[mensaje + 8] != '/n'){
      temp = Mensaje[mensaje + 8];
    }
    Serial.println(temp);
  }else if(Mensaje.indexOf("?tiraG") >= 0){
    if(Mensaje.indexOf("tiraG=1") >= 0){
      encenderG = 1;
    }else{
      encenderG = 0;
    }

    if(Mensaje.indexOf("efecto=0") >= 0){
      estadoG = 0;
    }else if(Mensaje.indexOf("efecto=1") >= 0){
      estadoG = 1;
    }else if(Mensaje.indexOf("efecto=2") >= 0){
      estadoG = 2;
    }else if(Mensaje.indexOf("efecto=3") >= 0){
      estadoG = 3;
    }else{
      estadoG = 4;
    }

    mensaje = Mensaje.indexOf("color=");
    temp = Mensaje[mensaje + 9];
    temp += Mensaje[mensaje + 10];
    temp += Mensaje[mensaje + 11];
    temp += Mensaje[mensaje + 12];
    temp += Mensaje[mensaje + 13];
    temp += Mensaje[mensaje + 14];
    Serial.println(temp);

    mensaje = Mensaje.indexOf("brillo=");
    temp = Mensaje[mensaje + 6];
    if(Mensaje[mensaje + 7] != ' ' || Mensaje[mensaje + 7] != '/n'){
      temp = Mensaje[mensaje + 7];
    }
    if(Mensaje[mensaje + 8] != ' ' || Mensaje[mensaje + 8] != '/n'){
      temp = Mensaje[mensaje + 8];
    }
    Serial.println(temp);
  }else if(Mensaje.indexOf("?micro") >= 0){
    mensaje = Mensaje.indexOf("micro=");
    cont = 0;
    temp = "";
    while(Mensaje[mensaje + 6 + cont] != '&'){
      temp += Mensaje[mensaje + 6 + cont];
      cont++;
    }
    Serial.println(temp);

    mensaje = Mensaje.indexOf("hora=");
    cont = 0;
    temp = "";
    while(Mensaje[mensaje + 5 + cont] != '&'){
      temp += Mensaje[mensaje + 5 + cont];
      cont++;
    }
    Serial.println(temp);

    mensaje = Mensaje.indexOf("minuto=");
    cont = 0;
    temp = "";
    while(Mensaje[mensaje + 7 + cont] != ' ' || Mensaje[mensaje + 7 + cont] != '/n'){
      temp += Mensaje[mensaje + 7 + cont];
      cont++;
    }
    Serial.println(temp);

  }
}

//------------------------------------------loop----------------------------------

void loop(){
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
  // tira gabinete
  if (encenderG == 0)
  {
    pixelsG.clear();
    pixelsG.show();
  }
  else if (estadoG == 0 && encenderG == 1)
  {
    pixelsG.fill(pixelsG.Color(rojoG, verdeG, azulG), 0, numLeds);
    pixelsG.setBrightness(brilloG);
    pixelsG.show();
  }
  else if (estadoG == 1 && encenderG == 1)
  {
    // metodo de musica
    pixelsG.setBrightness(brilloG);
    efectoMusica(pixelsG, 1); 
  }
  else if (estadoG == 2 && encenderG == 1)
  {
    // metodo llenar tira leds
    pixelsG.setBrightness(brilloG);
    efectoMusica(pixelsG, 2);
  }
  else if (estadoG == 3 && encenderG == 1)
  {
    // metodo llenar tira leds
    pixelsG.setBrightness(brilloG);
    llenarTira(pixelsG,pixelsE);
  }
  else if (estadoG == 4 && encenderG == 1)
  {
    // encender y apagar
    repirar();
  }

  // tira escritorio
  if (encenderE == 0)
  {
    pixelsE.clear();
    pixelsE.show();
  }
  else if (estadoE == 0 && encenderE == 1)
  {
    pixelsE.fill(pixelsE.Color(rojoE, verdeE, azulE), 0, numLeds);
    pixelsE.setBrightness(brilloE);
    pixelsE.show();
  }
  else if (estadoE == 1 && encenderE == 1)
  {
    // metodo de musica
    pixelsE.setBrightness(brilloE);
    efectoMusica(pixelsE, 3);
  }
  else if (estadoE == 2 && encenderE == 1)
  {
    // metodo llenar tira leds
    pixelsE.setBrightness(brilloE);
    efectoMusica(pixelsE, 4);
  }
  else if (estadoE == 3 && encenderE == 1)
  {
    // metodo llenar tira leds
    pixelsE.setBrightness(brilloE);
    llenarTira(pixelsG,pixelsE);
  }
  else if (estadoE == 4 && encenderE == 1)
  {
    // encender y apagar
    repirar();
  }

  // rele
  if (estadoRele == 0)
  {
    apagarRele();
  }
  else
  {
    encenderRele();
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
  if (botonEstado1 == HIGH)
  {
    encedeApagarTiraG();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado2 == HIGH)
  {
    encedeApagarTiraE();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado3 == HIGH)
  {
    encedeApagarFoco();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado4 == HIGH)
  {
    cambiarEfectoG();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado5 == HIGH)
  {
    cambiarEfectoE();
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado6 == HIGH)
  {
    encenderG = 0;
    encenderE = 0;
    estadoRele = 0;
    Serial.println("Botón táctil tocado!");
    delay(500);
  }

  if (botonEstado7 == HIGH)
  {
    encenderG = 1;
    encenderE = 1;
    estadoRele = 1;
    Serial.println("Botón táctil tocado!");
    delay(500);
  }
}
