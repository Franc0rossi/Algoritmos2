#include <iostream> 
using namespace std;

typedef pair <int, int> Par; 

struct Tripleta{
    int inicio;
    int final;
    int altura;

    Tripleta(int i, int f, int a){
        inicio = i;
        final = f;
        altura = a;
    }
};

Tripleta** arrayTripletas;


struct NodoPar{
    Par* par;
    int cantidadDeElementos;
    int capacidad;

    NodoPar(int capacidad){
        capacidad = capacidad;
        par = new Par[capacidad];
        cantidadDeElementos = 0;
    }
};

int alturaMaxima(int h1, int h2){
    if(h1>h2){
        return h1;
    }
    else{
        return h2;
    }
}

NodoPar* add(NodoPar*& np, Par p){
    if(np->cantidadDeElementos>0){
        if(np->par[np->cantidadDeElementos - 1].second == p.second){
            return np;
        }
        else if(np->par[np->cantidadDeElementos - 1].first == p.first){
            if(np->par[np->cantidadDeElementos - 1].second < p.second){
                np->par[np->cantidadDeElementos - 1].second = p.second; 
                return np;
            }
            else{
                return np;
            }
        }
    }
    np->par[np->cantidadDeElementos] = p;
    np->cantidadDeElementos++;
    return np;
}

NodoPar* merge(NodoPar* izq, NodoPar* der){
    NodoPar* res = new NodoPar(izq->cantidadDeElementos + der->cantidadDeElementos);
    int h1 = 0;
    int h2 = 0;
    int j = 0;
    int i = 0;
    while(i < izq->cantidadDeElementos && j < der->cantidadDeElementos){
        Par nuevo;
        if(izq->par[i].first == der->par[j].first){
            //int altura = alturaMaxima(izq->par[i].second, der->par[j].second);
            nuevo.first = izq->par[i].first;
            nuevo.second = izq->par[i].second;
            h1 = izq->par[i].second;
            h2 = der->par[j].second;
            res = add(res, nuevo);
            i++;
            j++;

        }
        else if(izq->par[i].first < der->par[j].first){
            h1 = izq->par[i].second;
            int altura = alturaMaxima(h1, der->par[j].second);
            nuevo.first = izq->par[i].first;
            nuevo.second = altura;
            res = add(res, nuevo);
            i++;
        }
        else if(izq->par[i].first > der->par[j].first){
            h2 = der->par[j].second;
            int altura = alturaMaxima(h2, izq->par[i].second);
            nuevo.first = der->par[j].first;
            nuevo.second = altura;
            res = add(res, nuevo);
            j++;
        }
    }
    while(i<izq->cantidadDeElementos){
        res = add(res, izq->par[i]);
        i++;
    }
    while(j<der->cantidadDeElementos){
        res = add(res, der->par[j]);
        j++;
    }

    return res;

}

NodoPar* obtenerContorno(Tripleta** arrayDeTripletas, int izq, int der){
    if(izq == der){
        Tripleta* tri = arrayDeTripletas[izq];
        NodoPar* result = new NodoPar(2);

        Par par1;
        par1.first = tri->inicio;
        par1.second = tri->altura;

        result = add(result, par1);

        Par par2;
        par2.first = tri->final;
        par2.second = 0;

        result = add(result, par2);

        return result;
    }
    else{
        int mitad = (izq + der) / 2;

        NodoPar* res1 = obtenerContorno(arrayTripletas, izq, mitad);
        NodoPar* res2 = obtenerContorno(arrayTripletas, mitad + 1, der);

        return merge(res1, res2);
    }
}

void imprimirSombra(NodoPar* sombra){
    for(int i = 0; i < sombra->cantidadDeElementos; i++){
        cout<<sombra->par[i].first<<" "<<sombra->par[i].second<<endl;
    }
}

int main(){
    
    int cantidadDeSombras;
    cin>>cantidadDeSombras;

    arrayTripletas = new Tripleta*[cantidadDeSombras];

    for(int i = 0; i < cantidadDeSombras; i++){
        int coordInicial;
        int coordFinal;
        int altura;

        cin>>coordInicial>>coordFinal>>altura;

        Tripleta* nueva = new Tripleta(coordInicial, coordFinal, altura);
        arrayTripletas[i] = nueva;
    }

    NodoPar* retorno = obtenerContorno(arrayTripletas, 0, cantidadDeSombras-1);

    imprimirSombra(retorno);

    return 0;
}
