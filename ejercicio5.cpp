#include <iostream> 
using namespace std;
#define INF 99999

struct Nodo
{
	int elem;
	int costo;
};

struct NodoAdy{
    int dato;
    int costo;
    NodoAdy *sig;
};

int* hashPosHeap;
Nodo *heap;
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

int posMinimo(int posHijoIzq, int posHijoDer){
    if(posHijoDer > tope){
        return posHijoIzq;
    }
    else{
        if(heap[posHijoIzq].costo > heap[posHijoDer].costo){
            return posHijoDer;
        }
        else{
            return posHijoIzq;
        }
    }
}

void swapNodos(int pos1, int pos2){
    Nodo aux = heap[pos1];
    heap[pos1] =  heap[pos2];
    heap[pos2] = aux;
}

void flotar(int pos){
    int posPadre = pos/2;
    if(pos > 1){
            if(heap[pos].costo < heap[posPadre].costo){
              hashPosHeap[heap[pos].elem] = posPadre;
				      hashPosHeap[heap[posPadre].elem] = pos;
              swapNodos(pos, posPadre);
              flotar(posPadre);
            }
    }
}

void add(Nodo nuevo)
{
		tope++;
		heap[tope] = nuevo;
		flotar(tope);
}

void inicializarHeap(int origen, int cantVertices){
  heap=new Nodo[cantVertices+1];
  for (int i = 1; i <= cantVertices; i++){
		Nodo nuevo;
		nuevo.elem = i;
		if (i != origen)
		{
			nuevo.costo = INF;
		}
		else
		{
			nuevo.costo = 0;
		}
		add(nuevo);
	}
  
}

bool esHoja(int pos)
{   
	return posicionHijoIzq(pos) > tope;
}

Nodo getMin()
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

			if (heap[posMinimoHijo].costo < heap[pos].costo)
			{
        hashPosHeap[heap[pos].elem] = posMinimoHijo;
			  hashPosHeap[heap[posMinimoHijo].elem] = pos;
				swapNodos(posMinimoHijo, pos);
				hundir(posMinimoHijo);
			}
	}
}

void removeMin()
{
	Nodo min = heap[1];
	heap[1] = heap[tope];
	tope--;
	hundir(1);
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

void modificarCosto(int vertice, int nuevoCosto)
{
	int indiceHeap = hashPosHeap[vertice];
	heap[indiceHeap].costo = nuevoCosto;
	hundir(indiceHeap);
	flotar(indiceHeap);
}

void caminoMasCorto(NodoAdy** listaAdy, int nodoOrigen, int cantidadDeVertices){
  int *costo = new int[cantidadDeVertices + 1];
  int *ant = new int[cantidadDeVertices + 1];
  bool *vis = new bool[cantidadDeVertices + 1];
  for(int i = 0; i < cantidadDeVertices + 1; i++){
    costo[i] = INF;
    ant[i] = -1;
    vis[i] = false;
  }
 costo[nodoOrigen] = 0;
  while(tope>0){
    Nodo minimo = getMin();
    removeMin();
    vis[minimo.elem] = true;
    NodoAdy* adyacentes = listaAdy[minimo.elem];
    while(adyacentes != NULL){
      if(!vis[adyacentes->dato]){
        if(costo[adyacentes->dato]>costo[minimo.elem] + adyacentes->costo){
			    costo[adyacentes->dato] = costo[minimo.elem] + adyacentes->costo;
			    ant[adyacentes->dato] = minimo.elem;
			    modificarCosto(adyacentes->dato,costo[minimo.elem] + adyacentes->costo);
        }
      }
      adyacentes = adyacentes->sig;
    }
    
  }
  imprimirCosto(costo, cantidadDeVertices);
    
}

int main(){

  int cantVertices;
  cin>>cantVertices;

  int cantAristas;
  cin>>cantAristas;

  hashPosHeap = new int[cantVertices + 1];
  for(int i=0;i<=cantVertices;i++){
    hashPosHeap[i]=i;
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
        NodoAdy* nuevo = new NodoAdy;
        nuevo->dato = vertice2;
        nuevo->sig = listaAdy[vertice1];
        nuevo->costo = costo;
        listaAdy[vertice1] = nuevo;
  }

  int verticesConsulta;
  cin>>verticesConsulta;

  for(int i = 0; i < verticesConsulta; i++){
    int origen;
    cin>>origen;
    //HAY QUE LIMPIAR EL HEAP CADA VEZ QUE LLAMAMOS A LA FUNCION
    inicializarHeap(origen,cantVertices);
    caminoMasCorto(listaAdy, origen, cantVertices);
    //Reseteamos hash por posiciones
    for (int j = 0; j <= cantVertices; j++)
      hashPosHeap[j] = j;
  }
}