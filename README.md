# Despertador de luz
Es un proyecto de despertador luminico con el modulo esp8266 de NodeMCU
Tengo alta paja para hacer este file pero sientanse libre de mejorar este codigo que solo es funcional.
Si conectan el modulo en el IDE de Arduino y abren el monitor serie, les va a decir que ip tiene el modulo
una vez conectado pueden entrar a ese ip con su navegador y van a poder seleccionar la hora en la que quieren despertarse. Cuando llegue esa hora se va a ir encendiendo la luz conectada a la pata (insertar el numero de pin que obviamente ya no me acuerdo cual es) utilizando PWM durante 15 minutos,luego la luz queda encendida. Ojo! tener en cuenta que el modulo tiene poca capacidad de entregar corriente por sus pines. Con un bc548 y un transistor de potencia pueden hacer una etapa que permita conectarle alguna tira led. No le pongan un rele porque se les va a pegar.
Bugs que me gustaria arreglar:
1. Mientras esta encendiendose no se puede acceder al modulo. Hay que esperar 15 minutos para apagar la luz. Estaria bueno poder apagarla cuando se nos cante.
2. La imagen. Mis conocimientos de html y css son extremadamentes basicos. mejorar esto seria un golazo.
3. Acceder desde fuera de la red local. Para esto hay que tocar la configuracion del router para permitir entradas externas. Si tienen Fibertel se puede acceder al router desconectandolo de internet y usado la clave y usuario que esta en la etiqueta del router.
4. Esta documentacion. Es una cagada porque tengo menos tiempo que un boson de Higgs.

Que lo disfruten y espero que podamos hacer de esto algo mas lindo. Saludos!
