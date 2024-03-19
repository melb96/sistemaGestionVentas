#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "string.h"
#include "windows.h"

#define n 10000

typedef struct {
    int NroFactura;
    char nombre[30];
    char direccion[45];
    int id_producto;
    char fecha[6];
    int cant;
    int precio_total;
    int acumulado;
} tcliente;

typedef struct {
    int id;
    char nombre[30];
    int precio;
    int cantidad;
    int stock_inicial;
} tproducto;

void nuevo(tcliente clientes[], tproducto productos[]);
void registrar(tcliente clientes[], tproducto productos[]);
void consulta(tcliente clientes[], tproducto productos[]);
void estadisticas(tcliente clientes[], tproducto productos[]);
void cargardatos(tcliente clientes[], tproducto productos[]);
void guardardatos(tcliente clientes[], tproducto productos[]);
void agregar_producto(tproducto productos[]);
void eliminar_producto(tproducto productos[]);
void eliminar_cliente(tcliente clientes[]);
void mostrar_stock(tproducto productos[]);
void mostrar_clientes(tcliente clientes[]);
void caja_tit(int izq, int arr, int der, int aba, const char s[]);
void printf_centrado(int izq, int der, int fila, const char s[]);
void caja(int izq, int arr, int der, int aba);
void gotoxy(int x, int y);

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {100, 50}; // Tamaño del búfer de la consola
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SMALL_RECT windowSize = {0, 0, 80, 30}; // Tamaño de la ventana de la consola
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    system("COLOR 30");
    system("title Sistema de Gestion de Ventas y Stock - Tamango's Sport");

    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 10;  // Ancho de la fuente
    fontInfo.dwFontSize.Y = 18; // Altura de la fuente (en puntos)
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy(fontInfo.FaceName, L"Terminal"); // Nombre de la fuente (puedes cambiarlo según tus preferencias) Fixedsys

    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);


    tcliente clientes[n] = {0, "", "", 0, "", 0, 0, 0, 0};
    tproducto productos[n] = {0, "", 0, 0, 0};
    int menu;
    char salir;

    printf("\n\n\n\n\t\t\tCARGANDO DATOS");
    printf("\n\n\t\t\t");
    int i;
    for (i = 0; i < 14; i++) {
        printf(":");
        Sleep(200);
    }
    cargardatos(clientes, productos);

menu:
    system("cls");
    caja(10, 1, 71, 3);
    gotoxy(4, 1);
    printf("\n\t\tSISTEMA GESTION DE VENTAS Y STOCK - TAMANGO'S SPORT");
    printf("\n\n\n\t\t\t\t-MENU PRINCIPAL-");
    printf("\n\n\t1-Ingresar Cliente");
    printf("\n\n\t2-Ingresar Producto");
    printf("\n\n\t3-Registrar Cobro");
    printf("\n\n\t4-Mostrar Stock");
    printf("\n\n\t5-Mostrar Clientes");
    printf("\n\n\t6-Consultar Cuenta");
    printf("\n\n\t7-Estadisticas");
    printf("\n\n\t8-Eliminar Producto");
    printf("\n\n\t9-Eliminar Cliente");
    printf("\n\n\t10-Salir");
    caja(0, 0, 80, 30);
    gotoxy(1, 27);
    printf("\n\tIngrese el Nro de la Operacion: ");
    scanf("%i", &menu);
    gotoxy(1, 26);

    switch (menu) {
        case 1: {
            nuevo(clientes, productos);
            break;
        }
        case 2: {
            agregar_producto(productos);
            break;
        }
        case 3: {
            registrar(clientes, productos);
            break;
        }
        case 4: {
            mostrar_stock(productos);
            getch();
            break;
        }
        case 5: {
    		mostrar_clientes(clientes);
    		break;
			}
        case 6: {
            consulta(clientes, productos);
            getch();
            break;
        }
        case 7: {
            estadisticas(clientes, productos);
            getch();
            break;
        }
        case 8: {
            eliminar_producto(productos);
            break;
        }
        case 9: {
            eliminar_cliente(clientes);
            break;
        }
        case 10: {
            printf("\n\n\t\t\t\t\tDESEA SALIR (s o n): ");
            do {
                scanf("%c", &salir);
            } while (salir != 's' && salir != 'n');

            if (salir == 's') {
                guardardatos(clientes, productos);
                exit(0);
            }

            goto menu;
        }
        default:
            break;
    }
    goto menu;
}

