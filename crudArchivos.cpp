#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Curso {
    string codigo;
    string nombre;
    int creditos;
    bool activo;

    void mostrar() const {
        cout << "\nCodigo: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Creditos: " << creditos << endl;
        cout << "Activo: " << (activo ? "Si" : "No") << endl;
        cout << "--------------------------------\n";
    }
};

const string RUTA = "cursos.txt";

ostream& operator<<(ostream& salida, const Curso& c) {
    salida << c.codigo << " "
        << c.nombre << " "
        << c.creditos << " "
        << c.activo << endl;
        return salida;
}

istream& operator>>(istream& entrada, Curso& c) {
    entrada >> c.codigo >> c.nombre >> c.creditos >> c.activo;
    return entrada;
}

ostream& operator<<(ostream& salida, const vector<Curso>& cursos) {
    for (const auto& c : cursos) {
        salida << c;
    }
    return salida;
}

istream& operator>>(istream& entrada, vector <Curso>& cursos) {  
    Curso c;
    while (entrada >> c) {
        cursos.push_back(c);
    }
    return entrada;
}

void guardar(const vector<Curso>& cursos, const string& ruta) {

    ofstream archivoSalida(ruta);

    if (!archivoSalida.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para guardar\n";
        return;
    }

    archivoSalida << cursos;
    archivoSalida.close();

    cout << "Archivo guardado correctamente\n";
}

vector<Curso> leer(const string& ruta) {
    vector<Curso> cursos;

    ifstream archivoEntrada(ruta);

    if (!archivoEntrada.is_open()) {
        return cursos;
    }

    archivoEntrada >> cursos;
    archivoEntrada.close();
    return cursos;
}

void registrarCurso() {
    vector<Curso> cursos = leer(RUTA);
    Curso nuevo;

    cout << "Codigo: ";
    cin >> nuevo.codigo;

    for (const auto& c : cursos) {
        if (c.codigo == nuevo.codigo) {
            cout << "Error: El codigo ya existe\n";
            return;
        }
    }

    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nuevo.nombre);

    if (nuevo.nombre == "") {
        cout << "Error: Nombre vacio\n";
        return;
    } 

    cout << "Creditos (1 - 10): ";
    cin >> nuevo.creditos;

    if (nuevo.creditos < 1 or nuevo.creditos > 10) {
        cout << "Error: Creditos fuera de rango\n";
        return;
    }

    char opcion;
    cout << "Esta activo? (s / n): ";
    cin >> opcion;

    if (opcion == 's' or opcion == 'S') {
        nuevo.activo = true;
    } else if (opcion == 'n' or opcion == 'N') {
        nuevo.activo = false;
    } else {
        cout << "Error\n";
        return;
    }

    cursos.push_back(nuevo);
    guardar(cursos, RUTA);

    cout << "Curso registrado correctamente\n";

}

void mostrarCursos() {
    vector<Curso> cursos = leer(RUTA);

    if (cursos.empty()) {
        cout << "Error: no hay cursos registrados\n";
        return;
    }

    for (const auto& c : cursos) {
        c.mostrar();
    }

}

void buscarPorCodigo() {
    vector<Curso> cursos = leer(RUTA);

    if (cursos.empty()) {
        cout << "Error: no hay cursos registrados\n";
        return;
    }

    string codigoBuscado;
    cout << "Codigo a buscar: ";
    cin >> codigoBuscado;

    for (const auto& c : cursos) {
        if (codigoBuscado == c.codigo) {
            c.mostrar();
            return;
        }
    }

    cout << "Codigo no encontrado\n";

}

void actualizarCurso() {
    vector<Curso> cursos = leer(RUTA);
    bool encontrado = false;

    if (cursos.empty()) {
        cout << "Error: No hay cursos registrados\n";
        return;
    }
    
    string codigoBuscado;
    cout << "Codigo a buscar: ";
    cin >> codigoBuscado;

    for (auto& c : cursos) {
        if (codigoBuscado == c.codigo) {

            cout << "Nuevo nombre: ";
            cin.ignore();
            getline(cin, c.nombre);

            if (c.nombre == "") {
                cout << "Error: Nombre vacio\n";
                return;
            }

            cout << "Nuevos creditos (1 - 10): ";
            cin >> c.creditos;

            if (c.creditos < 1 or c.creditos > 10) {
                cout << "Error: Creditos fuera de rango\n";
                return;
            }

            char opcion;
            cout << "Esta activo? (s / n): ";
            cin >> opcion;

            if (opcion == 's' or opcion == 'S') {
                c.activo = true;
            } else if (opcion == 'n' or opcion == 'N') {
                c.activo = false;
            } else {
                cout << "Error\n";
                return;
            }
            encontrado = true;
            break;
        }
    }
    if (encontrado) {
        guardar(cursos, RUTA);
        cout << "Curso actualizado\n";
    } else {
        cout << "Codigo no encontrado\n";
    }
}

void eliminarCurso() {
    vector<Curso> cursos = leer(RUTA);

    if (cursos.empty()) {
        cout << "Error: No hay cursos registrados\n";
        return;
    }

    string codigoBuscado;
    cout << "Codigo a buscar: ";
    cin >> codigoBuscado;

    auto it = remove_if(cursos.begin(), cursos.end(), [&](const Curso& c) {return c.codigo == codigoBuscado;});

    if (it != cursos.end()) {
        cursos.erase(it, cursos.end());
        guardar(cursos, RUTA);
        cout << "Curso eliminado\n";
        return;
    } else {
        cout << "Codigo no encontrado\n";
    }
}

void ordenarPorNombre() {
    vector<Curso> cursos = leer(RUTA);

    if (cursos.empty()) {
        cout << "No hay cursos registrados\n";
        return;
    }

    sort(cursos.begin(), cursos.end(), [] (const Curso& a, const Curso& b) {
        return a.nombre < b.nombre;
    });

    guardar(cursos, RUTA);
    cout << "Cursos ordenados correctamente\n";

    for (const auto& c : cursos) {
        c.mostrar();
    }
}
int main(){

    int opcion;
    do
    {
        cout << "\n=== MENU ===\n";
        cout << "1. Registrar curso\n";
        cout << "2. Mostrar cursos\n";
        cout << "3. Buscar por codigo\n";
        cout << "4. Actualizar curso\n";
        cout << "5. Eliminar curso\n";
        cout << "6. Ordenar por nombre\n";
        cout << "7. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1: registrarCurso(); break;
        case 2: mostrarCursos(); break;
        case 3: buscarPorCodigo(); break;
        case 4: actualizarCurso(); break;
        case 5: eliminarCurso(); break;
        case 6: ordenarPorNombre(); break;
        case 7: cout << "Saliendo del sistema"; break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 7);
    

    return 0;
}