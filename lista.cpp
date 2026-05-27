#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
string leerString(const string& etiqueta) {
    string valor;
    while (true) {
        cout << etiqueta;
        getline(cin, valor);
        if (!valor.empty()) return valor;
        cout << "  Error, el campo no puede estar vacio.\n";
    }
}

int leerEntero(const string& etiqueta) {
    int valor;
    while (true) {
        cout << etiqueta;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Error, solo se permiten numeros enteros.\n";
        }
        else {
            char sig = cin.peek();
            if (sig != '\n' && sig != EOF) {
                cin.ignore(1000, '\n');
                cout << "  Error, solo se permiten numeros enteros.\n";
            }
            else {
                cin.ignore(1000, '\n');
                return valor;
            }
        }
    }
}

double leerNota(int numero) {
    double nota;
    while (true) {
        cout << "  Nota " << numero << " (0 - 10): ";
        cin >> nota;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Error, valor no valido.\n";
        }
        else {
            cin.ignore(1000, '\n');
            if (nota < 0 || nota > 10) {
                cout << "  Error, La nota debe estar entre 0 y 10.\n";
            }
            else {
                return nota;
            }
        }
    }
}

class Alumno {
private:
    string nombres;
    string apellidos;
    int    carnet;
    string email;
    string telefono;
    double notas[5];

public:
    Alumno() : carnet(0) {
        for (int i = 0; i < 5; i++) notas[i] = 0.0;
    }

    void ingresar() {
        cout << "\n  -- Datos personales --\n";
        nombres = leerString("  Nombres   : ");
        apellidos = leerString("  Apellidos : ");
        carnet = leerEntero("  Carnet    : ");
        email = leerString("  Email     : ");
        telefono = leerString("  Telefono  : ");

        cout << "\n  -- Notas (0 a 10) --\n";
        for (int i = 0; i < 5; i++) {
            notas[i] = leerNota(i + 1);
        }
    }

    double calcularPromedio() const {
        double suma = 0;
        for (int i = 0; i < 5; i++) suma += notas[i];
        return suma / 5.0;
    }

    void mostrar() const {
        cout << fixed << setprecision(2);
        cout << "  Nombres   : " << nombres << "\n";
        cout << "  Apellidos : " << apellidos << "\n";
        cout << "  Carnet    : " << carnet << "\n";
        cout << "  Email     : " << email << "\n";
        cout << "  Telefono  : " << telefono << "\n";
        cout << "  Notas     : ";
        for (int i = 0; i < 5; i++) {
            cout << notas[i];
            if (i < 4) cout << " | ";
        }
        cout << "\n";
        cout << "  Promedio  : " << calcularPromedio() << "\n";
    }
};

class Nodo {
public:
    Alumno dato;      
    Nodo* siguiente; 

    Nodo() : siguiente(nullptr) {}
};

class ListaAlumnos {
private:
    Nodo* cabeza;
    int   cantidad;

public:
    ListaAlumnos() : cabeza(nullptr), cantidad(0) {}
    ~ListaAlumnos() {
        liberarMemoria();
    }

    void insertarAlumno(const Alumno& alumno) {
        Nodo* nuevo = new Nodo(); 
        nuevo->dato = alumno;

        if (cabeza == nullptr) {
            cabeza = nuevo;
        }
        else {
            Nodo* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
        }
        cantidad++;
    }

    void mostrarTodos() const {
        if (cabeza == nullptr) {
            cout << "\n  (La lista esta vacia)\n";
            return;
        }

        Nodo* temp = cabeza;
        int   num = 1;

        while (temp != nullptr) {
            cout << "\n  ----------------------------------------\n";
            cout << "  ALUMNO #" << num << "\n";
            cout << "  ----------------------------------------\n";
            temp->dato.mostrar();
            temp = temp->siguiente;
            num++;
        }
        cout << "\n  ----------------------------------------\n";
        cout << "  Total de alumnos registrados: " << cantidad << "\n";
    }

    void liberarMemoria() {
        Nodo* temp;
        while (cabeza != nullptr) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cabeza = nullptr;
        cantidad = 0;
    }

    bool estaVacia() const { return cabeza == nullptr; }
};

int main() {
    ListaAlumnos lista;
    char opcion;

    cout << "==========================================\n";
    cout << "            LISTA DE ALUMNOS     \n";
    cout << "==========================================\n";

    do {
        cout << "\nDesea ingresar un nuevo alumno? (S/N): ";
        cin >> opcion;
        cin.ignore(1000, '\n');
        opcion = toupper(opcion);

        if (opcion == 'S') {
            Alumno nuevo;
            nuevo.ingresar();
            lista.insertarAlumno(nuevo);
            cout << "\n Alumno agregado exitosamente.\n";
        }
        else if (opcion != 'N') {
            cout << " Opcion invalida. Ingrese S o N.\n";
        }

    } while (opcion != 'N');

    cout << "\n==========================================\n";
    cout << "           LISTADO DE ALUMNOS         \n";
    cout << "==========================================\n";
    lista.mostrarTodos();
    cout << "\nMemoria liberada. Programa finalizado.\n";
    return 0;
}
