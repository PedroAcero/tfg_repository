 # Semana 1/04/2024

En esta tercera semana de trabajo se busca corregir algunos detalles respecto a los contenedores realizados la semana anterior, así como comprobar operabilidad de dos sistemas físicos diferentes mediante _Zenoh_.  

***→ Objetivo:*** Mejora de las capacidades de los contenedores _Docker_ para su integración con _Zenoh_.  
***→ Objetivo:*** Establecer comunicación de dos dispositivos diferentes para evaluar la eficacia de _Zenoh_ como herramienta de estudio.  

Para conseguir estos objetivos, lo primero fue solucionar algunos de los problemas que aparecieron la semana anterior. Con respecto al _sourcing_ de ROS que se pretendía hacer desde un _entrypoint_, se ha optado por **prescindir del entrypoint**, y realizar todas las acciones necesarias para configurar el entorno dentro del mismo contenedor, simplificando así su construcción desde el [Dockerfile](../docker/Dockerfile).  

A continuación, se busca conseguir el segundo objetivo: comunicar dos ordenadores portátiles diferentes a través de _Zenoh_, haciendo uso de los contenedores que se han preparado las anteriores semanas de trabajo. En el **primer intento**, se conectaron ambos ordenadores dentro de la misma red local, y se siguieron las instrucciones de prueba de la [web de _Zenoh_](https://github.com/eclipse-zenoh/zenoh-plugin-ros2dds) para comunicar dos dispositivos:  

En uno de los ordenadores (el cliente), se lanza el bridge:

    zenoh-bridge-ros2dds  

En el otro ordenador (el host), se lanza el bridge con la siguiente configuración:  

    zenoh-bridge-ros2dds -e tcp/<robot-ip>:7447  

Con esta configuración, se fija un _endpoint_ para que el sistema host pueda establecer conexión con otras instancias de _Zenoh_. Para ello, _Zenoh_ ha configurado el puerto 7447 para los servicios del bridge de _Zenoh_, por lo que solo es necesario conocer la dirección IP del dispositivo con el que se quiere establecer una conexión. Gracias a la herramienta `ifconfig`, explicada en la [Semana 1](./Semana1.md), se obtiene la dirección IP del portátil dentro de la red de internet. A pesar de todas estas comprobaciones, **no se consiguió** establecer conexión entre ambos pordenadores portátiles.  

La explicación de esto es que los contenedores de Docker, sin las configuraciones necesarias, se asignan una dirección de **IP privada** dentro de una red virtual que crea Docker. Para poder usar _Zenoh_ se necesita conocer la dirección de IP pública del dispositivo al que se desea conectar.  

> [!NOTE]
> La red virtual de Docker asigna direcciones de IP virtuales (o subredes) dentro del rango: 172.17.0.0-16. Se puede acceder al contenedor de Docker a través de la red y subred tal y como se indica en [algunos sitios de internet](https://www.freecodecamp.org/espanol/news/como-obtener-la-direccion-ip-de-un-contenedor-docker-explicado-con-ejemplos/). Sin embargo, se ha optado por otra solución.  

La solución adoptada ha sido inspirada por la [web oficial de Docker](https://docs.docker.com/network/). La web facilita la infomración necesaria para comunicar diferentes contenedores de Docker. Se pueden utilizar redes personalizadas o ya definidas. Entre las ya definidas, se pueden encontrar tanto personalización completa de direcciones IP públicas, como el **uso de la red local** del ordenador. Esta última red es la que va a heredar el contenedor en la comprobación de _Zenoh_. De esta manera, el contenedor tendrá acceso a todas las interfaces de red del ordenador local, y usará la misma dirección IP.  

Con esto claro, se van a crear dos contenedores, uno en cada ordenador portátil, a partir del Dockerfile ya realizado en las anteriores semanas. La diferencia se encuentra en el argumento `--net host` para que el contenedor tenga acceso a la interfaz de red del ordenador local:  

    docker run -it --net host --name nombre_contenedor ros_prueba:latest /bin/bash  

Con esto se comrueba que efectivamente ahora **sí se consiguen** comunicar ambos ordenadores a través de _Zenoh_. También se comprueba con `ifconfig` que la dirección IP del contenedor es la misma dirección que el ordenador local. 

![Video test zenoh con wifi](images/zenoh_wifi.mp4)  

### Ordenador 1

* **Terminal 1:**  

        ros2 topic pub -r 1 topic_test std_msgs/msg/String "data: 'Hello World'"

* **Terminal 2:**

        zenoh-bridge-ros2dds -e tcp/<IP-address>:7447  

### Ordenador 2 

* **Terminal 1:**

        zenoh-bridge-ros2dds  

* **Terminal 2:**

        ros2 topic echo /topic_test

Durante el desarrollo de esta prueba se puede observar en las terminales de _Zenoh_ que se realiza el proceso de Discovery del otro dispositivo.
    

> [!NOTE]
> Configuración adicional para habilitar el multicast:
> 
>     sudo ip l set lo multicast on  
>
> La comprobación anterior también se realizó con direcciones MAC:
> 
>     docker network create -d macvlan --subnet 10.150.0.0/17 --gateway 10.150.0.1 -o parent=wlo1 mi_red_prueba
>     docker run -it --net mi_red_prueba --ip 10.150.0.11 --name cont_mac1 -p 80:80 ros_prueba:latest /bin/bash

## Próximas tareas  

1. Repetir el proceso anterior con otras tecnologías de comunicación diferentes a WiFi. Se ha propuesto empezar usando **Bluetooth** para comunicar dos dispositivos diferentes a través de _Zenoh_.

2. Familiarizarse con los archivos de configuración de _Zenoh_ para no tener que escribir todos los argumentos cada vez que se lanza el bridge.
