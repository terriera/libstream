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

static int	parse_mode(const char *mode, int *oflags)
{
  int		retval;
  int		write_mode;

  *oflags = 0;
  if ('r' == *mode)
  {
    write_mode = O_RDONLY;
    retval = LBS_RD;
  }
  else if ('w' == *mode || 'a'== *mode)
  {
    *oflags = O_CREAT | ('w' == *mode ? O_TRUNC : O_APPEND);
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
  *oflags |= write_mode;
  return retval;
}

t_my_file	*my_fopen(const char *path, const char *mode)
{
  int		fildes;
  int		oflags;
  int		flags;
  t_my_file	*stream;

  if (NULL == path || NULL == mode)
    return NULL;
  if (-1 == (flags = parse_mode(mode, &oflags)))
    return NULL;
  if (-1 == (fildes = open(path, oflags, 0666)))
    return NULL;
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
  stream->last_access = (stream->flags & O_WRONLY) ? ACC_WRITE : ACC_READ;
  return stream;
}
