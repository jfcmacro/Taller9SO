/* $Id: servidorBloqueante.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <utilidades.h>

int
main(int argc, char *argv[]) {

  int s;
  int ns;

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
    
  while (1) {


    if (leerEscribir2(ns, 1) < 0) {
      fprintf(stderr, "Error en la lectura: %d %s\n",
	      errno, strerror(errno));
      exit(1);
    }

    if (leerEscribir2(0, ns) < 0) {
      fprintf(stderr, "Error en la lectura: %d %s\n",
	      errno, strerror(errno));
      exit(1);
    }

  }
  
  exit(0);
  return 0;
}
