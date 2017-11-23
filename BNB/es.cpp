#include "es.h"

using namespace std;

void imprime_saida_bnb(std::vector<int> &melhor_solucao, int &custo,
					   int &lim_inf, int &num_nos_exp) {
    // j-esimo inteiro indica o dia de gravacao da cena j!
    for (int j = 0; j < melhor_solucao.size(); j++)
        cout << melhor_solucao[j] << " ";
	cout << endl << custo << endl << lim_inf << endl << num_nos_exp << endl;
}

void imprime_saida_heur(std::vector<int> &melhor_solucao, int &custo) {
    // j-esimo inteiro indica o dia de gravacao da cena j!
    for (int j = 0; j < melhor_solucao.size(); j++)
        cout << melhor_solucao[j] << " ";
	cout << endl << custo << endl;
}

void recebe_entrada(string arquivo, int &m, int &n, vector<vector <int> > &T) {
	int entrada, i, j;

	// abre arquivo e verifica
	ifstream meuArquivo(arquivo, ios::in);
	if (!meuArquivo.is_open()) {
		cout << "Erro na abertura do arquivo" << endl;
		exit(0);
	}

	// ajusta tamanho dos vetores
	T.resize(m);
	for (i = 0; i < m; i++)
		T[i].resize(n);

	// grava valores do arquivo de entrada
    scanf("%d", &entrada);
	m = entrada;
	scanf("%d", &entrada);
	n = entrada;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &entrada);
			T[i][j] = entrada;
		}
	} // fim fors

	meuArquivo.close();
}
