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
		  $(builddir)/exceptions.o

$(builddir)/crab-battle : $(builddir) $(objects) build_resources
	$(CXX) -o $(builddir)/crab-battle $(LDFLAGS) $(objects)

$(builddir) :
	mkdir $(builddir)

build_resources : $(builddir)/images $(builddir)/audio $(builddir)/titles.txt $(builddir)/titles1.txt $(builddir)/icon.png $(builddir)/times.ttf $(builddir)/titles-menu.txt

$(builddir)/%.o : $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(builddir)/BaseObject.o : $(srcdir)/BaseObject.h
$(builddir)/GameState.o : $(srcdir)/GameState.h $(srcdir)/Rect.h $(srcdir)/State.h $(srcdir)/constants.h $(srcdir)/exceptions.h
$(builddir)/main.o : $(srcdir)/State.h $(srcdir)/GameState.h $(srcdir)/Surface.h $(srcdir)/constants.h
$(builddir)/PausedState.o : $(srcdir)/PausedState.h $(srcdir)/Rect.h $(srcdir)/State.h $(srcdir)/constants.h $(srcdir)/exceptions.h
$(builddir)/MenuState.o : $(srcdir)/MenuState.h $(srcdir)/Rect.h $(srcdir)/Player.h $(srcdir)/State.h $(srcdir)/GameState.h $(srcdir)/constants.h
$(builddir)/Rect.o : $(srcdir)/Rect.h $(srcdir)/BaseObject.h
$(builddir)/Sprite.o : $(srcdir)/Sprite.h $(srcdir)/Rect.h $(srcdir)/Surface.h $(srcdir)/constants.h
$(builddir)/State.o : $(srcdir)/State.h $(srcdir)/BaseObject.h $(srcdir)/Surface.h
$(builddir)/Surface.o : $(srcdir)/Surface.h $(srcdir)/BaseObject.h $(srcdir)/Rect.h $(srcdir)/exceptions.h
$(builddir)/Player.o : $(srcdir)/Sprite.h
$(builddir)/exceptions.o : 

$(builddir)/images : $(resdir)/images
	$(CP) -r $(resdir)/images $(builddir)/images
$(builddir)/audio : $(resdir)/audio
	$(CP) -r $(resdir)/audio $(builddir)/audio
$(builddir)/titles.txt : $(resdir)/titles.txt
	$(CP) $(resdir)/titles.txt $(builddir)/titles.txt
$(builddir)/titles1.txt : $(resdir)/titles1.txt
	$(CP) $(resdir)/titles1.txt $(builddir)/titles1.txt
$(builddir)/titles-menu.txt : $(resdir)/titles-menu.txt
	$(CP) $(resdir)/titles-menu.txt $(builddir)/titles-menu.txt
$(builddir)/icon.png : $(resdir)/icon.png
	$(CP) $(resdir)/icon.png $(builddir)/icon.png
$(builddir)/times.ttf : $(resdir)/times.ttf
	$(CP) $(resdir)/times.ttf $(builddir)/times.ttf

.PHONY : clean build_resources
clean :
	$(RM) -r $(builddir)
