# Micromachines

Micromachines es un juego online de carreras. Por un lado se debe levantar el servidor y por el otro se ejecutan
tantos clientes como jugadores.

## Librerías requeridas para compilar

- CMAKE
- SDL2
- LUA
- QT5
- FFMPEG

#### Instalación en Ubuntu:
```
sudo apt install build-essential libreadline-dev cmake libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev qtbase5-dev qtdeclarative5-dev libavutil-dev libswresample-dev libavformat-dev libavcodec-dev libswscale-dev   
```

#### Instalación de Lua:
```
$ mkdir lua_build
$ cd lua_build
$ curl -R -O http://www.lua.org/ftp/lua-5.3.4.tar.gz
$ tar -zxf lua-5.3.4.tar.gz
$ cd lua-5.3.4
$ make linux test
$ sudo make install
```

## Instalación del juego

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

5. Ahora desde la carpeta 'build' puede ejecutar el cliente y el servidor:

```
./micromachines-client
./micromachines-server
```

## Docker

Se implemento un Dockerfile para crear una imagen modificada a partir de la imagen gcc de Docker. En esta imagen correra el server

En la raiz del proyecto ejecutar:

```
docker build -t micromachines-server .

docker run -p 7777:7777 -it --rm --name my-micromachines-server micromachines-server
```

## Documentacion

###Manual Tecnico
https://www.overleaf.com/read/tqgbrjjhfhhc

###Manual de Usuario - Server
https://www.overleaf.com/read/nbyxnftwfbpp

###Manual de Usuario - Client
https://www.overleaf.com/read/nkgfnpdvqcfr

###Manual de Proyecto
https://www.overleaf.com/read/spmvnqqqjvcw



