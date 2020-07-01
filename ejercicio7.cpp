#include <iostream> 
using namespace std;
#define INF 99999


int obtenerNoVisitado(bool* vis, int cantElem){
    for(int i = 1; i < cantElem + 1; i++){
        if(vis[i] == false){
            return i;
        }
    }
    return -1;
}

int obtenerVertice(bool** matAdy, int cantElem){
    for(int i = 1; i < cantElem + 1; i++){
        for(int j = 1; j < cantElem + 1; j++){
            if(matAdy[i][j]){
                return i;
            }
        }
    }
    return -1;            
}


void compConexasRec(int pos, bool* vis, int cantElem, bool** matAdy){
    if(!vis[pos]){
        vis[pos] = true;
        for(int i = 1; i < cantElem + 1; i++){
            if(matAdy[pos][i]){
                compConexasRec(i, vis, cantElem, matAdy);
            }
        }
    }
}

int compConexas(int posO, int cantElem, bool** matAdy){
    bool bandera = true;
    int compConexas = 1;
    bool* vis = new bool[cantElem + 1];
    for(int i = 0; i <= cantElem + 1; i++){
        vis[i] = false;
    }
    compConexasRec(posO, vis, cantElem, matAdy);
    while(bandera){
        int verticeNoVisitado = obtenerNoVisitado(vis, cantElem);
        if(verticeNoVisitado != -1){
            compConexas++;
            compConexasRec(verticeNoVisitado, vis, cantElem, matAdy);
        }
        else{
            bandera = false;
        }
    }
    return compConexas;
}

int main(){
    int cantVertices;
    cin>>cantVertices;

    int cantAristas;
    cin>>cantAristas;

    bool** matAdy = new bool*[cantVertices + 1];

    for(int i = 0; i <= cantVertices + 1; i++){
        matAdy[i] = new bool[cantVertices + 1];
    }

    for(int i = 0; i <= cantVertices+1; i++){
        for(int j = 0; j<= cantVertices+1; j++){
            matAdy[i][j] = false;
        }
    }

    for(int i = 0; i <cantAristas; i++){
        int vertice1;
        int vertice2;
        cin>>vertice1>>vertice2;
        matAdy[vertice1][vertice2] = true;
        matAdy[vertice2][vertice1] = true;
    }

    int retorno = compConexas(1, cantVertices, matAdy);
    cout << retorno << " ";

    return 0;



}