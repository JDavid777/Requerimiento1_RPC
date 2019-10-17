/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "alertas.h"

bool_t
xdr_Indicadores (XDR *xdrs, Indicadores *objp)
{
	register int32_t *buf;

	 if (!xdr_float (xdrs, &objp->frecuenciaCardiaca))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->frecuenciaRespiratoria))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->presionArterialSistolica))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->presionArterialDiastolica))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->temperatura))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->saturacionOxigeno))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Paciente (XDR *xdrs, Paciente *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nombres, MAXNOM,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->edad))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->numHabitacion))
		 return FALSE;
	 if (!xdr_Indicadores (xdrs, &objp->indicadores))
		 return FALSE;
	return TRUE;
}
