#include <iostream>
#include <locale.h> // bibloteca que proporciona funciones para manejar informacion relacionada con la configuracion regional de un programa (representacion de datos) 
#include <string> // bibloteca para trabajar con cadenas de caracteres
#include <cstdlib> // bibloteca que proporciona funciones para la gestion de memoria dinamica, generacion de numeros aleatorios, etc. Incluye system()
#include <vector> 
#include <fstream> 
#include <sstream> 
using namespace std;

void menuPrincipal();
void menuContinentes();
void menuPaises();

void registroContinentes();
void modificarContinentes();
void eliminarContinente();
void visualizarContinente();

void registroPaises();
void modificarPaises();
void eliminarPais();
void visualizarPais(); 

//Funciones para leer csv y almacenar los datos dentro de los vectores
void llenarVectorContinentes(); 
void llenarVectorPaises();

//Funciones para verificar existencia
void verificarExistenciaBaseDatos(); //Verfiicar la existencia de las bases de datos y crea los ficheros en caso de que no existan
void existenciaContinente(string nomContinente);  //Verifica si existe el continente
void existenciaPais(string nomDelPais); // Verifica si existe el pais

//Funciones para actualizar y registrar en los ficheros
void actualizarBaseDatosTodosDatosContinente();  //Funcion para actualizar los datos de un continente una vez se registra un pais dentro de dicho continente

void actualizarBaseDatosUnDatoPais(int columna, string datoPais); // Funcion para actualizar un solo dato del pais, recibe un parametro correspondiente a la columna y otro al dato que se quiere eliminar
void actualizarBaseDatosNombreContinente(); // Actualiza el fichero de paises y continentes, ya que cambia el nombre del Continente
void actualizarBaseDatosTodosDatosPais(); //Funcion cuando el usuario desee cambiar todos los datos de un pais
void actualizarBaseDatosNombrePaisEnContinentes(string datoOriginal, string datoNuevo); //Funcion para actualizar el continente cuando se modifica el nombre o idioma de un pais

//Funciones para actualizar la poblacion,superficie,Densidad
void poblacionesTotales(); //Funcion para actualizar las poblaciones,superficies y densidades totales cuando se elimina un pais
void actualizarBaseDatosPoblacionesTotales(); //Funcion para actualizar las poblaciones,superficies y densidades cuando se elimina un pais o se actualizan todos los dato

bool existeContinente, existePais; //Variables booleanas para comprobar existencia del continente

void topCincoPaises(); // Funcion del top 5 Paises
int mayor,aux;
string aux2;

// Nuevas variables
int numColumnaPais, numColumnaContinente, posPalabra, posIdiom;
string auxiliarPais, auxiliarContinente, idiomPais, idiomAntiguo;
string stringPob,stringSup,stringDens, stringPobTotal,stringSupTotal, stringDensTotal;

int opcion1,opcion2,opcion3,opcion4,opcion5,opcion6,opcion7, indexPais = 0,indexConti = 0;
string nomConti, idiomsConti;
string contiPais,nomPais,cap,pres,idiom;
long int pob, sup, pobTotal, supTotal;
float dens,densTotal;

//Vectores para top 5:
vector<long int>poblacionesMayores;
vector<string>paisesMayores;

// vectores para control de ficheros
vector<vector<string>>datosContinentes;
vector<vector<string>>datosPaises;

vector<string>fila;
string linea, palabra;  // La variable linea va ir leyendo cada fila, la variable palabra va almacenar cada string separado por coma

fstream BaseDatosContinentes;
fstream BaseDatosPaises;
fstream auxiliarBaseDatos; //Base de datos Auxiliar para la eliminacion de datos

int main()
{
    verificarExistenciaBaseDatos();
    
    setlocale(LC_CTYPE, "Spanish");
    cout << "EXPLORADOR DE CONTINENTES.\nEn este programa tendra la opcion de registrar y modificar informacion sobre continentes y paises.\nPara elegir una opcion digite el numero correspondiente.\n1) Ingresar al programa (oprima 1)\n2) Salir del programa (oprima 2)\nRespuesta: ";
    cin >> opcion1;
    while((opcion1 != 1) && (opcion1 != 2)){
        system("clear");
        cout << "Ingrese una opcion valida.\n1) Ingresar al programa (oprima 1)\n2) Salir del programa (oprima 2)\nRespuesta: ";
        cin >> opcion1;
    }
    system("clear");
    
    while(opcion1 == 1){ // ciclo que permite ingresar y volver al menu principal si el usuario asi lo elige 
        menuPrincipal();
        cout << "¿Desea volver al menu principal?\n1) Si\n2) No\nRespuesta: ";
        cin >> opcion1;
        while((opcion1 != 1) && (opcion1 != 2)){
            system("clear");
            cout << "Ingrese una opcion valida.\n1) Regresar el menu principal (oprima 1)\n2) Salir del programa (oprima 2)\nRespuesta: ";
            cin >> opcion1;
        }
        system("clear");
    }

    if(opcion1 == 2){ //Mensajes en caso de que el usuario quiera salir del programa o no eliga una opcion adecuada
        cout << "Saliendo del Explorador de Continentes..." << endl;
    }  
    return 0;
}

//   Menu principal
void menuPrincipal(){ 
    
    cout << "¿A que seccion desea ingresar?\n1) Seccion Continentes\n2) Seccion Paises\nRespuesta: ";
    cin >> opcion2;
    system("clear");
    
    if(opcion2 == 1){ // Seccion Continentes
        menuContinentes();
    }
    else if(opcion2 == 2){ // Seccion Paises
        menuPaises();
    } 
}

