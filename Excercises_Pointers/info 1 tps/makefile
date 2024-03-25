 #MAKEFILE: deve haber un solo main por ejecutable
 EXEC   = ejercicio2.4           	# ejecutable
 objs   = ejercicio2.4.o            # objetos

 cc     = gcc            	# compilador
 CFLAGS = Wall -g -c -o0	# (-o optimisar)
 LDflag = -g -lm -L pathlib	# lm(math.h) L dinde esta la libreria


$(EXEC):$(objs)             # regla>>> SALIDA : DEPENDENCIAS      LINEA DE LINKEO
	$(CC)  $(LDFLAGS) $(objs) -o $@   	#TAB obligatorio. gcc -g hola.o -o $EXEC
%.0: %.c 					# regla>>> para cada archivo .o ejecuta un archive igual pero .c LINEA DE COMPILACION
	$(CC) $(CFLAGS) -o $@			    #TAB obligatorio. gcc -Wall -g -c -o0 hola.o -o $EXEC
clean:						# regla>>> LIMPIARR
	rm -f *o$(EXEC)*~
doxy:						# regla>>> DOCUMENTAR
	doxygen doxyfile	
all: $(EXEC) doxy
