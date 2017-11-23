/* arquivo principal do BNB */

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "

using namespace std;

int main() {
	// Registra a funcao que trata o sinal
	signal(SIGINT, interrompe);

	// FAZ ALGO
	return 0;
}
