# make file

# TOOLS
CP = /bin/cp

LDFLAGS += -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lode -ggdb
CPPFLAGS += -I/usr/include/SDL

srcdir = src
resdir = Resources
builddir = build

objects = $(builddir)/BaseObject.o \
		  $(builddir)/GameState.o \
		  $(builddir)/MenuState.o \
		  $(builddir)/main.o \
		  $(builddir)/PausedState.o \
		  $(builddir)/Rect.o \
		  $(builddir)/Sprite.o \
		  $(builddir)/State.o \
		  $(builddir)/Surface.o \
		  $(builddir)/Player.o \
		  $(builddir)/PlayerSelect.o \
		  $(builddir)/SoundEffect.o \
		  $(builddir)/exceptions.o \
		  $(builddir)/util.o \
		  $(builddir)/VictoryScreen.o

$(builddir)/crab-battle : $(builddir) $(objects) build_resources
	$(CXX) -o $(builddir)/crab-battle $(LDFLAGS) $(objects)

$(builddir) :
	mkdir $(builddir)

build_resources : $(builddir)/images $(builddir)/audio $(builddir)/game-paths.txt $(builddir)/pause-paths.txt $(builddir)/icon.png $(builddir)/times.ttf $(builddir)/menu-paths.txt $(builddir)/platforms.txt $(builddir)/players.txt $(builddir)/pselect-paths.txt

$(builddir)/%.o : $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(builddir)/BaseObject.o : $(srcdir)/BaseObject.h
$(builddir)/GameState.o : $(srcdir)/GameState.h $(srcdir)/Rect.h $(srcdir)/State.h $(srcdir)/constants.h $(srcdir)/exceptions.h $(srcdir)/Player.h $(srcdir)/PausedState.h $(srcdir)/util.h $(srcdir)/VictoryScreen.h $(srcdir)/Surface.h
$(builddir)/main.o : $(srcdir)/State.h $(srcdir)/Surface.h $(srcdir)/constants.h $(srcdir)/MenuState.h
$(builddir)/MenuState.o : $(srcdir)/MenuState.h $(srcdir)/Rect.h $(srcdir)/Player.h $(srcdir)/State.h $(srcdir)/PlayerSelect.h $(srcdir)/constants.h $(srcdir)/exceptions.h $(srcdir)/util.h
$(builddir)/PausedState.o : $(srcdir)/PausedState.h $(srcdir)/State.h $(srcdir)/constants.h $(srcdir)/exceptions.h $(srcdir)/Surface.h
$(builddir)/Player.o : $(srcdir)/Sprite.h $(srcdir)/Player.h
$(builddir)/PlayerSelect.o : $(srcdir)/PlayerSelect.h $(srcdir)/util.h $(srcdir)/Surface.h $(srcdir)/State.h $(srcdir)/constants.h $(srcdir)/GameState.h
$(builddir)/Rect.o : $(srcdir)/Rect.h $(srcdir)/BaseObject.h
$(builddir)/Sprite.o : $(srcdir)/BaseObject.h $(srcdir)/Sprite.h $(srcdir)/Rect.h $(srcdir)/Surface.h $(srcdir)/constants.h
$(builddir)/State.o : $(srcdir)/State.h $(srcdir)/BaseObject.h $(srcdir)/Surface.h
$(builddir)/Surface.o : $(srcdir)/Surface.h $(srcdir)/BaseObject.h $(srcdir)/Rect.h $(srcdir)/exceptions.h
$(builddir)/SoundEffect.o : $(srcdir)/BaseObject.h $(srcdir)/exceptions.h
$(builddir)/exceptions.o : $(srcdir)/exceptions.h
$(builddir)/util.o : $(srcdir)/util.h $(srcdir)/exceptions.h
$(builddir)/VictoryScreen.o : $(srcdir)/Surface.h $(srcdir)/State.h

$(builddir)/images : $(resdir)/images
	$(CP) -r $(resdir)/images $(builddir)/images
$(builddir)/audio : $(resdir)/audio
	$(CP) -r $(resdir)/audio $(builddir)/audio
$(builddir)/game-paths.txt : $(resdir)/game-paths.txt
	$(CP) $(resdir)/game-paths.txt $(builddir)/game-paths.txt
$(builddir)/pause-paths.txt : $(resdir)/pause-paths.txt
	$(CP) $(resdir)/pause-paths.txt $(builddir)/pause-paths.txt
$(builddir)/menu-paths.txt : $(resdir)/menu-paths.txt
	$(CP) $(resdir)/menu-paths.txt $(builddir)/menu-paths.txt
$(builddir)/platforms.txt : $(resdir)/platforms.txt
	$(CP) $(resdir)/platforms.txt $(builddir)/platforms.txt
$(builddir)/players.txt : $(resdir)/players.txt
	$(CP) $(resdir)/players.txt $(builddir)/players.txt
$(builddir)/pselect-paths.txt : $(resdir)/pselect-paths.txt
	$(CP) $(resdir)/pselect-paths.txt $(builddir)/pselect-paths.txt
$(builddir)/icon.png : $(resdir)/icon.png
	$(CP) $(resdir)/icon.png $(builddir)/icon.png
$(builddir)/times.ttf : $(resdir)/times.ttf
	$(CP) $(resdir)/times.ttf $(builddir)/times.ttf

.PHONY : clean build_resources
clean :
	$(RM) -r $(builddir)
