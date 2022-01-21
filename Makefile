NAME	=		containers
DIY_NAME	=	DIY_containers

CC 		=		clang++

SRC_DIR = 		$(shell find srcs -type d)
INC_DIR = 		$(shell find includes -type d) \
				$(shell find srcs -type d)

OBJ_DIR = 		objs
DIY_OBJ_DIR = 	diy_objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

VECTOR_TEST =	vector_element_access_test.cpp \
				vector_modifiers_test.cpp \
				#vector_capacity_test.cpp \
				vector_iterators_test.cpp \
				vector_allocator_test.cpp \
				vector_relational_operators_test.cpp

SRC 	=		main.cpp \
				$(VECTOR_TEST) \
				Logger.cpp

OBJ		=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))
DIY_OBJ		=	$(addprefix $(DIY_OBJ_DIR)/, $(SRC:%.cpp=%.o))

#Compilation flag
CFLAGS	=		-Wall -Wextra -Werror -std=c++98

#Include flag
IFLAGS	=		$(foreach dir, $(INC_DIR), -I$(dir))

BUILD_LOG = logs/Makefile.log

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
	msg = $(shell echo "$(_PURPLE)fsanitize and debug flags are added.$(_WHITE)")
	useless := $(info $(msg))
else ifeq ($(DEBUG), vl)
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)Valgrind and debug flags are added. Take care to rebuild the program entirely if you already used valgrind.$(_WHITE)")
	useless := $(info $(msg))
else ifeq ($(DEBUG), gdb)
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)gdb and debug flags are added.$(_WHITE)")
	useless := $(info $(msg))
else
	CFLAGS += -O3
	msg = $(shell echo "$(_PURPLE)Debug mode not enabled. Optimization flags are added.$(_WHITE)")
	useless := $(info $(msg))
endif

msg = $(shell echo "$(_PURPLE)A file named $(_YELLOW)$(BUILD_LOG)$(_PURPLE) contain the current build informations.$(_WHITE)")
useless := $(info $(msg))

# Make sure the logs directory exists.
useless := $(shell mkdir -p logs)

# Split the log file between each run.
useless := $(shell echo "________________________________________________________________________________" >> $(BUILD_LOG); \
				echo "$(shell date) : \c" >> $(BUILD_LOG); \
				echo "building with : [$(MAKECMDGOALS)]" >> $(BUILD_LOG))

all:			$(NAME) $(DIY_NAME)
				@echo "$(_PURPLE)Usage:"
				@echo "Type $(_BLUE)make test SEED=NUMBER$(_PURPLE) to create a binary testing STL containers."
				@echo "Type $(_BLUE)make diy_test SEED=NUMBER$(_PURPLE) to create a binary testing homemade containers."
				@echo "Type $(_BLUE)make test_both SEED=NUMBER$(_PURPLE) to create a binary testing both containers and a diff.log file."
				@echo "Add $(_BLUE)DEBUG=fs$(_PURPLE) to compile with fsanitize and debug flags."
				@echo "Add $(_BLUE)DEBUG=vl$(_PURPLE) to compile with valgrind and debug flags.$(_WHITE)"
				@echo "Add $(_BLUE)DEBUG=gdb$(_PURPLE) to compile with gdb and debug flags.$(_WHITE)"

$(NAME):		$(OBJ)
				@echo "-----\nCompiling $(_YELLOW)$@$(_WHITE) ... \c"
				$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1 ; echo "$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@" >> $(BUILD_LOG) 2>&1)
				$(eval ret_status := $(shell $(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@ >> $(BUILD_LOG) 2>&1; echo $$?))
				@if [ $(ret_status) -eq 0 ]; then \
					echo "$(_GREEN)DONE$(_WHITE)\n-----"; \
				else \
					echo "$(_RED)FAILED$(_WHITE)\n-----"; \
					exit $(ret_status); \
				fi

$(DIY_NAME):	$(DIY_OBJ)
				@echo "-----\nCompiling $(_YELLOW)$@$(_WHITE) ... \c"
				$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1 ; echo "$(CC) $(CFLAGS) $(IFLAGS) $(DIY_OBJ) -o $@ " >> $(BUILD_LOG) 2>&1)
				$(eval ret_status := $(shell $(CC) $(CFLAGS) $(IFLAGS) $(DIY_OBJ) -o $@ >> $(BUILD_LOG) 2>&1; echo $$?))
				@if [ $(ret_status) -eq 0 ]; then \
					echo "$(_GREEN)DONE$(_WHITE)\n-----"; \
				else \
					echo "$(_RED)FAILED$(_WHITE)\n-----"; \
					exit $(ret_status); \
				fi

