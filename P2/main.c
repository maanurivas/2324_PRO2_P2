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
/*
 * Objetivo:  Cambiar la categoria del participante, de basic a pro.
 * Entrada:   Un nombre de usuario (tipo tUserName) y la lista (tipo tListU).
 * Salida:    La confirmación de que se ha cambiado la categoría, o en su defecto,
 *            La confirmación de que no se ha encontrado el usuario en la lista.
 * Precondiciones: -
 * Postcondiciones: -
 */
void Play(tUserName userName, tSongTitle songTitle, tPlayTime playTime, tListU *U);
/*
Objetivo:  Reproducción de playTime (minutos) de una canción por parte de un usuario.
Entrada:   Un nombre de usuario (tipo tUserName), un nombre de cancion (tipo tSongTitle), el tiempo de reproduccion en minutos (tipo tPlayTime) y la lista(tipo tListU).
Salida:    La confirmación de que se ha reproducido la canción, o en su defecto,
           la confirmación de que no se ha encontrado el usuario en la lista.
Precondiciones: -
Postcondiciones: -
*/
void Stats(tListU U);
/*
Objetivo: Listar los usuarios actuales de MUSFIC y sus datos.
Entrada:  Una lista (tipo tListL)
Salida:   Todos los datos que se requiere mostrar, o error en caso de que no se puedan mostrar estadisticas.
Precondiciones: -
Postcondiciones: -
*/
void Remove(tPlayTime maxTime, tListU U);
/*
Objetivo: Elimina todos los usuarios basic cuyo contador de tiempo de reproducción exceda maxTime minutos.
Entrada:  Un maximo de minutos de reproducción (tipo tPlayTime) y la lista (tipo tListU)
Salida:   La confirmacion de que se han borrado todos los usuarios que excedan el tiempo máximo, o en su defect,
          la confirmación de que no se han eliminado o no hay usuarios que lo excedan.
Precondiciones: -
Postcondiciones: -
*/

char *UserCategory_to_char(tUserCategory category);
/*
Objetivo: Convierte el parametro introducido al programa (basic/pro) a tipo char
Entrada: Un elemento tUserCategory
Salida: Devuelve true en caso de que el parametro introducido sea "basic" o false en caso contrario
Precondiciones: Recibe basic o pro
Postcondiciones: -
*/

tUserCategory char_to_UserCategory(char param[]);
/*
Objetivo: Convierte el parametro introducido al programa ("basic"/"pro") a tipo tUserCategory
Entrada: Un elemento char
Salida: Devuelve true en caso de que el parametro introducido sea "basic" o false en caso contrario
Precondiciones: Recibe "basic" o "pro"
Postcondiciones: -
*/


void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListU *U) {

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
    tListU U;
    createEmptyListU(&U);
    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, &U);
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

char *UserCategory_to_char(tUserCategory category){
    return category ? "basic" : "pro";
}


tUserCategory char_to_UserCategory(char param[]){
    return (strcmp(param, "basic") == 0);
}



