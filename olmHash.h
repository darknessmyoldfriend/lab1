#define ATTEMPT_MAX 3 //Define a user-defined security parameter n
#define MAX_IDS 20 //max users in table
#define MAX_TABLE_SIZE 400
#define MAX_USERS 20
#define MIN_USER_LENGTH 4
#define MAX_USER_LENGTH 31
#define MIN_PASS_LENGTH 1
#define MAX_PASS_LENGTH 11

int olmHash(void);

char * getUserID(void);

char * getPassword(void);

char * getHash(int x, char * pass);

int searchData(const char * s, char users[MAX_USERS]);
