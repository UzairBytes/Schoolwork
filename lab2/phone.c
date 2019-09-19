#include <stdio.h>
#include <stdlib.h>


int main(){
    char phone[11];
    int command;
    scanf("%s %d", phone, &command);

    if (command == -1){
        printf("%s", phone);
        return 0;
    }
    else if (command >= 0 && command <= 9)
    {
        printf("%c", phone[command]);
        return 0;
    }
    else{
        printf("ERROR");
        return 1;
    }
}