// Submenus principales
void menuContinentes(){ // Menu Continentes
    do{
        cout << "Bienvenido a la Seccion de Continentes. Seleccione una de las siguientes opciones:\n1) Registro de nuevos continentes\n2) Modificar informacion de un continente\n3) Eliminar un continente\n4) Visualizar informacion de un continente\n5) Salir de la seccion continentes\nRespuesta: ";
        cin >> opcion3;
        cin.ignore(); // Ignorar el caracter de nueva linea que queda en el buffer de entrada
        system("clear");
                
        switch(opcion3){
            case 1:
                registroContinentes();
                break;
                
            case 2:
                modificarContinentes();
                break;
                
            case 3:
                eliminarContinente();
                break;
                
            case 4:
                visualizarContinente();
                break;
                
            case 5:
                cout << "Saliendo de la seccion Continentes.." << endl;
                opcion6 = 2;
                break;
                
            default:
                cout << "Ninguna opcion Seleccionada, saliendo de la Seccion Continentes" << endl;
                break;
        }
        
        if(opcion3 != 5){ // en caso de que ya haya decidido salir de la Seccion Continentes esto no se mostrara
            cout << "Desea volver al menu principal de Continentes:\n1) Si\n2) No\nRespuesta: ";
            cin >> opcion6;
        }
        system("clear");
    }while(opcion6 == 1);
}

void menuPaises(){ // Menu Paises
    do{ // do para ejecutarlo una vez
        cout << "Bienvenido a la Seccion de Paises. Seleccione una de las siguientes opciones:\n1) Registro de nuevos paises\n2) Modificar informacion de un pais\n3) Eliminar un pais\n4) Visualizar informacion de un pais\n5) Top 5 paises mas poblados\n6) Salir de la seccion paises\nRespuesta: ";
        cin >> opcion4;
        cin.ignore();
        system("clear");
        
        switch(opcion4){
            case 1:
                registroPaises();
                break; 
                
            case 2:
                modificarPaises();
                break; 
            
            case 3:
                eliminarPais();
                break; 
                
            case 4:
                visualizarPais();
                break;
                
            case 5:
                topCincoPaises();
                break;
                
            case 6:
                cout << "Saliendo de la seccion paises..." << endl;
                opcion7 = 2;
                break;
                
            default: 
                cout << "Ninguna opcion seleccionada, saliendo de la seccion paises..." << endl;
                break;
        } // Fin del switch opcion4
        
        if(opcion4 != 6){
            cout << "Desea volver al menu principal de paises:\n1) Si\n2) No\nRespuesta: ";
            cin >> opcion7;
        }
    system("clear");   
    }while(opcion7 == 1);
}

// Funciones relativas a Continentes
void registroContinentes() {
    cout << "Nombre del continente: ";
    getline(cin, nomConti);
    BaseDatosContinentes.open("BaseDatosContinentes", ios::app); //El archivo se apre en el modo de apertura app para agregar todo al final del archivo
    BaseDatosContinentes << nomConti + "," + "n" + "," + "n" + "," + "n" + "," + "n" + "," + "n" << endl; // Las n son necesarias para llenar el vector en un futuro, evitando problemas con las dimensiones del mismo
    BaseDatosContinentes.close();    
    
    cout <<"El continente ha sido registrado exitosamente.";
}

void modificarContinentes(){
    cout << "Digite el nombre del continente para modificar su informacion: ";
    getline(cin, nomConti);
    contiPais = nomConti;
    existenciaContinente(nomConti); // Verifica la existencia del continente, cambia el valor de existeContinente en caso de encontrar el nombre ingresado
    
    if(existeContinente == true){ 
        cout << "Ingrese el nuevo nombre del continente: "; 
        getline(cin, nomConti);
        
        actualizarBaseDatosNombreContinente();
        cout << "Continente modificado exitosamente" << endl;
    }else{
        cout << "El continente ingresado no existe" << endl;
    }
}
                
void eliminarContinente(){
    cout << "Ingrese el nombre del continente que desea eliminar: ";
    getline(cin, nomConti);
    existenciaContinente(nomConti);
    
    // Eliminar el continente
    if(existeContinente == true){
        auxiliarBaseDatos.open("BaseDatosContinentes.tmp", ios::out); //Creamos un archivo temporal, donde vamos a guardar la informacion actualizada
    
        for (vector<string>fila : datosContinentes){ // For each -> itera por cada elemento del vector datosContinentes. for (tipo elemento : contenedor) 
            if (fila.size() > 0 && fila[0] != nomConti){ // Primero evalua si hay algun elemento, y luego verifica si el primer elemento es distinto a nomConti
                for (int i = 0; i < fila.size(); i++){ // En caso de que no contenga nomConti (el dato a eliminar), entonces llena el nuevo archivo con la informacion de esa fila
                    auxiliarBaseDatos << fila[i]; // Registra cada elemento del vector en el nuevo archivo
                    if (i < fila.size() - 1) { // Validacion para poner las comas antes de la posicion final
                        auxiliarBaseDatos << ",";
                    }
                }
                auxiliarBaseDatos << endl; // Un salto de linea al final de cada renglon del archivo
            }
        }
        auxiliarBaseDatos.close();
    
        // Eliminar el archivo original y renombrar el nuevo archivo
        if (remove("BaseDatosContinentes") != 0) { // remove es una funcion para eliminar archivo, devuelve cero (0) si la eliminacion es exitosa
            cout << "Error al eliminar el archivo original." << endl;
            return;
        }
    
        if (rename("BaseDatosContinentes.tmp", "BaseDatosContinentes") != 0) { // rename es una funcion que permite renombrar un fichero, el primer parametro es el nombre actual, y el segundo parametro es el nombre nuevo del archivo
            cout << "Error al renombrar el nuevo archivo." << endl;
            return;
        }
    
        cout << "El continente ha sido eliminado correctamente de la base de datos de continentes" << endl;

        // Eliminar los paises del continente
        llenarVectorPaises();
        auxiliarBaseDatos.open("BaseDatosPaises.tmp", ios::out); //Creamos un archivo temporal, donde vamos a guardar la informacion actualizada
        for (vector<string>fila : datosPaises){ // For each -> itera por cada elemento del vector datosContinentes -> for (tipo elemento : contenedor) 
            if (fila.size() > 0 && fila[0] != nomConti){ // Primero evalua si hay algun elemento, y luego verifica si el primer elemento es distinto a nomConti
                for (int i = 0; i < fila.size(); i++){ // En caso de que no contenga nomConti (el dato a eliminar), entonces llena el nuevo archivo con la informacion de esa fila
                    auxiliarBaseDatos << fila[i]; // Registra cada elemento del vector en el nuevo archivo
                    if (i < fila.size() - 1) { // Validacion para poner las comas antes de la posicion final
                        auxiliarBaseDatos << ",";
                    }
                }
                auxiliarBaseDatos << endl; // Un salto de linea al final de cada renglon del archivo
            }
        }
        auxiliarBaseDatos.close();
    
        // Eliminar el archivo original y renombrar el nuevo archivo
        if (remove("BaseDatosPaises") != 0) { // remove es una funcion para eliminar archivo, devuelve cero (0) si la eliminacion es exitosa
            cout << "Error al eliminar el archivo original." << endl;
            return;
        }
    
        if (rename("BaseDatosPaises.tmp", "BaseDatosPaises") != 0) { // rename es una funcion que permite renombrar un fichero, el primer parametro es el nombre actual, y el segundo parametro es el nombre nuevo del archivo
            cout << "Error al renombrar el nuevo archivo." << endl;
            return;
        }
        
        cout << "El continente ha sido eliminado correctamente de la base de datos de Paises" << endl;

    }else{
        cout << "El continente ingresado no existe" << endl;
    }
}

