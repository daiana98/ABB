
template <class T>
Conjunto<T>::Conjunto():_raiz(nullptr),_cardinal(0){
    // Completar
}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar


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
        while ((clave > actual->valor && actual->der!=nullptr)||(clave<actual->valor && actual->izq!=nullptr))
        {
            if(clave>actual->valor){
                actual=actual->der;
            }else{
                actual=actual->izq;
            }
        }
        if(clave>actual->valor){//pregunto si el valor que voy a ingresar es mayor a la raiz
            actual->der=in;//modifico el hijo derecho de la raiz agregandole la clave
            actual->der->sig=actual->sig;//le pongo el siguiente al nodo que agrege que es el siguiente de su raiz
            actual->sig=clave;//modifico el siguiente de la raiz que ahora es el valor que ingrese
        }else{
            actual->izq=in;//lo agrego en el hijo izquierdo
            actual->izq->sig=actual->valor;//el siguiente del valor que inserte es su padre
            T sigui = actual->valor;//me guardo el padre del elemento que inserte recien
            T min = minimo();//me guardo el minimo
            //QUE PASA SI ES EL MINIMO
            //QU PASA SI EL QUE AGREGO ES EL MINIMO
            while (siguiente(min)!=sigui)//mientras el suiguiente de donde estoy sea distinto del siguiente que estoy buscando sigo buscqando
            {
                min=siguiente(min);//uso la funcion siguiente
            }
            //cuando sale del while es por que el min tiene la clave del nodo que busco
            Nodo* act=_raiz;
            //este while encuentra el nodo donde se encuentra el anterio del padre 
            while(act->valor!=min){
                if(min>act->valor){
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
    
    assert(false);
    
}

template <class T>
void Conjunto<T>::remover(const T& clave) {

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

