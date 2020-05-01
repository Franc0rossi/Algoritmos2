#include <iostream>
using namespace std;


struct AVL{
    int dato;
    int bal;
    AVL* izq;
    AVL* der;
};

bool varioH;

void insertar(AVL*& a, int elemento){
    AVL* a1;
    AVL* a2;
    if(a==NULL){
        //Creo el arbol
        a = new AVL;
        a->dato = elemento;
        a->izq = NULL;
        a->der = NULL;
        a->bal = 0;
        varioH = true;
    }
    else if(a->dato > elemento){
        //Inserto en subarbol izquierdo
        insertar(a->izq, elemento);
        if(varioH){
            switch(a->bal){
                case 1:
                    a->bal = 0;
                    varioH = false;
                    break;

                case 0:
                    a->bal = -1;
                    break;

                case -1:
                    a1 = a->izq;
                    if(a1->bal == -1){
                        a->izq = a1->der;
                        a1->der = a;
                        a->bal = 0;
                        a = a1;
                    }
                    else{
                        a2 = a1->der;
                        a1->der = a2->izq;
                        a2->izq = a1;
                        a->izq = a2->der;
                        a2->der = a;
                        a->bal = a2->bal == -1 ? 1 : 0;
                        a1->bal = a2->bal == 1 ? -1 : 0;
                        a = a2;
                    }
                    a->bal = 0;
                    varioH = false;
                    break;
            }
        }
    }
    else if(a->dato < elemento){
        insertar(a->der, elemento);
        if(varioH){
            switch(a->bal){
                case -1:
                    a->bal = 0;
                    varioH = false;
                    break;

                case 0:
                    a->bal = 1;
                    break;

                case 1:
                    a1 = a->der;
                    if(a1->bal == 1){
                        a->der = a1->izq;
                        a1->izq = a;
                        a->bal = 0;
                        a = a1;
                    }
                    else{
                        a2 = a1->izq;
                        a1->izq = a2->der;
                        a2->der = a1;
                        a->der = a2->izq;
                        a2->izq = a;
                        a->bal = a2->bal == 1 ? -1 : 0;
                        a1->bal = a2->bal == -1 ? 1 : 0;
                        a = a2;
                    }
                    a->bal = 0;
                    varioH = false;
                    break;
            }
        }

    }
    else{
        varioH = false;
    }

}

void imprimirOrdenado(AVL* a){
    if(a!=NULL){
        imprimirOrdenado(a->izq);
        cout<<a->dato<<endl;
        imprimirOrdenado(a->der);
    }
}

int main(){
    int n;
    cin>>n;
    AVL* prueba = NULL;
    for (int i = 0; i < n; i++)
    {
        int elemento;
        cin>>elemento;
        insertar(prueba, elemento);
    }
    

    imprimirOrdenado(prueba);
    return 0;
}


