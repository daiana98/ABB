
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
                return true;
            }else {
                if (clave < actual->valor) {
                    actual = actual->izq;
                } else {
                    actual = actual->der;
                }
            }
        }
    }
    //assert(false);
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
    _cardinal--;
    if (clave == _raiz->valor) {
        Nodo* actual=_raiz;
        if (_raiz->der == nullptr && _raiz->izq == nullptr) {//caso1: no tine hijos
            delete actual;        
             _raiz == nullptr;       
        }        
        if (_raiz->der == nullptr || _raiz->izq == nullptr) {//caso 2; tiene un hijo
            //ES POR IZQUIERDA ENTONCES TIENE ANTERIOR Y NO TIENE SIGUIENTE
            if (_raiz->izq != nullptr) {
                //BUSCO EL ANTERIOR
                _raiz = _raiz->izq;
                delete actual;
            } else {//TIENE UN HIJO POR DERECHA
                _raiz = _raiz->der;
                delete actual;
            }
                }
        if (_raiz->der != nullptr && _raiz->izq != nullptr) {//CASO2: TIENE DOS HIJOS
          //ME CREO UN NODO NUEVO con el valor del siguiente hago remove del siguiente harreglo sus izq y der padre yo soyel siguietne
            Nodo *sucesor = new Nodo(_raiz->sig);
            remover(_raiz->sig);
            sucesor->der = _raiz->der;
            sucesor->izq = _raiz->izq;
            _raiz = sucesor;
        }
    }else{//NO ES RAIZ TENGO QUE HACER LOS TRES CASOS DE VUELTA
    //busco al padre
    Nodo* padre = _raiz;
    while(padre->izq->valor!=clave || padre->der->valor!=clave){
        if(clave>padre->valor){
            padre=padre->der;
        }else{
            padre=padre->izq;
        }
    }
    //busco al que apunta a la clave
    Nodo* apuntaValor=_raiz;
    while(apuntaValor->valor!=clave){
        if (clave>apuntaValor->valor){
            apuntaValor=apuntaValor->der;
        }else{
            apuntaValor=apuntaValor->izq;
        }
    }
    //caso 1: QUIERO ELIMINAR UNA HOJA
    if (apuntaValor->izq==nullptr && apuntaValor->der==nullptr){
        //ME ASEGURO QUE SEA DISTINTO DEL MINIMO POR QUE EL MIN NO TIENE ANTERIOR
        if(minimo()!=apuntaValor->valor){
        //busco al valor anterior por que no es el MINIMO Y tiene un anterior
        T anterior=minimo();
        while (siguiente(anterior)!=apuntaValor->valor){
            anterior=siguiente(anterior);
        }
        //busco al nodo anterior
        Nodo* buscaAnterior=_raiz;
        while(buscaAnterior->valor!=anterior){
            if (anterior>buscaAnterior->valor){
                buscaAnterior=buscaAnterior->der;
            }else{
                buscaAnterior=buscaAnterior->izq;
            }
        }
        buscaAnterior->sig=siguiente(clave);
        if(padre->der->valor==clave){
            delete apuntaValor;
            padre->der==nullptr;
        }else{
            delete apuntaValor;
            padre->izq==nullptr;
        }
    }
    //EN ESTE CASO ES EL MINIMO ASI QUE NO TIENE ANTERIOR
    else{
        delete apuntaValor;
        if(padre->der->valor==clave){
            delete apuntaValor;
            padre->der==nullptr;
        }else{
            delete apuntaValor;
            padre->izq==nullptr;
        }
    }
}//ES UN HIJO
if(apuntaValor->der==nullptr || apuntaValor->izq ==nullptr){
    //busco el anterior
    T anterior=minimo();
        while (siguiente(anterior)!=apuntaValor->valor){
            anterior=siguiente(anterior);
        }
        //busco al nodo anterior
        Nodo* buscaAnterior=_raiz;
        while(buscaAnterior->valor!=anterior){
            if (anterior>buscaAnterior->valor){
                buscaAnterior=buscaAnterior->der;
            }else{
                buscaAnterior=buscaAnterior->izq;
            }
        }
    buscaAnterior->sig=siguiente(clave);
    //la clave que borro viene por der
    if(padre->der->valor==clave){
        if(apuntaValor->izq!=nullptr){
        //hijo por izq
        padre->der=apuntaValor->izq;
        }else{
        padre->der=apuntaValor->der;
        }
    }else{
        if(apuntaValor->izq!=nullptr){
        //hijo por izq
        padre->izq=apuntaValor->izq;
        }else{
        padre->izq=apuntaValor->der;
        }
    }
    delete apuntaValor;
    
}//CASO 3: DOS HIJOS
if(apuntaValor->der!=nullptr && apuntaValor->izq !=nullptr){
    //ME CREO UN NODO NUEVO con el valor del siguiente hago remove del siguiente harreglo sus izq y der padre yo soyel siguietne
            Nodo *sucesor = new Nodo(siguiente(clave));
            remover(apuntaValor->sig);
            sucesor->der = apuntaValor->der;
            sucesor->izq = apuntaValor->izq;
            if(padre->der->valor==clave){
                padre->der=sucesor;
            }else{
                padre->izq=sucesor;
            }
            delete apuntaValor;
            //busco al anterior de la clave
         //busco al valor anterior por que no es el MINIMO Y tiene un anterior
        T anterior=minimo();
        while (siguiente(anterior)!=clave){
            anterior=siguiente(anterior);
        }
        //busco al nodo anterior
        Nodo* buscaAnterior=_raiz;
        while(buscaAnterior->valor!=anterior){
            if (anterior>buscaAnterior->valor){
                buscaAnterior=buscaAnterior->der;
            }else{
                buscaAnterior=buscaAnterior->izq;
            }
        }
        buscaAnterior->sig=sucesor->valor;
}
}
    }
    //assert(false);
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
    
    //assert(false);
    
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual=_raiz;
    while (actual->izq!=nullptr)
    {
        actual=actual->izq;
    }
    
    //assert(false);
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual=_raiz;
    while (actual->der!=nullptr)
    {
        actual=actual->der;
    }
    
    //assert(false);
    return actual->valor;
    
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
    //assert(false);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    //assert(false);
}