test:			$(NAME)
				@echo "-----\nTesting $(_YELLOW)$<$(_WHITE) ... \c"
				@if [ "$(DEBUG)" = "vl" ]; then \
					valgrind --leak-check=full --show-leak-kinds=all ./$< $(SEED); \
				elif [ "$(DEBUG)" = "gdb" ]; then \
					gdb ./$< $(SEED); \
				else \
					./$< $(SEED); \
				fi
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

diy_test:		$(DIY_NAME)
				@echo "-----\nTesting $(_YELLOW)$<$(_WHITE) ... \c"
				@if [ "$(DEBUG)" = "vl" ]; then \
					valgrind --leak-check=full --show-leak-kinds=all ./$< $(SEED); \
				elif [ "$(DEBUG)" = "gdb" ]; then \
					gdb ./$< $(SEED); \
				else \
					./$< $(SEED); \
				fi
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

test_both:		$(NAME) $(DIY_NAME)
				@echo "-----\nTesting $(_YELLOW)$(NAME)$(_WHITE) and $(_YELLOW)$(DIY_NAME)$(_WHITE) ... \c"
				@if [ "$(DEBUG)" = "vl" ]; then \
					valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(SEED); \
					valgrind --leak-check=full --show-leak-kinds=all ./$(DIY_NAME) $(SEED); \
				elif [ "$(DEBUG)" = "gdb" ]; then \
					gdb ./$(NAME) $(SEED); \
					gdb ./$(DIY_NAME) $(SEED); \
				else \
					./$(NAME) $(SEED); \
					./$(DIY_NAME) $(SEED); \
				fi
				@diff --expand-tabs --ignore-tab-expansion --side-by-side --left-column logs/DIY_containers.log logs/containers.log > logs/diff.log || true
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"
				@echo "$(_YELLOW)logs/diff.log$(_PURPLE) has been created.$(_WHITE)"

show:
				@echo "\nSRC :\n$(SRC)\n"
				@echo "OBJ :\n$(OBJ)\n"
				@echo "CFLAGS :\n$(CFLAGS)\n"
				@echo "IFLAGS :\n$(IFLAGS)\n"
				@echo "LIB_DIR :\n$(LIB_DIR)\n"

$(OBJ_DIR)/%.o : 	%.cpp
				@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
				$(shell mkdir -p $(OBJ_DIR))
				$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1 ;\
				echo "$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<" >> $(BUILD_LOG) 2>&1)
				$(eval ret_status := $(shell $(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $< >> $(BUILD_LOG) 2>&1; echo $$?))
				@if [ $(ret_status) -eq 0 ]; then \
					echo "$(_GREEN)DONE$(_WHITE)\n-----"; \
				else \
					echo "$(_RED)FAILED$(_WHITE)\n-----"; \
					exit $(ret_status); \
				fi

$(DIY_OBJ_DIR)/%.o : 	%.cpp
				@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
				$(shell mkdir -p $(DIY_OBJ_DIR))
				$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1 ;\
				echo "$(CC) $(CFLAGS) -D DIY=true $(IFLAGS) -o $@ -c $<" >> $(BUILD_LOG) 2>&1)
				$(eval ret_status := $(shell $(CC) $(CFLAGS) -D DIY=true $(IFLAGS) -o $@ -c $< >> $(BUILD_LOG) 2>&1; echo $$?))
				@if [ $(ret_status) -eq 0 ]; then \
					echo "$(_GREEN)DONE$(_WHITE)\n-----"; \
				else \
					echo "$(_RED)FAILED$(_WHITE)\n-----"; \
					exit $(ret_status); \
				fi

re:				fclean all

norme:
				norminette $(SRC_DIR)

clean_log:
				@echo "Cleaning $(_YELLOW)$(BUILD_LOG)$(_WHITE) ... \c"
				@cp /dev/null $(BUILD_LOG)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----";

clean:
				@echo "Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR) $(DIY_OBJ_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean clean_log
				@echo "Deleting library File $(_YELLOW)$(NAME)$(_WHITE) ... \c"
				@rm -f $(NAME) $(DIY_NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY:			all show re clean fclean clean_log norme test diy_test test_both