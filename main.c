#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Alumnos {
    int n_alumno;
    char nombre[25];
    char carrera[25];
    float notas[3];
    float promedio;
};

void LeerArchivo(struct Alumnos* alumnos);
void NuevoArchivo(const struct Alumnos* alumnos);

int main() {
    struct Alumnos alumnos[5];

    LeerArchivo(alumnos);
    NuevoArchivo(alumnos);

    return 0;
}

void LeerArchivo(struct Alumnos* alumnos) {
    FILE* archivo;
    char linea[100];
    int n_alumno;

    archivo = fopen("alumnos.txt", "r+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo alumnos.txt\n");
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            sscanf(linea, "%d;%24[^;];%24[^;];%f;%f;%f",
                   &n_alumno, alumnos[i].nombre, alumnos[i].carrera,
                   &alumnos[i].notas[0], &alumnos[i].notas[1], &alumnos[i].notas[2]);
            alumnos[i].n_alumno = n_alumno;
            alumnos[i].promedio = (alumnos[i].notas[0] + alumnos[i].notas[1] + alumnos[i].notas[2]) / 3;
        } else {
            printf("Error al leer la línea del estudiante %d.\n", i + 1);
        }
    }

    fclose(archivo);
}

void NuevoArchivo(const struct Alumnos* alumnos) {
    FILE* archivo;

    archivo = fopen("alumnosDest.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo alumnosDest.txt.\n");
        exit(1);
    }

    for (int i = 4; i >= 0; i--) {
        fprintf(archivo, "%d;%s;%s;%f;%f;%f;%f\n",
                alumnos[i].n_alumno, alumnos[i].nombre, alumnos[i].carrera,
                alumnos[i].notas[0], alumnos[i].notas[1], alumnos[i].notas[2], alumnos[i].promedio);
    }

    fclose(archivo);
}