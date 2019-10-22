const MAXMSJ = 70;


struct InfoPaciente{

	char nombres[MAXMSJ];
	char edad[MAXMSJ];
	int numHabitacion;
    char hora[10];
    char fecha[50];
};

struct IndicadoresAlerta{
    char indicador[MAXMSJ];
    float valor;
};

struct UltimasAlertas{
    char fecha[50];
    char hora[10];
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
