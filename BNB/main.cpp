/* arquivo principal do BNB */
#include "bnb.h"

using namespace std;

int main(int argc, char** argv) {
	int m, n;
	vector<vector <int> > T;
	string entrada;
	
	// Registra a funcao que trata o sinal
	signal(SIGINT, interrompe);

	// Recebe entrada
	entrada = string(argv[1]);
	recebe_entrada(argv[1], m, n, T);

	// FAZ ALGO
	BNB bnb(m, n, T);
	bnb.run();
	
	return 0;
}
