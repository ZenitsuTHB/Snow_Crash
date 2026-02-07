Level01 Explotación de cifrados de contraseñas no seguros

Búsqueda por nombre de archivos, no abre los archivos para ver lo que hay dentro
	find / -name "*flag01*" 2>/dev/null
Esto buscará en todo el disco cualquier archivo que se llame flag01, ignorando los errores de permisos denegados.
Busca dentro de los archivos
	grep / -R “flag” /etc  2>/dev/null
Busca la palabra flag dentro de todos los archivos del directorio /etc. Entra en subdirectorios y lee todos los archivos.

Porque el archivo etc ?
El archivo /etc/passwd es un archivo de texto plano que contiene una lista de las cuentas de usuario en un sistema operativo basado en Unix o Linux. Es fundamental para la gestión de usuarios, ya que define quién puede acceder al sistema y con qué atributos básicos. 
Estructura del archivo
Cada línea del archivo representa a un usuario y se divide en siete campos separados por dos puntos (:) :
	usuario:x:UID:GID:comentario:directorio_home:shell
Nombre de usuario: El nombre utilizado para iniciar sesión.
Contraseña: Históricamente contenía la contraseña cifrada. Hoy en día, la mayoría de los sistemas modernos muestran una x, lo que indica que la contraseña está almacenada de forma segura en /etc/shadow.
ID de usuario (UID): El número de identificación único del usuario. El superusuario (root) siempre tiene el UID 0.
ID de grupo (GID): El número de identificación del grupo principal al que pertenece el usuario.
Información del usuario (Gecos): Campo opcional para el nombre completo o datos de contacto.
Directorio Home: La ruta de la carpeta personal del usuario (donde inicia sesión por defecto).
Shell: El programa que se ejecuta automáticamente al entrar (usualmente /bin/bash para usuarios estándar o /usr/sbin/nologin para cuentas de servicios del sistema). 

¿Por qué está en /etc/passwd y no en /etc/shadow?
Porque:
DES NO usa salt moderno
sistemas viejos guardaban hashes en /etc/passwd
Snow Crash simula un sistema antiguo
Password : 42hDRfypTqqnw

1- Identificar qué tipo de cifrado es. Hashid en unix system; Hashtype online
Resultado : 
Cifrado DES o 3DES
Longitud: 13 caracteres
Charset: ./0-9A-Za-z
Sin prefijo $1$, $5$, $6$
Esto encaja PERFECTO con:
DES crypt (Unix clásico)
Usado en Unix antiguos


2- que herramienta se necesita para extraer la verdadera contraseña.
John the ripper
john  --format=descrypt  hash.txt
john --wordlist=/usr/share/wordlists/rockyou.txt hash.txt
crypt("password", "42");
Hashcat
hashcat -m 1500 hash.txt /usr/share/wordlists/rockyou.txt
mkpasswd --method=des password
NB: rockyou.txt es el diccionario estándar en Linux (comúnmente en /usr/share/wordlists/ en Kali o Parrot).
Sudo apt update
Sudo apt intall john hashcat -y 
John –show hash.txt
su flag01  then getflag
