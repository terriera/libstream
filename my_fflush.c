/*
** my_fflush.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include "libstream.h"

int	my_fflush(t_my_file *stream)
{
  int	result;

  if (NULL == stream)
    return MY_EOF;
  if (ACC_READ == stream->last_access)
  {
    stream->buffer->pos = 0;
    stream->buffer->limit = 0;
  }
  else if (ACC_WRITE == stream->last_access)
  {
    if (-1 == (result = buf_flush(stream->buffer, stream->fildes)))
    {
      stream->flags |= LBS_ERR;
      return MY_EOF;
    }
  }
  else
  {
    stream->flags |= LBS_ERR;
    return MY_EOF;
  }
  return 0;
}
