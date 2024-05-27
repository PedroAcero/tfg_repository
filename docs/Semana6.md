# Semana 13/05/2024  

Continuando con [la semana anterior](./Semana5.md), se va a integrar la comunicación serie en el entorno de trabajo de _Zenoh_.  

***→ Objetivo:*** Comunicación vía puerto serie de dispositivos a través de _Zenoh_.  



Problemas con las comunicación serie en Zenoh --> comunidad de Zenoh me ayudaron a resolverlo
colcon vs cargo --> añadir argumentos 


    docker run -v /var/run/dbus/:/var/run/dbus/:z -it --name zenoh_container_sinhost1 --device=/dev/ttyUSB0 --cap-add=SYS_ADMIN --cap-add=NET_ADMIN --privileged ros_prueba:latest /bin/bash  

    docker run -v /var/run/dbus/:/var/run/dbus/:z -it --name zenoh_container_sinhost --device=/dev/ttyUSB1 --cap-add=SYS_ADMIN --cap-add=NET_ADMIN --privileged ros_prueba:latest /bin/bash  

    docker exec -it zenoh_container_sinhost /bin/bash  

    zenoh-bridge-ros2dds -e "serial//dev/ttyUSB1#baudrate=57600"  

    
