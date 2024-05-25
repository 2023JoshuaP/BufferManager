#include "./BufferManager.h"
#include <fstream>
using namespace std;

BufferManager::BufferManager(){}

BufferManager::~BufferManager(){}

void BufferManager::crearBufferPoolSegunNumFrames(int numFrames)
{
    this->bufferPool.vectorFramesBufferPool.resize(numFrames);

    this->pageTable.columnaFrameIdSize = numFrames;
    this->pageTable.columnPageIdSize = 0;
    this->pageTable.columnaDirtyIdSize = 0;
    this->pageTable.columnaPinCountSize = 0;
    this->pageTable.columnaLastUsedSize = 0;

    cout<<"inicializando pageTable"<<endl;
    this->pageTable.matrizPageTableLRU.resize(numFrames);

    for (int i = 0; i < numFrames; i++)
    {
        for (int j = 0; j < this->pageTable.numColumnasEnPageTable; j++)
        {
            this->pageTable.matrizPageTableLRU[i].resize(this->pageTable.numColumnasEnPageTable);
        }
    }
    
}

void BufferManager::establecerLimiteDeFrames(int pesoBytesBLoque)
{
    this->bufferPool.capacidadDeCadaFrame = pesoBytesBLoque;

    for (int i = 0; i < this->bufferPool.vectorFramesBufferPool.size(); i++)
    {
        this->bufferPool.vectorFramesBufferPool[i].capacidadBytesDeFrame = pesoBytesBLoque;
    }
    
}


void BufferManager::obtenerUnaPagina(int numPagina)
{
    cout<<"----------------obtenerUnaPagina()-------------------"<<endl;
    string resultadosParaEliminacionYCambios=this->pageTable.analizarPageTableParaAgregarPagina(numPagina);
    if (resultadosParaEliminacionYCambios=="eliminarPageSinEscrituraEnDisco")
    {
        //eliminarPageSinEscrituraEnDisco
        cout<<">>>>>>>> eliminarPageSinEscrituraEnDisco"<<endl;
        cout << "Datos cambiados segun LRU en Page Table" << endl;
        this->pageTable.mostrarPageTableLRU();
        this->pageTable.descontarPinCountApagina(numPagina);


        cout << "Aplicando cambios en Buffer Pool segun Page Table" << endl;
        cout << "Mandando a agregar la nueva Pagina" << endl;

        // int numFrameDePagina = this->pageTable.getNumFrameDeUnaPagina(numPagina);

        // this->bufferPool.agregarNuevaPaginaBufferPool(numFrameDePagina,numPagina);
        // this->bufferPool.mostrarFramePagina(numPagina);
    }
    else if(resultadosParaEliminacionYCambios=="eliminarPageConEscrituraEnDisco")
    {
        //eliminarPageConEscrituraEnDisco
        cout<<">>>>>>>> eliminarPageConEscrituraEnDisco"<<endl;
        cout << "Datos cambiados segun LRU en Page Table" << endl;
        this->pageTable.mostrarPageTableLRU();
        this->pageTable.descontarPinCountApagina(numPagina);
    }
    else//Aun hay espacios en el frame
    {
        cout<<">>>>>>>> normal NO hay eliminacion"<<endl;
        this->pageTable.mostrarPageTableLRU();
        //this->pageTable.descontarPinCountApagina(numPagina);

        cout << "Aplicando cambios en Buffer Pool segun Page Table" << endl;
        cout << "Mandando a agregar la nueva Pagina" << endl;

        int numFrameDePagina = this->pageTable.getNumFrameDeUnaPagina(numPagina);

        cout<<"Ingresando Página al BufferPoll dentro vector de Frames...."<<endl;
        this->bufferPool.agregarNuevaPaginaBufferPool(numFrameDePagina,numPagina);
        this->bufferPool.mostrarFramePagina(numFrameDePagina);

    }

}

/*

void BufferManager::obtenerUnaPagina(int numPagina)
{
    cout<<".-----------------------obtenerUnaPagina() ----------------------"<<endl;
    cout << "----------- Revisando Page Table para insertado de Pagina" << endl;
    if (this->pageTable.columnPageIdSize == 0)
    {
        cout<<"No tiene  ninguna página insertada"<<endl;
        cout<<"---- Insertando Datos de pagina a ser insertada en Page table..."<<endl;
        for (int i = 0; i < this->pageTable.numColumnasEnPageTable; i++)
        {
            if (i==0)
            {
                this->pageTable.matrizPageTableLRU[0][i]=numPagina;
                cout<<"frame id:0 - Page id establecida: "<<numPagina<<endl;
            }
            else if (i==2)
            {
                this->pageTable.matrizPageTableLRU[0][i]=1;
                cout<<"frame id:0 - Pin Count establecida: "<<numPagina<<endl;
            }
            else if (i==3)
            {
                this->pageTable.matrizPageTableLRU[0][i]=this->pageTable.matrizPageTableLRU[0][i]+1;
                cout<<"frame id:0 - Last Used establecida: "<<numPagina<<endl;
            }
            
            else
            {
                this->pageTable.matrizPageTableLRU[0][i]=0;
                cout<<"frame id:0 - Dirty Bit establecida: "<<0<<endl;
                cout<<"frame id:0 - Last used establecida: "<<0<<endl;
            }
            
            
        }
        cout<<"Datos de Page Table actualizado"<<endl;

        cout<<"$$ Primera Pagina, Segun Page Table insertando Pagina A Frame 0"<<endl;
        this->bufferPool.vectorFramesBufferPool[0].paginaEnFrame.recogerRegistros(numPagina);
        
        cout<<"Mostrando Page Table..."<<endl;
        this->pageTable.mostrarPageTableLRU();

        cout<<"Aumenta tamaño de pageTable.columnPageIdSize"<<endl;
        this->pageTable.columnPageIdSize++;
    }
    else
    {
        cout<<"SI tiene páginas insertada"<<endl;
        //this->pageTable.
        
    }
    
}

*/
void BufferManager::mostrarUnaPagina(int numPagina)
{
    cout<<"----------------------- mostrarUnaPagina -------------------------"<<endl;
    if (this->pageTable.verificarExistenciaDePagina(numPagina) == true)
    {
        cout << "Existencia de pàgina verificada Verificada" << endl;
        cout << "MOstrandoDichaPAgina" << endl;
        int numFrameDePagina = this->pageTable.getNumFrameDeUnaPagina(numPagina);
        this->bufferPool.vectorFramesBufferPool[numFrameDePagina].paginaEnFrame.mostrarContenidoDePagina();
        // despuès de mostrar termina su 
    }
    else
    {
        cout << "NO EXISTE DICHA PÀGINA" << endl;
        cout << "Procediendo a pedido de nueva pàgina..." << endl;
        //SI todo en page tabl esta ocupado, APLICA LRU
    }
    
    
}

void BufferManager::mostrarPageTAble()
{
    cout << "--------------------Bloque mostrarPageTAble() -------------------------" << endl;
    this->pageTable.mostrarPageTableLRU();
}


void BufferManager::dejarDeUsarUnaPagina(int numPagina)
{
    this->pageTable.descontarPinCountApagina(numPagina);
}