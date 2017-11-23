/* arquivo principal do BNB */
#include "BNB.h"

int main() {
	int m, int n;
	vector<vector <int> > T;
	
	// Registra a funcao que trata o sinal
	signal(SIGINT, interrompe);

	// Recebe entrada
	recebe_entrada(argv[2], m, n, T);

	// FAZ ALGO
	
	return 0;
}
