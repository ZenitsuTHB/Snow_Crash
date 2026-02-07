Level07 Command Injection via Environment Variable
Clasificación:
	CWE-78: OS Command Injection
	CWE-454: External Control of Critical State Data
strings  level06 
Funciones peligrosas detectadas : 
	getenv, system, asprintf, setresuid, setresgid
String sospechoso : 
	LOGNAME
	/bin/echo %s
Significa que el programa hace algo como : 
	setresgid(flagxx), setresuid(flagxx)
	user = getenv(“LOGNAME”);
	asprintf(&cmd, “/bin/echo %s”, user);
	system(cmd);
NB : no valida LOGNAME
Conclusion : 
El binario SUID utiliza getenv para leer la variable de entorno LOGNAME, la inserta sin validación en un comando construido con asprintf y ejecutado mediante system, lo que permite inyección de comandos y ejecución arbitraria como el usuario propietario del binario.
export LOGNAME=”; getflag”

