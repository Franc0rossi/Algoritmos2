#include <iostream> 
using namespace std;

void combinaciones(int n, long long* actual, long long* anterior){

    for(int k = 0; k<=n; k++){
        if(n==k || k==0){
            actual[k] = 1;
        }
        else{
            actual[k] = anterior[k-1] + anterior[k];
        }

    }
    for(int i = 0; i<= n; i++){
        anterior[i] = actual[i];
    }

}

int main(){
    int N;
    int P;
    cin>>N;
    cin>>P;

    long long* actual = new long long[N+1];
    long long* anterior = new long long[N+1];

    int nivelCalculado = -1;

    for(int i = 0; i <= N; i++){
        actual[i] = 0;
        anterior[i] = 0;
    }

    for(int i = 0; i < P; i++){
        int n;
        int k;

        cin>>n;
        cin>>k;
        if(nivelCalculado != n){
            combinaciones(n, actual, anterior);
            cout<<actual[k]<<endl;
            nivelCalculado = n;
        }
        else{
            cout<<actual[k]<<endl;
        }

    }

    return 0;
}