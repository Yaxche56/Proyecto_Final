#include <stdio.h>

#define MAX_OYENTES 100
#define NUM_CANCIONES 10

// Prototipos de las funciones (una para cada inciso)
int leerYAlmacenarVotos(int votos[MAX_OYENTES][3]);
void calcularVotosCanciones(int votos[MAX_OYENTES][3], int num_oyentes, int *primera, int *segunda);
void calcularPremiosOyentes(int votos[MAX_OYENTES][3], int num_oyentes, int primera, int segunda);

int main() {
    // Matriz para almacenar las 3 canciones votadas por cada oyente
    int votos[MAX_OYENTES][3];
    int num_oyentes = 0;
    int primeraMostVotada = -1;
    int segundaMostVotada = -1;

    printf("--- PROYECTO FINAL: EMISORA DE RADIO ---\n\n");

    // 1. Leer y almacenar los votos
    num_oyentes = leerYAlmacenarVotos(votos);

    if (num_oyentes == 0) {
        printf("\nNo se registraron votos de oyentes.\n");
        return 0;
    }

    // 2. Calcular los votos por canción e identificar la 1ª y 2ª más votadas
    calcularVotosCanciones(votos, num_oyentes, &primeraMostVotada, &segundaMostVotada);

    // 3. Calcular puntos de los oyentes y determinar el ganador
    calcularPremiosOyentes(votos, num_oyentes, primeraMostVotada, segundaMostVotada);

    return 0;
}

/**
 * INCISO 1: Lee y almacena los votos emitidos por cada oyente.
 * Detiene la lectura si el primer dato del trío es -1.
 */
int leerYAlmacenarVotos(int votos[MAX_OYENTES][3]) {
    int i = 0;
    printf("Introduce las canciones de cada oyente (3 numeros por linea):\n");
    
    while (i < MAX_OYENTES) {
        printf("Oyente %d: ", i);
        scanf("%d", &votos[i][0]);
        
        // Condicion de parada: -1 en el primer dato
        if (votos[i][0] == -1) {
            // Leemos los otros dos datos obligatoriamente para limpiar el buffer de entrada
            scanf("%d %d", &votos[i][1], &votos[i][2]);
            break;
        }
        
        // Si no es -1, leemos los dos votos restantes del trio
        scanf("%d %d", &votos[i][1], &votos[i][2]);
        i++;
    }
    return i; // Retorna el total de oyentes que participaron efectivamente
}

/**
 * INCISO 2: Calcula los votos acumulados por cada canción (1º=3pts, 2º=2pts, 3º=1pt)
 * e identifica cuáles son las dos canciones más votadas.
 */
void calcularVotosCanciones(int votos[MAX_OYENTES][3], int num_oyentes, int *primera, int *segunda) {
    int puntos_canciones[NUM_CANCIONES] = {0}; // Inicializa el conteo de las 10 canciones en 0

    // Acumulación de puntos según la posición de preferencia
    for (int i = 0; i < num_oyentes; i++) {
        puntos_canciones[votos[i][0]] += 3; // 1er lugar recibe 3 puntos
        puntos_canciones[votos[i][1]] += 2; // 2do lugar recibe 2 puntos
        puntos_canciones[votos[i][2]] += 1; // 3er lugar recibe 1 punto
    }

    printf("\n--- RESULTADOS DE LAS CANCIONES ---\n");
    for (int i = 0; i < NUM_CANCIONES; i++) {
        printf("Cancion %d: %d votos\n", i, puntos_canciones[i]);
    }

    // Algoritmo para encontrar el 1º y 2º lugar con más puntos
    int max1 = -1;
    int max2 = -1;
    *primera = -1;
    *segunda = -1;

    for (int i = 0; i < NUM_CANCIONES; i++) {
        if (puntos_canciones[i] > max1) {
            max2 = max1;
            *segunda = *primera;
            
            max1 = puntos_canciones[i];
            *primera = i;
        } else if (puntos_canciones[i] > max2) {
            max2 = puntos_canciones[i];
            *segunda = i;
        }
    }

    printf("1ª cancion: %d\n", *primera);
    printf("2ª cancion: %d\n", *segunda);
}

/**
 * INCISO 3: Reparte los puntos a los oyentes según sus aciertos
 * y determina quién es el ganador del premio final.
 */
void calcularPremiosOyentes(int votos[MAX_OYENTES][3], int num_oyentes, int primera, int segunda) {
    int max_puntos_oyente = -1;
    int ganador = -1;

    printf("\n--- PUNTOS OBTENIDOS POR LOS OYENTES ---\n");
    for (int i = 0; i < num_oyentes; i++) {
        int puntos_totales = 0;
        int acerto_primera = 0;
        int acerto_segunda = 0;

        // Comprobamos si el oyente votó por las canciones ganadoras en cualquiera de sus 3 opciones
        for (int j = 0; j < 3; j++) {
            if (votos[i][j] == primera) {
                acerto_primera = 1;
            }
            if (votos[i][j] == segunda) {
                acerto_segunda = 1;
            }
        }

        // Aplicación de las reglas de puntuación del concurso
        if (acerto_primera) {
            puntos_totales += 30; // 30 puntos por incluir la 1ª más votada
        }
        if (acerto_segunda) {
            puntos_totales += 20; // 20 puntos por incluir la 2ª más votada
        }
        if (acerto_primera && acerto_segunda) {
            puntos_totales += 10; // 10 puntos suplementarios si acertó ambas
        }

        printf("Oyente %d: %d puntos\n", i, puntos_totales);

        // Actualizamos para encontrar al oyente con el puntaje más alto
        if (puntos_totales > max_puntos_oyente) {
            max_puntos_oyente = puntos_totales;
            ganador = i;
        }
    }

    printf("Ganador: el oyente numero %d\n", ganador);
}
