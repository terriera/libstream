/*
** my_fsetpos.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdio.h>
#include "libstream.h"

int	my_fsetpos(t_my_file *stream, const fpos_t *pos)
{
  return my_fseek(stream, *pos, SEEK_SET);
}
