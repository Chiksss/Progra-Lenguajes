#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Creacion de tipo de datos para los numeros telefonicos 
typedef int NumTelefono [8];

//ESTRUCTURAS DEL PROGRAMA
typedef struct Medico{
    int codigo;
    char nombre[25];
    char apellido1[25];
    char especialidad[25];
    char turno[25];
    struct Medico* siguiente;
}Medicos;

typedef struct Paciente{
  int identificacion;
  char nombre[25];
  char apellido1[25];
  int edad;
  int numero1;
  int numero2;
  struct Paciente* siguiente;
}Pacientes;

typedef struct Cita{
    int cod_medico;
    int id_cliente;
    int hora; //(08-19)
    //falta fecha dd-mm-aaaa 
    int dia;
    int mes;
    int anno;
    struct Cita* siguiente;
}Citas; 

//FUNCIONES
/*
 Funciones para cargar los archivos de texto que contienen los datos del programa
 No contiene entradas
 Tiene como salida un puntero a un fichero
 */

//Cargar archivo de Medicos
FILE* cargarMedicos(){
    FILE* fichero;
    fichero=fopen("medicos.txt","a");
    if(fichero==NULL)
    {
        printf("No se pudo cargar el archivo de medicos\n");
    }
    else
    {
        printf("Se cargo correctamente el archivo de medicos\n");
    }
    return fichero;
}

//Cargar archivos de Pacientes
FILE* cargarPacientes(){
    FILE* fichero;
    fichero=fopen("pacientes.txt","a");
    if(fichero==NULL)
    {
        printf("No se pudo cargar el archivo de pacientes\n");
    }
    else
    {
    printf("Se cargo correctamente el archivo de pacientes\n");
    }
    return fichero;
}
//Cargar archivo de Citas  
FILE* cargarCitas(){
    FILE* fichero;
    fichero=fopen("citas.txt","a");
    if(fichero==NULL){
        printf("No se pudo cargar el archivo de citas\n");
    }
    else
    {
    printf("Se cargo correctamente el archivo de citas\n");
    }
    return fichero;
}


/*
 Recibe los datos del nuevo medico y un puntero a la lista de medicos
 Sirve para agregar nuevos medicos 
 Retorna el ultimo medico agregado
 */
Medicos* agregarMedico(char* nombre,int codigo,char* apellido,char* especialidad,char* turno ,Medicos* ini){
    Medicos* nuevo=(Medicos*)malloc(sizeof(Medicos));
    strcpy(nuevo->nombre,nombre);
    strcpy(nuevo->apellido1,apellido);
    strcpy(nuevo->especialidad,especialidad);
    strcpy(nuevo->turno,turno);
    nuevo->codigo=codigo;    
        if(ini== NULL)
        {
            ini=nuevo;
            nuevo->siguiente=NULL;
        }
        else{
            nuevo->siguiente=ini;
            ini=nuevo;
        }
        printf("El nuevo médico se agregó correctamente\n");
        return ini;       
    }  

/*
 Recibe los datos de la nueva cita y un puntero a la lista de citas
 Sirve para agregar nuevas citas 
 Retorna la ultima cita agregada
 */
Citas* agregarCitas(int cod_medico,int id_cliente,int hora,int dia,int mes,int anno,Citas* ini){
    Citas* nuevo=(Citas*)malloc(sizeof(Citas));
    nuevo->cod_medico=cod_medico;
    nuevo->id_cliente=id_cliente;
    nuevo->hora=hora;
    nuevo->dia=dia;
    nuevo->mes=mes;
    nuevo->anno=anno;
        if(ini== NULL)
        {
            ini=nuevo;
            nuevo->siguiente=NULL;
        }
        else{
            nuevo->siguiente=ini;
            ini=nuevo;
        }
        printf("La nueva cita se agregó correctamente\n");
        return ini;       
    }

/*
 Funcion para agregar los nuevos pacientes a la lista
 */
Pacientes* agregarPacientes(int identificacion, char* nombre, char* apellido, int edad, int numero1,int numero2, Pacientes* ini){
    Pacientes* nuevo=(Pacientes*)malloc(sizeof(Pacientes));
    nuevo->identificacion=identificacion;
    strcpy(nuevo->nombre,nombre);
    strcpy(nuevo->apellido1,apellido);
    nuevo->edad=edad; 
    nuevo->numero1=numero1;
    nuevo->numero2=numero2;
        if(ini== NULL)
        {
            ini=nuevo;
            nuevo->siguiente=NULL;
        }
        else{
            nuevo->siguiente=ini;
            ini=nuevo;
        }
        printf("El nuevo paciente se agregó correctamente\n");
        return ini;       
    }

