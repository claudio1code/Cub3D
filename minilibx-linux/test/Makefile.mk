
INC=%%%%

INCLIB=$(INC)/../lib

UNAME := $(shell uname)

CFLAGS= -I$(INC) -O3 -I.. -g

NAME= mlx-test
SRC = main.c
OBJ = $(SRC:%.c=%.o)

LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm

ifeq ($(UNAME), Darwin)
	# mac
	CC = clang
else ifeq ($(UNAME), FreeBSD)
	# FreeBSD
	CC = clang
else
	#Linux and others...
	CC	= gcc
	LFLAGS += -lbsd
endif

GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
DEF_COLOR = \033[0;39m

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(YELLOW)A linkar $(NAME)...  $(DEF_COLOR)"
	@sh -c ' \
		(while :; do \
			printf "\b|"; sleep 0.05; \
			printf "\b/"; sleep 0.05; \
			printf "\b-"; sleep 0.05; \
			printf "\b\\\\"; sleep 0.05; \
		done) & \
		SPIN_PID=$$!; \
		$(CC) -o $(NAME) $(OBJ) $(LFLAGS); \
		kill $$SPIN_PID 2>/dev/null; \
		wait $$SPIN_PID 2>/dev/null || true; \
		printf "\b\b$(GREEN)OK!$(DEF_COLOR)\n"'

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean:
	@rm -f $(NAME) $(OBJ) *~ core *.core

re: clean all
