#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Capitulo {
    int numeroTemporada;
    int numeroCapitulo;
  string titulo;
    int duracion; 
};


struct Pelicula {
   string nombre;
    int duracion;
    int aEstreno;
    string genero;      
  string generos[10]; 
    int cantidadGeneros;      
};


struct Serie {
    string nombre;
    int numeroTemporadas;
    string genero;        
    string generos[10];   
    int cantidadGeneros;       
    Capitulo capitulos[100];  
    int cantidadCapitulos;
};


const int MAX_PELICULAS = 100;  
const int MAX_SERIES = 100;
Pelicula peliculas[MAX_PELICULAS];
Serie series[MAX_SERIES];
int cantidadPeliculas = 0;
int cantidadSeries = 0;     


string convierte(string str) {
    string result;
    for (char c : str) {
        if (c >= 'A' && c <= 'Z') {
            result += c + ('a' - 'A');  
        } else {
            result += c;
        }
    }
    return result;
}


void leerPeliculas(string nombreArchivo, Pelicula peliculas[], int& cantidadPeliculas) {
    ifstream archivo(nombreArchivo);
    string linea;
    cantidadPeliculas = 0;

    while (getline(archivo, linea) && cantidadPeliculas < MAX_PELICULAS) {
        stringstream ss(linea);
        string nombre, duracion, aEstreno, genero;

        getline(ss, nombre, ',');
        getline(ss, duracion, ',');
        getline(ss, aEstreno, ',');
        getline(ss, genero, ',');

        peliculas[cantidadPeliculas] = {nombre, stoi(duracion),stoi(aEstreno), genero};
        cantidadPeliculas++;
    }
    archivo.close();
}

void leerSeries(string nombreArchivo, Serie series[], int& cantidadSeries) {
    ifstream archivo(nombreArchivo);
    string linea;
    cantidadSeries = 0;

    while (getline(archivo, linea) && cantidadSeries < MAX_SERIES) {
       stringstream ss(linea);
       string nombre, numeroTemporadas, genero;

        getline(ss, nombre, ',');
        getline(ss, numeroTemporadas, ',');
        getline(ss, genero, ',');

        series[cantidadSeries] = {nombre, stoi(numeroTemporadas), genero};

        cantidadSeries++;
    }
       archivo.close();
}

void imprimirPeliculas(Pelicula peliculas[], int cantidadPeliculas) {
    cout << "Películas leídas:\n\n";
    for (int i = 0; i < cantidadPeliculas; i++) {
        cout << "Nombre: " << peliculas[i].nombre << "\n";
        cout << "Duración: " << peliculas[i].duracion << " minutos\n";
        cout << "Año de estreno: " << peliculas[i].aEstreno << "\n";
        cout << "Género: " << peliculas[i].genero << "\n\n";
    }
}



void imprimirSeries(Serie series[], int cantidadSeries) {
    cout << "Series leídas:\n\n";
    for (int i = 0; i < cantidadSeries; i++) {
        cout << "Nombre: " << series[i].nombre << "\n";
        cout << "Número de Temporadas: " << series[i].numeroTemporadas << "\n";
        cout << "Género: " << series[i].genero << "\n\n";
    }
}



bool peliculaExiste(string& nombre, Pelicula peliculas[], int cantidadPeliculas) {
   string nombreLower = convierte(nombre);
    for (int i = 0; i < cantidadPeliculas; i++) {
       string nombrePelicula = convierte(peliculas[i].nombre);
        if (nombreLower == nombrePelicula) {
            return true;
        }
    }
    return false;
}



void guardarPeliculaEnArchivo(Pelicula& pelicula) {
    ofstream archivo("peliculas.txt", ios::app);  
    if (archivo.is_open()) {
         archivo << pelicula.nombre << ", "
                 << pelicula.duracion << " minutos," 
                 << pelicula.aEstreno; 
             for (int i = 0; i < pelicula.cantidadGeneros; i++) {
                archivo <<", "<< pelicula.generos[i];
            }


        archivo << "\n"; 
        archivo.close();
        cout << "Película guardada en peliculas.txt\n";
    } else {
        cerr << "Error al abrir el archivo peliculas.txt\n";
    }

}



