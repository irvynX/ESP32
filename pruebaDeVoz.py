import pyttsx3

# Inicializar el motor de síntesis de voz
engine = pyttsx3.init()

# Obtener la lista de voces disponibles
voices = engine.getProperty('voices')

# Enumerar las voces disponibles
for voice in voices:
    print("Id: %s" % voice.id)
    print("Nombre: %s" % voice.name)
    print("Idioma: %s" % voice.languages)
    print("")

# Seleccionar una voz específica (por índice)
selected_voice_index = 0
engine.setProperty('voice', voices[selected_voice_index].id)

# Ejemplo de texto a sintetizar
texto = "Hola, esta es una prueba de síntesis de voz"

# Sintetizar y reproducir el texto con la voz seleccionada
engine.say(texto)
engine.runAndWait()
