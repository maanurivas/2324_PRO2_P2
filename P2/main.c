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
void Remove(tPlayTime maxTime, tListU *U);
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
            printf("********************\n"
                   "%s %c: user %s category %s\n",commandNumber, command,param1,param2);
            New(param1, char_to_UserCategory(param2),U);
            break;
        case 'D':
            printf("********************\n"
                   "%s %c: user %s\n",commandNumber, command,param1);
            Delete(param1,U);
            break;
        case 'A':
            printf("********************\n"
                   "%s %c: user %s song %s\n",commandNumber,command,param1,param2);
            Add(param1,param2,U);
            break;
        case 'U':
            printf("********************\n"
                   "%s %c: user %s\n",commandNumber, command,param1);
            Upgrade(param1,U);
            break;
        case 'P':
            printf("********************\n"
                   "%s %c: user %s song %s minutes %s\n",commandNumber, command,param1,param2,param3);
            Play(param1,param2, atoi(param3),U);
            break;
        case 'S':
            printf("********************\n"
                   "%s %c:\n",commandNumber, command);
            Stats(*U);
            break;
        case 'R':
            printf("********************\n"
                   "%s %c: maxtime %s\n",commandNumber, command,param1);
            Remove(atoi(param1),U);
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


void New(tUserName userName, tUserCategory userCategory, tListU *U){
    tItemU ITEM;
    bool insertado;
    char* UserCategory;//variables auxiliares para trabajar sobre ellas

    if(findItemU(userName, *U) != NULLU){//comprobamos si el participante ya está en la lista
        printf("+ Error: New not possible\n");//Error al realizar New, participante ya dado de alta
    } else{
        strcpy(ITEM.userName,userName);//copiamos el dato del nombre en el nombre del nuevo
        ITEM.userCategory=userCategory;//asignamos su categoria a la variable correspondiente
        ITEM.totalPlayTime=0;
        createEmptyListS(&ITEM.songList);
        insertado = insertItemU(ITEM, U);//insertamos el usuario
        if(!insertado){
            printf("+ Error: New not possible\n");
        } else{//con el usuario ya insertado
            if(ITEM.userCategory){//comprobamos la categoría del usuario para imprimir correctamente la categoría del usuario
                UserCategory = "basic";
            } else{
                UserCategory = "pro";
            }

            printf("* New: user %s category %s\n", ITEM.userName, UserCategory);//impresion por pantalla
        }
    }
}

void Delete(tUserName userName, tListU *U){
    tPosU p;
    tItemU auxITEM;
    char *UserCategory;
    //variables auxiliares para trabajar sobre ellas

    p = findItemU(userName, *U);//Buscamos el nombre
    if(p==NULLU){//No esta en la lista o está vacía
        printf("+ Error: Delete not possible\n");
    } else{//Está en la lista
        auxITEM = getItemU(p, *U);//Obtenemos el user
        if(auxITEM.userCategory){//comprobamos la categoria del usuario
            UserCategory = "basic";
        } else{
            UserCategory = "pro";
        }
        deleteAtPositionU(p, U);//lo eliminamos
        printf("* Delete: user %s category %s totalplaytime %d\n", userName, UserCategory, auxITEM.totalPlayTime);//imprimimos lo solicitado
    }
}

void Upgrade(tUserName userName, tListU *U){
    tPosU p;
    tItemU auxITEM;//variables auxiliares para trabajar sobre ellas

    p = findItemU(userName, *U);//buscamos el item
    if(p==NULLU){//comprobamos si está en la lista
        printf("+ Error: Upgrade not possible\n");
    } else{
        auxITEM = getItemU(p, *U);//caso en el que la categoría ya es pro
        if (strcmp(UserCategory_to_char(auxITEM.userCategory),"pro")==0) {//comprobamos que su categoría no es pro usando una función auxiliar para pasar a char los userCategory
            printf("+ Error: Upgrade not possible\n");
        } else{//está en la lista
            auxITEM.userCategory=char_to_UserCategory("pro"); // Pasamos la categoría a "pro"
            updateItemU(auxITEM, p, U); // Actualiza el usuario en la lista
            printf("* Upgrade: user %s category %s\n", userName, UserCategory_to_char(auxITEM.userCategory));//Imprimimos por pantalla
        }
    }
}

void Add(tUserName userName, tSongTitle songTitle, tListU *U){
    tPosU p;
    tItemU ITEM;
    bool insertado;
    tItemS auxSong;

    if(isEmptyListU(*U)){//COMPROBAMOS QUE LA LISTA NO ESTÉ VACÍA
        printf("+ Error: Add not possible\n");
    } else {
        p= findItemU(userName,*U);
        if (p == NULLU) {//COMPROBAMOS QUE EL USUARIO SE ENCUENTRE EN LA LISTA
            printf("+ Error: Add not possible\n");
        }
        ITEM = getItemU(p, *U);
        if (findItemS(songTitle, ITEM.songList) != NULLS) {//COMPROBAMOS QUE LA CANCIÓN NO EXISTA
            printf("+ Error: Add not possible\n");
        } else {
            strcpy(auxSong.songTitle,songTitle);//copiamos el dato del titulo de la cancion en el nombre del elemento a insertar
            auxSong.playTime=0;//asignamos el playtime a 0
            insertado=insertItemS(auxSong, NULLS, &ITEM.songList);
            if (!insertado) {
                printf("+ Error: Add not possible\n");
            } else {
                updateItemU(ITEM,p,U);
                printf("* Add: user %s adds song %s\n", userName, auxSong.songTitle);
            }
        }
    }
}

