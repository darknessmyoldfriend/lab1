#include "crAuth.h"
#include "olmHash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char dataArray[MAX_USERS][MAX_USER_LENGTH+MAX_PASS_LENGTH+1];

int crAuth(void){
    int random = rand();
    printf("Random number: %i\n", random);
    //if old user is found, ask for password and match
    char * input = getUserID();
    char * password = getXOR( (getHash(getPassword())), random);

    if(searchFile(input) == 0){
        //Old user
        if( searchFile(password) != 0 ){
            puts("Not authenticated.\n");
        } else {
            puts("Authenticated.\n");
            return 0;
        }
    } else {
        //New user
        writeFile(input);
        printf("Username written to file.\nYou will create a new password.\n");
        char * newPass = password;
        writeFile(newPass);
        writeFile("\n");
        printf("Password written to file. Run again to input more.\n");
        return 0;
    }
    return 0;
}

//xor the hash with the server's random number
char * getXOR(char * hash, int r){
	char * output = (char*)calloc(MAX_PASS_LENGTH, sizeof(char));
	R(hash, output, r);
	R(&hash[4], &output[4], r);
	R(&hash[8], &output[8], r);
	return output;
}


void R(char* in, char* out, int r){
	out[3] = in[3] ^ (r & 255); //XOR
	r = r >> SHIFT;
	out[2] = in[2] ^ (r & 255);
	r = r >> SHIFT;
	out[1] = in[1] ^ (r & 255);
	r = r >> SHIFT;
	out[0] = in[0] ^ (r & 255);
}

//converts password to hash
char * getCRAuthHash(char * pass){
    char * hash = (char*)calloc(MAX_PASS_LENGTH, sizeof(char));
    int passLength = strlen(pass);
    int i;
	for(i = 0; i < passLength+1; i++){ //pass char to E to getHash
       E(&pass[4*i],&hash[4*i]);
	}
   	return hash;
}


