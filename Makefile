CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl2-config --cflags` -g  -std=c++11  -pedantic -O0 -I `sdl2-config --prefix`/include/

LDFLAGS = `sdl2-config --libs` -lm -lexpat -lSDL2_ttf -lSDL2_image

OBJS = \
  renderContext.o \
	ioMod.o \
	parseXML.o \
	gameData.o \
	viewport.o \
	BackGround.o \
	spriteSheet.o \
	image.o \
	imageFactory.o \
	frameGenerator.o \
	sprite.o \
	multisprite.o \
	AngularSprite.o \
	twowaysprite.o \
	vector2f.o \
	clock.o \
	engine.o \
	main.o
EXEC = run

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
	rm -rf frames/*.bmp
