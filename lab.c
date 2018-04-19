#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLINE 200

/*El enunciado dice que un nombre tiene un largo maximo de 20 caracteres, pero se tiene que considerar el caracter nulo al final del string, por lo que se considera un caracter mas en caso que el nombre tenga 20 letras */
struct Cliente{
  char name[21];
  char sur1[31];
  char sur2[31];
  char pet[21];
  char species[21];//4
  unsigned short int age;//5
  char phone[21];//6
  unsigned short int atentions;//7
  char vaccines[3]; // si/no 8
  char date[11];
  char run[11];
  char id[11];
};

enum {OK, NULLPOINTER} stat;

/*Funcion que crea un arreglo de estructuras, recibe un puntero a int donde se guarda el tamaño del arreglo para futuros usos.*/
struct Cliente* crearArreglo(int* numeroRegistros){
  struct Cliente* clientesBultos;
  FILE* file;
  file = fopen("Bultos.in", "r");
  if (file == NULL){
    stat = NULLPOINTER;
    return NULL;
  }
  char line[MAXLINE];
  fgets(line, sizeof(line), file);
  *numeroRegistros = atoi(line);
  clientesBultos = (struct Cliente*) malloc(sizeof(struct Cliente)*(*numeroRegistros));
  int i = 0;
  while(fgets(line, sizeof(line), file)!= NULL){
    fprintf(stdout,"%s",line);
    sscanf(line, "%s %s %s %s %s %hu %s %hu %s %s", clientesBultos[i].name , clientesBultos[i].sur1, clientesBultos[i].sur2, clientesBultos[i].pet, clientesBultos[i].species, &clientesBultos[i].age, clientesBultos[i].phone, &clientesBultos[i].atentions, clientesBultos[i].vaccines, clientesBultos[i].date);
    i++;
  }
  fclose(file);
  return clientesBultos;
}
/*Funcion que libera la memoria ocupada por el arreglo de estructuras*/
void freeArreglo(struct Cliente* clientes){
  free(clientes);
  clientes = NULL;
}
/*Funcion que agrega el rut del dueño a un registro*/
struct Cliente* agregarRut(struct Cliente* clientes, char* rut, char* nombre, char* apellido, char* apellidoM, char* mascota, int size){
  int i;
  for (i = 0; i < size; i++){
    if (strcmp(clientes[i].name, nombre) == 0){
      if (strcmp(clientes[i].sur1, apellido) == 0){
        if (strcmp(clientes[i].sur2, apellidoM) == 0){
          if (strcmp(clientes[i].pet, mascota)== 0){
            strcpy(clientes[i].run, rut);
          }
        }
        else{
          continue;
        }
      }
      else{
        continue;
      }
    }
    else{
      continue;
    }
  }
  return clientes;
}
/*Funcion que agrega un id a la mascota en un registro*/
//TODO encontrar una forma de arreglar el resto de los ids y ruts para que no se imprima basura al ponerlos en el archivo
struct Cliente* agregarID(struct Cliente* clientes, char* id, char* nombre, char* apellido, char* apellidoM, char* mascota, int size){
  int i;
  for (i = 0; i < size; i++){
    if ( strcmp(clientes[i].name, nombre) == 0){
      if (strcmp(clientes[i].sur1, apellido) == 0){
        if (strcmp(clientes[i].sur2, apellidoM) == 0){
          if (strcmp(clientes[i].pet, mascota) == 0){
            strcpy(clientes[i].id, id);
          }
          else{
            continue;
          }
        }
        else{
          continue;
        }
      }
      else{
        continue;
      }
    }
    else{
      continue;
    }
  }
  return clientes;
}
//TODO eliminar, agregarRegistro, modificarRegistro, crearArchivo
/*void crearArchivo(struct Cliente* clientes, int size){
//TODO hacer esto una vez que arrgle lo de arriba
  FILE* file;
  file = fopen("Bultos.out", "w");
  if (file == NULL){
    stat = NULLPOINTER;
    printf("%s\n", "Ha habido un error, no se pudo crear el archivo de salida. El programa terminara.");
    exit(0);
  }
  else{
    int i;
    for (i = 0; i < size; i++){
      fprintf(file, "%s \n", );

    }

  }
}
*/

void menu(){
  struct Cliente* clientes;
  int size;
  clientes = crearArreglo(&size);
  //esto es una prueba
  clientes = agregarID(clientes, "11.111.111-2" ,"Susana", "Torio", "Grande", "Albondiga", size);
  printf("%s\n", clientes[0].id);
  //aca termina la prueba
  freeArreglo(clientes);


}

int main(int argc, char const *argv[]) {
  printf("\n\n%s\n\n", "****************COMIENZO PROGRAMA****************");
  menu();
  printf("\n\n%s\n\n", "****************TERMINO PROGRAMA****************");
  return 0;
}
