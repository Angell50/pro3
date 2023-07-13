#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100

struct Producto {
    char nombre[50];
    int cantidad;
    float precio;
};

struct Producto inventario[MAX_PRODUCTOS];
int numProductos = 0;

int leerEnteroPositivo(char* mensaje){
  int valor;
  do{
    printf("%s: ",mensaje);
    scanf("%d",&valor);
  }while(valor <= 0);
  return valor;
}

float leerFlotantePositivo(char* mensaje){
    float valor;
  do{
    printf("%s: ",mensaje);
    scanf("%f",&valor);
  }while(valor <= 0);
  return valor;

}

int leerEnteroEntre(char* mensaje, int minimo, int maximo){
  int valor;
  do{
    printf("%s",mensaje);
    scanf("%d",&valor);

  }while(valor < minimo || valor > maximo);
  return valor;
}

void guardarInventario() {
    FILE *archivo = fopen("inventario.txt", "w");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < numProductos; i++) {
        fprintf(archivo, "%s %d %.2f\n", inventario[i].nombre, inventario[i].cantidad, inventario[i].precio);
    }

    fclose(archivo);
    printf("Inventario guardado en el archivo 'inventario.txt' correctamente.\n");
}

void cargarInventario() {
    FILE *archivo = fopen("inventario.txt", "r");

    if (archivo == NULL) {
        printf("No se encontró el archivo de inventario. Se creará uno nuevo.\n");
        return;
    }

    numProductos = 0;

    while (!feof(archivo) && numProductos < MAX_PRODUCTOS) {
        fscanf(archivo, "%s %d %f\n", inventario[numProductos].nombre,
               &inventario[numProductos].cantidad, &inventario[numProductos].precio);

        numProductos++;
    }

    fclose(archivo);
    printf("Inventario cargado desde el archivo 'inventario.txt' correctamente.\n");
}

void agregarProducto() {
  int cant; 
  float precio;
    if (numProductos == MAX_PRODUCTOS) {
        printf("El inventario está lleno. No se pueden agregar más productos.\n");
        return;
    }

    struct Producto nuevoProducto;

    printf("Ingrese el nombre del producto: ");
    scanf("%s", nuevoProducto.nombre);
  
   printf("Ingrese la cantidad de productos: ");
   scanf("%d", &nuevoProducto.cantidad);

    printf("Ingrese el precio del producto: ");
    scanf("%f", &nuevoProducto.precio);

    inventario[numProductos] = nuevoProducto;
    numProductos++;

    printf("Producto agregado con éxito.\n");
}

void editarProducto() {
    char nombre[50];
    int cant;
    float precio;
    printf("Ingrese el nombre del producto a editar: ");
    scanf("%s", nombre);

    int encontrado = 0;
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombre) == 0) {
            printf("Ingrese la nueva cantidad de productos: ");
            scanf("%d", &inventario[i].cantidad);

            printf("Ingrese el nuevo precio del producto: ");
            scanf("%f", &inventario[i].precio);

            printf("Producto editado con éxito.\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró el producto con el nombre ingresado.\n");
    }
}

void eliminarProducto() {
    char nombre[50];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);

    int encontrado = 0;
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombre) == 0) {
            for (int j = i; j < numProductos - 1; j++) {
                inventario[j] = inventario[j + 1];
            }

            numProductos--;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró el producto con el nombre ingresado.\n");
    } else {
        printf("Producto eliminado con éxito.\n");
    }
}

void listarProductos() {
    if (numProductos == 0) {
        printf("No hay productos en el inventario.\n");
    } else {
        printf("INVENTARIO:\n");
        for (int i = 0; i < numProductos; i++) {
            printf("Producto: %s\n", inventario[i].nombre);
            printf("Cantidad: %d\n", inventario[i].cantidad);
            printf("Precio: %.2f\n", inventario[i].precio);
            printf("--------------------------\n");
        }
    }
}

int main() {
    cargarInventario();
    
    
    int opcion;

    do {
        printf("BIENVENIDO A LA CASA MUSICAL AMADOR JIMENEZ\n");
        printf("=== SISTEMA DE INVENTARIO ===\n");
        printf("1. AGREGAR PRODUCTO\n");
        printf("2. EDITAR PRODUCTO\n");
        printf("3. ELIMINAR PRODUCTO\n");
        printf("4. LISTAR PRODUCTO\n");
        printf("5. GUARDAR INVENTARIO\n");
        printf("6. SALIR\n");
        opcion = leerEnteroEntre("Ingrese una opcion: ",1,6);

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                editarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                listarProductos();
                break;
            case 5:
                guardarInventario();
                break;
            case 6:
                printf("Saliendo del sistema...\n");
                break;
        }

        printf("\n");
    } while (opcion != 6);

    return 0;
}
