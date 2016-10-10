#include "olmHash.h"
#include "oPass.h"

char passes[TABLE_LENGTH][MAX_UPPER_PASS + 1];
char hashes[TABLE_LENGTH][MAX_UPPER_PASS + 1];

int oPass(void){
	char * p = (char*)calloc(MAX_UPPER_PASS + 1, sizeof(char));
	p[MAX_UPPER_PASS] = 0;
	recurse(p, 0, MAX_UPPER_PASS);
    while(1){
        char * input = (char*)calloc(MAX_PASS_LENGTH, sizeof(char));
        puts("Enter hashed password:");
        scanf("%10s", input);
        char c;

        do {
            c = getchar();
        } while (c != '\n' && c != '\0');

        int result = 0;
        int i;
        for(i = 0; i < TABLE_LENGTH; i++){
            if( strcmp(hashes[i],input) == 0 ){
                printf("The real password is: %s\n", passes[i]);
                result++;
                break;
            }
        }
        if(result == 0){
            puts("No real password found!\n");
        }
    }
	return 0;
}
int tableLine = 0;
//populates all hashes for every possible password
void recurse(char * pass, int index, int max){
	//base case
	if (index >= max){
		strncpy(passes[tableLine], pass, 4);
		char * hash = getHash(pass);
		printf("%s : %s\n", pass, hash);
		strncpy(hashes[tableLine], hash, 4);
		tableLine++;
	} else {
	    int i;
		for (i = 0; i < 26; i++){
			char a = 'A' + i;
			pass[index] = a;
			recurse(pass, index + 1, max);
		}
	}
}
