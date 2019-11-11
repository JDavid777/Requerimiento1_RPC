/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "alertas.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

//Funciones Locales

void limpiarStdin();
char* calcularEdad(char *fecha);
int* partirFecha(char * fecha);
void ingresarDatosPaciente(Paciente *paciente);
void comenzarLecturaSensores(Paciente *paciente,CLIENT *clnt);
void menu(Paciente *paciente,CLIENT *clnt);

void gestion_alertas_1(char *host){
	CLIENT *clnt;
	Paciente  paciente;

#ifndef	DEBUG

	clnt = clnt_create (host, gestion_alertas, gestion_alertas_version, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

#endif	/* DEBUG */

	menu(&paciente,clnt); 

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}
int main (int argc, char *argv[]){
	char *host;
	if (argc < 2) {
		host="localhost";
	}
	else{
		host = argv[1];
	}
	
	gestion_alertas_1 (host);
	exit (0);
}

/**
 * Muestra y gestiona el menu de opciones de el host cliente
 **/
void menu(Paciente *paciente,CLIENT *clnt){
	
	char aux[2];
	int opcion=0;
	bool_t flag=FALSE;
	do{
			
		printf("\n|***************|-MENU-|**************|  \n");
		printf("|-1. Ingresar datos del paciente      |\n");
		printf("|-2. Comenzar lectura de los sensores |\n");
		printf("|-3. Terminar                         |\n");
		printf("|*************************************|\n");
		printf("Seleccione una opcion: \n ->");
		fgets(aux,2,stdin);
		strtok(aux,"\n");
		//limpiarStdin();
		opcion=atoi(aux);
		if (opcion>0)
		{
			switch (opcion)
			{
				case 1:
					if (flag==FALSE)
					{
						ingresarDatosPaciente(paciente); flag=TRUE; 
					}
					else{
						char respuesta[10];
						printf("EL paciente %s %s se encuentra registrado, ¿el paciente se murio o fue dado de alta? \n Presione s para resistrar uno nuevo o n para descartar.\n ->", 
						paciente->nombres,paciente->apellidos);
						scanf("%s",respuesta);
						if (strcmp(respuesta,"s") == 0)
						{
							ingresarDatosPaciente(paciente);
						}
					}					
					break;
				case 2: 
					if (flag==TRUE)
						comenzarLecturaSensores(paciente,clnt); 
					else
						printf("ALERTA! \nDebe Ingresar los datos del paciente de la habitacion\n");
					break;
				case 3:break;

				default: printf("Opcion no valida.\n por favor ingresar una opcion correcta\n");			
				}		
			}
			else
			{
				printf("¡No selecciono nada.!\n");	
			}	
	}
	while(opcion!=3);
}
/**
 * Funcion que permite el registro del paciente;
 * @param paciente 
 **/

void ingresarDatosPaciente(Paciente *paciente){
	
	bool_t flag=FALSE;
	limpiarStdin();
	printf("\n-- INGRESANDO DATOS DEL PACIENTE --");

	printf("\nNombres: ");
	fgets(paciente->nombres,MAXNOM,stdin);
	strtok(paciente->nombres,"\n");

	printf("\nApellidos: ");
	fgets(paciente->apellidos,MAXNOM,stdin);
	strtok(paciente->apellidos,"\n");

	while(flag==FALSE){
		
		printf("\nFecha nacimiento en formato dd/mm/yyyy: ");
		char *fecha=malloc(sizeof(char));
		fgets(fecha,20,stdin);
		strtok(fecha,"\n");
		char *edad=calcularEdad(fecha);
			printf("%s\n", edad);
		if (edad!=NULL){	
			strcpy(paciente->edad,edad);
			free(edad);
			flag=TRUE;
		}
		else{
			printf("\nFecha invalida. Intente Nuevamente.\n");
		}
		
	}
	flag=FALSE;
	while (flag==FALSE)
	{
		int habitacion=0;
		printf("\nNumero Habitacion: ");
		scanf("%d",&habitacion);
		if (habitacion>100&&habitacion<1000)
		{
			paciente->numHabitacion=habitacion;
			flag=TRUE;
		}
		else
		{
			printf("\nNumero de habitacion invalida: El numero debe estar entre 100 y 999\n");
			printf("Intente nuevamente\n");
		}
		limpiarStdin();
		
	}
	
	printf("\n-> ¡Paciente registrado con exito.!\n");
	sleep(1);
	
}

/**
 * Realiza la lectura de los sensores ques estan la habitacion; envia los indicadores cada cierto tiempo.
 * */
void comenzarLecturaSensores(Paciente *paciente,CLIENT *clnt){
	
	srand48(getpid());
	bool_t  *result;
	bool_t flag=TRUE;
	char control[5];
	while(flag==TRUE){
	 	
		paciente->indicadores.presionArterialDiastolica=rand()%(110-40+1) + 40;
		paciente->indicadores.frecuenciaCardiaca=rand()%(200+1);
		paciente->indicadores.frecuenciaRespiratoria=rand()%(60+1);
		paciente->indicadores.presionArterialSistolica=rand()%(160-50+1) + 50;
		paciente->indicadores.saturacionOxigeno=rand()%(110-40+1) + 40;
		paciente->indicadores.temperatura=drand48()*(44-33)+33;// numero aleatorio entre 33 y 44

		result = enviarindicadores_1(paciente, clnt);
		if (result == (bool_t *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		printf("\n\n ENVIANDO INDICADORES\n");
		printf("\n Frecuencia Cardiaca: %.2f",paciente->indicadores.frecuenciaCardiaca);
		printf("\n Frecuencia Respiratoria: %.2f",paciente->indicadores.frecuenciaRespiratoria);
		printf("\n Presion Arterial Diastolica: %.2f",paciente->indicadores.presionArterialDiastolica);
		printf("\n Presion Arterial Sistolica: %.2f",paciente->indicadores.presionArterialSistolica);
		printf("\n Saturacion de Oxigeno: %.2f",paciente->indicadores.saturacionOxigeno);
		printf("\n Temperatura: %.2f",paciente->indicadores.temperatura);

		//printf("Escriba stop para detener lectura de sensores\n");
		sleep(1);
		
	}		
} 
/**
 * Convierte una fecha en formato dd/mm/yyyy a un array que contiene un item de la fecha 
 * en cada posicion.
 * @param fecha fecha ordinarioa en formato dd/mm/yyyy
 * @return array con la fecha partida
 **/
int* partirFecha(char *fecha){

    int *resultFecha;
    resultFecha=malloc(3);
    char delimitador[] = "/";
    char *token = strtok(fecha, delimitador);
    if(token != NULL){
        for (int i=0; i<3;i++)
        {
            int aux=atoi(token);
            resultFecha[i]=aux;
            token = strtok(NULL, delimitador);
        }   
    }
	return resultFecha;
}

/**
 * Calcula la edad de un paciente en dias, meses y años
 * @param fecha fecha de nacimiento del paciente.
 * @return La edad actual del paciente
 * */
char* calcularEdad(char *fecha){

    time_t t;
    struct tm *tm;
    char fechaActual[MAXNOM];
	int dias , semanas, meses;
    char* buff;
	buff=malloc(sizeof(char)*MAXNOM);

    t=time(NULL);
    tm=localtime(&t);
    strftime(fechaActual, MAXNOM, "%d/%m/%Y", tm);
	int *fechaAct=partirFecha(fechaActual);
	int* fechaNac= partirFecha(fecha);

	if ((fechaNac[2] > 1900 && fechaNac[2] <= fechaAct[2]) && (fechaNac[1] > 0 && fechaNac[1] < 13) && (fechaNac[0] > 0 && fechaNac[0] < 32)){	
	
		int anios = fechaAct[2]-fechaNac[2];
			
		if ( fechaAct[2] < fechaNac[2]  )
		{   //En caso de ser menor la fecha actual que el nacimiento
			fechaAct[2] = fechaAct[2] + 30; // Se le suma los 30 días (1 mes) a la fecha actual
			fechaAct[1] = fechaAct[1] - 1; // Se le resta un mes (30 días) al mes actual
			dias =  fechaAct[2] - fechaNac[2]; //Se le resta fecha nacimiento al actual
		}
		else //En caso de ser mayor la fecha actual que el nacimiento
			dias =  fechaAct[2] - fechaNac[2];  //Se le resta fecha nacimiento al actual

		if( fechaAct[1] < fechaNac[1] )
		{   //En caso de ser menor el mes actual que el nacimiento
			fechaAct[1] = fechaAct[1] + 12; // Se le suma los 12 meses (1 año) al mes actual
			fechaAct[2] = fechaAct[2] - 1 ; // Se le resta 1 año ( 12 meses) al año actual
			meses = fechaAct[1] - fechaNac[1]; //Se le resta año nacimiento al actual
		}
		else //En caso de ser mayor el mes actual que el nacimiento
			meses = fechaAct[1] - fechaNac[1]; //Se le resta año nacimiento al actual

		semanas=dias/7;
		dias=dias-semanas*7;
		sprintf(buff,"%d-%d-%d-%d",fechaAct[2]-fechaNac[2],meses,semanas,dias); //Años-Meses-Semanas_Dias
		return buff;
	}
	 
	return NULL;
	
}
/**
 * Limpia la entrada estandar
 * */
void limpiarStdin(){
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}