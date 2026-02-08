### Level00

```
ls -la
ls  -l  /rofs/usr/sbin/  |  grep flag 
find  /  -user  level01  2>/dev/null;    flag00
```` 
find  :  busca en la raíz del sistema
-user  level01 : archivos propiedad usuario level01
2>/dev/null  :  rechaza errores de permission denied

Con flag00 me salio archivo de texto que es jhon

```
/usr/sbin/john
/rofs/usr/sbin/john
cat /usr/sbin/john : cdiiddwpgswtgt
Buscar archivos sospechosos
grep  -R  “password”  / 2>/dev/null;   “level01”
```
Criptoanálisis
Para detectar o inferir la codificacio se necesita 
Acceso a lo s bytes 
```
echo  -n  “texto”  |  hexdump  -C 
Salida : 
	00000000  74 65 78 74 6f                                	|texto|
00000005
```
son válidos en ASCII, UTF-8, ISO-8859-1


Deducción de la salida : 
Cada bytes esta entre 0x61..0x7a o entre 97..122; Letras minusculas
No hay UTF-8, no hay binario, no hay encoding extraño.
Hipotesis :
solo letras, todas válidas, pero sin sentido
probable cifrado por sustitución o desplazamiento. Cifrado Cesar ROT.

BASHCODE TO ROT Decipher (Brute force on Ceasar)
for i in {1..25};  → Crea una variable i que se irá cambiando de valor del 1 al 25.
do, done → Marcan dónde empieza y termina el bloque de comando que se ejecutará en cada vuelta.
echo -n “ROT$i:  ”; → Imprime por pantalla en qué numero de rotación estamos.
Printf con seq 97 122,  generan el abecedario.
seq 97 122 genera una lista de número del 97 al 122.
printf  ‘\\%03o’ → Convierte los números a formato octal para que lo entienda printf;
printf  %b → Toma estos códigos octales y los convierte de nuevo a letras creando dinámicamente la cadena a-z.
seq $((947 + i))  122 → Empieza el alfabeto en la letra desplazada, si i = 3, empieza en 100 (d) hasta 122 (z).
seq  97 $((96 + 1)) → Genera las letras que quedaron atrás para ponerlas al final, si i = 3,  genera de la 97 (a) a la 99 (c).
Resultado seria, con i = 3 : defghijklmnopqrstuvwxyzabc


Commando final : 

```
for i in {1..25}; do    echo -n "ROT$i: ";   echo "cdiiddwpgswtgt" | tr $(printf %b $(printf '\\%03o' $(seq 97 122))) $(printf %b $(printf '\\%03o' $(seq $((97+i)) 122; seq 97 $((96+i))))); done

su flag00  then getflag
```