/*
Recibe puntero y codigo 
Sirve para buscar un medico en la lista 
retorna true o false
 */
int existeMedico(int codigo, Medicos* ptr){
    while(ptr!=NULL){
        if(ptr->codigo==codigo)
        {
            return 1;
        }
        else{
            ptr=ptr->siguiente;
        }
    }
    return 0;
}

/*
Recibe puntero y codigo
Sirve para buscar un medico en la lista 
retorna true o false
 */
int existePaciente(int id, Pacientes* ptr){
    while(ptr!=NULL){
        if(ptr->identificacion==id)
        {
            return 1;
        }
        else{
            ptr=ptr->siguiente;
        }
    }
    return 0;
}

/*
Verificar que medico tiene mas de una cita el mismo dia,fecha,hora
*/
int ComprobarCitaM(Citas* lista,int codigoMedico,int dia,int mes,int anno,int hora){
    while(lista!=NULL){
        if(codigoMedico==lista->cod_medico && dia==lista->dia && mes==lista->mes && anno==lista->anno && hora==lista->hora){
            return 1;          
        }
        else{
            lista=lista->siguiente;
        }
    }   
}

/*
 * Verificar si el paciente tiene mas de una cita asignada
 */
int ComprobarCitaP(Citas* lista, int idPaciente,int dia,int mes,int anno,int hora){
    while(lista!=NULL){
        if(idPaciente==lista->id_cliente && dia==lista->dia && mes==lista->mes &&anno==lista->anno && hora==lista->hora){
            return 1;
        }
        else{
            lista=lista->siguiente;        }
    }
}


/*
 Recibe un puntero a la lista de medicos
 Sirve para imprimir todos los medicos de la lista
 */
void imprimirMedicos(Medicos* ptr){
    while(ptr!=NULL){
        printf("Codigo: %d  Nombre: %s Apellido: %s Especialidad: %s Turno: %s \n",ptr->codigo,ptr->nombre,ptr->apellido1,ptr->especialidad,ptr->turno);
        ptr=ptr->siguiente;
    }
}
/*
 Recibe un puntero a la lista de citas
 Sirve para imprimir todos las citas de la lista
 */
void imprimirCitas(Citas* ptr){
    while(ptr!=NULL){
        printf("Codigo de medico: %d  Identificacion del cliente: %d Hora: %d Fecha: %d-%d-%d\n",ptr->cod_medico,ptr->id_cliente,ptr->hora,ptr->dia,ptr->mes,ptr->anno);
        ptr=ptr->siguiente;
    }
}

void imprimirPacientes(Pacientes* ptr){
    while(ptr!=NULL){
        printf("Identificacion: %d  Nombre: %s Apellido: %s  Edad: %d Tel: %d-%d\n",ptr->identificacion,ptr->nombre,ptr->apellido1,ptr->edad,ptr->numero1,ptr->numero2);
        ptr=ptr->siguiente;
    }
}



/*
 Funcion para guardar los datos de los medicos en el archivo .txt 
 */
int guardarMedico(char* nombre, int codigo,char* apellido,char* especialidad,char* turno)
{
    FILE* fichero;
    fichero=fopen("medicos.txt","a");
    if(fichero==NULL)
    {
        printf("No se ha podido cargar el fichero\n");
        return 0;
    }
    else
    {
        fprintf(fichero,"%d %s %s %s %s\r\n",codigo,nombre,apellido,especialidad,turno);
        printf("Los datos se agregaron al fichero exitosamente\n");
        fclose(fichero);
        return 1;
    }   
}

/*
 Funcion para agregar las citas en el archivo de citas
*/
void guardarCita(FILE* fichero_citas,int cod_medico, int id_cliente,int hora,int dia, int mes, int anno)
{
    if(fichero_citas==NULL){
        printf("No se ha podido cargar el fichero\n");
    }
    else{
        if(hora<10){
            fprintf(fichero_citas,"%d %d 0%d %d %d %d\r\n",cod_medico,id_cliente,hora,dia,mes,anno);
        
        }
        else{
            fprintf(fichero_citas,"%d %d %d %d %d %d\r\n",cod_medico,id_cliente,hora,dia,mes,anno);
        
        }
        
    }
}
/*
 Funcion para agregar los pacientes en el archivo de pacientes 
 */
