/*
** my_fgetc.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include "libstream.h"

int	my_fgetc(t_my_file *stream)
{
  int 	c;

  if (NULL == stream)
    return MY_EOF;
  if (ACC_WRITE == stream->last_access)
  {
    if (-1 == buf_flush(stream->buffer, stream->fildes))
    {
      stream->flags |= LBS_ERR;
      return MY_EOF;
    }
    stream->last_access = ACC_READ;
  }
  c = buf_getc(stream->buffer);
  if (-1 == c)
  {
    if (-1 == buf_fill(stream->buffer, stream->fildes))
      return MY_EOF;
    c = buf_getc(stream->buffer);
  }
  return -1 == c ? MY_EOF : c;
}
