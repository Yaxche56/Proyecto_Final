#include <stdio.h>

#define MAX_OYENTES 100
#define NUM_CANCIONES 10

// --- PROTOTIPOS DE LAS FUNCIONES ---
int leerVotos(int votos[][3]);
void calcularVotosCanciones(int votos[][3], int num_oyentes, int puntaje_canciones[], int *primera, int *segunda);
void determinarGanador(int votos[][3], int num_oyentes, int primera, int segunda);


// --- FUNCIÓN PRINCIPAL ---
int main() {
    int matriz_votos[MAX_OYENTES][3];
    int puntajes_canciones[NUM_CANCIONES];
    int total_oyentes;
    int primera_cancion, segunda_cancion;

    printf("--- CONCURSO DE LA EMISORA DE RADIO ---\n\n");

    // 1. Ejecutar Inciso 1: Leer y almacenar los datos
    total_oyentes = leerVotos(matriz_votos);

    // Validar si al menos un oyente votó antes de procesar los resultados
    if (total_oyentes > 0) {
        
        // 2. Ejecutar Inciso 2: Calcular estadísticas de canciones
        calcularVotosCanciones(matriz_votos, total_oyentes, puntajes_canciones, &primera_cancion, &segunda_cancion);

        // 3. Ejecutar Inciso 3: Repartir puntos a los oyentes y elegir al ganador
        determinarGanador(matriz_votos, total_oyentes, primera_cancion, segunda_cancion);

    } else {
        printf("\nNo se registraron votos válidos. Saliendo del programa.\n");
    }

    return 0;
}


// --- DESARROLLO DE LAS FUNCIONES ---

// Inciso 1: Leer y almacenar los votos emitidos por cada oyente
int leerVotos(int votos[][3]) {
    int num_oyentes = 0;
    int c1, c2, c3;

    printf("Ingresa las 3 canciones de cada oyente separadas por espacios (ejemplo: 6 2 1).\n");
    printf("Para finalizar el registro, ingresa -1 en la primera opcion.\n\n");
    
    while (num_oyentes < MAX_OYENTES) {
        printf("Oyente %d: ", num_oyentes);
        scanf("%d", &c1);
        
        // Si el primer dato es -1, se detiene la captura de datos inmediatamente
        if (c1 == -1) {
            break;
        }
        
        // Si no es -1, lee las otras dos opciones del trío
        scanf("%d %d", &c2, &c3);

        votos[num_oyentes][0] = c1;
        votos[num_oyentes][1] = c2;
        votos[num_oyentes][2] = c3;
        num_oyentes++;
    }
    
    return num_oyentes; // Retorna la cantidad total de oyentes que participaron
}


// Inciso 2: Calcular los votos de las canciones y definir el 1er y 2do lugar
void calcularVotosCanciones(int votos[][3], int num_oyentes, int puntaje_canciones[], int *primera, int *segunda) {
    int i;
    int max1 = -1;
    int max2 = -1;
    
    // Inicializar el arreglo de puntajes de canciones en 0
    for (i = 0; i < NUM_CANCIONES; i++) {
        puntaje_canciones[i] = 0;
    }

    // Sumar puntos según la preferencia (1er lugar = 3pts, 2do lugar = 2pts, 3er lugar = 1pt)
    for (i = 0; i < num_oyentes; i++) {
        puntaje_canciones[votos[i][0]] += 3; 
        puntaje_canciones[votos[i][1]] += 2; 
        puntaje_canciones[votos[i][2]] += 1; 
    }

    // Mostrar en pantalla la sumatoria de votos por canción
    printf("\n=========================================\n");
    printf(" RESULTADOS DE LAS CANCIONES (INCISO 2) \n");
    printf("=========================================\n");
    for (i = 0; i < NUM_CANCIONES; i++) {
        printf("Cancion %d: %d votos\n", i, puntaje_canciones[i]);
    }

    // Buscar las dos canciones con los puntajes más altos (1ra y 2da)
    *primera = -1;
    *segunda = -1;

    for (i = 0; i < NUM_CANCIONES; i++) {
        if (puntaje_canciones[i] > max1) {
            max2 = max1;
            *segunda = *primera;
            max1 = puntaje_canciones[i];
            *primera = i;
        } else if (puntaje_canciones[i] > max2) {
            max2 = puntaje_canciones[i];
            *segunda = i;
        }
    }

    printf("\n1ª cancion mas votada: %d\n", *primera);
    printf("2ª cancion mas votada: %d\n", *segunda);
}


// Inciso 3: Repartir puntos a los oyentes y encontrar al ganador oficial
void determinarGanador(int votos[][3], int num_oyentes, int primera, int segunda) {
    int puntaje_oyentes[MAX_OYENTES];
    int max_puntos = -1;
    int ganador = -1;
    int i, j;

    printf("\n=========================================\n");
    printf("  PUNTAJES DE LOS OYENTES (INCISO 3)   \n");
    printf("=========================================\n");
    
    for (i = 0; i < num_oyentes; i++) {
        int tiene_primera = 0;
        int tiene_segunda = 0;
        puntaje_oyentes[i] = 0;

        // Validar si las canciones ganadoras se encuentran en las elecciones del oyente
        for (j = 0; j < 3; j++) {
            if (votos[i][j] == primera) {
                tiene_primera = 1;
            }
            if (votos[i][j] == segunda) {
                tiene_segunda = 1;
            }
        }

        // Aplicar reglas de asignación de puntos
        if (tiene_primera) {
            puntaje_oyentes[i] += 30;
        }
        if (tiene_segunda) {
            puntaje_oyentes[i] += 20;
        }
        if (tiene_primera && tiene_segunda) {
            puntaje_oyentes[i] += 10;
        }

        printf("Oyente %d: %d puntos\n", i, puntaje_oyentes[i]);

        // Registrar cuál oyente va liderando el puntaje máximo
        if (puntaje_oyentes[i] > max_puntos) {
            max_puntos = puntaje_oyentes[i];
            ganador = i;
        }
    }

    // Imprimir el veredicto final
    if (ganador != -1) {
        printf("\n¡GANADOR DEL CONCURSO!: El oyente numero %d con un total de %d puntos.\n", ganador, max_puntos);
    }
}
