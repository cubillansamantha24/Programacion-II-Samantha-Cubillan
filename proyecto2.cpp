#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <locale.h>

using namespace std;

// === ESTRUCTURAS ===
struct ArchivoHeader {
    int cantidadRegistros;
    int proximoID;
    int registrosActivos;
    int version;
    int ultimoId;

};
struct Asignacion {
    int idDoctor;
    int idPaciente;
    time_t fechaAsignacion;
};


struct Hospital {
    char nombre[100] = "Hospital Central";
    char direccion[150] = "Av. Principal, Chiquinquirá";
    char telefono[15] = "0261-1234567";
    int siguienteIDPaciente = 1;
    int siguienteIDDoctor = 1;
    int siguienteIDCita = 1;
    int siguienteIDConsulta = 1;
    int totalPacientesRegistrados = 0;
    int totalDoctoresRegistrados = 0;
    int totalCitasAgendadas = 0;
    int totalConsultasRealizadas = 0;
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
    char alergias[500];
    char observaciones[500];
    bool activo;
    int cantidadConsultas;
    int primerConsultaID;
    int cantidadCitas;
    int citasIDs[20];
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;
};

struct Doctor {
    int id;
    char nombre[50];
    char apellido[50];
    char cedulaProfesional[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    bool disponible;
    int cantidadPacientes;
    int pacientesIDs[50];
    int cantidadCitas;
    int citasIDs[30];
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;
    
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
    int consultaID;
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;
};

struct HistorialMedico {
    int id;
    int idPaciente;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int doctorID;
    float costo;
    int siguienteConsultaID;
    bool eliminado;
    time_t fechaRegistro;
    time_t fechaCreacion;
    time_t fechaModificacion;
   

};
//VALIDACIONES
//funcion para validar la fecha en YYYY-MM-DD

bool validarFecha(const char* fecha){
    int ano, mes, dia;
    if(strlen(fecha)!=10){// strlen se utiliza para indicar si la cadena es mas corta o mas larga de 10 digitos no es valida
        return false;
    }
//Para verificar el formato con guiones
    if(fecha[4]!='-' || fecha[7]!='-') {// verfica que los guines esten en las posiciones correctas
        return false;
    }
//verificamos que el numero corresponda 
for(int i=0; i<10;i++) {
    if (i==4 || i==7 ) //saltos en el caracter 4 y 7
continue;//saltamos los guiones
    if (fecha[i] < '0' || fecha[i]>'9') {// verifica que solo se ingresen numeros
    return false;
      }
}

//extraemos año,mes y dia 

ano =    (fecha[0]-'0')* 1000 + //hago la resta porque los caracteres tienen valores numerico internos (ASCII), "2"-"0"= 50-48=2
         (fecha[1]-'0')* 100 +
         (fecha[2]-'0')* 10 +
         (fecha[3]-'0');
mes =    (fecha[5]-'0')* 10 + (fecha[6]-'0');
dia =    (fecha[8]-'0')* 10 + (fecha[9]- '0');


//validar rangos 

    if ( ano < 1900 || ano > 2100) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;

//verificar dias segun mes

if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    if (dia > 30) return false;
}
 else if (mes==2) {
    bool esBisiesto = (ano % 4 == 0 && ano % 100 != 0) || (ano% 400 == 0); // aplica la reggla de como saber si un ano es bisiesto
        if (esBisiesto) {
            if (dia > 29) return false;
        } else {
            if (dia > 28) return false;
        }
       
    }
    
      return true;
}

//funcion para validar la hora en formato HH:MM

bool validarHora(const char* hora) {
    if (strlen(hora) != 5) return false;{
    }
    if (hora[2] != ':') return false;{
    }
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue; // saltar el ':'
        if (hora[i] < '0' || hora[i] > '9') {return false;
    }
    }
    int HH = (hora[0] - '0') * 10 + (hora[1] - '0');
    int MM = (hora[3] - '0') * 10 + (hora[4] - '0');
    if (HH < 0 || HH > 23) return false;
    if (MM < 0 || MM > 59) return false;
    return true;
}

bool validarEmail(const char* email) {
    if (email == nullptr || strlen(email) == 0) return false;

    bool tieneArroba = false, tienePunto = false;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') tieneArroba = true;
        else if (email[i] == '.' && tieneArroba) tienePunto = true;
    }

    return tieneArroba && tienePunto;
}

bool horarioOcupado(int idDoctor, const char* fecha, const char* hora) {
    ifstream archivo("citas.bin", ios::binary);
    if (!archivo.is_open()) return false;

    ArchivoHeader header;//Tipo de dato ArchivoHeader que es la estructura que contiene datos del archivo como cantidad de registros y ultimo id
    archivo.read((char*)&header, sizeof(ArchivoHeader));//lee el encabezado desde el archivo, todas sus propiedades

    Cita c;//Estructura que representa una cita medica la c representa una cita
    for (int i = 0; i < header.cantidadRegistros; i++) {//itera la cantidad de citas que hay en mi archivo citas, utilizando header accediendo a su propiedad cantidad de registros para el archivo citas porque es el archivo que esta abierto
        archivo.read((char*)&c, sizeof(Cita));//va leyendo la cita de cada iteracion
        if (!c.atendida && strcmp(c.estado, "Pendiente") == 0 &&
            c.idDoctor == idDoctor &&
            strcmp(c.fecha, fecha) == 0 &&
            strcmp(c.hora, hora) == 0) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}
//Verificacion para saber si la cedua existe
bool cedulaExiste(const char* cedulaBuscada) {
    fstream archivo("pacientes.bin", ios::binary | ios::in);
    if (!archivo.is_open()) {
    cerr << "Error al abrir pacientes.bin\n";//cerr es como mi cout pero se utliza como una salidad de error estandar
    return false;
}
    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));//lee todas propiedades del header de pacientes.bin
    Paciente paciente;
    for (int i = 0; i < header.cantidadRegistros; i++) {//itera la cantidad de pacientes que hay en el archivo guiandose del header
    streampos posicion = sizeof(ArchivoHeader) + i * sizeof(Paciente);//sumo lo que ocupa el header a la multiplicacion del numero de iteracion en el que estoy por el tamanio de pacientes para poder leer el paciente que corresponde a esa iteracion
    archivo.seekg(posicion);//mueve el puntero de lectura a la pocision calculada
    archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));//le el paciente de la posicion y lo guarda en la variable paciente
    if (!paciente.eliminado && strcmp(paciente.cedula, cedulaBuscada) == 0) {
    archivo.close();
    return true;
    }
}
    archivo.close();
    return false;
}




//FIN DE VALIDACIONES

//VERIFICACIONES DE ARCHIVO
// === FUNCIONES DE ARCHIVO Y ACCESO ALEATORIO ===

bool inicializarArchivo(const char* nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) return false;

    ArchivoHeader header = {0, 1, 0, 1}; // inicializa todos los campos de mi estructura ArchivoHeader Registros 0, proximoid 1, registros activos 0 y  versión 1
    archivo.write((char*)&header, sizeof(header));
    archivo.close();
    return true;
}

bool verificarArchivo(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);//abro el archivo que desee en modo lectura 
    if (!archivo.is_open()) return false;

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(ArchivoHeader));//lee el header del archivo
    archivo.close();

    return header.version == 1;//compara la version iinicializada en 1 con 1, si coincide retorna, sino retorna false
}



ArchivoHeader leerHeader(const char* nombreArchivo) {//me devuele un dato de tipo ArchivoHeader
    ifstream archivo(nombreArchivo, ios::binary);
    ArchivoHeader header = {};//inicializa todos las propiedades del header en 0 
    if (!archivo.is_open()) return header;// retorno header pq por ahora todos sus campos son 0

    archivo.read((char*)&header, sizeof(ArchivoHeader));// si se abre el archivo leo el header
    archivo.close();
    return header;//retorna header pero ahora con los datos del header del archivo que lei 
}

