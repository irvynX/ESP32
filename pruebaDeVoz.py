# mi api 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
import openai

openai.api_key = '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'

def enviar_mensaje(mensaje):
    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": "eres un asistente virtual personal"},
            {"role": "user", "content": mensaje},
        ]
    )
    return response.choices[0].message.content

mensaje = "de la lista cuales es el mejor para algoritmos geneticos"
respuesta = enviar_mensaje(mensaje)
print(respuesta)