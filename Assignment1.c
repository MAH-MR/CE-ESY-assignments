#include <stdio.h>
#include <string.h>
#define CB_SIZE 16          
#define CB_EMPTY '\0'       

struct ConsoleBuffer {
    char         s[CB_SIZE];   
    unsigned int rpos;         
    unsigned int wpos;         
};

struct ConsoleBuffer cons_buf;

void cons_buf_init(void) {
    cons_buf.rpos = 0;
    cons_buf.wpos = 0;
}

int cons_buf_is_empty(void) {
    return cons_buf.rpos == cons_buf.wpos;
}

int cons_buf_is_full(void) {
    return (cons_buf.wpos - cons_buf.rpos) == (unsigned int)CB_SIZE;
}
char cons_buf_read(void) {
    if (cons_buf.rpos == cons_buf.wpos) {
        printf("[Underflow] Buffer is empty – nothing to read.\n");
        return CB_EMPTY;
    }

    return cons_buf.s[cons_buf.rpos++ & (CB_SIZE - 1)];
}

void cons_buf_write(char c) {
    if (cons_buf_is_full()) {
        printf("[Overflow] Buffer full – oldest character '%c' discarded.\n",
               cons_buf.s[cons_buf.rpos & (CB_SIZE - 1)]);
        cons_buf.rpos++;
    }

    cons_buf.s[cons_buf.wpos++ & (CB_SIZE - 1)] = c;
}

int main(void) {
    char name[64];          
    char full_name[128];    
    int  i;

    cons_buf_init();

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = '\0';

    snprintf(full_name, sizeof(full_name), "%sCE-ESY", name);

    printf("Full string to buffer: \"%s\"\n", full_name);
    printf("Buffer size (CB_SIZE): %d\n\n", CB_SIZE);

    for (i = 0; full_name[i] != '\0'; i++) {
        cons_buf_write(full_name[i]);
    }

    printf("Output from buffer: ");
    while (!cons_buf_is_empty()) {
        putchar(cons_buf_read());
    }
    putchar('\n');

    if (cons_buf_is_empty()) {
        printf("\nBuffer is now empty. All characters consumed successfully.\n");
    }

    return 0;
}
