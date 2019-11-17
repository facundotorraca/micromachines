# Micromachines

Micromachines es un juego online de carreras. Por un lado se debe levantar el servidor y por el otro se ejecutan
tantos clientes como jugadores.

## Requerimientos

- CMAKE
- SDL2
- LUA

## Compilacion

Micromachines usa [CMake](http://www.cmake.org) para soportar la compilacion multiplataforma. Los pasos basicos para compilarse son:

1. Descargue e instale [CMake](http://www.cmake.org) (Resources -> Download).

2. Diríjase al direcotirio raiz de Micromachines y escriba:

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

## Docker

Se implemento un Dockerfile para crear una imagen modificada a partir de la imagen gcc de Docker. En esta imagen correra el server

En la raiz del proyecto ejecutar:

```
docker build -t micromachines-server .

docker run -p 7777:7777 -it --rm --name my-micromachines-server micromachines-srver
```

## Documentacion

La documentacion de la implementacion se encuentra en [GITHUB](https://github.com/facutorraca/Micromachines/blob/master/DOC.md)
