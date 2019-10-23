/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "alertas.h"
#include "notificaciones.h"
#include <time.h>


void 
puntuacionDeLaAlerta(Paciente *paciente,AlertaGenerada *alerta);

void arterialSistolica(Paciente *,AlertaGenerada *,float minimo, float maximo,int *);
void frecuenciaCardiaca(Paciente *argp,AlertaGenerada *enviarAlertaGenerada,float minimo, float maximo,int *puntuacion);
void frecuenciaRespiratoria(Paciente *argp,AlertaGenerada *enviarAlertaGenerada,float minimo, float maximo,int *puntuacion);
void Temperatura(Paciente *,AlertaGenerada *,float minimo, float maximo,int *);
void arterialDiastolica(Paciente *,AlertaGenerada *,float minimo, float maximo,int *);
int 
obtenerGrupo(float edad){

	//seis semanas
	if(edad<=0.06){
		return 1;
	}
	// 1 año
	if(edad<1){
		return 2;
	}
	// 2 años
	if(edad<2){
		return 3;
	}
	// 6 años
		if(edad<6){
		return 4;
	}
	//13 años
		if(edad<13){
		return 5;
	}
	// 16 años
		if(edad<16){
		return 6;
	}
	// mayores a 16 años
		if(edad>=16){
		return 7;
	}
	return -1;
}


