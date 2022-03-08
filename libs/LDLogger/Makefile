NAME	=		libLDLogger

CC 		=		clang++

SRC_DIR = 		$(shell find srcs -type d)
INC_DIR = 		$(shell find includes -type d)

OBJ_DIR = 		objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRC 	=		Logger.cpp

OBJ		=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))

#Compilation flag
CFLAGS	=		-Wall -Wextra -Werror -std=c++98 -g3

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
	msg = $(shell echo "$(_PURPLE)Valgrind and debug flags will are added. Take care to rebuild the program entirely if you already used valgrind.$(_WHITE)")
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

all:			$(NAME).a

$(NAME).a:		$(OBJ)
				@echo "-----\nCompiling $(_YELLOW)$@$(_WHITE) ... \c"
				$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1; echo "ar rc $@ $(OBJ) && ranlib $@" >> $(BUILD_LOG) 2>&1)
				$(eval ret_status := $(shell ar rc $@ $(OBJ) && ranlib $@ >> $(BUILD_LOG) 2>&1; echo $$?))
				@if [ $(ret_status) -eq 0 ]; then \
					echo "$(_GREEN)DONE$(_WHITE)\n-----"; \
				else \
					echo "$(_RED)FAILED$(_WHITE)\n-----"; \
					exit $(ret_status); \
				fi

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

re:				fclean all

clean_log:
				@echo "Cleaning $(_YELLOW)$(BUILD_LOG)$(_WHITE) ... \c"
				@cp /dev/null $(BUILD_LOG)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----";

clean:
				@echo "Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean clean_log
				@echo "Deleting library File $(_YELLOW)$(NAME).a $(_WHITE)and executable $(_YELLOW)$(NAME)$(_WHITE) ... \c"
				@rm -f $(NAME) $(NAME).a
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY:			all show re clean fclean clean_log
