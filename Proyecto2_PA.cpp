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

static Sticker* search(List<Sticker>* stickers, string code) {
    int c = 0;
    Sticker* temp;
    while (c != stickers->get_size())
    {
        if (c == stickers->get_size())
        {
            return nullptr;
        }
        temp = stickers->get(c);
        if (temp->get_code() == code)
        {
            return temp;
        }
        c++;
    }

}

static Sticker* search_by_name(List<Sticker>* stickers, string name) {
    int c = 0;
    Sticker* temp;
    while (c != stickers->get_size())
    {
        if (c == stickers->get_size())
        {
            return nullptr;
        }
        temp = stickers->get(c);
        if (temp->get_code() == name)
        {
            return temp;
        }
        c++;
    }

}


static int repeated_watcher(List<Sticker>* stickers, Sticker* temp) {
    int contador = 0;
    int repetidas = 0;
    while (contador != stickers->get_size())
    {
        if (contador == stickers->get_size())
        {
            return repetidas;
        }
        temp = stickers->get(contador);
        if (temp->is_repeated())
        {
            repetidas ++;
        }
        contador++;
    }
    return repetidas;
}

static int unmarked_watcher(List<Sticker>* stickers, Sticker* temp) {
    int contador = 0;
    int marcadas = 0;
    while (contador != stickers->get_size())
    {
        if (contador == stickers->get_size())
        {
            break;
        }
        temp = stickers->get(contador);
        if (!temp->is_marked())
        {
            marcadas++; 
        }
        contador++;
    }

    return (stickers->get_size()-(marcadas));
}

static int marked_watcher(List<Sticker>* stickers, Sticker* temp) {
    int contador = 0;
    int marcadas = 0;
    while (contador != stickers->get_size())
    {
        if (contador == stickers->get_size())
        {
            break;
        }
        temp = stickers->get(contador);
        if (temp->is_marked())
        {
            marcadas++;
        }
        contador++;
    }

    return (stickers->get_size() - (marcadas));
}

static string code_search(List<Sticker>* stickers, Sticker* temp, string code) {
    try
    {
        if (search(stickers, code))
        {
            int contador = 0;
            while (contador != stickers->get_size())
            {
                temp = stickers->get(contador);
                if (temp->get_code() == code)
                {
                    string repeated = temp->is_repeated() ? "true" : "false";
                    string contenido = temp->get_category()->get_name() + "\t" + temp->get_code() + "\t" + temp->get_name() + "\t" + repeated + "\t" + to_string(temp->get_appeareances()) + "\r\n";
                    return contenido;
                }
                contador++;
            }
        }
        else {
            cout << "No se pudo marcar la estampilla porque no se encontro dentro de la lista" << endl;
        }
    }
    catch (const std::exception&)
    {
        cout << "No se pudo completar la operacion solicitada" << endl;
    }
}

static string name_search(List<Sticker>* stickers, Sticker* temp, string name) {
    try
    {
        if (search(stickers, name))
        {
            int contador = 0;
            while (contador != stickers->get_size())
            {
                temp = stickers->get(contador);
                if (temp->get_name() == name)
                {
                    string repeated = temp->is_repeated() ? "true" : "false";
                    string contenido = temp->get_category()->get_name() + "\t" + temp->get_code() + "\t" + temp->get_name() + "\t" + repeated + "\t" + to_string(temp->get_appeareances()) + "\r\n";
                    return contenido;
                }
                contador++;
            }
        }
        else {
            cout << "No se pudo marcar la estampilla porque no se encontro dentro de la lista" << endl;
        }
    }
    catch (const std::exception&)
    {
        cout << "No se pudo completar la operacion solicitada" << endl;
    }
}

void print_stickers(Sticker * sticker) {

    string repeated = sticker->is_repeated() ? "true" : "false";
    string linea= sticker->get_category()->get_name() + "\t" + sticker->get_code() + "\t" + sticker->get_name() + "\t" + repeated + "\t" + to_string(sticker->get_appeareances()) + "\r\n";
    cout << linea;
}

