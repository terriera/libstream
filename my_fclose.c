/*
** my_fclose.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <unistd.h>
#include "libstream.h"

int	my_fclose(t_my_file *stream)
{
  int	fildes;

  if (NULL == stream)
    return MY_EOF;
  fildes = stream->fildes;
  buf_flush(stream->buffer, stream->fildes);
  stream->fildes = -1;
  stream->flags = 0;
  free(stream->buffer);
  free(stream);
  return (-1 == close(fildes)) ? MY_EOF : 0;
}
