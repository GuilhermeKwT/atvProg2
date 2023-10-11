#include <iostream>
#include <ctime> //Necessário para conseguir o tempo para calcular duração da partida e para definir a seed para o valores randomicos
#include <conio.h> //Necessário para ler as teclas pressionadas no teclado
#include <unistd.h> //Necessário para usar a função sleep e usleep
#include <windows.h> //Necessário para usar a função Beep para reproduzir um som quando é movido o cursor no menu

#define A 25 //Define a altura do quadro de jogo
#define L 7 //Define a largura do quadro de jogo
 
using namespace std;

/*
Essa versão, em teoria, roda em qualquer máquina windows moderna, sendo incerto se vai executar em outros sistemas operacionais.
Porém, há uma segunda versão comentada no fim do código, com essa segunda versão possuindo pequenas alterações, que permite que a tela do jogo não fique piscando
mas devido a tag usada para limpar o terminal, muitos terminais não reconhecem ela, fazendo com que o terminal não seja apagado antes de escrever uma nova imagem. 
*/

char area[A][L] = {}; //Matriz utilizada para posicionar e movimentar as estrelas e o cursor do player durante o jogo
int goal, pts, locPlayer, status, menuPos, mode, difLvl, startTime, topModes[8] = {INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, 0, 0, 0, 0};

// Define se uma estrela será gerada e se sim, onde ela vai ficar na matriz
void stars(){
    int RNG, value;

    if (mode == 2){ //É diferente entre os modos pois no Dificil tem que gerar mais meteoros no modo 2 e menos estrelas no modo 1
        value = difLvl * 2.5;
    }
    else {
        value = (0.5 / difLvl) * 10; 
    }
    RNG = rand()%value;
    if (RNG == 0){
        area[0][rand()%L] = '*';
    }
}

//Faz a movimentação das estrelas e a verificação da colisão com o Player
void starMovement(){
    int i = A - 1;

    while (i >= 0){
        for (int p = 0; p < L; p++){
            if (area[i][p] == '*'){
                if (i == A - 2 && p == locPlayer){ //Verificação de colisão
                    area[i][p] = ' ';
                    if (mode == 1){
                        pts++;
                    }
                    else if (mode == 2) {
                        pts--;
                    }  
                }
                else if ((i + 1) >= A){ //Verificação de se está na ultima linha
                    area[i][p] = ' ';
                }
                else {
                    area[i + 1][p] = '*'; //Movimento
                    area[i][p] = ' ';
                }
            }
        }
        i--;
    }
}

//Faz o movimento do player
void playerControl(){
    int key, menuSize;

    if (status == 0){ //Significa que está ocorrendo uma partida 
        if(_kbhit()){ //Movimento no jogo
            key = getch();
            switch(key){
                case 27: //Tecla esc
                    status = -1; //Encerra a execução do jogo
                    break;
                case 97: //Tecla a
                case 65: //Tecla A
                case 75: //Seta à esquerda
                    if (locPlayer > 0){
                        area[A - 1][locPlayer] = ' ';
                        locPlayer--;
                        area[A - 1][locPlayer] = '^';
                    }
                    break;
                case 100: //Tecla d
                case 68: //Tecla D
                case 77: //Seta à direita
                    if (locPlayer < (L - 1)){
                        area[A - 1][locPlayer] = ' ';
                        locPlayer++;
                        area[A - 1][locPlayer] = '^';
                    }
            }
        }
    }
    else {
        switch (status){
        case 1: //Menu inicial
            menuSize = 2; 
            break;
        case 2: //Menu de modos
            menuSize = 2;
            break;
        case 3: //Menu de dificuldade
            menuSize = 3;
            break;
        case 4: //Tela de seleção de objetivo
            menuSize = 1;
        }
        if(_kbhit()){ //Movimento pelo menu
            key = getch();
            switch(key){
                case 119: //Tecla w
                case 87: //Tecla W
                case 72: //Seta para cima
                    if (menuPos > 1){
                        Beep(850, 130); //Reproduz um som, onde o primeiro valor é a frequência e o segundo é o tempo de reprodução
                        menuPos--;
                    }
                    break;
                case 115: //Tecla s 
                case 83: //Tecla S
                case 80: //Seta para baixo
                    if (menuPos < menuSize){
                        Beep(850, 120);
                        menuPos++;
                    }
                    break;
                case 8: //Tecla backspace
                    if (status > 1){
                        Beep(600, 160);
                        status--;
                    }
                    break;
                case 27: //Tecla esc
                    status = -1;
                    break;
                case 13: //Tecla enter
                    Beep(750, 140);
                    switch (status){
                    case 1:
                        if (menuPos == 1){ //Botão de início
                            menuPos = 1;
                            status = 2;
                        }
                        else if(menuPos == 2){ //Botão de sair
                            status = -1;
                        }
                        break;
                    case 2:
                        if (menuPos == 1){
                            mode = 1; //Modo: coleta de estrelas
                        }
                        else if(menuPos == 2){
                            mode = 2; //Modo: chuva de meteoros
                        }
                        menuPos = 1;
                        status = 3;
                        break;
                    case 3:
                        if (menuPos == 1){
                            difLvl = 3; //Facil
                        }
                        else if (menuPos == 2){
                            difLvl = 2; //Médio
                        }
                        else {
                            difLvl = 1; //Difícil
                        }
                        menuPos = 1;
                        if (mode == 1){ //É usado pois só existe seleção de objetivo no modo 1
                            status = 4;
                        }
                        else {
                            status = 0;
                        }
                        break;
                }
            }
        }
    }
}

