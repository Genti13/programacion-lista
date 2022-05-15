#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_BIEN 0
#define SIN_MEM 1
#define CLA_DUP 2

#define minimo(X, Y) ((X) <= (Y) ? (X) : (Y))

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;

void crearLista(tLista * p);

int listaVacia(const tLista * p);

int listaLlena(const tLista * p, unsigned cantBytes);

int vaciarLista(tLista * p);


/***Poner***/

int ponerAlComienzo(tLista * p, const void * d, unsigned cantBytes);

int sacarPrimero(tLista * p, void * d, unsigned cantBytes);

int ponerEnOrden(tLista * p, const void * d, unsigned cantBytes,
                 int (*comparar)(const void *, const void *),
                 int (*acumular)(void **, unsigned *, const void*, unsigned));

/***Sacar***/

int sacarPrimero(tLista * p, void * d, unsigned cantBytes);

int sacarUltimo(tLista * p, void * d, unsigned cantBytes);


/***Ver***/

int verPrimero(const tLista *p, void * d, unsigned cantBytes);

int verUltimo(const tLista * p, void * d, unsigned cantBytes);

/***Mostrar***/

int mostrarLista(const tLista * p,
                 void (*mostrar)(const void*, FILE *), FILE * pf);

int mostrarListaAlReves(const tLista * p,
                        void (*mostrar)(const void *, FILE *), FILE * pf);

/***JUMANJI aka Ordenar y poner en Orden***/

int ponerEnOrden(tLista * p, const void *d, unsigned cantBytes,
                 int (*comparar)(const void *, const void *),
                 int (*acumular)(void **, unsigned *, const void *, unsigned));

void ordenar(tLista *p, int(*comparar)(const void *, const void *));

#endif // LISTA_H_INCLUDED