void visualizarContinente(){
    cout << "Digite el nombre del continente cuya informacion desea visualizar: ";
    getline(cin, nomConti);
    existenciaContinente(nomConti);
    
    if(existeContinente == true){ 
        for(int i = 0; i < datosContinentes.size(); i++){
            if(nomConti == datosContinentes[i][0]){
                cout << "Nombre del Continente: " << datosContinentes[i][0] << endl;
                cout << "Paises que componen el Continente: " << datosContinentes[i][1] << endl;
                cout << "Poblacion del Continente: " << datosContinentes[i][2] << endl;
                cout << "Superficie del Continente: " << datosContinentes[i][3] << endl;
                cout << "Densidad Poblacional del Continente: " << datosContinentes[i][4] << endl;
                cout << "Idiomas regionales: " << datosContinentes[i][5] << endl;
            }
        }
    }else{
        cout << "El continente ingresado no existe, dirigase a la seccion de registro" << endl;;
    }
}

// Funciones relativas a paises
void registroPaises(){
    cout << "Registro de Paises\nPara el registro de nuevos paises, por favor ingrese los siguientes datos:" << endl;
    cout << "Continente al que pertenece el pais: ";
    getline(cin, contiPais);
    auxiliarContinente = contiPais;
    
    existenciaContinente(contiPais);
    
    if(existeContinente == true){
        cout << "Continente encontrado, puede proceder con el registro del pais" << endl;
        cout << "Nombre del pais: ";
        getline(cin, nomPais);
        cout << "Capital del pais: ";
        getline(cin, cap);
        cout << "Presidente actual del pais: ";
        getline(cin, pres);
        cout << "Poblacion actual del pais: ";
        cin >> pob;
        cout << "Superficie del pais (km^2): ";
        cin >> sup;
        cin.ignore();
        cout << "Idioma oficial del pais: ";
        getline(cin, idiom);
        system("clear");
    
        while((pob <= 0) || (sup <= 0)){ // Ciclo while que evita que haya una poblacion, superficie y densidad menor o igual a cero
            if(pob <= 0){
                cout << "Digite una poblacion mayor a cero: ";
                cin >> pob;
                system("clear");
            }
            if(sup <= 0){
                cout << "Digite una superficie (km^2) mayor a cero: ";
                cin >> sup;
                system("clear");
            }
        }
        dens = float(pob)/sup;
        
        poblacionesTotales(); // Obtenemos los valores de poblacionesTotales
        BaseDatosPaises.open("BaseDatosPaises", ios::app);
        BaseDatosPaises << contiPais + "," + nomPais + "," + cap + "," + pres + "," + to_string(pob) + "," + to_string(sup) + "," + to_string(dens) + "," + idiom << endl;
        BaseDatosPaises.close();
        actualizarBaseDatosTodosDatosContinente();
        
        cout << "Pais registrado exitosamente" << endl;
    }else{ // Mensaje en caso de que el continente no exista aun
        cout  << "El continente ingresado no existe, dirigase a la seccion de registro" << endl;
    }
}