//void guardarPaciente(FILE* fichero, int id,char* nombre,char* apellido,int edad,int numero_tel){
void guardarPaciente(FILE* fichero,int id,char* nombre, char*apellido, int edad,int numero1,int numero2){
    if(fichero==NULL){
        printf("No se ha podido cargar el fichero de pacientes");
    }
    else{
        fprintf(fichero,"%d %s %s %d %d %d\r\n",id,nombre,apellido,edad,numero1,numero2);
        
    }
}


/*
 Funcion para leer los medicos del archivo txt y guardarlos en lista
 */
Medicos* leerMedicos(){
   Medicos* temporal=NULL;
   FILE* fichero;
   fichero=fopen("medicos.txt","r");
   
   char nombre[25], apellido[25], especialidad[25],turno[25];
   int codigo,contador=1;
   
   rewind(fichero);
   while((fscanf(fichero,"%d %s %s %s %s", &codigo, nombre, apellido, especialidad,turno))!=EOF){
       
        temporal=agregarMedico(nombre,codigo,apellido,especialidad,turno,temporal);
       // printf("Medico %d: %d %s %s %s %s\n",contador,codigo, nombre, apellido, especialidad,turno);
        //contador++;
   }
    fclose(fichero);
   
   return temporal;
} 

/*
 Funcion para verificar que el doctor asignado a la cita se encuentra 
 * registrado en el sistema
 * Retorna 1 si el codigo del doctor se encuentra registrado
 * Retorna 0 si el codigo del doctor no se encuentra registrado 
 */
int VerificarDoctor(Medicos* ptr,int codigoMedico)
{
    while(ptr!=NULL){
        if(codigoMedico==ptr->codigo){
            return 1;
        } 
        else{ 
            ptr=ptr->siguiente;
        }    
    }
    return 0;
}

/*
 Funcion para leer las citas del archivo txt y guardarlas en lista 
 */
Citas* leerCitas(){
   Citas* temporal=NULL;
   FILE* fichero;
   fichero=fopen("citas.txt","r");
   
   //char fecha[25];
   int codigoMedico,idCliente,hora,contador=0,dia,mes,anno;
   
   rewind(fichero);
   while((fscanf(fichero,"%d %d %d %d %d %d", &codigoMedico, &idCliente, &hora,&dia,&mes,&anno))!=EOF){
       
        temporal=agregarCitas(codigoMedico,idCliente,hora,dia,mes,anno,temporal);
        //printf("Cita agregada: %d %d %d %d-%d-%d\n",codigoMedico, idCliente, hora, dia,mes,anno);
        contador++;
   }
    fclose(fichero);
   
   return temporal;
}

/*
 Funcion para leer los pacientes del archivo txt y guardarlos en lista 
 */
Pacientes* leerPacientes(){
    Pacientes* temporal=NULL;
    FILE* fichero;
    fichero=fopen("pacientes.txt","r");
    
    int id,edad,numero1,numero2;
    char nombre[25],apellido[25];
    
    rewind(fichero);
    while((fscanf(fichero,"%d %s %s %d %d %d",&id,nombre,apellido,&edad,&numero1,&numero2))!=EOF){  
        temporal=agregarPacientes(id,nombre,apellido,edad,numero1,numero2,temporal);
    }
    fclose(fichero);
    return temporal;
}


//FUNCIONES PARA LAS VALIDACIONES AL PROGRAMAR CITA 
/*-----------------------------------------------------------------------------
 Funcion para contar las citas de un doctor a la misma hora
 * Retorna la cantidad de citas que un medico tiene asignado a una hora
 */
int ContarCitasporHorario(Citas* ptr,int codigoMedico, int hora)
{
    int totalCitas=0;
    while(ptr!=NULL){
        if((codigoMedico==ptr->cod_medico)&&(hora==ptr->hora)){
            totalCitas++; 
        } 
        else{ 
            ptr=ptr->siguiente;
        }    
    }
    return totalCitas;
}

/*
 Funcion para obtener Medico por codigo
 */
 Medicos* ObtenerMedico(Medicos* ptr,int codigoMedico){
    while(ptr!=NULL){
        if((ptr->codigo)==codigoMedico){
            return ptr;
        }
        else{
            ptr=ptr->siguiente;
        }
    }
}

