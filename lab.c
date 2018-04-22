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
  char species[21];
  unsigned short int age;
  char phone[21];
  unsigned short int atentions;
  char vaccines[3];
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
  clientesBultos = (struct Cliente*) calloc(*numeroRegistros, sizeof(struct Cliente));
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
/*Funcion que agrega el rut del dueño de un unico registro. Si se trata de un registro que no existe, el arreglo de clientes no se modifica.*/
struct Cliente* agregarRut(struct Cliente* clientes, int index, char* rut){
  if (index != -1){
    strcpy(clientes[index].run, rut);
  }
  return clientes;
}
/*Funcion que agrega un id a la mascota de un unico registro. Si se trata de un registro que no existe, el arreglo de clientes no se modifica.*/
struct Cliente* agregarID(struct Cliente* clientes, int index, char* id){
  if (index != -1){
    strcpy(clientes[index].id, id);
  }
  return clientes;
}
/*Funcion que crea el archivo de salida imprimiendo todo lo que tiene el arreglo de clientes.*/
void crearArchivo(struct Cliente* clientesBultos, int size){
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
      fprintf(file, "%s %s %s %s %s %hu %s %hu %s %s %s %s \n", clientesBultos[i].name , clientesBultos[i].sur1, clientesBultos[i].sur2, clientesBultos[i].pet, clientesBultos[i].species, clientesBultos[i].age, clientesBultos[i].phone, clientesBultos[i].atentions, clientesBultos[i].vaccines, clientesBultos[i].date, clientesBultos[i].run, clientesBultos[i].id);

    }
    fclose(file);
  }
}
/*Funcion que busca al cliente dado su nombre, apellidos y nombre de su mascota. Retorna el indice del cliente si lo encuentra, y -1 si no. Para esta funcion se asume que pueden haber clientes que tengan el mismo nombre y apellidos, pero en ese caso sus mascotas no se pueden llamar igual.*/
int getCliente(struct Cliente* clientes, int size, char* nombre, char* apellido, char* apellidoM, char* mascota, char* especie){
  int i, j;
  for (i = 0; i < size; i++){
    if ( strcmp(clientes[i].name, nombre) == 0){
      if (strcmp(clientes[i].sur1, apellido) == 0){
        if (strcmp(clientes[i].sur2, apellidoM) == 0){
          if (strcmp(clientes[i].pet, mascota) == 0){
            return j = i;
          }
          else{
            j = -1;
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
    continue;
  }
  return j;
}
/*Funcion que hace un arreglo con los Clientes que se quieren eliminar de los registros*/
struct Cliente* clientesAeliminar(int* size){
  int i;
  char line[MAXLINE];
  struct Cliente* clientesAborrar;
  printf("%s\n", "Ingrese la cantidad de clientes que desea eliminar de los registros.");
  fgets(line, sizeof(line), stdin);
  *size = atoi(line);
  clientesAborrar = (struct Cliente*)calloc(*size, sizeof(struct Cliente));
  for (i = 0; i < *size; i++){
    printf("%s\n", "Ingrese el cliente de la forma que esta en el archivo.");
    fgets(line, sizeof(line),stdin);
    sscanf(line, "%s %s %s %s %s %hu %s %hu %s %s", clientesAborrar[i].name , clientesAborrar[i].sur1, clientesAborrar[i].sur2, clientesAborrar[i].pet, clientesAborrar[i].species, &clientesAborrar[i].age, clientesAborrar[i].phone, &clientesAborrar[i].atentions, clientesAborrar[i].vaccines, clientesAborrar[i].date);
  }
  return clientesAborrar;
}
/*Funcion que revisa si un cliente esta dentro de un arreglo, en cuyo caso retorna el valor 1. Si no, retorna 0. Para esta funcion vale lo mismo que para getCliente, si dos clientes tienen el mismo nombre y apellido, no pueden tener mascotas del mismo nombre*/
int belongs(struct Cliente* clientesArevisar, struct Cliente cliente, int size){
  int i;
  for (i = 0; i < size; i++){
    if ( strcmp(clientesArevisar[i].name, cliente.name) == 0){
      if (strcmp(clientesArevisar[i].sur1, cliente.sur1) == 0){
        if (strcmp(clientesArevisar[i].sur2, cliente.sur2) == 0){
          if (strcmp(clientesArevisar[i].pet, cliente.pet) == 0){
            return 1;
          }
        }
      }
      else{
        i++;
      }
    }
    else{
      i++;
    }
  }
  return 0;
}
/*Funcion que se encarga de crear un arreglo nuevo, sin los clientes eliminados, los cuales se tienen registrados en otro arreglo. La memoria del arreglo original y del auxiliar para borrar se limpia antes de entregar el nuevo arreglo.*/
struct Cliente* eliminarClientes(struct Cliente* clientes, struct Cliente* clientesAborrar, int size, int size2, int* sizeN){
  if (size2 > size){
    printf("%s\n", "Ha habido un error, el arreglo de elementos a eliminar no puede ser mas grande que el arreglo original. El programa terminara.");
    freeArreglo(clientes);
    freeArreglo(clientesAborrar);
    exit(0);
  }
  else{
    int i;
    int j = 0;
    *sizeN = size -size2;
    struct Cliente* clientesNuevo;
    clientesNuevo = (struct Cliente*)calloc(*sizeN, sizeof(struct Cliente));
    while( j != (*sizeN)){
      for (i = 0; i < size; i++){
        if (belongs(clientesAborrar, clientes[i], size2) == 1){
          i++;
        }
        else{
          clientesNuevo[j] = clientes[i];
          j++;
        }
      }
    }
    freeArreglo(clientes);
    freeArreglo(clientesAborrar);
    for( i = 0; i < (size - size2); i++){
      printf("%s %s %s %s %s %hu %s %hu %s %s", clientesAborrar[i].name , clientesAborrar[i].sur1, clientesAborrar[i].sur2, clientesAborrar[i].pet, clientesAborrar[i].species, clientesAborrar[i].age, clientesAborrar[i].phone, clientesAborrar[i].atentions, clientesAborrar[i].vaccines, clientesAborrar[i].date);
    }
    return clientesNuevo;
  }
}
/*Funcion que agrega una cantidad de clientes, creando un arreglo nuevo donde copia los valores antiguos y pone tambien los nuevos*/
struct Cliente* agregarClientes(struct Cliente* clientes, int size, int* agregar, int* sizeN){
  char line[MAXLINE];
  printf("%s\n", "Ingrese el numero de clientes que desea agregar.");
  fgets(line, sizeof(line), stdin);
  *agregar = atoi(line);
  int i;
  *sizeN = *agregar + size;
  struct Cliente* nuevos;
  nuevos = (struct Cliente*)calloc(*sizeN, sizeof(struct Cliente));
  for (i = 0; i < *agregar; i++){
    printf("%s\n", "Ingrese el cliente de la forma que esta en el archivo.");
    fgets(line, sizeof(line),stdin);
    sscanf(line, "%s %s %s %s %s %hu %s %hu %s %s", nuevos[i].name , nuevos[i].sur1, nuevos[i].sur2, nuevos[i].pet, nuevos[i].species, &nuevos[i].age, nuevos[i].phone, &nuevos[i].atentions, nuevos[i].vaccines, nuevos[i].date);
  }
  for (i = 0; i < size; i++){
    strcpy(nuevos[i+*agregar].name, clientes[i].name);
    strcpy(nuevos[i+*agregar].sur1, clientes[i].sur1);
    strcpy(nuevos[i+*agregar].sur2, clientes[i].sur2);
    strcpy(nuevos[i+*agregar].pet, clientes[i].pet);
    strcpy(nuevos[i+*agregar].species, clientes[i].species);
    nuevos[i+*agregar].age = clientes[i].age;
    strcpy(nuevos[i+*agregar].phone, clientes[i].phone);
    nuevos[i+*agregar].atentions = clientes[i].atentions;
    strcpy(nuevos[i+*agregar].vaccines, clientes[i].vaccines);
    strcpy(nuevos[i+*agregar].date, clientes[i].date);
  }
  freeArreglo(clientes);
  return nuevos;
}


//TODO modificarRegistro

void menu(){
  struct Cliente* clientes;
  struct Cliente* clientes2;
  //struct Cliente* clientesNuevo;
  int size;
  //int eliminar;
  int sizeN;
  int agregar;
  clientes = crearArreglo(&size);
  clientes2 = agregarClientes(clientes, size, &agregar, &sizeN);
  //clientesNuevo = eliminarClientes(clientes, clientes2, size, eliminar, &sizeN);
  crearArchivo(clientes2, sizeN);
  freeArreglo(clientes2);
}

int main(int argc, char const *argv[]) {
  printf("\n\n%s\n\n", "****************COMIENZO PROGRAMA****************");
  menu();
  printf("\n\n%s\n\n", "****************TERMINO PROGRAMA****************");
  return 0;
}
