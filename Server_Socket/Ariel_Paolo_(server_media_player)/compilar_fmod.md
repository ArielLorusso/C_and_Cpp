# Compilar: 
```sh
gcc -o test main.c -L. -l fmodexL-4.44.30
```

# Ejecutar: g
```sh
./test
```


# Exportar Libreria:  

 open BASH-RC folder:
```sh
gedit /home/ariel/.bashrc
```

 Add LD_PATH :
 ```sh
export LD_LIBRARY_PATH=home/ariel/Documentos/fmain/lib/fmodexL-4.44.30:$LD_LIBRARY_PATH
```






