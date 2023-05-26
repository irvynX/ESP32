import speech_recognition as sr
import requests
import pyttsx3

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
    # Utiliza el micrófono como fuente de audio
    with sr.Microphone() as source:
        print("Di algo...")
        audio = r.listen(source)

        try:
            # Reconocimiento de voz utilizando Google Speech Recognition
            texto = r.recognize_google(audio, language="es")
            print("Has dicho: " + texto)

            if "computadora" in texto:
                # Aquí puedes agregar la lógica que deseas ejecutar cuando se dice la palabra clave
                print("¡Palabra clave reconocida!")
                # Construir la URL con la solicitud basada en el texto reconocido
                
                if "enciende todo" in texto:
                    enviar_solicitud("http://192.168.100.126/enCasa")
                    # Reproducir el texto reconocido en el altavoz
                    engine.say("luces encendidas")
                    engine.runAndWait()

                if "apaga todo" in texto:
                    enviar_solicitud("http://192.168.100.126/fueraCasa")
                    # Reproducir el texto reconocido en el altavoz
                    engine.say("luces apagadas")
                    engine.runAndWait()

        except sr.UnknownValueError:
            print("")
        except sr.RequestError as e:
            print("Error al enviar la solicitud; {0}".format(e))

