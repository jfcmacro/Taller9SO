/* $Id: servidor.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "utilities.h"

int
main(int argc, char *argv[]) {

  int s;
  fd_set readfds, execptfds;
  int nFds;
  int ns;

  if (argc != 2) {
    usage(argv[0]);
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

    FD_ZERO(&readfds);
    FD_ZERO(&execptfds);
    
    FD_SET(0, &readfds);
    FD_SET(ns, &readfds);
    FD_SET(0, &execptfds);
    FD_SET(ns, &execptfds);

    nFds = select(ns + 1, &readfds, NULL, &execptfds, NULL);

    if (nFds > 0) {
      if (leerEscribir(&readfds, 0, ns) < 0) {
	fprintf(stderr, "Error en la lectura: %d %s\n",
		errno, strerror(errno));
	exit(1);
      }
      
      if (leerEscribir(&readfds, ns, 1) < 0) {
	fprintf(stderr, "Error en la lectura: %d %s\n",
		errno, strerror(errno));
	exit(1);
      }

      if (validarError(&execptfds, 0) < 0) {
	fprintf(stderr, "Error en la lectura: %d %s\n",
		errno, strerror(errno));
	exit(1);
      }

      if (validarError(&execptfds, s) < 0) {
	fprintf(stderr, "Error en la lectura: %d %s\n",
		errno, strerror(errno));
	exit(1);
      }	
    }

  }
  
  exit(0);
  return 0;
}