void solicitarDatosPelicula(Pelicula peliculas[], int cantidadPeliculas) {
    Pelicula nuevaPelicula;
    nuevaPelicula.cantidadGeneros = 0;

    cout << "Ingrese el nombre de la película: ";
    getline(cin, nuevaPelicula.nombre);

      if (peliculaExiste(nuevaPelicula.nombre,peliculas,cantidadPeliculas)) {
        cerr << "ESTA PELÍCULA YA EXISTE, INTENTE DE NUEVO.\n";
        return;
      }    
    cout << "Ingrese la duración de la película (en minutos): ";
    cin >> nuevaPelicula.duracion;
    if (nuevaPelicula.duracion <= 0) {
        cerr << "LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO.\n";
        return;
    }

    cout << "Ingrese el año de estreno de la película: ";
    cin >> nuevaPelicula.aEstreno;
    if (nuevaPelicula.aEstreno <= 0) {
        cerr << "LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO.\n";
        return;
    }

    cin.ignore(); 

    string respuesta;
    do {
        cout << "Ingrese un género para la película: ";
        getline(cin, nuevaPelicula.generos[nuevaPelicula.cantidadGeneros]);
        nuevaPelicula.cantidadGeneros++;

        cout << "¿Desea asignarle otro género a la película? (s/n): ";
        getline(cin, respuesta);
    } while (respuesta == "s" || respuesta == "S");



    peliculas[cantidadPeliculas] = nuevaPelicula;
    cantidadPeliculas++;
    cout << "Película creada exitosamente.\n";
    guardarPeliculaEnArchivo(nuevaPelicula);
}


bool serieExiste(string& nombre, Serie series[], int cantidadSeries) {
    string nombreLower = convierte(nombre);
    for (int i = 0; i < cantidadSeries; i++) {
       string nombreSerie = convierte(series[i].nombre);
        if (nombreLower == nombreSerie) {
            return true;
        }
    }
    return false;
}


void guardarSerieEnArchivo(Serie& serie) {
    ofstream archivo("series.txt", ios::app);  
    if (archivo.is_open()) {
         archivo << serie.nombre << ", "
                 << serie.numeroTemporadas; 
             for (int i = 0; i < serie.cantidadGeneros; i++) {
                archivo <<", "<< serie.generos[i];
            }


        archivo << "\n"; 
        archivo.close();
        cout << "Serie guardada en series.txt\n";
    } else {
        cerr << "Error al abrir el archivo series.txt\n";
    }
}


void solicitarDatosSerie(Serie series[], int cantidadSeries) {
    Serie nuevaSerie;
    nuevaSerie.cantidadGeneros = 0;

    cout << "Ingrese el nombre de la serie: ";
    getline(cin, nuevaSerie.nombre);

    cout << "Ingrese el número de temporadas de la serie: ";
    cin >> nuevaSerie.numeroTemporadas;
    if (nuevaSerie.numeroTemporadas <= 0) {
        cerr << "LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO.\n";
        return;
    }

    cin.ignore();  

   string respuesta;
    do {
        cout << "Ingrese un género para la serie: ";
        getline(cin, nuevaSerie.generos[nuevaSerie.cantidadGeneros]);
        nuevaSerie.cantidadGeneros++;

        cout << "¿Desea asignarle otro género a la serie? (s/n): ";
        getline(cin, respuesta);
    } while (respuesta == "s" || respuesta == "S");

    if (serieExiste(nuevaSerie.nombre,series, cantidadSeries)) {
        cout << "ESTA SERIE YA EXISTE, INTENTE DE NUEVO.\n";
        return;
    }

    series[cantidadSeries] = nuevaSerie;
    cantidadSeries++;
    cout << "Serie creada exitosamente.\n";
    guardarSerieEnArchivo(nuevaSerie);  
}



int encontrarSerie(string nombre, Serie series[], int cantidadSeries) {
    string nombreLower = convierte(nombre);

    for (int i = 0; i < cantidadSeries; i++) {
        string nombreSerie = convierte(series[i].nombre);
        if (nombreLower == nombreSerie) {
            return i;
        }
    }
    return -1; 
}