//Telas do menu
void menuScreen(){
    string menu;
    boolean valid = false;
    menu.clear();

    playerControl();
    switch (status){ //Define qual menu deve ser mostrado
    case 1: //Tela do menu principal
        menu = "\n\033[1m"; //Códigos de escape ANSI, utilizados para formatar a saída de um terminal de texto, mudando coisas como cor do texto, negrito, etc.
        menu = menu + (menuPos == 1 ? "\033[34m>\033[36m " : "  \033[39m") + "Iniciar Jogo" + "\n" + (menuPos == 2 ? "\033[34m>\033[36m " : "  \033[39m") + "Sair" 
        + "\033[22m" + "\033[0m" + "\n";
        system("cls");
        cout << menu;
        break;
    case 2: //Tela de seleção do modo
        menu = menu + "\n" + "\033[1m" + "Modo:" + "\033[0m" + "\n" + (menuPos == 1 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Coleta de Estrelas" 
        + "\n"  + (menuPos == 2 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Chuva de Meteoros"  + "\033[0m" + "\n";
        system("cls");
        cout << menu;
        break;
    case 3: //Tela de seleção de dificuldade 
        menu = menu + "\n" + "\033[1m" + "Dificuldade:" + "\033[0m" + "\n" 
         + (menuPos == 1 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Facil" + "\n"
         + (menuPos == 2 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Medio" + "\n"
         + (menuPos == 3 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Dificil" + "\033[0m" + "\n";
        system("cls");
        cout << menu;
        break;
    case 4: //Tela para a seleção de objetivo para o modo de coleta
        system("cls");
        cout << "\n" << "\n" << "\033[1m" << "  Digite o Objetivo:  " << "\033[22m";
            while (!valid){ //Garante que um valor inteiro foi inserido
                if (cin >> goal){
                    valid = true;
                }
                else {
                    cin.clear();
                    cin.ignore(99999, '\n');
                }
                
            }
        status = 0;
    }
    
}   

// Monta e escreve o frame da partida
int image(){

    int currentTime = time(NULL);
    string frame, color;
    frame.clear();

    if (mode == 2){
        frame = "\033[1m\033[31m" + to_string(pts) + "/" + to_string(goal) + "\033[39m" + " Vidas" + "   Tempo: " + to_string(currentTime - startTime) + "s\033[22m\n//";
        color = "\033[31m";
    }
    else {
        frame = "\033[1m\033[33m" + to_string(pts) + "/" + to_string(goal) + "\033[39m" + " pontos" + "   Tempo: " + to_string(currentTime - startTime) + "s\033[22m\n//";
        color = "\033[33m";
    }
    for (int i = 0; i < (L * 2) + 1; i++){
        frame += '=';
    }
    frame += "\\\\ \n";
     for (int i = 0; i < A; i++){
        frame += "|| \033[1m" + color;
        for (int p = 0; p < L; p++){
            frame += area[i][p];
            frame += " ";
        }
        frame += "\033[0m||\n";
    }
    frame += "\\\\";
    for (int i = 0; i < (L * 2) + 1; i++){
        frame += '=';
    }
    frame += "//";
    system("cls");
    cout << frame;
    
    return (currentTime - startTime);
}

//Faz a execução do jogo enquanto está ocorrendo uma partida
int game(int speed){
    int finalTime;
    for (int i = 0; i < A; i++){
            for (int p = 0; p < L; p++){
                area[i][p] = ' ';
            }
    }
    area[A - 1][locPlayer] = '^';
    while ((mode == 1 ? pts < goal : pts > 0) && status != -1){ //Execução do jogo
        playerControl();
        starMovement();
        stars();
        finalTime = image();
        usleep(speed);
        if (speed > 50000){
            speed -= 90;
        }
        else if (speed > 11000){
            speed -= 45;
        }
    }
    return finalTime;
}

//Posiciona os top 3 tempos de cada modo em um vetor e escreve-os na tela
void top3(int finalTime){
    int n = 0;

    if (mode == 2){
        n = 4; //Utilizado para localizar os tempos do modo correto no vetor topModes
    }
    int i = 1 + n;
    while (i < 4 + n && finalTime != topModes[i - 1]){
        if ((mode == 1 ? finalTime < topModes[1 + n] : finalTime > topModes[1 + n])) {
            topModes[3 + n] = topModes[2 + n];
            topModes[2 + n] = topModes[1 + n];
            topModes[1 + n] = finalTime;
        } else if (finalTime > topModes[2 + n]) {
            topModes[3 + n] = topModes[2 + n];
            topModes[2 + n] = finalTime;
        } else if (finalTime > topModes[3 + n]) {
            topModes[3 + n] = finalTime;
        }
        i++;
    }
    for (int i = 1; i < 4; i++){
        if (topModes[i + n] == INT16_MAX){
            cout << i << " = ---" << endl;
        }
        else {
            cout << i << " = " << topModes[i + n] << "s" << endl;
        }  
    }
}

int main() {
    int speed, finalTime;
    char conti;
    string name;
    bool run = true;

    while (run){
        pts = 0; 
        locPlayer = (L / 2);
        status = 1;
        menuPos = 1;
        system("cls"); //É necessário para garantir que as tags funcionem corretamente
        while (status != 0 && status != -1){
            menuScreen();
            usleep(60000);
        }
        speed = (difLvl * 50000) + 50000;
        srand(time(NULL));
        system("cls");
        startTime = time(NULL); //Utilizado para determinar o tempo de duração da partida em segundos
        if (mode == 2){ //Vidas para o modo de desviar dos meteoros
            goal = 3;
            pts = 3;
        }
        finalTime = game(speed);
        system("cls");
        if (status != -1){
            cout << endl << endl << endl << "\033[1m" <<  "          Fim de Jogo" << endl << endl << endl 
            << "      Seu tempo foi: " << finalTime << " segundos" << endl << endl << "Top 3 do modo:" << endl;
            top3(finalTime);
            cout << endl << endl << "      Quer Continuar? (S/N)  " << "\033[0m";
            conti = ' ';
            while (conti != 'S' && conti != 'N'){
                cin >> conti;
            }
            cin.get();
        }
        if (conti == 'N' || status == -1){
            run = false;
        }
    }
    system("cls");
    cout << endl << endl << endl << "\033[1m" << "        Obrigado por Jogar " << "\033[31m" << "<3" << "\033[0m" << endl << endl << endl;
    sleep(1);

    return 0;
}

/*
#include <iostream>
#include <ctime> //Necessário para conseguir o tempo para contar o tempo de partida e para definir a seed para o valores randomicos
#include <conio.h> //Necessário para ler as teclas pressionadas no teclado
#include <unistd.h> //Necessário para usar a função sleep e usleep
#include <windows.h> //Necessário para usar a função Beep para reproduzir um som quando é movido o cursor

#define A 25 //Define a altura do quadro
#define L 7 //Define a largura do quadro
 
using namespace std;

char area[A][L] = {};
int goal, pts, locPlayer, status, menuPos, mode, difLvl, startTime, topModes[8] = {INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, 0, 0, 0, 0};

// Define se uma estrela será gerada e se sim, onde ela vai ficar na matriz
void stars(){
    int RNG, value;

    if (mode == 2){ //É diferente entre os modos pois no Dificil tem que gerar mais meteoros no modo 2 e menos estrelas no modo 1
        value = difLvl * 2.5;
    }
    else {
        value = (0.5 / difLvl) * 10; 
    }
    RNG = rand()%value;
    if (RNG == 0){
        area[0][rand()%L] = '*';
    }
}

//Faz a movimentação das estrelas e a verificação da colisão com o Player
void starMovement(){
    int i = A - 1;

    while (i >= 0){
        for (int p = 0; p < L; p++){
            if (area[i][p] == '*'){
                if (i == A - 2 && p == locPlayer){ //Verificação de colisão
                    area[i][p] = ' ';
                    if (mode == 1){
                        pts++;
                    }
                    else if (mode == 2) {
                        pts--;
                    }  
                }
                else if ((i + 1) >= A){ //Verificação de se está na ultima linha
                    area[i][p] = ' ';
                }
                else {
                    area[i + 1][p] = '*'; //Movimento
                    area[i][p] = ' ';
                }
            }
        }
        i--;
    }
}

//Faz o movimento do player
void playerControl(){
    int key, menuSize;

    if (status == 0){ //Significa que está ocorrendo uma partida 
        if(_kbhit()){ //Movimento no jogo
            key = getch();
            switch(key){
                case 97: //Tecla A
                case 75: //Seta à esquerda
                    if (locPlayer > 0){
                        area[A - 1][locPlayer] = ' ';
                        locPlayer--;
                        area[A - 1][locPlayer] = '^';
                    }
                    break;
                case 100: //Tecla D
                case 77: //Seta à direita
                    if (locPlayer < (L - 1)){
                        area[A - 1][locPlayer] = ' ';
                        locPlayer++;
                        area[A - 1][locPlayer] = '^';
                    }
                    break;
            }
        }
    }
    else {
        switch (status){
        case 1: //Menu inicial
            menuSize = 2; 
            break;
        case 2: //Menu de modos
            menuSize = 2;
            break;
        case 3: //Menu de dificuldade
            menuSize = 3;
            break;
        case 4: //Tela de seleção de objetivo
            menuSize = 1;
        }
        if(_kbhit()){ //Movimento pelo menu
            key = getch();
            switch(key){
                case 119: //Tecla W
                case 72: //Seta para cima
                    if (menuPos > 1){
                        Beep(850, 130); //Reproduz um som, onde o primeiro valor é a frequência e o segundo é o tempo de reprodução
                        menuPos--;
                    }
                    break;
                case 115: //Tecla S
                case 80: //Seta para baixo
                    if (menuPos < menuSize){
                        Beep(850, 120);
                        menuPos++;
                    }
                    break;
                case 8: //Tecla backspace
                    if (status > 1){
                        Beep(600, 160);
                        status--;
                    }
                    break;
                case 13: //Tecla enter
                    Beep(750, 140);
                    switch (status){
                    case 1:
                        if (menuPos == 1){ //Botão de início
                            menuPos = 1;
                            status = 2;
                        }
                        else if(menuPos == 2){ //Botão de sair
                            status = -1;
                        }
                        break;
                    case 2:
                        if (menuPos == 1){
                            mode = 1; //Modo: coleta de estrelas
                        }
                        else if(menuPos == 2){
                            mode = 2; //Modo: chuva de meteoros
                        }
                        menuPos = 1;
                        status = 3;
                        break;
                    case 3:
                        if (menuPos == 1){
                            difLvl = 3; //Facil
                        }
                        else if (menuPos == 2){
                            difLvl = 2; //Médio
                        }
                        else {
                            difLvl = 1; //Difícil
                        }
                        menuPos = 1;
                        if (mode == 1){ //É usado pois só existe seleção de objetivo no modo 1
                            status = 4;
                        }
                        else {
                            status = 0;
                        }
                        break;
                }
            }
        }
    }
}

//Telas do menu
void menuScreen(){
    string menu;
    menu.clear();

    playerControl();
    switch (status){ //Define qual menu deve ser mostrado
    case 1:
        menu = "\n\033[1m"; //Códigos de escape ANSI, utilizados para dar formato à saída de um terminal de texto, mudando coisas como cor do texto, negrito, etc.
        menu = menu + (menuPos == 1 ? "\033[34m>\033[36m " : "  \033[39m") + "Iniciar Jogo" + "\n" + (menuPos == 2 ? "\033[34m>\033[36m " : "  \033[39m") + "Sair" 
        + "\033[22m" + "\033[0m" + "\n";
        menu = "\033[2J\033[H" + menu; //Tag que limpa a tela, que causa menos flickering na imagem
        cout << menu;
        break;
    case 2:
        menu = menu + "\n" + "\033[1m" + "Modo:" + "\033[0m" + "\n" + (menuPos == 1 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Coleta de Estrelas" 
        + "\n"  + (menuPos == 2 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Chuva de Meteoros"  + "\033[0m" + "\n";
        menu = "\033[2J\033[H" + menu;
        cout << menu;
        break;
    case 3:
        menu = menu + "\n" + "\033[1m" + "Dificuldade:" + "\033[0m" + "\n" 
         + (menuPos == 1 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Facil" + "\n"
         + (menuPos == 2 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Medio" + "\n"
         + (menuPos == 3 ? "\033[1m\033[34m>\033[36m " : "  \033[0m") + "Dificil" + "\033[0m" + "\n";
        menu = "\033[2J\033[H" + menu;
        cout << menu;
        break;
    case 4:
        cout << "\033[2J\033[H" << "\n" << "\n" << "\033[1m" << "  Digite o Objetivo:  " << "\033[22m";
        cin >> goal; 
        status = 0;
    }
    
}   

// Monta e escreve o frame
int image(){

    int currentTime = time(NULL);
    string frame, color;
    frame.clear();

    if (mode == 2){
        frame = "\033[1m\033[31m" + to_string(pts) + "/" + to_string(goal) + "\033[39m" + " Vidas" + "   Tempo: " + to_string(currentTime - startTime) + "s\033[22m\n//";
        color = "\033[31m";
    }
    else {
        frame = "\033[1m\033[33m" + to_string(pts) + "/" + to_string(goal) + "\033[39m" + " pontos" + "   Tempo: " + to_string(currentTime - startTime) + "s\033[22m\n//";
        color = "\033[33m";
    }
    for (int i = 0; i < (L * 2) + 1; i++){
        frame += '=';
    }
    frame += "\\\\ \n";
     for (int i = 0; i < A; i++){
        frame += "|| \033[1m" + color;
        for (int p = 0; p < L; p++){
            frame += area[i][p];
            frame += " ";
        }
        frame += "\033[0m||\n";
    }
    frame += "\\\\";
    for (int i = 0; i < (L * 2) + 1; i++){
        frame += '=';
    }
    frame += "//";
    frame = "\033[2J\033[H" + frame;

    cout << frame;
    return (currentTime - startTime);
}

//Faz a execução do jogo enquanto ele está em uma partida
int game(int speed){
    int finalTime;
    for (int i = 0; i < A; i++){
            for (int p = 0; p < L; p++){
                area[i][p] = ' ';
            }
    }
    area[A - 1][locPlayer] = '^';
    while ((mode == 1 ? pts < goal : pts > 0) && status != -1){ //Execução do jogo
        playerControl();
        starMovement();
        stars();
        finalTime = image();
        usleep(speed);
        if (speed > 50000){
            speed -= 90;
        }
        else if (speed > 11000){
            speed -= 45;
        }
    }
    return finalTime;
}

//Posiciona os top 3 tempos de cada modo em um vetor e escreve-os na tela
void top3(int finalTime){ 
    int n = 0;

    if (mode == 2){
        n = 4; //Utilizado para localizar os tempos do modo correto no vetor topModes
    }
    int i = 1 + n;
    while (i < 4 + n && finalTime != topModes[i - 1]){
        if ((mode == 1 ? finalTime < topModes[1 + n] : finalTime > topModes[1 + n])) {
            topModes[3 + n] = topModes[2 + n];
            topModes[2 + n] = topModes[1 + n];
            topModes[1 + n] = finalTime;
        } else if (finalTime > topModes[2 + n]) {
            topModes[3 + n] = topModes[2 + n];
            topModes[2 + n] = finalTime;
        } else if (finalTime > topModes[3 + n]) {
            topModes[3 + n] = finalTime;
        }
        i++;
    }
    for (int i = 1; i < 4; i++){
        if (topModes[i + n] == INT16_MAX){
            cout << i << " = ---" << endl;
        }
        else {
            cout << i << " = " << topModes[i + n] << "s" << endl;
        }  
    }
}

int main() {
    int speed, finalTime;
    char conti;
    string name;
    bool run = true;

    while (run){
        pts = 0; 
        locPlayer = (L / 2);
        status = 1;
        menuPos = 1;
        system("cls"); //É necessário para garantir que as tags funcionem corretamente
        while (status != 0 && status != -1){
            menuScreen();
            usleep(60000);
        }
        speed = (difLvl * 50000) + 50000;
        srand(time(NULL));
        system("cls");
        startTime = time(NULL); //Utilizado para determinar o tempo de duração da partida em segundos
        if (mode == 2){ //Vidas para o modo de desviar dos meteoros
            goal = 3;
            pts = 3;
        }
        finalTime = game(speed);
        system("cls");
        if (status != -1){
            cout << endl << endl << endl << "\033[1m" <<  "          Fim de Jogo" << endl << endl << endl 
            << "      Seu tempo foi: " << finalTime << " segundos" << endl << endl << "Top 3 do modo:" << endl;
            top3(finalTime);
            cout << endl << endl << "      Quer Continuar? (S/N)  " << "\033[0m";
            cin >> conti;
            cin.get();
        }
        if (conti == 'N' || status == -1){
            run = false;
        }
    }
    system("cls");
    cout << endl << endl << endl << "\033[1m" << "        Obrigado por Jogar " << "\033[31m" << "<3" << "\033[0m" << endl << endl << endl;

    return 0;
}
*/