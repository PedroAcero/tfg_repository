# Comparativa de distintos sistemas de comunicación

El objeto de estudio de este *Trabajo de Fin de Grado* será **comparar los distintos sistemas de comunicación** en un contexto
de *drones*, las ventajas y desventajas que presentan respecto a los demás en la teoría, para luego comprobar los resultados
en la práctica.


|  | WiFi |  Bluetooth  |  ZigBee/Xbee  | 
| --- | --- | --- |--- |
| `Cobertura (alcance)` | Alto | Bajo | Medio-Alto | 
| `Consumo` | Alto | Bajo | Bajo |
| `Transferencia de datos` | Media | Alta | Baja |
| `Seguridad de transporte` | Bajo | Bajo | Alto |
| `Frecuencia` | 2.4 GHz | 2.4 GHz | 2.4 GHz |


Como se observa en la tabla, **Wifi**, que es el sistema más usado, presenta un buen alcance y una decente transferencia de datos 
(aunque depende de la tecnología utilizada); sin embargo, su principal desventaja es su elevado consumo y precio, y la posible 
pérdida de datos debido al ruido, a los obstáculos, etc.

Los sistemas que usan **BLuetooth** sacrifican su alcance y la seguridad en el transporte de datos, a cambio de obtener un consumo bajo y una
transferencia de datos elevada.

Los sistemas que usan **ZigBee** parece que son una buena alternativa a los sistemas que usan Wifi, porque corrigen sus desventajas (consumo 
y la seguridad de datos) con la diferencia que tiene un poco menos alcance con respecto a WiFi.

También se deberían tener en cuenta otras **alternativas**, como son GSM/GPRS y LoRa/LoRaWAN, ya que garantizan un gran alcance y una buena 
seguridad de transporte con un consumo muy bajo, en caso de no necesitar una transferencia de datos ni una frecuencia muy elevada.
