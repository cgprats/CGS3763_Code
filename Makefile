build:
	cc Fibonnaci.c -pthread
	cc FileCopy.c
	cc Prime.c -pthread
	cc Stats.c -pthread
	cc StringCaseReverser.c
	cc Zombie.c
	cc -pthread Sorting_Project/main.c
