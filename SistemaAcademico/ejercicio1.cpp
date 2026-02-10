#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

const string archivoMaterias = "Materias.txt";
const string archivoEstudiantes = "Registro.txt";
const string archivoMatriculas = "Matriculas.txt";

struct Materia {
    int id;
    string nombre;
    int cupos;
    int creditos;
    int costo;

    void mostrar() const {
        cout << "\nID: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Cupos: " << cupos << endl;
        cout << "Creditos: " << creditos << endl;
        cout << "Costo: $" << costo << endl;
        cout << "--------------------------\n";
    }
};

struct Estudiante {
    int id;
    string nombre;
    string cedula;
    string carrera;
    int semestre;
    double notas[3];
    double promedio;

    void calcularPromedio() {
        double suma = 0;
        for (int i = 0; i < 3; i++) {
            suma += notas[i];
        }
        promedio = suma / 3;
    }

    void mostrar() const {
        cout << "\nId del estudiante: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Cedula: " << cedula << endl;
        cout << "Carrera: " << carrera << endl;
        cout << "Semestre: " << semestre << endl;
        cout << "Notas: " << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Nota " << i + 1 << ": " << notas[i] << endl;
        }

        cout << "Promedio: " << promedio << endl;
        cout << "--------------------------\n";
    }
};

struct Matricula {
    int id;
    Estudiante e;
    Materia m;
};

vector<Materia> materias;
vector<Estudiante> estudiantes;
vector<Matricula> matriculas;

void guardarMaterias(const vector<Materia>& materias, const string& archivoMaterias) {

    ofstream archivoSalida(archivoMaterias);

    if (!archivoSalida.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para guardar\n";
        return;
    }

    for (const auto& m : materias) {
        archivoSalida << m.id << "|"
            << m.nombre << "|"
            << m.cupos << "|"
            << m.creditos << "|"
            << m.costo << endl;
    }
    archivoSalida.close();
}

void leerMaterias(vector<Materia>& materias, const string& archivoMaterias) {

    ifstream archivoEntrada(archivoMaterias);

    if (!archivoEntrada.is_open()) {
        cerr << "Error\n";
        return;
    } 

    materias.clear();

    string linea;
    Materia m;

    while (getline(archivoEntrada, linea)) {
        size_t pos;

        pos = linea.find('|');
        m.id = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        m.nombre = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        m.cupos = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        m.creditos = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        m.costo = stoi(linea);

        materias.push_back(m);
    }

    archivoEntrada.close();
}

void guardarEstudiante(const vector<Estudiante>& estudiantes, const string& archivoEstudiantes) {

    ofstream archivoSalida(archivoEstudiantes);

    if (!archivoSalida.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para guardar\n";
        return;
    }

    for (const auto& e : estudiantes) {
        archivoSalida << e.id << "|"
                << e.nombre << "|"
                << e.cedula << "|"
                << e.carrera << "|"
                << e.semestre << "|";
        for (int i = 0; i < 3; i++) {
            archivoSalida << e.notas[i] << ",";
        }
        archivoSalida << "|" << e.promedio << endl;
    }

    archivoSalida.close();
    cout << "Estudiantes guardados correctamente\n";
}

void leerEstudiantes(vector<Estudiante>& estudiantes, const string& archivoEstudiantes) {

    ifstream archivoEntrada(archivoEstudiantes);

    if (!archivoEntrada.is_open()) {
        cerr << "Error\n";
        return;
    }

    estudiantes.clear();

    string linea;
    Estudiante e;

    while (getline(archivoEntrada, linea)) {
        size_t pos;

        pos = linea.find('|');
        e.id = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        e.nombre = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        e.cedula = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        e.carrera = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        e.semestre = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        pos = linea.find('|');
        string notasTexto = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        for (int i = 0; i < 3; i++) {
            size_t coma = notasTexto.find(',');
            if(coma != string::npos) {
                e.notas[i] = stod(notasTexto.substr(0, coma));
                notasTexto.erase(0, coma + 1);
            } else {
                e.notas[i] = stod(notasTexto);
            }
        }

        e.promedio = stod(linea);

        estudiantes.push_back(e);
    }
    archivoEntrada.close();
}

