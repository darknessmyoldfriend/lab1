#include <stdlib.h>
#include <stdio.h>

#include "olmHash.h"
#include "crAuth.h"

//driver for project
int main(void){
    int user = 0;
    puts("MENU:\nEnter 1 for part 1.\nEnter 2 for part 2.\nEnter 3 for part 3.\nEnter any other character to quit.\n");
    scanf("%d", &user);
    if(user == 1){
        olmHash();
        return 0;
    } else if (user == 2){
        crAuth();
        return 0;
    } else if (user == 3){
        oPass();
        return 0;
    } else {
        return 0;
    }
    return 0;
}


