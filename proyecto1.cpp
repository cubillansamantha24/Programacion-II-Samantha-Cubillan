#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

// Estructuras
struct HistorialMedico {
    int idConsulta;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costoConsulta;
};

struct Cita {
    int id;
    int idPaciente;
    int idDoctor;
    char fecha[11];
    char hora[6];
    char motivo[150];
    char estado[20];
    char observaciones[200];
    bool atendida;
};

struct Paciente {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    int edad;
    char sexo;
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    HistorialMedico* historial;
    int cantidadConsultas;
    int capacidadHistorial;
    int capacidadConsultas;
    int cantidadHistorial;
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    char alergias[500];
    char observaciones[500];
    bool activo;
};


struct Doctor {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    int* pacientesAsignados;
    int cantidadPacientes;
    int capacidadPacientes;
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    bool disponible;
};
struct Hospital {
    char nombre[100];
    char direccion[150];
    char telefono[15];
    Paciente* pacientes;
    int cantidadPacientes;
    int capacidadPacientes;
    int siguienteIdPaciente;
    int siguienteIdConsulta;
    Doctor* doctores;
    int cantidadDoctores;
    int capacidadDoctores;
    int siguienteIdDoctor;
    Cita* citas;
    int cantidadCitas;
    int capacidadCitas;
    int siguienteIdCita;

};

// Inicializar hospital 
Hospital* inicializarHospital(const char* nombre, const char* direccion, const char* telefono) {
    Hospital* hospital = new Hospital;
    strncpy(hospital->nombre, nombre, 100);
    strncpy(hospital->direccion, direccion, 150);
    strncpy(hospital->telefono, telefono, 15);
    hospital->capacidadPacientes = 10;
    hospital->cantidadPacientes = 0;
    hospital->pacientes = new Paciente[hospital->capacidadPacientes];
    hospital->siguienteIdPaciente = 1;
    hospital->siguienteIdConsulta = 1;
    hospital->capacidadDoctores = 10;
hospital->cantidadDoctores = 0;
hospital->doctores = new Doctor[hospital->capacidadDoctores];
hospital->siguienteIdDoctor = 1;
hospital->capacidadCitas = 20;
hospital->cantidadCitas = 0;
hospital->siguienteIdCita = 1;
hospital->citas = new Cita[hospital->capacidadCitas];


    return hospital;
}
// FUNCIONES PACIENTES
// Crear paciente
Paciente* crearPaciente(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula, nt edad, char sexo,const char* tipoSangre, const char* telefono, const char* direccion, onst char* email, const char* alergias, const char* observaciones){
	//Para no registrar una cedula ya existente
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strcmp(hospital->pacientes[i].cedula, cedula) == 0) {
            cout << "Error: Cédula ya registrada.\n";
            return nullptr;
        }
    }
// Buscar paciente por ID
Paciente* buscarPacientePorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}
// Buscar paciente por cedula
Paciente* buscarPacientePorCedula(Hospital* hospital, const char* cedulaBuscada) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strcmp(hospital->pacientes[i].cedula, cedulaBuscada) == 0) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr; 
} //Verificar que la cedula ya esta registrada
bool cedulaExiste(Hospital* hospital, const char* cedulaBuscada) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strcmp(hospital->pacientes[i].cedula, cedulaBuscada) == 0) {
            return true;
        }
    }
    return false;
}
//Buscar paciente por nombre
void buscarPacientesPorNombre(Hospital* h, const char* fragmento) {
    cout << "\nPacientes que coinciden con \"" << fragmento << "\":\n";
    for (int i = 0; i < h->cantidadPacientes; i++) {
        if (strstr(h->pacientes[i].nombre, fragmento) != nullptr) {
            cout << "ID: " << h->pacientes[i].id << " | " << h->pacientes[i].nombre << " " << h->pacientes[i].apellido << "\n";
        }
    }
}


