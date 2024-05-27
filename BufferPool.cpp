#include "./BufferPool.h"

BufferPool::BufferPool(/* args */) {}

BufferPool::~BufferPool() {};

void BufferPool::agregarNuevaPaginaBufferPool(int numFrame, int numPagina)
{
    cout<<"-----------------agregarNuevaPaginaBufferPool() -----------------"<<endl;

    if (this->vectorFramesBufferPool[numFrame].paginaEnFrame.vectorRegistrosEnPagina.empty())
    {
        this->vectorFramesBufferPool[numFrame].leerDatosEnPaginaDeFrame(numPagina);
    }
    else
    {
        this->vectorFramesBufferPool[numFrame].paginaEnFrame.vectorRegistrosEnPagina.clear();
        this->vectorFramesBufferPool[numFrame].leerDatosEnPaginaDeFrame(numPagina);
    }

}

void BufferPool::mostrarFramePagina(int numFrame)
{
    cout<<"-------------------------mostrarFramePagina()--------------------------"<<endl;
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.mostrarContenidoDePagina();
}

void BufferPool::lecturaOescrituraPagina(int numFrame)
{
    cout<<"-------------------------lecturaOescrituraPagina()----------------------"<<endl;
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.leerOescribirEnPagina();
}

void BufferPool::agregarContenidoPaginaAbloque(int numFrame, int numPaginaEliminada)
{
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.agregarContenido(numPaginaEliminada);
}