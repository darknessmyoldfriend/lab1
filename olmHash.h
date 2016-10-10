#define ATTEMPT_MAX 3 //Define a user-defined security parameter n
#define MAX_TABLE_SIZE 400
#define MAX_USERS 20
#define MIN_USER_LENGTH 4
#define MAX_USER_LENGTH 31
#define MIN_PASS_LENGTH 1
#define MAX_PASS_LENGTH 11

int olmHash(void);

char * getUserID(void);

char * getPassword(void);

char * getHash(char * pass);

int writeFile(char * input);

int readFile(char user[MAX_USERS][MAX_USER_LENGTH+MAX_PASS_LENGTH+1]);

int searchUser(const char * s, char usernames[MAX_USERS][MAX_USER_LENGTH]);

int searchFile(char * input);

void E(char *in, char *out);
