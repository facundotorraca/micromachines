# Documentaicon

En el siguiente archive documentaremos como se implemnto el proyecto Micromachines.
Con tal objetivo describiremos cada una de las partes del mismo.

## Server

Se encarga de sincronizar los diferentes hilos que formaran parte del servidor. Esta compuesto por:

### ThreadAcceptor

Se encarga de bindear el puerto y levantar el servidor para recibir los nuevos clients.

### ThreadPlayerLocator

Se encargar de unir al nuevo jugador a la partida o de agregar la nueva partida a la cola de espera.

### ThreadMatchStarter

Es el encargado de generear la nueva partida que se encuentra en la cola de esperas.

## Common

### Socket

Es el encargado de realizar las funciones relacionadas con el socket como el enviar y recibir.

### Protocol

Se encarga de manejar el protocolo definido para la correcta comunicacion entre el cliente y el servidor.
