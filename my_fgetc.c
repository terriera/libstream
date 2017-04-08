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
    if (MY_EOF == my_fflush(stream))
      return MY_EOF;
    stream->last_access = ACC_READ;
  }
  if (-1 == (c = buf_getc(stream->buffer)))
  {
    c = buf_fill(stream->buffer, stream->fildes);
    if (0 == c || -1 == c)
    {
      stream->flags |= (0 == c ? LBS_EOF : LBS_ERR);
      return MY_EOF;
    }
    if (-1 == (c = buf_getc(stream->buffer)))
      stream->flags |= LBS_ERR;
  }
  return -1 == c ? MY_EOF : c;
}