void solicitarDatosCapitulo(Serie series[], int indiceSerie) {
    Serie& serie = series[indiceSerie];
    Capitulo nuevoCapitulo;

    cout << "Ingrese el número de temporada del capítulo: ";
    cin >> nuevoCapitulo.numeroTemporada;
    if (nuevoCapitulo.numeroTemporada <= 0 || nuevoCapitulo.numeroTemporada > serie.numeroTemporadas) {
        cout << "LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO.\n";
        return;
    }

    cout << "Ingrese el número del capítulo: ";
    cin >> nuevoCapitulo.numeroCapitulo;
    if (nuevoCapitulo.numeroCapitulo <= 0) {
        cout << "LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO.\n";
        return;
    }

    cin.ignore(); 
    
    cout << "Ingrese el título del capítulo: ";
    getline(cin, nuevoCapitulo.titulo);

    cout << "Ingrese la duración del capítulo (en minutos): ";
    cin >> nuevoCapitulo.duracion;
    if (nuevoCapitulo.duracion <= 0) {
        cout << "LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO.\n";
        return;
    }

    serie.capitulos[serie.cantidadCapitulos] = nuevoCapitulo;
    serie.cantidadCapitulos++;
    cout << "Capítulo añadido exitosamente.\n";
}
    


void mostrarCapitulos(Serie series[], int cantidadSeries) {
    if (cantidadSeries == 0) {
        cout << "No hay series registradas.\n";
        return;
    }

    for (int j = 0; j < cantidadSeries; ++j) {
        if (series[j].cantidadCapitulos == 0) {
            cout << "La serie \"" << series[j].nombre;
            cout << "\" no tiene capítulos registrados.\n";
            continue;
        }

        cout << "\nCapítulos de la serie \"" << series[j].nombre << "\":\n";
        for (int i = 0; i < series[j].cantidadCapitulos; ++i) {
            const Capitulo& cap = series[j].capitulos[i];
            cout << "  Temporada " << cap.numeroTemporada
                 << ", Capítulo " << cap.numeroCapitulo
                 << ": " << cap.titulo
                 << " (" << cap.duracion << " minutos)\n";
        }
    }
}

void manejarCapitulos(Serie series[], int cantidadSeries) {
    string opcionSerie;

    do {
        string nombreSerie;

      
        cout << "Ingrese el nombre de la serie: ";
        getline(cin, nombreSerie);

        
        int indiceSerie = encontrarSerie(nombreSerie, series, cantidadSeries);
        if (indiceSerie == -1) {
            cout << "LA SERIE NO EXISTE, INTENTE DE NUEVO.\n";
            continue;
        }

        string opcionCapitulo;
        do {
          
            solicitarDatosCapitulo(series, indiceSerie);

            cout << "¿Desea ingresar otro capítulo a esta serie? (s/n): ";
            cin.ignore();
            getline(cin, opcionCapitulo);

        } while (opcionCapitulo == "s" || opcionCapitulo == "S");

        cout << "¿Desea ingresar capítulos a otra serie? (s/n): ";
        getline(cin, opcionSerie);

    } while (opcionSerie == "s" || opcionSerie == "S");

  
    mostrarCapitulos(series, cantidadSeries);
}


void listarCapitulosPorTemporada(Serie series[], int cantidadSeries) {
    int temporada;
    cout << "Ingrese el número de temporada a listar: ";
    cin >> temporada;

    if (temporada <= 0) {
        cerr << "Número de temporada inválido.\n";
        return;
    }

    bool encontrados = false;

    for (int i = 0; i < cantidadSeries; i++) {
        Serie& serie = series[i];

        cout << "\nSerie: " << serie.nombre << "\n";
        cout << "Capítulos de la temporada " << temporada << ":\n";

        bool encontradosEnSerie = false;

        for (int j = 0; j < serie.cantidadCapitulos; j++) {
            if (serie.capitulos[j].numeroTemporada == temporada) {
                cout << "  Capítulo " << serie.capitulos[j].numeroCapitulo << ": "
                     << serie.capitulos[j].titulo << " - "
                     << serie.capitulos[j].duracion << " minutos\n";
                encontrados = true;
                encontradosEnSerie = true;
            }
        }

        if (!encontradosEnSerie) {
            cout << "  No se encontraron capítulos para esta temporada en la serie \"" << serie.nombre << "\".\n";
        }
    }

    if (!encontrados) {
        cout << "No se encontraron capítulos para la temporada " << temporada << " en ninguna serie.\n";
    }
}

