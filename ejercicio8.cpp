#include <iostream> 
using namespace std;
#define INF 99999

bool hayCiclo(int v, bool* visitados, bool* camino, int cantElem, bool**matAdy) { 
    if(visitados[v] == false){ 

        visitados[v] = true; 
        camino[v] = true; 
  
        for(int i = 1; i < cantElem + 1; i++){
            if(matAdy[v][i]){
                if (!visitados[i] && hayCiclo(i, visitados, camino, cantElem, matAdy)){
                    return true; 
                }   
                else if (camino[i]){
                    return true; 
                }
            }     
        } 
  
    } 
    camino[v] = false;  // remove the vertex from recursion stack 
    return false; 
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
    }

    bool* vis = new bool[cantVertices];
    bool* camino = new bool[cantVertices];

    for(int i = 0; i <= cantVertices + 1; i++){
        vis[i] = false;
        camino[i] = false;
    }

    bool ciclo = hayCiclo(1, vis, camino, cantVertices, matAdy);
    cout << ciclo << endl;

    return 0;
}