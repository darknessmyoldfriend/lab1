#include "olmHash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char * username;
char * password;
int userCount = 0;

int olmHash(void){
    //if old user is found, ask for password and match
    int attempts = 0;
    while(attempts < 3){
        char * input = getUserID();
        if(searchFile(input) == 0){
            //Old user
        puts("You will enter your old password.\n");
        if(searchFile(getHash(getPassword())) != 0){
            puts("Increase attempts.\n");
        }
        puts("Create a new password:\n");
        char * replacedPass = getHash(getPassword());
        writeFile("\n");
        writeFile(input);
        writeFile(replacedPass);
        writeFile("\n");
        printf("Password written to file. Run again to input more.\n");
    } else {
        //New user
        writeFile(input);
        printf("Username written to file.\nYou will create a new password.\n");
        char * newPass = getHash(getPassword());
        writeFile(newPass);
        writeFile("\n");
        printf("Password written to file. Run again to input more.\n");
    }

    }
    return 0;
}

int writeFile(char * input){
    FILE *fp = fopen("data.txt", "ab");
    if (fp != NULL){
        fprintf(fp, "%s", input);
        fclose(fp);
        return 0;
    } else {
        puts("Error: NSF\n");
        fclose(fp);
        return -1;
    }
    return 0;
}

int searchFile(char * input) {
	FILE *fp;

	int line_num = 1;
	int find_result = 0;
	char temp[MAX_USER_LENGTH];

	if((fp = fopen("data.txt", "rb")) == NULL) {
		return -1;
	}

	while(fgets(temp, MAX_USER_LENGTH, fp) != NULL) {
		if((strstr(temp, input)) != NULL) {
			puts("Input found in file!\n");
			return 0;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
		return -1;
	}

	//Close the file if still open.
	if(fp) {
		fclose(fp);
	}
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
char * getHash(char * pass){
    char * hash = (char*)calloc(MAX_PASS_LENGTH, sizeof(char));
    int passLength = strlen(pass);
    int i;
	for(i = 0; i < passLength/4; i++){ //pass char to E to hashify
       E(&pass[4*i],&hash[4*i]);
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
    return 0;
}
