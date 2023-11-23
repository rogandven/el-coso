#include "libraries/procedures.h"

static user user_db[MAX_USER];
static product product_db[MAX_DB] = {0};
int salir = 0, userPos = 0;

int main() {
  // malloc(1000000);
  importUserDatabase(user_db);
  for (int i = 0; i < MAX_DB; i++) {
    printProductInfo(product_db[i], 1);
  }

  /* userPos = login(user_db);
  if (userPos >= 0) {
    do {
      mainMenu(userPos, user_db[userPos].isAdmin, &salir);
    } while (salir == 0);
  } */
  return 0;
}