void modificarPaises(){ // Modificacion Paises
    cout << "Digite el nombre del pais para modificar su informacion: ";
    getline(cin, nomPais);
    system("clear");
    existenciaPais(nomPais);
    auxiliarPais = nomPais;  
    
    if(existePais == true){
        cout << "El pais ingresado existe, puede continuar" << endl;
        cout << "¿Cual de los siguientes datos desea modificar?:\n1) Nombre del pais\n2) Capital del pais\n3) Presidente actual\n4) Poblacion actual\n5) Superficie del pais\n6) Idioma oficial\n7) Todos los datos\nRespuesta: ";
        cin >> opcion5;
        cin.ignore();
        system("clear");
        
        switch(opcion5){
        case 1:
            cout << "Ingrese el nuevo nombre del pais: ";
            getline(cin, nomPais);
            numColumnaPais = 1;
            actualizarBaseDatosUnDatoPais(numColumnaPais, nomPais);
            actualizarBaseDatosNombrePaisEnContinentes(auxiliarPais, nomPais);
            break;
            
        case 2:
            cout << "Ingrese la nueva capital del pais: ";
            getline(cin, cap);
            numColumnaPais = 2;
            actualizarBaseDatosUnDatoPais(numColumnaPais, cap);
            break;
            
        case 3:
            cout << "Ingrese el nombre del presidente actual: ";
            getline(cin, pres);
            numColumnaPais = 3;
            actualizarBaseDatosUnDatoPais(numColumnaPais, pres);
            break;
            
        case 4:
            cout << "Digite la poblacion actual: ";
            cin >> pob;
            numColumnaPais = 4;
            while(pob <= 0){
                cout << "Digite una poblacion mayor a cero: ";
                cin >> pob;
                system("clear");
            }
            
            for(int i = 0; i < datosPaises.size(); i++){
                if(auxiliarPais == datosPaises[i][1]){
                    sup = stoi(datosPaises[i][5]);
                }
            }
            dens = float(pob)/sup;
            
            actualizarBaseDatosUnDatoPais(numColumnaPais, to_string(pob));
            numColumnaPais = numColumnaPais + 2;
            actualizarBaseDatosUnDatoPais(numColumnaPais, to_string(dens)); // AL cambiar la poblacion tambien lo hace la densidad
            
            llenarVectorPaises();
            for(int i = 0; i < datosPaises.size(); i++){
                if(auxiliarPais == datosPaises[i][1]){
                    contiPais = datosPaises[i][0];
                }
            }
            
            sup = 0; // Limpiamos la variable sup, ya que puede tener valores de anteriores interacciones influyendo en poblacionesTotales()
            poblacionesTotales();
            actualizarBaseDatosPoblacionesTotales();
            
            break;
        case 5:
            cout << "Digite la superficie(km^2) del pais: ";
            cin >> sup;
            numColumnaPais = 5;
            while(sup <= 0){
                cout << "Digite una superficie(km^2) mayor a cero: ";
                cin >> sup;
                system("clear");
            }
            
            for(int i = 0; i < datosPaises.size(); i++){
                if(auxiliarPais == datosPaises[i][1]){
                    pob = stoi(datosPaises[i][4]);
                }
            }
            dens = float(pob)/sup;
            
            llenarVectorPaises();
            for(int i = 0; i < datosPaises.size(); i++){
                if(auxiliarPais == datosPaises[i][1]){
                    contiPais = datosPaises[i][0];
                }
            }
            
            actualizarBaseDatosUnDatoPais(numColumnaPais, to_string(sup));
            numColumnaPais = numColumnaPais + 1;
            actualizarBaseDatosUnDatoPais(numColumnaPais, to_string(dens)); // AL cambiar la poblacion tambien lo hace la densidad
            
            llenarVectorPaises();
            for(int i = 0; i < datosPaises.size(); i++){
                if(auxiliarPais == datosPaises[i][1]){
                    contiPais = datosPaises[i][0];
                }
            }
            
            pob = 0;
            poblacionesTotales();
            actualizarBaseDatosPoblacionesTotales();
            break;
            
        case 6:
            for(int i = 0; i < datosPaises.size(); i++){
                if(nomPais == datosPaises[i][1]){
                    idiomAntiguo = datosPaises[i][7];
                }
            }
            cout << "Digite el nuevo idioma oficial del pais: ";
            getline(cin, idiom);
            numColumnaPais = 7;
            actualizarBaseDatosUnDatoPais(numColumnaPais,idiom);
            llenarVectorPaises();
            
            actualizarBaseDatosNombrePaisEnContinentes(idiomAntiguo, idiom);
            break;
            
        case 7:
            cout << "Nombre del pais: ";
            getline(cin, nomPais);
            cout << "Capital del pais: ";
            getline(cin, cap);
            cout << "Presidente actual del pais: ";
            getline(cin, pres);
            cout << "Poblacion actual del pais: ";
            cin >> pob;
            cout << "Superficie del pais (km^2): ";
            cin >> sup;
            cin.ignore();
            for(int i = 0; i < datosPaises.size(); i++){
                if(auxiliarPais == datosPaises[i][1]){
                    idiomAntiguo = datosPaises[i][7];
                }
            }
            cout << "Idioma oficial del pais: ";
            getline(cin, idiom);
            while((pob <= 0) || (sup <= 0)){ 
                if(pob <= 0){
                    cout << "Digite una poblacion mayor a cero: ";
                    cin >> pob;
                    system("clear");
                }
                if(sup <= 0){
                    cout << "Digite una superficie (km^2) mayor a cero: ";
                    cin >> sup;
                    system("clear");
                }
            }
            dens = float(pob)/sup;
            
            stringPob = to_string(pob);
            stringSup = to_string(sup);
            stringDens = to_string(dens);
            actualizarBaseDatosTodosDatosPais();  
            actualizarBaseDatosNombrePaisEnContinentes(auxiliarPais, nomPais); // Actualizar nombre del pais
            
            // Actualizar Poblaciones y Superficies Totales 
            llenarVectorPaises();
            for(int i = 0; i < datosPaises.size(); i++){
                if(nomPais == datosPaises[i][1]){
                    contiPais = datosPaises[i][0]; //contiPais es necesario para 
                }
            }
            poblacionesTotales(); //Obtener poblaciones  y superficies Totales
            actualizarBaseDatosPoblacionesTotales(); // Se actualizan dentro del Continente
            actualizarBaseDatosNombrePaisEnContinentes(idiomAntiguo, idiom);
            break;

        default:
            cout << "Ninguna opcion elegida, saliendo de Modificacion de paises...";
            break;
        }
        
    }else{
        cout  << "El pais ingresado no existe, dirigase a la seccion de registro" << endl;
    }  
}

