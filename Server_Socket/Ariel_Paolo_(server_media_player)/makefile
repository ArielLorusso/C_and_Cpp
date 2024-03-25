#	1) Compilar :
#
#   gcc -o server listfunc.c sock-lib.c main.c -L. -l fmodexL-4.44.30
#
#	2) Exportar Libreria :  
#
#   gedit /home/ariel/.bashrc
#   export LD_LIBRARY_PATH=home/ariel/Documentos/fmain/lib/fmodexL-4.44.30:$LD_LIBRARY_PATH
#
#
#	3) Ejecutar :
#   
#   ./server


FLAGS = -Wall -L. -l fmodexL-4.44.30
CC    = gcc
OBJS  = listfunc.o sock-lib.o main.o

rapido:
	$(CC) -o server listfunc.c sock-lib.c main.c $(FLAGS)

server: $(OBJS)
	$(CC) -o server $(OBJS) $(FLAGS)

listfunc.o: listfunc.c 
	$(CC) -c listfunc.c 

sock-lib.o: sock-lib.c
	$(CC) -c sock-lib.c

main.o: main.c
	$(CC) -c main.c


clean:
	rm listfunc.o
	rm sock-lib.o
	rm main.o
	rm server

