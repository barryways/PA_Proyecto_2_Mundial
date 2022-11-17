#include "pch.h"
#include "LinkedList.h"
#include "List.h"
#include <iostream>
#include <fstream>
#include "AlbumReader.h"
using namespace System;
using namespace System::IO;

ofstream archivo;
string texto_archivo_publico ="";

void llamar_csv() {
    
}

static Sticker* search(List<Sticker>* stickers, string code) {
    int c = 0;
    Sticker* temp;
    while (c < stickers->get_size())
    {
        temp = stickers->get(c);
        if (temp->get_code() == code)
        {
            return temp;
        }
    }
    if (c == stickers->get_size())
    {
        return nullptr;
    }
}


void print_stickers(Sticker* sticker) {
    string repeated = sticker->is_repeated() ? "true" : "false";
    string linea= sticker->get_category()->get_name() + "," + sticker->get_code() + "," + sticker->get_name() + "," + repeated + "," + to_string(sticker->get_appeareances()) + "\r\n";
    cout << linea;
}
void prueba_returneo(Sticker* sticker) {
    string repeated = sticker->is_repeated() ? "true" : "false";
    texto_archivo_publico += sticker->get_category()->get_name() + "," + sticker->get_code() + "," + sticker->get_name() + "," + repeated + "," + to_string(sticker->get_appeareances())+"\r";
}

void marshal_string(String^ s, string& os) {
    using namespace Runtime::InteropServices;
    const char* chars =
        (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void manejo_estadisticas(List<Sticker>* stickers) {
    int opcion_manejo_estampillas = 0;
    cout << "Usted entro a: ESTADISTICAS\n\r";
    do
    {
        cout << "Que desea hacer ? \r\n1.Ver repetidas\r\n2.Ver faltantes\r\n3.Ver marcadas\r\n4.volver al menu 1\r\n";
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


void manejo_marcaciones_estampillas(List<Sticker>* stickers) {
    int opcion_manejo_estampillas = 0;
    string opcion_marcar_estampilla = "";
    string opcion_desmarcar_estampilla = "";
   // Sticker* sticker_individual= new Sticker();


    cout << "Usted entro a: MARCAR O DESMARCAR ESTAMPILLAS\n\r";
    do
    {
        cout << "Que desea hacer ? \r\n1.Marcar estampillas\r\n2.Desmarcar estampillas por CSV\r\n3.Ver las estampillas actuales\r\n4.Volver al Menu 1 ";
        cin >> opcion_manejo_estampillas;
        switch (opcion_manejo_estampillas)
        {
        case 1:
            
            cout << "Que estampilla desea marcar? (ponga el codigo unico de estampa)\r";
            
            //Sticker* sticker1;
            //sticker1->mark();
            if (search(stickers, "FWC2") == nullptr)
            {
                cout << "Este no es el dato buscado\r";
            }
            else {
                cout << "Este es el dato buscado";
                cout<< search(stickers, "FWC2");
            }
            

            stickers->for_each(print_stickers);

            break;
        case 2:
            cout << "Que estampilla desea desmarcar? (ponga el codigo unico de estampa)";
            cin >> opcion_desmarcar_estampilla;
            
            break;
        case 3:
            //stickers->for_each(print_stickers);
            break;
        case 4:
                break;
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            break;
        }
    } while (opcion_manejo_estampillas == 0);
}



void escribir_archivo(string texto_csv) {

    ofstream archivo;
    archivo.open("albumCreado.csv", ios::out);
    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    archivo << texto_csv;
    archivo.close();
}


void manejo_CSV(List<Sticker>*stickers) {
    int opcion_manejo_csv = 0;
    Sticker* stickerIndividual;
    string texto__total_csv = "";
    cout << "Usted entro a: IMPORTAR O EXPORTAR ESTAMPILLAS\n\r";
    do
    {
        cout << "Que desea hacer ? \r\n1.Importar estampillas con CSV\r\n2.Exportar(filtrar) estampillas por CSV\r\n3.Volver al Menu 1\r\n";
        cin >> opcion_manejo_csv;
        switch (opcion_manejo_csv)
        {
        case 1:
            void llamar_csv();
            cout << "Las estampillas fueron importadas correctamente" << endl;
            return;
        case 2:
            
            stickers->for_each(prueba_returneo);
            texto__total_csv += texto_archivo_publico;
           
            escribir_archivo(texto__total_csv);
            cout << "Volviendo al menu 1\r\n";
            break;
        case 3:

            cout << "Volviendo al menu 1\r\n";
            break;
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            break;
        }
    } while (opcion_manejo_csv == 0);
}



int main()
{
    List<Sticker>* stickers = AlbumReader::read_album("album.csv");
    int opcion_menu_principal = 0;

    cout << "Bienvenido al manejador del album panini 2022\n\r";
    do
    {
        cout << "�Que desea hacer ? \r\n1.Importar o exportar estampillas con CSV\r\n2.Marcar/desmarcar/buscar estampillas\r\n3.Ver estadisticas de estampillas\r\n4.Salir\r\n";
        cin >> opcion_menu_principal;
        switch (opcion_menu_principal)
        {
        case 1:
            manejo_CSV(stickers);
            break ;
        case 2:
            manejo_marcaciones_estampillas(stickers);
            break;
        case 3:
            manejo_estadisticas(stickers);
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