void eliminarPais(){ // Eliminar Pais
    cout << "Digite el nombre del pais que desea eliminar: ";
    getline(cin, nomPais);
    system("clear");
    
    llenarVectorPaises();
     for(int i = 0; i < datosPaises.size(); i++){
        if(nomPais == datosPaises[i][1]){
            contiPais = datosPaises[i][0]; //Buscamos el continente de ese pais para saber que poblaciones tomar proximamente
        }  
    }

    existenciaPais(nomPais);
    
    // Eliminar el Pais
    if(existePais == true){
        auxiliarBaseDatos.open("BaseDatosPaises.tmp", ios::out); //Creamos un archivo temporal, donde vamos a guardar la informacion actualizada
        for (vector<string>fila : datosPaises){ // For each -> itera por cada elemento del vector datosContinentes. for (tipo elemento : contenedor) 
            if (fila.size() > 0 && fila[1] != nomPais){ // Primero evalua si hay algun elemento, y luego verifica si el primer elemento es distinto a nomConti
                for (int i = 0; i < fila.size(); i++){ // En caso de que no contenga nomConti (el dato a eliminar), entonces llena el nuevo archivo con la informacion de esa fila
                    auxiliarBaseDatos << fila[i]; // Registra cada elemento del vector en el nuevo archivo
                    if (i < fila.size() - 1) { // Validacion para poner las comas antes de la posicion final
                        auxiliarBaseDatos << ",";
                    }
                }
                auxiliarBaseDatos << endl; // Un salto de linea al final de cada renglon del archivo
            }
        }
        auxiliarBaseDatos.close();
    
        // Eliminar el archivo original y renombrar el nuevo archivo
        if (remove("BaseDatosPaises") != 0) { // remove es una funcion para eliminar archivo, devuelve cero (0) si la eliminacion es exitosa
            cout << "Error al eliminar el archivo original." << endl;
            return;
        }
    
        if (rename("BaseDatosPaises.tmp", "BaseDatosPaises") != 0) { // rename es una funcion que permite renombrar un fichero, el primer parametro es el nombre actual, y el segundo parametro es el nombre nuevo del archivo
            cout << "Error al renombrar el nuevo archivo." << endl;
            return;
        }
    
        cout << "El Pais ha sido eliminado correctamente de la base de datos de paises." << endl;
        
        // Eliminar del continente  
        auxiliarBaseDatos.open("BaseDatosContinentes.tmp", ios::out);
        BaseDatosContinentes.open("BaseDatosContinentes", ios::in);
        
        for(int i = 0; i < datosPaises.size(); i++){
            if(nomPais == datosPaises[i][1]){
                idiomPais = datosPaises[i][7]; //Buscamos el idioma de ese pais para eliminarlo tambien
            }  
        }

        while (getline(BaseDatosContinentes,palabra)){
            posPalabra = palabra.find(nomPais);  // Busca la posicion de la palabra a eliminar en linea
            
            if (posPalabra != string::npos) { // Si se encuentra la palabra, si la funcion find devuelve string::npos significa que la cadena no se encontra
                // Elimina la palabra de la linea
                if(palabra[posPalabra + nomPais.length()] == ','){ //Verifica si el caracter siguiente a la palabra es igual a una coma
                    if(palabra[posPalabra - 1] != ','){ // Verifica si el caracter antes de la posicion de la palabra a eliminar 
                        palabra.erase(posPalabra - 1, nomPais.length() + 1);
                    }else{
                        palabra.erase(posPalabra, nomPais.length());
                    } 
                }else{
                    palabra.erase(posPalabra, nomPais.length() + 1);  // la funcion erase() elimina caracteres de un string por medio de dos parametros, la posicion inicial y el numero de caracteres a eliminar  
                }
                
                posIdiom = palabra.find(idiomPais); // buscamos el idioma
                if(posIdiom != string::npos){
                    if(palabra[posIdiom - 1] == ','){ //En caso de que haya una coma antes borramos el pais y el espacio que siguiente
                        palabra.erase(posIdiom,idiomPais.length() + 1);
                    }else{
                        palabra.erase(posIdiom - 1,idiomPais.length() + 1);
                    }
                }
            }
            auxiliarBaseDatos << palabra << endl; // Escribir la linea modificada en el archivo temporal
        }
        
        auxiliarBaseDatos.close();
        BaseDatosContinentes.close();
        
        if (remove("BaseDatosContinentes") != 0) { // remove es una funcion para eliminar archivo, devuelve cero (0) si la eliminacion es exitosa
            cout << "Error al eliminar el archivo original." << endl;
            return;
        }
    
        if (rename("BaseDatosContinentes.tmp", "BaseDatosContinentes") != 0) { // rename es una funcion que permite renombrar un fichero, el primer parametro es el nombre actual, y el segundo parametro es el nombre nuevo del archivo
            cout << "Error al renombrar el nuevo archivo." << endl;
            return;
        }
        
        actualizarBaseDatosPoblacionesTotales();
        cout << "El Pais ha sido eliminado correctamente de la base de datos de continentes." << endl;
    }else{
        cout << "El pais ingresado no existe" << endl;
    }
}

void visualizarPais(){
    cout << "Digite el nombre del pais cuya informacion desea visualizar: ";
    getline(cin, nomPais);
    existenciaPais(nomPais);
    
    if(existePais == true){
        for(int i = 0; i < datosPaises.size(); i++){
            if(nomPais == datosPaises[i][1]){
                cout << "Continente del Pais: " << datosPaises[i][0] << endl;
                cout << "Nombre del Pais: " << datosPaises[i][1] << endl;
                cout << "Capital: " << datosPaises[i][2] << endl;
                cout << "Presidente: " << datosPaises[i][3] << endl;
                cout << "Poblacion: " << datosPaises[i][4] << endl;
                cout << "Superficie: " << datosPaises[i][5] << endl;
                cout << "Densidad: " << datosPaises[i][6] << endl;
                cout << "Idioma: " << datosPaises[i][7] << endl;
            }
        }
    }else{
        cout << "El pais ingresado no existe, dirigase a la seccion de registro" << endl;;
    }
}