bool actualizarHeader(const char* nombreArchivo, const ArchivoHeader& header) {
    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;

    archivo.seekp(0);//mueve el puntero de escritura al inicio del archivo
    archivo.write((char*)&header, sizeof(ArchivoHeader));//escribo el nuevo header 
    archivo.close();
    return true;
}

streampos calcularPosicion(int indice, size_t tamRegistro) {// size_t tamRegistro tipo entero sin signo (es decir, no puede ser negativo). siempre que use sizeof devuelve un size_t
    return sizeof(ArchivoHeader) + indice * tamRegistro;
}

int buscarIndicePorID(const char* nombreArchivo, int idBuscado, size_t tamRegistro) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) return -1;

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(ArchivoHeader));

    char* buffer = new char[tamRegistro];//crea un bufer dinamico para leer cada registro completo, reserva un espacio de tamanio para cualquier estructura
    for (int i = 0; i < header.cantidadRegistros; i++) {//recorre todos los registros del archivo
        archivo.read(buffer, tamRegistro);//lee el registro actual el de esa iteracion,en buffer se guarda la info
        int id;
        memcpy(&id, buffer, sizeof(int));//memcpy es una función de la biblioteca estándar de C++ que copia bloques de memoria de un lugar a otro, pasa los primeros 4 bytes del buffer (registro) al id
        bool eliminado;
        memcpy(&eliminado, buffer + tamRegistro - sizeof(bool) - sizeof(time_t)*2, sizeof(bool));//Calcula la posición del campo eliminado dentro del registro.
        if (id == idBuscado && !eliminado) {
            delete[] buffer;
            archivo.close();
            return i;
        }
    }
    delete[] buffer;
    archivo.close();
    return -1;
}

void mostrarHeader(const char* nombreArchivo) {
    ArchivoHeader header = leerHeader(nombreArchivo);
    cout << "\n--- Header de " << nombreArchivo << " ---\n";
    cout << "Cantidad de registros: " << header.cantidadRegistros << "\n";
    cout << "Próximo ID: " << header.proximoID << "\n";
    cout << "Registros activos: " << header.registrosActivos << "\n";
    cout << "Versión: " << header.version << "\n";
}

template<typename T>//template<typename T>: permite que la función trabaje con cualquier tipo de registro (Paciente, Doctor, Cita, etc.).
bool agregarRegistro(const char* nombreArchivo, T& nuevo) {
    ArchivoHeader header = leerHeader(nombreArchivo);

    nuevo.id = header.proximoID;     // ? Asigna el ID actual
    header.proximoID++;              // ? Aumenta para el siguiente

    nuevo.eliminado = false;
    nuevo.fechaCreacion = time(nullptr);
    nuevo.fechaModificacion = time(nullptr);

    ofstream archivo(nombreArchivo, ios::binary | ios::app);
    if (!archivo.is_open()) return false;

    archivo.write((char*)&nuevo, sizeof(T));
    archivo.close();

    header.cantidadRegistros++;
    header.registrosActivos++;

    return actualizarHeader(nombreArchivo, header); // ? Guarda el nuevo header
}

template<typename T>
bool actualizarRegistro(const char* nombreArchivo, const T& modificado) {
    int indice = buscarIndicePorID(nombreArchivo, modificado.id, sizeof(T));
    if (indice == -1) return false;

    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;

    archivo.seekp(calcularPosicion(indice, sizeof(T)));//mueve el puntero de escritura hasta la posicion del registro que quiero modificar
    archivo.write((char*)&modificado, sizeof(T));//escribe los datos modificados
    archivo.close();
    return true;
}

template<typename T>
bool eliminarRegistro(const char* nombreArchivo, int id) {
    int indice = buscarIndicePorID(nombreArchivo, id, sizeof(T));
    if (indice == -1) return false;

    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;

    archivo.seekg(calcularPosicion(indice, sizeof(T)));//muevo mi puntero de lectura a la posicion del registro
    T registro;//declaro la variable donde se va a guardar el registro que quiero eliminar
    archivo.read((char*)&registro, sizeof(T));//lo leo y ahi se guarda 

    registro.eliminado = true;
    registro.fechaModificacion = time(nullptr);

    archivo.seekp(calcularPosicion(indice, sizeof(T)));//muebo mi puntero de escritura a la posicion del registro que elimine
    archivo.write((char*)&registro, sizeof(T));//Escribe el registro modificado (con eliminado = true) sobre el anterior.
    archivo.close();

    ArchivoHeader header = leerHeader(nombreArchivo);
    header.registrosActivos--;//reduce el contador de registros activos
    return actualizarHeader(nombreArchivo, header);
}

template<typename T>
void listarRegistrosActivos(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo.\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(ArchivoHeader));
    T registro;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&registro, sizeof(T));
        if (!registro.eliminado) {
            cout << "ID: " << registro.id << " - Nombre: " << registro.nombre << "\n";
        }
    }
    archivo.close();
}
 
//PACIENTES

//Reiniciar el archivo de pacientes
void reiniciarArchivoPacientes() {
    ofstream archivo("pacientes.bin", ios::binary | ios::trunc);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear pacientes.bin\n";
        return;
    }

    ArchivoHeader header = {0, 1, 0, 1}; // Reinicia contador de ID
    archivo.write((char*)&header, sizeof(header));
    archivo.close();

    cout << "Archivo pacientes.bin reiniciado. Todos los registros fueron eliminados.\n";
}
//Agregar paciente
void registrarPaciente(const char* cedulaInicial){
Paciente p = {};
char cedula[20];
cin.ignore();
cout << "Nombre: "; cin.getline(p.nombre, 50);
cout << "Apellido: "; cin.getline(p.apellido, 50);
strncpy(p.cedula, cedulaInicial, 20);
cout << "Edad: "; cin >> p.edad;
cout << "Sexo (M/F): "; cin >> p.sexo;
cin.ignore();
cout << "Tipo de sangre: "; cin.getline(p.tipoSangre, 5);
cout << "Teléfono: "; cin.getline(p.telefono, 15);
cout << "Dirección: "; cin.getline(p.direccion, 100);
do {
        cout << "Email: ";
        cin.getline(p.email, 50);
        if (!validarEmail(p.email)) {
            cout << "? Email inválido. Debe contener '@' y al menos un '.' después.\n";
        }
    } while (!validarEmail(p.email));
cout << "Alergias: "; cin.getline(p.alergias, 500);
cout << "Observaciones: "; cin.getline(p.observaciones, 500);
p.activo = true;
p.cantidadConsultas = 0;
p.primerConsultaID = -1;
p.cantidadCitas = 0;
if (agregarRegistro("pacientes.bin", p)) {
cout << "Paciente registrado con ID: " << p.id << "\n";
} else {
cout << "Error al registrar paciente.\n";
}
}

Paciente leerPacientePorID(int id) {
int indice = buscarIndicePorID("pacientes.bin", id, sizeof(Paciente));
if (indice == -1) return {};
ifstream archivo("pacientes.bin",ios::binary);
archivo.seekg(calcularPosicion(indice, sizeof(Paciente)));//mueve el puntero de lectura hasta la posicion del paciente que le corresponde ese id
Paciente p;
archivo.read((char*)&p, sizeof(Paciente));
archivo.close();
return p;
}

