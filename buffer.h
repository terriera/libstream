/*
** buffer.h for libstream
**
** Made by gumhead
**
*/

#ifndef BUFFER_H_
# define BUFFER_H_

# include "libstream_defines.h"

# define MY_BUFSIZE (MY_READ_SIZE > MY_WRITE_SIZE ? \
	MY_READ_SIZE : MY_WRITE_SIZE)

/*
** pos:  position in buffer [0..pos[ already read
** limit: buffer filled part [0..limit[ is valid data
*/
struct		s_buffer
{
    char	data[MY_BUFSIZE];
    unsigned	pos;
    unsigned	limit;
};

typedef struct	s_buffer t_buffer;

/*
** Allocate and initialize a new buffer
*/
t_buffer	*buf_new();

/*
** Release a buffer, free all memory
*/
void		buf_free(t_buffer *buf);

/*
** Return the next (unsigned) char from buffer, or -1 if the buffer is empty.
*/
int		buf_getc(t_buffer *buf);


size_t		buf_getbytes(t_buffer *buf, void *dst, size_t size);
size_t		buf_putbytes(t_buffer *buf, const void *src, size_t size);

/*
** Return the number of bytes actually read (at most size bytes) from buffer
** and copied to dst.
*/
size_t		buf_getbytes(t_buffer *buf, void *dst, size_t size);

/*
** Read data from file (fildes), and store them in buffer.
**
** Return -1 if there is an error while reading
** Return buffer total used space on success.
**
** Note: current data in buffer are always moved at the begining
** start before attempting to complete the buffer
*/
int		buf_fill(t_buffer *buf, int fildes);

int		buf_flush(t_buffer *buf, int fildes);

int		buf_putc(t_buffer *buf, int c);

/*
** Return the number of valid data, that haven't been used.
*/
unsigned	buf_size(t_buffer *buf);

/*
** Use n char, without having to call getc on each of them.
*/
void		buf_skip(t_buffer *buf, unsigned n);

#endif /*!BUFFER_H_ */
