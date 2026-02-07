Level02 Explotación de tráfico de redes
ls  -la
	Level02.pcap
SCP (Secure copy protocol)
Una herramienta para transferir archivos entre computadoras a través de una red, utilizando ssh para cifrar los datos. Es el comando cp con superpoderes para viajar entre servidores.
scp -P [serv_port]  [serv_user]@[serv_ip]:/[path_to_file_to_copy]  ./[path_destiny]
Flags : 
-r : copiar archivos entero
-P : define puertos
-p : preserva los atributos del archivo (fecha de creación, permisos).
-C : comprime los datos durante el envío. (Archivos grandes en redes lentas)

Procedure:
Mira si hay algún texto legible escondido en el tráfico binario con el comando strings
	strings  [name_of_the_binary]
strings Te dice que hay tráfico de red, contraseña esta en texto plano.
Análisis de la salida : 
wwwbugs login:  Alguien intentó iniciar sesión con un usuario llamado wwwbugs.
Password: Se introdujo una contraseña inmediatamente después del intento de login.
Login incorrect: El primer intento falló.
Analisis del binario : 
Wireshark : entorno grafico
tshark; tcpdump :  terminal
Procedure : 
	sudo apt update & install tshark -y
Para ver los datos : 

Ver que protocolos hay 
tshark -r level02.pcap -q -z io,phs
-r : le dice a tshark que lea un archivo especifico en lugar de capturar un trafico en vivo.
-q : Modo silencioso evita que se imprima la información de cada paquete individual-
-z io, phs : Genera una estadística de jerarquía de protocolos.
Muestra un árbol con todos los protocolos detectados (Ethernet, IP, TCP, HTTP, etc.)
Ver conversaciones TCP
tshark -r level02.pcap -q -z conv,tcp
-z conv,tcp : solicita una tabla de conversaciones específicas de protocolo TCP.
Lista todas las conexiones establecidas, mostrando las IP y puerto de origen/destino, la cantidad de paquetes y los bytes transmitidos en cada flujo.
Ver payload legible
tshark -r level02.pcap -Y "tcp" -T fields -e tcp.payload
-Y “tcp” : Aplica un filtro de visualización para procesar solo paquetes TCP.
-T fields : Cambia el formato de salida para mostrar solo campos específicos en lugar del resumen estándar.
-e tcp.payload : Especifica el campo a extraer: la carga útil (los datos reales transportados) de cada segmento TCP.
Imprime por pantalla una lista de los datos de cada paquete TCP en formato hexadecimal, que se convertirán de hex a texto legible.
Extraer y Convertir payload a texto
tshark -r level02.pcap -Y "tcp" -T fields -e data | xxd -r -p
-e data : Extrae el campo de datos genérico.
| xxd -r -p : Toma la salida hex. De tshark y usa herramienta xxd para revertirla -r desde su formato plano -p a caracteres ASCII legibles. 
O por filtro
tshark -r level02.pcap -Y "tcp.port == 23" -T fields -e data | xxd -r -p 
-Y “tcp.port == 23” : filtra solo los datos que pasan por el puerto 23, que tradicionalmente corresponde a Telnet.
O todo TCP interactivo
tshark -r level02.pcap -Y "tcp.len > 0" -T fields -e data | xxd -r -p
-Y “tcp.len > 0” : filtra para excluir paquetes de control como SYN o ACK.
Análisis de las secuencias de letras con los hexadecimales para encontrar password
 su flag02  then getflag
