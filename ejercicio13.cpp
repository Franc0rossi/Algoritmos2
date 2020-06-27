#include <iostream> 
using namespace std;

#define INF 99999

int** matriz;
int movX[4] = {1, 0, -1, 0};
int movY[4] = {0, 1, 0, -1};
bool** matrizVisitados;


bool esPosicionValida(int posXActual, int posYActual, int filas, int columnas){
    return posXActual>=0 && posYActual>=0 && posXActual<filas && posYActual<columnas;
}

bool movimientoValido(int posXActual, int posYActual){
    return ((matriz[posXActual][posYActual] != 0) && (!matrizVisitados[posXActual][posYActual]));
}

bool llegueADestino(int posXActual, int posYActual, int posXFinal, int posYFinal){
    return (posXActual == posXFinal) && (posYActual == posYFinal);
}

void quitarMovimiento(int X, int Y){
    matrizVisitados[X][Y] = false;
}

void laberintoBT(int posXActual, int posYActual, int posXFinal, int posYFinal, int sumaActual, int& sumaOptima, int K, int columnas, int filas){
    if(llegueADestino(posXActual, posYActual, posXFinal, posYFinal)){
        if(sumaActual<sumaOptima){
            sumaOptima = sumaActual;
        }   
    }
    else{
        for(int i = 0; i < 4; i++){
            int nuevoX = posXActual + movX[i];
            int nuevoY = posYActual + movY[i];
            if(esPosicionValida(nuevoX, nuevoY, filas, columnas)){
                if(movimientoValido(nuevoX, nuevoY) && sumaActual + matriz[nuevoX][nuevoY] < K ){
                    matrizVisitados[nuevoX][nuevoY] = true;
                    int nuevaSuma = sumaActual + matriz[nuevoX][nuevoY];
                    laberintoBT(nuevoX, nuevoY, posXFinal, posYFinal, nuevaSuma, sumaOptima, K, columnas, filas);
                    quitarMovimiento(nuevoX, nuevoY);
                }
            }
        }
    }
}

int main (){

    int M; //COLUMNAS
    int N; //FILAS
    cin>>M;
    cin>>N;

    matriz = new int*[N];
    matrizVisitados = new bool*[N];

    for(int i = 0; i < N; i++){
        matriz[i] = new int[M];
        matrizVisitados[i] = new bool[M];
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            matriz[i][j] = -1;
        }
    }

    int K;
    cin>>K;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            int valor;
            cin>>valor;
            matriz[i][j] = valor;
        }
    }

    int P;
    cin>>P;

    for(int i = 0; i < P; i++){
        int Xi; 
        int Yi; 
        int Xf; 
        int Yf; 
        cin>>Yi>>Xi>>Yf>>Xf;
        Xi--;
        Yi--;
        Xf--;
        Yf--;

        int sumaOptima = INF;
        int sumaActual = matriz[Xi][Yi];

        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                matrizVisitados[i][j] = false;
            }    
        }

        matrizVisitados[Xi][Yi] = true;
        laberintoBT(Xi, Yi, Xf, Yf, sumaActual, sumaOptima, K, M, N);

        cout<<sumaOptima<<endl;
    }
    return 0;
}