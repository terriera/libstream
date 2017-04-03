/*
** buffer.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <unistd.h>
#include "libstream.h"
#include "buffer.h"

#define min(a, b) ((a) > (b) ? (b) : (a))

static void		*memcpy(void *dst, const void *src, size_t n)
{
  unsigned char		*d;
  const unsigned char	*s;

  d = dst;
  s = src;
  while (n--)
    *d++ = *s++;
  return dst;
}

t_buffer	*buf_new()
{
  t_buffer	*buf;

  buf = malloc(sizeof(t_buffer));
  if (NULL == buf)
    return NULL;
  buf->pos = 0;
  buf->limit = 0;
  return buf;
}

void		buf_free(t_buffer *buf)
{
  if (NULL != buf)
    free(buf);
}

int		buf_getc(t_buffer *buf)
{
  if (NULL == buf)
    return -1;
  if (buf->limit <= buf->pos || 0 == buf->limit)
    return -1;
  return buf->data[buf->pos++];
}

size_t		buf_getbytes(t_buffer *buf, void *dst, size_t size)
{
  size_t	avail;

  if (NULL == buf)
    return 0;
  if (buf->limit <= buf->pos || 0 == buf->limit)
    return 0;
  avail = min(buf->limit - buf->pos, size);
  dst = memcpy(dst, &buf->data[buf->pos], avail);
  buf->pos += avail;
  return avail;
}

int		buf_fill(t_buffer *buf, int fildes)
{
  int		result;

  if (NULL == buf)
    return -1;
  buf->pos = 0;
  if (-1 == (result = read(fildes, buf->data, MY_READ_SIZE)))
  {
    buf->limit = 0;
    return -1;
  }
  return buf->limit = result;
}

/*
** int pos -> avoid int and unsigned comparison.
*/
int		buf_flush(t_buffer *buf, int fildes)
{
  int		result;
  int		pos;

  if (NULL == buf)
    return -1;
  pos = buf->pos;
  if (pos != (result = write(fildes, buf->data, pos)))
    return -1;
  buf->pos = 0;
  buf->limit = 0;
  return result;
}

int		buf_putc(t_buffer *buf, int c)
{
  if (NULL == buf)
    return -1;
  if (buf->pos >= MY_WRITE_SIZE)
    return -1;
  buf->data[buf->pos++] = c;
  return c;
}

unsigned	buf_size(t_buffer *buf)
{
  if (NULL == buf)
    return -1;
  return buf->limit <= buf->pos ? 0 : buf->limit - buf->pos;
}

void		buf_skip(t_buffer *buf, unsigned n)
{
  if (NULL != buf)
  {
    if (buf->limit >= buf->pos + n)
      buf->pos += n;
    else
      buf->pos = buf->limit;
  }
}
