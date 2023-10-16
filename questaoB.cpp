#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//1
bool multi4(int num){
    return ((num % 4) == 0? true : false);
}

//2
int parOuImpar(int num){
    return ((num % 2) == 0? 1 : 0);
}

//3
int somaIntervalo(int n1, int n2){
    int soma = 0;
    while (n1 <= n2){
        soma += n1;
        n1++;
    }
    return soma;
}

//4
double calcVolume(double raio){
    return (4 * M_PI * (raio * raio * raio)) / 3;
}

//5
int fatorial(int num){
    int fator = 1;
    while (num > 0){
        fator *= num;
        num--;
    }
    return fator;
}

//6
int potencia(int base, int exp){
    int  result = base;
    for (int i = 1; i < exp; i++){
        result *= base;
    }
    return result;
}

int main(){
    int n1, n2;
    double raio;
    cin >> n1;
    if (multi4(n1)){
        cout << "Eh multiplo de 4" << endl;
    }
    else {
        cout << "Nao eh multiplo de 4" << endl;
    }
    cin >> n1;
    if (parOuImpar(n1) == 1){
        cout << "Par" << endl;
    }
    else {
        cout << "Impar" << endl;
    }
    cin >> n1 >> n2;
    cout << "Soma do intervalo: " << somaIntervalo(n1, n2) << endl;
    cin >> n1;
    cout << fixed << setprecision(4) << "Volume: " << calcVolume(n1) << endl;
    cin >> n1;
    cout << "Fatorial: " << fatorial(n1) << endl;
    cin >> n1 >> n2;
    cout << "Potencia: " << potencia(n1, n2) << endl;

    return 0;
}