void nuevo(tcliente clientes[], tproducto productos[]) {
    int i, e;
    char salir;
    do {
        system("cls");
        caja(0, 0, 80, 30);
        gotoxy(1, 1);
        caja(10, 1, 70, 3);
        gotoxy(4, 1);
        printf("\n\t\t\t\tNUEVO CLIENTE\n");

        for (i = n - 1; i > -1; i--)
            if (clientes[i].NroFactura == 0)
                e = i;

        fflush(stdin);
        printf("\n\tNombre y Apellido: ");
        gets(clientes[e].nombre);
        fflush(stdin);

        int factura_existente = 0;
        do {
            printf("\n\tNumero de Factura: ");
            scanf("%i", &clientes[e].NroFactura);
            fflush(stdin);

            factura_existente = 0;

            for (i = 0; i < n; i++) {
                if (clientes[i].NroFactura == clientes[e].NroFactura && i != e) {
                    factura_existente = 1;
                    printf("\n\tEl numero de factura ya existe. Ingrese otro num.\n");
                    break;
                }
            }

        } while (clientes[e].NroFactura == 0 || factura_existente);

        printf("\n\tDireccion: ");
        gets(clientes[e].direccion);
        fflush(stdin);

		int producto_existente = 0;
		int id_producto;

		do {
   		 printf("\n\tId del Producto: ");
    		scanf("%i", &id_producto);
    		fflush(stdin);

    	for (i = 0; i < n; i++) {
        if (productos[i].id == id_producto) {
            producto_existente = 1;
            // Mostrar los datos del producto
            printf("\n\tNombre del Producto: %s", productos[i].nombre);
            printf("\n\tPrecio del Producto: $%d", productos[i].precio);
            printf("\n\tCantidad en Stock: %d", productos[i].cantidad);

            if (productos[i].cantidad == 0) {
                printf("\n\tEl producto seleccionado tiene un stock de 0");
                getchar();
                return;
            }

            clientes[e].id_producto = id_producto;
            clientes[e].precio_total = productos[i].precio; // Establecer automáticamente el precio del producto
            break;
        }
    }

	    if (!producto_existente) {
        printf("\n\tEl ID del producto no existe. Presione Enter para volver al menu.\n");
        getchar(); // Esperar a que el usuario presione Enter
        return;    // Volver al menú principal
    }
	} while (!producto_existente);
    
    printf("\n");
    printf("\n\tFecha de Compra (ddmmaa): ");
    gets(clientes[e].fecha);
    fflush(stdin);
    printf("\n\tCantidad Unidades Compradas: ");
    scanf("%i", &clientes[e].cant);
    fflush(stdin);

    // Calcular el precio total de la compra
    clientes[e].precio_total *= clientes[e].cant;

    // Actualizar el stock del producto correspondiente
    for (i = 0; i < n; i++) {
        if (productos[i].id == clientes[e].id_producto) {
            productos[i].cantidad -= clientes[e].cant;
            break; // Detener la búsqueda una vez que se actualice el stock
        }
    }

    guardardatos(clientes, productos);

    do {
        printf("\n\n\tDESEA INGRESAR UN NUEVO CLIENTE? (s o n): ");
        scanf("%c", &salir);
        fflush(stdin);
    } while (salir != 's' && salir != 'n');

} while (salir == 's');
}

