#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	logger = log_create("tp0.log", "MiPrograma", true, LOG_LEVEL_INFO);

	if (logger == NULL) {
		printf("Error: No se pudo crear el Logger.\n");
		return 1;
	}

	log_info(logger, "Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	// Loggeamos el valor de config

	config = config_create("cliente.config");
	if (config == NULL) {
		logger = log_create("tp0.log", "config_create:", true, LOG_LEVEL_INFO);
		log_info(logger, "Error: No se pudo cargar el archivo de configuración.\n");
	}

	if (config_has_property(config, "CLAVE"))
	{
		valor = config_get_string_value(config, "CLAVE");
	}

	if (config_has_property(config, "IP")){
		ip = config_get_string_value(config, "IP");
	}

	if (config_has_property(config, "PUERTO")){
		puerto = config_get_string_value(config, "PUERTO");
	}

	logger = log_create("tp0.log", "VALOR:", true, LOG_LEVEL_INFO);
	log_info(logger, valor);
	logger = log_create("tp0.log", "IP:", true, LOG_LEVEL_INFO);
	log_info(logger, ip);
	logger = log_create("tp0.log", "PUERTO:", true, LOG_LEVEL_INFO);
	log_info(logger, puerto);

	/* ---------------- LEER DE CONSOLA ---------------- */

	// leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);


	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente

	// log_destroy(logger);
	
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	while(true){
		// La primera te la dejo de yapa
		leido = readline("> ");

		// El resto, las vamos leyendo y logueando hasta recibir un string vacío
		// ¡No te olvides de liberar las lineas antes de regresar!

		if (leido[0] == '\0') {
			return;
		}

		logger = log_create("tp0.log", "Linea:", true, LOG_LEVEL_INFO);
		log_info(logger, leido);
	}
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();
	
	// Leemos y esta vez agregamos las lineas al paquete

	while(true){
		// La primera te la dejo de yapa
		leido = readline("> ");

		// El resto, las vamos leyendo y logueando hasta recibir un string vacío
		// ¡No te olvides de liberar las lineas antes de regresar!

		if (leido[0] == '\0') {
			return;
		}

		agregar_a_paquete(paquete, leido, strlen(leido) + 1 );
		enviar_paquete(paquete, conexion);
	}

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
	eliminar_paquete(paquete);
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
  	liberar_conexion(conexion);
	free(logger);
	free(config);

}
