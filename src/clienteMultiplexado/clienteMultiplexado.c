/* $Id: clienteMultiplexado.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
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
  fd_set readfds, execptfds;
  int nFds;

  if (argc != 2) {
    usage(argv[0], "namesocket");
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
    
  while (1) {

    FD_ZERO(&readfds);
    FD_ZERO(&execptfds);
    
    FD_SET(0, &readfds);
    FD_SET(s, &readfds);
    FD_SET(0, &execptfds);
    FD_SET(s, &execptfds);

    nFds = select(s + 1, &readfds, NULL, &execptfds, NULL);

    if (nFds > 0) {
      if (leerEscribir(&readfds, 0, s) < 0) {
	fprintf(stderr, "Error en la lectura: %d %s\n",
		errno, strerror(errno));
	exit(1);
      }
      
      if (leerEscribir(&readfds, s, 1) < 0) {
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
