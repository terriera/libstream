/*
** my_fgetpos.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdio.h>
#include "libstream.h"

int	my_fgetpos(t_my_file *stream, fpos_t *pos)
{
  *pos = my_ftell(stream);
  return -1 == *pos ? -1 : 0;
}
