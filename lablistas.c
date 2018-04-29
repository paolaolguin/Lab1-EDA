#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


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
  char run[14];
  char id[14];
};
struct nodo{
	struct nodo *siguiente;
	struct Cliente cliente;
};
struct lista{
	struct nodo *inicial;
	struct nodo *final;
	int cantidad;
};
enum {OK, NULLPOINTER} stat;

#define MAXLINE 200

/*Funcion que inicializa el centinela, puntero que apunta al principio y al final de la lista*/
struct lista *crearLista(void){
  struct lista *centinela = NULL;
  centinela = (struct lista *)calloc(1, sizeof(struct lista));
  return centinela;
}
/*Funcion que crea un nuevo nodo, agregando su cliente.*/
struct nodo *nuevoNodo(struct Cliente client){
  struct nodo *nuevo = NULL;
  nuevo = (struct nodo*)calloc(1, sizeof(struct nodo));
  nuevo->cliente = client;
  nuevo->siguiente = NULL;
  return nuevo;
}
/*Funcion que agrega un nodo a la lista.*/
short int agregarNodo(struct lista *centinela, struct nodo *node){
  if (centinela == NULL || node == NULL){
    return -1;
  }
  if (centinela->inicial == NULL){
    centinela->inicial = node;
    centinela->final = node;
    centinela->cantidad++;
    return 1;
  }
  struct nodo *temp = NULL;
  temp = centinela->inicial;
  while (temp->siguiente != NULL){
    temp = temp->siguiente; 
  }
  temp->siguiente = node;
  centinela->final = node;
  centinela->cantidad++;
  return 1;
}
/*Funcion que crea un cliente a partir de un string. Para evitar errores, run e id, cosas que no estan en el archivo, se inician como strings vacios.*/
struct Cliente crearCliente(char* line){
  struct Cliente client;
  strcpy(client.run, "");
  strcpy(client.id, "");
  sscanf(line, "%s %s %s %s %s %hu %s %hu %s %s", client.name, client.sur1, client.sur2, client.pet, client.species, &client.age, client.phone, &client.atentions, client.vaccines, client.date);
  return client;
}
/*Funcion que lee el archivo y arma la lista*/
short int leerArchivo(struct lista *centinela){
  FILE* file;
  file = fopen("Bultos.in", "r");
  if (file == NULL){
    return -1;
  }
  char line[MAXLINE];
  unsigned int cantidad;
  unsigned int index;
  struct nodo *temp = NULL;
  struct Cliente client;
  fgets(line, sizeof(line), file);
  cantidad = atoi(line);
  for (index = 0; index < cantidad; index++){
    fgets(line, sizeof(line), file);
    client = crearCliente(line);
    temp = nuevoNodo(client);
    agregarNodo(centinela, temp);
  }
  fclose(file);
  return 1;
}
/*Funcion que busca un nodo dada su posicion*/
struct nodo *buscarNodo(struct lista *centinela, unsigned int posicion){
  if (centinela == NULL || posicion >= centinela->cantidad){
    return NULL;
  }
  int index;
  struct nodo *temp = NULL;
  temp = centinela->inicial;
  for (index = 0; index < posicion; index++){
    temp = temp->siguiente;
  }
  return temp;
}
/*Funcion que elimina un unico nodo dada su posicion*/
short int removerNodo(struct lista *centinela, unsigned int posicion){
  if (centinela == NULL || posicion >= centinela->cantidad){
    return -1;
  }
  struct nodo *temp = NULL;
  struct nodo *exiliado = NULL;
  if (posicion == 0){
    exiliado = centinela->inicial;
    temp = exiliado->siguiente;
    centinela->inicial = temp;
    free(exiliado);
    exiliado = NULL;
    return 1;
  }
  int index;
  temp = centinela->inicial;
  for (index = 0; index < posicion - 1; index++){
    temp = temp->siguiente;
  }
  exiliado = temp->siguiente;
  temp->siguiente = exiliado->siguiente;
  if (posicion == centinela->cantidad -1){
    centinela->final = temp;
  }
  centinela->cantidad--;
  free(exiliado);
  exiliado = NULL;
  return 1;
}
/*Funcion que se encarga de liberar la memoria, se limita a ir unicamente eliminando el primer elemento de la lista, hasta que ya no tenga elementos.*/
short int freeLista(struct lista *centinela){
	if(centinela == NULL)
		return -1;
	unsigned int cantidad = centinela->cantidad;
	unsigned int index;
	for(index = 0; index < cantidad; index++)
		removerNodo(centinela,0);
	return 1;
}
/*Funcion que imprime la lista en un archivo. Retorna el numero de datos impresos*/
unsigned int printLista(struct lista *centinela, FILE *file){
  if (centinela == NULL){
    return 0;
  }
  struct nodo *temp = NULL;
  unsigned int cantidad = centinela->cantidad;
  temp = centinela->inicial;
  while (temp != NULL){
    fprintf(file, "%s %s %s %s %s %hu %s %hu %s %s %s %s\n", temp->cliente.name, temp->cliente.sur1, temp->cliente.sur2, temp->cliente.pet, temp->cliente.species, temp->cliente.age, temp->cliente.phone, temp->cliente.atentions, temp->cliente.vaccines, temp->cliente.date, temp->cliente.run, temp->cliente.id);
    temp = temp->siguiente;
  }
  return cantidad;
}
/*Funcion que crea el archivo de salida*/
short int crearArchivo(struct lista *centinela){
  FILE* file;
  file = fopen("Bultos.out", "w");
  if (file == NULL){
    return -1;
  }
  printLista(centinela, file);
  fclose(file);
  return 1;
}
/*Funcion que consigue el indice de un cliente, dado el string como aparece en el archivo de entrada*/
int getCliente(char* string, struct lista *centinela){
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
  sscanf(string, "%s %s %s %s %s %hu %s %hu %s %s", name, sur1, sur2, pet, species, &age, phone, &atentions, vaccines, date);
  unsigned int index;
  struct nodo *temp = NULL;
  temp = centinela->inicial;
  for (index = 0; index < centinela->cantidad; index++){
    if ( strcmp(temp->cliente.name, name) == 0 && strcmp(temp->cliente.sur1, sur1) == 0 && strcmp(temp->cliente.sur2, sur2) == 0 && strcmp(temp->cliente.pet, pet) == 0 && strcmp(temp->cliente.species, species) == 0 && ( temp->cliente.age == age) && strcmp(temp->cliente.phone, phone) == 0 && ( temp->cliente.atentions == atentions) && strcmp(temp->cliente.vaccines, vaccines) == 0 && strcmp(temp->cliente.date, date) == 0 ){
      return index;
    }
    temp = temp->siguiente;
  }
  return -1;
}
/*Funcion menu que recibe un entero que luego se evalua en modificar*/
short int menuModificacion(){
  char line[MAXLINE];
  int numero;
  printf("%s\n", "Que le gustaria cambiar de este Cliente? 0, nombre, 1, apellido paterno, 2 apellido materno, 3 nombre de la mascota, 4 especie de la mascota, 5 edad de la mascota, 6 vacunas, 7 telefono, 8 proxima fecha de atencion, 9 si desea agregar un rut, y 10 si desea agregar id.");
  fgets(line, sizeof(line), stdin);
  numero = atoi(line);
  return numero;
}
/*Funcion que modifica un cliente*/
void modificar(struct lista *centinela, unsigned int posicion){
  struct nodo *temp = NULL;
  char line[MAXLINE];
  char nombre[21];
  char apellido[31];
  char opcion[3];
  char fecha[11];
  char rutid[13];
  int index = 0;

  temp = buscarNodo(centinela, posicion);

  short int menu = menuModificacion();
  switch (menu){
    case 0:
    printf("%s\n", "Ingrese el nombre corregido, recuerde que tiene un largo maximo de 20.");
    fgets(nombre, sizeof(nombre), stdin);
    while(index  != 21 && nombre[index++] != '\n');
    nombre[index - 1] = '\0';
    strcpy(temp->cliente.name, nombre);
    break;
  case 1:
    printf("%s\n", "Ingrese el apellido paterno corregido, recuerde que tiene un largo maximo de 30.");
    fgets(apellido, sizeof(apellido), stdin);
    while(index  != 21 && apellido[index++] != '\n');
    apellido[index - 1] = '\0';
    strcpy(temp->cliente.sur1, apellido);
    break;
  case 2:
    printf("%s\n", "Ingrese el apellido materno corregido, recuerde que tiene un largo maximo de 30.");
    fgets(apellido, sizeof(apellido), stdin);
    while(index  != 31 && apellido[index++] != '\n');
    apellido[index - 1] = '\0';
    strcpy(temp->cliente.sur2, apellido);
    break;
  case 3:
    printf("%s\n", "Ingrese el nombre de la mascota corregido, recuerde que tiene un largo maximo de 20.");
    fgets(nombre, sizeof(nombre), stdin);
    while(index  != 31 && nombre[index++] != '\n');
    nombre[index - 1] = '\0';
    strcpy(temp->cliente.pet, nombre);
    break;
  case 4:
    printf("%s\n", "Ingrese la especie de la mascota corregida, recuerde que tiene un largo maximo de 20.");
    fgets(nombre, sizeof(nombre), stdin);
    while(index  != 31 && nombre[index++] != '\n');
    nombre[index - 1] = '\0';
    strcpy(temp->cliente.species, nombre);
    break;
  case 5:
    printf("%s\n", "Ingrese la edad de la mascota corregida.");
    fgets(line, sizeof(line), stdin);
    temp->cliente.age = atoi(line);
    break;
  case 6:
    printf("%s\n", "Ingrese la correcion sobre si la mascota tiene sus vacunas al dia o no. Recuerde que el largo maximo de esto es 2 (si o no)");
    fgets(opcion, sizeof(opcion), stdin);
    while(index  != 31 && opcion[index++] != '\n');
    opcion[index - 1] = '\0';
    strcpy(temp->cliente.vaccines, opcion);
    break;
  case 7:
    printf("%s\n", "Ingrese el telefono de contacto del cliente corregido. Recuerde que tiene un largo maximo de 20.");
    fgets(nombre, sizeof(nombre), stdin);
    while(index  != 21 && nombre[index++] != '\n');
    nombre[index - 1] = '\0';
    strcpy(temp->cliente.phone, nombre);
    break;
  case 8:
    printf("%s\n", "Ingrese la proxima fecha de atencion corregida. Recuerde que esta en el formato DD/MM/YYYY y que, por lo mismo, su largo maximo es de 10.");
    fgets(fecha, sizeof(fecha), stdin);
    while(index  != 11 && fecha[index++] != '\n');
    fecha[index - 1] = '\0';
    strcpy(temp->cliente.date, fecha);
    break;
  case 9:
    printf("%s\n", "Ingrese el rut, con puntos y guiones. por ejemplo: 11.111.111-1");
    fgets(rutid, sizeof(rutid), stdin);
    while(index  != 14 && rutid[index++] != '\n');
    rutid[index - 1] = '\0';
    strcpy(temp->cliente.run, rutid);
    break;
  case 10:
    printf("%s\n", "Ingrese el id, que tiene el mismo formato que un rut con puntos y guiones. por ejemplo: 11.111.111-1");
    fgets(rutid, sizeof(rutid), stdin);
    while(index  != 14 && rutid[index++] != '\n');
    rutid[index - 1] = '\0';
    strcpy(temp->cliente.run, rutid);
    break;
  default:
    printf("%s\n", "Opcion no valida, el programa terminara.");
    exit(0);
  }

}
/*Funcion que agrega un nuevo cliente a la lista*/
short int agregarCliente(struct lista *centinela){
  short int result;
  char string[MAXLINE];
  printf("%s\n", "Ingrese el cliente de la misma forma que se encuentra en el archivo de entrada.");
  fgets(string, sizeof(string), stdin);
  struct nodo *nuevo = NULL;
  struct Cliente client = crearCliente(string);
  nuevo = nuevoNodo(client);
  result = agregarNodo(centinela, nuevo);
  return result;
}
int *arregloPosiciones(struct lista *centinela, int* arr, int size){
  char line[MAXLINE];
  unsigned int i;
  for (i = 0; i < size; i++){
    printf("Ingrese el cliente numero %d con el mismo formato que se encuentra en el archivo de entrada.\n", i);
    fgets(line, sizeof(line), stdin);
    arr[i] = getCliente(line, centinela);
  }
  return arr;
}

