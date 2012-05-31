CFLAGS=
LDFLAGS=

SRC = mksocket.c leerEscribir.c mkconnect.c usage.c ioutils.c

OBJ = $(SRC:.c=.o)

OUT = ../lib/libutilidades.a

all: $(OUT)

../lib:
	mkdir ../lib

${OUT}: $(OBJ) ../lib
	ar rcs $@ $(OBJ)

clean:
	rm -f $(OBJ) $(OUT) 