#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
//revisar bien tipos de datos para q en cedula no me acepte letras y en numero tlf y demas variables
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
 

Paciente* crearPaciente(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula, nt edad, char sexo,const char* tipoSangre, const char* telefono, const char* direccion, onst char* email, const char* alergias, const char* observaciones){
	//Para no registrar una cedula ya existente
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strcmp(hospital->pacientes[i].cedula, cedula) == 0) {
            cout << "Error: Cédula ya registrada.\n";
            return nullptr;
        }
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

    cout << string(66, '-') << "\n";

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
//Al ejecutar en vez de que el numero de id me sirva para un nuevo user, me salta al siguiente id, borro id 2 creo uno nuevo y en vez de guardar en 2, se guarda en id 3 
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
    paciente->cantidadConsultas++; 

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
//FUNCIONES CITAS
bool agendarCita(Hospital* hospital, int idPaciente, int idDoctor, const char* fecha, const char* hora, const char* motivo) {
    if (hospital->cantidadCitas >= hospital->capacidadCitas) {
        int nuevaCapacidad = hospital->capacidadCitas * 2;
        Cita* nuevoArray = new Cita[nuevaCapacidad];
        for (int i = 0; i < hospital->cantidadCitas; i++) {
            nuevoArray[i] = hospital->citas[i];
        }
        delete[] hospital->citas;
        hospital->citas = nuevoArray;
        hospital->capacidadCitas = nuevaCapacidad;
    }

    Cita& c = hospital->citas[hospital->cantidadCitas];
    c.id = hospital->siguienteIdCita++;
    c.idPaciente = idPaciente;
    c.idDoctor = idDoctor;
    strncpy(c.fecha, fecha, 10); c.fecha[10] = '\0';
    strncpy(c.hora, hora, 5); c.hora[5] = '\0';
    strncpy(c.motivo, motivo, 149); c.motivo[149] = '\0';
    strcpy(c.estado, "Pendiente");
    strcpy(c.observaciones, "");
    c.atendida = false;

    hospital->cantidadCitas++;
    return true;
}
//Cancelar cita
bool cancelarCita(Hospital* hospital, int idCita) {
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].id == idCita && !hospital->citas[i].atendida) {
            strcpy(hospital->citas[i].estado, "Cancelada");
            hospital->citas[i].atendida = false;
            return true;
        }
    }
    return false;
}

void verCitasDePaciente(Hospital* hospital, int idPaciente) {
    cout << "\nCitas del paciente:\n";
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idPaciente == idPaciente) {
            Cita& c = hospital->citas[i];
            cout << "ID: " << c.id << " | Fecha: " << c.fecha << " " << c.hora
                 << " | Motivo: " << c.motivo << " | Estado: " << c.estado << "\n";
        }
    }
}
void verCitasDeDoctor(Hospital* hospital, int idDoctor) {
    cout << "\nCitas del doctor:\n";
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == idDoctor) {
            Cita& c = hospital->citas[i];
            cout << "ID: " << c.id << " | Fecha: " << c.fecha << " " << c.hora
                 << " | Motivo: " << c.motivo << " | Estado: " << c.estado << "\n";
        }
    }
}
void verCitasPorFecha(Hospital* hospital, const char* fecha) {
    cout << "\nCitas para la fecha " << fecha << ":\n";
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].fecha, fecha) == 0) {
            Cita& c = hospital->citas[i];
            cout << "ID: " << c.id << " | Hora: " << c.hora
                 << " | Motivo: " << c.motivo << " | Estado: " << c.estado << "\n";
        }
    }
}
void verCitasPendientes(Hospital* hospital) {
    cout << "\nCitas pendientes:\n";
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].estado, "Pendiente") == 0) {
            Cita& c = hospital->citas[i];
            cout << "ID: " << c.id << " | Fecha: " << c.fecha << " " << c.hora
                 << " | Motivo: " << c.motivo << "\n";
        }
    }
} //AQUIIIII
bool atenderCita(Hospital* hospital, int idCita, const char* observaciones) {
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita& c = hospital->citas[i];

        if (c.id == idCita && strcmp(c.estado, "Pendiente") == 0) {
            // Marcar como atendida la ciat
            strcpy(c.estado, "Atendida");
            strncpy(c.observaciones, observaciones, 199);
            c.observaciones[199] = '\0';
            c.atendida = true;

            // Buscar paciente y doctor
            Paciente* p = buscarPacientePorId(hospital, c.idPaciente);
            Doctor* d = buscarDoctorPorId(hospital, c.idDoctor);

            if (p && d) {
                agregarHistorialMedico(p, c.fecha, c.hora, c.motivo, "Tratamiento aplicado", "Medicamentos recetados", d->id, d->costoConsulta);
            }

            return true;
        }
    }

    return false;
}




