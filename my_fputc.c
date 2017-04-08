/*
** my_fputc.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include "libstream.h"

int	my_fputc(int c, t_my_file *stream)
{
  if (NULL == stream)
    return MY_EOF;
  if (ACC_READ == stream->last_access)
  {
    stream->buffer->pos = 0;
    stream->buffer->limit = 0;
    stream->last_access = ACC_WRITE;
  }
  if (-1 == buf_putc(stream->buffer, c))
  {
    if (MY_EOF == my_fflush(stream))
      return MY_EOF;
    if (-1 == (c = buf_putc(stream->buffer, c)))
      stream->flags |= LBS_ERR;
  }
  return -1 == c ? MY_EOF : c;
}
