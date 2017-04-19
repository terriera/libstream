NAME	= libstream_`uname -m`-`uname -s`.a
CC      = cc
IPATH   = .
CFLAGS  = -O2 -W -Wall -Werror -ansi -pedantic -I${IPATH}
OBJ     = $(SRC:.c=.o)
RM      = rm -f
SRC     = buffer.c          \
	  my_fopen.c        \
	  my_fclose.c       \
	  my_fgetc.c        \
	  my_fputc.c        \
	  my_fread.c        \
	  my_fwrite.c       \
	  my_fgets.c        \
	  my_fputs.c        \
	  my_fflush.c       \
	  my_fseek.c        \
	  my_ftell.c        \
	  my_rewind.c       \
	  my_fgetpos.c      \
	  my_fsetpos.c      \
	  my_fdopen.c       \
	  my_freopen.c

# rules
all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) *~ \#*

distclean: clean
	$(RM) $(NAME)

re: distclean all
