// main.cpp
// Author: Claudia Izeki

#include<iostream>
#include "Pilha.cpp"
using namespace std;

bool ehOperando(int ch)
{
	return ch >= 'A' && ch <= 'Z';
}
bool ehOperador(int ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int main()
{
	setlocale(LC_ALL, "Portuguese");

	int quant, i = 0;
	float* valor;
	char letra;
	char expressao[30];

	cout << "...NOTAÇÃO POLONESA REVERSA...\n\n";

	Pilha<float>* p1 = new Pilha<float>();

	cout << "Quantos operandos? ";
	cin >> quant;
	valor = new float[quant];

	for (int i = 0; i < quant; i++)
	{
		letra = 'A' + i;
		cout << "Qual o valor de " << letra << ": ";
		cin >> valor[i];
	}
	
	cout << "Entre com a expressão: ";
	cin.ignore(); //fflush(stdin);
	cin.getline(expressao, 30);

	/////////////////////////////////////////////////////
	// Algoritmo da notação polonesa aqui!
	while (expressao[i] != '\0') {
		if (ehOperando(expressao[i])) {
			p1->empilha(valor[expressao[i] - 'A']);
		}
		else if (expressao[i] == '+') {
			p1->empilha(p1->desempilha() + p1->desempilha());
			cout << "Res: " << p1->valorTopo() << endl;
		}
		else if (expressao[i] == '-') {
			p1->empilha(-p1->desempilha() + p1->desempilha());
			cout << "Res: " << p1->valorTopo() << endl;
		}
		else if (expressao[i] == '*') {
			p1->empilha(p1->desempilha() * p1->desempilha());
			cout << "Res: " << p1->valorTopo() << endl;
		}
		else if (expressao[i] == '/') {
			p1->empilha(1 / p1->desempilha() * p1->desempilha());
			cout << "Res: " << p1->valorTopo() << endl;
		}
		i++;
	}
	
	/////////////////////////////////////////////////////
	// Algoritmo da parentização aqui!
	cout << "-------------------------------------------" << endl << endl
		<< "...PARENTIZAÇÃO..." << endl << endl
		<< "Entre com a expressão: ";
	cin.ignore(); //fflush(stdin);
	cin.getline(expressao, 30);
	char op=0;

	for (int i = 0; expressao[i] != '\0'; i++) { //((A+B)*C)
		if (ehOperando(expressao[i]))
			p1->empilha(valor[expressao[i] - 'A']);
		else if (ehOperador(expressao[i])) {
			if (expressao[i] == '+')
				op = '+';
			else if (expressao[i] == '-')
				op = '-';
			else if (expressao[i] == '*')
				op = '*';
			else if (expressao[i] == '/')
				op = '/';
		}
		else if (expressao[i] == ')')
			if (op == '+') {
				p1->empilha(p1->desempilha() + p1->desempilha());
				cout << "Res: " << p1->valorTopo() << endl;
			}
			else if (op == '-') {
				p1->empilha(-p1->desempilha() + p1->desempilha());
				cout << "Res: " << p1->valorTopo() << endl;
			}
			else if (op == '*') {
				p1->empilha(p1->desempilha() * p1->desempilha());
				cout << "Res: " << p1->valorTopo() << endl;
			}
			else if (op == '/') {
				p1->empilha(1 / p1->desempilha() * p1->desempilha());
				cout << "Res: " << p1->valorTopo() << endl;
			}
	}

	delete[]valor;
	delete p1;

	return 0;
}