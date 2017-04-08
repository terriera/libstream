/*
** my_fgets.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <fcntl.h>
#include "libstream.h"

char	*my_fgets(char *str, int size, t_my_file *stream)
{
  char	c;
  int	i;

  if (size-- <= 0)
    return NULL;
  for (i = 0; size > 0; ++i, --size)
  {
    c = my_fgetc(stream);
    if (MY_EOF == c || '\n' == c)
      break;
    str[i] = c;
  }
  if ('\n' == c)
    str[i++] = '\n';
  str[i] = '\0';
  return str;
}