//Redimensionar arreglo pacientes
if (hospital->cantidadPacientes >= hospital->capacidadPacientes) {
        int nuevaCapacidad = hospital->capacidadPacientes * 2;
        Paciente* nuevoArray = new Paciente[nuevaCapacidad];
        for (int i = 0; i < hospital->cantidadPacientes; i++) {
            nuevoArray[i] = hospital->pacientes[i];
        }
        delete[] hospital->pacientes;
        hospital->pacientes = nuevoArray;
        hospital->capacidadPacientes = nuevaCapacidad;
    }
    Paciente& nuevo = hospital->pacientes[hospital->cantidadPacientes];
    nuevo.id = hospital->siguienteIdPaciente++;
    strncpy(nuevo.nombre, nombre, 50);
    strncpy(nuevo.apellido, apellido, 50);
    strncpy(nuevo.cedula, cedula, 20);
    nuevo.edad = edad;
    nuevo.sexo = sexo;
    strncpy(nuevo.tipoSangre, tipoSangre, 5);
    strncpy(nuevo.telefono, telefono, 15);
    strncpy(nuevo.direccion, direccion, 100);
    strncpy(nuevo.email, email, 50);
    strncpy(nuevo.alergias, alergias, 500);
    strncpy(nuevo.observaciones, observaciones, 500);
    nuevo.activo = true;
    nuevo.capacidadConsultas = 5;
    nuevo.cantidadHistorial = 0;
    nuevo.historial = new HistorialMedico[nuevo.capacidadHistorial];
    nuevo.capacidadCitas = 5;
    nuevo.cantidadCitas = 0;
    nuevo.citasAgendadas = new int[nuevo.capacidadCitas];
    hospital->cantidadPacientes++;
    return &nuevo;
 
}
// Actualizar paciente
bool actualizarPaciente(Hospital* hospital, int id) {
    Paciente* p = buscarPacientePorId(hospital, id);
    if (!p) return false;

    cin.ignore();
    cout << "Nombre actual: " << p->nombre << "\nNuevo nombre: "; cin.getline(p->nombre, 50);
    cout << "Apellido actual: " << p->apellido << "\nNuevo apellido: "; cin.getline(p->apellido, 50);
    cout << "Edad actual: " << p->edad << "\nNueva edad: "; cin >> p->edad;
    cout << "Sexo actual: " << p->sexo << "\nNuevo sexo (M/F): "; cin >> p->sexo;
    cin.ignore();
    cout << "Tipo de sangre actual: " << p->tipoSangre << "\nNuevo tipo de sangre: "; cin.getline(p->tipoSangre, 5);
    cout << "Teléfono actual: " << p->telefono << "\nNuevo teléfono: "; cin.getline(p->telefono, 15);
    cout << "Dirección actual: " << p->direccion << "\nNueva dirección: "; cin.getline(p->direccion, 100);
    cout << "Email actual: " << p->email << "\nNuevo email: "; cin.getline(p->email, 50);
    cout << "Alergias actuales: " << p->alergias << "\nNuevas alergias: "; cin.getline(p->alergias, 500);
    cout << "Observaciones actuales: " << p->observaciones << "\nNuevas observaciones: "; cin.getline(p->observaciones, 500);
    return true;
}
//Listar pacientes
void listarPacientes(Hospital* hospital) {
    cout << "\nListado de Pacientes\n";
    cout << left << setw(5) << "ID"
         << setw(15) << "Nombre"
         << setw(15) << "Apellido"
         << setw(15) << "Cédula"
         << setw(6) << "Edad"
         << setw(10) << "Consultas" << "\n";

    cout << string(66, '-') << "\n"; // Línea divisoria

    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        Paciente& p = hospital->pacientes[i];
        cout << left << setw(5) << p.id
             << setw(15) << p.nombre
             << setw(15) << p.apellido
             << setw(15) << p.cedula
             << setw(6) << p.edad
             << setw(10) << p.cantidadConsultas << "\n";
    }
}
bool eliminarPaciente(Hospital* h, int id) {
    for (int i = 0; i < h->cantidadPacientes; i++) {
        if (h->pacientes[i].id == id) {
            delete[] h->pacientes[i].historial;

            // Eliminar citas
            for (int j = 0; j < h->cantidadCitas; j++) {
                if (h->citas[j].idPaciente == id) {
                    h->citas[j].idPaciente = -1;
                    strcpy(h->citas[j].estado, "Cancelada");
                }
            }

            // Remover de doctores
            for (int d = 0; d < h->cantidadDoctores; d++) {
                Doctor& doc = h->doctores[d];
                for (int p = 0; p < doc.cantidadPacientes; p++) {
                    if (doc.pacientesAsignados[p] == id) {
                        for (int k = p; k < doc.cantidadPacientes - 1; k++) {
                            doc.pacientesAsignados[k] = doc.pacientesAsignados[k + 1];
                        }
                        doc.cantidadPacientes--;
                        break;
                    }
                }
            }

            // Compactar arreglo
            for (int k = i; k < h->cantidadPacientes - 1; k++) {
                h->pacientes[k] = h->pacientes[k + 1];
            }
            h->cantidadPacientes--;
            return true;
        }
    }
    return false;
}
//HISTORIAL MEDICO
bool agregarHistorialMedico(Paciente* paciente, const char* fecha, const char* hora,
                            const char* diagnostico, const char* tratamiento,
                            const char* medicamentos, int idDoctor, float costo) {
 
    if (!paciente) return false;

    // Verificar si hay que duplicar el arreglo
    if (paciente->cantidadHistorial >= paciente->capacidadHistorial) {
        int nuevaCapacidad = paciente->capacidadHistorial * 2;
        HistorialMedico* nuevoHistorial = new HistorialMedico[nuevaCapacidad];

        // Copiar datos existentes
        for (int i = 0; i < paciente->cantidadHistorial; i++) {
            nuevoHistorial[i] = paciente->historial[i];
        }

        // Liberar memoria anterior
        delete[] paciente->historial;
        paciente->historial = nuevoHistorial;
        paciente->capacidadHistorial = nuevaCapacidad;
    }

    // Agregar nueva entrada
    HistorialMedico& h = paciente->historial[paciente->cantidadHistorial];
    h.idConsulta = paciente->cantidadHistorial + 1;

    strncpy(h.fecha, fecha, 10); h.fecha[10] = '\0';
    strncpy(h.hora, hora, 5); h.hora[5] = '\0';
    strncpy(h.diagnostico, diagnostico, 199); h.diagnostico[199] = '\0';
    strncpy(h.tratamiento, tratamiento, 199); h.tratamiento[199] = '\0';
    strncpy(h.medicamentos, medicamentos, 149); h.medicamentos[149] = '\0';

    h.idDoctor = idDoctor;
    h.costoConsulta = costo;

    paciente->cantidadHistorial++;
    paciente->cantidadConsultas++; // opcional

    return true;
}

