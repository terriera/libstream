/*
** my_fputc.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include "libstream.h"

/*
** FIXME: replace direct access to buffer inner variables by a my_fflush call
** when it's implemented.
*/
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
    if (-1 == buf_flush(stream->buffer, stream->fildes))
    {
      stream->flags |= LBS_ERR;
      return MY_EOF;
    }
    c = buf_putc(stream->buffer, c);
  }
  return -1 == c ? MY_EOF : c;
}
