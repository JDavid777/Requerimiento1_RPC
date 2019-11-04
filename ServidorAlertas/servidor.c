/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "alertas.h"
#include "notificaciones.h"
#include <time.h>

int obtenerGrupo(AlertaGenerada *enviarAlertaGenerada, char*edades);
int* ObtenerEdad(char *fecha);
void guardarHistoria(char* buff);
char** partirRegistroAlertas(char *registro);
void cargarUltimasAlertas(AlertaGenerada *enviarAlertaGenerada);
void generarAlerta(int puntuacion,AlertaGenerada* enviarAlertaGenereada,CLIENT* clnt);
void puntuacionDeLaAlerta(Paciente *paciente,AlertaGenerada *alerta);
void arterialSistolica(Paciente *,IndicadoresAlerta *,float minimo, float maximo,int *);
void frecuenciaCardiaca(Paciente *paciente,IndicadoresAlerta *,float minimo, float maximo,int *puntuacion);
void frecuenciaRespiratoria(Paciente *paciente,IndicadoresAlerta *,float minimo, float maximo,int *puntuacion);
void Temperatura(Paciente *,IndicadoresAlerta *,float minimo, float maximo,int *);
void arterialDiastolica(Paciente *,IndicadoresAlerta *,float minimo, float maximo,int *);
void generarPuntuacion(Paciente *paciente, AlertaGenerada * enviarAlertaGenerada,int * puntuacion);

bool_t *enviarindicadores_1_svc(Paciente *paciente, struct svc_req *rqstp){

	printf("\n -> Servidor de alertas escuchando... \n");
	static bool_t result;
	CLIENT *clnt;
	AlertaGenerada  enviarAlertaGenerada;
    char * dirIpServidorNotificaciones="localhost";
	int   puntuacion=0;

	#ifndef	DEBUG
	clnt = clnt_create (dirIpServidorNotificaciones, gestion_notificaciones, gestion_notificaiones_version, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (dirIpServidorNotificaciones);
		exit (1);
	}
	#endif	/* DEBUG */

	//DATOS PACIENTE
	strcpy(enviarAlertaGenerada.paciente.nombres,paciente->nombres);
	strcpy(enviarAlertaGenerada.paciente.apellidos,paciente->apellidos);
	enviarAlertaGenerada.paciente.numHabitacion=paciente->numHabitacion;
	generarPuntuacion(paciente,&enviarAlertaGenerada,&puntuacion);
	generarAlerta(puntuacion,&enviarAlertaGenerada,clnt);
	
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */

	return &result;
}
/**
 * Genera la puntuacion de un paciente segun los criterios medicos
 * */
