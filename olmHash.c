#include "olmHash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char users[MAX_USERS][MAX_USER_LENGTH];
char passes[MAX_USERS][MAX_PASS_LENGTH];
int userCount = 0;

int olmHash(void){
    char * temp = getUserID();
    int in = searchFile(temp,users);

    //if not found, return -1.
    if(in != 0){
        printf("%i\n", in);
        puts("cool!\n");
    } else {
        printf("%i\n", in);
        puts("not cool! save it to file\n");
        strcpy(users[userCount],temp);
        writeFile(userCount,users);
        puts("file saved!\n");
        return -1;
    }
    return 0;
}

int writeFile(int i, char array[MAX_USERS][MAX_USER_LENGTH]){
    FILE *f = fopen("data.txt", "ab");
    fwrite(array[i], sizeof(char), sizeof(array[i]), f);
    fprintf(f, "\n");
    fclose(f);
    return 0;
}

//int readFile(char array[MAX_USERS][MAX_USER_LENGTH]){
//    FILE *f = fopen("data.txt", "rb");
//    fread(array, sizeof(char), sizeof(array), f);
//    return 0;
//}
//searches for username in table
int searchUser(const char * c, char array[MAX_USERS][MAX_USER_LENGTH]){
    int i;
    for(i = 0; i < MAX_USERS; i++){
        if(stricmp(c,array[i]) == 0){
            puts("Username found");
            return i;
        } else {
            puts("Username not found. Creating new username.\n");
            return -1;
        }
    }
    return 0;
}

int searchFile(char * c, char array[MAX_USERS][MAX_USER_LENGTH]){
    FILE *fp;
    fp = fopen("data.txt", "rb");
    while(fgets(c, sizeof(array), fp) != NULL){
        puts("found!\n");
        return -1;
    }
    /*
    const char * temp = array;

    if((strstr(c, temp)) == NULL){
        printf("Not found!\n");
        return -1;
    } else {
        printf("Found!");
        return 0;
    }
    */
    puts("not found!\n");
    return 0;
}
// DES replacement cipher
// The function E takes 4 bytes from *in as input and
// writes 4 bytes to *out
void E(char *in, char *out){

    char c0 = toupper(in[0]);
	char c1 = toupper(in[1]);
	char c2 = toupper(in[2]);
	char c3 = toupper(in[3]);

    out[0] = (c0 & 0x80) ^ (((c0 >> 1) & 0x7F) ^ ((c0) & 0x7F));
	out[1] = ((c1 & 0x80) ^ ((c0 << 7) & 0x80)) ^ (((c1 >> 1) & 0x7F) ^ ((c1) & 0x7F));
	out[2] = ((c2 & 0x80) ^ ((c1 << 7) & 0x80)) ^ (((c2 >> 1) & 0x7F) ^ ((c2) & 0x7F));
	out[3] = ((c3 & 0x80) ^ ((c2 << 7) & 0x80)) ^ (((c3 >> 1) & 0x7F) ^ ((c3) & 0x7F));
}

//converts password to hash
char * getHash(int x, char * pass){
    char * hash = (char*)calloc(MAX_PASS_LENGTH, sizeof(char));
    //getUpper(0,&*pass);
	int j;
	for(j=0; j<x; j++){ //pass char to E to hashify

       E(&pass[4*j],&hash[4*j]);
	}
   	return hash;
}

//gets userID and returns it
char * getUserID(void){
    char * user = (char*)calloc(MAX_USER_LENGTH, sizeof(char));
    int n;

    printf("Enter your username: ");
    // the program asks the user to enter a new password
    fgets(user, MAX_USER_LENGTH, stdin);
        user[strlen(user) - 1] = '\0';
        n = strlen(user);

    //User id’s must be at least 4 characters,
    //but less than 32 characters long.
        if (n < MIN_USER_LENGTH){
            printf("Username must be 4 to 31 characters long!\n");
            return 0;
        } else {
            return user;
        }
}

//gets password and returns it
char * getPassword(void){
    char * pass = (char*)calloc(MAX_USER_LENGTH, sizeof(char));

    int n;

    printf("Enter your password: ");
    // the program asks the user to enter a new password
    fgets(pass, MAX_PASS_LENGTH, stdin);
    pass[strlen(pass) - 1] = '\0';
    n = strlen(pass);
    //passwords must be at least 1 character long
    if (n < MIN_PASS_LENGTH){
        printf("Password must be 1-12 characters long!\n");
        return 0;
    } else {
        return pass;
    }
}
