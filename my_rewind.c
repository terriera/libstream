/*
** my_rewind.c for libstream
**
** Made by Arnaud Terrier
**
*/

#include <stdlib.h>
#include <unistd.h>
#include "libstream.h"

void	my_rewind(t_my_file *stream)
{
  my_fseek(stream, 0, SEEK_SET);
}