void menu(){
  char line[MAXLINE];
  short int opcion;
  short int control;
  int *cant;
  unsigned int size;
  unsigned int index;
  struct Cliente client;
  struct nodo *node = NULL;
  time_t inicio, fin, inicioA, finA, inicioM, finM, inicioE, finE;
  inicio = time(NULL);
  struct lista *lista = crearLista();
  leerArchivo(lista);
  fin = time(NULL);
  printf("Tiempo en crear la lista = %f\n\n", difftime(fin, inicio));
  printf("%s\n", "Bienvenido al programa de listas de la Veterinaria El Bulto Feliz. Con este programa puede modificar registros (0), agregarlos (1) o eliminarlos (2). Que desea hacer? Para cada vez que se le de una opcion, si ingresa un valor no valido, el programa terminara.");
  fgets(line, sizeof(line), stdin);
  opcion = atoi(line);
  switch (opcion) {
    case 0:
      printf("%s\n", "Ha decidido modificar registros existentes. Desde aqui puede cambiar cualquier valor que el cliente tenga, ademas de poder agregar rut o id. Cuantos datos desea modificar?");
      fgets(line, sizeof(line), stdin);
      inicioM = time(NULL);
      size = atoi(line);
      cant = (int*)calloc(size, sizeof(int));

      cant = arregloPosiciones(lista, cant, size);

      for (index = 0; index < size; index++){
        if (cant[index] == -1){
          printf("El indice de este cliente no es valido. Esto significa que el cliente no esta en la lista, por lo que no se podra modificar.\n");
          continue;
        }
        printf("Para el cliente numero %d: \n", index);
        modificar(lista, cant[index]);
      }
      free(cant);
      cant = NULL;
      crearArchivo(lista);
      finM = time(NULL);
      printf("Tiempo en crear solucion tras modificar %f\n", difftime(finM, inicioM));
      freeLista(lista);
      printf("%s\n", "Si todo salio como debe, en la carpeta donde se encuentra este programa habra un archivo llamado Bultos.out con las modificaciones pertinentes.");
      break;
    case 1:
      printf("%s\n", "Ha decidido agregar nuevos registros a los existentes. Desde aqui puede agregar un cliente, con el formato que se encuentra en el archivo de entrada. Cuantos datos desea agregar?");
      fgets(line, sizeof(line), stdin);
      inicioA = time(NULL);
      size = atoi(line);
      for (index = 0; index < size; index++){
        fgets(line, sizeof(line), stdin);
        client = crearCliente(line);
        node = nuevoNodo(client);
        control = agregarNodo(lista, node);
        if (control == -1){
          printf("%s\n", "Paso algo y no se pudo agregar el cliente.");
          continue;
        }
      }
      crearArchivo(lista);
      finA = time(NULL);
      printf("Tiempo en crear solucion tras agregar %f\n", difftime(finA, inicioA));
      freeLista(lista);
      printf("%s\n", "Si todo salio como debe, en la carpeta donde se encuentra este programa habra un archivo llamado Bultos.out con las modificaciones pertinentes.");
      break;
    case 2:
      printf("%s\n", "Ha decidido eliminar registros. Cuantos datos desea borrar?");
      inicioE = time(NULL);
      fgets(line, sizeof(line), stdin);
      size = atoi(line);
      if (size >= lista->cantidad){
        printf("%s\n", "No se pueden eliminar mas clientes que los que se tienen. El programa terminara");
        exit(0);
      }
      cant = (int*)calloc(size, sizeof(int));
      cant = arregloPosiciones(lista, cant, size);
      for (index = 0; index < size; index++){
        control = removerNodo(lista, cant[index]);
        if (control == -1){
          printf("%s\n", "Hubo un error y no se pudo eliminar ese cliente.");
          continue;
        }
      }
      free(cant);
      cant = NULL;
      finE = time(NULL);
      printf("Tiempo en crear solucion eliminando = %f\n", difftime(finE, inicioE));
      crearArchivo(lista);
      freeLista(lista);
      printf("%s\n", "Si todo salio como debe, en la carpeta donde se encuentra este programa habra un archivo llamado Bultos.out con las modificaciones pertinentes.");
      break;
    default:
        printf("%s\n", "El valor ingresado no es valido. Se terminara el programa");
        exit(0);

  }

}

int main(int argc, char const *argv[]) {
  printf("\n\n%s\n\n", "****************COMIENZO PROGRAMA****************");
  menu();
  printf("\n\n%s\n\n", "****************TERMINO PROGRAMA****************");
  return 0;
}
