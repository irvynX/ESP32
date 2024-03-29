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
#include <ArduinoJson.h>

const String pagina1 = R"====(
<html lang="es-MX">
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
                        <br>
                        <br>
                        <h3>BRILLO</h3>
                        <div class="mb-4">
                            <input type="range" class="form-range w-50 p-3" min="0" max="255" step="5" id="customRange3" name="brillo" value=")====";
// ------------------------------- ingresamos el valor en hexadecimal de la tira led
const String pagina11 = R"====(">
                        </div>
                        <br>
                        
                        <div class="mb-4 align-content-center">
                            <h3>COLOR</h3>
                            <input type="color" class="form-control form-control-color m-auto" value=")====";
// ------------------------------ ingresamos el brillo de nuestra tira led en un rango de 0 a 255
const String pagina12 = R"====(" title="Choose your color" name="color">
                        </div>
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
                        <br>
                        <br>
                        <h3>BRILLO</h3>
                        <div class="mb-4">
                            <input type="range" class="form-range w-50 p-3" min="0" max="255" step="5" id="customRange3" name="brillo" value=")====";
                        
// -------------------------- valor en hexadecimal del color
const String pagina20 = R"====(">
                        </div>
                        <div class="mb-4">
                            <h3>COLOR</h3>
                            <input type="color" class="form-control form-control-color m-auto" value=")====";
                        
// -------------------------- brillo de la tira led
const String pagina21 = R"====(" title="Choose your color" name="color">
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
                            <div class="invisible">
                              <input type="number" class="form-control w-50 m-auto" placeholder="MM" name="no" min="-60" max="60" value="1">
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
const long TiempoCancelacion = 10000;

WiFiServer servidor(80);

// globales
// numero de leds
const int numLeds = 30;
// tira gabinete
int tira1 = 18;
// tira escritorio
int tira2 = 19;
// reloj
int reloj = 21;
int numLedsReloj = 70;
int relojX = 14;
int relojY = 5;
int tiempoActualReloj = 0;
int tiempoPrevioReloj = 0;
int intervaloReloj = 50000;
int hora = 0;
int minutos = 0;
int tempMinutos = 0;
int tiempoActualPantalla = 10000;
int tiempoPrevioPantalla = 0;
int intervaloPantalla = 10;
int encenderReloj = 1;
// estas variables se tiene que configurar cuando hay notificacion
int notificacion = 0;
int cambioDeMinuto = 0;
int numLogo = 0;
int rojoGTemp = 0;
int verdeGTemp = 0;
int azulGTemp = 0;
int rojoETemp = 0;
int verdeETemp = 0;
int azulETemp = 0;
int encendidoGTemp = 0;
int encendidoETemp = 0;
// microfono
int microfono = 34;
// rele
int rele = 5;
// boton 1
/*
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
*/
// sensibilidad del boton
int botonLimite = 15;
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
int encenderG = 0;
int encenderE = 0;
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
int mulMicrofono = 5;

// variables para el rele
int estadoRele = 0;
// variables para efectode musica 1
int encenderLeds = 0;
int tiempoActualMusica = 0;
int tiempoPrevioMusica = 0;
int intervaloMusica = 50;
int ultimosEncenderLeds[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// variables para musica 2
int luces[numLeds];
int tiempoActualMusica2 = 0;
int tiempoPrevioMusica2 = 0;
int intervaloMusica2 = 50;
// variables para llenar tira
int tiempoActualLlenar = 0;
int tiempoPrevioLlenar = 0;
int intervaloLlenar = 40;
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

const int logo[3][5][3] = {
  // youtube
    {
        {0, 0, 0},
        {0, 1, 0},
        {0, 1, 1},
        {0, 1, 0},
        {0, 0, 0}
    },
    // facebook
    {
        {0, 1, 1},
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0},
        {0, 1, 0}
    },
    // whatsapp
    {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0}
    },
};
const int num0_9[10][5][3] = {
    // 0
    {
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1}
    },
    // 1
    {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    },
    // 2
    {
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1}
    },
    // 3
    {
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
    },
    // 4
    {
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1}
    },
    // 5
    {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
    },
    // 6
    {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    },
    // 7
    {
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1}
    },
    // 8
    {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    },
    // 9
    {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1}
    }
};


