#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//1
void multi4(){
    int num;
    cin >> num;
    cout << ((num % 4) == 0? "Eh multiplo de 4" : "Nao eh multiplo de 4") << endl;
}

//2
void parOuImpar(){
    int num;
    cin >> num;
    cout << ((num % 2) == 0? "Par" : "Impar") << endl;
}

//3
void somaIntervalo(){
    int n1, n2, soma = 0;
    cin >> n1 >> n2;
    while (n1 <= n2){
        soma += n1;
        n1++;
    }
    cout << soma << endl;
}

//4
void calcVolume(){
    double raio;
    cin >> raio;
    cout << fixed << setprecision(4) << (4 * M_PI * (raio * raio * raio)) / 3 << endl;
}

//5
void fatorial(){
    int num, fator = 1;
    cin >> num;
    while (num > 0){
        fator *= num;
        num--;
    }
    cout << fator << endl;
}

//6
void potencia(){
    int base, exp;
    cin >> base >> exp;
    int  result = base;
    for (int i = 1; i < exp; i++){
        result *= base;
    }
    cout << result;
}

int main(){
    multi4();
    parOuImpar();
    somaIntervalo();
    calcVolume();
    fatorial();
    potencia();
    
    return 0;
}
