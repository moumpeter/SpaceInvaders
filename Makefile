CC = g++
CCFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lsfml-window -lsfml-graphics -lsfml-system
OBJS = game_main.o state.o game_object.o player.o projectile.o

game: $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.cc %.h
	$(CC) $(CCFLAGS) -c $<

.PHONY: clean
clean:
	rm -f game $(OBJS) *.o