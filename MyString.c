#include "MyString.h"
#include <stdlib.h>

typedef struct MyString {
    char *str;
    unsigned int length;
} MyString;

unsigned int charsLength(const char *p) {
    if (p == 0) {
        return (unsigned int) (-1);
    }

    unsigned int count = 0;
    while (*p != 0) {
        p++;
        count++;
    }

    return count;
}


void copyChars(const char *src, char *dest) {
    if (src == 0 || dest == 0) {
        return;
    }

    while (*src != 0) {
        *dest = *src;
        src++;
        dest++;
    }
    *dest = 0;
}

unsigned int copyCharsWithoutLetter(char *src, char *dest, char letter) {
    if (src == 0 || dest == 0) {
        return 0;
    }
    unsigned int destLength = 0;
    while (*src != 0) {
        if (*src != letter) {
            *dest = *src;
            destLength++;
            dest++;
        }
        src++;
    }
    *dest = 0;
    return destLength;
}

MyStringP createStringFromChars(const char *str1) {
    MyStringP p = (MyStringP) malloc(sizeof(MyString));
    p->length = charsLength(str1);
    p->str = (char *) malloc(p->length + 1);
    copyChars(str1, p->str);
    return p;
}

MyStringP createStringFromString(const MyStringP str1) {

    return createStringFromChars(str1->str);
}

void freeString(MyStringP str1) {
    free(str1->str);
    free(str1);
}

unsigned int lengthString(const MyStringP str1) {
    return str1->length;
}

const char *cString(const MyStringP str1) {

    return str1->str;
}

int cmpString(const MyStringP str1, const MyStringP str2) {

    char *pt1 = str1->str;
    char *pt2 = str2->str;

    while (*pt1 != 0 || *pt2 != 0) {
        if (*pt1 > *pt2) {
            return 1;
        }
        if (*pt1 < *pt2) {
            return -1;
        }
        pt1++;
        pt2++;
    }
    if (*pt1 == 0) {
        if (*pt2 == 0) {
            return 0;
        }
        return 1;
    } else {
        return -1;
    }

}

MyStringP concatString(MyStringP str1, const MyStringP str2) {

    unsigned int newLength = str1->length + str2->length;
    str1->str = (char *) realloc(str1->str, newLength);
    copyChars(str2->str, str1->str + str1->length);
    str1->length = newLength;
    return createStringFromString(str1);

}

MyStringP deleteCharString(MyStringP str1, const char letter) {
    str1->length = copyCharsWithoutLetter(str1->str, str1->str, letter);
    return str1;
}

unsigned int countSubStr(const MyStringP str1, const MyStringP str2, int isCyclic) {
    char *start = str1->str;
    unsigned int count = 0;

    while (*start != 0) {

        char *current1 = start;
        char *current2 = str2->str;

        while (*current2 != 0) {
            if (*current1 == 0) {
                if (isCyclic == 0) {
                    break;
                } else {
                    current1 = str1->str;
                }
            } else {
                if (*current1 != *current2) {
                    break;
                }
                current1++;
            }
            current2++;
        }
        if (*current2 == 0) {
            count++;
        }
        start++;
    }
    return count;
}

void testConcat();

void testDelete();

void testCreateFromString();

void testCompareString();

void printTestResult(int passed) {

    printf("%s\n", passed == 1 ? "passed" : "failed");

}

int main() {
//    testConcat();
//    testDelete();
//    testCreateFromString();
//    testCompareString();

    MyStringP str1 = createStringFromChars("abcdefgh");
    MyStringP str2 = createStringFromChars("abcdefgha");
    unsigned int count = countSubStr(str1, str2, 1);
    int passed = count == 1 ? 1 : 0;
    freeString(str1);
    freeString(str2);
    printTestResult(passed);


    return 0;
}

void testCompareString() {
    MyStringP s1 = createStringFromChars("hello");
    MyStringP s2 = createStringFromChars("hallo");
    MyStringP s3 = createStringFromChars("hallo ");
    MyStringP s4 = createStringFromChars("Hallo ");
    MyStringP s5 = createStringFromChars("hello world");

    int eq1 = cmpString(s1, s2);
    int eq2 = cmpString(s2, s3);
    int eq3 = cmpString(s3, s4);
    int eq4 = cmpString(s1, s5);

    int passed = ((eq1 == -1) && (eq2 == -1) && (eq3 == 1) && (eq4 == 1)) ? 1 : 0;
    printTestResult(passed);

    freeString(s5);
    freeString(s4);
    freeString(s3);
    freeString(s2);
    freeString(s1);
}

void testCreateFromString() {
    MyStringP hello1 = createStringFromChars("hello world");
    MyStringP hello2 = createStringFromString(hello1);

    int eq = cmpString(hello1, hello2);

    freeString(hello1);
    freeString(hello2);
    printTestResult(eq == 0 ? 1 : 0);
}

void testDelete() {
    MyStringP danielle = createStringFromChars("danielle sackstein");
    deleteCharString(danielle, 'a');
    MyStringP dnielle = createStringFromChars("dnielle sckstein");

    int eq = cmpString(danielle, dnielle);
    freeString(danielle);
    printTestResult(eq == 0 ? 1 : 0);
}

void testConcat() {
    MyStringP s1 = createStringFromChars("hello");
    MyStringP s2 = createStringFromChars(" ");
    MyStringP s3 = createStringFromChars("world");
    MyStringP s4 = concatString(s1, s2);
    MyStringP s5 = concatString(s4, s3);

    printf("%s\n", s5->str);

    freeString(s5);
    freeString(s4);
    freeString(s3);
    freeString(s2);
    freeString(s1);
}