//Buscar paciente por nombre
void buscarPacientesPorNombre(const char* fragmento) {
fstream archivo("pacientes.bin", ios::binary | ios::in);
if (!archivo.is_open()) {
cerr << "Error al abrir pacientes.bin\n";
return;
}
ArchivoHeader header;
archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
Paciente paciente;
bool encontrado = false;
cout << "\nPacientes que coinciden con \"" << fragmento << "\":\n";
for (int i = 0; i < header.cantidadRegistros; i++) {
streampos posicion = sizeof(ArchivoHeader) + i * sizeof(Paciente);
archivo.seekg(posicion);//leo la posicion del paciente de esa iteracion
archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
if (!paciente.eliminado && strstr(paciente.nombre, fragmento) != nullptr) {
cout << "ID: " << paciente.id << " | " << paciente.nombre << " " << paciente.apellido
<< "\n";
encontrado = true;
}
}
if (!encontrado) {
cout << "No se encontraron pacientes con ese fragmento en el nombre.\n";
}
archivo.close();
}

//0Buscar paciente por id
void buscarPacientePorID() {
int id;
cout << "Ingrese ID del paciente: ";
cin >> id;
Paciente p = leerPacientePorID(id);// lo iguala a la funcion para que sin iterar p sea automaticamente l paciente al cual le pertenece el id
if (p.id == 0 || p.eliminado) {
cout << "Paciente no encontrado.\n";
return;
}
cout << "\nNombre: " << p.nombre << " " << p.apellido << "\n";
cout <<"Apellido: " <<p.apellido << "\n";
cout << "Cédula: " << p.cedula << "\n";
cout << "Edad: " << p.edad << "\n";
cout << "Sexo: " << p.sexo << "\n";
cout << "Tipo de sangre: " << p.tipoSangre << "\n";
cout << "Teléfono: " << p.telefono << "\n";
cout << "Direccion: " << p.direccion<< "\n";
cout << "Email: " << p.email << "\n";
cout <<"Alergias: " <<p.alergias << "\n";
cout <<"Observaciones: " <<p.observaciones << "\n";
}

//Buscar paciente por cedula
Paciente buscarPacientePorCedula(const char* cedulaBuscada) {
fstream archivo("pacientes.bin", ios::binary | ios::in);
Paciente paciente = {};
if (!archivo.is_open()) {
cerr << "Error al abrir pacientes.bin\n";
paciente.id = -1;//senal de error 
return paciente;
}
ArchivoHeader header;
archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
for (int i = 0; i < header.cantidadRegistros; i++) {
streampos posicion = sizeof(ArchivoHeader) + i * sizeof(Paciente);
archivo.seekg(posicion);//lectura
archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
if (!paciente.eliminado && strcmp(paciente.cedula, cedulaBuscada) == 0) {
archivo.close();
return paciente;
}
}
archivo.close();
paciente.id = -1; // No encontrado
return paciente;
}

void actualizarPacienteInteractivo() {
int id;
cout << "ID del paciente a actualizar: ";
cin >> id;
Paciente p = leerPacientePorID(id);
if (p.id == 0 || p.eliminado) {
cout << "Paciente no encontrado.\n";
return;
}
cin.ignore();
cout << "Nuevo nombre (" << p.nombre << "): "; cin.getline(p.nombre, 50);
cout << "Nuevo apellido (" << p.apellido << "): "; cin.getline(p.apellido, 50);
cout << "Nueva cedula (" << p.cedula << "): "; cin.getline(p.cedula, 20);
cout << "Nueva edad (" << p.edad <<"): "; cin>> p.edad;
cout << "Nuevo sexo (" << p.sexo <<"): "; cin>> p.sexo;
cin.ignore();
cout << "Nuevo tipo de sangre (" << p.tipoSangre << "): "; cin.getline(p.tipoSangre, 5);
cout << "Nuevo teléfono (" << p.telefono << "): "; cin.getline(p.telefono, 15);
cout << "Nueva direccion (" << p.direccion << "): "; cin.getline(p.direccion, 100);
cout << "Nueva alergia (" << p.alergias << "): "; cin.getline(p.alergias, 500);
do {
        cout << "Nuevo email (" << p.email << "): ";
        cin.getline(p.email, 50);
        if (!validarEmail(p.email)) {
            cout << "? Email inválido. Debe contener '@' y al menos un '.' después.\n";
        }
    } while (!validarEmail(p.email));
cout << "Nuevas observaciones (" << p.observaciones << "): ";
cin.getline(p.observaciones, 500);
p.fechaModificacion = time(nullptr);
if (actualizarRegistro("pacientes.bin", p)) {
cout << "Paciente actualizado.\n";
} else {
cout << "Error al actualizar.\n";
}
}



void reordenarPacientes() {
   ifstream archivoOriginal("pacientes.bin", ios::binary);
    if (!archivoOriginal.is_open()) {
        cerr << "No se pudo abrir pacientes.bin\n";
        return;
    }

    ArchivoHeader headerOriginal;
    archivoOriginal.read((char*)&headerOriginal, sizeof(headerOriginal));

    ofstream archivoTemporal("temp_pacientes.bin", ios::binary | ios::trunc);//creo un archivo temporal
    if (!archivoTemporal.is_open()) {
        cerr << "No se pudo crear archivo temporal.\n";
        archivoOriginal.close();// si no se pudo crear un archivo temporal me cierra el archivo original
        return;
    }

    ArchivoHeader nuevoHeader = {};
    nuevoHeader.version = headerOriginal.version;//iguala la version del nuevo header a la version del header original 

    // Reservar espacio para el header
    archivoTemporal.write((char*)&nuevoHeader, sizeof(nuevoHeader));

    Paciente p;
    int nuevoID = 1;//inicializa los nuevos id

    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {//itera por la cantidad de registros que tiene el archivo original 
        archivoOriginal.read((char*)&p, sizeof(Paciente));//lee cada paciente del archivo original
        if (!p.eliminado) {//si el paciente no fue eliminado 
            p.id = nuevoID++;
            archivoTemporal.write((char*)&p, sizeof(Paciente));//escribe solo los pacientes activos con su respectivo id ordenado
        }
    }

    archivoOriginal.close();

    // Actualizar header
    nuevoHeader.cantidadRegistros = nuevoID - 1;//actualiza la cantidad de registros 
    nuevoHeader.proximoID = nuevoID;
    nuevoHeader.registrosActivos = nuevoID - 1;//actualiza la cantidad de registros activos

    // Reescribir header al inicio
    archivoTemporal.seekp(0);//mueve el puntero de escritura al inicio del archivo
    archivoTemporal.write((char*)&nuevoHeader, sizeof(nuevoHeader));//escribe el nuevo header
    archivoTemporal.close();

    // Reemplazar archivo original
    remove("pacientes.bin");//borra el archivo original
   rename("temp_pacientes.bin", "pacientes.bin");//renombra el archivo temporal como el archivo original

    cout << "? Pacientes reordenados automáticamente. Próximo ID: " << nuevoHeader.proximoID << "\n";
}

void eliminarPacienteInteractivo() {
    int id;
    cout << "ID del paciente a eliminar: ";
    cin >> id;

    if (eliminarRegistro<Paciente>("pacientes.bin", id)) {
        cout << "Paciente eliminado lógicamente.\n";
        reordenarPacientes(); // Aquí se reorganiza automáticamente
    } else {
        cout << "No se pudo eliminar.\n";
    }
}

//DOCTORES

void reiniciarArchivoDoctores() {
ofstream archivo("doctores.bin", ios::binary | ios::trunc);
if (!archivo.is_open()) {
cerr << "No se pudo crear doctores.bin\n";
return;
}
ArchivoHeader header = {0, 1, 0, 1}; // Reinicia contador de ID
archivo.write((char*)&header, sizeof(header));
archivo.close();
cout << "Archivo doctores.bin reiniciado. Todos los registros fueron eliminados.\n";
}