// pratiras led
#include <Adafruit_NeoPixel.h>

// gabinete
Adafruit_NeoPixel pixelsG(numLeds, tira1, NEO_GRB + NEO_KHZ800);
// escritorio
Adafruit_NeoPixel pixelsE(numLeds, tira2, NEO_GRB + NEO_KHZ800);
// reloj
Adafruit_NeoPixel pixelsReloj(numLedsReloj, reloj, NEO_GRB + NEO_KHZ800);
IPAddress staticIP(192, 168, 1, 100);  // La IP estática que deseas asignar
IPAddress gateway(192, 168, 1, 254);    // Dirección IP del gateway
IPAddress subnet(255, 255, 255, 0);   // Máscara de subred
void wifi(){
  Serial.println("\nIniciando Wifi");

  wifiMulti.addAP("cuartoRed", "irvyn2703");
  wifiMulti.addAP("Totalplay-2DA1", "irvyn2703");

  WiFi.mode(WIFI_STA);
  //WiFi.config(staticIP, gateway, subnet);
  Serial.print("Conectando a Wifi ..");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED)
  {
  }
  Serial.println(".. Conectado");
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
  Serial.print(" ID:");
  Serial.print(WiFi.localIP());
  Serial.print(" gateway:");
  Serial.print(WiFi.gatewayIP());
  Serial.print(" mascara:");
  Serial.println(WiFi.subnetMask());
  Serial.print(" macAddress:");
  Serial.println(WiFi.macAddress());  
}

void setup()
{
  randomSeed(analogRead(0));  // Puedes usar cualquier pin analógico

  // wifi
  Serial.begin(115200);
  wifi();
  servidor.begin();

  //MDNS.addService("http", "tcp", 80);

  // preparar entradas
  pinMode(microfono, INPUT);
  pinMode(rele, OUTPUT);

  pixelsReloj.begin();
  pixelsReloj.setBrightness(1);
  pixelsReloj.show();
  
  pixelsG.begin();
  pixelsE.begin();

  pixelsG.show();
  pixelsE.show();
}


//------------------------------------------mostrar numero en pantalla --------------
void mostrarNumero(int num, int x, int y) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      if (num0_9[num][i][j] == 1) {
        if ((j+ (x-1) + (relojX * i) + (relojX * (y-1))) <= (y+i) * relojX && (j+ (x-1) + (relojX * i) + (relojX * (y-1))) > (y+i-1) * relojX) {
          pixelsReloj.setPixelColor((j+ (x-1) + (relojX * i) + (relojX * (y-1))), 150, 150, 150);
        }
      }
    }
  }
}

//------------------------------------------mostrar logo en pantalla --------------
void mostrarLogo(int num, int x, int y) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      if (logo[num][i][j] == 1) {
        if ((j+ (x-1) + (relojX * i) + (relojX * (y-1))) <= (y+i) * relojX && (j+ (x-1) + (relojX * i) + (relojX * (y-1))) > (y+i-1) * relojX) {
          pixelsReloj.setPixelColor((j+ (x-1) + (relojX * i) + (relojX * (y-1))), 150, 150, 150);
        }
      }
    }
  }
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
  digitalWrite(rele, HIGH);
}

