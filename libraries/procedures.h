#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

// Wipe databases
void wipeUserDB(user user_db[MAX_USER]) {
  int i = 0;
  for (i = 0; i < MAX_USER; i++) {
    user_db[i] = placeholderUser();
  }
}

void wipeProductDB(product product_db[MAX_DB]) {
  int i = 0;
  for (i = 0; i < MAX_DB; i++) {
    product_db[i] = placeholderProduct();
  }
}

void wipeAllDB(user user_db[MAX_USER], product product_db[MAX_DB]) {
  int i = 0;
  for (i = 0; i < MAX_DB; i++) {
    product_db[i] = placeholderProduct();
    if (i < MAX_USER) {
      user_db[i] = placeholderUser();
    }
  }
}

// Miscelaneous functions
void encrypt(char *pass, int key) {
  int i = 0, sizer = strlen(pass);
  for (i = 0; i < sizer; i++) {
    pass[i] = pass[i] + key;
  }
}

void toUppercase(char *name) {
  int i = 0, sizer = strlen(name);
  for (i = 0; i < sizer; i++) {
    if (name[i] >= 97 && name[i] <= 122) {
      name[i] = name[i] - 32;
    }
  }
}

void removeSpaces(char *name) {
  int i = 0, sizer = strlen(name);
  for (i = 0; i < sizer; i++) {
    if (name[i] == ' ') {
      name[i] = '_';
    }
  }
}

int validateName(char name[MAX_NAME]) {
  int i = 0, sizer = strlen(name), valid = 1;
  toUppercase(name);
  for (i = 0; i < sizer && valid == 1; i++) {
    if (name[i] >= 65 && name[i] <= 90) {
      valid = 1;
    } else {
      valid = 0;
      printf("ERROR: Caracter invalido.\n");
    }
  }
  return valid;
}

int validateAge(int age, int import) {
  int valid = 1;
  if ((age > 0 && age < MAX_AGE) || (age == DELETED_INDICATOR)) {
    valid = 1;
    if (import != 1) {
      valid = 0;
      printf("ERROR: Edad fuera de rango.\n");
    }
  } else {
    valid = 0;
    printf("ERROR: Edad fuera de rango.\n");
  }
  return valid;
}

int isDeletedProduct(product x) {
  int flags = 0;
  if (strcmp(x.name, "DELETED") == 0) {
    flags++;
  }
  if (strcmp(x.brand, "DELETED") == 0) {
    flags++;
  }
  if (strcmp(x.type, "DELETED") == 0) {
    flags++;
  }
  if (x.boughtPrice == DELETED_INDICATOR) {
    flags++;
  }
  if (x.currentPrice == DELETED_INDICATOR) {
    flags++;
  } else {
    if (x.currentPrice == 0 || x.stock == 0) {
      flags = 5000;
    }
  }
  if (x.stock == DELETED_INDICATOR) {
    flags++;
  }
  if (flags >= 5) {
    return 1;
  } else {
    return 0;
  }
}

// File System Functions
void exportUserDatabase(user user_db[MAX_USER]) {
  user x;
  FILE *file1;
  int c = 0;
  char *filename1 = "user_db.txt";

  // User database
  file1 = fopen(filename1, "w");
  if (file1) {
    for (c = 0; c < MAX_USER; c++) {
      x = user_db[c];
      fprintf(file1, "%s %s %s %s %s %s %d %d %d %d %d\n", x.username,
              x.password, x.data.n1, x.data.n2, x.data.n3, x.data.n4,
              x.data.age, x.isAdmin, x.isBlocked, x.encryptionKey, x.money);
    }
    fclose(file1);
    printf("Base de datos de usuarios exportada con exito.\n");
  } else {
    printf("No se ha encontrado la base de datos de usuarios.\n");
  }
}

void exportProductDatabase(product product_db[MAX_DB]) {
  product x;
  FILE *file1;
  int c = 0;
  char *filename1 = "product_db.txt";

  // User database
  file1 = fopen(filename1, "w");
  if (file1) {
    for (c = 0; c < MAX_DB; c++) {
      x = product_db[c];
      fprintf(file1, "%s %s %s %d %d %d\n", x.name, x.brand, x.type,
              x.boughtPrice, x.currentPrice, x.stock);
    }
    fclose(file1);
    printf("Base de datos de productos exportada con exito.\n");
  } else {
    printf("No se ha encontrado la base de datos de productos.\n");
  }
}

