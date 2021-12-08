NAME	=		containers
DIY_NAME	=	DIY_containers

CC 		=		clang++

SRC_DIR = 		$(shell find srcs -type d)
INC_DIR = 		$(shell find includes -type d) \
				$(shell find srcs -type d)

OBJ_DIR = 		objs
DIY_OBJ_DIR = 	diy_objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRC 	=		main.cpp \
				vector_iterators_test.cpp \
				vector_capacity_test.cpp \
				vector_element_access_test.cpp \
				vector_modifiers_test.cpp \
				vector_allocator_test.cpp \
				Logger.cpp

OBJ		=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))
DIY_OBJ		=	$(addprefix $(DIY_OBJ_DIR)/, $(SRC:%.cpp=%.o))

#Compilation flag
CFLAGS	=		-Wall -Wextra -Werror -std=c++98

#Include flag
IFLAGS	=		$(foreach dir, $(INC_DIR), -I$(dir))

# Colors
_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m

DEBUG =
# Add fsanitize to the compilation flags if DEBUG is set to fs.
# If DEBUG is set to valgrind, add debug flags to the compilation flags.
ifeq ($(DEBUG), fs)
	CFLAGS += -fsanitize=address
	CFLAGS += -g3
	CFLAGS += -O0
	useless := $(info Compiling with fsanitize and debug flags.)
else ifeq ($(DEBUG), vl)
	CFLAGS += -g3
	CFLAGS += -O0
	useless := $(info Compiling with valgrind and debug flags.)
else
	CFLAGS += -O3
	useless := $(info Compiling without debug flags. Optimization flags are added.)
endif

all:			$(NAME) $(DIY_NAME)
				@echo "$(_PURPLE)Usage:"
				@echo "Type $(_BLUE)make test SEED=NUMBER$(_PURPLE) to create a binary testing STL containers."
				@echo "Type $(_BLUE)make diy_test SEED=NUMBER$(_PURPLE) to create a binary testing homemade containers."

$(NAME):		$(OBJ) Makefile
				@echo "-----\nCompiling $(_YELLOW)$@$(_WHITE) ... \c"
				@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

$(DIY_NAME):	$(DIY_OBJ) Makefile
				@echo "-----\nCompiling $(_YELLOW)$@$(_WHITE) ... \c"
				@$(CC) $(CFLAGS) $(IFLAGS) $(DIY_OBJ) -o $@
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

test:			$(NAME)
				@echo "-----\nTesting $(_YELLOW)$<$(_WHITE) ... \c"
				@if [ "$(DEBUG)" = "vl" ]; then \
					valgrind --leak-check=full --show-leak-kinds=all ./$< $(SEED); \
				else \
					./$< $(SEED); \
				fi
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

diy_test:		$(DIY_NAME)
				@echo "-----\nTesting $(_YELLOW)$<$(_WHITE) ...\c"
				@if [ "$(DEBUG)" = "vl" ]; then \
					valgrind --leak-check=full --show-leak-kinds=all ./$< $(SEED); \
				else \
					./$< $(SEED); \
				fi
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

test_both:		$(NAME) $(DIY_NAME)
				@echo "-----\nTesting $(_YELLOW)$(NAME)$(_WHITE) and $(_YELLOW)$(DIY_NAME)$(_WHITE) ...\c"
				@./$(NAME) $(SEED)
				@./$(DIY_NAME) $(SEED)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

show:
				@echo "\nSRC :\n$(SRC)\n"
				@echo "OBJ :\n$(OBJ)\n"
				@echo "CFLAGS :\n$(CFLAGS)\n"
				@echo "IFLAGS :\n$(IFLAGS)\n"
				@echo "LIB_DIR :\n$(LIB_DIR)\n"

$(OBJ_DIR)/%.o : 	%.cpp
				@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

$(DIY_OBJ_DIR)/%.o : 	%.cpp
				@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(DIY_OBJ_DIR)
				@$(CC) $(CFLAGS) -D DIY=true $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

re:				fclean all

debug:			$(OBJ) $(NAME) srcs/main.cpp
				@echo "executing Binary File $(_YELLOW)$@$(_WHITE) ..."
				@./$(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n"

norme:
				norminette $(SRC_DIR)

clean:
				@echo "Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR) $(DIY_OBJ_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean
				@echo "Deleting library File $(_YELLOW)$(NAME)$(_WHITE) ... \c"
				@rm -f $(NAME) $(DIY_NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY:			all show re clean fclean debug norme test diy_test