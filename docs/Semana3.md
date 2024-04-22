 # Semana 1/04/2024

docker build -t ros_prueba -f Imagen.Dockerfile . --progress=plain  

docker run -it --name contenedor_zenoh1  ros_prueba:latest /bin/bash  

docker start contenedor_zenoh1  

docker exec -it contenedor_zenoh1 /bin/bash  

source "/opt/ros/humble/setup.bash"  

docker network create -d macvlan --subnet 10.150.0.0/17 --gateway 10.150.0.1 -o parent=wlo1 mi_red_prueba  

docker run -dit --net mi_red_prueba --ip 10.150.0.11 --name cont_mac1 -p 80:80 ros_prueba:latest /bin/bash  

sudo docker run -v /var/run/dbus/:/var/run/dbus/:z -it --name contenedor_wifi4 --cap-add=SYS_ADMIN --cap-add=NET_ADMIN --net=host --privileged ros_prueba:latest /bin/bash
