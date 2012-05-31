CFLAGS=-I../include
LDFLAGS=../lib/libutilidades.a -lpthread

SRC=servidorBloqueante2.c

OBJ=$(SRC:.c=.o)

TARGET=$(SRC:.c=)

all: $(TARGET)

$(OBJ): $(SRC)

$(TARGET): $(OBJ)
	$(CC) -o $@ $< $(LDFLAGS)

clean: 
	rm -f $(OBJ) $(TARGET)

