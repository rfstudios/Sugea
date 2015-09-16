#include <cstdlib>
#include "miniwin.h"
using namespace miniwin;
using namespace std;

int tablero[128][72];
int sDirec=0;   //0 = Derecha; 1 = Izquierda; 2 = Arriba; 3 = Abajo;
int x=90, y=36, tam=3;

void pintaPixel(int _x, int _y, int _color)
{
    color(_color);
    rectangulo_lleno(10*_x,10*_y,10*_x+10,10*_y+10);
}

void creaPastilla()
{
    int _x, _y;

    do
    {
        _x=rand()%128;
        _y=rand()%72;
    }while(tablero[_x][_y]!=0);

    tablero[_x][_y]=-1;
}

bool Input()
{
    int t=tecla();
    bool salir=false;
    switch(t)
    {
        case ARRIBA:
            if(sDirec!=3){sDirec=2;}
            break;
        case ABAJO:
            if(sDirec!=2){sDirec=3;}
            break;
        case IZQUIERDA:
            if(sDirec!=0){sDirec=1;}
            break;
        case DERECHA:
            if(sDirec!=1){sDirec=0;}
            break;
    }

    return salir;
}

bool Update()
{
    int _x, _y;
    switch(sDirec)
    {
        case 0:
            _x=1; _y=0;
            break;
        case 1:
            _x=-1; _y=0;
            break;
        case 2:
            _x=0; _y=-1;
            break;
        case 3:
            _x=0; _y=1;
            break;
    }

    x+=_x;
    y+=_y;

    if(x>127){x=0;} else if(x<0){x=127;}
    if(y>71){y=0;} else if(y<0){y=71;}

    if(tablero[x][y]==-1)
    {
        tam++;
        creaPastilla();
    }
    if(tablero[x][y]==-2 || tablero[x][y]>0)
    {
        return true;
    }

    tablero[x][y]=tam;
    return false;
}
void Render()
{
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<72;j++)
        {
            if(tablero[i][j]>0)
            {
                //Pintamos serpiente
                pintaPixel(i,j,AMARILLO);
                tablero[i][j]--;
            }
            else if(tablero[i][j]==0)
            {
                //Pintamos negro
                pintaPixel(i,j,NEGRO);
            }
            else if(tablero[i][j]==-1)
            {
                //Pintamos pastilla
                pintaPixel(i,j,ROJO);
            }
            else if(tablero[i][j]==-2)
            {
                //Pintamos pared
                pintaPixel(i,j,VERDE);
            }
        }
    }
}

int main()
{
    vredimensiona(1280,720);

    int tec;
    do
    {
        texto(575,360,"Ongi etorri Sugea jokora");
        tec=tecla();
        rand();
        espera(3);
    }while(tec!=ESPACIO);

    for(int i=0;i<128;i++)
    {
        for(int j=0;j<72;j++)
        {
            tablero[i][j]=0;
        }
    }

    creaPastilla();
    bool salida=false;
    do
    {
        salida=Input();    //Detección de tecla;
        salida=Update();   //Lógica del programa (movimiento de la serpiente);
        Render();           //Pintado de la pantalla;

        refresca();
        if(salida){break;}
        espera(60);
    }while(!salida);

    vcierra();
    return 0;
}
