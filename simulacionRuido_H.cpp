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
//----------------------------------------------------------------------------------------------------------------
//  Crea Achivos .dat con los datos a graficar  
//-----------------------------------------------------------------------------------------------------------------

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
//*********************************************************************************************************************
// Convierte entero en una cadena de 4 números, aquí se usa para etiquetar secuencia de archivos desde 0000 hasta 9999 
//**********************************************************************************************************************
void convIntEnChar(int entero, char cadenaTemp [5])
{
  int div, resi;
  char k = '0';
  div = entero/1000;
  resi= entero%1000;
  k = div + 0x30;
  cadenaTemp[0] = k;  
  div = resi/100;
  resi= resi%100;
  k = div + 0x30;
  cadenaTemp[1] = k;
  div = resi/10;
  resi = resi%10;
  k = div + 0x30;
  cadenaTemp[2] = k;
  k = resi + 0x30;
  cadenaTemp[3] = k;
  cadenaTemp[4]='\0'; 
   
}
//**********************************************************************************************************************
void graficar(char ordenCuadro[5])
{
  char plotIni[100]="splot 'datos_";
  char plotParam[70]=" using 1:2:3:4 with points pt 7 ps 0.4 lc palette";
  char plotExt[6]=".dat'";
  char datosIni[32]="set output 'cuadro_";
  char datoExt[6]=".png'";
  strcat(plotIni,ordenCuadro);
  strcat(plotIni,plotExt);
  strcat(plotIni,plotParam);
  strcat(datosIni,ordenCuadro);
  strcat(datosIni,datoExt); 
  cout<<"set terminal png"<<endl;
  cout<< datosIni <<endl;
  cout<<"set vgrid $v size 100"<<endl;
  cout<<"set vxrange [0:100]; set vyrange [0:100]; set vzrange [0:100]"<<endl ;
  cout<<"set xrange [0:100]; set yrange [0:100]; set zrange [0:100]" <<endl;
  cout<<"set pm3d"<<endl;
  cout<<"set cbrange [-1.2:1.3]"<<endl;
  cout<<"set ylabel \"y\""<<endl;
  cout<<"set xlabel \"x\""<<endl;
  cout<<"set zlabel \"z\""<<endl;
  cout<<"set title \"Ruido Dependiente de H [0,2] \""<<endl;
  cout<<"set key noautotitle"<<endl;
  cout<<plotIni<<endl;

}

int main(void){
Ruido Fondo;
int m=0;
char orden [5];
char extArchivo[5]=".dat";

  for ( H=0;H<Hmax; H=m*dH)
  {
    char nomArchivo[14]="datos_";
    Fondo.Cargue();
    convIntEnChar(m,orden);
    strcat(nomArchivo,orden);
    strcat(nomArchivo,extArchivo);
    Fondo.Imprimase(nomArchivo);
    graficar(orden);
    m++;
  }
  return 0;
}
