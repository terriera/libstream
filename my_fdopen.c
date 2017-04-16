/*
** my_fdopen.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include "libstream.h"

/*
** Defined in my_fopen.c
** Not part of the public interface, so not declared in libstream.h.
*/
int		parse_mode(const char *mode, int *oflags);
t_my_file	*create_stream(int fildes, int flags);


/*
** As far as I understand, checking that ``mode'' and open() original flags
** are compatible requires to use fcntl(). This is not allowed by the
** assignment, so just skip this test...
*/
t_my_file	*my_fdopen(int fildes, const char *mode)
{
  int		oflags;
  int		flags;

  if (-1 == fildes || NULL == mode)
    return NULL;
  if (-1 == (flags = parse_mode(mode, &oflags)))
    return NULL;
  return create_stream(fildes, flags);
}
