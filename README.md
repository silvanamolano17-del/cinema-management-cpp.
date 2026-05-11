# cinema-management-cpp.

Sistema de gestión de catálogo audiovisual desarrollado en C++ como proyecto académico en la Pontificia Universidad Javeriana. El sistema permite administrar un inventario de películas y series mediante persistencia en archivos planos.

## 🚀 Funcionalidades
- **Gestión de Contenido:** Registro de películas y series con múltiples géneros.
- **Jerarquía de Datos:** Manejo de temporadas y capítulos asociados a series específicas.
- **Persistencia:** Lectura y escritura automática en archivos `.txt`.
- **Motor de Búsqueda:** Filtrado avanzado por género, rango de años y cantidad de capítulos.
- **Algoritmos de Ordenamiento:** Organización del catálogo por año de estreno (ascendente/descendente).

## 🛠️ Tecnologías Utilizadas
- **Lenguaje:** C++11
- **Librerías Estándar:** `iostream`, `fstream`, `sstream`, `string`.
- **Estructuras:** Uso de `structs` anidados y arreglos estáticos.

## 📥 Instalación y Ejecución

1. **Clona el repositorio:**
   ```bash
   git clone [https://github.com/silvanamolano17-del/cinema-management-cpp.git](https://github.com/silvanamolano17-del/cinema-management-cpp.git)

Compila el código:
g++ -o cinema_manager src/main.cpp

Ejecuta la aplicación:
./cinema_manager
