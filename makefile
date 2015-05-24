# compiler
CXX = g++
OBJDIR = obj
 
SRC = $(wildcard *.cpp)
DEPS = $(wildcard *.hpp)
 
CFLAGS += -std=c++11
CFLAGS += -Wall
CFLAGS += -g
 
LIBS +=-lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lGL
 
# ============================================================================ #
OBJS = $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(SRC)))
 
# targets
main : $(OBJS) | $(BINDIR)
	$(CXX) $(OBJS) $(LIBS) -o $@
 
$(OBJS) : | $(OBJDIR)
$(OBJDIR) : ; mkdir $(OBJDIR)
$(BINDIR) : ; mkdir $(BINDIR)
 
$(OBJDIR)/%.o : %.cpp $(DEPS)
	$(CXX) -c $< $(CFLAGS) -o $@
 
.PHONY: clean
clean :
	rm $(OBJDIR)/*
	rmdir $(OBJDIR)
