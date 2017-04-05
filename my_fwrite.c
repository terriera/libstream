/*
** my_fwrite.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include "libstream.h"

size_t		write_item(t_my_file *stream, const char *src, size_t size)
{
  size_t	buffered;
  size_t	total;

  if (NULL == stream)
    return 0;
  buffered = 0;
  total = 0;
  while (total < size)
  {
    buffered = buf_putbytes(stream->buffer, src, size - total);
    total += buffered;
    src += buffered;
    if (total < size)
      if (MY_EOF == my_fflush(stream))
      	break;
  }
  return total;
}

size_t		my_fwrite(const void *ptr, 
			  size_t size, 
			  size_t nmemb, 
			  t_my_file *stream)
{
  size_t	n;
  const char	*p;

  if (NULL == stream)
    return MY_EOF;
  if (ACC_READ == stream->last_access)
  {
    if (MY_EOF == my_fflush(stream))
      return 0;
    stream->last_access = ACC_WRITE;
  }
  p = ptr;
  for (n = 0; n < nmemb; ++n)
  {
    if (write_item(stream, p, size) < size)
      break;
    p += size;
  }
  return n;
}
