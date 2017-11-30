BNB_PATH=/BNB
PLI_PATH=/PLI
HEUR_PATH=/HEUR

bnb: main.cpp bnb.cpp es.cpp
	g++ -std=gnu++03 -O3 main.cpp bnb.cpp es.cpp -o bnb
pli-solver: pli-solver.c
	gcc -O3 pli-solver.c -lglpk -o pli-solver
heur: main.cpp heur.cpp es.cpp
	g++ -std=gnu++03 -O3 main.cpp heur.cpp es.cpp -o heur