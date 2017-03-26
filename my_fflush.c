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
  if (-1 == (result = buf_fflush(stream->buffer, stream->fildes)))
  {
    stream->flags |= LBS_ERR;
    return MY_EOF;
  }
  return 0;
}
