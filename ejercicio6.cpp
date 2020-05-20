#include <iostream> 
using namespace std;
#define INF 99999

struct Nodo
{
	int vertice;
	int costo;
};

struct NodoAdy {
	int dato;
	int costo;
	NodoAdy* sig;
};
Nodo** heap;
int tope = 0;

NodoAdy** listaAdy;

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

int posMinimo(int posHijoIzq, int posHijoDer) {
	if (posHijoDer > tope) {
		return posHijoIzq;
	}
	else {
		if (heap[posHijoIzq]->costo > heap[posHijoDer]->costo) {
			return posHijoDer;
		}
		else {
			return posHijoIzq;
		}
	}
}

void swapNodos(int pos1, int pos2) {
	Nodo* aux = heap[pos1];
	heap[pos1] = heap[pos2];
	heap[pos2] = aux;
}

void flotar(int pos) {
	int posPadre = pos / 2;
	if (pos > 1) {
		if (heap[pos] != NULL && heap[posPadre] != NULL) {
			if (heap[pos]->costo < heap[posPadre]->costo) {
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
			if (heap[posMinimoHijo]->costo < heap[pos]->costo)
			{
				swapNodos(posMinimoHijo, pos);
				hundir(posMinimoHijo);
			}
		}
	}
}

void add(Nodo* nuevo)
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
	Nodo* min = heap[1];
	heap[1] = heap[tope];
	tope--;
	hundir(1);
}

int sumaTotal(int* costo, int cantidadDeVertices){
    int suma = 0;
    for(int i = 1; i <= cantidadDeVertices; i++){
        suma += costo[i];
    }
    return suma;
}

int arbolDeCubrimientoMinimo(NodoAdy** listaAdy, int nodoOrigen, int cantidadDeVertices) {
	bool* vis = new bool[cantidadDeVertices + 1];
    int *costo = new int[cantidadDeVertices + 1];
    int *ant = new int[cantidadDeVertices + 1];
	for (int i = 0; i < cantidadDeVertices + 1; i++) {
		vis[i] = false;
        costo[i] = INF;
        ant[i] = -1;
	}

	vis[nodoOrigen] = true;
    costo[nodoOrigen] = 0;
    Nodo* nuevo = new Nodo;
    nuevo->vertice = nodoOrigen;
    nuevo->costo = 0;
    add(nuevo);
    while(tope>0){
        Nodo* minimo = getMin();
        removeMin();
        vis[minimo->vertice] = true;
        NodoAdy* adyacentes = listaAdy[minimo->vertice];
        while(adyacentes != NULL){
            if(!vis[adyacentes->dato]){
                if(costo[adyacentes->dato] > adyacentes->costo){
                    costo[adyacentes->dato] = adyacentes->costo;
                    ant[adyacentes->dato] = minimo->vertice;
                    Nodo* agrego = new Nodo;
                    agrego->vertice = adyacentes->dato;
                    agrego->costo = adyacentes->costo;
                    add(agrego);
                }
            }
            adyacentes = adyacentes->sig;
        }
        
    }

    return sumaTotal(costo, cantidadDeVertices);
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

  listaAdy = new NodoAdy*[cantVertices + 1];
  for(int i = 0; i <= cantVertices; i++){
    listaAdy[i] = NULL;
  }

  for(int i = 0; i < cantAristas; i++){
    int vertice1;
    int vertice2;
    int costo;
    cin >> vertice1 >> vertice2 >> costo;
        NodoAdy* nuevo2=new NodoAdy;
        NodoAdy* nuevo = new NodoAdy;
        nuevo->dato = vertice2;
        nuevo->sig = listaAdy[vertice1];
        nuevo->costo = costo;
        listaAdy[vertice1] = nuevo;

        nuevo2->dato = vertice1;
        nuevo2->sig = listaAdy[vertice2];
        nuevo2->costo = costo;
        listaAdy[vertice2] = nuevo2;
  }

  int retorno = arbolDeCubrimientoMinimo(listaAdy, 1, cantVertices);
  cout<<retorno<<" ";

return 0;
}
