#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <vector>
#include <iostream>

#include "./Frame.cpp"
using namespace std;

class BufferPool 
{
    public:
        //atributos
        int capacidadDeCadaFrame;
        vector<Frame> vectorFramesBufferPool;
    public:
        //Funciones
        BufferPool(/* args */);
        ~BufferPool();

        void agregarNuevaPaginaBufferPool(int numFrame, int numPagina);
        void mostrarFramePagina(int numPagina);
        void lecturaOescrituraPagina(int numPagina);
};

#endif