//Estadisticas
/*
 Funcion para contar la cantidad de medicos en la lista 
 * Retorna la cantidad de Medicos 
 */
int contarMedicos(Medicos* ptr)
{
    int total=0;
    while(ptr!=NULL){
        total++;
        ptr=ptr->siguiente;
    }
    return total;
}

/*
 Funcion para contar la cantidad de citas en la lista 
 * Retorna la cantidad de Citas 
 */
int contarCitas(Citas* ptr)
{
    int total=0;
    while(ptr!=NULL){
        total++;
        ptr=ptr->siguiente;
    }
    return total;
}

/*
 Funcion para contar la cantidad de pacientes en la lista 
 * Retorna la cantidad de Pacientes 
 */
int contarPacientes(Pacientes* ptr)
{
    int total=0;
    while(ptr!=NULL){
        total++;
        ptr=ptr->siguiente;
    }
    return total;
}

/*Funcion que va retornar la cantidad de especialidades existentes*/
int contarEspecialidades(Medicos* ptr){
    
    int totalEspecialidad = 0;
    while(ptr!=NULL){
        totalEspecialidad++;
        ptr=ptr-> siguiente;
    }
    return totalEspecialidad;
}

/*FunciÃ³n que muestra cual contador es mayor, 
 * segun las veces que se verifica la existencia de un codigo*/
int contadorMayor(int cont, Medicos* ptr){
    int mayor = 0;
    int temporal = 0;
    while(ptr!=NULL){
        if (temporal < cont){
            mayor = cont;
            temporal= cont;
        }
        else{
            mayor= temporal;
        }
           
    }  
    ptr = ptr-> siguiente; 
   return mayor;  
}
 /*FunciÃ³n que imprime cual mÃ©dico tiene mÃ¡s citas
 Falta indicacion para que compruebe si es el mayor*/
 int medicoCotizado(Medicos* ptr, int mayor){
    while(ptr!=NULL){
        if(contadorMayor(ptr-> contador)== mayor){
            printf("El mÃ©dico con mÃ¡s citas es: %s,%s,%s", ptr->nombre, ptr->apellido1, ptr->especialidad);
            printf("\n");
            printf("Tiene una cantidad de citas de: %d", ptr-> contador);    
        }
        else{
            ptr= ptr-> siguiente;
        }
    }
    return 0;
    
} 

/*Funcion para contar las citas segun las especialidades existentes*/
int contarCitasEspecialidad(Citas* ptr, int codigoMedico, Medicos* punt, char* especialidad){
    int mayorE = 0;
    int totalCitasE = 0;
    char temporal;
    
    while(ptr!=NULL && punt!=NULL){
        if((codigoMedico==ptr->cod_medico) && (especialidad==punt->especialidad)){
            temporal = punt->especialidad;
            if (temporal==punt->especialidad){
                totalCitasE++;   
            }
        }
        else{
           ptr=ptr->siguiente;
           punt=punt-> siguiente;
            }        
    }
   return totalCitasE;
   return temporal;
 }

 /*Funcion para contar la cantidad de medicos por especialidad*/
int contarMedicosE (Medicos* ptr,int codigoMedico, char especialidad){
    
    int totalMedicosE = 0;
    while(ptr!=NULL){
        if(codigoMedico==ptr->codigo && especialidad==ptr->especialidad){
            totalMedicosE++;
        }
        else{
            ptr= ptr-> siguiente;
        }
    }
    return totalMedicosE;
}

/*Funcion que recibe como entrada el total de citas y el total de medicos,
 retorna promedioTotalC que es el promedio de citas que se obtiene al
 dividir el total de citas entre el total de medicos*/
int promedioCitas(int totalCitas, int totalMedicos ){
    int promedioTotalC = totalCitas/totalMedicos;
    printf("El promedio general es: %d citas por medico.\n",promedioTotalC);

    return promedioTotalC;
    }

/*Funcion que recibe como entrada el total de citas y el total de pacientes,
 retorna promedioTotalCP que es el promedio total de citas por paciente
 que se obtiene al dividir el total de citas entre el total de pacientes*/
int promedioCPaciente(int totalCitas, int totalPacientes){
    int promedioTotalCP  = totalCitas/totalPacientes;
    printf("Promedio de citas por paciente es %d\n",promedioTotalCP);
    return promedioTotalCP;
   }

 /*Funcion que retorna cual especialidad tiene mas citas*/
