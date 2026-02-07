Level08 Path Traversal / Symlink Bypass (TOCTOU lógico)
Clasificación:
	CWE-22: Improper Limitation of a Pathname
	CWE-59: Improper Link Resolution Before File Access
strings  level06 
Funciones Importantes detectadas : 
	open, read, write, strstr, printf, exit
strstr sirve para buscar una subcadena dentro de otra
Conclusion : 
El programa NO compara rutas reales. Solo busca si el nombre contiene "token".
Cuando el programa hace strstr("/tmp/apple", "token"), el resultado es falso porque la palabra "token" no está en el nombre.
El programa permite el acceso y ejecuta open("/tmp/apple").
Como es un enlace simbólico, el sistema operativo abre el archivo original (/home/user/levelxx/token).
Como el binario es SUID flag08, tiene permisos para leerlo y te imprimirá el contenido en la pantalla.

ln -s token hackerfile
ln -s /home/user/levelxx/token /tmp/hackerfile
./levelxx /tmp/hackerfile
su flag08 then getflag
