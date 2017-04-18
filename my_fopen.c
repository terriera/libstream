/*
** my_fopen.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libstream.h"

/*
** Both parse_mode and create_stream are not static as they are useful for
** my_fdopen as well.
** Yet they're not declared in libstream.h as they're not meant to be part of
** the public interface.
*/
int		parse_mode(const char *mode, int *raw_flags)
{
  int		retval;
  int		write_mode;

  *raw_flags = 0;
  if ('r' == *mode)
  {
    write_mode = O_RDONLY;
    retval = LBS_RD;
  }
  else if ('w' == *mode || 'a'== *mode)
  {
    *raw_flags = O_CREAT | ('w' == *mode ? O_TRUNC : O_APPEND);
    write_mode = O_WRONLY;
    retval = LBS_WR;
  }
  else
    return -1;
  for (++mode; '\0' != *mode; ++mode)
    if ('+' == *mode)
    {
      write_mode = O_RDWR;
      retval = LBS_RW;
    }
  *raw_flags |= write_mode;
  return retval;
}

t_my_file	*create_stream(int fildes, int flags)
{
  t_my_file	*stream;

  if (NULL == (stream = malloc(sizeof (t_my_file))))
  {
    close(fildes);
    return NULL;
  }
  if (NULL == (stream->buffer = buf_new()))
  {
    my_fclose(stream);
    return NULL;
  }
  stream->fildes = fildes;
  stream->flags = flags;
  stream->last_access = (stream->flags & LBS_WR) ? ACC_WRITE : ACC_READ;
  return stream;
}

t_my_file	*my_fopen(const char *path, const char *mode)
{
  int		fildes;
  int		raw_flags;
  int		flags;

  if (NULL == path || NULL == mode)
    return NULL;
  if (-1 == (flags = parse_mode(mode, &raw_flags)))
    return NULL;
  if (-1 == (fildes = open(path, raw_flags, 0666)))
    return NULL;
  return create_stream(fildes, flags);
}
