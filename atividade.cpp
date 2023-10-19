#include <iostream>
#include <iomanip>

using namespace std;

int somaMenores(int num);
bool bissexto(int ano);
void conversaoBinaria(int num);
bool validarSenha(string senha);
void valorComJuros(double valor, double taxaAnual, int numAnos);
void ordenarVetor(int vetor[], int n);

int main(){
    int n1, numAnos;
    string senha;
    double valor, taxaAnual;
    cout << "Digite um numero: ";
    cin >> n1;
    cout << somaMenores(n1) << endl
        << "Digite um ano: ";
    cin >> n1;
    if (bissexto(n1)){
        cout << "Eh bissexto" << endl;
    }
    else {
        cout << "Nao eh bissexto" << endl;
    }
    cout << "Digite um numero: ";
    cin >> n1;
    conversaoBinaria(n1);
    cout << endl << "Digite uma senha: ";
    cin >> senha;
    if (validarSenha){
        cout << "Senha valida" << endl;
    }
    else {
        cout << "Senha invalida" << endl;
    }
    cout << "Digite o valor inicial do investimento: ";
    cin >> valor;
    cout << "Digite a taxa anual de juros em %: ";
    cin >> taxaAnual;
    cout << "Digite o numero de anos: ";
    cin >> numAnos;
    valorComJuros(valor, taxaAnual, numAnos);
    cout << "Digite o tamanho do vetor: ";
    cin >> n1;
    int vetor[n1];
    cout << "Digite os valor para o vetor: ";
    for (int i = 0; i < n1; i++){
        cin >> vetor[i];
    }
    ordenarVetor(vetor, n1);
}

//1
int somaMenores(int num){
    int s = 0;
    while (num > 0){
        s += num;
        num--;
    }
    return s;
}

//2
bool bissexto(int ano){
    bool ehbissexto;
    if (ano % 4 == 0){
        ehbissexto = true;
    }
    else if (ano % 400){
        ehbissexto = true;
    }
    else {
        ehbissexto = false;
    }
    return ehbissexto;
}

//3
void conversaoBinaria(int num){
    string binario;
    while (num > 0){
        binario += to_string(num % 2);
        num /= 2;
    }
    int i = binario.length();
    while (i >= 0){
        cout << binario[i];
        i--;
    }
}

//4
bool validarSenha(string senha){
    if (senha.length() >= 8){
        bool maiusc = false, minusc = false, num = false;
        for (int i = 0; i < senha.length(); i++){
            if (senha[i] > 64 && senha[i] < 91){
                maiusc = true;
            }
            if (senha[i] > 96 && senha[i] < 123){
                minusc = true;
            }
            if (senha[i] > 47 && senha[i] < 58){
                num = true;
            }
        }
        if (maiusc && minusc && num){
            return true;
        }
    }
    return false;
}

//5
void valorComJuros(double valor, double taxaAnual, int numAnos){
    double valorFinal = valor;
    for (int i = 0; i < numAnos; i++){
        valorFinal += (valorFinal * taxaAnual) / 100;
    }
    cout << "O valor final eh: " << valorFinal << endl;
}

//6
void ordenarVetor(int vetor[], int n){
    int aux;
    for (int i = 0; i < n - 1; i++){
        for (int p = i; p < n; p++){
            if (vetor[i] > vetor[p]){
                aux = vetor[i];
                vetor[i] = vetor[p];
                vetor[p] = aux;
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout << vetor[i] << setw(2);
    }
}