void topCincoPaises(){
    cout << "Top 5 paises mas poblados: " << endl;
    llenarVectorPaises();
    
    // Llenamos el vector de poblaciones mayores con todos las poblaciones del fichero
    for (int i = 1; i < datosPaises.size(); i++){ //Debemos inicializarlo en 1, ya que la fila 0 corresponde al nombre de las columnas, lo que ocasionaria problemas en la conversion 
        long int poblacionMayor = stol(datosPaises[i][4]); // Convierte la cadena de la columna de poblacion a long int, ya que el vector datosPaises es de tipo string
        poblacionesMayores.push_back(poblacionMayor);
        paisesMayores.push_back(datosPaises[i][1]);
    }   
    
    // Ordenamos el vector de poblaciones mayores
    for(int i = 0; i < paisesMayores.size(); i++){
        mayor = i; // mayor es la posicion actual
        for(int j = i + 1; j < paisesMayores.size(); j++){ // Recorremos los paises desde la posicion actual + 1
            if(poblacionesMayores[j] > poblacionesMayores[mayor]){ // Si la posicion actual + 1 es mayor que la posicion actual
                mayor = j; // mayor pasa a ser la posicion actual + 1
            }
        }    
        aux = poblacionesMayores[i]; // Valor de la posicion actual
        aux2 = paisesMayores[i];
        poblacionesMayores[i] = poblacionesMayores[mayor]; // Reemplazamos la posicion actual por el mayor Valor
        paisesMayores[i] = paisesMayores[mayor]; 
        poblacionesMayores[mayor] = aux; // Reemplazamos la posicion mayor por el valor que habia en la posicion actual, es decir aux
        paisesMayores[mayor] = aux2;
    }
    
    //Imprimimos los cinco primeros elementos:
    if (paisesMayores.size() >= 5 && poblacionesMayores.size() >= 5) { //Verificamos que haya por lo menos cinco elementos en el vector, ya que asi evitamos errores
        for(int i = 0; i < 5; i++){
            cout << "Top " << i + 1 << ": " << paisesMayores[i] << " -> " << poblacionesMayores[i] << " habitantes"<<  endl;
        } 
    }else{ //En caso de que haya menos de cinco elementos se imprimen de acuerdo al tamaño del vector
        for(int i = 0; i < paisesMayores.size();i++){
            cout << "Top " << i + 1 << ": " << paisesMayores[i] << " -> " << poblacionesMayores[i] << " habitantes"<<  endl;
        }
    }
}
// Base de datos

void llenarVectorContinentes(){ // Funcion para llenar el vector de continentes con todas las filas del fichero
    datosContinentes.clear(); // Es necesario limpiar el continenido del vector, puesto que puede contener informacion vieja
    
    // Recorremos cada palabra y la guardamos en el vector datosContinentes
    BaseDatosContinentes.open("BaseDatosContinentes", ios::in);
    while(getline(BaseDatosContinentes,linea)){
        fila.clear();
        
        stringstream str(linea);
        
        while(getline(str, palabra, ',')){
            fila.push_back(palabra);
        }
        datosContinentes.push_back(fila);
    }
    BaseDatosContinentes.close();
}

void llenarVectorPaises(){ // Funcion para llenar el vector de continentes con todas las filas del fichero
    datosPaises.clear();
    BaseDatosPaises.open("BaseDatosPaises", ios::in);
    while(getline(BaseDatosPaises,linea)){
        fila.clear();
        
        stringstream str(linea);
        
        while(getline(str, palabra, ',')){
            fila.push_back(palabra);
        }
        datosPaises.push_back(fila);
    }
    BaseDatosPaises.close();
}

void verificarExistenciaBaseDatos(){ //Verfiicar la existencia de las bases de datos y crea los ficheros en caso de que no existan
    ofstream CrearBaseDatos;
    
    BaseDatosContinentes.open("BaseDatosContinentes", ios::in);
    if(!BaseDatosContinentes.is_open()){ //En caso de que no se pueda abrir, se crea el fichero con sus respectivas columnas
        CrearBaseDatos.open("BaseDatosContinentes", ios::out);
        CrearBaseDatos << "NombreContinente,Paises,PoblacionTotal,SuperficieTotal,DensidadPoblacionalTotal,IdiomasRegionales" << endl;
        CrearBaseDatos.close();
    }
    BaseDatosContinentes.close();
    
    BaseDatosPaises.open("BaseDatosPaises", ios::in);
    if(!BaseDatosPaises.is_open()){
        CrearBaseDatos.open("BaseDatosPaises", ios::out);
        CrearBaseDatos << "ContinenteDelPais,NombrePais,Capital,Presidente,Poblacion,Superficie,DensidadPoblacional,Idioma" << endl;
    }
    BaseDatosPaises.close();
}

void existenciaContinente(string nomContinente){ //Verifica si existe el continente
    llenarVectorContinentes(); 
    
    for(int i = 0; i < datosContinentes.size(); i++){ //Recorremos el vector de continentes buscando si el continente ingresado existe
        if(nomContinente == datosContinentes[i][0]){ // en este caso la columna correspondiente al indice 0 es la del nombre del continente
            existeContinente = true;
            break; //Salir del ciclo si se encuentra con el continente
        }else{
            existeContinente = false;
        }
    }
}

