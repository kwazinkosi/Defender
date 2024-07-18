# Compiler
CC = g++

# Compiler flags
CFLAGS = -IC:\Libraries\SFML-2.6.1\include

# Linker flags
LDFLAGS = -LC:\Libraries\SFML-2.6.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files
SOURCES = main.cpp Game.cpp Player.cpp StateStack.cpp State.cpp GameState.cpp SplashState.cpp MainMenuState.cpp TextFormater.cpp Collidable.cpp PauseState.cpp
HEADERS = Game.hpp Player.hpp StateStack.hpp State.hpp GameState.hpp SplashState.hpp MainMenuState.hpp TextFormater.hpp Collidable.hpp PauseState.hpp

# Object files (place them in the OBJDIR)
OBJDIR = objects
OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

# Executable name
EXECUTABLE = main.exe

# Default rule
all: compile link

# Compile source files into object files
compile: $(OBJECTS)

$(OBJDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Link object files into executable
link: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Clean rule
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
