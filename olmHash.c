#include "olmhash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char users[MAX_USERS];
char passes[MAX_USERS];
int userCount = 0;

int olmHash(void){
    int attempts;
    attempts = 0;

    char * input = 0;
    while(input == 0){
        input = getUserID();
        printf("%s\n", input);
    }

    int searchName = searchData(input, users);
    if(searchName == -1){
        char * pass = getPassword();
        char * hash = getHash(4, pass);

        strcpy(&users[userCount], input);
        writeFile(userCount, users, passes);
        strcpy(&passes[userCount], hash);
        writeFile(userCount, users, passes);
        userCount--;
    } else {
        while(attempts < ATTEMPT_MAX){
        printf("Hello %s", input);
        char * pass = getPassword();
        char * hash = getHash(3, pass);
        int checkPass = strcmp(hash, passes[userCount]);
            if(checkPass == 0){
                attempts = 0;
                puts("Authenticated. Enter new password:\n");
                char * newPass = getPassword();
                char * newHash = getHash(3, newPass);
                strcpy(passes[userCount], hash);
                puts("Password updated.\n");
                break;
            }
            puts("Incorrect. Please try again. Max 4 attempts.\n");
            attempts++;
        }
        if(attempts >= ATTEMPT_MAX){
            puts("You have been locked out!\n");
        }
    }

        /*
        char * fail = "fail";
        getPassword();
        while((getPassword() == fail) && (attempts < ATTEMPT_MAX)){
            getPassword();
            attempts++;
        }

        if(attempts == ATTEMPT_MAX){
            puts("You have been locked out!\n");
            return 0;
        }
        /*
        getPassword();
        if("fail"){
            attempts++;
            getPassword();
        } else {
            puts("You have been locked out!");
            return 0;
        }
        */


        return 0;
}
/*
		printf("Enter a new password: /n");
		scanf(%c, password); // the program asks the user to enter a new password
		getHash(password); // The hash of the password is then computed and added to the table alongside the user id
		break;
		} else if (search(user_id)){ //If the user id already exists in the table
		printf("Enter your password: /n");
		scanf(%c, password); // the program asks the user to enter their old password
		getHash(password); //The hash of the entered password is computed and
							//compared to the hash of the user’s old password stored in the table
		search(password); //If the hashes match
		printf("Enter a new password: /n");
		scanf(%c, password); // the program asks the user to enter a new password
		getHash(password); // The hash of the password is then computed and added to the table alongside the user id
		break;
		}

	printf("Too many unsuccessful attempts - your account is locked \n");
	attempt = 0;
}*/
/*
int readFile(char users[MAX_USERS], char passes[MAX_USERS]){
    FILE * fp;
    char line[100];
    char newLine = '\n';
    if ((fp = fopen("data.txt, "rt")) == NULL){
        return;
    }
}
*/
int writeFile(int count, char users[MAX_USERS], char passes[MAX_USERS]){
    char * newLine = '\n';
    FILE * fp;

    fp = fopen("data.txt", "w+");

    while(count > -1){
        puts("done\n");
        fwrite(&users[userCount], sizeof(char), sizeof(strlen(users[userCount]))+1, fp);
        fwrite(&newLine, sizeof(char), 2b, fp);
        fwrite(&passes[count], sizeof(char), sizeof(strlen(passes[count]))+1, fp);
        fwrite(&newLine, sizeof(char), 2, fp);
        count--;
    }
    fclose(fp);
    return 0;
}
//searches for username in table
int searchData(const char * s, char usernames[MAX_USERS]){
    int i;

    for(i = 0; i < MAX_USERS; i++){
        if(stricmp(&s,&usernames[i]) == 0){
            puts("Username found");
            return i;
        } else {
            puts("Username not found. Creating new username.\n");
            return -1;
        }
    }
}

int searchFile(char usernames[MAX_USERS],char passwords[MAX_USERS]){
    FILE * fp;
	char line[20];
	char newLine = '\n';
	//attempt to open file
	fp = fopen("data.txt", "rt");

	int count = 0;
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
        } else {
            return user;
        }
    return user;
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
        return "fail";
    } else {
        return pass;
    }
    return pass;
}