void existenciaPais(string nomDelPais){ //Verifica si existe el con
    llenarVectorPaises();
    
    for(int i = 0; i < datosPaises.size(); i++){  //verifica si existe el pais
        if(nomDelPais == datosPaises[i][1]){
            existePais = true;
            break; //Salir del ciclo si se encuentra con el pais
        }else{
            existePais = false;
        }
    }
}

void actualizarBaseDatosNombreContinente(){ // Actualiza el fichero de paises y continentes, ya que cambia el nombre del Continente
    llenarVectorContinentes();
    
    // Buscamos el continente que queria cambiar el usuario y lo cambiamos por el nuevo nombre
    for(int i = 0; i < datosContinentes.size(); i++){
        if(datosContinentes[i][0] == contiPais){ // Evaluamos de acuerdo a la primera columna del vector, ya que alli se ubica el nombre del continentes
            datosContinentes[i][0] = nomConti;
        }
    }
    
    // Ponemos todos los datos ya actualizados del vector dentro del fichero 
    BaseDatosContinentes.open("BaseDatosContinentes", ios::out);
    for(int i = 0; i < datosContinentes.size(); i++){
        for(int j = 0; j < datosContinentes[i].size(); j++){
            if(j < datosContinentes[i].size() - 1){ //Condicion para evitar que el ultimo elemento de la fila tenga una coma
                BaseDatosContinentes << datosContinentes[i][j] << ",";
            }else{
                BaseDatosContinentes << datosContinentes[i][j];
            }
        }
        BaseDatosContinentes << endl;
    }
    BaseDatosContinentes.close();
    
    // Cambiar los nombres del continente en la seccion de paises
    llenarVectorPaises();
    
    for(int i = 0; i < datosPaises.size(); i++){
        if(datosPaises[i][0] == contiPais){ 
            datosPaises[i][0] = nomConti;
        }
    }
    
    // Ponemos todos los datos ya actualizados del vector dentro del fichero 
    BaseDatosPaises.open("BaseDatosPaises", ios::out);
    for(int i = 0; i < datosPaises.size(); i++){
        for(int j = 0; j < datosPaises[i].size(); j++){
            if(j < datosPaises[i].size() - 1){ //Condicion para evitar que el ultimo elemento de la fila tenga una coma
                BaseDatosPaises << datosPaises[i][j] << ",";
            }
            else{
                BaseDatosPaises << datosPaises[i][j];
            }
        }
        BaseDatosPaises << endl;
    }
    BaseDatosPaises.close();
}

void actualizarBaseDatosUnDatoPais(int columna, string datoPais){ // Funcion para actualizar un solo dato del pais, recibe un parametro correspondiente a la columna y otro al dato que se quiere eliminar
    llenarVectorPaises();
    
    for(int i = 0; i < datosPaises.size(); i++){ // Se recorre el vector paises para buscar el dato a cambiar 
        for(int j = 0; j < datosPaises[i].size(); j++){
            if(auxiliarPais == datosPaises[i][j]){
                datosPaises[i][columna] = datoPais;
            }
        }
    }
    
    //Se reemplaza la informacion del fichero con los nuevos datos
    BaseDatosPaises.open("BaseDatosPaises", ios::out);
    for(int i = 0; i < datosPaises.size(); i++){
        for(int j = 0; j < datosPaises[i].size(); j++){
            if(j < datosPaises[i].size() - 1){
                BaseDatosPaises << datosPaises[i][j] << ",";
            }
            else{
                BaseDatosPaises << datosPaises[i][j];
            }
        }
        BaseDatosPaises << endl;
    }
    BaseDatosPaises.close();
}

void actualizarBaseDatosTodosDatosPais(){ //Funcion cuando el usuario desee cambiar todos los datos de un pais
    llenarVectorPaises();
    
    for(int i = 0; i < datosPaises.size(); i++){
        for(int j = 0; j < datosPaises[i].size(); j++){
            if(auxiliarPais == datosPaises[i][j]){
                datosPaises[i][1] = nomPais;
                datosPaises[i][2] = cap;
                datosPaises[i][3] = pres;
                datosPaises[i][4] = stringPob;
                datosPaises[i][5] = stringSup;
                datosPaises[i][6] = stringDens;
                datosPaises[i][7] = idiom;
            }
        }
    }
    
    BaseDatosPaises.open("BaseDatosPaises", ios::out);
    for(int i = 0; i < datosPaises.size(); i++){
        for(int j = 0; j < datosPaises[i].size(); j++){
            if(j < datosPaises[i].size() - 1){
                BaseDatosPaises << datosPaises[i][j] << ",";
            }
            else{
                BaseDatosPaises << datosPaises[i][j];
            }
        }
        BaseDatosPaises << endl;
    }
    BaseDatosPaises.close();
}

void actualizarBaseDatosTodosDatosContinente(){ //Funcion para actualizar los datos de un continente una vez se registra un pais dentro de dicho continente
    llenarVectorContinentes();
    
    for(int i = 0; i < datosContinentes.size(); i++){
        for(int j = 0; j < datosContinentes[i].size(); j++){
            if((auxiliarContinente == datosContinentes[i][j])){ //Recorremos todo el vector continentes y buscamos donde esta el continente, en dicha fila modificamos los datos correspondientes
                datosContinentes[i][2] = stringPobTotal;
                datosContinentes[i][3] = stringSupTotal;
                datosContinentes[i][4] = stringDensTotal;
                
                if((datosContinentes[i][1] == "n") || (datosContinentes[i][5] == "n")){ //En caso de que la columna de paises o idiomas tenga n(es decir no haya ningun dato aun), entonces se reemplaza la informacion
                    datosContinentes[i][1] = nomPais;
                    datosContinentes[i][5] = idiom;
                }else{
                    datosContinentes[i][1] = datosContinentes[i][1] + " " + nomPais; //En este caso, ya hay algo registrado, por lo que se agrega un espacio y el siguiente pais o idioma
                    datosContinentes[i][5] = datosContinentes[i][5] + " " + idiom;
                }
            }
        }
    }
    
    //Procedemos a sobreescribir el archivo con infromacion actualizada
    BaseDatosContinentes.open("BaseDatosContinentes", ios::out);
    for(int i = 0; i < datosContinentes.size(); i++){
        for(int j = 0; j < datosContinentes[i].size(); j++){
            if(j < datosContinentes[i].size() - 1){
                BaseDatosContinentes << datosContinentes[i][j] << ",";
            }
            else{
                BaseDatosContinentes << datosContinentes[i][j];
            }
        }
        BaseDatosContinentes << endl;
    }
    BaseDatosContinentes.close();
}

