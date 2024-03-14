# Introducción a Zenoh 
  
Zenoh es un middleware que se encarga de conectar y comunicar diversos entornos distribuidos con diferentes topologías de red. Destaca por algunas de sus características, como su eficiencia, escalabilidad y flexibilidad diversas aplicaciones IoT.    

  
El objetivo de este estudio es comparar y mejorar la comunicación entre sistemas en un entorno de ROS2. ROS cuenta con un middleware llamado DDS (Data Distribution Service) que se caracteriza por una baja latencia con baja pérdida de mensajes, pero con un alto ancho de banda. Además, DDS utiliza un sistema de transporte UDP (User Data Protocol) que se utiliza para enviar datos a diferentes destinatarios al mismo tiempo. Sin embargo, esto requiere que todos los nodos deben ecnontrarse, conocer la topología de la red, para establecer la conexión. Este proceso, que se llama *Discovery*, puede hacer más ineficiente la comunicación. En cambio, Zenoh es un sistema descentralizado que evita estos problemas de DDS.  
  
 ## Semana 11/03/2024
 
En estas primeras semanas de trabajo, tras investigar los fundamentos teóricos de Zenoh, se trabajó con el bridge desarrollado por *Eclipse Zenoh* (https://github.com/eclipse-zenoh/zenoh-plugin-ros2dds). También se ha empezado a configurar el entorno en el que se va a trabajar para estudiar las posibilidades de Zenoh: contenedores de Docker para simular sistemas diferentes, y configurar la forma en la que se comunican. 
