NAME = pipex
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS= -I libft/src # -I : include 
CC = cc
SRC = \
	  path.c pipex_utils.c children.c main.c 
OBJ = $(SRC:.c=.o)
LIBFT= libft/libft.a

all : $(NAME)
	
%.o : %.c pipex.h
	$(CC) $(CFLAGS) $(CPPFLAGS)-o $@ -c $<

re: fclean all

fclean: clean
	rm -f $(NAME) 
	make fclean -C libft #appel le make de libft

clean :
	rm -rf $(OBJ)

sanitize:
	make CFLAGS="-Wall -Wextra -Werror -g3 -fsanitize=address"

debug:
	make CFLAGS="-Wall -Wextra -Werror -g3"

FORCE : 
 
$(LIBFT) : FORCE #commande vide pour qu'il execute a chaque fois make
	make -C libft # -C : make dans un autre dossier.

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

.PHONY: all clean fclean re FORCE