void generarPuntuacion(Paciente *paciente, AlertaGenerada * enviarAlertaGenerada,int * puntuacion){
	
	int grupo = obtenerGrupo(enviarAlertaGenerada,paciente->edad);
	IndicadoresAlerta listIndicadores[5];

	if(paciente->indicadores.saturacionOxigeno<90){
		puntuacion++;
	}
	switch (grupo)
	{
		case 1:
			frecuenciaCardiaca(paciente,listIndicadores,120,140,puntuacion);
			frecuenciaRespiratoria(paciente,listIndicadores,40,45,puntuacion);		
			Temperatura(paciente,listIndicadores,38,38,puntuacion);
			arterialSistolica(paciente,listIndicadores,70,100,puntuacion);
			arterialDiastolica(paciente,listIndicadores,50,68,puntuacion);
			break;

		case 2:
			frecuenciaCardiaca(paciente,listIndicadores,100,130,puntuacion);
			frecuenciaRespiratoria(paciente,listIndicadores,20,30,puntuacion);
			Temperatura(paciente,listIndicadores,37.5,37.8,puntuacion);
			arterialSistolica(paciente,listIndicadores,84,106,puntuacion);
			arterialDiastolica(paciente,listIndicadores,56,70,puntuacion);
			break;

		case 3:
			frecuenciaCardiaca(paciente,listIndicadores,100,120,puntuacion);
			frecuenciaRespiratoria(paciente,listIndicadores,20,30,puntuacion);
			Temperatura(paciente,listIndicadores,37.5,37.8,puntuacion);
			arterialSistolica(paciente,listIndicadores,98,106,puntuacion);
			arterialDiastolica(paciente,listIndicadores,56,70,puntuacion);
			break;

		case 4:
			frecuenciaCardiaca(paciente,listIndicadores,80,120,puntuacion);
			frecuenciaRespiratoria(paciente,listIndicadores,20,30,puntuacion);
			Temperatura(paciente,listIndicadores,37.5,37.8,puntuacion);
			arterialSistolica(paciente,listIndicadores,99,112,puntuacion);
			arterialDiastolica(paciente,listIndicadores,64,70,puntuacion);
			break;

		case 5:
			frecuenciaCardiaca(paciente,listIndicadores,80,100,puntuacion);
			frecuenciaRespiratoria(paciente,listIndicadores,12,20,puntuacion);
			Temperatura(paciente,listIndicadores,37,37.5,puntuacion);
			arterialSistolica(paciente,listIndicadores,104,124,puntuacion);
			arterialDiastolica(paciente,listIndicadores,64,86,puntuacion);
			break;

		case 6:
			frecuenciaCardiaca(paciente,listIndicadores,70,80,puntuacion);
			frecuenciaRespiratoria(paciente,listIndicadores,12,20,puntuacion);
			Temperatura(paciente,listIndicadores,37,37,puntuacion);
			arterialSistolica(paciente,listIndicadores,118,132,puntuacion);
			arterialDiastolica(paciente,listIndicadores,70,82,puntuacion);
			break;

		case 7:
			frecuenciaCardiaca(paciente,listIndicadores,60,80,puntuacion);
			frecuenciaRespiratoria(paciente,listIndicadores,12,20,puntuacion);	
			Temperatura(paciente,listIndicadores,36.2,37.2,puntuacion);
			arterialSistolica(paciente,listIndicadores,110,140,puntuacion);
			arterialDiastolica(paciente,listIndicadores,70,90,puntuacion);		
			break;
		
		default:
			break;
	}
	strcpy(enviarAlertaGenerada->indicadoresAlerta[0].indicador,listIndicadores[0].indicador);
	strcpy(enviarAlertaGenerada->indicadoresAlerta[1].indicador,listIndicadores[1].indicador);
	strcpy(enviarAlertaGenerada->indicadoresAlerta[2].indicador,listIndicadores[2].indicador);
	strcpy(enviarAlertaGenerada->indicadoresAlerta[3].indicador,listIndicadores[3].indicador);
	strcpy(enviarAlertaGenerada->indicadoresAlerta[4].indicador,listIndicadores[4].indicador);
	enviarAlertaGenerada->indicadoresAlerta[0].valor=listIndicadores[0].valor;
	enviarAlertaGenerada->indicadoresAlerta[1].valor=listIndicadores[1].valor;
	enviarAlertaGenerada->indicadoresAlerta[2].valor=listIndicadores[2].valor;
	enviarAlertaGenerada->indicadoresAlerta[3].valor=listIndicadores[3].valor;
	enviarAlertaGenerada->indicadoresAlerta[4].valor=listIndicadores[4].valor;

}
/**
 * Valida la puntuacion que obtuvo un paciente para generar o no una alerta, 
 * almacena en un historial de alertas y envia la alerta al ervidor de notificaciones
 **/