bool_t *
enviarindicadores_1_svc(Paciente *argp, struct svc_req *rqstp)
{
	static bool_t result;
	bool_t *result_1;
	CLIENT *clnt;
	AlertaGenerada  enviarAlertaGenerada;
	
    char * dirIpServidorNotificaciones="localhost";

	int grupo ;//=obtenerGrupo((float)argp->edad); // TODO cambiar a float el int edad de la interfaz
	int  puntuacion=0;

	//Saturacion de oxigeno es igual para todas las edades
	if(argp->indicadores.saturacionOxigeno<90){
		puntuacion++;
	}

	//DATOS PACIENTE
	strcpy(enviarAlertaGenerada.paciente.nombres,argp->nombres);
	enviarAlertaGenerada.paciente.numHabitacion=argp->numHabitacion;

	//GENERANDO PUNTUACION 
	switch (grupo)
	{
		case 1:
			frecuenciaCardiaca(argp,&enviarAlertaGenerada,120,140,&puntuacion);
			frecuenciaRespiratoria(argp,&enviarAlertaGenerada,40,45,&puntuacion);		 // VERIFICAR SI SE TRANSMITEN LOS DATOS CORRECTAMENTE
			Temperatura(argp,&enviarAlertaGenerada,38,38,&puntuacion);
			arterialSistolica(argp,&enviarAlertaGenerada,70,100,&puntuacion);
			arterialDiastolica(argp,&enviarAlertaGenerada,50,68,&puntuacion);
			break;
		case 2:
			frecuenciaCardiaca(argp,&enviarAlertaGenerada,100,130,&puntuacion);
			frecuenciaRespiratoria(argp,&enviarAlertaGenerada,20,30,&puntuacion);		 // VERIFICAR SI SE TRANSMITEN LOS DATOS CORRECTAMENTE
			Temperatura(argp,&enviarAlertaGenerada,37.5,37.8,&puntuacion);
			arterialSistolica(argp,&enviarAlertaGenerada,84,106,&puntuacion);
			arterialDiastolica(argp,&enviarAlertaGenerada,56,70,&puntuacion);
			break;
		case 3:
			frecuenciaCardiaca(argp,&enviarAlertaGenerada,100,120,&puntuacion);
			frecuenciaRespiratoria(argp,&enviarAlertaGenerada,20,30,&puntuacion);		 // VERIFICAR SI SE TRANSMITEN LOS DATOS CORRECTAMENTE
			Temperatura(argp,&enviarAlertaGenerada,37.5,37.8,&puntuacion);
			arterialSistolica(argp,&enviarAlertaGenerada,98,106,&puntuacion);
			arterialDiastolica(argp,&enviarAlertaGenerada,56,70,&puntuacion);
			
			break;
		case 4:
			frecuenciaCardiaca(argp,&enviarAlertaGenerada,80,120,&puntuacion);
			frecuenciaRespiratoria(argp,&enviarAlertaGenerada,20,30,&puntuacion);		 // VERIFICAR SI SE TRANSMITEN LOS DATOS CORRECTAMENTE
			Temperatura(argp,&enviarAlertaGenerada,37.5,37.8,&puntuacion);
			arterialSistolica(argp,&enviarAlertaGenerada,99,112,&puntuacion);
			arterialDiastolica(argp,&enviarAlertaGenerada,64,70,&puntuacion);

			break;
		case 5:
			frecuenciaCardiaca(argp,&enviarAlertaGenerada,80,100,&puntuacion);
			frecuenciaRespiratoria(argp,&enviarAlertaGenerada,12,20,&puntuacion);		 // VERIFICAR SI SE TRANSMITEN LOS DATOS CORRECTAMENTE
			Temperatura(argp,&enviarAlertaGenerada,37,37.5,&puntuacion);
			arterialSistolica(argp,&enviarAlertaGenerada,104,124,&puntuacion);
			arterialDiastolica(argp,&enviarAlertaGenerada,64,86,&puntuacion);


			break;
		case 6:
			frecuenciaCardiaca(argp,&enviarAlertaGenerada,70,80,&puntuacion);
			frecuenciaRespiratoria(argp,&enviarAlertaGenerada,12,20,&puntuacion);		 // VERIFICAR SI SE TRANSMITEN LOS DATOS CORRECTAMENTE
			Temperatura(argp,&enviarAlertaGenerada,37,37,&puntuacion);
			arterialSistolica(argp,&enviarAlertaGenerada,118,132,&puntuacion);
			arterialDiastolica(argp,&enviarAlertaGenerada,70,82,&puntuacion);

			break;
		case 7:
			frecuenciaCardiaca(argp,&enviarAlertaGenerada,60,80,&puntuacion);
			frecuenciaRespiratoria(argp,&enviarAlertaGenerada,12,20,&puntuacion);		 // VERIFICAR SI SE TRANSMITEN LOS DATOS CORRECTAMENTE
			Temperatura(argp,&enviarAlertaGenerada,36.2,37.2,&puntuacion);
			arterialSistolica(argp,&enviarAlertaGenerada,110,140,&puntuacion);
			arterialDiastolica(argp,&enviarAlertaGenerada,70,90,&puntuacion);		
			break;
		
		default:
			break;
	}

	//MENSAJE

	if(puntuacion==2){
		strcpy(enviarAlertaGenerada.mensaje,"Enviar una enfermera");
	}else if(puntuacion>2){
		strcpy(enviarAlertaGenerada.mensaje,"Enviar un medico y una enfermera");
	}




	#ifndef	DEBUG
	clnt = clnt_create (dirIpServidorNotificaciones, gestion_notificaciones, gestion_notificaiones_version, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (dirIpServidorNotificaciones);
		exit (1);
	}
	#endif	/* DEBUG */
	// Generar alerta si hay mas de dos puntuciones
	if(puntuacion>=2){
		time_t t;
    	struct tm *tm;
    	char fechaActual[100];
		char horaActual[100];
		int dias , meses;
    	char* buff;
		buff=malloc(sizeof(char));

    	t=time(NULL);
    	tm=localtime(&t);
    	strftime(fechaActual, 100, "%d/%m/%Y", tm);
		strftime(horaActual, 100, "%H:%M:%S", tm);
		strcpy(enviarAlertaGenerada.paciente.fecha,fechaActual); // fecha en que se genero la alerta
		strcpy(enviarAlertaGenerada.paciente.hora,horaActual);  // hora actual
		
		//TODO ... Hay que guardar la informacion de la alerta en un archivo txt

		printf("\n \n ENVIANDO ALERTA...");
		//TODO AGREGAR A ULTIMAS ALERTAS

		result_1 = enviarnotificacion_2(&enviarAlertaGenerada, clnt);
			
		if (result_1 == (bool_t *) NULL) {
			clnt_perror (clnt, "call failed");
		}
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */

	return &result;
}

void frecuenciaCardiaca(Paciente *argp,AlertaGenerada *enviarAlertaGenerada,float minimo, float maximo,int *puntuacion){

			if(argp->indicadores.frecuenciaCardiaca<minimo || 
				argp->indicadores.frecuenciaCardiaca>maximo ){
				strcpy(enviarAlertaGenerada->indicadoresAlerta[0].indicador,"frecuencia cardiaca");
				enviarAlertaGenerada->indicadoresAlerta[0].valor=argp->indicadores.frecuenciaCardiaca;
				puntuacion++;
			}
}
void frecuenciaRespiratoria(Paciente *argp,AlertaGenerada *enviarAlertaGenerada,float minimo, float maximo,int *puntuacion){
		
			if(argp->indicadores.frecuenciaRespiratoria<minimo || 
				argp->indicadores.frecuenciaCardiaca>maximo ){
				strcpy(enviarAlertaGenerada->indicadoresAlerta[1].indicador,"frecuencia Respiratoria");
				enviarAlertaGenerada->indicadoresAlerta[1].valor=argp->indicadores.frecuenciaRespiratoria;
				puntuacion++;
			}
}
void Temperatura(Paciente *argp,AlertaGenerada *enviarAlertaGenerada,float minimo, float maximo,int *puntuacion){

			if(argp->indicadores.temperatura<minimo || 
				argp->indicadores.temperatura>maximo ){
				strcpy(enviarAlertaGenerada->indicadoresAlerta[2].indicador,"Temperatura");
				enviarAlertaGenerada->indicadoresAlerta[2].valor=argp->indicadores.temperatura;
				puntuacion++;
			}
}
void arterialSistolica(Paciente *argp,AlertaGenerada *enviarAlertaGenerada,float minimo, float maximo,int *puntuacion){
	//Tension arterial sistolica
			if(argp->indicadores.frecuenciaCardiaca<minimo || 
				argp->indicadores.frecuenciaCardiaca>maximo ){
				strcpy(enviarAlertaGenerada->indicadoresAlerta[3].indicador,"Presion arterial sistloca");
				enviarAlertaGenerada->indicadoresAlerta[3].valor=argp->indicadores.presionArterialSistolica;
				puntuacion++;
			}
}
void arterialDiastolica(Paciente *argp,AlertaGenerada *enviarAlertaGenerada,float minimo, float maximo,int *puntuacion){

			
			if(argp->indicadores.frecuenciaCardiaca<minimo || 
				argp->indicadores.frecuenciaCardiaca>maximo ){
				strcpy(enviarAlertaGenerada->indicadoresAlerta[4].indicador,"Presion arterial diastolica");
				enviarAlertaGenerada->indicadoresAlerta[4].valor=argp->indicadores.presionArterialSistolica;
				puntuacion++;
			}
}