void registrarDoctor() {
    Doctor d = {};
    cin.ignore();
    cout << "Nombre: "; cin.getline(d.nombre, 50);
    cout << "Apellido: "; cin.getline(d.apellido, 50);
    cout << "Cédula profesional: "; cin.getline(d.cedulaProfesional, 20);
    cout << "Especialidad: "; cin.getline(d.especialidad, 50);
    cout << "Años de experiencia: "; cin >> d.aniosExperiencia;
    cout << "Costo de consulta: "; cin >> d.costoConsulta;
    cin.ignore();
    cout << "Horario de atención: "; cin.getline(d.horarioAtencion, 50);
    cout << "Teléfono: "; cin.getline(d.telefono, 15);
   do {
        cout << "Email: ";
        cin.getline(d.email, 50);
        if (!validarEmail(d.email)) {
            cout << "? Email inválido. Debe contener '@' y al menos un '.' después.\n";
        }
    } while (!validarEmail(d.email));
    d.disponible = true;
    d.cantidadPacientes = 0;
    d.cantidadCitas = 0;

    if (agregarRegistro("doctores.bin", d)) {
        cout << "Doctor registrado con ID: " << d.id << "\n";
    } else {
        cout << "Error al registrar doctor.\n";
    }
}

Doctor buscarDoctorPorId(int id) {
    ifstream archivo("doctores.bin", ios::binary);
    Doctor resultado;
    resultado.id = 0;

    if (!archivo.is_open()) return resultado;

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Doctor d;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&d, sizeof(Doctor));
        if (!d.eliminado && d.id == id) {
            archivo.close();
            return d;//retorna el doctor al q le pertenece el id 
        }
    }
    
 
    
    

    archivo.close();
    return resultado;
}


void reordenarDoctores() {
    ifstream archivoOriginal("doctores.bin", ios::binary);
    if (!archivoOriginal.is_open()) {
        cerr << "No se pudo abrir doctores.bin\n";
        return;
    }

    ArchivoHeader headerOriginal;
    archivoOriginal.read((char*)&headerOriginal, sizeof(headerOriginal));

    ofstream archivoTemporal("temp_doctores.bin", ios::binary | ios::trunc);
    if (!archivoTemporal.is_open()) {
        std::cerr << "No se pudo crear archivo temporal.\n";
        archivoOriginal.close();
        return;
    }

    ArchivoHeader nuevoHeader = {};
    nuevoHeader.version = headerOriginal.version;

    // Reservar espacio para el header
    archivoTemporal.write((char*)&nuevoHeader, sizeof(nuevoHeader));

    Doctor d;
    int nuevoID = 1;

    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {
        archivoOriginal.read((char*)&d, sizeof(Doctor));
        if (!d.eliminado) {
            d.id = nuevoID++;
            archivoTemporal.write((char*)&d, sizeof(Doctor));
        }
    }

    archivoOriginal.close();

    // Actualizar header
    nuevoHeader.cantidadRegistros = nuevoID - 1;
    nuevoHeader.proximoID = nuevoID;
    nuevoHeader.registrosActivos = nuevoID - 1;

    // Reescribir header al inicio
    archivoTemporal.seekp(0);
    archivoTemporal.write((char*)&nuevoHeader, sizeof(nuevoHeader));
    archivoTemporal.close();

    // Reemplazar archivo original
    remove("doctores.bin");
    rename("temp_doctores.bin", "doctores.bin");

    cout << "? Doctores reordenados automáticamente. Próximo ID: " << nuevoHeader.proximoID << "\n";
}

void eliminarDoctorInteractivo() {
    int id;
    cout << "ID del doctor a eliminar: ";
    cin >> id;

    if (eliminarRegistro<Doctor>("doctores.bin", id)) {
        cout << "Doctor eliminado lógicamente.\n";
        reordenarDoctores(); // ? reorganiza automáticamente
    } else {
        cout << "No se pudo eliminar.\n";
    }
}

void buscarDoctoresPorEspecialidad(const char* especialidadBuscada) {
   ifstream archivo("doctores.bin", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir doctores.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Doctor d;
    bool encontrados = false;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&d, sizeof(Doctor));
        if (!d.eliminado && strcmp(d.especialidad, especialidadBuscada) == 0) {
            cout << "\nID: " << d.id << "\n";
            cout << "Nombre: " << d.nombre << " " << d.apellido << "\n";
            cout << "Teléfono: " << d.telefono << "\n";
            cout << "Email: " << d.email << "\n";
            encontrados = true;
        }
    }

    archivo.close();

    if (!encontrados) {
        cout << "No se encontraron doctores con esa especialidad.\n";
    }
}

bool asignarPacienteADoctor(int idDoctor, int idPaciente) {
    // Verificar si ya existe la asignación
    ifstream lectura("asignaciones.bin", ios::binary);
    Asignacion a;
    while (lectura.read((char*)&a, sizeof(Asignacion))) {
        if (a.idDoctor == idDoctor && a.idPaciente == idPaciente) {
            cout << "El paciente ya está asignado a este doctor.\n";
            lectura.close();
            return false;
        }
    }
    lectura.close();

    // Crear nueva asignación
    ofstream escritura("asignaciones.bin", ios::binary | ios::app);
    Asignacion nueva;
    nueva.idDoctor = idDoctor;
    nueva.idPaciente = idPaciente;
    nueva.fechaAsignacion = time(nullptr);
    escritura.write((char*)&nueva, sizeof(Asignacion));
    escritura.close();

    // Mostrar nombre del paciente
    ifstream pacientes("pacientes.bin", ios::binary);
    ArchivoHeader header;
    pacientes.read((char*)&header, sizeof(header));

    Paciente p;
    while (pacientes.read((char*)&p, sizeof(Paciente))) {
        if (!p.eliminado && p.id == idPaciente) {
            cout << "Paciente asignado: [" << p.id << "] " << p.nombre << " " << p.apellido << "\n";
            break;
        }
    }
    pacientes.close();

    return true;
}


void mostrarPacientesDeDoctor(int idDoctor) {
    ifstream asignaciones("asignaciones.bin", ios::binary);
    if (!asignaciones.is_open()) {
        cerr << "No se pudo abrir asignaciones.bin\n";
        return;
    }

    bool tienePacientes = false;
    Asignacion a;

    ifstream pacientes("pacientes.bin", ios::binary);
    if (!pacientes.is_open()) {
        cerr << "No se pudo abrir pacientes.bin\n";
        asignaciones.close();
        return;
    }

    ArchivoHeader header;
    pacientes.read((char*)&header, sizeof(header));

    cout << "\nPacientes asignados:\n";

    while (asignaciones.read((char*)&a, sizeof(Asignacion))) {
        if (a.idDoctor == idDoctor) {
            // Buscar paciente por ID
            Paciente p;
            pacientes.clear();//resetea el estado del archivo para que puedas seguir usándolo. Se coloca pq recorremos varias veces el archivo, para evitar errores
            pacientes.seekg(sizeof(ArchivoHeader)); // volver al inicio de registros

            for (int i = 0; i < header.cantidadRegistros; i++) {
                pacientes.read((char*)&p, sizeof(Paciente));
                if (!p.eliminado && p.id == a.idPaciente) {
                    cout << "[" << p.id << "] " << p.nombre << " " << p.apellido << "\n";
                    tienePacientes = true;
                    break;
                }
            }
        }
    }

    if (!tienePacientes) {
        cout << "Este doctor no tiene pacientes asignados.\n";
    }

    pacientes.close();
    asignaciones.close();
}

