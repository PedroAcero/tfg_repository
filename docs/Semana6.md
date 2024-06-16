# Semana 13/05/2024  

Continuando con [la semana anterior](./Semana5.md), se va a integrar la comunicación serie en el entorno de trabajo de _Zenoh_.  

***→ Objetivo:*** Comunicación vía puerto serie de dispositivos a través de _Zenoh_.  

En un primer intento, se intentó comunicar los contenedores de la [semana 4](./Semana4.md), que utilizan las interfaces del ordenador local. Sin embargo, se comprobó que no se comunicaban a través de las antenas, sino a través de Wifi (entre dos ordenadores diferentes) o de *loopback* (si se utiliza el mismo ordenador), en lugar de hacerlo a través de las antenas. Para comprobar esto, fue muy importante el uso de la herramienta `tcpdump`.  
Por ello, se optó por crear otros dos contenedores sin las interfaces locales:  

    docker run -v /var/run/dbus/:/var/run/dbus/:z -it --name zenoh_container_sinhost --device=/dev/ttyUSB1 --cap-add=SYS_ADMIN --cap-add=NET_ADMIN --privileged ros_prueba:latest /bin/bash  

    docker run -v /var/run/dbus/:/var/run/dbus/:z -it --name zenoh_container_sinhost1 --device=/dev/ttyUSB0 --cap-add=SYS_ADMIN --cap-add=NET_ADMIN --privileged ros_prueba:latest /bin/bash  

Y se pueden crear instancias del mismo contenedor de la siguiente manera:  

     docker exec -it zenoh_container_sinhost /bin/bash  

>[!Note]  
>El orden en el que conectas los puertos USB en el ordenador sí importa. Independientemente del puerto físico que utilices en tu ordenador, el primero que conectes siempre será el USB0, el segundo el USB1 y así sucesivamente.  
Esto será importante tenerlo en cuenta sobre todo en pruebas de dos antenas en un ordenador, o entre dos ordenadores, donde se deberá utilizar los contenedores que tengan acceso al USB0.  

Con esta preparación, se llevó a cabo la siguiente prueba con la que se pretende una comunicación bidireccional entre las instancias de _Zenoh_:  

### zenoh_container_sinhost  

#### Terminal 1

     ros2 topic pub -r 1 prueba std_msgs/msg/String "data: 'Hello World'"

#### Terminal 2

    zenoh_bridge_ros2dds -e "serial//dev/ttyUSB1#baudrate=57600"  

### zenoh_container_sinhost1  

#### Terminal 1

    ros2 topic list

#### Terminal 2

    zenoh_bridge_ros2dds -e "serial//dev/ttyUSB0#baudrate=57600"  

Sin embargo, se recibe el siguiente error:  

`[2024-05-22T14:31:57Z INFO  zenoh_bridge_ros2dds] zenoh-bridge-ros2dds v0.11.0-dev-24-gd5d6a95 built with rustc 1.72.0 (5680fa18f 2023-08-23) [2024-05-22T14:31:57Z INFO  zenoh::net::runtime] Using PID: c57be5548da4c3c170891f3f32545ca5 [2024-05-22T14:31:57Z ERROR zenoh::net::runtime::orchestrator] Unable to open listener serial//dev/ttyUSB0#baudrate=57600: Unsupported protocol: serial. at /home/pedro/.cargo/git/checkouts/zenoh-cc237f2570fab813/b669489/io/zenoh-link/src/lib.rs:140. thread 'main' panicked at 'calledResult::unwrap()on anErrvalue: Unsupported protocol: serial. at /home/pedro/.cargo/git/checkouts/zenoh-cc237f2570fab813/b669489/io/zenoh-link/src/lib.rs:140.', zenoh-bridge-ros2dds/src/main.rs:77:62 note: run withRUST_BACKTRACE=1environment variable to display a backtrace Aborted (core dumped)`  

Esta prueba con el problema existente se explica en el [_issue_](https://github.com/eclipse-zenoh/roadmap/discussions/137) que se creó en el repositorio de _Zenoh_. Se buscó ayuda tanto en la sección de _issues_ del repositorio ya mencionado, como en [el canal de Discord](https://discord.com/invite/vSDSpqnbkm). En el canal de _Discord_ resolvieron muy rápido el problema, y de manera precisa.  

Lo primero, en el [Dockerfile](../docker/Dockerfile) faltaba añadir el siguiente argumento:  

    RUN cargo build --release --features zenoh/transport_serial  

De esta manera, se permite la comunicación serie en el entorno de _Zenoh_.  

Lo segundo que faltaba es establecer uno de los contenedores como _listener_ a través del comando `-l`La idea inicial era establecer ambos contenedores como _endpoints_ del otro contenedor a través del comando `-e` para
que la comunicación sea bidireccional. Pero realmente, aunque se establezca uno de los contenedores como _listener_, este no deja de poder publicar información para el otro contenedor.  

Con todo ello, la prueba de comunicación quedaría así:  

### zenoh_container_sinhost  

#### Terminal 1

     ros2 topic pub -r 1 prueba std_msgs/msg/String "data: 'Hello World'"

#### Terminal 2

    zenoh_bridge_ros2dds -e "serial//dev/ttyUSB1#baudrate=57600"  

### zenoh_container_sinhost1  

#### Terminal 1

    ros2 topic echo /prueba

#### Terminal 2

    zenoh_bridge_ros2dds -l "serial//dev/ttyUSB0#baudrate=57600"  

Y podemos comprobar que, efectivamente se pueden comunicar dos contenedores a través de _Zenoh_.   

imagen  

## Próximas tareas

1. Comprobar la eficiencia del transporte de datos con _Zenoh_ para diferentes tipos de mensaje, con diferentes tamaños y frecuencias.
2. Buscar caso práctico para [aerostack2](https://github.com/aerostack2/aerostack2).
