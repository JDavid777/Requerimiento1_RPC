/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "notificaciones.h"

bool_t *enviarnotificacion_2_svc(AlertaGenerada *argp, struct svc_req *rqstp){

	static bool_t  result;
	printf("\n********************************************************************************");	

	printf("\n  				ALERTA GENERADA        \n");
	printf("\nN° habitacion: %d",argp->paciente.numHabitacion);
	printf("\nNombres y apellidos: %s %s",argp->paciente.nombres,argp->paciente.apellidos);
	printf("\nEdad: %s",argp->paciente.edad); 
	printf("\nHora de la alerta: %s",argp->paciente.hora); 
	printf("\nFecha de la alerta: %s\n",argp->paciente.fecha); 
	printf("\n********************************************************************************");	

	printf("\n\n	***         INDICADORES QUE GERENARON LA ALERTA        ***\n");

	printf("\n	Nombre Indicador			Valor\n\n");
	for(int i=0; i<5; i++){

		if (argp->indicadoresAlerta[i].valor > 0)
		{
			printf("-> %s			%.2f\n",argp->indicadoresAlerta[i].indicador,argp->indicadoresAlerta[i].valor);

		}		
	}	
	printf("\n********************************************************************************\n");	

	printf("\n********************************************************************************");	
	printf("\n*              ¡ATENCION: %s!                    *", argp->mensaje);
	printf("\n********************************************************************************\n");	
	printf("\n********************************************************************************");	

	printf("\n Fecha de la alerta		     Hora de la alerta		      Puntuacion\n\n");

	for(int i=0; i<5; i++){

			//printf("-> %s	     	  	     %s			      %d\n",argp->ultimasAlertas[i].fecha,argp->ultimasAlertas[i].hora,argp->ultimasAlertas[i].puntuacion);	

		if (argp->ultimasAlertas[i].puntuacion!=-1)
		{
			printf("-> %s	     	  	     %s			      %d\n",argp->ultimasAlertas[i].fecha,argp->ultimasAlertas[i].hora,argp->ultimasAlertas[i].puntuacion);	

		}
		
	}
	printf("\n********************************************************************************");	

	
	return &result;
}