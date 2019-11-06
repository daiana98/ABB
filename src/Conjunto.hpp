
template <class T>
Conjunto<T>::Conjunto():_raiz(nullptr),_cardinal(0){
    // Completar
}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
    int cont=cardinal();
    while(cont>0){
        remover(minimo());
        cont=cont-1;
    }

}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res=false;
    if(cardinal()==0){
        return res;
    }else{
        Nodo* actual=_raiz;
        while(actual!= nullptr) {
            if(actual->valor==clave) {
                res= true;
            }else {
                if (clave < actual->valor) {
                    actual = actual->izq;
                } else {
                    actual = actual->der;
                }
            }
        }
    }
    assert(false);
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(!pertenece(clave)){
        _cardinal=_cardinal+1;
        Nodo* actual=_raiz;
        Nodo* in= new Nodo(clave);
        //preguntar si es la raiz
        if(actual==nullptr){
            _raiz=in;
        }else{
        while ((clave > actual->valor && actual->der!=nullptr)||(clave<actual->valor && actual->izq!=nullptr))
        {
            if(clave>actual->valor){
                actual=actual->der;
            }else{
                actual=actual->izq;
            }
        }
        if(clave>actual->valor){// POR DERECHA pregunto si el valor que voy a ingresar es mayor a la raiz
            actual->der=in;//modifico el hijo derecho de la raiz agregandole la clave
            actual->der->sig=actual->sig;//le pongo el siguiente al nodo que agrege que es el siguiente de su raiz
            actual->sig=clave;//modifico el siguiente de la raiz que ahora es el valor que ingrese
        }else{
            actual->izq=in;//lo agrego en el hijo izquierdo
            actual->izq->sig=actual->valor;//el siguiente del valor que inserte es su padre
            if(clave!=minimo()){//si lo que inserte es distinto del minimo BUSCO SU ANTERIOR Y HAGO TODA LA CAGADA
            T sigui = actual->valor;//me guardo el padre del elemento que inserte recien
            T anterior = minimo();//me guardo el minimo
            //QUE PASA SI ES EL MINIMO
            //QU PASA SI EL QUE AGREGO ES EL MINIMO
            
            while (siguiente(anterior)!=sigui)//mientras el siguiente de donde estoy sea distinto del siguiente que estoy buscando sigo buscqando
            {
                anterior=siguiente(anterior);//uso la funcion siguiente
            }
           
            //cuando sale del while es por que el min tiene la clave del nodo que busco
            Nodo* act=_raiz;//ENCONTRE EL ANTERIOR DEL NODO QUE INSERTE POR IZQ
            //este while encuentra el nodo donde se encuentra el anterio del padre 
            while(act->valor!=anterior){
                if(anterior>act->valor){
                    act=act->der;
                }else{
                    act=act->izq;
                }
            }
            //finalmente conecto el nodo que tenia como siguiente al padre donde inserte el valor, 
            //ese nodo ahora va a tener como siguiente el elemento que inserte 
            act->sig=clave;
            }
        }
        
    }
    }
    
    //assert(false);
    
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(pertenece(clave)){
    Nodo* apuntaValor=_raiz;
    Nodo* padre=_raiz;
    //busco el padre del nodo
    while(padre->izq->valor==clave || padre->der->valor==clave){
        if(clave>padre->valor){
            padre=padre->der;
        }else{
            padre=padre->izq;
        }
    }//tengo al padre del nodo que quiero borrar
    //el puntero que apunta al valor
    while(apuntaValor->valor!=clave){
        if(clave>apuntaValor->valor){
            apuntaValor=apuntaValor->der;
        }else{
            apuntaValor=apuntaValor->izq;
        }
    }

    if(apuntaValor->izq==nullptr && apuntaValor->der==nullptr){//CASO 1 el que quiero remover no tiene HIJOS
        if(clave!=minimo()){
        T BuscaAnterior=minimo();//este va a buscar el anterior del que quiero borrar
        while(siguiente(BuscaAnterior)!=clave){
            BuscaAnterior=siguiente(BuscaAnterior);
        }//sale cuando ya encontre el antrior del que quiero borrar
        Nodo* act=_raiz;
        while (act->valor!=BuscaAnterior)
        {
            if(BuscaAnterior>act->valor){
                act=act->der;
            }else{
                act=act->izq;
            }
        }
        act->sig=siguiente(clave);//el siguiente del anterior del que quiero borrar ahoraapunta al siguiente del siguiente del valor que me dieron para remover
        delete apuntaValor;//borre el nodo que me pidieron
    }else{//la clave es el minimo
        Nodo* buscoMinimo=_raiz;
        while(buscoMinimo->valor!=minimo()){
            buscoMinimo=buscoMinimo->izq;
        }//encontre el puntero del minimo
        delete buscoMinimo;
    }
    }
    if(apuntaValor->izq!=nullptr || apuntaValor->der!=nullptr){// CASO 2:hijo izquierdo
        /*if(padre->izq->valor==clave){//si la clave que quiero remover es hijo por izq
            //el siguiente del hijo izq es el padre 
            apuntaValor->izq->sig=padre->valor;
            //el padre ahora apunta al hijo izq sin el clave que quiero borrar
            padre->izq=apuntaValor->izq;
            //borro el valor que quiero borrar
            delete apuntaValor;
        }else{
            //la clave a borrar es hijo por derecha y tiene hijos por izq
            //busco el puntero al siguiente

        }
        */
       //BUSCO ANTERIOR Y SIGUIENTE
       T siguiDeElem=siguiente(apuntaValor->valor);//me guardo el siguiete del elemento
       //me guardo el minimo para moverlo con siguiente
       T encontrarAnterior=minimo();
       //encuentro el anterior del elemento que quiero borrar
       while(siguiente(encontrarAnterior)!=clave){
           encontrarAnterior=siguiente(encontrarAnterior);
       }
       //BUSCO EL PUNTERO QUE APUNTA A ANTERIOR
        Nodo* buscador=_raiz;
       while(buscador->valor!=encontrarAnterior){
           if(encontrarAnterior>buscador->valor){
           buscador=buscador->der;
            }else{
                buscador=buscador->izq;
            }
       }
       //actualize el siguiente del anterior que quiero borrar
       buscador->sig=siguiDeElem;
       //RECONECTO LOS NODOS
       //el elemnto a borrar es hijo izquierdo de padre
       if(padre->izq->valor==clave){
           if(apuntaValor->izq!=nullptr){//tiene hijo por izquierda
                padre->izq=apuntaValor->izq;//reconecte los nodos
           }else{//tiene hijo por derecha
                padre->izq=apuntaValor->der;
           }
       }else{//el elemento a borrar es hijo derecho de padre
                if(apuntaValor->izq!=nullptr){//tiene hijo por izquierda
                padre->izq=apuntaValor->izq;//reconecte los nodos
           }else{//tiene hijo por derecha
                padre->izq=apuntaValor->der;
           }
       }
    
       
    }
    
    if(apuntaValor->izq!=nullptr && apuntaValor->der!=nullptr){
         //BUSCO ANTERIOR Y SIGUIENTE
       T siguiDeElem=siguiente(apuntaValor->valor);//me guardo el siguiete del elemento
       //me guardo el minimo para moverlo con siguiente
       T encontrarAnterior=minimo();
       //encuentro el anterior del elemento que quiero borrar
       while(siguiente(encontrarAnterior)!=clave){
           encontrarAnterior=siguiente(encontrarAnterior);
       }
       //BUSCO EL PUNTERO QUE APUNTA A ANTERIOR
        Nodo* buscador=_raiz;
       while(buscador->valor!=encontrarAnterior){
           if(encontrarAnterior>buscador->valor){
           buscador=buscador->der;
            }else{
                buscador=buscador->izq;
            }
       }
       
       //me guardo el valor del anterior
       T ante=buscador->valor;
       //remuevo el anterior
       remover(encontrarAnterior);
        //cambio los valores de la clave por su anterior
       apuntaValor->valor=ante;

    }
    
    
    }
    assert(false);
}


template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    if(pertenece(clave)){
    Nodo* actual=_raiz;
    if(clave!=maximo()){//si es el maximo entonces no tiene siguiente
    
    while(actual->valor!=clave){
        if(clave>actual->valor){
            actual=actual->der;
        }else{
            actual=actual->izq;
        }
    }
    }
    return actual->sig;
    }
    
    assert(false);
    
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual=_raiz;
    while (actual->izq!=nullptr)
    {
        actual=actual->izq;
    }
    
    assert(false);
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual=_raiz;
    while (actual->der!=nullptr)
    {
        actual=actual->der;
    }
    
    assert(false);
    return actual->valor;
    
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
    //assert(false);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

