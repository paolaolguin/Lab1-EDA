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
  char run[14];
  char id[14];
};

enum {OK, NULLPOINTER} stat;
/*Funcion que crea un cliente a partir de un string. Para evitar errores, run e id, cosas que no estan en el archivo, se inician como strings vacios.*/
struct Cliente crearCliente(char* line){
  struct Cliente client;
  strcpy(client.run, "");
  strcpy(client.id, "");
  sscanf(line, "%s %s %s %s %s %hu %s %hu %s %s", client.name, client.sur1, client.sur2, client.pet, client.species, &client.age, client.phone, &client.atentions, client.vaccines, client.date);
  return client;
}
/*Funcion que entrega la posicion de un cliente en el arreglo. En el caso de que no lo encuentre, retorna -1*/
int getCliente(char* string, struct Cliente *clientes, int size){
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
  for (index = 0; index < size; index++){
	if ( strcmp(clientes[index].name, name) == 0 && strcmp(clientes[index].sur1, sur1) == 0 && strcmp(clientes[index].sur2, sur2) == 0 && strcmp(clientes[index].pet, pet) == 0 && strcmp(clientes[index].species, species) == 0 && ( clientes[index].age == age) && strcmp(clientes[index].phone, phone) == 0 && ( clientes[index].atentions == atentions) && strcmp(clientes[index].vaccines, vaccines) == 0 && strcmp(clientes[index].date, date) == 0 ){
	  return index;
	}
  }
  return -1;
}
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
/*Funcion que agrega una cantidad de clientes, creando un arreglo nuevo donde copia los valores antiguos y pone tambien los nuevos*/
struct Cliente* agregarClientes(struct Cliente *clientes, int size, int* agregar, int* sizeN){
  char line[MAXLINE];
  printf("%s\n", "Ingrese el numero de clientes que desea agregar.");
  fgets(line, sizeof(line), stdin);
  *agregar = atoi(line);
  int i;
  *sizeN = *agregar + size;
  struct Cliente* nuevos;
  nuevos = (struct Cliente*)calloc(*sizeN, sizeof(struct Cliente));
  for (i = 0; i < *agregar; i++){
	printf("Ingrese el cliente %d de la forma que esta en el archivo.\n", i);
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
/*Funcion que crea un arreglo con las posiciones de los clientes que se desean modificar o eliminar*/
int *arregloPosiciones(struct Cliente *clientes, int* arr, int size, int cantidadaModificar){
  char line[MAXLINE];
  unsigned int i;
  for (i = 0; i < cantidadaModificar; i++){
	printf("Ingrese el cliente numero %d con el mismo formato que se encuentra en el archivo de entrada.\n", i);
	fgets(line, sizeof(line), stdin);
	arr[i] = getCliente(line, clientes, size);
  }
  return arr;  
}
/*Funcion que entrega un arreglo nuevo sin los clientes que se quisieron eliminar*/
struct Cliente *eliminarClientes(struct Cliente *clientes, int size, int *posiciones, int cantidadEliminados){
  if (cantidadEliminados > size){
	printf("%s\n", "No se pueden eliminar mas datos que los que hay en el arreglo. El programa terminara.");
	exit(0);
  }
  int nuevoTamano = size - cantidadEliminados;
  struct Cliente *salvados = (struct Cliente*)calloc(nuevoTamano, sizeof(struct Cliente));
  unsigned int index;
  unsigned int indexPos;
  for (index = 0; index < nuevoTamano; index++){
	for (indexPos = 0; indexPos < cantidadEliminados; indexPos++){
	  if (indexPos == -1){
		printf("%s\n", "Hay una posicion que no es valida. Se va a omitir.");
		continue;
	  }
	  if (index != posiciones[indexPos]){
		salvados[size-index] = clientes[index];
	  }
	} 
  }
  freeArreglo(clientes);
  free(posiciones);
  return salvados;
}
/*Menu para las modificaciones.*/
short int menuModificacion(){
  char line[MAXLINE];
  int numero;
  printf("Que le gustaria cambiar del cliente? 0, nombre, 1, apellido paterno, 2 apellido materno, 3 nombre de la mascota, 4 especie de la mascota, 5 edad de la mascota, 6 vacunas, 7 telefono, 8 proxima fecha de atencion, 9 si desea agregar un rut, y 10 si desea agregar id.\n");
  fgets(line, sizeof(line), stdin);
  numero = atoi(line);
  return numero;
}
/*Funcion que modifica los clientes pedidos por el usuario.*/
void modificar(struct Cliente *clientes, int size, int *posiciones, int cantidadModificados){

  if (cantidadModificados > size){
	printf("%s\n", "No se pueden modificar mas elementos que los que hay en el arreglo. El programa terminara.");
	exit(0);
  }
  char line[MAXLINE];
  char nombre[21];
  char apellido[31];
  char opcion[3];
  char fecha[11];
  char rutid[14];
  int index = 0;
  int indice;
  short int menu;

  for (indice = 0; indice < cantidadModificados; indice++){
  	printf("Para el cliente numero %d\n", indice);
	if (posiciones[indice] == -1){
	  printf("%s\n", "Hay una posicion no valida. Se omitira.");
	  continue;
	}
	menu = menuModificacion();
	switch (menu){
	  case 0:
	  printf("%s\n", "Ingrese el nombre corregido, recuerde que tiene un largo maximo de 20.");
	fgets(nombre, sizeof(nombre), stdin);
	while(index  != 21 && nombre[index++] != '\n');
	nombre[index - 1] = '\0';
	strcpy(clientes[indice].name, nombre);
	break;
  case 1:
	printf("%s\n", "Ingrese el apellido paterno corregido, recuerde que tiene un largo maximo de 30.");
	fgets(apellido, sizeof(apellido), stdin);
	while(index  != 21 && apellido[index++] != '\n');
	apellido[index - 1] = '\0';
	strcpy(clientes[indice].sur1, apellido);
	break;
  case 2:
	printf("%s\n", "Ingrese el apellido materno corregido, recuerde que tiene un largo maximo de 30.");
	fgets(apellido, sizeof(apellido), stdin);
	while(index  != 31 && apellido[index++] != '\n');
	apellido[index - 1] = '\0';
	strcpy(clientes[indice].sur2, apellido);
	break;
  case 3:
	printf("%s\n", "Ingrese el nombre de la mascota corregido, recuerde que tiene un largo maximo de 20.");
	fgets(nombre, sizeof(nombre), stdin);
	while(index  != 31 && nombre[index++] != '\n');
	nombre[index - 1] = '\0';
	strcpy(clientes[indice].pet, nombre);
	break;
  case 4:
	printf("%s\n", "Ingrese la especie de la mascota corregida, recuerde que tiene un largo maximo de 20.");
	fgets(nombre, sizeof(nombre), stdin);
	while(index  != 31 && nombre[index++] != '\n');
	nombre[index - 1] = '\0';
	strcpy(clientes[indice].species, nombre);
	break;
  case 5:
	printf("%s\n", "Ingrese la edad de la mascota corregida.");
	fgets(line, sizeof(line), stdin);
	clientes[indice].age = atoi(line);
	break;
  case 6:
	printf("%s\n", "Ingrese la correcion sobre si la mascota tiene sus vacunas al dia o no. Recuerde que el largo maximo de esto es 2 (si o no)");
	fgets(opcion, sizeof(opcion), stdin);
	while(index  != 31 && opcion[index++] != '\n');
	opcion[index - 1] = '\0';
	strcpy(clientes[indice].vaccines, opcion);
	break;
  case 7:
	printf("%s\n", "Ingrese el telefono de contacto del cliente corregido. Recuerde que tiene un largo maximo de 20.");
	fgets(nombre, sizeof(nombre), stdin);
	while(index  != 21 && nombre[index++] != '\n');
	nombre[index - 1] = '\0';
	strcpy(clientes[indice].phone, nombre);
	break;
  case 8:
	printf("%s\n", "Ingrese la proxima fecha de atencion corregida. Recuerde que esta en el formato DD/MM/YYYY y que, por lo mismo, su largo maximo es de 10.");
	fgets(fecha, sizeof(fecha), stdin);
	while(index  != 11 && fecha[index++] != '\n');
	fecha[index - 1] = '\0';
	strcpy(clientes[indice].date, fecha);
	break;
  case 9:
	printf("%s\n", "Ingrese el rut, con puntos y guiones. por ejemplo: 11.111.111-1");
	fgets(rutid, sizeof(rutid), stdin);
	while(index  != 14 && rutid[index++] != '\n');
	rutid[index - 1] = '\0';
	strcpy(clientes[indice].run, rutid);
	break;
  case 10:
	printf("%s\n", "Ingrese el id, que tiene el mismo formato que un rut con puntos y guiones. por ejemplo: 11.111.111-1");
	fgets(rutid, sizeof(rutid), stdin);
	while(index  != 14 && rutid[index++] != '\n');
	rutid[index - 1] = '\0';
	strcpy(clientes[indice].id, rutid);
	break;
  default:
	printf("%s\n", "Opcion no valida, el programa terminara.");
	exit(0);
	}
  }
}

void menu(){
  time_t inicio, fin, inicioA, finA, inicioM, finM, inicioE, finE;
  char line[MAXLINE];
  short int opcion;
  short int control;
  int *aModificar;
  int cantidadEliminados;
  unsigned int sizeModificar;
  unsigned int sizeOriginal;
  unsigned int nuevoTamano;
  unsigned int index;
  struct Cliente client;
  inicio = time(NULL);
  struct Cliente *clientes = crearArreglo(&sizeOriginal);
  fin = time(NULL);
  printf("Tiempo que demora en crear el arreglo: %f\n\n", difftime(fin, inicio));
  struct Cliente *clientesNuevos;
  printf("%s\n", "Bienvenido al programa de arreglos de la Veterinaria El Bulto Feliz. Con este programa puede modificar registros (0), agregarlos (1) o eliminarlos (2). Que desea hacer? Para cada vez que se le de una opcion, si ingresa un valor no valido, el programa terminara.");
  fgets(line, sizeof(line), stdin);
  opcion = atoi(line);
  switch (opcion){
	case 0:
	  printf("%s\n", "Ha decidido modificar registros existentes. Desde aqui puede cambiar cualquier valor que el cliente tenga, ademas de poder agregar rut o id. Cuantos datos desea modificar?");
	  fgets(line, sizeof(line), stdin);
	  inicioM = time(NULL);
	  sizeModificar = atoi(line);
	  if (sizeModificar > sizeOriginal){
	  	printf("%s\n", "No se pueden modificar mas clientes que los que hay en el archivo de entrada. El programa se terminara.");
	  	exit(0);
	  }
	  aModificar = (int*)calloc(sizeModificar, sizeof(int));
	  aModificar = arregloPosiciones(clientes, aModificar, sizeOriginal, sizeModificar);
	  for (index = 0; index < sizeModificar; index++){
		if (aModificar[index] == -1){
		  printf("El indice de este cliente no es valido. Esto significa que el cliente no esta en la lista, por lo que no se podra modificar.\n");
		  continue;
		}
	  }
	  modificar(clientes, sizeOriginal, aModificar, sizeModificar);
	  free(aModificar);
	  crearArchivo(clientes, sizeOriginal);
	  finM = time(NULL);
	  printf("Tiempo que demora en entregar solución tras modificar.: %f\n\n", difftime(finM, inicioM));
	  freeArreglo(clientes);
	  printf("%s\n", "Si todo salio como debe, en la carpeta donde se encuentra este programa habra un archivo llamado Bultos.out con las modificaciones pertinentes.");
	  break;
	case 1:
	  printf("%s\n", "Ha decidido agregar nuevos registros a los existentes. Desde aqui puede agregar un cliente, con el formato que se encuentra en el archivo de entrada. Cuantos datos desea agregar?");
	  fgets(line, sizeof(line), stdin);
	  inicioA = time(NULL);
	  sizeModificar = atoi(line);
	  nuevoTamano = sizeModificar + sizeOriginal;
	  clientesNuevos = (struct Cliente*)calloc(nuevoTamano, sizeof(struct Cliente));
	  for (index = 0; index < sizeModificar; index++){
	  	printf("Ingrese el cliente numero %d con el formato del archivo de entrada.\n", index);
		fgets(line, sizeof(line), stdin);
		client = crearCliente(line);
		clientesNuevos[index] = client;
	  }
	  for (index = 0; index < sizeOriginal; index++){
		clientesNuevos[index+sizeModificar] = clientes[index];
	  }
	  crearArchivo(clientesNuevos, nuevoTamano);
	  finA = time(NULL);
	  printf("Tiempo que demora en crear solucion tras agregar: %f\n\n", difftime(finA, inicioA));
	  freeArreglo(clientes);
	  freeArreglo(clientesNuevos);
	  printf("%s\n", "Si todo salio como debe, en la carpeta donde se encuentra este programa habra un archivo llamado Bultos.out con las modificaciones pertinentes.");
	  break;
	case 2:
	  printf("%s\n", "Ha decidido eliminar registros. Cuantos datos desea borrar?");
	  fgets(line, sizeof(line), stdin);
	  inicioE = time(NULL);
	  cantidadEliminados = atoi(line);
	  aModificar = (int*)calloc(cantidadEliminados, sizeof(int));
	  aModificar = arregloPosiciones(clientes, aModificar, sizeOriginal, cantidadEliminados);
	  clientesNuevos = eliminarClientes(clientes, sizeOriginal, aModificar, cantidadEliminados);
	  nuevoTamano = sizeOriginal - cantidadEliminados;
	  crearArchivo(clientesNuevos, nuevoTamano);
	  finE = time(NULL);
	  printf("Tiempo que demora en crear solucion tras eliminar: %f\n\n", difftime(finE, inicioE));
	  freeArreglo(clientesNuevos);
	  printf("%s\n", "Si todo salio como debe, en la carpeta donde se encuentra este programa habra un archivo llamado Bultos.out con las modificaciones pertinentes.");
	  break;
	default:
	  printf("%s\n", "El valor ingresado no es valido. El programa terminara.");
	  exit(0);  
  }
}

int main(int argc, char const *argv[]){
  printf("\n\n%s\n\n", "****************COMIENZO PROGRAMA****************");
  menu();
  printf("\n\n%s\n\n", "****************TERMINO PROGRAMA****************");
  return 0;
}