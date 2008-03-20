# make file

# TOOLS
CP = /bin/cp

LDFLAGS += -lSDL -lSDL_image -ggdb
CPPFLAGS += -I/usr/include/SDL

srcdir = src
resdir = Resources
builddir = build

objects = $(builddir)/BaseObject.o \
		  $(builddir)/GameState.o \
		  $(builddir)/main.o \
		  $(builddir)/Rect.o \
		  $(builddir)/Sprite.o \
		  $(builddir)/State.o \
		  $(builddir)/Surface.o

$(builddir)/crab-battle : $(builddir) $(objects) $(builddir)/images
	$(CXX) -o $(builddir)/crab-battle $(LDFLAGS) $(objects)

$(builddir) :
	mkdir $(builddir)

$(builddir)/%.o : $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(builddir)/BaseObject.o : $(srcdir)/BaseObject.h
$(builddir)/GameState.o : $(srcdir)/GameState.h $(srcdir)/Rect.h $(srcdir)/State.h $(srcdir)/constants.h
$(builddir)/main.o : $(srcdir)/State.h $(srcdir)/GameState.h $(srcdir)/Surface.h $(srcdir)/constants.h
$(builddir)/Rect.o : $(srcdir)/Rect.h $(srcdir)/BaseObject.h
$(builddir)/Sprite.o : $(srcdir)/Sprite.h $(srcdir)/Rect.h $(srcdir)/Surface.h
$(builddir)/State.o : $(srcdir)/State.h $(srcdir)/BaseObject.h $(srcdir)/Surface.h
$(builddir)/Surface.o : $(srcdir)/Surface.h $(srcdir)/BaseObject.h $(srcdir)/Rect.h

$(builddir)/images : $(resdir)/images
	$(CP) -r $(resdir)/images $(builddir)/images

.PHONY : clean
clean :
	$(RM) -r $(builddir)
