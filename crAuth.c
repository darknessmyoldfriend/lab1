#include "olmHash.h"
int crAuth(void){
    char * username = getUserID();
    char * password = getHash(getPassword());
    int xor = getXOR(username, password);


    return 0;
}

int getRandomNumber(void){
    int x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;
    return x;
}

void R(char* input, char* output, int r)
{
	output[3] = input[3] ^ (r & 255); //xor the first byte with r's first byte
	r = r >> 8; //shift r by one byte
	output[2] = input[2] ^ (r & 255);
	r = r >> 8;
	output[1] = input[1] ^ (r & 255);
	r = r >> 8;
	output[0] = input[0] ^ (r & 255);
}
