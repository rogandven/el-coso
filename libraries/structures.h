#include<string.h>

#define MAX_NAME 30
#define MAX_PASSWORD 90
#define MAX_DB 100
#define MAX_USER 40
#define DELETED_INDICATOR -69
#define MAX_AGE 130
#define MAX_ATTEMPTS 10

// -- Structures --

// Data
typedef struct a{
	char n1[MAX_NAME];
	char n2[MAX_NAME];
	char n3[MAX_NAME];
	char n4[MAX_NAME];
	int age;
}person;

// User
typedef struct b{
	char username[MAX_NAME];
	char password[MAX_PASSWORD];
	person data;
	int isAdmin;
	int isBlocked;
	int encryptionKey;
	int money;
}user;

// Product
typedef struct c{
	char name[MAX_NAME];
	char brand[MAX_NAME];
	char type[MAX_NAME];
	int boughtPrice;
	int currentPrice;
	int stock;
}product;

// -- Placeholders --

user placeholderUser(){
	user x;
	strcpy(x.username, "DELETED");
	strcpy(x.password, "DELETED");
	strcpy(x.data.n1, "DELETED");
	strcpy(x.data.n2, "DELETED");
	strcpy(x.data.n3, "DELETED");
	strcpy(x.data.n4, "DELETED");
	x.data.age=DELETED_INDICATOR;
	x.isAdmin=DELETED_INDICATOR;
	x.isBlocked=DELETED_INDICATOR;
	x.money=DELETED_INDICATOR;
	x.encryptionKey=DELETED_INDICATOR;
	return x;
}

product placeholderProduct(){
	product x;
	strcpy(x.name, "DELETED");
	strcpy(x.brand, "DELETED");
	strcpy(x.type, "DELETED");
	x.boughtPrice=DELETED_INDICATOR;
	x.currentPrice=DELETED_INDICATOR;
	x.stock=DELETED_INDICATOR;
	return x;
}
