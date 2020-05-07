#include <iostream> 
using namespace std;
#define INF 99999

/*
void dijkstra(int posO, int posD)
{
  // Creo vectores auxiliares
  int *dist = new int[tope];
  int *ant = new int[tope];
  bool *vis = new bool[tope];

  // Inicializo los vectores
  for (int i = 0; i < tope; dist[i] = INF, ant[i] = -1, vis[i] = false; i++)
    ;

  // Proceso al origen
  vis[posO] = true;
  dist[posO] = 0;
  for (int j = 0; j < tope; j++)
  {
    if (matAdy[posO][j]->existe)
    {
      ant[j] = posO;
      dist[j] = matAdy[posO][j]->costo;
    }
  }

  // Evalúo a todos los demás vértices
  for (int k = 1; k < tope; k++)
  {
    // Selecciono el vértice de menor distancia no visitado
    int posMin = -1;
    int min = INF;
    for (int i = 0; i < tope; i++)
    {
      if (!vis[i] && dist[i] < min)
      {
        posMin = i;
        min = dist[i];
      }
    }
    // Visito al vértice intermedio
    if (posMin == -1)
      break;
    vis[posMin] = true;
    // Evaluo adyacentes
    for (int j = 0; j < tope; j++)
    {
      // Actualizo la distancia y el anterior en caso que un adyacente tenga distancia acumulada mejor a la actual
      if (!vis[j] && matAdy[posMin][j]->existe)
      {
        int nuevoCosto = dist[posMin] + matAdy[posMin][j]->costo;
        if (nuevoCosto < dist[j])
        {
          dist[j] = nuevoCosto;
          ant[j] = posMin;
        }
      }
    }
  }

  int ret = dist[posD];

  delete[] dist;
  delete[] ant;
  delete[] vis;

  return ret;
}
*/