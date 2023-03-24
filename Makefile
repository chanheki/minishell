
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

PROMPT		=	prompt
PARSE		=	pars
HISTORY		=	history
EXECUTE		=	execute
SIGNAL		=	signal
PARSE		=	parse
TOKEN		=	token
TREE 		=	ASTtree

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

sources1 += $(PARSE)/is_valid_syntax.c
sources1 += $(PARSE)/parse.c

sources1 += $(PARSE)/$(TREE)/add_node_to_direction.c
sources1 += $(PARSE)/$(TREE)/clear_nodes.c
sources1 += $(PARSE)/$(TREE)/create_new_node.c
sources1 += $(PARSE)/$(TREE)/get_parent_node.c
sources1 += $(PARSE)/$(TREE)/get_root_node.c
sources1 += $(PARSE)/$(TREE)/make_ast_tree.c
sources1 += $(PARSE)/$(TREE)/make_node.c

sources1 += $(PARSE)/$(TOKEN)/add_token_to_tail.c
sources1 += $(PARSE)/$(TOKEN)/create_new_token.c
sources1 += $(PARSE)/$(TOKEN)/delete_outer_quotes.c
sources1 += $(PARSE)/$(TOKEN)/free_token_list.c
sources1 += $(PARSE)/$(TOKEN)/get_last_token_in_parenthesis.c
sources1 += $(PARSE)/$(TOKEN)/get_tail_token.c
sources1 += $(PARSE)/$(TOKEN)/handle_wildcard.c
sources1 += $(PARSE)/$(TOKEN)/interpret_expansion.c
sources1 += $(PARSE)/$(TOKEN)/join_token_value.c
sources1 += $(PARSE)/$(TOKEN)/set_fd_redirection_token.c
sources1 += $(PARSE)/$(TOKEN)/set_normal_token.c
sources1 += $(PARSE)/$(TOKEN)/set_operator_token.c
sources1 += $(PARSE)/$(TOKEN)/set_quote_token.c
sources1 += $(PARSE)/$(TOKEN)/set_token.c
sources1 += $(PARSE)/$(TOKEN)/tokenize_line.c
sources1 += $(PARSE)/$(TOKEN)/type_checker.c

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

# ----- Test ---- #
TEST_NAME = test
parse_sources = $(wildcard $(PARSE)/**/*.c)
parse_sources += $(wildcard $(PARSE)/*.c)
parse_objects = $(parse_sources:.c=.o)
tokenize = $(addprefix $(TEST_NAME)/, tokenize.c)
tokenize_objects = $(addprefix $(TEST_NAME)/, tokenize.o)
syntax = $(addprefix $(TEST_NAME)/, syntax_check.c)
syntax_objects = $(addprefix $(TEST_NAME)/, syntax_check.o)
ast = $(addprefix $(TEST_NAME)/, ast_tree.c)
ast_objects = $(addprefix $(TEST_NAME)/, ast_tree.o)

# ---- Command ---- #

.PHONY : all bonus clean fclean re

all : $(NAME)

$(NAME) : $(objects_goal) $(LIB)
	@$(CC) $(CFLAGS) -o $@ $(objects_goal) $(LIBCC) $(READLINE)
	@echo "$(DELINE) $(MAGENTA)$@ $(RESET) is compiled $(GREEN)$(BOLD) OK ✅ $(RESET)"

bonus : $(NAME)

test-tokenize: $(tokenize_objects) $(parse_objects) $(LIB)
	@$(CC) $(CFLAGS) -g -o $@ $(tokenize_objects) $(parse_objects) $(LIB) $(INCS)

test-syntax: $(syntax_objects) $(parse_objects) $(LIB)
	@$(CC) $(CFLAGS) -g -o $@ $(syntax_objects) $(parse_objects) $(LIB) $(INCS)

test-ast: $(ast_objects) $(parse_objects) $(LIB)
	@$(CC) $(CFLAGS) -g -o $@ $(ast_objects) $(parse_objects) $(LIB) $(INCS)

test-clean:
	@$(RM) $(tokenize_objects) $(syntax_objects) $(ast_objects) $(parse_objects) test-tokenize test-syntax test-ast
	@make -C ./lib fclean

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