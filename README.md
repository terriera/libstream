# libstream

A library that handles buffered input / output.

## Description

The functions defined in *libstream* are simply basic versions of the libc stdio functions which names are prefixed with 'my_' to avoid any collisions. Here are the so far implemented functions:
```C
t_my_file	*my_fopen(const char *path, const char *mode);	
  
int	    	my_fclose(t_my_file *stream);
  
int	    	my_fputc(int c, t_my_file *stream);
  
int		    my_fgetc(t_my_file *stream);
 
size_t	    my_fread(void *ptr, size_t size, size_t nmemb, t_my_file *stream);
		 
size_t	    my_fwrite(const void *ptr, size_t size, size_t nmemb, t_my_file *stream);
 		  
char	    *my_fgets(char *str, int size, t_my_file *stream);
 		  
int		    my_fputs(const char *str, t_my_file *stream);

int		    my_fflush(t_my_file *stream);

int		    my_fseek(t_my_file *stream, long offset, int whence);

long	    my_ftell(t_my_file *stream);

void	    my_rewind(t_my_file *stream);

int		    my_fgetpos(t_my_file *stream, fpos_t *pos);

int	    	my_fsetpos(t_my_file *stream, const fpos_t *pos);

t_my_file	*my_fdopen(int fildes, const char *mode);

t_my_file	*my_freopen(const char *path, const char *mode, t_my_file *stream);
```
## Contraintes du projet

This small project had to be implemented in **Ansi C**, using a small set of functions:
- open(2)
- close(2)
- read(2)
- write(2)
- lseek(2)
- malloc(3)
- free(3)

Global or external static variables are strictly prohibited.

## Still to implement
The behavior of `my_fflush(NULL)`, flushing all the open output streams is still to implement.
