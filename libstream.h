/*
** libstream.h for libstream
**
** Made by Arnaud Terrier
**
*/

#ifndef LIBSTREAM_H_
# define LIBSTREAM_H_

# include <stdio.h>
# include "libstream_defines.h"
# include "buffer.h"

# define LBS_OPENED	1
# define LBS_RD		2
# define LBS_WR		4
# define LBS_RW		8
# define LBS_EOF	16
# define LBS_ERR	32

# define MY_EOF		(-1)

enum	e_access_type
{
	ACC_READ,
	ACC_WRITE
};

typedef enum	e_access_type t_access_type;

struct		s_my_file
{
  t_buffer	*buffer;
  int		fildes;
  int		flags;
  t_access_type	last_access;
};

typedef struct	s_my_file t_my_file;

/*
** Level 0.
*/
t_my_file	*my_fopen(const char *path, const char *mode);
int		my_fclose(t_my_file *stream);
int		my_fgetc(t_my_file *stream);
int		my_fputc(int c, t_my_file *stream);

/*
** Level 1.
*/
size_t		my_fread(void *ptr,
			 size_t size,
			 size_t nmemb,
			 t_my_file *stream);
size_t		my_fwrite(const void *ptr, 
			  size_t size, 
			  size_t nmemb, 
			  t_my_file *stream);
int		my_fflush(t_my_file *stream);
char		*my_fgets(char *str, int size, t_my_file *stream);
int		my_fputs(const char *str, t_my_file *stream);

/*
** Level 2.
*/
int		my_fseek(t_my_file *stream, long offset, int whence);
long		my_ftell(t_my_file *stream);
void		my_rewind(t_my_file *stream);
int		my_fgetpos(t_my_file *stream, fpos_t *pos);
int		my_fsetpos(t_my_file *stream, const fpos_t *pos);

/*
** Level 3.
*/
t_my_file	*my_fdopen(int fildes, const char *mode);
t_my_file	*my_freopen(const char *path, 
			    const char *mode, 
			    t_my_file *stream);

#endif /*!LIBSTREAM_H_ */
