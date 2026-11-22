// De: Santiago Hernandez Morales y Maria Paula Rodriguez Ruiz
// Algoritmo de Lagrange
// Compilar: g++ -std=c++17 -o lagrange lagrange.cpp
// Ejecutar: ./lagrange

#include <iostream>
#include <iomanip>

using namespace std;

// Estos son los años de Estonia que se van a usar para construir el polinomio de Lagrange.
// Nodos que se van a usar para construir el polinomio (x0, x1, ..., x24).
int x[25]={
    1994, 1995, 1997, 1998, 1999, 2000, 2001, 2002,
    2004, 2005, 2006, 2007, 2008, 2009, 2011, 2012,
    2013, 2014, 2015, 2017, 2018, 2019, 2020, 2022,
    2023
};
// A cada año le corresponde una población; estas poblaciones son los valores f(xi) del polinomio.
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

int k;
double m;
int i=0;
int j;
double errorAbsoluto;
double errorRelativo;
double aproximacion;

int main(){

    cout<<fixed<<setprecision(2);
    cout<<"Aproximaciones con el polinomio de Lagrange (1996, 2003, 2010, 2016, 2021):"<<endl;
    cout<<"***************************************************************************"<<endl;
    cout<<""<<endl;
    cout<<"Anio\tPoblacion real\tAproximacion\tError relativo (%)"<<endl;
    for(k=0; k<=4;k++){
        // El año a probar se guarda en m; m toma los valores 1996, 2003, 2010, 2016 y 2021 en cada iteración.
        m=tiempoprueba[k];
        double suma=0;
        // Se construye el polinomio interpolador de Lagrange con x0, x1, ..., x24 (sin los años de prueba).
        for(i=0; i<=24; i++){
            // Se inicializa en 1 la productoria del polinomio base de Lagrange Li(m).
            double productoria=1;
            for(j=0; j<=24; j++){
                if(i!=j){
                    // Se multiplican las fracciones (m - xj)/(xi - xj) del polinomio base Li.
                    productoria*=(m-x[j])/(x[i]-x[j]);
                }
            }
            // Cada polinomio base se multiplica por su f(xi) y los productos se van sumando.
            suma=suma+y[i]*productoria;
        }
        // El resultado de la suma es la aproximación de la población en ese año.
        aproximacion=suma;
        // Se calcula la diferencia absoluta.
        errorAbsoluto=poblacionprueba[k]-aproximacion;
        // Si la diferencia es negativa se cambia de signo para que el error absoluto quede positivo.
        if(errorAbsoluto<0){
            errorAbsoluto=errorAbsoluto*(-1);
        }
        // El error relativo porcentual es el error absoluto dividido entre la población real, por 100.
        errorRelativo=(errorAbsoluto/poblacionprueba[k])*100;
        // Se imprimen los resultados.
        cout<<tiempoprueba[k]<<"\t"
            <<poblacionprueba[k]<<"\t\t"
            <<aproximacion<<"\t"
            <<setprecision(6)<<errorRelativo<<setprecision(2)<<endl;
    }
    cout<<"*************************"<<endl;
    return 0;
}
