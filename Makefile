# CC is for the compilier I am using and CXXFLAGS is for the defintion of what else I want with the compile  cd actions && $(MAKE)
CC = g++
CXXFLAGS = -Wall -Wextra -pedantic

objects = Pathfinder.o Character.o Dice.o Weapon.o Armor.o combat_System.o actions/strike.o

Pathfinder: $(objects)
	cd actions && $(MAKE)
	$(CC) $(CFLAGS) -o Pathfinder $(objects)

Character.o: Character.cpp Character.h
	$(CC) $(CFLAGS) -c Character.cpp

combat_System.o: combat_System.cpp combat_System.h
	$(CC) $(CFLAGS) -c combat_System.cpp

Dice.o: Dice.cpp Dice.h
	$(CC) $(CFLAGS) -c Dice.cpp

Armor.o: Armor.cpp Armor.h Dice.h
	$(CC) $(CFLAGS) -c Armor.cpp

Weapon.o: Weapon.cpp Dice.h Weapon.h
	$(CC) $(CFLAGS) -c Weapon.cpp

.PHONY : clean
clean:
	cd actions && del *.o
	del *.o