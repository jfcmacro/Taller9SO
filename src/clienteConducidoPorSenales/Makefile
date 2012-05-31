CFLAGS=-I../include
LDFLAGS=../lib/libutilidades.a

SRC=clienteConducidoPorSenales.c

OBJ=$(SRC:.c=.o)

TARGET=$(SRC:.c=)

all: $(TARGET)

$(OBJ): $(SRC)

$(TARGET): $(OBJ)
	$(CC) -o $@ $< $(LDFLAGS)

clean: 
	rm -f $(OBJ) $(TARGET)
