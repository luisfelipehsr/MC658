/* arquivo principal do BNB */
#include <csignal>
#include <vector>
#include <string>

#include "es.h"
#include "bnb.h"

using namespace std;

int main(int argc, char** argv) {
	int m, n;
	vector<vector <int> > T;
	vector<int> salario;
	string entrada;
	
	// Registra a funcao que trata o sinal
	signal(SIGINT, BNB::interrompe);

	// Recebe entrada
	entrada = string(argv[1]);
	recebe_entrada(argv[1], m, n, T, salario);

	// Pode utilizar heuristica aqui. Envolve alterar bnb para aceitar tambem
	// um lower bound inicial na construcao.
	
	// FAZ ALGO
	BNB bnb(m, n, -1, T, salario);
	bnb.run();
	
	return 0;
}
