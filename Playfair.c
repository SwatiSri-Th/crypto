#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* Function for Playfair Cipher encryption  */
void Playfair(char str[], char keystr[]) {
    char keyMat[5][5];
    // Key & plainText
    char ks = strlen(keystr);
    char ps = strlen(str);   
    void toUpperCase(char encrypt[], int ps) {
    	int i;
        for ( i= 0; i < ps; i++) {
            if (encrypt[i] > 96 && encrypt[i] < 123)
                encrypt[i] -= 32;
        }
    }
    int removeSpaces(char* plain, int ps) {
        int i, count = 0;
        for (i = 0; i < ps; i++)
            if (plain[i] != ' ')
                plain[count++] = plain[i];
        plain[count] = '\0';
        return count;
    }
    /* this function will create a 5 by 5 matrix. */
    void createMatrix(char keystr[], int ks, char keyMat[5][5]) {
        int flag = 0, *dict,i,j,k;
        /* here we are creating a hashmap for alphabets */
        dict = (int*)calloc(26, sizeof(int));
        for ( i = 0; i < ks; i++) {
            if (keystr[i] != 'j')
                dict[keystr[i] - 97] = 2;
        }
        dict['j' - 97] = 1;
        i = 0, j = 0;
        for ( k = 0; k < ks; k++) {
            if (dict[keystr[k] - 97] == 2) {
                dict[keystr[k] - 97] -= 1;
                keyMat[i][j] = keystr[k];
                j++;
                if (j == 5) {
                    i++;
                    j = 0;
                }
            }
        }
        for ( k = 0; k < 26; k++) {
            if (dict[k] == 0) {
                keyMat[i][j] = (char)(k + 97);
                j++;
                if (j == 5) {
                    i++;
                    j = 0;
                }
            }
        }
    }
    /*this function looks for a digraph's characters in the key matrix and returns their positions.*/
    void search(char keyMat[5][5], char a, char b, int arr[]) {
    	int i,j;
        if (a == 'j')
            a = 'i';
        else if (b == 'j')
            b = 'i';
        for( i = 0; i < 5; i++) {
            for( j = 0; j < 5; j++) {
                if (keyMat[i][j] == a) {
                    arr[0] = i;
                    arr[1] = j;
                }
                else if (keyMat[i][j] == b) {
                    arr[2] = i;
                    arr[3] = j;
                }
            }
        }
    }
    /* This function avoids duplication and levels out the length of plain text by making it even.*/
    int prep(char str[], int p) {
        int i,j,sub = p;
        for ( i = 0; i < sub; i += 2) {
            if(str[i]==str[i+1]){
                for( j=sub; j>i+1; j--){
                   str[j]=str[j-1];
                }
                str[i+1]='x';
                sub+=1;
            }
        }
        str[sub]='\0';
        if (sub % 2 != 0) {
            str[sub++] = 'z';
            str[sub] = '\0';
        }
        return sub;
    }
    // Here, the encryption is done.
    void encrypt(char str[], char keyMat[5][5], int pos) {
        int a[4],i;
        for( i=0; i<pos; i+=2){
            search(keyMat, str[i], str[i + 1], a);
            if (a[0] == a[2]) {
                str[i] = keyMat[a[0]][(a[1] + 1)%5];
                str[i + 1] = keyMat[a[0]][(a[3] + 1)%5];
            }
            else if (a[1] == a[3]) {
                str[i] = keyMat[(a[0] + 1)%5][a[1]];
                str[i + 1] = keyMat[(a[2] + 1)%5][a[1]];
            }
            else {
                str[i] = keyMat[a[0]][a[3]];
                str[i + 1] = keyMat[a[2]][a[1]];
            }
        }
    }
    ks = removeSpaces(keystr, ks);
    ps = removeSpaces(str, ps);
    ps = prep(str, ps);
    createMatrix(keystr, ks, keyMat);
    encrypt(str, keyMat, ps);
    toUpperCase(str, ps);
    /* str is the final encrypted string in uppercase */
    printf("Cipher text: %s\n", str);
}


int main() {
    char string[200], keyString[200];
    printf("Enter key: ");
    scanf("%[^\n]s", &keyString);
    printf("Enter plaintext: ");
    scanf("\n");
    scanf("%[^\n]s", &string);
    
    //Playfair Cipher Program in C functional call
    Playfair(string, keyString);
    return 0;
}

