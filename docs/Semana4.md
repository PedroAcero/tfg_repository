# Semana 08/04/2024  

Home Assistant -> Docker compose  


En esta cuarta semana de trabajo, se ha propuesto utilizar Bluetooth como tecnología de comunicación. En las anteriores semanas se consiguió utilizar el sistema WiFi de los ordenadores para comunicarse con _Zenoh_. Esta semana se ha intentado realizar el mismo objetivo, pero usando el sistema de Bluetooth de los ordenadores locales.  

**→ Objetivo:** Comunicar dos ordenadores a través de _Zenoh_ utilizando Bluetooth.  

El primer problema que se encontró fue que el contenedor _Docker_ que tenemos no tenía las herramientas de Bluetooth incluidas. De esta manera, el primer paso fue actualizar el [Dockerfile](../docker/Dockerfile), actualizando la siguiente línea del archivo:  

    RUN apt update && \
    apt-get -y install net-tools iputils-ping iproute2 bluez  

Con esta instrucción, además de las herramientas que disponíamos en las anteriores semanas para facilitar interfaces relacionadas con WiFi (`net-tools`, `iputils-ping`, `iproute2`), se han añadido el paquete `bluez`, que instala en el ordenador herramientas relacionadas con el uso de Bluetooth, que van a facilitar el trabajo. Este paquete añade la interfaz de `bluetoothctl`, que facilita la conexión y desconexión de dispositivos a través de Bluetooth, entre otras configuraciones.  

Además, como se vio [la semana anterior](./Semana3.md), gracias al argumento `--net=host`, en teoría permite utilizar la pila de red del _host_, incluyendo los dispositivos de Bluetooth que utilice el ordenador local. Sin embargo, con esta configuración, el contenedor Docker **no tiene acceso** a los dispositivos de Bluetooth.  

(imagen)  

>[!Warning]  
>A través de buscar respuestas en foros donde personas comentan errores similares a este, finalmente se entendió el error que impedía utilizar el dispositivo de Bluetooth en el contenedor del Docker. Al final de [este foro](https://www.reddit.com/r/archlinux/comments/x8vu8o/bluetoothctl_no_default_controller_available/), plantean varias respuestas, donde destacan:
>
>    /etc/init.d/dbus start
>    /usr/lib/bluetooth/bluetoothd --debug &
>
>Estas instrucciones que se introducen en el contenedor no solucionan directamente el problema, pero muestran la necesidad de realizar varias acciones dentro del contenedor. La primera instrucción se encarga de iniciar el sistema de comunicación entre procesos (`d-bus`) para que intercambien información de manera eficiente y flexible. Tras iniciar este sistema, se inicia el servicio de Bluetooth.  

Tras una investigación más profunda, se consiguió resolver el problema, añadiento otras facilidades. El comando para crear el contenedor Docker, finalmente queda así:  

    docker run -v /var/run/dbus/:/var/run/dbus/:z -it --name contenedor_docker --cap-add=SYS_ADMIN --cap-add=NET_ADMIN --net=host --privileged ros_prueba:latest /bin/bash

Los argumentos utilizados en la creación del contenedor son los siguientes:  

* `-v /var/run/dbus/:/var/run/dbus/:z`: Permite montar un volumen en el contenedor. /var/run/dbus/ es el directorio del sistema de archivos en el host que contiene los sockets de comunicación de D-Bus.
* `--cap-add=SYS_ADMIN`: Esta opción agrega la capacidad al contenedor de realizar diversas operaciones del sistema, como la configuración de interfaces de red.
* `--cap-add=NET_ADMIN`: Similar a SYS_ADMIN, pero para operaciones de red, como la configuración de interfaces de red y el enrutamiento.
* `--privileged`: Añade privilegios adicionales al contenedor, permitiendo obtener acceso a todas las capacidades disponibles en el host.  

Con esta configuración, **sí se consigue** utilizar Bluetooth en el contenedor, e incluso establecer conexión con otros dispositivos:  

(Imagen)

Paralelamente a esto, se ha propuesto investigar el uso del software [Home Assistant](https://www.home-assistant.io/). Esta plataforma se utiliza principalmente para domotizar el hogar. Sin embargo, como exponen en [un blog](https://www.homeautomationguy.io/blog/home-assistant-tips/installing-docker-home-assistant-and-portainer-on-ubuntu-linux) y [una serie de vídeos](https://www.youtube.com/playlist?list=PL4ed4sZb-R_8dJmakzfBywx1zL9HrFEOy), también se puede utilizar para automatizar las capacidades de varios sistemas que utilicen contendores Docker.  

La herramienta principal que utiliza es [Docker Compose](https://docs.docker.com/compose/), una herramienta que te permite gestionar varios contenedores Docker a la vez. Uno de los contenedores que facilita _Home Assistant_ es el contenedor [Portainer](https://docs.portainer.io/start/install-ce/server/docker/linux), que ofrece una interfaz web para el uso de _Docker Compose_.  

Una vez seguidas las instrucciones descritas en el blog y el los vídeos sobre la instalación de _Home Assistant_ y las herramientas necesarias para su uso, se consiguió la interfaz con la que manejar de manera sencilla varios contenedores, incluyendo el contenedor que incluye _Zenoh_. Esto en el futuro quizás pueda aprovecharse para iniciar de manera automática los contenedores necesarios para el uso de _Zenoh_ en los ordenadores de a bordo de los drones, y la configuración de los mismos a través de la web.  

(Imagen)

# Próximas tareas

 1. Uso de _Zenoh_ para comunicar dos dispositivos físicos diferentes a través de Bluetooth
  
 2. Implementación en _Home Assistant_ o _Docker Compose_ de lo necesario para gestionar contenedores. 
