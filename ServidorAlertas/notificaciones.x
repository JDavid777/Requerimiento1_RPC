const MAXMSJ = 100;


struct InfoPaciente{

	char nombres[MAXMSJ];
    char apellidos[MAXMSJ];
	char edad[MAXMSJ];
	int numHabitacion;
    char hora[MAXMSJ];
    char fecha[MAXMSJ];
};

struct IndicadoresAlerta{
    char indicador[MAXMSJ];
    float valor;
};

struct UltimasAlertas{
    char fecha[MAXMSJ];
    char hora[MAXMSJ];
    int puntuacion;
};

struct AlertaGenerada{
    InfoPaciente paciente;
    IndicadoresAlerta indicadoresAlerta[5];
    char mensaje[MAXMSJ];
    UltimasAlertas ultimasAlertas[5];
};


program gestion_notificaciones{
    version gestion_notificaiones_version{
        bool enviarNotificacion(AlertaGenerada objAlertaGenerada)=1;
}=2;
}=0x20000002;
