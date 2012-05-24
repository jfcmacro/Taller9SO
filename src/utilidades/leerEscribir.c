/* $Id: leerEscribir.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
/* leerEscribir.c */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMANO  1024

int
leerEscribir(fd_set* set, int in, int out) {
  static char *buffer = NULL;
  int nCLeidos;

  if (!buffer) {
    buffer = (char *) malloc(TAMANO);
    if (!buffer) {
      return -1;
    }
  }

  if (FD_ISSET(in, set)) {
    
    do {

      nCLeidos = read(in, buffer, TAMANO);
      if (nCLeidos > 0) {
	if (write(out, buffer, nCLeidos) < 0) {
	  return -1;
	}
      }
      else 
	return -1;

    } while (nCLeidos == TAMANO);
  }
  return 0;
}

int
validarError(fd_set* set, int in) {
  char buffer[1];

  if (FD_ISSET(in, set)) {
    if (read(in, buffer, 1) < 0) {
      return -1;
    }
  }
  return 0;
}

int
leerEscribir2(int in, int out){

  static char *buffer = NULL;
  int nCarR;
  int nCarW;

  if (!buffer)
    if (!(buffer = (char *) malloc(TAMANO)))
      return -1;
      
  do {
    
    if ((nCarR = read(in, buffer, TAMANO)) < 0) 
      return -1;

    if (nCarR > 0)
      if ((nCarW = write(out, buffer, nCarR)) < 0)
	return -1;

  } while (nCarR == TAMANO);

  return 0;
}


int
leerEscribirNoBloqueante(int in, int out){

  static char *buffer = NULL;
  int nCarR;
  int nCarW;

  if (!buffer)
    if (!(buffer = (char *) malloc(TAMANO)))
      return -1;
      
  do {
    
    if ((nCarR = read(in, buffer, TAMANO)) < 0) {
      if (errno != EWOULDBLOCK) 
	return -1;
    }
    
    if (nCarR > 0)
      if ((nCarW = write(out, buffer, nCarR)) < 0)
	return -1;
    
  } while (nCarR == TAMANO);

  return 0;
}