void contarDoctoresRegistrados() {
    ifstream archivo("doctores.bin", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir doctores.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Doctor d;
    int contador = 0;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&d, sizeof(Doctor));
        if (!d.eliminado) {
            contador++;
        }
    }

    archivo.close();
   cout << "Total de doctores registrados (activos): " << contador << "\n";
}



//CITAS E HISTORIAL

void reiniciarArchivoCitas() {
    ofstream archivo("citas.bin", ios::binary | ios::trunc);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear citas.bin\n";
        return;
    }

    ArchivoHeader header = {0, 1, 0, 1}; // Reinicia contador de ID
    archivo.write((char*)&header, sizeof(header));
    archivo.close();

    cout << "Archivo cin.bin reiniciado. Todos los registros fueron eliminados.\n";
}

bool existePaciente(int id) {
    ifstream archivo("pacientes.bin", ios::binary);
    if (!archivo.is_open()) return false;

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Paciente p;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&p, sizeof(Paciente));
        if (p.id == id && p.activo) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

bool existeDoctor(int id) {
    ifstream archivo("doctores.bin", ios::binary);
    if (!archivo.is_open()) return false;

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Doctor d;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&d, sizeof(Doctor));
        if (d.id == id && d.disponible) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}


void agendarCitaInteractiva() {
    int idPaciente, idDoctor;
    char fecha[11], hora[6], motivo[150];

    cout << "\n--- Agendar Nueva Cita ---\n";
    cout << "ID del paciente: ";
    cin >> idPaciente;
    cout << "ID del doctor: ";
    cin >> idDoctor;
     if (!existePaciente(idPaciente)) {
    cout << "? El paciente con ID " << idPaciente << " no existe o está inactivo.\n";
    return;
}

if (!existeDoctor(idDoctor)) {
    cout << "? El doctor con ID " << idDoctor << " no existe o no está disponible.\n";
    return;
}

    cin.ignore();
    do {
        cout << "Fecha (YYYY-MM-DD): ";
        cin.getline(fecha, 11);
        if (!validarFecha(fecha)) {
            cout << "? Fecha inválida. Intente de nuevo.\n";
        }
    } while (!validarFecha(fecha));

    do {
        cout << "Hora (HH:MM): ";
        cin.getline(hora, 6);
        if (!validarHora(hora)) {
            cout << "? Hora inválida. Intente de nuevo.\n";
        }
    } while (!validarHora(hora));

    if (horarioOcupado(idDoctor, fecha, hora)) {
        cout << "? El doctor ya tiene una cita pendiente en ese horario.\n";
        return;
    }

    cout << "Motivo de la cita: ";
    cin.getline(motivo, 150);

    // Abrir archivo y registrar cita
    fstream archivo("citas.bin", ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir citas.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Cita nueva;
    nueva.id = header.ultimoId + 1;
    nueva.idPaciente = idPaciente;
    nueva.idDoctor = idDoctor;
    strncpy(nueva.fecha, fecha, 10); nueva.fecha[10] = '\0';
    strncpy(nueva.hora, hora, 5); nueva.hora[5] = '\0';
    strncpy(nueva.motivo, motivo, 149); nueva.motivo[149] = '\0';
    strcpy(nueva.estado, "Pendiente");
    strcpy(nueva.observaciones, "");
    nueva.atendida = false;

    // Escribir cita
    archivo.seekp(0, ios::end);//coloca el puntero de escritura al final del archivo
    archivo.write((char*)&nueva, sizeof(Cita));

    // Actualizar header
    header.ultimoId++;
    header.cantidadRegistros++;
    archivo.seekp(0);
    archivo.write((char*)&header, sizeof(ArchivoHeader));//escribe kas modificaciones del header

    archivo.close();

    cout << "? Cita agendada con ID: " << nueva.id << "\n";
}

void atenderCitaInteractiva() {
    int id;
    cin.ignore();
    cout << "ID de la cita a atender: ";
    cin >> id;
    cin.ignore();

    int idx = buscarIndicePorID("citas.bin", id, sizeof(Cita));
    if (idx == -1) {
        cout << "Cita no encontrada.\n";
        return;
    }

    fstream archivo("citas.bin", ios::binary | ios::in | ios::out);
    archivo.seekg(calcularPosicion(idx, sizeof(Cita)));
    Cita c;
    archivo.read((char*)&c, sizeof(Cita));

    if (strcmp(c.estado, "Agendada") != 0 || c.eliminado) {
        cout << "La cita no está en estado válido para ser atendida.\n";
        archivo.close();
        return;
    }

    char observaciones[200];
    cout << "Observaciones: ";
    cin.getline(observaciones, 200);

    strcpy(c.estado, "Atendida");
    strncpy(c.observaciones, observaciones, 199);
    c.observaciones[199] = '\0';
    c.atendida = true;
    c.fechaModificacion = time(nullptr);

    // Crear consulta médica
    HistorialMedico consulta = {};
    consulta.idPaciente = c.idPaciente;
    consulta.doctorID = c.idDoctor;
    strcpy(consulta.fecha, c.fecha);
    strcpy(consulta.hora, c.hora);
    strcpy(consulta.diagnostico, c.motivo);
    strcpy(consulta.tratamiento, "Tratamiento aplicado");
    strcpy(consulta.medicamentos, "Medicamentos recetados");
    consulta.costo = 0;//como no se lo pido al usuario lo igualo a 0 para que no quede como basura de memoria

    agregarRegistro("historiales.bin", consulta);
    c.consultaID = consulta.id;//Se guarda la consulta en historiales.bin. Se vincula la cita con el ID de la consulta.



    archivo.seekp(calcularPosicion(idx, sizeof(Cita)));
    archivo.write((char*)&c, sizeof(Cita));
    archivo.close();

    cout << "Cita atendida y registrada en el historial.\n";
}

void verCitasPorFechaInteractiva() {
    char fecha[11];
    cin.ignore();
    cout << "Ingrese la fecha (YYYY-MM-DD): ";
cin.getline(fecha, 11);

if (!validarFecha(fecha)) {
    cout << "❌ Fecha inválida. Intente de nuevo.\n";
    return;
}

    ifstream archivo("citas.bin", ios::binary);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de citas.\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(ArchivoHeader));
    Cita c;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&c, sizeof(Cita));
        if (!c.eliminado && strcmp(c.fecha, fecha) == 0) {
            cout << "ID: " << c.id << " | Hora: " << c.hora << " | Estado: " << c.estado << "\n";
        }
    }

    archivo.close();
}

void verHistorialInteractivo() {
    int id;
    cout << "ID del paciente: ";
    cin >> id;

    int cantidad = 0;
    ifstream archivo("historiales.bin", ios::binary);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de historiales.\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    HistorialMedico h;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&h, sizeof(HistorialMedico));
        if (!h.eliminado && h.idPaciente == id) {
            cantidad++;
            cout << "\nConsulta #" << h.id << " - Fecha: " << h.fecha << " " << h.hora << "\n";
            cout << "Diagnóstico: " << h.diagnostico << "\n";
            cout << "Tratamiento: " << h.tratamiento << "\n";
            cout << "Medicamentos: " << h.medicamentos << "\n";
        }
    }

    archivo.close();

    if (cantidad == 0) {
        cout << "Este paciente no tiene historial médico registrado.\n";
    }
}

void verCitasDePacienteInteractivo() {
    int id;
    cout << "ID del paciente: ";
    cin >> id;

    ifstream archivo("citas.bin", ios::binary);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de citas.\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));
    Cita c;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&c, sizeof(Cita));
        if (!c.eliminado && c.idPaciente== id) {
            cout << "ID: " << c.id << " | Fecha: " << c.fecha << " " << c.hora
                 << " | Motivo: " << c.motivo << " | Estado: " << c.estado << "\n";
        }
    }

    archivo.close();
}

