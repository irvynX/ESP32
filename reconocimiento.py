import speech_recognition as sr
import requests
import openai
import time
import pyttsx3

openai.api_key = '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'
paraEsp = False

# enviar mensaje a la IA
def enviar_mensaje(mensaje):
    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": "eres un asistente virtual personal"},
            {"role": "user", "content": mensaje},
        ]
    )
    return response.choices[0].message.content

# Función para enviar una solicitud HTTP GET sin procesar la respuesta
def enviar_solicitud(url):
    try:
        response = requests.get(url, timeout=5)
        # Ignorar la respuesta y no hacer nada con ella
    except requests.exceptions.RequestException as e:
        print("Error al enviar la solicitud:", e)

# Configuración del reconocimiento de voz
r = sr.Recognizer()

# Configuración de síntesis de voz
engine = pyttsx3.init()

# Bucle infinito para mantener el programa en ejecución continua
while True:
    # Escucha hasta que se detecte la palabra clave "computadora"
    with sr.Microphone() as source:
        print("Esperando la palabra clave...")
        while True:
            audio = r.listen(source, phrase_time_limit=5)

            try:
                texto = r.recognize_google(audio, language="es")
                texto = texto.lower() 
                print("Has dicho: " + texto)

                if "cortana" in texto:
                    paraEsp = False
                    print("¡Palabra clave reconocida!")
                    engine.runAndWait()
                    break  # Salir del bucle y pasar a la escucha de la petición

            except sr.UnknownValueError:
                print("")
            except sr.RequestError as e:
                print("Error al enviar la solicitud; {0}".format(e))

    # Escucha la petición del usuario después de detectar la palabra clave
    with sr.Microphone() as source:
        print("Di algo...")
        engine.say("¿en que puedo ayudarte? ....")
        engine.runAndWait()


        audio = r.listen(source, timeout=10, phrase_time_limit=10)

        try:
            texto = r.recognize_google(audio, language="es")
            texto = texto.lower()
            print("Has dicho: " + texto)

            if "enciende todo" in texto:
                enviar_solicitud("http://192.168.100.126/enCasa")
                engine.say("todas las luces fueron encendidas")
                engine.runAndWait()
                paraEsp = True

            elif "apaga todo" in texto:
                enviar_solicitud("http://192.168.100.126/fueraCasa")
                engine.say("todas las luces fueron apagadas")
                engine.runAndWait()
                paraEsp = True

            elif "enciende el foco" in texto:
                enviar_solicitud("http://192.168.100.126/?foco=1")
                engine.say("foco encendido")
                engine.runAndWait()
                paraEsp = True

            elif "apaga el foco" in texto:
                enviar_solicitud("http://192.168.100.126/?foco=0")
                engine.say("foco apagado")
                engine.runAndWait()
                paraEsp = True

            elif "enciende las luces" in texto:
                enviar_solicitud("http://192.168.100.126/encenderLuces")
                engine.say("las tiras leds fueron encendidas")
                engine.runAndWait()
                paraEsp = True

            elif "apaga las luces" in texto:
                enviar_solicitud("http://192.168.100.126/apagarLuces")
                engine.say("las tiras leds fueron apagadas")
                engine.runAndWait()
                paraEsp = True

            elif "cambia el efecto" in texto:
                enviar_solicitud("http://192.168.100.126/cambiarEfecto")
                engine.say("efecto de las luces cambiadas")
                engine.runAndWait()
                paraEsp = True

            if paraEsp == False:
                mensaje = texto.replace("computadora", "")
                mensaje = "intenta responder con menos de 500 caracteres a: " + mensaje
                print(mensaje)
                respuesta = enviar_mensaje(mensaje)
                print(respuesta)
                engine.say(respuesta)
                engine.runAndWait()

        except sr.UnknownValueError:
            print("")
        except sr.RequestError as e:
            print("Error al enviar la solicitud; {0}".format(e))
