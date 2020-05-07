#include<iostream>
using namespace std;

struct Nodo{
    int elem;
    int distanciaOrigen;
};

struct NodoAdy{
    int dato;
    NodoAdy* sig;
};

Nodo** heap;
int tope = 0;

// retorna el indice del hijo izq
int hIzq(int i){ return (2 * i); }

// retorna el indice del hijo der
int hDer(int i){ return (2 * i + 1); }

void swapNodos(int pos1, int pos2){
    Nodo* aux = heap[pos1];
    heap[pos1] =  heap[pos2];
    heap[pos2] = aux;
}

void flotar(int pos){
    int posPadre = pos/2;
    if(pos > 1){
        if(heap[pos]->distanciaOrigen < heap[posPadre]->distanciaOrigen){
            swapNodos(pos, posPadre);
            flotar(posPadre);
        }
        else if(heap[pos]->distanciaOrigen == heap[posPadre]->distanciaOrigen){
            if(heap[pos]->elem < heap[posPadre]->elem){
                swapNodos(pos, posPadre);
                flotar(posPadre);
            }
        }
    }
}

int posMinimo(int posHijoIzq, int posHijoDer){
    if(heap[posHijoIzq]->distanciaOrigen > heap[posHijoDer]->distanciaOrigen){
        return posHijoDer;
    }
    else if(heap[posHijoIzq]->distanciaOrigen < heap[posHijoDer]->distanciaOrigen){
        return posHijoIzq;
    }
    else if(heap[posHijoIzq]->distanciaOrigen == heap[posHijoDer]->distanciaOrigen){
        if (heap[posHijoIzq]->elem > heap[posHijoDer]->elem){
            return posHijoDer;
        }
        else{
            return posHijoIzq;
        }
    }
}

void hundir(int pos){
    int posHijoIzq = hIzq(pos);
    int posHijoDer = hDer(pos);
    //para que sea hoja basta con saber que el izquierdo sea distinto de null
    if(heap[posHijoIzq]!= NULL){
        if(heap[posHijoDer]==NULL){
            if(heap[pos]->distanciaOrigen > heap[posHijoIzq]->distanciaOrigen){
                swapNodos(pos, posHijoIzq);
                hundir(posHijoIzq);
            }
            else if(heap[pos]->distanciaOrigen == heap[posHijoIzq]->distanciaOrigen){
                if(heap[pos]->elem > heap[posHijoIzq]->elem){
                    swapNodos(pos, posHijoIzq);
                    hundir(posHijoIzq);
                }
            }
        }
        else{
            //Obtengo la pos del hijo menor y los comparo conmigo
            int posHijoMenor = posMinimo(posHijoDer, posHijoIzq);
            if(heap[pos]->distanciaOrigen > heap[posHijoMenor]->distanciaOrigen){
                swapNodos(pos, posHijoMenor);
                hundir(posHijoMenor);
            }
            else if(heap[pos]->distanciaOrigen == heap[posHijoMenor]->distanciaOrigen){
                if(heap[pos]->elem > heap[posHijoMenor]->elem){
                    swapNodos(pos, posHijoMenor);
                    hundir(posHijoMenor);
                }
            }
        }
    }
}

void add(int distanciaOrigen, int elem){
    Nodo* nuevo = new Nodo;
    nuevo->distanciaOrigen = distanciaOrigen;
    nuevo->elem = elem;
    int posNuevo = tope + 1;
    heap[posNuevo] = nuevo;
    flotar(posNuevo);
    tope++;
}

Nodo* getMin(){
    return heap[1];
}

void removeMin(){
    swapNodos(tope, 1);
    heap[tope] = NULL;
    tope--;
    hundir(1);
}

int main(){
    int cantVertices;
    int cantAristas;
    cin>>cantVertices;
    cin>>cantAristas;


    NodoAdy** listaAdy = new NodoAdy*[cantVertices+1];
    int* vecIncidentes = new int[cantVertices+1];
    heap = new Nodo*[cantVertices+1];

    for(int i = 0; i<cantVertices+1; i++){
        listaAdy[i] = NULL;
    }

    for(int i = 0; i < cantVertices + 1; i++){
        vecIncidentes[i] = 0;
        heap[i] = NULL;
    }


    
    for(int i = 0; i < cantAristas; i++){
        int vertice1;
        int vertice2;
        cin >> vertice1 >> vertice2;

        NodoAdy* nuevo = new NodoAdy;
        nuevo->dato = vertice2;
        nuevo->sig = listaAdy[vertice1];
        listaAdy[vertice1] = nuevo;
        vecIncidentes[vertice2]++;

    }

    //AGREGO EN EL HEAP TODOS LOS VERTICES DE INCIDENCIA CERO
    for(int i = 1; i <= cantVertices; i++){
        if(vecIncidentes[i] == 0){
            add(0,i);
        }
    }

    /*
    CORROBORAMOS VECTOR DE INCIDENCIAS
    for(int i = 1; i<cantVertices+1; i++){
        cout<<vecIncidentes[i]<<endl;
    }
    */

    
    /*CORROBORAMOS LISTA DE ADYACENTES
    for(int i = 1; i<cantVertices; i++){
        NodoAdy* iter = listaAdy[i];
        while(iter!=NULL){
            cout<<iter->dato<<endl;
            iter = iter->sig;
        }
    }
    */
    
    while(tope!=0){
        Nodo* minimoHeap = getMin();
        removeMin();
        cout << minimoHeap->elem << endl;
        NodoAdy* ady = listaAdy[minimoHeap->elem];
        while(ady!=NULL){
            //Debo fijarme que el vertice en incidentes al pararme en el sea cero, con esto me aseguro que es el proximo en agregar al heap
            vecIncidentes[ady->dato]--;
            if(vecIncidentes[ady->dato]==0){
                 add(minimoHeap->distanciaOrigen + 1, ady->dato);
            }
            ady = ady->sig;
        }
    }
    
    return 0;
}



/*
input
10
20
10 2
1 5
7 1
9 2
5 6
1 2
2 4
3 2
2 6
1 6
7 5
10 5
8 7
8 6
10 6
3 6
9 4
9 1
5 4
3 8

output
3
9
10
8
7
1
2
5
4
6
*/