void registrar(tcliente clientes[], tproducto productos[]) {
    int nrobuscar, i, cliente, pago, b = 0;
    char salir;
    do {
        system("cls");
        caja(0, 0, 80, 30);
        gotoxy(1, 1);
        caja(10, 1, 70, 3);
        gotoxy(4, 1);
        printf("\n\t\t\t\tREGISTRAR COBRO");
        printf("\n\n\tIngrese Nro de Factura: ");
        scanf("%i", &nrobuscar);

        for (i = 0; i < n; i++)
            if (clientes[i].NroFactura == nrobuscar) {
                cliente = i;
                b = 1;
            }
        if (b == 0) {
            printf("\n\n\n\n\t\t\tNO SE ENCONTRO LA FACTURA");
            getch();
            return;
        }
        printf("\n\tFactura: %s", clientes[cliente].nombre);
        printf("\n\tMonto Total: $%i", clientes[cliente].precio_total);
        printf("\n\tPagado: $%i", clientes[cliente].acumulado);
        printf("\n\tSaldo pendiente: $%i", clientes[cliente].precio_total - clientes[cliente].acumulado);

        printf("\n\tCobro Efectuado: $");
        scanf("%i", &pago);

        clientes[cliente].acumulado += pago;

        guardardatos(clientes, productos);

    salir:
        printf("\n\n\tDesea regitrar otro cobro? (s o n): ");
        do {
            scanf("%c", &salir);
            fflush(stdin);
        } while (salir != 's' && salir != 'n');
    } while (salir == 's');
}

void consulta(tcliente clientes[], tproducto productos[]) {
    int i, nro, cliente, b = 0;

    system("cls");
    caja(0, 0, 80, 30);
    gotoxy(1, 1);
    caja(10, 1, 70, 3);
    gotoxy(4, 1);
    printf("\n\t\t\t   CONSULTA DE CLIENTES");
    printf("\n\n\tIngrese Nro de Factura del Cliente: ");
    scanf("%i", &nro);

    for (i = 0; i < n; i++)
        if (clientes[i].NroFactura == nro) {
            cliente = i;
            b = 1;
        }
    if (b == 0) {
        printf("\n\n\n\n\t\t\tNO SE ENCONTRO LA FACTURA");
        return;
    }

    printf("\n\tNro de Factura: %i", clientes[cliente].NroFactura);
    printf("\n\tCliente: %s", clientes[cliente].nombre);
    printf("\n\tDireccion: %s", clientes[cliente].direccion);
    // Mostrar el id del producto y nombre
    printf("\n\tId del Producto: %i", clientes[cliente].id_producto);
    printf("\n\tFecha de Compra: %c%c/%c%c/%c%c", clientes[cliente].fecha[0], clientes[cliente].fecha[1], clientes[cliente].fecha[2], clientes[cliente].fecha[3], clientes[cliente].fecha[4], clientes[cliente].fecha[5]);
    printf("\n\tMonto Total: $%i", clientes[cliente].precio_total);
    printf("\n\tPagado: $%i", clientes[cliente].acumulado);
    printf("\n\tSaldo pendiente: $%i", clientes[cliente].precio_total - clientes[cliente].acumulado);
}

void estadisticas(tcliente clientes[], tproducto productos[]) {

    int i, accanastos = 0, acventatotal = 0, acpagadototal = 0, acsaldototal = 0, acclientes = 0;
    for (i = 0; i < n; i++) {
    	accanastos += clientes[i].cant;
        acventatotal += clientes[i].precio_total;
        acpagadototal += clientes[i].acumulado;
        acsaldototal += clientes[i].precio_total - clientes[i].acumulado;
        if (clientes[i].precio_total != 0)
            acclientes += 1;
    }
    system("cls");
    caja(0, 0, 80, 30);
    gotoxy(1, 1);
    caja(10, 1, 70, 3);
    gotoxy(4, 1);
    printf("\n\t\t\tESTADISTICAS GENERALES");
    printf("\n\n\n\tFacturacion Total: %i", acventatotal);
    printf("\n\n\tPagado Total: %i", acpagadototal);
    printf("\n\n\tSaldo Total: %i", acsaldototal);
    printf("\n\n\tCantidad de Ventas: %i", acclientes);
    printf("\n\n\tCantidad de Articulos Vendidos: %i", accanastos);
    printf("\n\n\tStock de Productos:\n");
    for (i = 0; i < n; i++) {
        if (productos[i].id != 0) {
            printf("\n\tId: %i, Nombre: %s, Precio: %i, Cantidad: %i\n", productos[i].id, productos[i].nombre, productos[i].precio, productos[i].cantidad);
        }
    }
}

void cargardatos(tcliente clientes[], tproducto productos[]) {
    FILE *a;
    int i;

    if ((a = fopen("clientes.dat", "rb")) == NULL)
        return;
    fread(clientes, sizeof(tcliente), n, a);
    fclose(a);

    if ((a = fopen("productos.dat", "rb")) == NULL)
        return;
    fread(productos, sizeof(tproducto), n, a);
    fclose(a);
}