void mostrarHistorialMedico(Paciente* paciente) {
    if (paciente->cantidadHistorial == 0) {
        cout << "Este paciente no tiene historial médico registrado.\n";
        return;
    }

    cout << "\nHistorial Médico del Paciente:\n";
    for (int i = 0; i < paciente->cantidadHistorial; i++) {
        HistorialMedico& h = paciente->historial[i];
        cout << "\nConsulta #" << h.idConsulta << "\n";
        cout << "Fecha: " << h.fecha << "   Hora: " << h.hora << "\n";
        cout << "Diagnóstico: " << h.diagnostico << "\n";
        cout << "Tratamiento: " << h.tratamiento << "\n";
        cout << "Medicamentos: " << h.medicamentos << "\n";
        cout << "ID Doctor: " << h.idDoctor << "\n";
        cout << "Costo: $" << h.costoConsulta << "\n";
    }
}
//FUNCIONES DOCTOR
Doctor* crearDoctor(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula,
                    const char* especialidad, int experiencia, float costo,
                    const char* horario, const char* telefono, const char* email) {
    // Verificar si hay espacio suficiente
    if (hospital->cantidadDoctores >= hospital->capacidadDoctores) {
        int nuevaCapacidad = hospital->capacidadDoctores * 2;
        Doctor* nuevoArray = new Doctor[nuevaCapacidad];

        for (int i = 0; i < hospital->cantidadDoctores; i++) {
            nuevoArray[i] = hospital->doctores[i];
        }

        delete[] hospital->doctores;
        hospital->doctores = nuevoArray;
        hospital->capacidadDoctores = nuevaCapacidad;
    }

    // Crear nuevo doctor
    Doctor& d = hospital->doctores[hospital->cantidadDoctores];
    d.id = hospital->siguienteIdDoctor++;

    strncpy(d.nombre, nombre, 49); d.nombre[49] = '\0';
    strncpy(d.apellido, apellido, 49); d.apellido[49] = '\0';
    strncpy(d.cedula, cedula, 19); d.cedula[19] = '\0';
    strncpy(d.especialidad, especialidad, 49); d.especialidad[49] = '\0';
    d.aniosExperiencia = experiencia;
    d.costoConsulta = costo;
    strncpy(d.horarioAtencion, horario, 49); d.horarioAtencion[49] = '\0';
    strncpy(d.telefono, telefono, 14); d.telefono[14] = '\0';
    strncpy(d.email, email, 49); d.email[49] = '\0';
    d.disponible = true;
// Inicializar arreglos dinámicos
    d.capacidadPacientes = 5;
    d.cantidadPacientes = 0;
    d.pacientesAsignados = new int[d.capacidadPacientes];

    d.capacidadCitas = 5;
    d.cantidadCitas = 0;
    d.citasAgendadas = new int[d.capacidadCitas];

    hospital->cantidadDoctores++;
    return &d;
}

