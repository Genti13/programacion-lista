#include "lista.h"

void crearLista(tLista * p)
{
    *p = NULL; //Cuando se Crea la Lista, esta apunta a NULL
    //Despues se le agregaran los nodos
}

int listaVacia(const tLista * p)
{
    return *p == NULL; //Si la pila esta vacia es porque todavia no tiene nodos
}

int listaLlena(const tLista * p, unsigned cantBytes)
{
    tNodo * aux = (tNodo *)malloc(sizeof(tNodo));
    void * info = malloc(cantBytes);

    free(aux);
    free(info);

    return aux == NULL || info == NULL; //Si no se pudo reservar memoria
}

int vaciarLista(tLista *p)
{
    int cant = 0;

    tNodo * aux = *p;

    while(*p) //Mientras que haya nodos
    {
        aux = *p; //Apuntan al mismo lugar

        *p = aux->sig; //Se apunta al siguiente

        free(aux->info); //Se Elimina
        free(aux);

        cant++; //????? Para Saber cuantos nodos habia?
    }

    return cant;
}

/*************************/
/**********PONER**********/
/*************************/

int ponerAlComienzo(tLista * p, const void *d, unsigned cantBytes)
{
    tNodo * nue;

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
            (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->info,d,cantBytes);

    nue->tamInfo = cantBytes;
    nue->sig = *p;

    *p = nue;

    return TODO_BIEN;
}

int ponerAlFinal(tLista * p, void * d, unsigned cantBytes)
{
    //Creamos el nodo nuevo
    tNodo * nue;

    //Vamos hasta el final de la lista
    while(*p)
    {
        p=&(*p)->sig;
    }

    //Vemos si podemos reservar memoria
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
            (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);

        return SIN_MEM;
    }

    //Copiamos la info de d en el campo info del nuevo nodo
    memcpy(nue->info,d, cantBytes);

    //Completamos el nodo con los datos restantes
    nue->tamInfo = cantBytes;
    nue->sig = NULL;

    //Se apunta al nodo nuevo, osea, se lo agrega a la lista
    *p = nue;

    return TODO_BIEN;
}

/*************************/
/**********SACAR**********/
/*************************/

int sacarPrimero(tLista *p, void *d, unsigned cantBytes)
{
    tNodo *aux = *p;

    if(aux == NULL)
    {
        return 0;
    }

    *p = aux->sig;

    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo)); //Copio la info
    //dentro de d, porque sacar tambien permite recuperar la info

    free(aux->info);
    free(aux);

    return TODO_BIEN;
}

int sacarUltimo(tLista * p, void * d, unsigned cantBytes)
{
    while((*p)->sig)
    {
        p=&(*p)->sig;
    }

    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));

    free((*p)->info);
    free(*p);

    *p=NULL;

    return TODO_BIEN;
}

/*************************/
/***********VER***********/
/*************************/

int verPrimero(const tLista * p, void * d, unsigned cantBytes)
{
    if(*p == NULL)
    {
        return 0;
    }

    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));

    return TODO_BIEN;
}

int verUltimo(const tLista * p, void * d, unsigned cantBytes)
{
    if(*p == NULL)
    {
        return 0;
    }

    while((*p)->sig)
    {
        p=&(*p)->sig;
    }
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));

    return TODO_BIEN;
}

/******************************************************************************/
/******************************************************************************/

int ponerEnOrden(tLista *p, const void * d, unsigned cantBytes,
                 int (*comparar) (const void *, const void *),
                 int (*acumular)(void **, unsigned *, const void *, unsigned))
{
    tNodo * nue; //El nuevo nodo a agregar

    while(*p && comparar((*p)->info, d) < 0) //La funcion de comparacion depende
        //de lo que este haciendo, es generico asi que se va a tener que definir
        //un comportamiento para evaluar cuando algo es mayor o menor que otro
        //y retornar menor que 0 si el elemento a insertar es mas chico que
        //el del nodo que estamos comparando
        //ACLARACION: Esto en realidad depende del orden en el que se este
        //guardando, ASCENDENTE O DESCENDENTE
    {
        p = &(*p)->sig;
    }

    if(*p && comparar((*p)->info, d) == 0) //Si los elemento son iguales
    {
        if(acumular) //aca acumular no tiene parametros porque al llamar a
            //ponerEnOrden si no quiere que se acumule con un valor con una clave
            //identica se puede pasar NULL y todo este bloque se ignoraria
        {
            if(!acumular(&(*p)->info, &(*p)->tamInfo, d, cantBytes))
            {
                return SIN_MEM;
            }
            return CLA_DUP;
        }

    }
    /****Ahora reservo la memoria del nodo*****/
    if((nue = (tNodo *) malloc(sizeof(tNodo))) == NULL ||
            (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    /****Ahora Cargamos la info****/

    memcpy(nue->info,d,cantBytes);

    nue->tamInfo = cantBytes;
    nue->sig = *p;

    *p = nue;

    return TODO_BIEN;
}

/******************************************************************************/
/******************************************************************************/

void ordenar(tLista *p, int (*comparar)(const void *, const void *))
{
    tLista *pri = p;

    if(*p == NULL)
    {
        return;
    }

    while((*p)->sig)
    {
        if(comparar((*p)->info, (*p)->sig->info) > 0)
        {
            tLista * q = pri;
            tNodo * aux = (*p)->sig;

            (*p)->sig = aux->sig;

            while(comparar((*q)->info, aux->info) > 0)
            {
                q = &(*q)->sig; //La DDM del snodo iguiente de q
            }

            aux->sig = *q;
            *q = aux;
        }
        else
        {
            p = &(*p)->sig;
        }
    }
}

/******************************************************************************/
/******************************************************************************/

int mostrarLista(const tLista * p,
                 void(*mostrar)(const void *, FILE *), FILE * pf )
{
    int cant = 0;

    while(*p)
    {
        mostrar((*p)->info, pf); //Podria no ser un FILE y ser por pantalla?
        p = &(*p)->sig;
        cant++;
    }

    return cant;
}

int mostrarListaAlReves(const tLista *p,
                        void(*mostrar)(const void *, FILE *), FILE *pf)
{
    if(*p)
    {
        int n = mostrarListaAlReves(&(*p)->sig, mostrar,pf); //Recursividad

        mostrar((*p)->info, pf);

        return n+1; //Para que el n?
    }

    return 0;
}