void reordenarCitas() {
    ifstream archivoOriginal("citas.bin", ios::binary);
    if (!archivoOriginal.is_open()) {
        cerr << "No se pudo abrir citas.bin\n";
        return;
    }

    ArchivoHeader headerOriginal;
    archivoOriginal.read((char*)&headerOriginal, sizeof(headerOriginal));

    ofstream archivoTemporal("temp_citas.bin", ios::binary | ios::trunc);
    if (!archivoTemporal.is_open()) {
        cerr << "No se pudo crear archivo temporal.\n";
        archivoOriginal.close();
        return;
    }

    ArchivoHeader nuevoHeader = {};
    nuevoHeader.version = headerOriginal.version;

    // Reservar espacio para el header
    archivoTemporal.write((char*)&nuevoHeader, sizeof(nuevoHeader));

    Cita c;
    int nuevoID = 1;

    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {
        archivoOriginal.read((char*)&c, sizeof(Cita));
        if (!c.eliminado) {
            c.id = nuevoID++;
            archivoTemporal.write((char*)&c, sizeof(Cita));
        }
    }

    archivoOriginal.close();

    // Actualizar header
    nuevoHeader.cantidadRegistros = nuevoID - 1;
    nuevoHeader.proximoID = nuevoID;
    nuevoHeader.registrosActivos = nuevoID - 1;

    // Reescribir header al inicio
    archivoTemporal.seekp(0);
    archivoTemporal.write((char*)&nuevoHeader, sizeof(nuevoHeader));
    archivoTemporal.close();

    // Reemplazar archivo original
    remove("citas.bin");
    rename("temp_citas.bin", "citas.bin");

    cout << "? Citas reordenadas automáticamente. Próximo ID: " << nuevoHeader.proximoID << "\n";
}


void cancelarCitaInteractiva() {
    int id;
    cout << "ID de la cita a cancelar: ";
    cin >> id;

    int idx = buscarIndicePorID("citas.bin", id, sizeof(Cita));
    if (idx == -1) {
        cout << "Cita no encontrada.\n";
        return;
    }

    fstream archivo("citas.bin", ios::binary | ios::in | ios::out);
    archivo.seekg(calcularPosicion(idx, sizeof(Cita)));

    Cita c;
    archivo.read((char*)&c, sizeof(Cita));

    if (c.atendida || c.eliminado) {
        cout << "La cita ya fue atendida o está eliminada.\n";
        archivo.close();
        return;
    }

    strcpy(c.estado, "Cancelada");
    c.fechaModificacion = time(nullptr);
    c.eliminado = true;

    archivo.seekp(calcularPosicion(idx, sizeof(Cita)));
    archivo.write((char*)&c, sizeof(Cita));
    archivo.close();

    cout << "Cita cancelada correctamente.\n";
    reordenarCitas(); // ? reorganiza automáticamente
}

void verCitasDeDoctor(int idDoctor) {
    ifstream archivo("citas.bin", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir citas.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Cita c;
    bool encontradas = false;

    cout << "\nCitas del doctor con ID " << idDoctor << ":\n";
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&c, sizeof(Cita));
        if (!c.eliminado && c.idDoctor == idDoctor) {
            cout << "ID Cita: " << c.id << " - Paciente ID: " << c.idPaciente
                 << " - Fecha: " << c.fecha << " - Hora: " << c.hora << "\n";
            encontradas = true;
        }
    }

    archivo.close();

    if (!encontradas) {
        cout << "No se encontraron citas para este doctor.\n";
    }
}


void verCitasDePaciente(int idPaciente) {
   ifstream archivo("citas.bin", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir citas.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Cita c;
    bool encontradas = false;

   cout << "\nCitas del paciente con ID " << idPaciente << ":\n";
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&c, sizeof(Cita));
        if (!c.eliminado && c.idPaciente == idPaciente) {
            cout << "ID Cita: " << c.id << " - Fecha: " << c.fecha
                      << " - Hora: " << c.hora << " - Doctor ID: " << c.idDoctor << "\n";
            encontradas = true;
        }
    }

    archivo.close();

    if (!encontradas) {
        cout << "No se encontraron citas para este paciente.\n";
    }
}

void verCitasDePacienteInteractiva() {
    int idPaciente;
    cout << "Ingrese el ID del paciente: ";
    cin >> idPaciente;
    verCitasDePaciente(idPaciente);
}
void verCitasDeDoctorInteractiva() {
    int idDoctor;
    cout << "Ingrese el ID del doctor: ";
    cin >> idDoctor;
    verCitasDeDoctor(idDoctor);
}
void verCitasPendientes() {
    ifstream archivo("citas.bin", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir citas.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Cita c;
    cout << "\nCitas pendientes:\n";
    while (archivo.read((char*)&c, sizeof(Cita))) {
        if (!c.eliminado && !c.atendida) {
            cout << "ID: " << c.id << " - Fecha: " << c.fecha << " - Hora: " << c.hora << "\n";
        }
    }

    archivo.close();
}

void contarCitasRegistradas() {
    ifstream archivo("citas.bin", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir citas.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(header));

    Cita c;
    int contador = 0;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&c, sizeof(Cita));
        if (!c.eliminado) {
            contador++;
        }
    }

    archivo.close();
    cout << " Total de citas registradas (activas): " << contador << "\n";
}

//MANTENIMIENTO

void verificarIntegridadReferencial() {
    ifstream citas("citas.bin", ios::binary);
    if (!citas.is_open()) {
        cerr << "No se pudo abrir citas.bin\n";
        return;
    }

    ArchivoHeader headerCitas;
    citas.read((char*)&headerCitas, sizeof(ArchivoHeader));

    Cita c;
    bool errores = false;

    for (int i = 0; i < headerCitas.cantidadRegistros; i++) {
        citas.read((char*)&c, sizeof(Cita));
        if (c.eliminado) continue;

        bool doctorValido = false;
        bool pacienteValido = false;

        // Verificar doctor
        ifstream doctores("doctores.bin", ios::binary);
        if (doctores.is_open()) {
            ArchivoHeader headerDoc;
            doctores.read((char*)&headerDoc, sizeof(ArchivoHeader));
            Doctor d;
            for (int j = 0; j < headerDoc.cantidadRegistros; j++) {
                doctores.read((char*)&d, sizeof(Doctor));
                if (!d.eliminado && d.id == c.idDoctor) {
                    doctorValido = true;
                    break;
                }
            }
            doctores.close();
        }

        // Verificar paciente
        ifstream pacientes("pacientes.bin", ios::binary);
        if (pacientes.is_open()) {
            ArchivoHeader headerPac;
            pacientes.read((char*)&headerPac, sizeof(headerPac));
            Paciente p;
            for (int j = 0; j < headerPac.cantidadRegistros; j++) {
                pacientes.read((char*)&p, sizeof(Paciente));
                if (!p.eliminado && p.id == c.idPaciente) {
                    pacienteValido = true;
                    break;
                }
            }
            pacientes.close();
        }

        if (!doctorValido || !pacienteValido) {
            errores = true;
            cout << "? Cita ID " << c.id << " tiene referencias inválidas:\n";
            if (!doctorValido) cout << "   - Doctor ID " << c.idDoctor << " no existe o está eliminado.\n";
            if (!pacienteValido) cout << "   - Paciente ID " << c.idPaciente << " no existe o está eliminado.\n";
        }
    }

    citas.close();

    if (!errores) {
        cout << "? Todas las citas tienen referencias válidas.\n";
    }
}

