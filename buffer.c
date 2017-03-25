/*
** buffer.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libstream.h"
#include "buffer.h"

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

int		buf_fill(t_buffer *buf, int fildes)
{
  int		result;

  if (NULL == buf)
    return -1;
  buf->pos = 0;
  if (-1 == (result = read(fildes, buf->data, MY_BUFSIZE)))
  {
    buf->limit = 0;
    return -1;
  }
  return buf->limit = result;
}

int		buf_flush(t_buffer *buf, int fildes)
{
  int		result;
  int		pos;

  if (NULL == buf)
    return -1;
  pos = buf->pos;
  result = write(fildes, buf->data, pos);
  if (result != pos)
    return -1;
  buf->pos = 0;
  return result;
}

int		buf_putc(t_buffer *buf, int c)
{
  if (NULL == buf)
    return -1;
  if (buf->pos >= MY_BUFSIZE)
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

void		buf_print(t_buffer *buf)
{
  unsigned	i;

  printf("Limit : %d, position: %d\n", buf->limit, buf->pos);
  printf("[ ");
  for (i = 0; i < MY_BUFSIZE; ++i)
  {
    if (i < buf->limit)
      printf("%x ", (buf->data[i]));
    else
      printf("%c ", '.');
  }
  puts("]");
}