void write_in_file(Sticker* sticker) {
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


void manejo_estadisticas(List<Sticker>* stickers, Sticker* nodo_actual) {
    int opcion_manejo_estampillas = 0;
    cout << "Usted entro a: ESTADISTICAS\n\r";
    do
    {
        cout << "Que desea hacer ? \r\n1.Ver repetidas\r\n2.Ver faltantes\r\n3.Ver marcadas\r\n4.volver al menu 1\r\n";
        cin >> opcion_manejo_estampillas;
        switch (opcion_manejo_estampillas)
        {
        case 1:

            cout << "Usted tiene "<<repeated_watcher(stickers, nodo_actual)<<" estampillas repetidas\r\n";
            break;
        case 2:
            cout << "Usted necesita "<< unmarked_watcher(stickers, nodo_actual) << endl;
            break;
        case 3:
            cout << "Usted ha marcado " <<marked_watcher(stickers, nodo_actual)<< endl;
            break;
        case 4:
            break;
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            break;
        }
    } while (opcion_manejo_estampillas == 0);
}

void manejo_marcaciones_estampillas(List<Sticker>* stickers, Sticker* nodo_principal) {
    int opcion_manejo_estampillas = 0;
    int opcion_busqueda_estampilla = 0;
    string opcion_marcar_estampilla = "";
    string opcion_desmarcar_estampilla = "";
    string opcion_buscar_estampilla_nombre = "";
    string opcion_buscar_estampilla_codigo = "";

    cout << "Usted entro a: MARCAR O DESMARCAR ESTAMPILLAS\n\r";
    do
    {
        cout << "Que desea hacer ? \r\n1.Marcar estampillas\r\n2.Desmarcar estampillas por CSV\r\n3.Ver las estampillas actuales\r\n4.Buscar Estampa \r\n5.Volver al Menu 1 \r\n";
        cin >> opcion_manejo_estampillas;
        switch (opcion_manejo_estampillas)
        {
        case 1:
            try
            {
                cout << "Que estampilla desea marcar? (ponga el codigo unico de estampa)\r\n";
                cin >> opcion_marcar_estampilla;
                if (search(stickers, opcion_marcar_estampilla))
                {
                    int contador = 0;

                    while (contador != stickers->get_size())
                    {
                        nodo_principal = stickers->get(contador);
                        if (nodo_principal->get_code() == opcion_marcar_estampilla)
                        {
                            cout << "Estampilla marcada? " << nodo_principal->is_marked() << "\r\n";
                            nodo_principal->mark();
                            stickers->remove(contador);
                            stickers->insert(contador, nodo_principal);
                            cout << "Estampilla con Codigo " << nodo_principal->get_code() << ", jugador " << nodo_principal->get_name() << endl;
                            cout << "Estampilla marcada? " << nodo_principal->get_appeareances()<< "\r\n";
                            cout << "Estampilla marcada correctamente" << endl;
                            break;
                        }
                        contador++;
                    }
                }
                else {
                    cout << "No se pudo marcar la estampilla porque no se encontro dentro de la lista" << endl;
                }
            }
            catch (const std::exception&)
            {
                cout << "No se pudo completar la operacion solicitada" << endl;
            }

            break;
        case 2:
            try
            {
                cout << "Que estampilla desea desmarcar? (ponga el codigo unico de estampa)\r\n";

                cin >> opcion_desmarcar_estampilla;

                if (search(stickers, opcion_desmarcar_estampilla))
                {
                    int contador = 0;

                    while (contador != stickers->get_size())
                    {
                        nodo_principal = stickers->get(contador);
                        if (nodo_principal->get_code() == opcion_desmarcar_estampilla)
                        {
                            cout << "Estampilla marcada? " << nodo_principal->is_marked() << "\r\n";
                            nodo_principal->unmark();
                            stickers->remove(contador);
                            stickers->insert(contador, nodo_principal);
                            cout << "Estampilla con Codigo " << nodo_principal->get_code() << ", jugador " << nodo_principal->get_name() << endl;
                            cout << "Estampilla marcada? " << nodo_principal->is_marked() << "\r\n";
                            cout << "Estampilla marcada correctamente" << endl;
                            break;
                        }
                        contador++;
                    }
                }
                else {
                    cout << "No se pudo desmarcar la estampilla porque no se encontro dentro de la lista" << endl;
                
                }
            }
            catch (const std::exception&)
            {
                cout << "No se pudo realizar la operacion solicitada" << endl;
            }



            break;
        case 3:
            stickers->for_each(print_stickers);
            break;
        case 4:
            try
            {
                cout << "Como desea buscar la estampilla? 1. Codigo Unico 2. Nombre\r\n";
                
                cin >> opcion_busqueda_estampilla;
                do
                {
                    switch (opcion_busqueda_estampilla)
                    {
                    case 1:
                        try
                        {
                            cout << "Ingrese el codigo unico de estampa" << endl;
                            cin >> opcion_buscar_estampilla_codigo;
                            if (search(stickers, opcion_buscar_estampilla_codigo))
                            {
                                int contador = 0;
                                string contenido = "";
                                while (contador != stickers->get_size())
                                {
                                    nodo_principal = stickers->get(contador);
                                    if (nodo_principal->get_code() == opcion_buscar_estampilla_codigo)
                                    {
                                        string repeated = nodo_principal->is_repeated() ? "true" : "false";
                                        contenido = nodo_principal->get_category()->get_name() + "\t" + nodo_principal->get_code() + "\t" + nodo_principal->get_name() + "\t" + repeated + "\t" + to_string(nodo_principal->get_appeareances()) + "\r\n Este es el codigo de messi \"" + nodo_principal->get_name() + "\"";
                                        break;
                                    }
                                    contador++;
                                }
                                cout << contenido << endl;
                            }
                            else {
                                cout << "No se pudo marcar la estampilla porque no se encontro dentro de la lista" << endl;
                                break;
                            }
                        }
                        catch (const std::exception&)
                        {
                            cout << "No se pudo completar la operacion solicitada" << endl;
                        }
                        break;
                    case 2:
                       /* cout << "Ingrese el nombre del jugador de estampa" << endl;
                        cin >> opcion_buscar_estampilla_nombre;
                        try
                        {
                            if (search_by_name(stickers, opcion_buscar_estampilla_nombre))
                            {
                                int contador2 = 0;
                                string contenido = "";
                                while (contador2 != stickers->get_size())
                                {
                                    nodo_principal = stickers->get(contador2);
                                    if (nodo_principal->get_name() == opcion_buscar_estampilla_nombre)
                                    {
                                        string repeated = nodo_principal->is_repeated() ? "true" : "false";
                                        contenido = nodo_principal->get_category()->get_name() + "\t" + nodo_principal->get_code() + "\t" + nodo_principal->get_name() + "\t" + repeated + "\t" + to_string(nodo_principal->get_appeareances()) + "\r\n Este es el codigo de messi \"" + nodo_principal->get_name() + "\"";
                                        break;
                                    }
                                    contador2++;
                                }
                                cout << contenido << endl;
                                break;
                            }
                            else {
                                cout << "No se pudo marcar la estampilla porque no se encontro dentro de la lista" << endl;
                                break;
                            }
                        }
                        catch (const std::exception&)
                        {
                            cout << "No se pudo completar la operacion solicitada" << endl;
                        }
                        break;*/
                    default:
                        cout << "Esta opcion no la maneja el progrma" << endl;
                        break;
                    }
                } while (opcion_busqueda_estampilla==0);
            }
            catch (const std::exception&)
            {
                cout << "No se pudo realzar la operacion esperada, contactese con un administrador\r\n";
            }
                break;
        case 5:
                break;
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            break;
        }
    } while (opcion_manejo_estampillas == 0);
}



void manejo_CSV(List<Sticker>*stickers) {
    int opcion_manejo_csv = 0;
    string texto__total_csv = "";
    cout << "Usted entro a: IMPORTAR O EXPORTAR ESTAMPILLAS\n\r";
    do
    {
        cout << "Que desea hacer ? \r\n1.Importar estampillas con CSV\r\n2.Exportar(filtrar) estampillas por CSV\r\n3.Volver al Menu 1\r\n";
        cin >> opcion_manejo_csv;
        switch (opcion_manejo_csv)
        {
        case 1:
            cout << "Las estampillas fueron importadas correctamente" << endl;
            return;
        case 2:
            stickers->for_each(write_in_file);
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
    Sticker* nodo_principal= stickers->get(0);
    int opcion_menu_principal = 0;

    cout << "Bienvenido al manejador del album panini 2022\n\r";
    do
    {
        cout << "Que desea hacer ? \r\n1.Importar o exportar estampillas con CSV\r\n2.Marcar/desmarcar/buscar estampillas\r\n3.Ver estadisticas de estampillas\r\n4.Salir\r\n";
        cin >> opcion_menu_principal;
        switch (opcion_menu_principal)
        {
        case 1:
            manejo_CSV(stickers);
            main();
            break ;
        case 2:
            manejo_marcaciones_estampillas(stickers, nodo_principal);
            main();
            break;
        case 3:
            manejo_estadisticas(stickers, nodo_principal);
            main();
            break;
        case 4:
            exit(1);
        default:
            cout << "El programa no maneja esa opcion, pongase en contacto con un administrador\r\n";
            main();
        }
    } while (opcion_menu_principal==0);

    return 0;
}
