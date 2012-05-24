/* $Id: clienteNoBloqueante.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <utilidades.h>

#define BLOQUE_SIZE 512

int
main(int argc, char *argv[]) {

  int s;
  long val;

  if (argc != 2) {
    usage(argv[0],"socketname");
  }

  s = mksocketcliente();

  if (s < 0) {
    fprintf(stderr, "No se pudo crear un socket %d %s\n", 
	    errno, strerror(errno));
    exit(1);
  }

  if (mkconnect(s, argv[1]) < 0) {
    fprintf(stderr, "No se pudo conectar al socket %d %s\n", 
	    errno, strerror(errno));
    exit(1);
  }

  if (establecerDescriptorNoBloqueante(0) < 0) { 
    fprintf(stderr, "Error estableciendo descriptor no bloqueante %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }

  if (establecerDescriptorNoBloqueante(s) < 0) { 
    fprintf(stderr, "Error estableciendo descriptor no bloqueante %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }

  while (1) {

    if (leerEscribirNoBloqueante(0, s) < 0) { 
      fprintf(stderr, "Error en la lectura: %d %s\n",
	      errno, strerror(errno));
      exit(1);
    }

    if (leerEscribirNoBloqueante(s, 1) < 0) { 
      fprintf(stderr, "Error en la lectura: %d %s\n",
	      errno, strerror(errno));
      exit(1);
    }
  }
  
  exit(0);
  return 0;
}
