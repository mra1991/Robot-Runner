CC = g++
CFLAGS = -Wall -w
PROG = the_game

SRCS = main_main.cpp ../classes/game.cpp ../classes/robot.cpp ../classes/map.cpp ../classes/obstacle.cpp ../classes/environment.cpp ../classes/decorative.cpp ../classes/objHandler.cpp ../glmwithtexture/glm.c ../glmwithtexture/glmimg.c ../glmwithtexture/glm_util.c ../glmwithtexture/glmimg_jpg.c

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGL -lGLU -ljpeg
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)

