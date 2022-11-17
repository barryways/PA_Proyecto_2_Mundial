#include "pch.h"
#include "LinkedList.h"
#include "List.h"
#include <iostream>
#include "AlbumReader.h"

using namespace System;


void marshal_string(String^ s, string& os) {
    using namespace Runtime::InteropServices;
    const char* chars =
        (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void manejo_estadisticas() {
    int opcion_manejo_estampillas = 0;
    cout << "Usted entro a: ESTADISTICAS\n\r";
    do
    {
        cout << "¿Que desea hacer ? \r\n1.Ver repetidas\r\n2.Ver faltantes\r\n3.Ver marcadas\r\n4.volver al menu 1\r\n";
        cin >> opcion_manejo_estampillas;
        switch (opcion_manejo_estampillas)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            break;
        }
    } while (opcion_manejo_estampillas == 0);
}


void manejo_marcaciones_estampillas() {
    int opcion_manejo_estampillas = 0;
    cout << "Usted entro a: MARCAR O DESMARCAR ESTAMPILLAS\n\r";
    do
    {
        cout << "¿Que desea hacer ? \r\n1.marcar estampillas\r\n2.Desmarcar estampillas por CSV\r\n3.Volver al Menu 1\r\n";
        cin >> opcion_manejo_estampillas;
        switch (opcion_manejo_estampillas)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            break;
        }
    } while (opcion_manejo_estampillas == 0);
}

void print_stickers(Sticker* sticker) {
    string repeated = sticker->is_repeated() ? "true" : "false";
    cout << sticker->get_category()->get_name() << "," << sticker->get_code() << "," << sticker->get_name() << "," << repeated << "," << sticker->get_appeareances()<<"\r\n";
}
void print_stickers(Sticker* sticker) {
    string repeated = sticker->is_repeated() ? "true" : "false";
    cout << sticker->get_category()->get_name() << "," << sticker->get_code() << "," << sticker->get_name() << "," << repeated << "," << sticker->get_appeareances() << "\r\n";
}

void escribir_archivo(Sticker* sticker) {

    ofstream archivo;
    string nombre_archivo="";
    archivo.open("albumCreado.csv", ios::out);
    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    string repeated = sticker->is_repeated() ? "true" : "false";
    archivo<<sticker->get_category()->get_name() + "," + sticker->get_code() + "," + sticker->get_name() + "," + repeated + "," + to_string(sticker->get_appeareances()) + "\r\n";
   
    archivo.close();
}


void manejo_CSV(List<Sticker>* stickers) {
    int opcion_manejo_csv = 0;
    cout << "Usted entro a: IMPORTAR O EXPORTAR ESTAMPILLAS\n\r";
    do
    {
        cout << "¿Que desea hacer ? \r\n1.Importar estampillas con CSV\r\n2.Exportar(filtrar) estampillas por CSV\r\n3.Volver al Menu 1\r\n";
        cin >> opcion_manejo_csv;
        switch (opcion_manejo_csv)
        {
        case 1:
            string contenido_csv = stickers->for_each_funcion(print_stickers());
            //escribir_archivo();
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            break;
        }
    } while (opcion_manejo_csv == 0);
}


int main()
{
    //llamada de la lista
    List<Sticker>* stickers = AlbumReader::read_album("album.csv");
    //incializacion de variables
    int opcion_menu_principal = 0;

    cout << "Bienvenido al manejador del album panini 2022\n\r";
    do
    {
        cout << "¿Que desea hacer ? \r\n1.Importar o exportar estampillas con CSV\r\n2.Marcar o desmarcar estampillas\r\n3.Ver estadisticas de estampillas\r\n4.Salir\r\n";
        cin >> opcion_menu_principal;
        switch (opcion_menu_principal)
        {
        case 1:
            manejo_CSV(stickers);
            break;
        case 2:
            manejo_marcaciones_estampillas();
            break;
        case 3:
            manejo_estadisticas();
            break;
        case 4:
            exit(0);
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            break;
        }
    } while (opcion_menu_principal==0);

    return 0;
}
