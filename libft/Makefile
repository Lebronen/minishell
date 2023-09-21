# Variables

NAME		= libft.a
INCLUDE		= includes
SRC_DIR		= sources/
OBJ_DIR		= objects/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
AR			= ar rcs
SMAKE		= make --no-print-directory

# Colors

END			=	\033[0m
BOLD		=	\033[1m
UNDER		=	\033[4m
REV			=	\033[7m
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
LIGHT_RED	=	\033[0;31m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

# Sources

SRC_FILES	=	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii \
				ft_isdigit ft_isprint ft_memchr ft_memcmp ft_memcpy ft_memmove \
				ft_memset ft_strchr ft_strdup ft_strlcpy ft_strlen ft_strncmp \
				ft_strnstr ft_strtrim ft_tolower ft_toupper ft_substr ft_strjoin \
				ft_itoa ft_split ft_strmapi ft_strlcat ft_striteri ft_putendl_fd \
				ft_putnbr_fd ft_putstr_fd ft_putchar_fd ft_strrchr \
				ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
				ft_lstdelone ft_lstclear ft_lstiter ft_lstmap  \
				ft_printf flags_utils handlers putui putnbr \
				putptr putstr putul_hex


SRC			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

bonus:		all

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)
			@echo "\033[1A                                                     "
			@echo -n "\033[1A"
			@echo "$(GREEN)$(BOLD)libft compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "\033[1A                                                     "
			@echo -n "\033[1A"
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -r $(OBJ_DIR)
			@echo "$(BLUE)libft object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme | awk '{\
			if ($$NF == "OK!") { \
				print "$(GREEN)"$$0"$(END)" \
			} else if ($$NF == "Error!") { \
				print "$(RED)$(BOLD)"$$0"$(END)" \
			} else if ($$1 == "Error:") { \
				print "$(LIGHT_RED)"$$0"$(END)" \
			} else { print }}'

.PHONY:		all clean fclean re norm