/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Ana Gomez Mesias LOGIN 1: ana.gmesias@udc.es
 * AUTHOR 2: Manuel Rivas Capeans LOGIN 2: m.rivas.capeans@udc.es
 * GROUP: 3.3
 * DATE: 18 / 03 / 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "user_list.h"

#define MAX_BUFFER 255

void New(tUserName userName, tUserCategory userCategory, tListU *U);
/*
Objetivo: Crea un nuevo usuario en la lista de usuarios de la plataforma MUSFIC, con su nombre,
          y categoría.
Entrada: Un nombre(tipo tUserName), una categoría (tipo tUserCategory) y la lista (tListU).
Salida:  La confirmación de que se ha creado correctamente el nuevo elemento, o en su defecto,
         la confirmación de que no se ha podido crear o que el usuario no existe.
Precondiciones: -
Postcondiciones: -
*/

void Delete(tUserName userName, tListU *U);
/*
Objetivo: Eliminar a un usuario de la lista, eliminando también todas sus reproducciones.
Entrada:  Un nombre de usuario (tipo tUserName) y la lista de usuarios (tipo tListU).
Salida:   La confirmación de que se ha eliminado al usuario introducido, o en su defecto,
          (si el usuario no estaba en la lista) un error de eliminacion.
Precondiciones: -
Postcondiciones: -
*/

void Add(tUserName userName, tSongTitle songTitle, tListU *U);
/*
Objetivo: Añadir una canción al usuario correspondiente, en su correspondiente lista de
          canciones.
Entrada: Un nombre de usuario (tipo tUserName), el nombre de la canción (tipo tSongTitle)
         y la lista de usuarios (tipo tListU).
Salida:  La confirmación de que se ha añadido la canción en la lista correspondiente,
         o en su defecto, (si el usuario no estaba en la lista) un error de eliminacion.
Precondiciones: -
Postcondiciones: -
 */

void Upgrade(tUserName userName, tListU *U);
void Play(tUserName userName, tSongTitle songTitle, tPlayTime playTime, tListU *U);
void Stats(tListU U);
void Remove(tPlayTime maxTime, tListU U);



void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3) {

    switch (command) {
        case 'N':
            printf("Command: %s %c %s %s\n", commandNumber, command, param1, param2);
            break;
        case 'D':
            break;
        case 'A':
            break;
        case 'U':
            break;
        case 'P':
            break;
        case 'S':
            break;
        case 'R':
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}
