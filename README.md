
Proyecto: Sistema Hospitalario en C++

Este sistema fue desarrollado para gestionar de forma integral la información de pacientes, doctores y citas médicas dentro de un hospital. Está escrito completamente en C++ y utiliza estructuras dinámicas para adaptarse al crecimiento de los datos.

Componentes principales

El sistema se basa en varias estructuras clave:

- Hospital: núcleo del sistema, contiene listas dinámicas de pacientes, doctores y citas.
- Paciente: incluye datos personales, historial médico, citas agendadas y estado activo.
- Doctor: almacena información profesional, pacientes asignados y citas.
- Cita: representa una consulta médica con fecha, hora, motivo y estado.
- HistorialMedico: guarda los detalles clínicos de cada consulta.

 Funciones implementadas

 Pacientes
- Registro con validación de cédula y correo.
- Búsqueda por ID, cédula o nombre parcial.
- Edición de datos personales.
- Eliminación con limpieza de citas y desvinculación de doctores.
- Visualización de todos los pacientes.
- Gestión del historial médico.

 Doctores
- Registro con validación de cédula.
- Búsqueda por ID o especialidad.
- Asignación de pacientes.
- Listado de doctores y sus pacientes.
- Eliminación con liberación de memoria.

 Citas
- Agendamiento con validación de fecha y hora.
- Cancelación de citas no atendidas.
- Verificación de disponibilidad horaria.
- Visualización por paciente, doctor, fecha o estado.
- Atención de citas con registro automático en el historial.

 Validaciones incluidas
- Fecha (YYYY-MM-DD) con control de días válidos y años bisiestos.
- Hora (HH:MM) con rango de 24 horas.
- Email con verificación de formato básico.

 Manejo de memoria
Se libera toda la memoria dinámica al cerrar el programa para evitar fugas.

Ejecución
El programa inicia con un menú principal dividido en tres áreas: pacientes, doctores y citas. Cada sección tiene submenús interactivos para realizar las operaciones disponibles.



