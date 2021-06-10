#include "tecladoMatricial.h"

char tecladoTL04[NUM_COLUMNAS_TECLADO][NUM_FILAS_TECLADO] = { { '1', '2', '3',
		'C' }, { '4', '5', '6', 'D' }, { '7', '8', '9', 'E' }, { 'A', '0', 'B',
		'F' } };

// Maquina de estados: lista de transiciones
// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
fsm_trans_t fsm_trans_excitacion_columnas[] = { { TECLADO_ESPERA_COLUMNA,
		CompruebaTimeoutColumna, TECLADO_ESPERA_COLUMNA, TecladoExcitaColumna },
		{ -1, NULL, -1, NULL }, };

fsm_trans_t fsm_trans_deteccion_pulsaciones[] = { { TECLADO_ESPERA_TECLA,
		CompruebaTeclaPulsada, TECLADO_ESPERA_TECLA, ProcesaTeclaPulsada }, {
		-1, NULL, -1, NULL }, };

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaTeclado(TipoTeclado *p_teclado) {

	if (wiringPiSetupGpio() < 0) {
		fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
		return;
	}

	// Comenzamos excitacion por primera columna
	p_teclado->columna_actual = COLUMNA_1;

	// Inicialmente no hay tecla pulsada
	p_teclado->teclaPulsada.col = -1;
	p_teclado->teclaPulsada.row = -1;

	pinMode(GPIO_KEYBOARD_ROW_1, INPUT);
	pullUpDnControl(GPIO_KEYBOARD_ROW_1, PUD_DOWN);
	wiringPiISR(GPIO_KEYBOARD_ROW_1, INT_EDGE_RISING, teclado_fila_1_isr);

	pinMode(GPIO_KEYBOARD_ROW_2, INPUT);
	pullUpDnControl(GPIO_KEYBOARD_ROW_2, PUD_DOWN);
	wiringPiISR(GPIO_KEYBOARD_ROW_2, INT_EDGE_RISING, teclado_fila_2_isr);

	pinMode(GPIO_KEYBOARD_ROW_3, INPUT);
	pullUpDnControl(GPIO_KEYBOARD_ROW_3, PUD_DOWN);
	wiringPiISR(GPIO_KEYBOARD_ROW_3, INT_EDGE_RISING, teclado_fila_3_isr);

	pinMode(GPIO_KEYBOARD_ROW_4, INPUT);
	pullUpDnControl(GPIO_KEYBOARD_ROW_4, PUD_DOWN);
	wiringPiISR(GPIO_KEYBOARD_ROW_4, INT_EDGE_RISING, teclado_fila_4_isr);

	pinMode(GPIO_KEYBOARD_COL_1, OUTPUT);
	digitalWrite(GPIO_KEYBOARD_COL_1, HIGH);

	pinMode(GPIO_KEYBOARD_COL_2, OUTPUT);
	digitalWrite(GPIO_KEYBOARD_COL_2, LOW);

	pinMode(GPIO_KEYBOARD_COL_3, OUTPUT);
	digitalWrite(GPIO_KEYBOARD_COL_3, LOW);

	pinMode(GPIO_KEYBOARD_COL_4, OUTPUT);
	digitalWrite(GPIO_KEYBOARD_COL_4, LOW);

	p_teclado->tmr_duracion_columna = tmr_new(timer_duracion_columna_isr);
	tmr_startms((tmr_t*) (p_teclado->tmr_duracion_columna),
	TIMEOUT_COLUMNA_TECLADO);

	printf("\nSystem init complete! keypad ready to process the code!!!\n");
	fflush(stdout);

	return 0;
}

//------------------------------------------------------
// OTROS PROCEDIMIENTOS PROPIOS DE LA LIBRERIA
//------------------------------------------------------

void ActualizaExcitacionTecladoGPIO(int columna) {
	// A completar por el alumno
	// ...
	switch (columna) {
	// ...
	}
}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaTimeoutColumna(fsm_t *this) {
	int result = 0;
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*) (this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_TIMEOUT_COLUMNA_TECLADO);
	piUnlock(SYSTEM_FLAGS_KEY);

	return result;
}

int CompruebaTeclaPulsada(fsm_t *this) {
	int result = 0;
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*) (this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_TECLA_PULSADA);
	piUnlock(SYSTEM_FLAGS_KEY);

	return result;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LAS MAQUINAS DE ESTADOS
//------------------------------------------------------

void TecladoExcitaColumna(fsm_t *this) {
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*) (this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TIMEOUT_COLUMNA_TECLADO;
	piUnlock(SYSTEM_FLAGS_KEY);

	// Llamada a ActualizaExcitacionTecladoGPIO con columna a activar como argumento
}

void ProcesaTeclaPulsada(fsm_t *this) {
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*) (this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);
}

//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void teclado_fila_1_isr(void) {
	// A completar por el alumno
	// ...
}

void teclado_fila_2_isr(void) {
	// A completar por el alumno
	// ...
}

void teclado_fila_3_isr(void) {
	// A completar por el alumno
	// ...
}

void teclado_fila_4_isr(void) {
	// A completar por el alumno
	// ...
}

void timer_duracion_columna_isr(union sigval value) {
	// A completar por el alumno
	// ...
}
