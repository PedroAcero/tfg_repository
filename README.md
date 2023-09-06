# Comparativa de distintos sistemas de comunicación

El objeto de estudio de este *Trabajo de Fin de Grado* será **comparar los distintos sistemas de comunicación** en un contexto
de *drones*, las ventajas y desventajas que presentan respecto a los demás en la teoría, para luego comprobar los resultados
en la práctica.


|  |  Radiofrecuencia [¹] | WiFi [²] |  Bluetooth [³] |  ZigBee/Xbee [⁴]  | Satélite [⁵] |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `Alcance` | Bajo | Alto | Bajo | Medio-Alto | Muy Alto |
| `Consumo` | Bajo | Alto | Bajo | Bajo | Bajo |
| `Latencia (transferencia de datos)` | Baja | Media | Baja | Alta | Alta
| `Seguridad de transporte` | Baja | Baja | Baja | Alta | Alta |
| `Frecuencia` | 2.4 GHz | 2.4 GHz | 2.4 GHz | 2.4 GHz | 868  MHz |


[¹] Los sistemas que usan **Radiofrecuencia** tienen una baja latencia y alta velocidad de datos, un control confiable del dron
y en tiempo real. A pesar de su buena penetración de obstáculos, es susceptible a ruido e interferencias, y el alcance se 
encuentra limitado por la línea de visión del piloto.

[²] Los sistemas con **Wifi** están ampliamente disponibles y son económicos en la mayoría de los casos. Presentan unas buenas 
características respecto al alcance y a la transferencia de datos (dependen de la tecnología usada), aunque sus principales 
desventajas son su elevado consumo, y la posible pérdida de datos debido al ruido, interferencias y obstáculos. Además, dependen 
de que trabajen en áreas con cobertura WiFi disponible.

[³] Los sistemas que usan **BLuetooth** sacrifican su alcance y la seguridad en el transporte de datos, a cambio de obtener un 
consumo bajo y una transferencia de datos elevada.

[⁴] Los sistemas que usan **ZigBee** parece que son una buena alternativa a los sistemas que usan Wifi, porque corrigen sus 
desventajas (consumo y la seguridad de datos) con la diferencia que tiene un poco menos alcance con respecto a WiFi.

[⁵] También se deberían tener en cuenta otras **alternativas por satélite**, como son GSM/GPRS y LoRa/LoRaWAN, ya que garantizan 
una conexión global sin límites, ininterrumpida. Tiene un gran alcance, un consumo muy bajo, y no depende de la cobrtura de la zona.
Son adecuados si no se precisa de una transferencia de datos ni de una frecuencia muy alta, además tener un elevado costo de hardware
y de servicio.



La selección del sistema de comunicación más adecuado dependerá de las condiciones y de la ubicación exacta de las misiones de los *drones*,
por lo que lo más seguro sería optar por una combinación de varias tecnologías.
