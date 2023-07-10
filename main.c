#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Alumnos
{
    int n_alumno;
    char* nombre;
    char* carrera;
    float* notas;
    float promedio;
};


void LeerArchivo(struct Alumnos* alumnos);
void NuevoArchivo(struct Alumnos* alumnos);

int main(){

    struct Alumnos alumnos[5];

    LeerArchivo(alumnos);

    NuevoArchivo(alumnos);

    return 0;
}

void LeerArchivo(struct Alumnos* alumnos) {
    FILE* archivo;
    char linea[100], nombre[25], carrera[25];
    int n_alumno;
    float notas[3];

    archivo = fopen("alumnos.txt", "r+");

    for (int i = 0; i < 5; i++) {
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            linea[strcspn(linea, "\n")] = '\0';
            sscanf_s(linea, "%d;%25[^;];%25[^;];%f;%f;%f;", &n_alumno, nombre, sizeof(nombre), carrera, sizeof(carrera), &notas[0], &notas[1], &notas[2]);
            alumnos[i].n_alumno = n_alumno;
            alumnos[i].nombre = strdup(nombre);
            alumnos[i].carrera = strdup(carrera);
            memcpy(alumnos[i].notas, notas, sizeof(notas));
            alumnos[i].promedio = (notas[0] + notas[1] + notas[2]) / 3;
        } else {
            printf("Error al leer la linea del estudiante %d.\n", i + 1);
        }
    }

    fclose(archivo);
}

void NuevoArchivo(struct Alumnos* alumnos) {
    FILE* archivo;

    archivo = fopen("alumnosDest.txt", "w+");

    for (int i = 4; i >= 0; i--) {
        fprintf_s(archivo, "%d;%s;%s;%f;%f;%f;%f\n", alumnos[i].n_alumno, alumnos[i].nombre, alumnos[i].carrera, alumnos[i].notas[0], alumnos[i].notas[1], alumnos[i].notas[2], alumnos[i].promedio);
    }

    fclose(archivo);
}
