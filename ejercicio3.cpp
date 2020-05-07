#include<iostream>
using namespace std;

struct Nodo
{
	int elem;
	Nodo *sig;
};

Nodo **vectorDeListas;
Nodo **vectorConFinales;
Nodo **heap;
int tope;

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

void insertarAlFinal(int elemento, int posicion)
{
    Nodo* nuevo = new Nodo();
    nuevo->elem = elemento;
    nuevo->sig = NULL;
	Nodo *ultimo = vectorConFinales[posicion];
	if (ultimo == NULL)
	{
		vectorDeListas[posicion] = nuevo;
	}
	else
	{
		ultimo->sig = nuevo;
	}
	vectorConFinales[posicion] = nuevo;
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
	add(min->sig);
}

int main()
{
	int k;
	cin >> k;
	tope = 0;
	vectorDeListas = new Nodo *[k + 1];
	vectorConFinales = new Nodo *[k + 1];
    heap = new Nodo *[k + 1];

	for (int i = 1; i <= k; i++)
	{
        heap[i] = NULL;
		vectorDeListas[i] = NULL;
		vectorConFinales[i] = NULL;
	}
	for (int i = 1; i <= k; i++)
	{
		int cantElem;
		cin >> cantElem;
		for (int j = 0; j < cantElem; j++)
		{
			int elemento;
			cin >> elemento;
			insertarAlFinal(elemento, i);
		}
	}
	for (int i = 1; i <= k; i++)
	{
		add(vectorDeListas[i]);
	}
	while (tope != 0)
	{
		Nodo *min = getMin();
		cout << min->elem << endl;
		removeMin();
	}
	return 0;
}