void guardardatos(tcliente clientes[], tproducto productos[]) {
    FILE *a;
    int i;
    if ((a = fopen("clientes.dat", "wb")) == NULL)
        return;
    fwrite(clientes, sizeof(tcliente), n, a);
    fclose(a);

    if ((a = fopen("productos.dat", "wb")) == NULL)
        return;
    fwrite(productos, sizeof(tproducto), n, a);
    fclose(a);
}

void agregar_producto(tproducto productos[]) {
    int i, e;
    char salir;
    do {
        system("cls");
        caja(0, 0, 80, 30);
        gotoxy(1, 1);
        caja(10, 1, 70, 3);
        gotoxy(4, 1);
        printf("\n\t\t\t\tNUEVO PRODUCTO\n");

        for (i = n - 1; i > -1; i--)
            if (productos[i].id == 0)
                e = i;

        fflush(stdin);
        printf("\n\tNombre: ");
        gets(productos[e].nombre);
        fflush(stdin);

        printf("\n\tID: ");
        scanf("%d", &productos[e].id);
        
        // Verificar si el ID ya existe
        for (i = 0; i < n; i++) {
            if (productos[i].id == productos[e].id && i != e) {
                printf("\n\tEl ID del producto ya existe. Por favor, ingrese otro ID.\n");
                fflush(stdin);
                getchar();
                break; // Salir del bucle si se encuentra un ID existente
            }
        }

        if (i < n) {
            continue; // Volver al inicio del bucle si se encontró un ID existente
        }

        printf("\n\tPrecio: ");
        scanf("%d", &productos[e].precio);
        fflush(stdin);

        printf("\n\tCantidad Inicial: ");
        scanf("%d", &productos[e].cantidad);
        fflush(stdin);

        printf("\n\tAgregado con exito\n\n");

        printf("\n\tDesea agregar otro producto? (s o n): ");
        scanf(" %c", &salir); // Corregido el espacio antes de %c
        fflush(stdin);
    } while (salir == 's' && i < n); // Permitir al usuario ingresar otro ID si es necesario
}

void eliminar_producto(tproducto productos[]) {
    int id_producto, i, encontrado = 0;
    char confirmar;

    system("cls");
    caja(0, 0, 80, 30);
    gotoxy(1, 1);
    caja(10, 1, 70, 3);
    gotoxy(4, 1);
    printf("\n\t\t\t\tELIMINAR PRODUCTO\n");

    printf("\n\tIngrese el ID del producto que desea eliminar: ");
    scanf("%d", &id_producto);
    fflush(stdin);

    // Buscar el producto por su ID
    for (i = 0; i < n; i++) {
        if (productos[i].id == id_producto) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        printf("\n\tProducto encontrado:");
        printf("\n\tNombre: %s", productos[i].nombre);
        printf("\n\tID: %d", productos[i].id);
        printf("\n\tPrecio: %d", productos[i].precio);
        printf("\n\tCantidad en stock: %d", productos[i].cantidad);
        
        printf("\n\n\tEstas seguro que deseas eliminar este producto? (s/n): ");
        scanf(" %c", &confirmar);

        if (confirmar == 's') {
            // Eliminar el producto estableciendo sus valores en cero
            productos[i].id = 0;
            strcpy(productos[i].nombre, "");
            productos[i].precio = 0;
            productos[i].cantidad = 0;

            printf("\n\tProducto eliminado con exito.");
        } else {
            printf("\n\tOperacion cancelada.");
        }
    } else {
        printf("\n\tNo se encontro ningun producto con el ID proporcionado.");
    }

    printf("\n\n\tPresione cualquier tecla para continuar...");
    getch();
}

