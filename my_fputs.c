/*
** my_fputs.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include "libstream.h"

static unsigned	my_strlen(const char *str)
{
  unsigned	count;

  count = 0;
  while(*str++)
    ++count;
  return count;
}

int		my_fputs(const char *str, t_my_file *stream)
{
  unsigned	len;

  if (0 != (len = my_strlen(str)))
    return my_fwrite(str, 1, len, stream);
  return 0;
}
