#include<iostream>
using namespace std;

void imprimirOpciones(){
 
 cout<<"SISTEMA DE GESTION HOSPITALARIA" <<endl;
 cout<<"1.Gestion de pacientes"<<endl;
 cout<<"2.Gestion de doctores"<<endl;
 cout<<"3.Gestion de citas"<<endl;
 cout<<"4. Salir"<< endl;
 cout<<"Ingrese la opcion que desee:"<<endl;
};

void CrearListaDePaciente(int CantidadInicial){
 Paciente* pacientes= new Paciente [CantidadInicial];
 cout<<"Ingrese los datos de las personas"<<endl;
 for (int i=0; i<CantidadInicial; i++){
  cout<<"persona:"<<(i+1)<<endl;
  cout<<"Nombres:"<<endl;
  cin.ignore();
        getline(cin, pacientes[i].nombre);
  cout<<"Apellidos:"<<endl;
  cin.ignore();
        getline(cin, pacientes[i].apellido);
        cout << "  Edad: ";
        cin >> pacientes[i].edad;
        cout << " ID: ";
        cin >> pacientes[i].id;
        cout << " Cedula: ";
        cin >> pacientes[i].cedula;
        cout << " Sexo: ";
        cin >> pacientes[i].sexo;
        cout << " Tipo de sangre: ";
        cin >> pacientes[i].tipoSangre;
        cout << "  Edad: ";
        cin >> pacientes[i].edad;
 }}
int Redimensionar(CantidadInicial){
//Aqui Va lo del examen
}
void AniadirPaciente(){
 Redimensionar(cantidadActual + 1);
 cout<<"persona:"<<endl;
  cout<<"Nombres:"<<endl;
  cin.ignore();
        getline(cin, pacientes[cantidadActual + 1].nombre);
  cout<<"Apellidos:"<<endl;
  cin.ignore();
        getline(cin, pacientes[i].apellido);
        cout << "  Edad: ";
        cin >> pacientes[i].edad;
        cout << " ID: ";
        cin >> pacientes[i].id;
        cout << " Cedula: ";
        cin >> pacientes[i].cedula;
        cout << " Sexo: ";
        cin >> pacientes[i].sexo;
        cout << " Tipo de sangre: ";
        cin >> pacientes[i].tipoSangre;
        cout << "  Edad: ";
        cin >> pacientes[i].edad;
}

struct HistorialMedico {
    int idConsulta;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;
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
    
    Doctor* doctores;
    int cantidadDoctores;
    int capacidadDoctores;
    
    Cita* citas;
    int cantidadCitas;
    int capacidadCitas;
    
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;
};

int main(){
 int opcionpacientesw=0;
 int opciondoctorsw;
 int opcioncitasw;
 int opciongestion = 0;
 
 
 while(opciongestion != 4){
  
 imprimirOpciones();
 cin>> opciongestion;

switch (opciongestion){
 case 1:
 cout<<"Menu de pacientes"<<endl;
  cout<<"1.Registrar nuevo paciente"<<endl;
  cout<<"2.Buscar paciente por c�dula"<<endl;
  cout<<"3.Buscar paciente por nombre"<<endl;
  cout<<"4.Ver historial m�dico completo"<<endl;
  cout<<"5.Actualizar datos del paciente"<<endl;
  cout<<"6.Listar todos los pacientes"<<endl;
  cout<<"7.Eliminar paciente"<<endl;
  cout<<"0. volver al menu principal"<<endl;
  cout<<"Ingrese la opcion que desee:"<<endl;
  cin>>opcionpacientesw;
  
  switch (opcionpacientesw){
   while(opcionpacientesw != 0){
   case 1:
    int cantidad = 0;
    cout << "Con cuantos pacientes va a iniciar?"
    cin>>cantidad;
    CrearListaDePaciente(cantidad)
    cout<<"aqui se encuentra su menu de pacientes"<<endl;
   break;
   
   case 2:
    cout<<"Aqui se encuentra su paciente por cedula:"<<endl;
   break;
   
   case 3:
    cout<<"Aqui se encuentra su paciente por el nombre:"<<endl;
   break;
   
   case 4:
    cout<<"Aqui se encuentra el historial medico completo del paciente"<<endl;
   break;
   
   case 5:
    cout<<"ya se actualizaron los datos del paciete"<<endl;
   break;
   
   case 6:
       cout<<"Aqui esta la lista de todos los pacientes"<<endl;
   break;
   
   case 7:
    cout<<"Su paciente ha sido eliminado"<<endl;
   break;
   
   case 0:
    cout<<"Volviendo al menu principal"<<endl;
  }   
  } 
  
  break;
  
 case 2:
  cout<<"1.Registrar nuevo doctor"<<endl;
  cout<<"2.Buscar doctor por ID"<<endl;
  cout<<"3.Buscar doctores por especialidad"<<endl;
  cout<<"4.Asignar paciente a doctor"<<endl;
  cout<<"5.Ver pacientes asignados a doctores"<<endl;
  cout<<"6.Listar todos los doctores"<<endl;
  cout<<"7.Eliminar doctor"<<endl;
  cout<<"0.Volver al menu principal"<<endl;
  cin>>opciondoctorsw;
  
  switch (opciondoctorsw){
   case 1:
    cout<<"Se ha registrado un nuevo doctor"<<endl;
   break;
   
   case 2:
    cout<<"El doctor por ID es:"<<endl;
   break;
   
      case 3:
       cout<<"El doctor por la especialidad fue"<<endl;
      break;
      
      case 4:
       cout<<"El paciente asignado al doctor fue:"<<endl;
      break;
      
      case 5:
       cout<<"lista de pacinetes asignados a doctores es:"<<endl;
      break;
      
      case 6:
       cout<<"lista para todos los doctores"<<endl;
      break;
      
      case 7:
       cout<<"El doctor fue eliminado"<<endl;
      break;
      
      case 0:
       cout<<"volver al menu principal"<<endl;
      break;
  }
  
  break;
 
 case 3:
  cout<<"1.Agendar nueva cita"<<endl;
  cout<<"2.Cancelar cita"<<endl;
  cout<<"3.Atender cita"<<endl;
  cout<<"4. Ver citas de un paciente"<<endl;
  cout<<"5. Ver citas de un doctor"<<endl;
  cout<<"6. Ver citas de una fecha"<<endl;
  cout<<"7. Ver citas pendientes"<<endl;
  cout<<"0. Volver al menu principal"<<endl;
  cin>>opcioncitasw;
  
  switch (opcioncitasw){
   case 1:
       cout<<"La cita fue agendada"<<endl;
      break;
      
      case 2:
       cout<<"La cita fue cancelada"<<endl;
      break;
      
      case 3:
       cout<<"La cita por atender es"<<endl;
      break;
      
      case 4:
       cout<<"Las citas del paciente son"<<endl;
      break;
      
      case 5:
       cout<<"Las citas del doctor son"<<endl;
      break;
      
      case 6:
       cout<<"Las citas de la fecha son"<<endl;
      break;
      
      case 7:
       cout<<"Las citas pendientes son"<<endl;
      break;
      
      case 0:
       cout<<"Volver al menu principal"<<endl;
      break;
  }
  
  break;
  
 default: cout<<"Ingrese numeros del 1-4"<<endl;
} 
 
 return 0;
}
}
