# this Makefile is intended to make any of the examples in this directory
#all:  proto-texture proto-ui proto-ui2 proto-counting proto-windows proto-sound proto-chat proto-multiplayer

# the following lines pertain to using sound
# if you download FMOD onto your own machine, change the line below
FMOD_DIR = /usr/local/dept/apps/fmod
FMOD_INCLUDE = -I$(FMOD_DIR)/api/inc -I$(FMOD_DIR)/examples/common
FMOD_LIB = $(FMOD_DIR)/api/lib/libfmodex64.so

# the following lines pertain to setting up compiler options and libraries
OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

main: main.o texture.o pokemon.o tower.o minion.o projectile.o wave.o trainer.o button.o FloatingText.o
	g++ $(OPTS) -std=c++11 -o main main.o texture.o pokemon.o projectile.o tower.o minion.o wave.o trainer.o button.o FloatingText.o $(LIBS)

main.o: main.cpp menu.h game.h defeat.h victory.h help.h button.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c main.cpp

texture.o: texture.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c texture.cpp

pokemon.o: pokemon.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c pokemon.cpp

tower.o: tower.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c tower.cpp

minion.o: minion.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c minion.cpp

projectile.o: projectile.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c projectile.cpp

wave.o: wave.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c wave.cpp

trainer.o: trainer.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c trainer.cpp

button.o: button.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c button.cpp
FloatingText.o: FloatingText.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c FloatingText.cpp