void generarAlerta(int puntuacion,AlertaGenerada *enviarAlertaGenerada,CLIENT *clnt){

	bool_t *result;
	
	if(puntuacion==2){
		strcpy(enviarAlertaGenerada->mensaje,"Enviar una enfermera");
	}else if(puntuacion>2){
		strcpy(enviarAlertaGenerada->mensaje,"Enviar un medico y una enfermera");
	}

	// Generar alerta si hay mas de dos puntuciones
	if(puntuacion>=2){
		time_t t;
    	struct tm *tm;
    	char fechaAlerta[MAXNOM];
		char horaAlerta[MAXNOM];
    	char* buff;
		buff=malloc(sizeof(char)*300);

    	t=time(NULL);
    	tm=localtime(&t);
    	strftime(fechaAlerta, MAXNOM, "%d/%m/%Y", tm);
		strftime(horaAlerta, MAXNOM, "%H:%M:%S", tm);
		strcpy(enviarAlertaGenerada->paciente.fecha,fechaAlerta); // fecha en que se genero la alerta
		strcpy(enviarAlertaGenerada->paciente.hora,horaAlerta);  // hora actual 
		
		sprintf(buff,"%d-%s %s-%s-%s-%d\n",enviarAlertaGenerada->paciente.numHabitacion,
		enviarAlertaGenerada->paciente.nombres,enviarAlertaGenerada->paciente.apellidos,
		enviarAlertaGenerada->paciente.fecha,enviarAlertaGenerada->paciente.hora,puntuacion);
		guardarHistoria(buff);
		free(buff);
		
		cargarUltimasAlertas(enviarAlertaGenerada);
		

		printf("\n\n         ALERTA GENERADA        ");

		printf("\n  ->!ENVIANDO ALERTA...¡");

		result = enviarnotificacion_2(enviarAlertaGenerada, clnt);
			
		if (result == (bool_t *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		else{
			printf("\n  ->!ALERTA ENVIADA CON EXITO...¡");
		}
		
	}
}
/**
 * Almacena en un archivo la informacion de una alerta generada
 * */
void guardarHistoria(char *buffer){

	FILE *archivo;
	archivo = fopen("historialDeAlertas.txt","a");

	if (archivo == NULL)
	{
		printf("Error al abrir el archivo");
	} 		
	else
	{	
		fputs(buffer,archivo);
		printf("\n ->Alerta guardada exitosamente.\n");
		fclose(archivo);
	}
}
/**
 * Lee las ultimas cinco alertas que se generaron a un paciente expecifico
 **/
void cargarUltimasAlertas(AlertaGenerada *enviarAlertaGenerada){

	static int numAlertas=0; //contep de alertas
	FILE *archivo;
	char numHabitacion[100];
	char* buffer;
    char** alertaLeida;
	buffer=malloc(sizeof(char)*100);
		
	sprintf(numHabitacion,"%d", enviarAlertaGenerada->paciente.numHabitacion);

	archivo= fopen("historialDeAlertas.txt","r");

	if (archivo == NULL)
	{
		printf("Error al abrir el archivo");
	} 		
	else
	{
		while (feof(archivo) == 0){

			fgets(buffer,100,archivo);
             
			if (strncmp(numHabitacion,buffer,3)==0)
			{	
             	 alertaLeida=partirRegistroAlertas(buffer);
		
			  	if (numAlertas==4){ numAlertas=0;}
				strcpy(enviarAlertaGenerada->ultimasAlertas[numAlertas].fecha,alertaLeida[0]);
				strcpy(enviarAlertaGenerada->ultimasAlertas[numAlertas].hora,alertaLeida[1]);
				enviarAlertaGenerada->ultimasAlertas[numAlertas].puntuacion=atoi(alertaLeida[2]);
				numAlertas++;				
			}
			strcpy(buffer,"");	//clear buffer
		}
		fclose(archivo);
		numAlertas=0;
	}
}
/**
 * Carga desde el archivo de historial de alertas y parte el registro almacenendo la fecha, hora y puntuacion de la alarta en un array
 * @param registro registro que se carga desde el archivo
 * @return array que contiene la informacion de la ultima alerta
 * */
char** partirRegistroAlertas(char* registro){

    int idx=0;
    char** buf;
    buf=(char**)malloc(sizeof(char*)*3);
    char delimitador[] = "-";
    char *token = strtok(registro,"\n");
		
    token = strtok(registro, delimitador);
    if(token != NULL){
        for (int i=0; i<4;i++)
        {
            token = strtok(NULL, delimitador);
			if (i>=1)
			{
                buf[idx]=token; 
            	idx++;
			}
        }   
    }	
	return buf;
}
//Validadores de indicadores: Verifican que los valores esten en un rango normal, si no, se aumenta la puntuacion para su posterior analisis
void frecuenciaCardiaca(Paciente *paciente,IndicadoresAlerta *indicadoresAlerta,float minimo, float maximo,int *puntuacion){

	if(paciente->indicadores.frecuenciaCardiaca<minimo || paciente->indicadores.frecuenciaCardiaca>maximo ){
		strcpy(indicadoresAlerta[0].indicador,"frecuencia cardiaca");
		indicadoresAlerta[0].valor=paciente->indicadores.frecuenciaCardiaca;	
		*puntuacion=(int)((int)*puntuacion + 1);
	}
	else
	{
		indicadoresAlerta[0].valor=0;	
	}
}
void frecuenciaRespiratoria(Paciente *argp,IndicadoresAlerta *indicadoresAlerta,float minimo, float maximo,int *puntuacion){
		
	if(argp->indicadores.frecuenciaRespiratoria<minimo || 
		argp->indicadores.frecuenciaCardiaca>maximo ){
		strcpy(indicadoresAlerta[1].indicador,"frecuencia Respiratoria");
		indicadoresAlerta[1].valor=argp->indicadores.frecuenciaRespiratoria;
		*puntuacion=(int)((int)*puntuacion + 1);
			
	}
	else
	{
		indicadoresAlerta[1].valor=0;	
	}
}
void Temperatura(Paciente *paciente,IndicadoresAlerta *indicadoresAlerta,float minimo, float maximo,int *puntuacion){

		
	if(paciente->indicadores.temperatura<minimo || paciente->indicadores.temperatura>maximo ){

		strcpy(indicadoresAlerta[2].indicador,"Temperatura");
		indicadoresAlerta[2].valor=paciente->indicadores.temperatura;
		*puntuacion=(int)((int)*puntuacion + 1);
	}	
	else
	{
		indicadoresAlerta[2].valor=0;	
	}
		
	
}
void arterialSistolica(Paciente *paciente,IndicadoresAlerta *indicadoresAlerta,float minimo, float maximo,int *puntuacion){
	//Tension arterial sistolica
	
	if(paciente->indicadores.frecuenciaCardiaca<minimo || 
		paciente->indicadores.frecuenciaCardiaca>maximo ){
					
		strcpy(indicadoresAlerta[3].indicador,"Presion arterial sistloca");
		indicadoresAlerta[3].valor=paciente->indicadores.presionArterialSistolica;
		*puntuacion=(int)((int)*puntuacion + 1);
	}
	else
	{
		indicadoresAlerta[3].valor=0;	
	}
}
void arterialDiastolica(Paciente *paciente,IndicadoresAlerta *indicadoresAlerta,float minimo, float maximo,int *puntuacion){
	
	if(paciente->indicadores.frecuenciaCardiaca<minimo || 
		paciente->indicadores.frecuenciaCardiaca>maximo ){
		strcpy(indicadoresAlerta[4].indicador,"Presion arterial diastolica");
		indicadoresAlerta[4].valor=paciente->indicadores.presionArterialDiastolica;
		*puntuacion=(int)((int)*puntuacion + 1);
	}
	else
	{
		indicadoresAlerta[4].valor=0;	
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
/**
 * Obtiene el grupo al que pertenece un paciente ya sea adulto, joven, niño, infante
 * */
int obtenerGrupo(AlertaGenerada *enviarAlertaGenerada, char *edades){

	int *edadExacta=ObtenerEdad(edades);
	char *edad;
	edad=malloc(sizeof(char)*MAXNOM);
	//seis semanas
	if(edadExacta[0]==0 && edadExacta[1]==0 && edadExacta[2]<=6){
		if (edadExacta[2]==0)
		{
			sprintf(edad,"%d Dias",edadExacta[2]);
			strcpy(enviarAlertaGenerada->paciente.edad,edad);
		}
		else{
			sprintf(edad,"%d Semanas con %d dias",edadExacta[2],edadExacta[3]);
			strcpy(enviarAlertaGenerada->paciente.edad,edad);
		}
		
		return 1;
	}
	// 1 año
	if(edadExacta[0]<=1){
		if (edadExacta[1]==0)
		{
			sprintf(edad,"%d Semanas y %d dias",edadExacta[2],edadExacta[3]);
			strcpy(enviarAlertaGenerada->paciente.edad,edad);
		}
		else{
			sprintf(edad,"%d Meses con %d Semanas y %d dias",edadExacta[1],edadExacta[2],edadExacta[3]);
			strcpy(enviarAlertaGenerada->paciente.edad,edad);
		}
		return 2;
	}
	// 2 años
	if(edadExacta[0]<=2){
		sprintf(edad,"%d Años",edadExacta[0]);
		strcpy(enviarAlertaGenerada->paciente.edad,edad);
		return 3;
	}
	// 6 años
		if(edadExacta[0]<=6){
		sprintf(edad,"%d Años",edadExacta[0]);
		strcpy(enviarAlertaGenerada->paciente.edad,edad);
		return 4;
	}
	//13 años
		if(edadExacta[0]<=13){
		sprintf(edad,"%d Años",edadExacta[0]);
		strcpy(enviarAlertaGenerada->paciente.edad,edad);
		return 5;
	}
	// 16 años
		if(edadExacta[0]<=16){
		sprintf(edad,"%d Años",edadExacta[0]);
		strcpy(enviarAlertaGenerada->paciente.edad,edad);
		return 6;
	}

	//mayores a 16
	sprintf(edad,"%d Años",edadExacta[0]);
	strcpy(enviarAlertaGenerada->paciente.edad,edad);
	return 7;
}
/**
 * Determina la edad exacta de un paciente
 * */
int* ObtenerEdad(char *fecha){
   int *resultFecha;
   int idx=0;
   resultFecha=malloc(4);
    char delimitador[] = "-";
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