void filtrarSeriesPorGenero(Serie series[], int cantidadSeries, string generoBuscado) {
    bool encontrado = false;
    cout << "Series del género \"" << generoBuscado << "\":\n";
    for (int i = 0; i < cantidadSeries; ++i) {
        if (series[i].genero == generoBuscado) {
            cout << "- " << series[i].nombre << " | Temporadas: " 
                 << series[i].numeroTemporadas << " | Capítulos: " 
                 << series[i].cantidadCapitulos << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron series del género \"" << generoBuscado << "\".\n";
    }
}

void filtrarPeliculasPorGenero(Pelicula peliculas[], int cantidadPeliculas, string generoBuscado) {
    bool encontrado = false;
    cout << "Películas del género \"" << generoBuscado << "\":\n";
    for (int i = 0; i < cantidadPeliculas; ++i) {
        if (peliculas[i].genero == generoBuscado) {
            cout << "- " << peliculas[i].nombre << " | Nombre: "  << peliculas[i].duracion << " minutos\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron películas del género \"" << generoBuscado << "\".\n";
    }
}

void filtrarSeriesPorCapitulos(Serie series[], int cantidadSeries, int minCapitulos) {
    bool encontrado = false;

    cout << "Series con al menos " << minCapitulos << " capítulos:\n";
    for (int i = 0; i < cantidadSeries; ++i) {
        if (series[i].cantidadCapitulos >= minCapitulos) {
            cout << "- " << series[i].nombre
                 << " | Género: " << series[i].genero
                 << " | Temporadas: " << series[i].numeroTemporadas
                 << " | Capítulos: " << series[i].cantidadCapitulos << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron series con al menos " << minCapitulos << " capítulos.\n";
    }
}



bool filtrarPeliculasPorAño(Pelicula peliculas[], int cantidadPeliculas) {
    int anioInicio, anioFin;


    cout << "Ingrese el año de inicio: ";
    cin >> anioInicio;
    cout << "Ingrese el año de fin: ";
    cin >> anioFin;

    cin.ignore(); 


    if (anioInicio > anioFin) {
        cout << "El año de inicio no puede ser mayor que el año de fin. Intente de nuevo.\n";
        return false;
    }

    bool encontrado = false;
    cout << "Películas estrenadas entre " << anioInicio << " y " << anioFin << ":\n";


    for (int i = 0; i < cantidadPeliculas; i++) {
        if (peliculas[i].aEstreno >= anioInicio && peliculas[i].aEstreno <= anioFin) {
            cout << "Película: " << peliculas[i].nombre << " (Año: " << peliculas[i].aEstreno << ")\n";
            encontrado = true;
        }
    }

 
    if (!encontrado) {
        cout << "No se encontraron películas estrenadas en el rango de años especificado.\n";
    }

    return encontrado;
}

void ordenarPeliculas(Pelicula peliculas[], int cantidadPeliculas, string orden) {
    bool ascendente = (orden == "ascendente");

    for (int i = 0; i < cantidadPeliculas - 1; i++) {
        for (int j = 0; j < cantidadPeliculas - i - 1; j++) {
           
            bool condicion;
            if (ascendente) {
                condicion = peliculas[j].aEstreno > peliculas[j + 1].aEstreno;
            } else {
                condicion = peliculas[j].aEstreno < peliculas[j + 1].aEstreno;
            }

            
            if (condicion || 
                (peliculas[j].aEstreno == peliculas[j + 1].aEstreno &&
                 peliculas[j].nombre > peliculas[j + 1].nombre)) {
           
                Pelicula temp = peliculas[j];
                peliculas[j] = peliculas[j + 1];
                peliculas[j + 1] = temp;
            }
        }
    }
}

void guardarEImprimirPeliculasOrdenadas(Pelicula peliculas[], int cantidadPeliculas, string orden) {
    
    ordenarPeliculas(peliculas, cantidadPeliculas, orden);


    ofstream archivo("peliculas_ordenadas.txt");

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar las películas ordenadas." << endl;
        return;
    }


    cout << "\nPelículas ordenadas (" << orden << "):\n";
    for (int i = 0; i < cantidadPeliculas; ++i) {
        cout << "- " << peliculas[i].nombre << " | Año: " << peliculas[i].aEstreno << "\n";
        archivo << peliculas[i].nombre << " | Año: " << peliculas[i].aEstreno << "\n";
    }

    archivo.close();
    cout << "\n Películas ordenadas guardadas en 'peliculas_ordenadas.txt'.\n";
}

// Guarde en un archivo todas las peliculas que tienen un anio de estreno par.
// NOMBRE DE LA PELICULA -  ANIO 

void guardarPeliculasPorAnio(Pelicula peliculas[], int cantidadPeliculas) {
    int aniopar;


    ofstream archivo("peliculas_por_anio.txt");

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar las películas.\n";
        return;
    }

    bool encontrado = false;


    for (int i = 0; i < cantidadPeliculas; ++i) {
        if (peliculas[i].aEstreno % 2 == 0) {
         
            cout << "Nombre: " << peliculas[i].nombre 
                 << " | Año: " << peliculas[i].aEstreno << "\n";

            
            archivo << "Título: " << peliculas[i].nombre 
                    << " | Año: " << peliculas[i].aEstreno << "\n";

            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron películas del año " << aniopar << ".\n";
        archivo << "No se encontraron películas del año " << aniopar << ".\n";
    }

    archivo.close();
    cout << "Películas guardadas en 'peliculas_por_anio.txt'.\n  " << aniopar;
}


int main() {
    Pelicula peliculas[MAX_PELICULAS];
    int cantidadPeliculas = 0;

    Serie series[MAX_SERIES];
    int cantidadSeries = 0;

    int opcion;
    bool continuar = true;

    while (continuar) {
    
        cout << "1. Leer archivo películas\n";
        cout << "2. Leer archivo series\n";
        cout << "3. Crear película\n";
        cout << "4. Crear serie\n";
        cout << "5. Añadir capítulos a una serie\n";
        cout << "6. Listar capítulos por temporada\n";
        cout << "7. Listar series por género\n";
        cout << "8. Listar películas por género\n";
        cout << "9. filtar por cantidad de capitulos\n";
        cout << "10.Filtrar peliculas por años\n";
        cout << "11.Ordenar Peliculas\n";
        cout << "12.Peliculas por año par\n";
        cout << "13.Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); 

        if (opcion == 1) {
            leerPeliculas("peliculas.txt", peliculas, cantidadPeliculas);
            imprimirPeliculas(peliculas, cantidadPeliculas);
        } else if (opcion == 2) {
            leerSeries("series.txt", series, cantidadSeries);
            imprimirSeries(series, cantidadSeries);
        } else if (opcion == 3) {
            solicitarDatosPelicula(peliculas, cantidadPeliculas);
        } else if (opcion == 4) {
            solicitarDatosSerie(series, cantidadSeries);
        } else if (opcion == 5) {
            manejarCapitulos(series, cantidadSeries);
        } else if (opcion == 6) {
             listarCapitulosPorTemporada(series, cantidadSeries);
           
        } else if (opcion == 7) {
            string genero;
            cout << "Ingrese el género de las series a buscar: ";
            getline(cin, genero);
            filtrarSeriesPorGenero(series, cantidadSeries, genero);
        } else if (opcion == 8) {
            string genero;
            cout << "Ingrese el género de las películas a buscar: ";
            getline(cin, genero);
            filtrarPeliculasPorGenero(peliculas, cantidadPeliculas, genero);
        } else if (opcion == 9) {
            int minCapitulos;
            cout << "Ingrese la cantidad mínima de capítulos: ";
            cin >> minCapitulos;
            filtrarSeriesPorCapitulos(series, cantidadSeries, minCapitulos);
          
        } else if (opcion == 10) {
            
          filtrarPeliculasPorAño(peliculas, cantidadPeliculas);
        
        } else if (opcion == 11) {
   string orden;
    			cout << "Ingrese el orden para ordenar las películas (ascendente/descendente): ";
    			cin >> orden;

    			if (orden != "ascendente" && orden != "descendente") {
       				 cout << "Orden no válido. Por favor, elija 'ascendente' o 'descendente'." << endl;
        			return 1;
    }
				guardarEImprimirPeliculasOrdenadas(peliculas, cantidadPeliculas, orden);
				
        } else if (opcion == 12) {
            
            guardarPeliculasPorAnio(peliculas,cantidadPeliculas);
            
        } else if (opcion == 13) {
    
            continuar = false; 
            cout << "Saliendo del programa...\n";
        } else {
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    }

    return 0;
}