void exportAllDatabases(user user_db[MAX_USER], product product_db[MAX_DB]) {
  exportUserDatabase(user_db);
  exportProductDatabase(product_db);
}

int importUserDatabase(user user_db[MAX_USER]) {
  // Return values:
  // -1: Database not found
  // 0: Database is found, data isn't readable
  // 1: Database is found, data is readable

  int scan = 0, error = 1;
  user x;
  FILE *file1;
  int i = 0;
  char *filename1 = "user_db.txt";

  // User database
  file1 = fopen(filename1, "r");
  if (!file1) {
    printf("No se ha podido encontrar la base de datos de usuarios.\n");
    error = -1;
  } else {
    while (!feof(file1) && i != MAX_USER) {
      scan = fscanf(file1, "%s %s %s %s %s %s %d %d %d %d %d\n", x.username,
                    x.password, x.data.n1, x.data.n2, x.data.n3, x.data.n4,
                    &x.data.age, &x.isAdmin, &x.isBlocked, &x.encryptionKey,
                    &x.money);
      if (scan && validateName(x.data.n1) && validateName(x.data.n2) &&
          validateName(x.data.n3) && validateName(x.data.n4) &&
          validateAge(x.data.age, 1)) {
        user_db[i] = x;
        i++;
      } else {
        i = MAX_USER;
        printf("Hubo un error importando la base de datos de usuarios.\n");
        error = 0;
      }
      fclose(file1);
    }
  }
  return error;
}

// Printing info
void printProductInfo(product x, int isAdmin) {
  if (!(isDeletedProduct(x))) {
    printf("Nombre: %s\n", x.name);
    printf("Marca: %s\n", x.brand);
    printf("Rubro: %s\n", x.type);
    if (isAdmin == 1) {
      printf("Precio al comprar: $%d\n", x.boughtPrice);
    }
    printf("Stock: %d\n", x.stock);
  }
}

// Validations
int login(user user_db[MAX_USER]) {
  int posUser = 0, valid = 0, i = 0, attempts = MAX_ATTEMPTS;
  char enteredName[MAX_NAME];
  char enteredPassword[MAX_PASSWORD];

  do {
    strcpy(enteredName, "HOMERO");
    posUser = -420;
    printf("Ingrese su nombre de usuario: ");
    fflush(stdin);
    scanf(" %s", enteredName);

    if (strcmp(enteredName, "DELETED") != 0) {
      for (i = 0; i < MAX_USER; i++) {
        if (strcmp(enteredName, user_db[i].username) == 0) {
          posUser = i;
          i = MAX_USER;
          valid = 1;
        }
      }
    }

    if (posUser < 0) {
      printf("ERROR: No existe un registro asociado al nombre ingresado.\n");
    }
  } while (valid == 0);

  valid = 0;
  do {
    strcpy(enteredPassword, "DELETED");
    printf("Ingrese contrasenia: ");
    fflush(stdin);
    scanf(" %s", enteredPassword);
    if (strcmp(enteredPassword, user_db[posUser].password) == 0) {
      valid = 1;
    } else {
      attempts--;
      printf("Contrasenia incorrecta.\nQuedan %d intentos.\n", attempts);
    }
  } while (valid == 0 && attempts > 0);

  if (attempts <= 0 || user_db[posUser].isBlocked != 0) {
    user_db[posUser].isBlocked = 1;
    if (posUser == 0) {
      posUser = -45;
    } else {
      posUser = posUser * -1;
    }
    printf("Su cuenta ha sido bloqueada. Contacte a otro administrador para "
           "recuperarla.\n");
  }

  return posUser;
  // Must make sure return value is positive for a valid login.
}

void mainMenu(int userPos, int isAdmin, int *salir) {
  int option = -420;
  if (isAdmin == 1) {
    // Admin
    do {
      printf("1: Gestion de usuarios\n");
      printf("2: Gestion de productos\n");
      printf("3: Salir\n");
      printf("Opcion seleccionada: ");
      fflush(stdin);
      scanf(" %d", &option);
    } while (option != 1 && option != 2 && option != 3);

    switch (option) {
    case 1:
      printf("Placeholder.\n");
      break;
    case 2:
      printf("Placeholder.\n");
      break;
    case 3:
      *salir = 1;
    }
  } else {
    // Customer
    printf("Placeholder.\n");
    *salir = 1;
  }
}