int leerMicro()
{
  // Leer el nivel de audio desde el micrófono
  int nivelAudio = analogRead(microfono) * mulMicrofono;
  //Serial.println(nivelAudio);
  if (nivelAudio < 0){
    nivelAudio = 0;
  }
  if (nivelAudio > 4000){
    nivelAudio = 4000;
  }
  // Convertir el nivel de audio en la cantidad de LED que se deben encender
  int cantidadLEDs = map(nivelAudio, 0, 4000, 0, numLeds-1);
  // Serial.println("microfono: " + cantidadLEDs);

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

void RGBhexa(int r, int g, int b) {
  char hexR[3];
  char hexG[3];
  char hexB[3];
  
  sprintf(hexR, "%02X", r);
  sprintf(hexG, "%02X", g);
  sprintf(hexB, "%02X", b);

  valorHexa = "#" + String(hexR) + String(hexG) + String(hexB); // Combinar con "#" y la cadena con ceros a la izquierda
  Serial.println(valorHexa);
}

void obtenerHora() {
    HTTPClient http;

    http.begin("http://worldtimeapi.org/api/timezone/America/Mexico_City");

    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK)
    {
        String payload = http.getString();

        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);

        if (!error)
        {
            String horaCompleta = doc["datetime"];

            hora = horaCompleta.substring(11, 13).toInt();
            minutos = horaCompleta.substring(14, 16).toInt();
            if (hora > 12)
            {
              hora -= 12;
            }
            if (tempMinutos != minutos){
              cambioDeMinuto = 10000/intervaloPantalla;
              tempMinutos = minutos;
            }

            Serial.print(hora);
            Serial.print(":");
            Serial.println(minutos);
        }
        else
        {
            Serial.println("Error parsing JSON");
        }
    }
    else
    {
        Serial.println("HTTP request failed");
    }

    http.end();
}

//-----------------------------------metodos de los efectos --------------------------------

