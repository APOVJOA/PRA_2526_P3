#ifndef DICT_H
#define DICT_H
#include <string>

template <typename V> 
class Dict {
    public:
    //Inserta el par key->value en el diccionario. 
    //Lanza una excepción std::runtime_error si key ya existe en el diccionario.
        virtual void insert(std::string key, V value)=0;
    //Busca el valor correspondiente a key. Devuelve el valor value 
    //asociado si key está en el diccionario. Si no se encuentra, lanza una excepción std::runtime_error.    
        virtual V search(std::string key)=0;
    //Elimina el par key->value si se encuentra en el diccionario. 
    //Si no se encuentra, lanza una excepción std::runtime_error.
        virtual V remove(std::string key)=0;
    //Devuelve el número de elementos que tiene el Diccionario.
        virtual int entries()=0;
};

#endif