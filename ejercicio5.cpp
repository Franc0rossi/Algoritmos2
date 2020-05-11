#include <iostream> 
using namespace std;
#define INF 99999

struct Nodo
{
	int elem;
	int costo;
};

Nodo **heap;
int tope = 0;

int** matAdy;

int posicionPadre(int pos)
{
	return pos / 2;
}

int posicionHijoIzq(int pos)
{
	return pos * 2;
}

int posicionHijoDer(int pos)
{
	return pos * 2 + 1;
}

int posMinimo(int posHijoIzq, int posHijoDer){
    if(posHijoDer > tope){
        return posHijoIzq;
    }
    else{
        if(heap[posHijoIzq]->elem > heap[posHijoDer]->elem){
            return posHijoDer;
        }
        else{
            return posHijoIzq;
        }
    }
}

void swapNodos(int pos1, int pos2){
    Nodo* aux = heap[pos1];
    heap[pos1] =  heap[pos2];
    heap[pos2] = aux;
}

void flotar(int pos){
    int posPadre = pos/2;
    if(pos > 1){
        if(heap[pos] != NULL && heap[posPadre] != NULL){
            if(heap[pos]->elem < heap[posPadre]->elem){
                swapNodos(pos, posPadre);
                flotar(posPadre);
            }
        }

    }
}


bool esHoja(int pos)
{   
	return posicionHijoIzq(pos) > tope;
}

Nodo* getMin()
{
	return heap[1];
}

void hundir(int pos)
{
	if (!esHoja(pos))
	{
    int posHijoDer = posicionHijoDer(pos);
    int posHijoIzq = posicionHijoIzq(pos);
		int posMinimoHijo = posMinimo(posHijoDer, posHijoIzq);

		if (heap[posMinimoHijo] != NULL && heap[pos] != NULL)
		{
			if (heap[posMinimoHijo]->elem < heap[pos]->elem)
			{
				swapNodos(posMinimoHijo, pos);
				hundir(posMinimoHijo);
			}
		}
	}
}

void add(Nodo *nuevo)
{
	if (nuevo != NULL)
	{
		tope++;
		heap[tope] = nuevo;
		flotar(tope);
	}
}

void removeMin()
{
	Nodo *min = heap[1];
	heap[1] = heap[tope];
	tope--;
	hundir(1);
}

void vaciarHeap(int cantVertices){
  for(int i = 1; i <= cantVertices; i++){
    heap[i] = NULL;
  }
}

void imprimirCosto(int* costo, int cantVertices){
  for(int i = 1; i <= cantVertices; i++){
    if(costo[i] == 0 || costo[i] == INF){

      cout<<-1<<endl;
    }
    else{
      cout<<costo[i]<<endl;
    }
  }
}

void caminoMasCorto(int** grafo, int origen, int cantVertices){
  int *costo = new int[cantVertices];
  int *ant = new int[cantVertices];
  bool *vis = new bool[cantVertices];
  for(int i = 0; i < cantVertices; i++){
    costo[i] = INF;
    ant[i] = -1;
    vis[i] = false;
  }
  costo[origen] = 0;
  Nodo* nuevo = new Nodo;
  nuevo->elem = origen;
  nuevo->costo = 0;
  add(nuevo);
  while(tope>0){
    Nodo* minimo = getMin();
    removeMin();
    vis[minimo->elem] = true;
    for(int i = 1; i<= cantVertices; i++){
      if(matAdy[minimo->elem][i]!=INF && !vis[i]){
        if(costo[i]>costo[minimo->elem] + matAdy[minimo->elem][i]){
          costo[i] = costo[minimo->elem] + matAdy[minimo->elem][i];
          ant[i] = minimo->elem;
          Nodo* agrego = new Nodo;
          agrego->elem = matAdy[minimo->elem][i];
          agrego->costo = costo[minimo->elem] + matAdy[minimo->elem][i];
          add(agrego);
        }
      }
    }
  }

  imprimirCosto(costo, cantVertices);

}

int main(){

int cantVertices;
cin>>cantVertices;

int cantAristas;
cin>>cantAristas;

heap = new Nodo*[cantVertices + 1];
for(int i = 1; i<= cantVertices; i++){
  heap[i] = NULL;
}

matAdy = new int*[cantVertices + 1];
for(int i = 1; i <= cantVertices; i++){
  matAdy[i] = new int[cantVertices + 1];
  for(int j = 1; j <= cantVertices; j++){
    matAdy[i][j] = INF;
  }
}

for(int i = 0; i < cantAristas; i++){
  int vertice1;
  int vertice2;
  int costo;
  cin >> vertice1 >> vertice2 >> costo;
  matAdy[vertice1][vertice2] = costo;
}

int verticesConsulta;
cin>>verticesConsulta;

for(int i = 0; i < verticesConsulta; i++){
  int origen;
  cin>>origen;
  //HAY QUE LIMPIAR EL HEAP CADA VEZ QUE LLAMAMOS A LA FUNCION
  if(i!=0){
    vaciarHeap(cantVertices);
  }
  caminoMasCorto(matAdy, origen, cantVertices);
}

}
