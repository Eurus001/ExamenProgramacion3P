#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct de alumnos
struct Alumnos {
    int n_alumno;
    char nombre[25];
    char carrera[25];
    float notas[3];
    float promedio;
};

//Declaracion variables
void LeerArchivo(struct Alumnos* alumnos);
void NuevoArchivo(const struct Alumnos* alumnos);

//Main (solo llama funciones)
int main() {
    struct Alumnos alumnos[5];

    LeerArchivo(alumnos);
    NuevoArchivo(alumnos);

    return 0;
}

//Funcion que lee los datos y los guarda en el aaray de structs de alumnos
void LeerArchivo(struct Alumnos* alumnos) {
    FILE* archivo;
    char linea[100];
    int n_alumno;

    //Abre archivo
    archivo = fopen("alumnos.txt", "r+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo alumnos.txt\n");
        exit(1);
    }

    //Lee cada linea
    for (int i = 0; i < 5; i++) {
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            sscanf(linea, "%d;%24[^;];%24[^;];%f;%f;%f",
                   &n_alumno, alumnos[i].nombre, alumnos[i].carrera,
                   &alumnos[i].notas[0], &alumnos[i].notas[1], &alumnos[i].notas[2]); //ingresa las notas
            alumnos[i].n_alumno = n_alumno;
            alumnos[i].promedio = (alumnos[i].notas[0] + alumnos[i].notas[1] + alumnos[i].notas[2]) / 3; //Promedio
        } else {
            printf("Error al leer la línea del estudiante %d.\n", i + 1);
        }
    }

    //cierra cada archivo
    fclose(archivo);
}

void NuevoArchivo(const struct Alumnos* alumnos) {
    FILE* archivo;

    //Crea archivo
    archivo = fopen("alumnosDest.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo alumnosDest.txt.\n");
        exit(1);
    }

    //Escribe el nuevo archivo
    for (int i = 4; i >= 0; i--) {
        fprintf(archivo, "%d;%s;%s;%f;%f;%f;%f\n",
                alumnos[i].n_alumno, alumnos[i].nombre, alumnos[i].carrera,
                alumnos[i].notas[0], alumnos[i].notas[1], alumnos[i].notas[2], alumnos[i].promedio);
    }

    fclose(archivo);
}