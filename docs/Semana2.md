# Semana 18/03/2024

En la segunda semana de trabajo, se preparó el entorno de simulación para Zenoh. Para ello, se optó por utilizar contenedores de Docker a modo de prueba, para familiarizarnos con el plugin.

***→ Objetivo:***  Simulación de dos elementos aislados que se comuniquen a través de la red local de Wifi gracias a Zenoh. Una vez finalizada la prueba, se puede extender el alcance de las próximas tareas para acercarnos a la aplicación real del proyecto, donde los elementos involucrados sean drones controlados a través de ordenadores.    

Para este propósito, se ha diseñado una imagen de Docker (link) que incluye los siguientes elementos:  

* **ROS2:** Se utiliza como base una imagen preconfigurada de ROS2 (osrf/ros:humble-desktop, link)
* **Zenoh:** Se añade el plugin de Zenoh (link) para tenerlo disponible en el contenedor
* **Configuración del entorno de desarrollo:** Configuramos el entorno de desarrollo instalando _Rust_, y contruyendo el plugin de Zenoh utilizando _cargo_. También se incluye la configuración de otras variables de entorno en el archivo _".bashrc"_ para optimizar el entorno de desarrollo. Por ejemplo, se restringen las conexiones al _host_ local para garantizar un aislamiento adecuado. 
* **Instalación de herramientas:** Se instalan herramientas de red necesarias, como _"net-tools"_ y _"iputils-ping"_
* **Instalación de dependencias** necesarias para el funcionamiento de todos los elementos anteriores  

Uno de los principales problemas que se encontraron a la hora de contruir una imagen adecuada fue al añadir el plugin de Zenoh. En primer lugar, se intentó la instalación binaria, como indican en el repositorio de GitHub (link), y de manera similar a como se hizo la semana pasada en el ordenador local. Sin embargo, la instalación de Zenoh falla debida (systemd)  


> [!NOTE]
> `systemd` es un conjunto de _daemons_ de administración de sistema, bibliotecas y herramientas utilizados por los sistemas operativos de Linux. `systemd` se encarga de coordinar el arranque del sistema, la gestión de servicios, el manejo de sesiones de usuario, la administración de módulos de kernel, el seguimiento de procesos, la gestión de logs (registros) y otras tareas relacionadas con la administración del sistema. Más información sobre systemd (link).

De esta manera, como  el contenedor de Docker no tiene kernel propio, sino que comparte kernel con el host de nuestro ordenador local, por lo que no tiene un sistema operativo completo. No tienen servicios de inicialización del sistema, entre los que se incluye systemd, necesario para la instación del plugin de Zenoh.  
Una posible solución encontrada fue en un repositorio que también instala Zenoh en su imagen de Docker (link). Se utiliza un `workaround` como recurso para completar la contrucción de la imagen. Sin embargo, esto se trata de una solución temporal, y no resuelve la causa subyaciente del problema, sino que solo se evita. Por ello, se tuvo que encontrar otra solución que resuelva el problema.  

Como solución final se encontró que la instalación binaria resuelve el problema con systemd. En la instalación por fuente que se estaba realizando previamente, el código fuente se compila en el sistema. Sin embargo, en la instalación binaria utiliza un paquete binario precompilado.  

Con esto, se consiguó construir la imagen de Docker (añadir y link) adecuada para la aplicación.  

<h2> Resultados </h2>  

+ Construcción de la imagen, comandos
+ Problemas con el entrypoint
+ Comprobación que funciona todo, pero se comunican internamente (siguiente semana)
