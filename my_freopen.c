/*
** my_freopen.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libstream.h"

/*
** Defined in my_fopen.c
** Not part of the public interface, so not declared in libstream.h.
*/
int		parse_mode(const char *mode, int *raw_flags);

/*
** Can't handle the case where path == NULL without fcntl() which happens not
** to be allowed by the assignment.
** Otherwise, the code handling it would have been as follows:
**
**   if (NULL == path)
**   {
**     if(-1 == fcntl(file->fildes, F_SETFL, stream->flags))
**       return NULL;
**   }
**   else if (-1 == close(stream->fildes))
**   {
**     stream->flags |= LBS_ERR;
**     return NULL;
**   }
*/
t_my_file	*my_freopen(const char *path,
			    const char *mode,
			    t_my_file *stream)
{
  int		raw_flags;

  if (NULL == path || NULL == mode || NULL ==  stream)
    return NULL;
  if (-1 == (stream->flags = parse_mode(mode, &raw_flags)))
    return NULL;
  if (-1 == close(stream->fildes))
  {
    stream->flags |= LBS_ERR;
    return NULL;
  }
  if (-1 == (stream->fildes = open(path, raw_flags, 0666)))
    return NULL;
  stream->last_access = (stream->flags & LBS_WR) ? ACC_WRITE : ACC_READ;
  return stream;
}
