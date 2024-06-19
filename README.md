# Introducción a Zenoh 
  
Zenoh es un middleware que se encarga de conectar y comunicar diversos entornos distribuidos con diferentes topologías de red. Destaca por algunas de sus características, como su eficiencia, escalabilidad y flexibilidad diversas aplicaciones IoT.    

  
El objetivo de este estudio es comparar y mejorar la comunicación entre sistemas en un entorno de ROS2. ROS cuenta con un middleware llamado DDS (Data Distribution Service) que se caracteriza por una baja latencia con baja pérdida de mensajes, pero con un alto ancho de banda. Además, DDS utiliza un sistema de transporte UDP (User Data Protocol) que se utiliza para enviar datos a diferentes destinatarios al mismo tiempo. Sin embargo, esto requiere que todos los nodos deben ecnontrarse, conocer la topología de la red, para establecer la conexión. Este proceso, que se llama *Discovery*, puede hacer más ineficiente la comunicación. En cambio, Zenoh es un sistema descentralizado que evita estos problemas de DDS.  
  
 ## Registro semanal 

 * [Semana 1](docs/Semana1.md): Fundamentos teóricos y pruebas básicas con Zenoh
 * [Semana 2](docs/Semana2.md): Preparando el entorno de simulación con Docker
 * [Semana 3](docs/Semana3.md): Comunicación de contenedores a través de la red local
 * [Semana 4](docs/Semana4.md): Comunicación de contenedores a través de Bluetooth
 * [Semana 5](docs/Semana5.md): Integración con diferentes tecnologías de comunicación
 * [Semana 6](docs/Semana6.md): Integración de comunicación serial en el entorno de Zenoh
 * [Semana 7](docs/Semana7.md): Análisis de resultados teóricos
