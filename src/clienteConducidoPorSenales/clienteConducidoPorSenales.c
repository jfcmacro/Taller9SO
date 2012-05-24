/* $Id: clienteConducidoPorSenales.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <utilidades.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>

int s;
unsigned long veces = 0;

void
manejadorSenales(int senal) {

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

  fprintf(stdout, "Veces: %ld\n", veces);
}

int
main(int argc, char *argv[]) {

  struct sigaction nuevaSenal;
  struct sigaction viejaSenal;
  sigset_t conjuntoSenales;
  int on = 1;

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

  sigemptyset(&conjuntoSenales);
  
  nuevaSenal.sa_handler = manejadorSenales;
  nuevaSenal.sa_mask = conjuntoSenales;
  nuevaSenal.sa_flags = 0;

  if (sigaction(SIGIO, &nuevaSenal, &viejaSenal) < 0) { 
    fprintf(stderr, "Error manejo de senales %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }

  if (fcntl(0, F_SETOWN, getpid()) < 0) {
    fprintf(stderr, "Error estableciendo la identificacion %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }
    
  if (ioctl(0, FIOASYNC, &on) < 0) {
    fprintf(stderr, "Error estableciendo FIOASYNC %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }

  if (noBloqueante(0) < 0) { 
    fprintf(stderr, "Error estableciendo descriptor no bloqueante %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }

  if (fcntl(s, F_SETOWN, getpid()) < 0) {
    fprintf(stderr, "Error estableciendo la identificacion %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }
    
  if (ioctl(s, FIOASYNC, &on) < 0) {
    fprintf(stderr, "Error estableciendo FIOASYNC %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }

  if (noBloqueante(s) < 0) { 
    fprintf(stderr, "Error estableciendo descriptor no bloqueante %d %s\n",
	    errno, strerror(errno));
    exit(1);
  }
  
  while (1) {
    veces++;
  }
  
  exit(0);
  return 0;
}
