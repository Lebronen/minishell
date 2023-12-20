# Variables

NAME		= minishell
NAME_B		= minishell_bonus
INCLUDE		= includes
LIBFT		= libft
SRC_DIR		= srcs/
OBJ_DIR		= objects/
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
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

SRC_FILES	=	minishell prompt prompt_utils exec exec_utils error env lexer lexer_utils lexer_types lexer_types2 lexer_env lexer_envbis builtins utils2 \
				 linked_list nodes nodes_free redirections heredoc_v2 heredoc_v2bis builtins_utils env_shlvl signal pipes pipe_utils exec_utils2 builtins2 \
				 lexer_types3 is_dir builtin_utils2 builtins3

SRC_B_FILES	=	minishell prompt exec


SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC_B		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_B_FILES)))
OBJ_B		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_B_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

bonus:		$(NAME_B)

$(NAME):	$(OBJ)
			@$(SMAKE) -C $(LIBFT)
			@$(CC) $(OBJ) -L $(LIBFT) -lft -lreadline -o $(NAME)
			@echo "$(GREEN)$(BOLD)$(NAME) compiled!$(DEF_COLOR)"

$(NAME_B):	$(OBJ_B)
			@$(SMAKE) -C $(LIBFT)
			@$(CC) $(OBJ_B) -L $(LIBFT) -lft -o $(NAME_B)
			@echo "$(GREEN)$(BOLD)$(NAME_B) compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "\033[1A                                                     "
			@echo -n "\033[1A"
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIBFT)/includes -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -r $(OBJ_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) $(NAME_B)
			@$(SMAKE) -C $(LIBFT) fclean
			@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

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

.PHONY:		all clean fclean re norm bonus
