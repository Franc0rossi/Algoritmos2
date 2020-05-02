#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

struct Node 
{
    string value;
    Node* next;
};


    unsigned int funcHash(string &key, int tableLength){
	    unsigned int hashVal = 0;
	    for (int i = 0; i < key.length(); i++){
		    hashVal = 37 * hashVal + key[i];
	    }
	    return hashVal % tableLength;
    }

    void add(string& value, Node**& tabla, int length){
      int pos = funcHash(value, length);
      Node* principio = tabla[pos];
      Node* nuevo = new Node;
      nuevo->value = value;
      nuevo->next = principio;
      tabla[pos] = nuevo;
      
    }

    int exists(string& value, Node**& tabla, int length){
     int pos = funcHash(value, length);
     Node* principio = tabla[pos]; 
     while(principio != NULL && principio->value != value){
       principio = principio->next;
     }
      if(principio == NULL){
          return 0;
      }
      else{
          return 1;
      }
    }

    bool isPrime(int num){
      assert(num>=1);
      if(num==1){
        return false;
      } else {
        for(int i=2; i<num/2; i++){
          if(num%i==0){
            return false;
          }
        }
        return true;
      }
    }

    int nextPrime(int num){
      // while(!isPrime(++num));
      // return num; 
      return isPrime(++num) ? num : nextPrime(num);
    }


int main(){
    int n;
    cin >> n;
    int length = nextPrime(n);
    Node** HashPrueba = new Node*[length];
    for(int i = 0; i < length ; i++){
        HashPrueba[i] = NULL;
    }

    for(int i = 0; i < n ; i++){
        string value;
        cin >> value;
        add(value, HashPrueba, length);
    }

    int m;
    cin >> m;
    int* retorno = new int[m];

    for(int i = 0; i < m; i++){
        string value;
        cin >> value;
        retorno[i] = exists(value, HashPrueba, length);
    }

    for(int i = 0; i < m; i++){
        cout<<retorno[i]<<endl;
    }

    return 0;

}