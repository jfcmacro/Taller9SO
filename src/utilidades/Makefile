CFLAGS=--shared -fPIC
LDFLAGS=--shared

.phony: ../lib

all: ../lib/libutilidades.so

../lib: 
	mkdir ../lib

../lib/libutilidades.so: mksocket.o leerEscribir.o mkconnect.o usage.o ioutils.o ../lib
	gcc --shared -o $@ mksocket.o leerEscribir.o mkconnect.o usage.o ioutils.o

clean: 
	rm -f *.o