void verificarIntegridadDeArchivos() {//verifica que cada archivo se pueda abrir
    const char* archivos[] = { "pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin" };//arrreglo que contiene los nombres de mis archivos
    for (const char* nombre : archivos) {//recorre cada nombre en el arreglo
        ifstream archivo(nombre, ios::binary);
        if (!archivo.is_open()) {
          cout << "? No se pudo abrir " << nombre << "\n";
        } else {
            cout << "? " << nombre << " está accesible.\n";
            archivo.close();
        }
    }
}
void compactarArchivo(const char* nombreArchivo, size_t tamanoRegistro) {
    ifstream entrada(nombreArchivo, ios::binary);
    if (!entrada.is_open()) {
        cerr << "No se pudo abrir " << nombreArchivo << " para lectura.\n";
        return;
    }

    ArchivoHeader headerOriginal;
    entrada.read((char*)&headerOriginal, sizeof(ArchivoHeader));

    ofstream salidaTemp("temp_compactado.bin", ios::binary | ios::trunc);
    if (!salidaTemp.is_open()) {
        std::cerr << "No se pudo crear archivo temporal.\n";
        entrada.close();
        return;
    }

    ArchivoHeader nuevoHeader = {};
    nuevoHeader.version = headerOriginal.version;

    // Reservar espacio para el header
    salidaTemp.write((char*)&nuevoHeader, sizeof(nuevoHeader));

    char* buffer = new char[tamanoRegistro];
    int registrosActivos = 0;

    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {
        entrada.read(buffer, tamanoRegistro);
        bool eliminado = *(bool*)(buffer + tamanoRegistro - sizeof(bool)); // campo 'eliminado' al final
        if (!eliminado) {
            salidaTemp.write(buffer, tamanoRegistro);
            registrosActivos++;
        }
    }

    entrada.close();
    delete[] buffer;

    // Actualizar header
    nuevoHeader.cantidadRegistros = registrosActivos;
    nuevoHeader.ultimoId = headerOriginal.ultimoId;

    salidaTemp.seekp(0);
    salidaTemp.write((char*)&nuevoHeader, sizeof(nuevoHeader));
    salidaTemp.close();

    // Reemplazar archivo original
    remove(nombreArchivo);
    rename("temp_compactado.bin", nombreArchivo);

    cout << "? Archivo " << nombreArchivo << " compactado. Registros activos: " << nuevoHeader.cantidadRegistros << "\n";
}

void hacerRespaldo() {
    const char* archivos[] = { "pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin" };

    for (const char* nombre : archivos) {
        ifstream origen(nombre, ios::binary);

        // Construir nombre del archivo de respaldo con char[]
        char nombreRespaldo[100]; // tamaño suficiente
        strcpy(nombreRespaldo, "respaldo_"); // copiar prefijo, es decir nombrerespalde es respaldo_
        strcat(nombreRespaldo, nombre);      // concatenar nombre original, junta respaldo_ con el nomre og del archivo y ese es ahora mi nombre respaldp

        ofstream destino(nombreRespaldo, ios::binary);//abro el archivo respaldo

        if (origen && destino) {//si ambos se abren correctamente 
            destino << origen.rdbuf(); // copiar contenido, pasa la info del archivo og al respaldo. rdbuf() significa read buffer.
            cout << "? Respaldo creado para " << nombre << "\n";
        } else {
            cout << "? Error al respaldar " << nombre << "\n";
        }
    }
}


void restaurarRespaldo() {//contrario a hacer respaldo pasa los datos guardados en el respaldo a mi archivo original
    const char* archivos[] = { "pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin" };

    for (const char* nombre : archivos) {
        char respaldo[100];
        strcpy(respaldo, "respaldo_");
        strcat(respaldo, nombre);

        ifstream origen(respaldo, ios::binary);
        ofstream destino(nombre, ios::binary | ios::trunc);

        if (origen && destino) {
            destino << origen.rdbuf();
            cout << "✔ Restaurado " << nombre << " desde " << respaldo << "\n";
        } else {
            cout << "❌ No se pudo restaurar " << nombre << "\n";
        }
    }
}

void mostrarEstadisticas() {//la estadistica es cuantas veces uso el archivo y lo uso cada vez que registro algo 
    const char* archivos[] = { "pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin" };
    for (const char* nombre : archivos) {
        ifstream archivo(nombre, ios::binary);
        if (!archivo.is_open()) {
            std::cout << "? No se pudo abrir " << nombre << "\n";
            continue;
        }

        ArchivoHeader header;
        archivo.read((char*)&header, sizeof(header));
        cout << "?? " << nombre << ": " << header.cantidadRegistros  << "\n";
        archivo.close();
    }
}


//MENUS

void menuPacientes() {
int opcion;
do {
cout << "\n--- Gestión de Pacientes ---\n";
cout << "1. Registrar nuevo paciente\n";
cout << "2. Buscar paciente por ID\n";
cout << "3. Actualizar paciente\n";
cout << "4. Eliminar paciente\n";
cout << "5. Listar pacientes\n";
cout << "6. Ver historial médico\n";
cout << "7. Buscar paciente por nombre \n";
cout << "8. Buscar paciente por cedula \n";
cout << "9. Ver cuantos pacientes hay registrados\n";
cout << "0. Volver\n";
cout << "Opción: ";
cin >> opcion;
switch (opcion) {
case 1: {
char cedula[20];

cout << "Ingrese la cédula del nuevo paciente: ";

cin.getline(cedula, 20);
cin.ignore();
if (cedulaExiste(cedula)) {
cout << "Ya existe un paciente registrado con esa cédula.\n";
break;
}
// Si no existe, continúa con el registro
registrarPaciente(cedula); 
break;
}
case 2: buscarPacientePorID(); break;
case 3: actualizarPacienteInteractivo(); break;
case 4: eliminarPacienteInteractivo(); break;
case 5: listarRegistrosActivos<Paciente>("pacientes.bin"); break;
case 6: verHistorialInteractivo(); break;
case 7: {
char fragmento[50];
cin.ignore();
cout << "Ingrese parte del nombre a buscar: ";
cin.getline(fragmento, 50);
buscarPacientesPorNombre(fragmento);
break;
}
case 8: {
char cedula[20];
cout << "Ingrese la cédula a buscar: ";
cin.ignore();
cin.getline(cedula, 20);
Paciente p = buscarPacientePorCedula(cedula);//iguala p al paciente econtrado por la cedula
if (p.id != -1) {//el id que devuelve es valido 
cout << "Paciente encontrado: " << p.nombre << " " << p.apellido << endl;
} else {
cout << "No se encontró ningún paciente con esa cédula.\n";
}
break;
}
case 9: mostrarHeader("pacientes.bin"); break;
}
} while (opcion != 0);
}


