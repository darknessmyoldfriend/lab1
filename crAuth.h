#define SHIFT 8 //8bits = 1byte

int crAuth(void);

//xor the hash with the server's random number
char * getXOR(char * password, int r);

void R(char* in, char* out, int r);

//converts password to hash
char * getCRAuthHash(char * pass);