//-----------------------------------efecto Musica -----------------------------------------
void efectoMusica(Adafruit_NeoPixel &miPixels, int num)
{
  tiempoActualMusica = millis();
  if (tiempoActualMusica - tiempoPrevioMusica >= intervaloMusica){
    encenderLeds = leerMicro();
    int encenderLeds = (encenderLeds + ultimosEncenderLeds[0] + ultimosEncenderLeds[1] + ultimosEncenderLeds[2] + ultimosEncenderLeds[3] + ultimosEncenderLeds[4] + ultimosEncenderLeds[5] + ultimosEncenderLeds[6] + ultimosEncenderLeds[7] + ultimosEncenderLeds[8] + ultimosEncenderLeds[9] + ultimosEncenderLeds[10] + ultimosEncenderLeds[11] + ultimosEncenderLeds[12] + ultimosEncenderLeds[13] + ultimosEncenderLeds[14] + ultimosEncenderLeds[15] + ultimosEncenderLeds[16] + ultimosEncenderLeds[17] + ultimosEncenderLeds[18] + ultimosEncenderLeds[19] / 21);
    for (int i = 0; i < 19; i++){
      ultimosEncenderLeds[i+1] = ultimosEncenderLeds[i]; 
    }
    ultimosEncenderLeds[0] = encenderLeds;
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
    miPixels.fill(miPixels.Color(rojoG, verdeG, azulG), 0, numLeds);
    miPixels.setBrightness(map(encenderLeds, 0, numLeds, 0, 255));
    miPixels.show();
  }
  if (num == 3)
  {
    // tiraE efecto 1
    miPixels.fill(miPixels.Color(rojoE, verdeE, azulE), 0, encenderLeds);
    miPixels.fill(miPixels.Color(0, 0, 0), encenderLeds, numLeds);
    miPixels.show();
  }
  if (num == 4)
  {
    // tiraE efecto 2
    miPixels.fill(miPixels.Color(rojoE, verdeE, azulE), 0, numLeds);
    miPixels.setBrightness(map(encenderLeds, 0, numLeds, 0, 255));
    miPixels.show();
  }
  int tam1 = map(encenderLeds, 0, numLeds, 0, numLedsReloj);
  int tam2 = map(ultimosEncenderLeds[1], 0, numLeds, 0, numLedsReloj);
  int tam3 = map(ultimosEncenderLeds[2], 0, numLeds, 0, numLedsReloj);
  int tam4 = map(ultimosEncenderLeds[3], 0, numLeds, 0, numLedsReloj);
  int tam5 = map(ultimosEncenderLeds[4], 0, numLeds, 0, numLedsReloj);

  // Calcular los nuevos tamaños de tam2 a tam5
  int nuevoTam2 = (tam2 + tam1) / 2;
  int nuevoTam3 = (tam3 + nuevoTam2) / 2;
  int nuevoTam4 = (tam4 + nuevoTam3) / 2;
  int nuevoTam5 = (tam5 + nuevoTam4) / 2;

  if(encenderReloj == 1){
    // de izquierda a derecha
    pixelsReloj.fill(pixelsReloj.Color(rojoG, verdeG, azulG), 0, nuevoTam4);
    pixelsReloj.fill(pixelsReloj.Color(0, 0, 0), nuevoTam4, relojX);

    pixelsReloj.fill(pixelsReloj.Color(rojoG, verdeG, azulG), relojX, nuevoTam2 + (relojX + 1));
    pixelsReloj.fill(pixelsReloj.Color(0, 0, 0), nuevoTam2 + (relojX), relojX * 2);

    pixelsReloj.fill(pixelsReloj.Color(rojoG, verdeG, azulG), relojX * 2, tam1 + (relojX * 2 + 1));
    pixelsReloj.fill(pixelsReloj.Color(0, 0, 0), tam1 + (relojX * 2), relojX * 3);

    pixelsReloj.fill(pixelsReloj.Color(rojoG, verdeG, azulG), relojX * 3, nuevoTam3 + (relojX * 3 + 1));
    pixelsReloj.fill(pixelsReloj.Color(0, 0, 0), nuevoTam3 + (relojX * 3), relojX * 4);

    pixelsReloj.fill(pixelsReloj.Color(rojoG, verdeG, azulG), relojX * 4, nuevoTam5 + (relojX * 4 + 1));
    pixelsReloj.fill(pixelsReloj.Color(0, 0, 0), nuevoTam5 + (relojX * 4), relojX * 5);

    if (cambioDeMinuto > 0)
    {
      int pos = map(cambioDeMinuto,0,10000/intervaloPantalla,0,35);
      if (pos > 28)
      {
        mostrarNumero((minutos/10),5,(1 - pos) + 28);
        mostrarNumero((minutos%10),8,(1 - pos) + 28);
        mostrarNumero((hora/10),(5 + pos) - 35,1);
        mostrarNumero((hora%10),(8 - pos) + 35,1);
      }else if (pos < 7){
        mostrarNumero((minutos/10),5,(1 + pos) - 7);
        mostrarNumero((minutos%10),8,(1 + pos) - 7);
        mostrarNumero((hora/10),(5 - pos),1);
        mostrarNumero((hora%10),(8 + pos),1);
      }else{
        mostrarNumero((minutos/10),5,1);
        mostrarNumero((minutos%10),8,1);
      }
      
      cambioDeMinuto -= 1;
    }else{
      mostrarNumero((hora/10),5,1);
      mostrarNumero((hora%10),8,1);
    }
    pixelsReloj.setBrightness(3);
    pixelsReloj.show();
  }

}
//-----------------------------------efecto llenar tira -----------------------------------------
void llenarTira(Adafruit_NeoPixel &miPixelsG,Adafruit_NeoPixel &miPixelsE){
  tiempoActualLlenar = millis();
  if (tiempoActualLlenar - tiempoPrevioLlenar >= intervaloLlenar){
    if(estadoG == 3){
      miPixelsG.setPixelColor(ledLlenar - 4, rojoG/16, verdeG/16, azulG/16);
      miPixelsG.setPixelColor(ledLlenar - 3, rojoE/8, verdeE/8, azulE/8);
      miPixelsG.setPixelColor(ledLlenar - 2, rojoE/4, verdeE/4, azulE/4);
      miPixelsG.setPixelColor(ledLlenar - 1, rojoE/2, verdeE/2, azulE/2);
      miPixelsG.setPixelColor(ledLlenar, rojoE, verdeE, azulE);
      miPixelsG.show();
    }
    if(estadoE == 3){
      miPixelsE.setPixelColor(ledLlenar - 4, rojoE/16, verdeE/16, azulE/16);
      miPixelsE.setPixelColor(ledLlenar - 3, rojoG/8, verdeG/8, azulG/8);
      miPixelsE.setPixelColor(ledLlenar - 2, rojoG/4, verdeG/4, azulG/4);
      miPixelsE.setPixelColor(ledLlenar - 1, rojoG/2, verdeG/2, azulG/2);
      miPixelsE.setPixelColor(ledLlenar, rojoG, verdeG, azulG);
      miPixelsE.show();
    }
    ledLlenar++;
    if (ledLlenar > numLeds)
    {
      miPixelsE.setPixelColor(numLeds - 4, rojoE/16, verdeE/16, azulE/16);
      miPixelsE.setPixelColor(numLeds - 3, rojoE/16, verdeE/16, azulE/16);
      miPixelsE.setPixelColor(numLeds - 2, rojoE/16, verdeE/16, azulE/16);
      miPixelsE.setPixelColor(numLeds - 1, rojoE/16, verdeE/16, azulE/16);

      miPixelsG.setPixelColor(numLeds - 4, rojoG/16, verdeG/16, azulG/16);
      miPixelsG.setPixelColor(numLeds - 3, rojoG/16, verdeG/16, azulG/16);
      miPixelsG.setPixelColor(numLeds - 2, rojoG/16, verdeG/16, azulG/16);
      miPixelsG.setPixelColor(numLeds - 1, rojoG/16, verdeG/16, azulG/16);

      miPixelsE.show();

      ledLlenar = 0;
    }
    tiempoPrevioLlenar = millis();
  }
}