void Play(tUserName name, tSongTitle  title, tPlayTime playTime, tListU *U) {
    tPosU p;
    tItemU auxUSER;//variables auxiliares para trabajar sobre ellas
    tPosS q;
    tItemS auxSONG;

    if (isEmptyListU(*U)) {//COMPROBAMOS QUE LA LISTA NO ESTÉ VACÍA
        printf("+ Error: Play not possible\n");
    }
    p= findItemU(name,*U);
    if (p == NULLU) {//COMPROBAMOS QUE EL USUARIO SE ENCUENTRE EN LA LISTA
        printf("+ Error: Play not possible\n");
    }
    auxUSER = getItemU(p, *U);
    if(isEmptyListS(auxUSER.songList)){//COMPROBAMOS QUE LA LISTA DE CANCIONES NO ESTÉ VACIA
        printf("+ Error: Play not possible\n");
    } else{
        q= findItemS(title,auxUSER.songList);
        auxSONG= getItemS(q,auxUSER.songList);
        auxSONG.playTime=auxSONG.playTime+playTime;
        updateItemS(auxSONG,q,&auxUSER.songList);
        auxUSER.totalPlayTime=auxUSER.totalPlayTime+auxSONG.playTime;
        updateItemU(auxUSER,p,U);
        printf("* Play: user %s plays song %s playtime %d totalplaytime %d\n",name,title,playTime,auxUSER.totalPlayTime);
    }
}


void Remove(tPlayTime maxTime, tListU *U){
    tItemU auxUSER;
    tPosU p;

    if(isEmptyListU(*U)){
        printf("+ Error: Remove not possible\n");
    }
    p= firstU(*U);
    auxUSER = getItemU(p,*U);
    while (p!=NULLU && p<= lastU(*U)){
        if(strcmp(UserCategory_to_char(auxUSER.userCategory),"basic")==0 && auxUSER.totalPlayTime>maxTime){
            printf("Removing user %s totalplaytime %d\n",auxUSER.userName,auxUSER.totalPlayTime);
            for (tPosS i= firstS(auxUSER.songList); nextS(i,auxUSER.songList)!=NULLS;i= nextS(i,auxUSER.songList)){
                deleteAtPositionS(i,&auxUSER.songList);
            }
            deleteAtPositionU(p,U);
        } else{
            p = nextU(p,*U);
        }
        if (p!=NULLU){
            auxUSER = getItemU(p,*U);
        }
    }
}


void Stats(tListU U){
    tPosU p;
    tItemU auxUSER;
    tItemS auxSONG;
    int cntBasic=0, cntPro=0, minsBasic=0, minsPro=0;
    float mediaBasic=0.0f, mediaPro=0.0f;

    if(isEmptyListU(U)){//compruebo si está vacia
        printf("+ Error: Stats not possible\n");
    } else{
        for(p= firstU(U);p!=NULLU;p= nextU(p,U)){//recorro la lista de usuarios
            auxUSER = getItemU(p,U);//obtengo el usuario
            if(strcmp(UserCategory_to_char(auxUSER.userCategory),"basic")==0){//compruebo la categoria del usuario y aumento los contadores
                cntBasic=cntBasic+1;
                minsBasic+=auxUSER.totalPlayTime;
            } else{
                cntPro=cntPro+1;
                minsPro+=auxUSER.totalPlayTime;
            }
            printf("User %s category %s totalplaytime %d\n",auxUSER.userName,UserCategory_to_char(auxUSER.userCategory),auxUSER.totalPlayTime);
            if(isEmptyListS(auxUSER.songList)){
                printf("No songs\n");
            } else {
                for (tPosS i= firstS(auxUSER.songList); i!= NULLS; i=nextS(i,auxUSER.songList)) {
                    auxSONG = getItemS(i,auxUSER.songList);
                    printf("Song %s playtime %d\n",auxSONG.songTitle,auxSONG.playTime);
                }
            }printf("\n");
        }
        if(cntBasic==0){
            mediaBasic = 0.0f;
        } else{
            mediaBasic= (float)minsBasic/(float)cntBasic;
        }
        if(cntPro==0){
            mediaPro = 0.0f;
        } else{
            mediaPro= (float)minsPro/(float)cntPro;
        }
        printf("Category  Users  TimePlay  Average\n");
        printf("Basic     %5d %9d %8.2f\n",cntBasic,minsBasic,mediaBasic);
        printf("Pro       %5d %9d %8.2f\n",cntPro,minsPro,mediaPro);
    }
}