void poblacionesTotales(){ // Funcion para saber la poblacion total de un Continente 
    llenarVectorPaises();
    
    pobTotal = 0; //Las varaibles se inicializan en cero, ya que cada continente tiene una poblacion y superfie distinta
    supTotal = 0;
    int k = 0;
    
    for(int i = 1; i < datosPaises.size(); i++){ //Recorremos las filas del vector paises; se inicializa en 1 ya que 0 tomaria en cuenta la fila de los nombres de las columnas
        if(contiPais == datosPaises[i][0]){ //Verificamos donde esta el continente
            k++;
            if(k == 1){ //Si la fila donde se encuentra el continente es la primera(es decir estamos en la prime iteracion del bucle)
                pobTotal = stol(datosPaises[i][4]) + pob; //Asignamos a pobTotal la poblacion de dicha fila(pais) + la que haya ingresado el usuario 
                supTotal = stol(datosPaises[i][5]) + sup; 
            }else{
                pobTotal = pobTotal + stol(datosPaises[i][4]); // Tomamos el valor de pobTotal y solo le sumamos el valor de la poblacion de dicha fila(pais)
                supTotal = supTotal + stol(datosPaises[i][5]);
            } 
        }
    }
    
    densTotal = float(pobTotal)/supTotal; // Obtenemos el valor de la densidad
    
    //Guardamos los valores convertidos en strings
    stringPobTotal = to_string(pobTotal); 
    stringSupTotal = to_string(supTotal);
    stringDensTotal = to_string(densTotal);
}

void actualizarBaseDatosPoblacionesTotales(){ //Funcion para actualizar las poblaciones,superficies y densidades cuando se elimina un pais
    llenarVectorPaises();
    llenarVectorContinentes();
    
    pobTotal = 0; //Las varaibles se inicializan en cero, ya que cada continente tiene una poblacion y superfie distinta
    supTotal = 0;
    
    for(int i = 1; i < datosPaises.size(); i++){ //Recorremos las filas del vector paises; se inicializa en 1 ya que 0 tomaria en cuenta la fila de los nombres de las columnas
        if(contiPais == datosPaises[i][0]){ //Verificamos donde esta el continente
            pobTotal = pobTotal + stol(datosPaises[i][4]); // Tomamos el valor de pobTotal y solo le sumamos el valor de la poblacion de dicha fila(pais)
            supTotal = supTotal + stol(datosPaises[i][5]);
        } 
    }
    
    densTotal = float(pobTotal)/supTotal; // Obtenemos el valor de la densidad
  
    //Guardamos los valores convertidos en strings
    stringPobTotal = to_string(pobTotal); 
    stringSupTotal = to_string(supTotal);
    stringDensTotal = to_string(densTotal);
    
    // Ahora asignamos los datos en el vector Continentes
    for(int i = 0; i < datosContinentes.size(); i++){
        if(contiPais == datosContinentes[i][0]){
            datosContinentes[i][2] = stringPobTotal;
            datosContinentes[i][3] = stringSupTotal;
            datosContinentes[i][4] = stringDensTotal;
        }
    }
    
    BaseDatosContinentes.open("BaseDatosContinentes", ios::out);
    for(int i = 0; i < datosContinentes.size(); i++){
        for(int j = 0; j < datosContinentes[i].size(); j++){
            if(j < datosContinentes[i].size() - 1){
                BaseDatosContinentes << datosContinentes[i][j] << ",";
            }
            else{
                BaseDatosContinentes << datosContinentes[i][j];
            }
        }
        BaseDatosContinentes << endl;
    }
    BaseDatosContinentes.close();
}

void actualizarBaseDatosNombrePaisEnContinentes(string datoOriginal, string datoNuevo){ //Funcion para actualizar el continente cuando se modifica el nombre de un pais
    auxiliarBaseDatos.open("BaseDatosContinentes.tmp", ios::out);
    BaseDatosContinentes.open("BaseDatosContinentes", ios::in);
  
    while(getline(BaseDatosContinentes, palabra)){
        posPalabra = palabra.find(datoOriginal);
        
        if(posPalabra != string::npos){
            palabra.replace(posPalabra,datoOriginal.length(),datoNuevo);
        }
        auxiliarBaseDatos << palabra << endl;
    }
    
    auxiliarBaseDatos.close();
    BaseDatosContinentes.close();
    
    if(remove("BaseDatosContinentes") != 0) { // remove es una funcion para eliminar archivo, devuelve cero (0) si la eliminacion es exitosa
        cout << "Error al eliminar el archivo original." << endl;
        return;
    }
    
    if (rename("BaseDatosContinentes.tmp", "BaseDatosContinentes") != 0) { // rename es una funcion que permite renombrar un fichero, el primer parametro es el nombre actual, y el segundo parametro es el nombre nuevo del archivo
        cout << "Error al renombrar el nuevo archivo." << endl;
        return;
    }
        
    cout << "El Pais ha sido modificado correctamente de la base de datos de continentes." << endl;
}