//-----------------------------------efecto respirar tira -----------------------------------------
void repirar(){
  tiempoActualRes = millis();
  if (tiempoActualRes - tiempoPrevioRes >= intervaloRes)
  {
    if (estadoG == 4)
    {
      pixelsG.fill(pixelsG.Color(rojoG, verdeG, azulG), 0, numLeds);
      pixelsG.setBrightness(brillo);
      pixelsG.show();
    }
    if (estadoE == 4)
    {
      pixelsE.fill(pixelsE.Color(rojoE, verdeE, azulE), 0, numLeds);
      pixelsE.setBrightness(brillo);
      pixelsE.show();
    }
    Serial.println(brillo);
    if (respirar == true)
    {
      brillo++;
      if (brillo > 254)
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
    tiempoPrevioRes = millis();
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
  cliente.print(brilloE);
  cliente.print(pagina11);
  RGBhexa(rojoE, verdeE, azulE);
  cliente.print(valorHexa);
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
  cliente.print(brilloG);
  cliente.print(pagina20);
  RGBhexa(rojoG, verdeG, azulG);
  cliente.print(valorHexa);
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
  //codigo oculto
  if (Mensaje.indexOf("reloj") >= 0)
  {
    if(encenderReloj == 0){
      encenderReloj = 1;
    }else{
      encenderReloj = 0;
    }
  }
  if (Mensaje.indexOf("apagarFoco") >= 0)
  {
    estadoRele = 0;
  }
  if (Mensaje.indexOf("encenderFoco") >= 0)
  {
    estadoRele = 1;
  }
  if (Mensaje.indexOf("encenderLuces") >= 0){
    encenderG = 1;
    encenderE = 1;
  }
  if (Mensaje.indexOf("apagarLuces") >= 0){
    encenderG = 0;
    encenderE = 0;
  }
  if (Mensaje.indexOf("fueraCasa") >= 0){
    encenderG = 0;
    encenderE = 0;
    estadoRele = 0;
  }
  if (Mensaje.indexOf("enCasa") >= 0){
    encenderG = 1;
    encenderE = 1;
    estadoRele = 1;
  }
  if (Mensaje.indexOf("cambiarEfecto") >= 0){
    cambiarEfectoE();
    cambiarEfectoG();
  }
  if (Mensaje.indexOf("notificacion:") >= 0){
    if (Mensaje.indexOf("notificacion:Youtube") >= 0){
      if (notificacion == 0){
        numLogo = 0;
        notificacion = 10000/intervaloPantalla;
        encendidoETemp = encenderE;
        encendidoGTemp = encenderG;
        rojoETemp = rojoE;
        verdeETemp = verdeE;
        azulETemp = azulE;
        rojoGTemp = rojoG;
        verdeGTemp = verdeG;
        azulGTemp = azulG;
        encenderE = 1;
        encenderG = 1;
      }      
    }
    if (Mensaje.indexOf("notificacion:Facebook") >= 0){
      if (notificacion == 0){
        numLogo = 1;
        notificacion = 10000/intervaloPantalla;
        encendidoETemp = encenderE;
        encendidoGTemp = encenderG;
        rojoETemp = rojoE;
        verdeETemp = verdeE;
        azulETemp = azulE;
        rojoGTemp = rojoG;
        verdeGTemp = verdeG;
        azulGTemp = azulG;
        encenderE = 1;
        encenderG = 1;
      }
    }
    if (Mensaje.indexOf("notificacion:Whatsapp") >= 0){
      if (notificacion == 0){
        numLogo = 2;
        notificacion = 10000/intervaloPantalla;
        encendidoETemp = encenderE;
        encendidoGTemp = encenderG;
        rojoETemp = rojoE;
        verdeETemp = verdeE;
        azulETemp = azulE;
        rojoGTemp = rojoG;
        verdeGTemp = verdeG;
        azulGTemp = azulG;
        encenderE = 1;
        encenderG = 1;
      }
    }
  }
  
  //codigo normal
  if (Mensaje.indexOf("?foco") >= 0){
    if(Mensaje.indexOf("foco=1") >= 0){
      estadoRele = 1;
      Serial.println("rele encendido");
    }else{
      estadoRele = 0;
      Serial.println("rele apagado");
    }
  }else if(Mensaje.indexOf("?tiraE") >= 0){
    if(Mensaje.indexOf("tiraE=1") >= 0){
      Serial.println("tira E: encendido");
      encenderE = 1;
    }else{
      encenderE = 0;
      Serial.println("tira E: apagado");
    }

    if(Mensaje.indexOf("efecto=0") >= 0){
      estadoE = 0;
      Serial.println("efecto 0");
    }else if(Mensaje.indexOf("efecto=1") >= 0){
      estadoE = 1;
      Serial.println("efecto 1");
    }else if(Mensaje.indexOf("efecto=2") >= 0){
      estadoE = 2;
      Serial.println("efecto 2");
    }else if(Mensaje.indexOf("efecto=3") >= 0){
      estadoE = 3;
      Serial.println("efecto 3");
    }else{
      estadoE = 4;
      Serial.println("efecto 4");
    }

    mensaje = Mensaje.indexOf("color=");
    temp = Mensaje[mensaje + 9];
    temp += Mensaje[mensaje + 10];
    temp += Mensaje[mensaje + 11];
    temp += Mensaje[mensaje + 12];
    temp += Mensaje[mensaje + 13];
    temp += Mensaje[mensaje + 14];
    Serial.println(temp);
    hexaRGB(temp);
    rojoE = rojoTemp;
    verdeE = verdeTemp;
    azulE = azulTemp;

    mensaje = Mensaje.indexOf("brillo=");
    temp = Mensaje[mensaje + 7];
    if(Mensaje[mensaje + 8] != '&'){
      temp += Mensaje[mensaje + 8];
    }
    if(Mensaje[mensaje + 9] != '&'){
      temp += Mensaje[mensaje + 9];
    }
    Serial.println(temp);
    brilloE = temp.toInt();
  }else if(Mensaje.indexOf("?tiraG") >= 0){
    if(Mensaje.indexOf("tiraG=1") >= 0){
      encenderG = 1;
      Serial.println("tira G: encendida");
    }else{
      encenderG = 0;
      Serial.println("tira G: apagado");
    }

    if(Mensaje.indexOf("efecto=0") >= 0){
      estadoG = 0;
      Serial.println("efecto 0");
    }else if(Mensaje.indexOf("efecto=1") >= 0){
      estadoG = 1;
      Serial.println("efecto 1");
    }else if(Mensaje.indexOf("efecto=2") >= 0){
      estadoG = 2;
      Serial.println("efecto 2");
    }else if(Mensaje.indexOf("efecto=3") >= 0){
      estadoG = 3;
      Serial.println("efecto 3");
    }else{
      estadoG = 4;
      Serial.println("efecto 4");
    }

    mensaje = Mensaje.indexOf("color=");
    temp = Mensaje[mensaje + 9];
    temp += Mensaje[mensaje + 10];
    temp += Mensaje[mensaje + 11];
    temp += Mensaje[mensaje + 12];
    temp += Mensaje[mensaje + 13];
    temp += Mensaje[mensaje + 14];
    Serial.println(temp);
    hexaRGB(temp);
    rojoG = rojoTemp;
    verdeG = verdeTemp;
    azulG = azulTemp;

    mensaje = Mensaje.indexOf("brillo=");
    temp = Mensaje[mensaje + 7];
    if(Mensaje[mensaje + 8] != '&'){
      temp += Mensaje[mensaje + 8];
    }
    if(Mensaje[mensaje + 9] != '&'){
      temp += Mensaje[mensaje + 9];
    }
    Serial.println(temp);
    brilloG = temp.toInt();
  }else if(Mensaje.indexOf("?micro") >= 0){
    mensaje = Mensaje.indexOf("micro=");
    cont = 0;
    temp = "";
    while(Mensaje[mensaje + 6 + cont] != '&'){
      temp += Mensaje[mensaje + 6 + cont];
      cont++;
    }
    Serial.println("micro: " + temp);
    mulMicrofono = temp.toInt();

    mensaje = Mensaje.indexOf("hora=");
    cont = 0;
    temp = "";
    while(Mensaje[mensaje + 5 + cont] != '&'){
      temp += Mensaje[mensaje + 5 + cont];
      cont++;
    }
    Serial.println("hora: " + temp);
    horaSumar = temp.toInt();

    mensaje = Mensaje.indexOf("minuto=");
    cont = 0;
    temp = "";
    while(Mensaje[mensaje + 7 + cont] != '&'){
      temp += Mensaje[mensaje + 7 + cont];
      cont++;
    }
    Serial.println("minuto: " + temp);
    minSumar = temp.toInt();

  }
}

//------------------------------------------loop----------------------------------

void loop(){
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexión WiFi perdida. Intentando reconexión...");
    WiFi.reconnect();
  }
  WiFiClient cliente = servidor.available();
  // usuario en la pagina web
  if (cliente)
  {
    Serial.println("Nuevo Cliente");
    TiempoActual = millis();
    TiempoAnterior = millis();
    String LineaActual = "";

    while (cliente.connected() && (TiempoActual - TiempoAnterior <= TiempoCancelacion))
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

  //obtenemos la hora
  tiempoActualReloj = millis();
  if (tiempoActualReloj - tiempoPrevioReloj > intervaloReloj)
  {
    obtenerHora();
    tiempoPrevioReloj = millis();
  }  

  // pantalla del reloj
  tiempoActualPantalla = millis();
  if (tiempoActualPantalla - tiempoPrevioPantalla > intervaloPantalla)
  {
    if (encenderReloj == 1)
    {
      if (notificacion == 0)
      {
        int porcentajeMinutos = map(minutos,0,60,0,numLedsReloj);
        if (!((encenderE == 1 && (estadoE == 1 || estadoE == 2)) || (encenderG == 1 && (estadoG == 1 || estadoG == 2))))
        { 
          pixelsReloj.fill(pixelsG.Color(rojoG, verdeG, azulG), 0, porcentajeMinutos);
          pixelsReloj.fill(pixelsG.Color(0, 0, 0), porcentajeMinutos, numLedsReloj);
          if (cambioDeMinuto > 0)
          {
            int pos = map(cambioDeMinuto,0,10000/intervaloPantalla,0,35);
            if (pos > 28)
            {
              mostrarNumero((minutos/10),5,(1 - pos) + 28);
              mostrarNumero((minutos%10),8,(1 - pos) + 28);
              mostrarNumero((hora/10),(5 + pos) - 35,1);
              mostrarNumero((hora%10),(8 - pos) + 35,1);
            }else if (pos < 7){
              mostrarNumero((minutos/10),5,(1 + pos) - 7);
              mostrarNumero((minutos%10),8,(1 + pos) - 7);
              mostrarNumero((hora/10),(5 - pos),1);
              mostrarNumero((hora%10),(8 + pos),1);
            }else{
              mostrarNumero((minutos/10),5,1);
              mostrarNumero((minutos%10),8,1);
            }
            
            cambioDeMinuto -= 2;
          }else{
            mostrarNumero((hora/10),5,1);
            mostrarNumero((hora%10),8,1);
          }
        }
      }else{
        switch (numLogo){
        case 0:
          pixelsReloj.fill(pixelsG.Color(255, 0, 0), 0, numLedsReloj);
          rojoE = 255;
          verdeE = 0;
          azulE = 0;
          rojoG = 255;
          verdeG = 0;
          azulG = 0;
          encenderE = 1;
          encenderG = 1;
          break;
        case 1:
          pixelsReloj.fill(pixelsG.Color(0, 0, 255), 0, numLedsReloj);
          rojoE = 0;
          verdeE = 0;
          azulE = 255;
          rojoG = 0;
          verdeG = 0;
          azulG = 255;
          encenderE = 1;
          encenderG = 1;
          break;
        case 2:
          pixelsReloj.fill(pixelsG.Color(0, 255, 0), 0, numLedsReloj);
          rojoE = 0;
          verdeE = 255;
          azulE = 0;
          rojoG = 0;
          verdeG = 255;
          azulG = 0;
          encenderE = 1;
          encenderG = 1;
          break;
        default:
          pixelsReloj.fill(pixelsG.Color(150, 75, 175), 0, numLedsReloj);
          rojoE = 190;
          verdeE = 255;
          azulE = 200;
          rojoG = 146;
          verdeG = 225;
          azulG = 200;
          encenderE = 1;
          encenderG = 1;
          break;
        }
        mostrarLogo(numLogo,1,1);
        mostrarLogo(numLogo,12,1);
        mostrarNumero((hora/10),5,1);
        mostrarNumero((hora%10),8,1);

        if (notificacion == 1){
          encenderE = encendidoETemp;
          encenderG = encendidoGTemp;
          rojoE = rojoETemp;
          verdeE = verdeETemp;
          azulE = azulETemp;
          rojoG = rojoGTemp;
          verdeG = verdeGTemp;
          azulG = azulGTemp;
        }
        

        //reducir notificacion 
        notificacion -= 1;
      }
    }
    else{
      pixelsReloj.clear();
    }
    pixelsReloj.setBrightness(1);
    pixelsReloj.show();
    tiempoPrevioPantalla = millis();
  }

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
  int btnEstado1 = touchRead(T9);
  int btnEstado2 = touchRead(T8);
  int btnEstado3 = touchRead(T7);
  int btnEstado4 = touchRead(T6);
  int btnEstado5 = touchRead(T5);
  int btnEstado6 = touchRead(T4);
  int btnEstado7 = touchRead(T3);


  // realizar acciones en función del estado de los botones
  /*
  if (btnEstado1 < botonLimite)
  {
    encedeApagarTiraG();
    Serial.println("Botón tira 1!");
    delay(250);
  }

  if (btnEstado2 < botonLimite)
  {
    encedeApagarTiraE();
    Serial.println("Botón tira 2!");
    delay(250);
  }

  if (btnEstado3 < botonLimite)
  {
    encedeApagarFoco();
    Serial.println("Botón rele!");
    delay(250);
  }

  if (btnEstado4 < botonLimite)
  {
    encenderG = 1;
    encenderE = 1;
    estadoRele = 1;
    Serial.println("Botón encender todo!");
    delay(250);
  }

  if (btnEstado5 < botonLimite)
  {
    cambiarEfectoE();
    Serial.println("Botón cambiar efecto tira 2!");
    delay(250);
  }

  if (btnEstado6 < botonLimite)
  {
    cambiarEfectoG();
    Serial.println("Botón cambiar efecto tira 1!");
    delay(250);
  }

  if (btnEstado7 < botonLimite)
  {
    encenderG = 0;
    encenderE = 0;
    estadoRele = 0;
    Serial.println("Botón apagar todo!");
    delay(250);
  }
  */
}
