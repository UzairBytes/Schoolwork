#include <stdio.h>
#include <stdlib.h>

int main() {
    char phone[11];
    scanf("%s", phone);
    int errors = 0;
    int next;

    while (scanf("%d", &next) != EOF){
        if (next == -1){
            printf("%s\n", phone);
        }
    
        else if (next >= 0 && next <=9){
            printf("%c\n", phone[next]);
        }

        else if (next < 0 || next > 9){
            printf("ERROR\n");
            errors += 1;
        }
    }

    if (errors != 0){
        return 1;
    }
    else{
        return 0;
    }
}