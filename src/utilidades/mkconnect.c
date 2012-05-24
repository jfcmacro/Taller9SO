/* $Id: mkconnect.c,v 1.1.1.1 2003/06/19 19:00:15 fcardona Exp $ */
/* mkconnect.c */
#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/un.h>
#include <errno.h>

int
mkconnect(int s, const char *name) {

  struct sockaddr_un addr;
  
  if (strlen(name) > sizeof(addr.sun_path)) {
    errno = ENAMETOOLONG;
    return -1;
  }

  bzero(&addr, sizeof(addr));
  addr.sun_family = AF_LOCAL;
  strcpy(addr.sun_path, name);

  if (connect(s, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
    return -1;
  }
  return 0;
}
  