int mayorEspecialidad(int totalCitasE, char temporal, Medicos* ptr, int mayor){
    if(contadorMayor(totalCitasE)== mayor){
        printf("La especialidad con mayor numero de citas es: %s", &temporal );
    }
    return 0;
}

/*Funcion que retorna cual es el promedio de citas por una especialidad*/
int promedioEspecialidad(int totalCitasE, int totalMedicosE){
    int promedioTotalPE= totalCitasE/totalMedicosE;
    return promedioTotalPE;
    printf("El promedio de citas por especialidad es: %d\n ", promedioTotalPE);
    
}

 /*
 Funcion para obtener Medico por codigo
 */
 Medicos* ObtenerMedico(Medicos* ptr,int codigoMedico){
    while(ptr!=NULL){
        if((ptr->codigo)==codigoMedico){
            return ptr;
        }
        else{
            ptr=ptr-> siguiente;
        }
    }
}

/*
 Funcion para comprobar que las horas ingresadas en la cita estan dentro del horario del medico
 * Retorna 1 si no lo está
 */
int ComprobarHorario(Medicos* medico,int hora){
    int num=0;
    if(strcmp(medico->turno,"M")==0 && hora>12){
        num=1;
    } 
    else if(strcmp(medico->turno,"T")==0 && hora<14){
        num=1;
    }
    else if(strcmp(medico->turno,"A")==0 &&( hora<9 || hora>12 && hora<14||hora>17)){
        num=1;
    }
    return num;
}