//Buscar doctor por id
Doctor* buscarDoctorPorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].id == id) return &hospital->doctores[i];
    }
    return nullptr;
}
//buscar doctores por especialidad
void buscarDoctoresPorEspecialidad(Hospital* hospital, const char* especialidad) {
    cout << "\nDoctores con especialidad en " << especialidad << ":\n";
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        Doctor& d = hospital->doctores[i];
        if (strcmp(d.especialidad, especialidad) == 0) {
            cout << "ID: " << d.id << " - " << d.nombre << " " << d.apellido << "\n";
        }
    }
}
//Asignar Paciente a doctor
bool asignarPacienteADoctor(Doctor* doctor, int idPaciente) {
    if (doctor->cantidadPacientes >= doctor->capacidadPacientes) {
        int nuevaCapacidad = doctor->capacidadPacientes * 2;
        int* nuevoArray = new int[nuevaCapacidad];
        for (int i = 0; i < doctor->cantidadPacientes; i++) {
            nuevoArray[i] = doctor->pacientesAsignados[i];
        }
        delete[] doctor->pacientesAsignados;
        doctor->pacientesAsignados = nuevoArray;
        doctor->capacidadPacientes = nuevaCapacidad;
    }

    doctor->pacientesAsignados[doctor->cantidadPacientes++] = idPaciente;
    return true;
}
//ver paciente de doctor
void verPacientesDeDoctor(Hospital* hospital, Doctor* doctor) {
    cout << "\nPacientes asignados al Dr. " << doctor->nombre << " " << doctor->apellido << ":\n";
    for (int i = 0; i < doctor->cantidadPacientes; i++) {
        int idPaciente = doctor->pacientesAsignados[i];
        Paciente* p = buscarPacientePorId(hospital, idPaciente);
        if (p) {
            cout << "ID: " << p->id << " - " << p->nombre << " " << p->apellido << "\n";
        }
    }
}
//ver listado de doctores
void listarDoctores(Hospital* hospital) {
    cout << "\nListado de Doctores:\n";
    cout << left << setw(5) << "ID"
         << setw(20) << "Nombre"
         << setw(20) << "Apellido"
         << setw(20) << "Especialidad"
         << setw(15) << "Teléfono" << "\n";

    cout << string(80, '-') << "\n";

    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        Doctor& d = hospital->doctores[i];
        cout << left << setw(5) << d.id
             << setw(20) << d.nombre
             << setw(20) << d.apellido
             << setw(20) << d.especialidad
             << setw(15) << d.telefono << "\n";
    }
}
//eliminar doctor
bool eliminarDoctor(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].id == id) {
            delete[] hospital->doctores[i].pacientesAsignados;
            delete[] hospital->doctores[i].citasAgendadas;

            for (int j = i; j < hospital->cantidadDoctores - 1; j++) {
                hospital->doctores[j] = hospital->doctores[j + 1];
            }
            hospital->cantidadDoctores--;
            return true;
        }
    }
    return false;
}
//