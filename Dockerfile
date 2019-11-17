FROM gcc
RUN apt-get update
RUN apt-get -y install cmake
COPY configs.json /usr/micromachines-server/configs.json
COPY CMakeLists-Server.txt /usr/micromachines-server/CMakeLists.txt
COPY ./src /usr/micromachines-server/src
COPY ./libs /usr/micromachines-server/libs
COPY ./maps /usr/micromachines-server/maps
WORKDIR /usr/micromachines-server
RUN mkdir build
WORKDIR /usr/micromachines-server/build
RUN cmake ..
RUN make micromachines-server
CMD ["./micromachines-server"]
EXPOSE 7777 7777