// Limpieza de memoria dinamica
void destruirHospital(Hospital* hospital) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        delete[] hospital->pacientes[i].historial;
        delete[] hospital->pacientes[i].citasAgendadas;
   

       
    }
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
    delete[] hospital->doctores[i].pacientesAsignados;
    delete[] hospital->doctores[i].citasAgendadas;
}
delete[] hospital->doctores;


    delete[] hospital->pacientes;
    delete[] hospital->doctores;
    delete hospital;
}

// Menú principal
int main() {
    Hospital* hospital = inicializarHospital("Hospital Universitario", "Av. Guajira", "+58 261752315");
    int opcion = 0;

    while (opcion != 4) {
        cout << "\n--- MENÚ PRINCIPAL ---\n";
        cout << "1. Gestión de Pacientes\n";
        cout << "2. Gestión de Doctores \n";
        cout << "3. Gestión de Citas \n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int subopcion = -1;
                while (subopcion != 0) {
                    cout << "\n--- Gestión de Pacientes ---\n";
                    cout << "1. Registrar nuevo paciente\n";
                    cout << "2. Buscar paciente por ID\n";
                    cout << "3. Actualizar datos del paciente\n";
                    cout << "4. Listar todos los pacientes\n";
                    cout << "5. Eliminar paciente\n";
                    cout << "6. Buscar paciente por cédula\n";
                    cout << "7. Agregar historial médico\n";
                    cout << "8. Ver historial médico\n";
                    cout << "9. Buscar paciente por nombre\n";

                    cout << "0. Volver al menú principal\n";
                    cout << "Seleccione una opción: ";
                    cin >> subopcion;

                    switch (subopcion) {
                        case 1: {
                            char nombre[50], apellido[50], cedula[20];int edad;char sexo;char tipoSangre[5], telefono[15], direccion[100], email[50];char alergias[500], observaciones[500];
                            cin.ignore();
                            cout << "Nombre: "; cin.getline(nombre, 50);
                            cout << "Apellido: "; cin.getline(apellido, 50);
                            cout << "Cédula: "; cin.getline(cedula, 20);
                            if (cedulaExiste(hospital, cedula)) {
                            cout << "Ya existe un paciente registrado con esa cédula.\n";
                            break;                             }
                            cout << "Edad: "; cin >> edad;
                            cout << "Sexo (M/F): "; cin >> sexo;
                            cin.ignore();
                            cout<<"Alergias: " ;cin.getline(alergias, 500);
                            cout<<"Tipo de Sangre: " ;cin.getline(tipoSangre, 5);
                            cout<<"Telefono: " ;cin.getline(telefono, 15);
                            cout<<"Direccion: " ;cin.getline(direccion, 100);
                            cout<<"Email: " ;cin.getline(email, 50);
                            cout<<"observaciones: " ;cin.getline(observaciones, 500);
                            cin.ignore();
                            Paciente* nuevo = crearPaciente(hospital, nombre, apellido, cedula, edad, sexo, tipoSangre, telefono, direccion, email, alergias, observaciones);
                            if (nuevo) {
                            cout << "Paciente registrado con ID: " << nuevo->id << "\n";
                            }
                              break;
                            }

                        case 2: {
                        int id;
                        cout << "Ingrese el ID del paciente: ";
                        cin >> id;
                        Paciente* p = buscarPacientePorId(hospital, id);
                        if (p) {
                            cout << "\nPaciente encontrado:\n";
                             cout << "Nombre: " << p->nombre << " " << p->apellido << "\n";
                             cout << "Cédula: " << p->cedula << "\n";
                             cout << "Edad: " << p->edad << "\n";
                             cout << "Sexo: " << p->sexo << "\n";
                             cout << "Tipo de sangre: " << p->tipoSangre << "\n";
                             cout << "Teléfono: " << p->telefono << "\n";
                             cout << "Email: " << p->email << "\n";
                             cout << "Consultas registradas: " << p->cantidadConsultas << "\n";
                            } else {
                                cout << "Paciente no encontrado.\n";
                            }
                            break;
                        }
                        case 3: {
                            int id;
                            cout << "Ingrese el ID del paciente a actualizar: ";
                            cin >> id;
                            if (actualizarPaciente(hospital, id)) {
                                cout << "Datos actualizados correctamente.\n";
                            } else {
                                cout << "No se pudo actualizar el paciente.\n";
                            }
                            break;
                        }
                        case 4:
                            listarPacientes(hospital);
                            break;

                        case 5: {
                            int id;
                            cout << "Ingrese el ID del paciente a eliminar: ";
                            cin >> id;
                            if (eliminarPaciente(hospital, id)) {
                                cout << "Paciente eliminado correctamente.\n";
                            } else {
                                cout << "No se pudo eliminar el paciente.\n";
                            }
                            break;
                        }
                        case 6: {
                        char cedulaBuscada[20];
                        cin.ignore();
                        cout << "Ingrese la cédula del paciente: ";
                        cin.getline(cedulaBuscada, 20);

                        Paciente* p = buscarPacientePorCedula(hospital, cedulaBuscada);
                        if (p) {
                            cout << "\nPaciente encontrado:\n";
                            cout << "ID: " << p->id << "\n";
                            cout << "Nombre: " << p->nombre << " " << p->apellido << "\n";
                            cout << "Cédula: " << p->cedula << "\n";
                            cout << "Edad: " << p->edad << "\n";
                            cout << "Sexo: " << p->sexo << "\n";
                            cout << "Tipo de sangre: " << p->tipoSangre << "\n";
                            cout << "Teléfono: " << p->telefono << "\n";
                            cout << "Dirección: " << p->direccion << "\n";
                            cout << "Email: " << p->email << "\n";
                            cout << "Alergias: " << p->alergias << "\n";
                            cout << "Observaciones: " << p->observaciones << "\n";
                            cout << "Consultas registradas: " << p->cantidadConsultas << "\n";
                        } else {
                            cout << "Paciente no encontrado.\n";
                        }
                        break;
                    }
                        case 7: {

                            int id;
                            cout << "\nIngrese el ID del paciente: ";
                            cin >> id;
                            Paciente* p = buscarPacientePorId(hospital, id);
                            if (!p) {
                                cout << "Paciente no encontrado.\n";
                                break;
                            }

                            // Variables de entrada
                            char fecha[11], hora[6], diagnostico[200], tratamiento[200], medicamentos[150];
                            int idDoctor;
                            float costo;

                            cin.ignore(); 

                            cout << "\n--- Registro de Historial Médico ---\n";

                            cout << "Fecha (YYYY-MM-DD): ";
                            cin.getline(fecha, 11);
                            cout << "? Fecha ingresada: " << fecha << "\n";

                            cout << "Hora (HH:MM): ";
                            cin.getline(hora, 6);
                            cout << "? Hora ingresada: " << hora << "\n";

                            cout << "Diagnóstico (máx 199 caracteres): ";
                            cin.getline(diagnostico, 199);
                            cout << "? Diagnóstico ingresado: " << diagnostico << "\n";

                            cout << "Tratamiento (máx 199 caracteres): ";
                            cin.getline(tratamiento, 199);
                            cout << "? Tratamiento ingresado: " << tratamiento << "\n";

                            cout << "Medicamentos recetados (máx 149 caracteres): ";
                            cin.getline(medicamentos, 149);
                            cout << "? Medicamentos ingresados: " << medicamentos << "\n";

                            cout << "ID del doctor que atendió: ";
                            cin >> idDoctor;
                            cout << "? ID doctor: " << idDoctor << "\n";

                            cout << "Costo de la consulta: ";
                            cin >> costo;
                            cout << "? Costo ingresado: $" << costo << "\n";

                            
                            cout << "\nGuardando historial médico...\n";

                            bool exito = agregarHistorialMedico(p, fecha, hora, diagnostico, tratamiento, medicamentos, idDoctor, costo);
                            if (exito) {
                                cout << "? Historial médico agregado correctamente.\n";
                            } else {
                                cout << "? No se pudo agregar el historial (posible error de memoria).\n";
                            }

                            break;
                        }

                        case 8: {
                            int id;
                            cout << "Ingrese el ID del paciente: ";
                            cin >> id;
                            Paciente* p = buscarPacientePorId(hospital, id);
                            if (!p) {
                                cout << "Paciente no encontrado.\n";
                                break;
                            }

                            mostrarHistorialMedico(p);
                            break;
                        }
                        case 9: {
                            char nombreBuscado[50];
                            cin.ignore();
                            cout << "Ingrese el nombre o parte del nombre a buscar: ";
                            cin.getline(nombreBuscado, 50);
                            buscarPacientesPorNombre(hospital, nombreBuscado);
                            break;
                        }




                        case 0:
                            cout << "Volviendo al menú principal...\n";
                            break;

                        default:
                            cout << "Opción inválida. Intente nuevamente.\n";
                            
                    }
                }
                break;
        }

           case 2: {
    int opcionDoctor = -1;
    while (opcionDoctor != 8) {
        cout << "\n--- Menú de Doctores ---\n";
        cout << "1. Registrar nuevo doctor\n";
        cout << "2. Buscar doctor por ID\n";
        cout << "3. Buscar doctores por especialidad\n";
        cout << "4. Asignar paciente a doctor\n";
        cout << "5. Ver pacientes asignados a doctor\n";
        cout << "6. Listar todos los doctores\n";
        cout << "7. Eliminar doctor\n";
        cout << "8. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcionDoctor;

        switch (opcionDoctor) {
            case 1: {
                char nombre[50], apellido[50], cedula[20], especialidad[50], horario[50], telefono[15], email[50];
                int experiencia;
                float costo;

                cin.ignore();
                cout << "Nombre: "; cin.getline(nombre, 50);
                cout << "Apellido: "; cin.getline(apellido, 50);
                cout << "Cédula: "; cin.getline(cedula, 20);
                cout << "Especialidad: "; cin.getline(especialidad, 50);
                cout << "Años de experiencia: "; cin >> experiencia;
                cout << "Costo de consulta: "; cin >> costo;
                cin.ignore();
                cout << "Horario de atención: "; cin.getline(horario, 50);
                cout << "Teléfono: "; cin.getline(telefono, 15);
                cout << "Email: "; cin.getline(email, 50);

                Doctor* d = crearDoctor(hospital, nombre, apellido, cedula, especialidad, experiencia, costo, horario, telefono, email);
                if (d) {
                    cout << "? Doctor registrado con ID: " << d->id << "\n";
                } else {
                    cout << "? No se pudo registrar el doctor.\n";
                }
                break;
            }

            case 2: {
                //falta

            case 3: // falta

            case 4: {
                int idDoctor, idPaciente;
                cout << "ID del doctor: "; cin >> idDoctor;
                cout << "ID del paciente a asignar: "; cin >> idPaciente;

                Doctor* d = buscarDoctorPorId(hospital, idDoctor);
                Paciente* p = buscarPacientePorId(hospital, idPaciente);

                if (!d || !p) {
                    cout << "? Doctor o paciente no encontrado.\n";
                    break;
                }

                if (asignarPacienteADoctor(d, idPaciente)) {
                    cout << "? Paciente asignado correctamente.\n";
                } else {
                    cout << "? No se pudo asignar el paciente.\n";
                }
                break;
            }

            case 5: {
                //ver como hacer esta partecitaaaa

            case 6: {
                listarDoctores(hospital);
                break;
            }

            case 7: {
                int id;
                //pendiente
            }

            case 8:
                cout << "Volviendo al menú principal...\n";
                break;

            default:
                cout << "? Opción inválida. Intente nuevamente.\n";
        }
    }
    break;
}

case 3: {
    int opcionCita = 0;
    do {
        cout << "\n--- Menú de Citas ---\n";
        cout << "1. Agendar nueva cita\n";
        cout << "2. Cancelar cita\n";
        cout << "3. Atender cita\n";
        cout << "4. Ver citas de un paciente\n";
        cout << "5. Ver citas de un doctor\n";
        cout << "6. Ver citas de una fecha\n";
        cout << "7. Ver citas pendientes\n";
        cout << "8. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcionCita;
        cin.ignore();

        switch (opcionCita) {
            case 1: {
                int idPaciente, idDoctor;
                char fecha[11], hora[6], motivo[150];
                cout << "ID del paciente: "; cin >> idPaciente;
                cout << "ID del doctor: "; cin >> idDoctor;
                cin.ignore();
                cout << "Fecha (YYYY-MM-DD): "; cin.getline(fecha, 11);
                cout << "Hora (HH:MM): "; cin.getline(hora, 6);
                cout << "Motivo: "; cin.getline(motivo, 150);

                if (horarioOcupado(hospital, idDoctor, fecha, hora)) {
                    cout << "? El doctor ya tiene una cita pendiente en ese horario.\n";
                } else {
                    if (agendarCita(hospital, idPaciente, idDoctor, fecha, hora, motivo)) {
                        int nuevoId = hospital->siguienteIdCita - 1;
                        cout << "? Cita agendada correctamente. ID: " << nuevoId << "\n";
                    } else {
                        cout << "? No se pudo agendar la cita.\n";
                    }
                }
                break;
            }

            case 2: {
                //pendiente :(
            }
            //GRAN PROBLEMAAAA 911 AYUSAAAA
            case 3: {
                int idCita;
                char observaciones[200];
                cout << "ID de la cita a atender: ";
                cin >> idCita;
                cin.ignore();
                cout << "Observaciones: ";
                cin.getline(observaciones, 200);

                if (atenderCita(hospital, idCita, observaciones))
                    cout << "? Cita atendida.\n";
                else
                    cout << "? No se pudo atender la cita.\n";
                break;
            }

            case 4: {
                int idPaciente;
                cout << "ID del paciente: ";
                cin >> idPaciente;
                verCitasDePaciente(hospital, idPaciente);
                break;
            }

            case 5: {
                int idDoctor;
                cout << "ID del doctor: ";
                cin >> idDoctor;
                verCitasDeDoctor(hospital, idDoctor);
                break;
            }

            case 6: {
               //pendiente
            }

            case 7: {
                verCitasPendientes(hospital);
                break;
            }

            case 8:
                cout << "Volviendo al menú principal...\n";
                break;

            default:
                cout << "? Opción inválida. Intente nuevamente.\n";
        }
    } while (opcionCita != 8);
    break;
}



case 4:
   //pendientes

}


