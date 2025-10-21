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
