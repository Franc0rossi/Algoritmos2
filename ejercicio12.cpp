#include <iostream> 
using namespace std;

bool** matriz;
int* conjunto;

void inicializarMatriz(int n, int m){
    matriz = new bool *[n + 1];
    for (int i = 0; i <= n; i++){
        matriz[i] = new bool[m + 1];
        for (int j = 0; j <= m; j++){
            matriz[i][j] = false;
        }
    }

    for (int i = 0; i <= n; i++){
        matriz[i][0] = true;
    }
}

void esPosibleSuma(int n, int m){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (conjunto[i - 1] > j){
                matriz[i][j] = matriz[i - 1][j];
            }
            else{
                matriz[i][j] = matriz[i - 1][j] || matriz[i - 1][j - conjunto[i - 1]];
            }
        }
    }
}

int main(){
    int tamConj;
    cin>>tamConj;
    conjunto = new int[tamConj];
    for(int i = 0; i < tamConj; i++){
        int valor;
        cin>>valor;
        conjunto[i] = valor;
    }
    int sumaMaxima;
    cin>>sumaMaxima;

    inicializarMatriz(tamConj, sumaMaxima);
    esPosibleSuma(tamConj, sumaMaxima);

    int cantPruebas;
    cin>>cantPruebas;


    for(int i = 0; i < cantPruebas; i++){
        bool imprimiUno = false;
        int suma;
        cin>>suma;
        for(int n = 1; n <= tamConj; n++){
            if(matriz[n][suma]){
                cout<<"1"<<endl;
                imprimiUno = true;
                n = tamConj;
            }
        }
        if(!imprimiUno){
            cout<<"0"<<endl;
        }
    }
    return 0;
}




