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
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	gestion_alertas_1 (host);
exit (0);
}

/**
 * Muestra y gestiona el menu de opciones de el host cliente
 **/
void menu(Paciente *paciente,CLIENT *clnt){
	int opcion=0;
	bool_t flag=FALSE;
	do{
			
			printf("\n|***************|-MENU-|**************|  \n");
			printf("|-1. Ingresar datos del paciente      |\n");
			printf("|-2. Comenzar lectura de los sensores |\n");
			printf("|-3. Terminar                         |\n");
			printf("|*************************************|\n");
			printf("Seleccione una opcion: \n ->");
			scanf("%d",&opcion);
			//limpiarStdin();

			switch (opcion)
			{
			case 1: ingresarDatosPaciente(paciente); flag=TRUE; 
				break;
			case 2: 
				if (flag==TRUE)
					comenzarLecturaSensores(paciente,clnt); 
				else
					printf("ALERTA! \nDebe Ingresar los datos del paciente de la habitacion\n");
				break;
			case 3: printf("Saliendo...");break;

			default: printf("Opcion no valida.\n por favor ingresar una opcion correcta\n");			
			}		
	}
	while(opcion!=3);
}
/**
 * Funcion que permite el registro del paciente;
 * @param paciente 
 **/

void ingresarDatosPaciente(Paciente *paciente){
	
	limpiarStdin();
	printf("\n-- INGRESANDO DATOS DEL PACIENTE --");

	printf("\nNombres: ");
	fgets(paciente->nombres,MAXNOM,stdin);
	strtok(paciente->nombres,"\n");

	printf("\nApellidos: ");
	fgets(paciente->apellidos,MAXNOM,stdin);
	strtok(paciente->apellidos,"\n");

	printf("\nFecha nacimiento en formato dd/mm/yyyy: ");
	char *fecha=malloc(sizeof(char));
	fgets(fecha,20,stdin);
	strtok(fecha,"\n");
	char *edad=calcularEdad(fecha);
	strcpy(paciente->edad,edad);
	free(edad);

	printf("\nNumero Habitacion: ");
	scanf("%d",&paciente->numHabitacion);
	limpiarStdin();
}

/**
 * Realiza la lectura de los sensores ques estan la habitacion; envia los indicadores cada cierto tiempo.
 * */
void comenzarLecturaSensores(Paciente *paciente,CLIENT *clnt){
	srand48(getpid());
	bool_t  *result;
	while(TRUE){
	 	
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
   int idx=0;
   resultFecha=malloc(3);
    char delimitador[] = "/";
    char *token = strtok(fecha, delimitador);
    if(token != NULL){
        for (int i=0; i<3;i++)
        {
            int aux=atoi(token);
            resultFecha[idx]=aux;
            token = strtok(NULL, delimitador);
            idx++;
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
    char fechaActual[100];
	int dias , semanas, meses;
    char* buff;
	buff=malloc(sizeof(char));

    t=time(NULL);
    tm=localtime(&t);
    strftime(fechaActual, 100, "%d/%m/%Y", tm);
    int *fechaAct=partirFecha(fechaActual);
    int* fechaNac= partirFecha(fecha);
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
void limpiarStdin(){
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}