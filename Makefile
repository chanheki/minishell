
# ---- NAME ---- #

NAME		=	minishell

LIB			=	./lib/libft.a
LIBCC		=	-L./lib -lft

CC = cc
CFLAGS = -Wall -Wextra -Werror $(DBGS)
DBGS = -fsanitize=address -g3

AR = ar
ARFLAG = ruc
RM = rm -rf

RDLINE_DIR	=	$(shell brew --prefix readline)
READLINE	=	-L$(RDLINE_DIR)/lib/ -lreadline
INCS		=	-I ./include -I$(RDLINE_DIR)/include 

object_dir	=	./objects

PROMPT		=	prompt/
PARSE		=	pars/
HISTORY		=	history/
EXECUTE		=	execute/
SIGNAL		=	signal/

# ---- escape ---- #

DELINE = \033[K
CURSUP = \033[A

RESET = \033[0m
RESTINT = \033[22m

BOLD = \033[1m

MAGENTA = \033[35m
GREEN = \033[32m
RED = \033[31m

# ---- Mandatory ---- #

sources1 :=	

sources1 += main.c

sources1 += $(PROMPT)/prompt.c
sources1 += $(EXECUTE)/execute.c
sources1 += $(SIGNAL)/signal.c


# ---- Bonus ---- #

sources2 :=	

sources2 += main_bonus.c

# ---- Elements ---- #

all_sources = $(sources1) $(sources2)

objects1 = $(sources1:.c=.o)
objects2 = $(sources2:.c=.o)
all_objects = $(objects1) $(objects2)

define objects_goal
$(addprefix $(object_dir)/, $(call $(if $(filter bonus, $(MAKECMDGOALS)), objects2, objects1))) 
endef

define react
$(if $(filter bonus, $(MAKECMDGOALS)), bonus, all)
endef

# ---- Command ---- #

.PHONY : all bonus clean fclean re

all : $(NAME)

$(NAME) : $(objects_goal) $(LIB)
	@$(CC) $(CFLAGS) -o $@ $(objects_goal) $(LIBCC) $(READLINE)
	@echo "$(DELINE) $(MAGENTA)$@ $(RESET) is compiled $(GREEN)$(BOLD) OK ✅ $(RESET)"

bonus : $(NAME)

$(object_dir)/%.o : %.c
	@#mkdir -p $(object_dir)
	@mkdir -p $(object_dir)/$(dir $^)
	@$(CC) $(CFLAGS) -c $^ -o $@ $(INCS)
	@echo " $(MAGENTA)$(NAME) $(RESET)objects file compiling... $(DELINE)$(GREEN) $^ $(RESET)$(CURSUP)"

$(LIB) :
	@make -C ./lib all

clean :
	@$(RM) $(all_objects)
	@rm -rf $(object_dir)
	@make -C ./lib clean
	@echo "$(RED) Delete$(BOLD) objects $(RESTINT)file $(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@make -C ./lib fclean
	@echo "$(RED) Delete$(BOLD) $(NAME) $(RESTINT)file $(RESET)"

re : fclean
	@make $(react)