void menuDoctores() {
    int opcion;
    do {
        cout << "\n--- Gestión de Doctores ---\n";
        cout << "1. Registrar nuevo doctor\n";
        cout << "2. Buscar doctor por ID\n";
        cout << "3. Buscar doctores por especialidad\n";
        cout << "4. Asignar paciente a doctor\n";
        cout << "5. Ver pacientes asignados a doctor\n";
        cout << "6. Listar todos los doctores\n";
        cout << "7. Eliminar doctor\n";
        cout << "8. Ver citas de un doctor\n";
        cout << "9. Ver cuántos doctores hay registrados\n";
        cout << "0. Volver\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
          case 1: {
         

            registrarDoctor(); 
            break;
        }
            case 2: {
                int id;
                cout << "Ingrese ID del doctor: ";
                cin >> id;
                Doctor d = buscarDoctorPorId(id);
                if (d.id == 0 || d.eliminado) {
                    cout << "Doctor no encontrado.\n";
                } else {
                    cout << "\nNombre: " << d.nombre << " " << d.apellido << "\n";
                    cout << "Cedula Profesional: " << d.cedulaProfesional << "\n";
                    cout << "Especialidad: " << d.especialidad << "\n";
                    cout << "Anios de experiencia: " << d.aniosExperiencia << "\n";
                    cout << "Costo Consulta: " << d.costoConsulta << "\n";
                    cout << "Horario de atencion: " << d.horarioAtencion<< "\n";
                    cout << "Teléfono: " << d.telefono << "\n";
                    cout << "Email: " << d.email << "\n";
                }
                break;
            }

            case 3: {
                char especialidad[50];
                cin.ignore();
                cout << "Ingrese especialidad: ";
                cin.getline(especialidad, 50);
                buscarDoctoresPorEspecialidad(especialidad);

                break;
            }

            case 4: {
                int idDoctor, idPaciente;
                cout << "Ingrese ID del doctor: ";
                cin >> idDoctor;
                cout << "Ingrese ID del paciente: ";
                cin >> idPaciente;

                if (asignarPacienteADoctor(idDoctor, idPaciente)) {
                    cout << "Asignación completada.\n";
                } else {
                    cout << "No se pudo asignar el paciente.\n";
                }
                break;
            }
       case 5: {
            int id;
            cout << "ID del doctor: ";
            cin >> id;
            Doctor d = buscarDoctorPorId(id);
            if (d.id != 0) {
                cout << "Doctor: " << d.nombre << " " << d.apellido << "\n";
                mostrarPacientesDeDoctor(id);
            } else {
                cout << "Doctor no encontrado.\n";
            }
            break;
        }



                
            case 6:
                listarRegistrosActivos<Doctor>("doctores.bin");
                break;

            case 7:
                eliminarDoctorInteractivo(); // incluye reordenarDoctores()
                break;

            case 8: {
                int id;
                cout << "ID del doctor: ";
                cin >> id;
                verCitasDeDoctor(id);

                break;
            }
            case 9: contarDoctoresRegistrados(); break;
        }
    } while (opcion != 0);{
	}
}



void menuCitas() {
    int opcion;
    do {
        cout << "\n--- Menú de Citas ---\n";
        cout << "1. Agendar nueva cita\n";
        cout << "2. Cancelar cita\n";
        cout << "3. Atender cita\n";
        cout << "4. Ver citas de un paciente\n";
        cout << "5. Ver citas de un doctor\n";
        cout << "6. Ver citas de una fecha\n";
        cout << "7. Ver citas pendientes\n";
        cout << "8. Ver cuántas citas hay registradas\n";
		cout << "9. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agendarCitaInteractiva(); break;
            case 2: cancelarCitaInteractiva(); break;
            case 3: atenderCitaInteractiva(); break;
            case 4: verCitasDePacienteInteractiva(); break;
            case 5: verCitasDeDoctorInteractiva(); break;
            case 6: verCitasPorFechaInteractiva(); break;
            case 7: verCitasPendientes(); break;
            case 8: contarCitasRegistradas(); break;
            case 9: cout << "Volviendo al menú principal...\n"; break;
			default: cout << "Opción inválida.\n";
        }
    } while (opcion != 9);
}



void menuMantenimientoArchivos() {
    int opcion;
    do {
        cout << "\n=== MANTENIMIENTO DE ARCHIVOS ===" << endl;
        cout << "1. Verificar integridad de archivos" << endl;
        cout << "2. Verificar integridad referencial" << endl;
        cout << "3. Compactar archivo de pacientes" << endl;
        cout << "4. Compactar archivo de doctores" << endl;
        cout << "5. Compactar archivo de citas" << endl;
        cout << "6. Compactar archivo de historiales" << endl;
        cout << "7. Reiniciar archivo de Pacientes" << endl;
        cout << "8. Reiniciar archivo de Doctores" << endl;
        cout << "9. Reiniciar archivo de Citas" << endl;
        cout << "10. Hacer respaldo de datos" << endl;
        cout << "11. Restaurar desde respaldo" << endl;
        cout << "12. Estadísticas de uso de archivos" << endl;
        cout << "13. Volver al menú principal" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: verificarIntegridadDeArchivos(); break;
            case 2: verificarIntegridadReferencial(); break;
            case 3: compactarArchivo("pacientes.bin", sizeof(Paciente)); break;
            case 4: compactarArchivo("doctores.bin", sizeof(Doctor)); break;
            case 5: compactarArchivo("citas.bin", sizeof(Cita)); break;
            case 6: compactarArchivo("historiales.bin", sizeof(HistorialMedico)); break;
            case 7: reiniciarArchivoPacientes(); break;
            case 8: reiniciarArchivoDoctores(); break;
            case 9: reiniciarArchivoCitas(); break;
            case 10: hacerRespaldo(); break;
            case 11: restaurarRespaldo(); break;
            case 12: mostrarEstadisticas(); break;
            case 13: cout << "Volviendo al menú principal...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 13);
}

void menuPrincipal(Hospital* hospital) {
    int opcion;
    do {
        cout << "\n=== SISTEMA DE GESTIÓN HOSPITALARIA ===\n";
        cout << "1. Gestión de Pacientes\n";
        cout << "2. Gestión de Doctores\n";
        cout << "3. Gestión de Citas\n";
        cout << "4. Mantenimiento de Archivos\n";
        cout << "5. Guardar y Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuPacientes(); break;
            case 2: menuDoctores(); break;
            case 3: menuCitas(); break;
            case 4: menuMantenimientoArchivos(); break;

            case 5: {
                ofstream archivo("hospital.bin", ios::binary);
                if (archivo.is_open()) {
                    archivo.write((char*)hospital, sizeof(Hospital));
                    archivo.close();
                    cout << "Datos del hospital guardados.\n";
                }
                break;
            }
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 5);
}

//INT MAIN

int main() {
    setlocale(LC_ALL, "");
    // Archivos que usará el sistema
    const char* archivos[] = {
        "hospital.bin", "pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin"
    };

    // Verificar e inicializar cada archivo si no existe
    for (const char* nombre : archivos) {
        if (!verificarArchivo(nombre)) {
            cout << "Inicializando archivo: " << nombre << "\n";
            inicializarArchivo(nombre);
        }
    }
 



    // Cargar datos del hospital
    Hospital* hospital = new Hospital;//para que persista en el sistema hasta hacerle delete
    
    ifstream archivoHospital("hospital.bin", ios::binary);
    
    if (archivoHospital.is_open()) {
        archivoHospital.read((char*)hospital, sizeof(Hospital));
        archivoHospital.close();
    } else {
    cerr << "Error al cargar datos del hospital.\n";
        delete hospital;
        return 1;
    }
    strcpy(hospital->nombre, "Hospital Central");
    strcpy(hospital->direccion, "Av. Principal, Chiquinquirá");
    strcpy(hospital->telefono, "0261-1234567");
    // Mostrar datos básicos del hospital
    cout << "\n=== BIENVENIDO AL SISTEMA HOSPITALARIO ===\n";
    cout << "Hospital: " << hospital->nombre << "\n";
    cout << "Dirección: " << hospital->direccion << "\n";
    cout << "Teléfono: " << hospital->telefono << "\n";

    // Lanzar menú principal
    menuPrincipal(hospital);

    // Guardar datos del hospital al salir
    ofstream guardar("hospital.bin", ios::binary);
    if (guardar.is_open()) {
        guardar.write((char*)hospital, sizeof(Hospital));
        guardar.close();
        cout << "Datos del hospital guardados correctamente.\n";
    }

    // Liberar memoria
    delete hospital;
    return 0;
}







