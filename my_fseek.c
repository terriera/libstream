/*
** my_fseek.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <unistd.h>
#include "libstream.h"

int	my_fseek(t_my_file *stream, long offset, int whence)
{
  long	pos;

  if (SEEK_SET != whence && SEEK_CUR != whence && SEEK_END != whence)
    return -1;
  pos = offset;
  if (SEEK_CUR == whence)
  {
    pos += my_ftell(stream);
    whence = SEEK_SET;
  }
  return -1 == lseek(stream->fildes, pos, whence) ? -1 : 0;
}
