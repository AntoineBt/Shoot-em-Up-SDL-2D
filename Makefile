NAME		=	bin/shmupsdl2d
CC		=	gcc
CFLAGS		=	-Wall -Wextra -pedantic
CFLAGS		+=	-Iinc -Iinc/SDLazy -Iinc/SDLazy/CList

LDFLAGS		=	-L.
LDFLAGS		+=	-lm
LDFLAGS		+=	bin/libSDL-1.2.so.0
LDFLAGS		+=	bin/libSDL_image-1.2.so.0
LDFLAGS		+=	bin/libtiff.so.3
LDFLAGS		+=	bin/libjpeg.so.62
LDFLAGS		+=	bin/libSDLazy.so
LDFLAGS		+=	bin/libCList.so
LDFLAGS		+=	bin/libfmodex64.so
LDFLAGS		+=	-pthread

RM		=	@rm -f

SRC		=	src/main.c		\
			src/data_init.c		\
			src/sdldata_init.c	\
			src/controls.c		\
			src/menu.c		\
						\
			src/events.c		\
			src/core.c		\
			src/camera_focus.c	\
						\
			src/render.c		\
			src/pos_onscreen.c	\
						\
			src/ship.c		\
			src/ship_move.c		\
			src/ship_recoil.c	\
			src/xship_init.c	\
			src/xship_blit.c	\
			src/xship_move.c	\
			src/xship_move_bases.c	\
			src/xship_shoot.c	\
						\
			src/ammo_push.c		\
			src/ammos_core.c	\
			src/ammos_blit.c	\

OBJ		=	$(SRC:.c=.o)

$(NAME)		:	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all		:	$(NAME)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean $(NAME)

.PHONY		:	all clean fclean re
