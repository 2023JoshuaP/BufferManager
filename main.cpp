#include <iostream>
#include "./BufferManager.cpp"

using namespace std;

void menuBufferManager(BufferManager &bufferManagerPrincipal)
{
    cout << "Bienvenido a implementación de BUFFER" << endl;
    int pesoBytesBLoque;
    cout << "Ingrese el peso de su bloque de Disco: " << endl;
    cin >> pesoBytesBLoque;
    int numFrames;
    cout << "Ingrese la cantidad de Frames a tener en el Buffer Pool: " << endl;
    cin >> numFrames;

    /*Creación de buffer pool*/
    bufferManagerPrincipal.crearBufferPoolSegunNumFrames(numFrames);
    bufferManagerPrincipal.establecerLimiteDeFrames(pesoBytesBLoque);
    cout << "----------- Creación de estructura Básica de BufferManager implementado" << endl;

}

void menu()
{      
    BufferManager bufferManagerPrincipal;
    int opcion = 0;
    int numPagina;
    //solicitar 1 página
    while (opcion!=4)
    {
        cout << "Menú Principal Programa Buffer MAnager:" << endl;
        cout << "1. Crear Buffer Pool" << endl;
        cout << "2. Obtener Una Página" << endl;
        cout << "3. Mostrar Page Table" << endl;
        cout << "4. SALIR del programa principal" << endl;
        cout << ">>>Ingrese el numero de opcion" << endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuBufferManager(bufferManagerPrincipal);
            break;
        case 2:       
            cout << "Ingrese el numero de pagina que desea OBTENER (Modo Prueba 1 - 6): "<< endl;
            cin >> numPagina;        
            bufferManagerPrincipal.obtenerUnaPagina(numPagina);
            break;

        case 3:
            bufferManagerPrincipal.mostrarPageTAble();
            break;

        default:
            break;
        }
        
    }
    
}

int main()
{
    menu();
    return 0;
}