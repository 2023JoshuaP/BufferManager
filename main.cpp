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
    while (opcion!=6)
    {
        cout << "Menú Principal Programa Buffer MAnager:" << endl;
        cout << "1. Crear Buffer Pool" << endl;
        cout << "2. Obtener Una Página" << endl;
        //RELACIONADO CON OPCION 4
        /*Falta leer correctamente o dirgir correctamente al numero de FrameId en el que se insertara)*/
        /*convertir registros en txt a Registros Fijos (primero) - Variable
        describir función y autor (comentarios)*/
        /*(dentro de obtener página Se preguntará al usuario
        si leerá(L) o escribirá(W). y a la vez este aumentará pin count de dicha página
        describir función y autor (comentarios)*/
        cout << "3. Mostrar Page Table" << endl;
        cout << "4. Mostrar Una Página" << endl;
        /*Falta leer correctamente o dirigir correctamente al numero de FrameId en el que se insertara)*/
        cout<<"5. Liberar uso de Página"<<endl;
        //Se deberá tener una opción para liberar uso de página, para descontar Pin Counts.- describir función y autor (comentarios)
        cout << "6. SALIR del programa principal" << endl;
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
            case 4:
                cout << "Ingrese el numero de la pagina a mostrale"<<endl;
                cin >> numPagina;
                char accionEnPagina;
                cout << "Leer (L/l) o Escribir (W/w) en pagina?: ";
                cin >> accionEnPagina;
                if (accionEnPagina == 'L' || accionEnPagina == 'l') {
                    bufferManagerPrincipal.bufferPool.mostrarFramePagina(numPagina);//leer
                    //accionValida = true;
                    break;
                }
                else if (accionEnPagina == 'W' || accionEnPagina == 'w') {
                    bufferManagerPrincipal.bufferPool.lecturaOescrituraPagina(numPagina); //escribir
                    //accionValida = true;
                    break;
                }
                //else {
                    //cout << "Opcion invalida." << endl;
                //}
                
                //bufferManagerPrincipal.bufferPool.mostrarFramePagina(numPagina);//leer

                //bufferManagerPrincipal.bufferPool.lecturaOescrituraPagina(numPagina); //escribir
                break;
                
            case 5:
                cout<<"Ingrese el numero de la pagina a liberar"<<endl;
                cin>>numPagina;
                //funcion
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