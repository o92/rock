#include <lib/stringUtils.h>

#include <stddef.h>

char *itob(uint64_t num, uint64_t base) {
    static char hold[] = "0123456789ABCDEF";
    static char buffer[50];
    char *str;

    str = &buffer[49];
    *str = '\0';

    do {
        *--str = hold[num%base];
        num /= base;
    } while(num != 0);

    return str;
}

uint64_t strlen(const char *str) {
    uint64_t len = 0;
    while (str[len])
        len++;
    return len;
}


int strcmp(const char *str0, const char *str1) {
    while(*str0 && *str0 == *str1) {
        str0++;
        str1++;
    }
    return (int)(*str0) - (int)(*str1);
}

int strncmp(const char *str0, const char *str1, uint64_t n) {
    for(uint64_t i = 0; i < n; i++) {
        if (str0[i] != str1[i]) 
            return 1;
    }
    return 0;
}

char *strcpy(char *dest, const char *src) {
    uint64_t i;

    for(i = 0; src[i]; i++)
        dest[i] = src[i];

    dest[i] = 0;

    return dest;
}

char *strncpy(char *dest, const char *src, uint64_t n) {
    uint64_t i;

    for(i = 0; i < n && src[i]; i++)
        dest[i] = src[i];
    for(; i < n; i++)
        dest[i] = 0;

    return dest;
}


uint64_t splitString(char **subs, const char *str, const char *delimiter) {
    uint64_t subCnt = 0, last = 0;

    for(uint64_t i = 0; i < strlen(str); i++) {
        if(i == strlen(str) - 1) {
            subs[subCnt] = new char[i - last];
            strncpy(subs[subCnt++], str + last, i - last + 1);
            break;
        }

        if(strncmp(delimiter, str + i, strlen(delimiter)) == 0) {
            subs[subCnt] = new char[i - last];
            strncpy(subs[subCnt++], str + last, i - last);
            last = i + 1;
        }
    }

    return subCnt;
}
