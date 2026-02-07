Level09 Weak / Reversible Encoding (Logic Flaw)
Clasificación:
	CWE-327: Broken or Risky Cryptographic Algorithm
	CWE-640: Weak Obfuscation
strings level09
El binario implementa un algoritmo de transformación ASCII predecible y reversible, como protección. El archivo token contiene el resultado de esa transformación. Al comprender la lógica, es posible invertirla y recuperar el valor original esperado por el programa.
./levelxx aaaaaaaaaaaaaaaaa
	abcdefghijklmnopq
python3 -c 'data = open("token", "rb").read().strip(); print("".join(chr((b - i) % 256) for i, b in enumerate(data)))'
su flag09 then getflag
