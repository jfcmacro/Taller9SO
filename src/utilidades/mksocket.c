/* $Id: mksocket.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
/* mksocket.h */
#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/un.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int
mksocket(const char* name) {
  int fd, len;
  struct sockaddr_un addr;
  struct stat sbuf;

  /*
   * Si la longitud de la direccion del socket es muy larga,
   * el requirimiento falla
   */
  if (strlen(name) > sizeof(addr.sun_path)) {
    errno = ENAMETOOLONG;
    return -1;
  }
  
  if (stat(name, &sbuf) < 0) {
    /*
     * Si el stat falla es debido a que el nombre esta perdido
     * ignore el error.
     */
    if (errno == ENOENT) 
      errno = 0;
    else
      return -1;
  }
  else {
    /*
     * Si el archivo existe y es un socket, entonces borrelo
     * De otra forma el nombre esta en uso
     */
    if (S_ISSOCK(sbuf.st_mode)) {
      if (unlink(name) < 0) {
	return -1;
      }
    } 
    else {
      errno = EBUSY;
      return -1;
    }
  }

  /*
   * Crea un unix domain stream
   */
  if ((fd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
    return -1;
  }

  /*
   * Crea y liga el nombre.
   */
  bzero(&addr, sizeof(addr));
  addr.sun_family = AF_LOCAL;
  strcpy(addr.sun_path, name);
  len = sizeof(addr);
  if (bind(fd, (struct sockaddr *) &addr, len) < 0) {
    return -1;
  }

  /*
   * Retorna el punto final del socket
   */
  return fd;
}

int 
mksocketcliente() {
  
  return socket(AF_LOCAL, SOCK_STREAM, 0);
}
