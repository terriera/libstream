/*
** my_ftell.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <unistd.h>
#include "libstream.h"

/*
** FIXME: find a way to give t_buffer interface the offset job.
**
*/
long	my_ftell(t_my_file *stream)
{
  long	pos;

  if (-1 == (pos = lseek(stream->fildes, 0, SEEK_CUR)))
    return -1;
  if (ACC_WRITE == stream->last_access)
    pos += stream->buffer->pos;
  else if (ACC_READ == stream->last_access)
    pos -= stream->buffer->limit - stream->buffer->pos;
  return pos;
}
