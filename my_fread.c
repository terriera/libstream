/*
** my_fread.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include "libstream.h"

/*
** Reads size bytes (at most) from stream and store it in dst.
** Returns the number of bytes actually read from stream.
*/
static size_t	read_item(t_my_file *stream, char *dst, size_t size)
{
  size_t	avail;
  size_t	total;
  int		filled;

  total = 0;
  avail = 0;
  while (total < size)
  {
    avail = buf_getbytes(stream->buffer, dst, size - total);
    total += avail;
    dst += avail;
    if (total < size)
    {
      filled = buf_fill(stream->buffer, stream->fildes);
      if (0 == filled || -1 == filled)
      {
        stream->flags |= (0 == filled ? LBS_EOF : LBS_ERR);
        break;
      }
    }
  }
  return total;
}

size_t		my_fread(void *ptr,
			 size_t size,
			 size_t nmemb,
			 t_my_file *stream)
{
  char		*p;
  size_t	n;

  if (NULL == stream)
    return MY_EOF;
  if (ACC_WRITE == stream->last_access)
  {
    if (MY_EOF == my_fflush(stream))
      return MY_EOF;
    stream->last_access = ACC_READ;
  }
  p = ptr;
  for (n = 0; n < nmemb; ++n)
  {
    if (read_item(stream, p, size) < size)
      break;
    p += size;
  }
  return n;
}
