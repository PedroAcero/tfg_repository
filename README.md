# Introducción a Zenoh 
  
Zenoh es un middleware que se encarga de conectar y comunicar diversos entornos distribuidos con diferentes topologías de red. Destaca por algunas de sus características, como su eficiencia, escalabilidad y flexibilidad diversas aplicaciones IoT.    

  
El objetivo de este estudio es comparar y mejorar la comunicación entre sistemas en un entorno de ROS2. ROS cuenta con un middleware llamado DDS (Data Distribution Service) que se caracteriza por una baja latencia con baja pérdida de mensajes, pero con un alto ancho de banda. Además, DDS utiliza un sistema de transporte UDP (User Data Protocol) que se utiliza para enviar datos a diferentes destinatarios al mismo tiempo. Sin embargo, esto requiere que todos los nodos deben ecnontrarse, conocer la topología de la red, para establecer la conexión. Este proceso, que se llama *Discovery*, puede hacer más ineficiente la comunicación. En cambio, Zenoh es un sistema descentralizado que evita estos problemas de DDS.  
  
 ## Semana 11/03/2024
 
En estas primeras semanas de trabajo, tras investigar los fundamentos teóricos de Zenoh, se trabajó con el bridge desarrollado por *Eclipse Zenoh* (https://github.com/eclipse-zenoh/zenoh-plugin-ros2dds). También se ha empezado a configurar el entorno en el que se va a trabajar para estudiar las posibilidades de Zenoh: contenedores de Docker para simular sistemas diferentes, y configurar la forma en la que se comunican. 


**En primer lugar**, se realizó una prueba con el bridge de forma local en el ordenador. Este bridge permite la comunicación entre dos nodos de ROS2 con dominios diferentes, al igual que DDS. Sin embargo, es necesario comprender en profundidad este proceso para evaluar las ventajas o desventajas que presenta Zenoh en comparación con DDS.  
Como parte de la prueba, se verificó la comunicación entre dos nodos básicos con distintos ROS_DOMAIN_IDs en terminales separadas:  

    ROS_DOMAIN_ID=1 ros2 topic pub -r 1 prueba std_msgs/msg/String "data: 'Hello World'"    
    
    ros2 topic list  

Con esto se observa que el topic "/prueba" no aparece en la lista de de topics. Para poder visualizarlo, y ver su contenido, debe incluirse el dominio en el que se está trabajando:  

    ROS_DOMAIN_ID=1 ros2 topic list  



Además, se utilizó el paquete *net-tools* para verificar cómo los nodos de ROS enrutan la información. Al introducir el siguiente comando en una nueva terminal:  

    ifconfig  

Se pudo obtener información sobre las interfaces de red del sistema. Del mismo modo, al ejecutar  

    ping ip6-loopback  

se confirma que a información de ROS2 que se publica a través del tema se enruta a través de la **dirección de loopback 127.0.0.1**.  
  
---

La siguiente prueba tiene como objetivo familiarizarse con el plugin de Zenoh, que incluye un bridge diseñado para posibilitar la comunicación entre nodos de ROS a través de Zenoh.  

En una ventana de la terminal, se ejecuta el siguiente comando para publicar un mensaje en el tema "prueba" con un intervalo de 1 segundo:  

    ROS_DOMAIN_ID=1 ros2 topic pub -r 1 prueba std_msgs/msg/String "data: 'Hello World'"  

Y en otra pestaña de la misma ventana lanzamos Zenoh con una serie de argumentos:  

    ros2 run zenoh_bridge_ros2dds zenoh_bridge_ros2dds -d 1 -m peer -n /prueba-1  

El bridge puede contener una serie de argumentos que configuran rápidamente el nodo de Zenoh sin necesidad de un archivo de configuración. El significado de los argumentos utilizados en el ejemplo son los siguientes:  

* **-d:** Establece el valor del dominio de ROS_DOMAIN_ID en 1 para que coincida con nuestro publicación en /prueba.
* **-m:** Define el modo de sesión de Zenoh. Puede ser "peer" o "client".
* **-n:** Especifica el namespace que se agrega a todos los topics descubiertos por Zenoh.  

La salida por pantalla del nodo de Zenoh proporciona información relevante para comprender lo que está ocurriendo. Por ejemplo, muestra la dirección IP a través de la cual se puede acceder a Zenoh:

`Zenoh can be reached at: tcp/172.26.211.248:33479`    

Esto indica que Zenoh puede ser accedido mediante la dirección TCP especificada en el puerto 33479. También proporciona otras direcciones, como la dirección IP multicast.  
Además, se observa el proceso de descubrimiento de los elementos que conforman la red. En este caso, Zenoh ha descubierto tres elementos en la red con ROS_DOMAIN_ID = 1: */parameter_events*, */prueba* y */rosout*. El nodo de Zenoh, tras este proceso, que se conoce como *Discovery* de los topics, crea una red espejo aplicando el namespace indicado:  

`/prueba-1/parameter_events`  
`/prueba-1/prueba`  
`/prueba-1/rosout`  

Se observa que cuando se realiza una suscripción al tema /prueba, a través de:  

    ROS_DOMAIN_ID=1 ros2 topic echo /prueba-1/prueba  
    
El nodo de Zenoh también descubre a ese nodo suscriptor dentro de su red.  

Como prueba adicional, al desconectar el wifi del ordenador, Zenoh deja de funcionar. Esto se debe a que Zenoh utiliza la interfaz de red *wlo1* de la red inalámbrica del sistema, con la **dirección IP 172.26.211.248**, como se puede ver a través del comando *ifconfig* de la misma manera que en la prueba anterior.  

***

Finalmente, se plantea preparar el entorno de pruebas para Zenoh la próxima semana. Se trabajará con dos contenedores Docker de la misma imagen, que incluyen ROS2 Humble y el bridge de Zenoh, así como las herramientas necesarias para obtener la información requerida (como ifconfig y ping). Se trabajará con Docker para simular la comunicación entre dos sistemas independientes entre sí.
