/* $Id: servidorBloqueante2.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include <utilidades.h>

struct descriptores {
  int in;
  int out;
};

typedef struct descriptores descriptores;
typedef struct descriptores* pdescriptores;

void*
hiloDeTrabajo(void *arg) {
  descriptores des = *((pdescriptores) arg);
  
  while (1) {
    if (leerEscribir2(des.in, des.out) < 0)  {
      fprintf(stderr, "Error en la lectura: %d %s\n",
	      errno, strerror(errno));
      exit(1);
    }
  }
  return (void *) 0;
}
 
int
main(int argc, char *argv[]) {

  int s;
  int ns;
  pdescriptores des = (pdescriptores) NULL;
  pthread_t id;

  if (argc != 2) {
    usage(argv[0], "namesocket");
  }

  s = mksocket(argv[1]);
  
  if (s < 0) {
    fprintf(stderr, "No se pudo crear un socket %d %s\n", 
	    errno, strerror(errno));
    exit(1);
  }
  
  listen(s, 5);

  if ((ns = accept(s, NULL, NULL)) < 0) {
    fprintf(stderr, "No se pudo aceptar una conexion %d %s\n", 
	    errno, strerror(errno));
    exit(1);
  }
 
  des = (pdescriptores) malloc(sizeof(descriptores));

  if (!des) {
    fprintf(stderr, "Error al solicitar memoria: %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }

  des->in = ns;
  des->out = 1;

  if (pthread_create(&id, NULL, hiloDeTrabajo, (void *) des) < 0)  {
    fprintf(stderr, "Al crear hilo de trabajo: %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }

  while (1) {
    
    if (leerEscribir2(0, ns) < 0) {
      fprintf(stderr, "Error en la lectura: %d %s\n",
	      errno, strerror(errno));
      exit(1);
    }
  }
  
  exit(0);
  return 0;
}