int main(int argc, char** argv) {
    int respuesta;
    FILE* ficheroMedicos;
    FILE* ficheroCitas;
    FILE* ficheroPacientes;

    //Atributos de medicos
    int codigoMedico;
    char nombreMedico[15];
    char apellidoMedico[15];
    char especialidad[25];
    char turno[15];
    
    //Inicio para las listas de Medicos, Citas y Pacientes
    Medicos* inicioMedico=NULL; 
    Citas* inicioCitas=NULL;
    Pacientes* inicioPacientes=NULL;
    
    //Atributos de los pacientes
    int identificacion;
    char nombrePaciente[15];
    char apellidoPaciente[15];
    int edad;
    int dia;
    int mes;
    int ano;
    int pnumtelefono;
    int snumtelefono;
    
    //Atributos de las citas
    int cod_medico;
    int id_cliente;
    int hora;
    Medicos* medico_cita;
    
    //Estadisticas
    int promedioGeneral;
    
    
    
    while(respuesta!=5){ 
        printf("--------------Menu de opciones------------ \n Seleccione la opción que desea :\n 1.Cargar datos \n 2.Registrar nuevo medico \n 3.Programar cita \n 4.Estadisticas \n 5.Salir\n");
        scanf("%d",&respuesta);
        if(respuesta==1)
        { 
            printf("-----------Cargando archivos-----------\n");
            
            ficheroMedicos=cargarMedicos();
            ficheroPacientes=cargarPacientes();
            ficheroCitas=cargarCitas();
            inicioMedico=leerMedicos();
            inicioCitas=leerCitas();
            inicioPacientes=leerPacientes();         
        }
        else if(respuesta==2)
        {
            if(ficheroMedicos==NULL)
                {
                 printf("Debe cargar el archivo de Medicos primero\n");   
                }
            else
                {
                printf("-----------Agregando Medicos-----------\n");
                printf("Escriba el codigo del nuevo medico: ");
                scanf("%d",&codigoMedico);
            
                if((existeMedico(codigoMedico,inicioMedico))==1)
                {
                    printf("El codigo ya fue asignado, no se pudo agregar el medico\n");
                    exit(1);
                }      
                else
                {
                    printf("Escriba el nombre del medico:  ");
                    scanf("%s",nombreMedico);
                    printf("Escriba el primer apellido del medico: ");
                    scanf("%s",apellidoMedico);
                    printf("Escriba la especialidad del medico: "); 
                    scanf("%s",especialidad);
                    printf("Escriba el turno del medico:\n M-mañana 8:00-12:00 \n T-tarde 14:00-19:00\n A-todo el dia 9:00-12:00 y 14:00-17:00\n");
                    scanf("%s",turno);
                    guardarMedico(nombreMedico,codigoMedico,apellidoMedico,especialidad,turno);
                    inicioMedico=agregarMedico(nombreMedico,codigoMedico,apellidoMedico,especialidad,turno,inicioMedico); 
                }
            }
        }
    
            
        else if(respuesta==3)
        {
            printf("--------------Programando una cita---------------\n");
            printf("Escriba el codigo del medico: ");
            scanf("%d",&cod_medico);
            
            if((existeMedico(cod_medico,inicioMedico))==0)
            {
                printf("No se puede asignar el doctor, no existe dentro de los datos guardados\n");    
                exit(1);
            }
            printf("Escriba la identificacion del paciente: ");
            scanf("%d",&identificacion);
            
            printf("Escriba la hora de la cita: ");
            scanf("%d",&hora);
            
           
            if(hora>19 || hora<8){
                printf("La hora ingresada no es válida, debe estar entre 08-19\n");
                exit(1);
            }
            
            medico_cita=ObtenerMedico(inicioMedico,cod_medico);
            if(ComprobarHorario(medico_cita,hora)==1){
                printf("Este horario no se encuentra disponible para el doctor seleccionado");    
                exit(1);
            }
            

            printf("Escriba el dia(dd) de la cita: ");
            scanf("%d",&dia);

            printf("Escriba el mes(mm) de la cita: ");
            scanf("%d",&mes);

            printf("Escriba el año(aaaa) de la cita: ");
            scanf("%d",&ano);

            if((existePaciente(identificacion,inicioPacientes))==0)
            {
                printf("--------Ingresando nuevo paciente--------\n");
                printf("Ingrese su nombre: ");
                scanf("%s",nombrePaciente);
                
                printf("Ingrese el apellido: ");
                scanf("%s",apellidoPaciente);
                
                printf("Ingrese su edad: ");
                scanf("%d",&edad);
                
                printf("Ingrese los primeros 4 dígitos de su número telefónico: ");
                scanf("%d",&pnumtelefono); 
            
                printf("Ingrese los segundos 4 dígitos de su número telefónico: ");
                scanf("%d",&snumtelefono);
                
                inicioPacientes=agregarPacientes(identificacion,nombrePaciente,apellidoPaciente,edad,pnumtelefono,snumtelefono,inicioPacientes);
                guardarPaciente(ficheroPacientes,identificacion,nombrePaciente,apellidoPaciente,edad,pnumtelefono,snumtelefono);   
            }
            
            if((ComprobarCitaM(inicioCitas,cod_medico,dia,mes,ano,hora))==1){
                printf("Error al ingresar cita, el medico ya tenia una consulta asignada");
                exit(1);
            }
            else if(ComprobarCitaP(inicioCitas,identificacion,dia,mes,ano,hora)==1) {
                printf("Error al ingresar cita, paciente ya tiene una cita asignada");
                exit(1);
            }
            else{
                inicioCitas=agregarCitas(cod_medico,identificacion,hora,dia,mes,ano,inicioCitas);
                guardarCita(ficheroCitas,cod_medico,identificacion,hora,dia,mes,ano);
            }
            }
        
        else if(respuesta==4){
            int opcionestadistica;
            int cantCitas=contarCitas(inicioCitas); 
            int cantMedicos=contarMedicos(inicioMedico);
            int cantPacientes=contarPacientes(inicioPacientes);
            int promedioCP;
               
            printf("Seleccione la informacion que desea visualizar\n 1-Médico con más citas y promedio general de citas\n 2-Especialidad con más citas y promedio de citas por especialidad\n 3-Promedio de citas por paciente\n");
            scanf("%d",&opcionestadistica);
            
            if(opcionestadistica==1){
                promedioGeneral=promedioCitas(cantCitas,cantMedicos);
            }
            else if(opcionestadistica==2){
                
            }
            else if(opcionestadistica==3){
                 promedioCP=promedioCPaciente(cantCitas,cantPacientes);
            }
            
            /*
            printf("-----------Lista de medicos-----------\n");
            imprimirMedicos(inicioMedico);
            printf("----------Lista de Citas---------------\n");
            imprimirCitas(inicioCitas);
            printf("----------Lista de Pacientes------------\n");
            imprimirPacientes(inicioPacientes);
            int cantMedicos=contarMedicos(inicioMedico);
            int cantPacientes=contarPacientes(inicioPacientes);
            int cantCitas=contarCitas(inicioCitas); 
            printf("----------------------------------------\n"); 
            printf("La cantidad de medicos es: %d\n",cantMedicos);
            printf("La cantidad de citas es: %d\n",cantCitas);
            printf("La cantidad de pacientes es: %d\n",cantPacientes);
            */
        }

    }


    return (EXIT_SUCCESS);
}