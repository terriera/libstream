#ifndef LIBSTREAM_H_
# define LIBSTREAM_H_

# include "libstream_defines.h"
# include "buffer.h"

# define LBS_RD		1
# define LBS_WR		2
# define LBS_RW		4
# define LBS_EOF	8
# define LBS_ERR	16

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

#endif /*!LIBSTREAM_H_ */
