# Micromachines

Micromachines es un juego online de carreras. Por un lado se debe levantar el servidor y por el otro se ejecutan
tantos clientes como jugadores.

## Requerimientos

- CMAKE
- SDL2
- LUA

## Compilacion

Micromachines usa [CMake](http://www.cmake.org) para soportar la compilacion multiplataforma. Los pasos basicos para compilarse son:

1. Descarge e instale [CMake](http://www.cmake.org) (Resources -> Download).

2. Dirigase al direcotirio raiz de micromachines y escriba:

```
mkdir build
cd build
```

3. Ejecute CMake:

```
cmake ..
```

4. Para compilar introduzca:

```
make
```

5. Ahora puede ejecutar el cliente y el servidor:

```
./micromachines-client
./micromachines-server
```

## Documentacion

La documentacion de la implementacion se encuentra en [GITHUB](https://github.com/facutorraca/Micromachines/blob/master/DOC.md)
