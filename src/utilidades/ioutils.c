/* $Id: ioutils.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

 /*
   * Establece los descriptores como funciones
   * no bloqueantes
   */

int
establecerDescriptorNoBloqueante(int descriptor) {
  int val;

  if ((val = fcntl(descriptor, F_GETFL, 0)) < 0)
    return -1;

  if ((val = fcntl(descriptor, F_SETFL, val | O_NONBLOCK)) < 0)
    return -1;

  return 0;
}

int
establecerDescriptorBloqueante(int descriptor) {
  int val;

  if ((val = fcntl(descriptor, F_GETFL, 0)) < 0)
    return -1;

  if ((val = fcntl(descriptor, F_SETFL, val & ~O_NONBLOCK)) < 0)
    return -1;

  return 0;
}

int
noBloqueante(int fd) {
  int on = 1;

  return ioctl(fd, FIONBIO, &on);
}

int
bloqueante(int fd) {
  int off = 0;

  return ioctl(fd, FIONBIO, &off);
}
