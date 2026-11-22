// TRAZADORES CÚBICOS (condiciones de frontera naturales)
// De: Santiago Hernandez Morales y Maria Paula Rodriguez Ruiz
// Compilar: g++ -std=c++17 -o trazador_cubico trazador_cubico.cpp
// Ejecutar: ./trazador_cubico

#include <iostream>
#include <iomanip>

using namespace std;

// Estos son los años de Estonia que se van a usar para construir el trazador cúbico (x0, x1, ..., x24).
int x[25]={
    1994, 1995, 1997, 1998, 1999, 2000, 2001, 2002,
    2004, 2005, 2006, 2007, 2008, 2009, 2011, 2012,
    2013, 2014, 2015, 2017, 2018, 2019, 2020, 2022,
    2023
};
// A cada año le corresponde una población; estas poblaciones se usan para construir el trazador.
int y[25]={
    1475716, 1452774, 1421494, 1411206, 1403578, 1397001,
    1388174, 1379438, 1362682, 1354847, 1346885, 1340709,
    1337078, 1334528, 1327366, 1322615, 1317920, 1314457,
    1314580, 1317430, 1321972, 1326822, 1329675, 1350093,
    1367195
};
// Años subrayados (datos de prueba).
int tiempoprueba[5]={1996,2003,2010,2016,2021};
// Población subrayada (valores reales de los años de prueba).
int poblacionprueba[5]={1434655,1370849,1331450,1315850,1331750};

int i;
int j;
// Coeficientes de cada polinomio Sj(x) = aj + bj(x-xj) + cj(x-xj)^2 + dj(x-xj)^3.
double a[25];
double b[24];
double c[25];
double d[24];
// Sistema de ecuaciones A c = Y para hallar los coeficientes c.
double A[25][25];
double Y[25];
// Longitud de cada intervalo, h[j] = x[j+1] - x[j].
double h[24];
// Aproximaciones del trazador en los años de prueba.
double s[5];
double factor,suma,aproximacion;
double errorAbsoluto,errorRelativo;

int k;
int main(){
    // Se calculan las a (son los valores de la población en los nodos).
    for(j=0; j<=24; j++){
        a[j]=y[j];
    }
    // Se calculan las h.
    for(j=0; j<=23; j++){
        h[j]=x[j+1]-x[j];
    }
    // Se inicializan las matrices en cero.
    for(i=0; i<=24; i++){
        Y[i]=0;
        for(j=0; j<=24; j++){
            A[i][j]=0;
        }
    }
    // Condiciones de frontera naturales del sistema A c = Y: c0 = 0 y c24 = 0 (S''=0 en los extremos).
    A[0][0]=1;
    A[24][24]=1;
    Y[0]=0;
    Y[24]=0;

    for(i=1; i<=23; i++){
        // Se calculan las demás componentes de la matriz A (es tridiagonal).
        A[i][i-1]=h[i-1];
        A[i][i]=2*(h[i-1]+h[i]);
        A[i][i+1]=h[i];
        // Se calculan las componentes del vector Y.
        Y[i]=(3.0/h[i])*(a[i+1]-a[i])-(3.0/h[i-1])*(a[i]-a[i-1]);
    }
    // Eliminación gaussiana para obtener las c.
    for(i=0; i<=23; i++){
        for(j=i+1; j<=24; j++){
            factor=A[j][i]/A[i][i];
            for(k=i; k<=24;k++){
                A[j][k]=A[j][k]-factor*A[i][k];
            }
            Y[j]=Y[j]-factor*Y[i];
        }
    }
    // Sustitución hacia atrás.
    for(i=24; i>=0; i--){
        suma=Y[i];
        for(j=i+1;j<=24;j++){
            suma=suma-A[i][j]*c[j];
        }
        // Se obtienen y se almacenan los coeficientes c.
        c[i]=suma/A[i][i];
    }
    // Se calculan b y d.
    for(i=0; i<=23; i++){
        b[i]=(a[i+1]-a[i])/h[i]-(h[i]/3.0)*(2*c[i]+c[i+1]);
        d[i]=(c[i+1]-c[i])/(3.0*h[i]);
    }
    // Se calculan las aproximaciones.
    cout<<fixed<<setprecision(2);
    cout<<"Estos son los resultados del trazador cubico"<<endl;
    cout<<"**********************************************"<<endl;
    cout<<"Anio\tPoblacion real\tAproximacion S(x)\tError relativo (%)"<<endl;
    // Se usan 5 de los 24 polinomios Sj(x): cada año subrayado (1996, 2003, 2010, 2016, 2021) cae en un
    // intervalo específico del trazador, y de eso depende en qué polinomio cúbico se evalúa.
    for(k=0; k<5; k++){
        // Se busca el intervalo al que pertenece el año y se evalúa en el polinomio de ese intervalo.
        for(j=0;j<=23;j++){
            if(tiempoprueba[k]>=x[j] && tiempoprueba[k]<=x[j+1]){
                // Se evalúa el año en el polinomio cúbico correspondiente para aproximar la población.
                s[k]=a[j]+b[j]*(tiempoprueba[k]-x[j])
                     +c[j]*(tiempoprueba[k]-x[j])*(tiempoprueba[k]-x[j])
                     +d[j]*(tiempoprueba[k]-x[j])*(tiempoprueba[k]-x[j])*(tiempoprueba[k]-x[j]);
            }
        }
        // Se calcula el error absoluto.
        errorAbsoluto=poblacionprueba[k]-s[k];
        if(errorAbsoluto<0){
            errorAbsoluto=errorAbsoluto*(-1);
        }
        // Se calcula el error relativo porcentual.
        errorRelativo=(errorAbsoluto/poblacionprueba[k])*100;

        // Se muestran los resultados.
        cout<<tiempoprueba[k]<<"\t"
            <<poblacionprueba[k]<<"\t\t"
            <<s[k]<<"\t\t"
            <<setprecision(6)<<errorRelativo<<setprecision(2)<<endl;
    }
    cout<<"***********************************"<<endl;
    return 0;
}
