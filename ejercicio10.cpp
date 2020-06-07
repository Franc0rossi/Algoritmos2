#include <iostream> 
using namespace std;

void llenar(int*& vec, char* cuadrillasOperadores, int tamCuadOp, char caracter){
    int j = 0;
    for(int i = 0; i < tamCuadOp; i++){
        if(cuadrillasOperadores[i] == caracter){
            vec[j] = i;
            j++;
        }
    }
}

int abs(int x){
    if(x>0){
        return x;
    }
    else{
        return (-x);
    }

}

int pisosAtendidos(int* cuadrillas, int tamCuad, int* operadores, int tamOp, int rango){
    int i = 0;
    int j = 0;
    int cont = 0;

    while(i<tamCuad && j<tamOp){
        if(abs(cuadrillas[i]-operadores[j])<= rango){
            cont++;
            i++;
            j++;
        }
        else if(cuadrillas[i] <= operadores[j]){
            i++;
        }
        else{
            j++;
        }
    }
    return cont;
}

int main(){
    int numeroPruebas;
    cin>>numeroPruebas;

    int* resultados = new int[numeroPruebas];
    

    for(int i = 0; i < numeroPruebas; i++){
        int rango;
        int tam;
        cin>>rango;
        cin>>tam;

        char* cuadrillasOperadores = new char[tam];

        int cantOp = 0;
        int cantCuad = 0;
        for(int j = 0; j < tam; j++){
            char dato;
            cin>>dato;
            if(dato == 'C'){
                cantCuad++;
            }
            else{
                cantOp++;
            }
            cuadrillasOperadores[j] = dato;
        }

        int* cuadrillas = new int[cantCuad];
        int* operadores = new int[cantOp];

        llenar(cuadrillas, cuadrillasOperadores, tam, 'C');
        llenar(operadores, cuadrillasOperadores, tam, 'O');

        int total = pisosAtendidos(cuadrillas, cantCuad, operadores, cantOp, rango);

        cout<< total << endl;

    }

    return 0;
}