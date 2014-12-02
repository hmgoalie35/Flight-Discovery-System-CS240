FLAGS = -g -Wall -std=c++11
Assignment = "_Lab8.tar.gz"
Branch = "master"
Conor = "Cunningham_Conor$(Assignment)"
Harris = "Pittinsky_Harris$(Assignment)"
Evan = "Young_Evan$(Assignment)"

all:	Main

Main:	clean Date.o time.o timeLength.o graph.o main.o
	g++ Date.o time.o timeLength.o graph.o main.o -o fly

Date.o:	Date.cpp
	g++ $(FLAGS) -c Date.cpp -o Date.o

graph.o:	graph.cpp
	g++ $(FLAGS) -c graph.cpp -o graph.o

time.o:	time.cpp
		g++ $(FLAGS) -c time.cpp -o time.o

timeLength.o:	timeLength.cpp
		g++ $(FLAGS) -c timeLength.cpp -o timeLength.o

main.o:	fly.cpp
	g++ $(FLAGS) -c fly.cpp -o main.o

harris:	clean
	git archive $(Branch) --format=tar.gz -5 --output $(Harris)

conor:	clean
	git archive $(Branch) --format=tar.gz -5 --output $(Conor)

evan:	clean
	git archive $(Branch) --format=tar.gz -5 --output $(Evan)

clean:
	rm -f *.o *.exe fly