void eliminar_cliente(tcliente clientes[]) {
    int factura, i, encontrado = 0;
    char confirmar;

    system("cls");
    caja(0, 0, 80, 30);
    gotoxy(1, 1);
    caja(10, 1, 70, 3);
    gotoxy(4, 1);
    printf("\n\t\t\t\tELIMINAR CLIENTE\n");

    printf("\n\tIngrese el numero de factura del cliente que desea eliminar: ");
    scanf("%d", &factura);
    fflush(stdin);

    // Buscar al cliente por su número de factura
    for (i = 0; i < n; i++) {
        if (clientes[i].NroFactura == factura) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        printf("\n\tCliente encontrado:");
        printf("\n\tNombre: %s", clientes[i].nombre);
        printf("\n\tNumero de factura: %d", clientes[i].NroFactura);
        
        printf("\n\n\tEstas seguro que deseas eliminar este cliente? (s/n): ");
        scanf(" %c", &confirmar);

        if (confirmar == 's') {
            // Eliminar al cliente estableciendo sus valores en cero
            clientes[i].NroFactura = 0;
            strcpy(clientes[i].nombre, "");
            strcpy(clientes[i].direccion, "");
            clientes[i].id_producto = 0;
            strcpy(clientes[i].fecha, "");
            clientes[i].cant = 0;
            clientes[i].precio_total = 0;
            clientes[i].acumulado = 0;

            printf("\n\tCliente eliminado con exito.");
        } else {
            printf("\n\tOperacion cancelada.");
        }
    } else {
        printf("\n\tNo se encontro ningun cliente con el numero de factura proporcionado.");
    }

    printf("\n\n\tPresione cualquier tecla para continuar...");
    getch();
}

void mostrar_stock(tproducto productos[]) {
    int i;

    system("cls");
    caja(0, 0, 80, 30);
    gotoxy(1, 1);
    caja(10, 1, 70, 3);
    gotoxy(4, 1);
    printf("\n\t\t\t\tSTOCK DE PRODUCTOS\n");

    printf("\n\tID\t| Nombre\t| Precio\t| Cantidad\n");
    printf("\t-----------------------------------------------\n");
    for (i = 0; i < n; i++) {
        if (productos[i].id != 0) {
            printf("\t%d\t| %s\t| $%d\t\t| %d\n", productos[i].id, productos[i].nombre, productos[i].precio, productos[i].cantidad);
        }
    }
}

void mostrar_clientes(tcliente clientes[]) {
    int i;

    system("cls");
    caja(0, 0, 80, 30);
    gotoxy(1, 1);
    caja(10, 1, 70, 3);
    gotoxy(4, 1);
    printf("\n\t\t\t\tLISTADO DE CLIENTES\n");

    printf("\n\tNro Factura\t| Nombre\t| Domicilio\t| Saldo Deudor\n");
    printf("\t------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        if (clientes[i].NroFactura != 0) {
            printf("\t%d\t\t| %s\t| %s\t| $%d\n", clientes[i].NroFactura, clientes[i].nombre, clientes[i].direccion, clientes[i].precio_total - clientes[i].acumulado);
        }
    }
    printf("\n\n\tPresione cualquier tecla para continuar...");
    getch();
}


void caja_tit(int izq, int arr, int der, int aba, const char s[]) {
    int i;
    gotoxy(izq, arr);
    printf("%c", 201);
    for (i = izq + 1; i < der - 1; i++)
        printf("%c", 205);
    printf("%c", 187);
    gotoxy(izq, aba);
    printf("%c", 200);
    for (i = izq + 1; i < der - 1; i++)
        printf("%c", 205);
    printf("%c", 188);
    for (i = arr + 1; i < aba; i++) {
        gotoxy(izq, i);
        printf("%c", 186);
        gotoxy(der, i);
        printf("%c", 186);
    }
    gotoxy((der - izq - strlen(s)) / 2 + izq, (aba - arr) / 2 + arr);
    printf("%s", s);
}

void printf_centrado(int izq, int der, int fila, const char s[]) {
    gotoxy((der - izq - strlen(s)) / 2 + izq, fila);
    printf("%s", s);
}

void caja(int izq, int arr, int der, int aba) {
    int i;
    gotoxy(izq, arr);
    printf("%c", 201);
    for (i = izq + 1; i < der; i++)
        printf("%c", 205);
    printf("%c", 187);
    for (i = arr + 1; i < aba; i++) {
        gotoxy(izq, i);
        printf("%c", 186);
        gotoxy(der, i);
        printf("%c", 186);
    }
    gotoxy(izq, aba);
    printf("%c", 200);
    for (i = izq + 1; i < der; i++)
        printf("%c", 205);
    printf("%c", 188);
}

void gotoxy(int x, int y) {
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}