void agregarMateria(vector<Materia>& materias) {
    Materia m;
    cout << "ID: ";
    cin >> m.id;

    cout << "Nombre: ";
    cin.ignore();
    getline(cin, m.nombre);

    cout << "Cupos: ";
    cin >> m.cupos;

    cout << "Creditos: ";
    cin >> m.creditos;

    cout << "Costo: $";
    cin >> m.costo;

    materias.push_back(m);
    cout << "Materia agregada correctamente\n";
}

void mostrarMaterias(const vector<Materia>& materias) {

    if (materias.empty()) {
        cout << "No hay materias registradas\n";
        return;
    }

    for (const auto& m : materias) {
        m.mostrar();
    }
}

void actualizarMateria(vector<Materia>& materias) {
    if (materias.empty()) {
        cout << "No hay materias registradas\n";
        return;
    }

    int idBuscado;
    cout << "Ingrese el ID de la materia a actualizar: ";
    cin >> idBuscado;
    cin.ignore();

    for (auto& m : materias) {
        if (idBuscado == m.id) {
            cout << "Nuevo nombre: ";
            getline(cin, m.nombre);

            cout << "Nuevos cupos: ";
            cin >> m.cupos;

            cout << "Nuevos creditos: ";
            cin >> m.creditos;

            cout << "Nuevo costo: $";
            cin >> m.costo;
            
            cout << "Materia actualizada\n";
            return;
        }
    }
    cout << "Materia no encontrada\n";
}

void eliminarMateria(vector<Materia>& materias) {

    if (materias.empty()) {
        cout << "No hay materias registradas\n";
        return;
    }

    int idBuscado;
    cout << "Ingrese el ID de la materia a eliminar: ";
    cin >> idBuscado;

    auto it = remove_if(materias.begin(), materias.end(), [&](const Materia& m) {return m.id == idBuscado;});

    if (it != materias.end()) {
        materias.erase(it, materias.end());
        cout << "Materia eliminada\n";
        return;
    }

    cout << "Materia no encontrada\n";
}

void menuMaterias(vector<Materia>& materias) {
    int opcion;
    do
    {
        cout << "\n=== MENU MATERIAS ===\n";
        cout << "1. Agregar una materia\n";
        cout << "2. Mostrar todas las materias registradas\n";
        cout << "3. Actualizar una materia por su ID\n";
        cout << "4. Eliminar una materia por su ID\n";
        cout << "5. Salir al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                agregarMateria(materias);
                guardarMaterias(materias, archivoMaterias);
                break;
            case 2:
                mostrarMaterias(materias);
                break;
            case 3:
                actualizarMateria(materias);
                guardarMaterias(materias, archivoMaterias);
                break;
            case 4:
                eliminarMateria(materias);
                guardarMaterias(materias, archivoMaterias);
                break;
            case 5:
                cout << "Saliendo del menu materias...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
    } while (opcion != 5);
    
}

void crearEstudiante(vector<Estudiante>& estudiantes) {

    Estudiante e;

    cout << "ID: ";
    cin >> e.id;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, e.nombre);

    cout << "Cedula: ";
    cin >> e.cedula;

    cout << "Carrera: ";
    cin >> e.carrera;

    cout << "Semestre: ";
    cin >> e.semestre;

    cout << "Ingrese las 3 notas:\n";
    for (int i = 0; i < 3; i++) {
        cout << "Nota " << i + 1 << ": ";
        cin >> e.notas[i];
    }

    e.calcularPromedio();

    estudiantes.push_back(e);
    cout << "Estudiante agregado correctamente\n";
}

void mostrarEstudiantes(const vector<Estudiante>& estudiantes) {

    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados\n";
        return;
    }

    for (const auto& e : estudiantes) {
        e.mostrar();
    }
}

void actualizarEstudiante(vector<Estudiante>& estudiantes) {

    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados\n";
        return;
    }

    int idBuscado;
    cout << "Ingrese el ID del estudiante a actualizar: ";
    cin >> idBuscado;
    cin.ignore();

    for (auto& e : estudiantes) {
        if (e.id == idBuscado) {
            cout << "Nuevo nombre: ";
            getline(cin, e.nombre);

            cout << "Nueva cedula: ";
            cin >> e.cedula;

            cout << "Nueva carrera: ";
            cin >> e.carrera;

            cout << "Nuevo semestre: ";
            cin >> e.semestre;

            cout << "Ingrese nuevas notas:\n";
            for (int i = 0; i < 3; i++) {
                cout << "Nota " << i + 1 << ": ";
                cin >> e.notas[i];
            }

            e.calcularPromedio();

            cout << "Estudiante actualizado\n";
            return;
        }
    }
    cout << "Estudiante no encontrado\n";  
}

