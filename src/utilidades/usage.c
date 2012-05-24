/* $Id: usage.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
/* usage.c */
#include <stdio.h>
#include <stdlib.h>

void
usage(const char* progname, const char* mensaje) {
  static char uso[] = "Uso: %s %s\n";
  fprintf(stderr, uso, progname, mensaje);
  exit(1);
}
