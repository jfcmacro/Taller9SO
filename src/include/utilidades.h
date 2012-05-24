/* $Id: utilidades.h,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
#ifndef UTILIDADES_H
#define UTILIDADES_H utilidades_h

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int mksocket(const char*);
int mksocketclient();
int mkconnect(int s, const char *);
void usage(const char*progname, const char*mensaje);
int validarError(fd_set*, int);
int leerEscribir(fd_set*, int, int);
int leerEscribir2(int, int);
int leerEscribirNoBloqueante(int, int);
int establecerDescriptorNoBloqueante(int);
int establecerDescriptorBloqueante(int);
int noBloqueante(int);
int bloqueante(int);

#endif