void eliminarEstudiante(vector<Estudiante>& estudiantes) {

    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados\n";
        return;
    }

    int idBuscado;
    cout << "Ingrese el ID del estudiante a eliminar: ";
    cin >> idBuscado;

    auto it = remove_if(estudiantes.begin(), estudiantes.end(), [&](const Estudiante& e) {return e.id == idBuscado;});

    if (it != estudiantes.end()) {
        estudiantes.erase(it, estudiantes.end());
        cout << "Estudiante eliminado\n";
        return;
    }
    cout << "Estudiante no encontrado\n";
}

void menuEstudiantes(vector<Estudiante>& estudiantes) {
    int opcion;

    do
    {
        cout << "\n=== MENU ESTUDIANTES ===\n";
        cout << "1. Crear un registro de estudiante\n";
        cout << "2. Mostrar todos los estudiantes\n";
        cout << "3. Modificar un estudiante por ID\n";
        cout << "4. Eliminar un estudiante por ID\n";
        cout << "5. Guardar estudiantes en archivo\n";
        cout << "6. Salir al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crearEstudiante(estudiantes);
                break;
            case 2:
                mostrarEstudiantes(estudiantes);
                break;
            case 3:
                actualizarEstudiante(estudiantes);
                break;
            case 4:
                eliminarEstudiante(estudiantes);
                break;
            case 5:
                guardarEstudiante(estudiantes, archivoEstudiantes);
                break;
            case 6:
                cout << "Saliendo del menu estudiantes...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
    } while (opcion != 6);
    
}

void guardarMatricula(vector<Matricula>& matriculas, const string& archivoMatriculas) {

    ofstream archivoSalida(archivoMatriculas);

    if(!archivoSalida.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para guardar\n";
        return;
    }

    for (const auto& m : matriculas) {
        archivoSalida << m.id << "|"
                << m.e.id << "|"
                << m.m.id << "|" << endl;
    }
    archivoSalida.close();
}

void matricularEstudiante(const vector<Estudiante>& estudiantes, vector<Materia>& materias, vector<Matricula>& matriculas) {

    if (estudiantes.empty() or materias.empty()) {
        cout << "No hay estudiantes o materias registradas\n";
        return;
    }

    int idEstudiante, idMateria;
    bool estudianteEncontrado = false;
    bool materiaEncontrada = false;
    int posEstudiante = -1;
    int posMateria = -1;

    cout << "Ingrese el ID del estudiante a matricular: ";
    cin >> idEstudiante;

    for (int i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i].id == idEstudiante) {
            estudianteEncontrado = true;
            posEstudiante = i;
            break;;
        }
    }

    if(!estudianteEncontrado) {
        cout << "Estudiante no encontrado\n";
        return;
    }

    cout << "Ingrese el ID de la materia a matricular: ";
    cin >> idMateria;

    for (int i = 0; i < materias.size(); i++) {
        if (materias[i].id == idMateria) {
            materiaEncontrada = true;
            posMateria = i;
            break;
        }
    }

    if (!materiaEncontrada) {
        cout << "Materia no encontrada\n";
        return;
    }

    if (materias[posMateria].cupos <= 0) {
        cout << "No hay cupos disponibles en esa materia\n";
        return;
    }

    Matricula nueva;

    nueva.id = matriculas.size() + 1;
    nueva.e = estudiantes[posEstudiante];
    nueva.m = materias[posMateria];

    matriculas.push_back(nueva);

    materias[posMateria].cupos--;

    guardarMatricula(matriculas, archivoMatriculas);
    guardarMaterias(materias, archivoMaterias);
    cout << "Matricula realizada correctamente\n";

}

void menuPrincipal() {
    int opcion;
    do
    {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Gestion de materias\n";
        cout << "2. Gestion de estudiantes\n";
        cout << "3. Matricular estudiante\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuMaterias(materias); break;
            case 2: menuEstudiantes(estudiantes); break;
            case 3: matricularEstudiante(estudiantes, materias, matriculas);
        }
    } while (opcion != 4);
    
}
int main() {

    leerMaterias(materias, archivoMaterias);
    leerEstudiantes(estudiantes, archivoEstudiantes);

    menuPrincipal();
    return 0;
}
