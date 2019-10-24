const MAXNOM = 30;

struct Indicadores{

	float frecuenciaCardiaca;
    float frecuenciaRespiratoria;
    float presionArterialSistolica;
    float presionArterialDiastolica;
    float temperatura;
    float saturacionOxigeno;

};
struct Paciente{

	char nombres[MAXNOM];
	char apellidos[MAXNOM];
	char edad[MAXNOM];
	int numHabitacion;
	Indicadores indicadores;
};

program gestion_alertas{

	version gestion_alertas_version{
		bool enviarIndicadores(Paciente objPaciente)=1;
	}=1;

}=0x20000001;


