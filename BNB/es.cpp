#include "es.h"

using namespace std;

void imprime_saida_bnb(std::vector<int> &melhor_solucao, int &custo,
					   int &lim_inf, int &num_nos_exp) {
    // j-esimo inteiro indica o dia de gravacao da cena j!
    for (int j = 0; j < melhor_solucao.size(); j++)
        cout << melhor_solucao[j] << " ";
	// linha nao dita no enunciado?
	cout << endl << custo << endl << lim_inf << endl << num_nos_exp << endl;
}

void imprime_saida_heur(std::vector<int> &melhor_solucao, int &custo) {
    // j-esimo inteiro indica o dia de gravacao da cena j!
    for (int j = 0; j < melhor_solucao.size(); j++)
        cout << melhor_solucao[j] << " ";
	cout << endl << custo << endl;
}

void recebe_entrada(const string arquivo, int &m, int &n, vector<vector <int> > &T) {
	int entrada, i, j;
	ifstream meuArquivo;
	
	// abre arquivo e verifica
	meuArquivo.open(arquivo.c_str());

	cout << arquivo.c_str() << endl << m << endl << n << endl;
	
	if (!meuArquivo.is_open() || !meuArquivo.good()) {
		cout << "Erro na abertura do arquivo" << endl;
		exit(0);
	}
	
	// ajusta tamanho dos vetores
	T.resize(m);
	for (i = 0; i < m; i++)
		T[i].resize(n);

	// grava valores do arquivo de entrada
    if(scanf("%d", &entrada))
		m = entrada;
	if(scanf("%d", &entrada))
		n = entrada;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if(scanf("%d", &entrada))
				T[i][j] = entrada;
		}
	} // fim fors

	cout << m << endl << n << endl;

	meuArquivo.close();
}
