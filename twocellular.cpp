#include <iostream> 
#include <stdlib.h>
#include <time.h>
using namespace std;


/*Funcion en la cual consulta la cantidad de vecinos que tiene la celula en la lattice*/
int neighbours(int a, int b, int c, int d, int e, int f, int g, int h)
{
 int result =a+b+c+d+e+f+g+h;
 return result; 
}




int main(void)
{
 int i, j;
 int N = 32; // tamanio de la lattice
 //Crecion de objetos dinamicos para el arreglo de tamanio N
 int** A = new int* [N]; 

 for(i=0;i<N;i++) // creacion de los objetos en el arreglo dinamico
  A[i] = new int[N] ; 

  int** B = new int* [N]; 

  for(i=0;i<N;i++)
   B[i] = new int[N] ;
  
  // se generan las celulas las celulas en la lattice 0 si no existe y 1 si existe
  // Estado inicial
  cout << "Initial State " << endl;
  for(i=0;i<N;i++)
  { 
   for(j=0;j<N;j++) 
   {
    A[i][j] = rand() % 2;
   }
  }

//impresion de la primer lattice 
  for (i=0; i<N; i++)
  {
   for(j=0; j<N; j++)
   { 
    cout << A[i][j] << " ";
   }
    cout << endl;
  }

  int T = 100; // cantidad de iteraciones 
  for(int t=0;t<T;t++)
  {
   for(i=0;i<N;i++)
   {
    for(j=0;j<N;j++)
    {
     B[i][j] = A[i][j]; // paso de la lattice original a la nueva lattice
    }
   }
 
   /*
	Recorre la lattice 
   */
  for(i=0;i<N;i++)
   {
    for(j=0;j<N;j++)
    {
     int temp=  //GUarda la cantidad de vecinos al rededor de la celula
     neighbours(
     B[((i+1)%N)][j],
     B[((i+1)%N)][((j+1)%N)],
     B[i][((j+1)%N)],
     B[((i-1+N)%N)][((j+1)%N)],
     B[((i-1+N)%N)][j], 
     B[((i-1+N)%N)][((j-1+N)%N)] ,
     B[i][((j-1+N)%N)] , 
     B[((i+1)%N)][((j-1+N)%N)]);

     // rule 1:Una celula cobra actividad (o permanece activa si ya lo estaba) cuandola rodean 3 celulas activas (nacimiento).
     if((B[i][j] == 0) && (temp == 3)) 
     { 
      A[i][j] = 1; 
     }

     // rule 2: Una celula mantiene su estado, sea este cual fuera, si tiene tan solo 2 celulas vecinas activas (conservacion).
     if((B[i][j] == 1) && ((temp ==2) || (temp == 3))) 
     {
      A[i][j] = 1; 
     }

     // rule 3: Una celula se inactiva (o permanece inactiva) si posee menos de 2 o mas de 3s vecinas activas (muerte).
     if((B[i][j] == 1) && ((temp >= 4) || (temp <= 1)))
     {
      A[i][j] = 0 ; 
     }

  }
 }

cout << endl; //impresion de iteracion
cout << "t = " << t; 
cout << endl;

//impresion de la lattice despues de cada evolucion
for(i=0;i<N;i++)
{
 for(j=0;j<N;j++)
 {
  cout <<  A[i][j] << " "; 
 }
 cout << endl;
}
  cout << endl << endl;
} 

// livera la memoria para no hace stackoverflow
for(i=0;i<N;i++) 
 delete[] A[i];

delete[] A;


for(i=0;i<N;i++) 
 delete[] B[i]; 

delete[] B;

return 0;


}
