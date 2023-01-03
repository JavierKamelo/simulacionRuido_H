#include <iostream>
#include <fstream>
#include <cmath>
#include <complex.h>
#include <string>
#include <bits/stdc++.h>
//#include "Random64.h"
using namespace std;

const int Lx=90;
const int Ly=90;
const int Lz=40;
float H; 
const float dH=0.1;
const float Hmin=0.0;
const float Hmax=2;
const float ax=0.5;
const float ay=0.5;


class Ruido{
private:
    complex<float> Ux[Lx][Ly][Lz], Uy[Lx][Ly][Lz],Uz[Lx][Ly][Lz];
  
public:
  
  void Cargue(void);
  void Imprimase(const char * NombreArchivo);
};

void Ruido::Cargue(void){
  int i,j,k;
  //complex<float> kk (8, 0);
   
   
    for (i=0; i<Lx; i++){
        for (j=0; j<Ly-1; j++){
            for(k=0; k<Lz; k++){
                
               
                Ux[i][j][k]=complex<float>(cosf(0.5*H*ax*ay*(-Ly/2.+j-1.)),sinf(0.5*H*ax*ay*(-Ly/2.+j-1.)));
                //if (real(Ux[i][j][k])> -0.6 && real(Ux[i][j][k])< 0.6) Ux[i][j][k]= Ux[i][j][k] + kk;
                
               
            } 
        }
    }

}

void Ruido::Imprimase(const char * NombreArchivo){
  ofstream MiArchivo(NombreArchivo); 
  int i,j,k;
    
    for(i=0;i<Lx;i++){
        for(j=0;j<Ly;j++){
          for(k=0; k<Lz; k++){
            
                //rho0=rho(ix,iy,false);
                MiArchivo<<" "<<i<<" "<<j<<" "<<k<<" "<< real(Ux[i][j][k])   <<endl;
          }     
        }
    MiArchivo<<endl;
    }

  MiArchivo.close();
}

void convIntEnChar(int entero, char cadenaTemp [4])
{
  int div, resi;
  char k = '0';  
  div = entero/100;
  resi= entero%100;
  k = div + 0x30;
  cadenaTemp[0] = k;
  div = resi/10;
  resi = resi%10;
  k = div + 0x30;
  cadenaTemp[1] = k;
  k = resi + 0x30;
  cadenaTemp[2] = k;
  cadenaTemp[3]='\0'; 
   
}

int main(void){
  Ruido Fondo;
int m=0;
char orden [4];
cout << orden << endl;

  for ( H=0;H<Hmax; H=m*dH)
  {
    Fondo.Cargue();
    convIntEnChar(m,orden);
    char nomArchivo[5]="y_";
    strcat(nomArchivo,orden);
    const char *arch = nomArchivo;
    cout<< "H es: " << H << "  k = "<<nomArchivo << "  m="<< m << endl;
    Fondo.Imprimase(nomArchivo);
    m++;
  }
  return 0;
}
