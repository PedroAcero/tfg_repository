FROM osrf/ros:humble-desktop

# Instalación de zenoh bridge
RUN apt-get update && apt-get install -y ros-humble-rmw-cyclonedds-cpp curl
RUN apt-get install llvm-dev libclang-dev -y

WORKDIR /root
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | bash -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

RUN git clone https://github.com/eclipse-zenoh/zenoh-plugin-ros2dds.git
WORKDIR /root/zenoh-plugin-ros2dds
RUN cargo build --release
ENV PATH="/root/zenoh-plugin-ros2dds/target/release:${PATH}"

RUN echo 'export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp' >> /root/.bashrc
RUN echo 'export ROS_LOCALHOST_ONLY=1' >> /root/.bashrc

# Copia del entrypoint
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Herramientas necesarias
RUN apt update && \
    apt-get install -y net-tools iputils-ping iproute2

# Script de configuración del entorno
COPY setup_environment.sh /setup_environment.sh
RUN chmod +x /setup_environment.sh

# Configuración del entrypoint
ENTRYPOINT ["/entrypoint.sh"]
CMD ["/bin/bash", "-c", "/setup_environment.sh && exec bash"]
