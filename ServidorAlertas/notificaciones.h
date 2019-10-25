/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _NOTIFICACIONES_H_RPCGEN
#define _NOTIFICACIONES_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAXMSJ 100

struct InfoPaciente {
	char nombres[MAXMSJ];
	char apellidos[MAXMSJ];
	char edad[MAXMSJ];
	int numHabitacion;
	char hora[MAXMSJ];
	char fecha[MAXMSJ];
};
typedef struct InfoPaciente InfoPaciente;

struct IndicadoresAlerta {
	char indicador[MAXMSJ];
	float valor;
};
typedef struct IndicadoresAlerta IndicadoresAlerta;

struct UltimasAlertas {
	char fecha[MAXMSJ];
	char hora[MAXMSJ];
	int puntuacion;
};
typedef struct UltimasAlertas UltimasAlertas;

struct AlertaGenerada {
	InfoPaciente paciente;
	IndicadoresAlerta indicadoresAlerta[5];
	char mensaje[MAXMSJ];
	UltimasAlertas ultimasAlertas[5];
};
typedef struct AlertaGenerada AlertaGenerada;

#define gestion_notificaciones 0x20000002
#define gestion_notificaiones_version 2

#if defined(__STDC__) || defined(__cplusplus)
#define enviarNotificacion 1
extern  bool_t * enviarnotificacion_2(AlertaGenerada *, CLIENT *);
extern  bool_t * enviarnotificacion_2_svc(AlertaGenerada *, struct svc_req *);
extern int gestion_notificaciones_2_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define enviarNotificacion 1
extern  bool_t * enviarnotificacion_2();
extern  bool_t * enviarnotificacion_2_svc();
extern int gestion_notificaciones_2_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_InfoPaciente (XDR *, InfoPaciente*);
extern  bool_t xdr_IndicadoresAlerta (XDR *, IndicadoresAlerta*);
extern  bool_t xdr_UltimasAlertas (XDR *, UltimasAlertas*);
extern  bool_t xdr_AlertaGenerada (XDR *, AlertaGenerada*);

#else /* K&R C */
extern bool_t xdr_InfoPaciente ();
extern bool_t xdr_IndicadoresAlerta ();
extern bool_t xdr_UltimasAlertas ();
extern bool_t xdr_AlertaGenerada ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_NOTIFICACIONES_H_RPCGEN */
