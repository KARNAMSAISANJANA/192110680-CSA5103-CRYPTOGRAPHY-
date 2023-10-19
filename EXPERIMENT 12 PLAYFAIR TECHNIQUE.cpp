#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to prepare the key and remove duplicates and 'J'
void prepareKey(char key[], int key_len) {
    bool alphabets[26] = {false};
    char new_key[key_len];
    int new_key_len = 0;

    for (int i = 0; i < key_len; i++) {
        char c = key[i];

        if (c != 'J' && !alphabets[c - 'A']) {
            new_key[new_key_len++] = c;
            alphabets[c - 'A'] = true;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c != 'J' && !alphabets[c - 'A']) {
            new_key[new_key_len++] = c;
        }
    }

    strncpy(key, new_key, new_key_len);
}

// Function to initialize the Playfair matrix
void initializeMatrix(char key[], char matrix[5][5]) {
    int key_len = strlen(key);
    int k = 0;
    bool alphabets[26] = {false};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            while (k < key_len) {
                char c = key[k++];
                if (!alphabets[c - 'A']) {
                    matrix[i][j] = c;
                    alphabets[c - 'A'] = true;
                    break;
                }
            }
        }
    }
}

// Function to find the position of a character in the matrix
void findPosition(char matrix[5][5], char c, int *row, int *col) {
    if (c == 'J') c = 'I';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a digraph using Playfair
void playfairEncrypt(char matrix[5][5], char a, char b) {
    int rowA, colA, rowB, colB;
    findPosition(matrix, a, &rowA, &colA);
    findPosition(matrix, b, &rowB, &colB);

    if (rowA == rowB) {
        colA = (colA + 1) % 5;
        colB = (colB + 1) % 5;
    } else if (colA == colB) {
        rowA = (rowA + 1) % 5;
        rowB = (rowB + 1) % 5;
    } else {
        int temp = colA;
        colA = colB;
        colB = temp;
    }

    printf("%c%c", matrix[rowA][colA], matrix[rowB][colB]);
}

int main() {
    char key[26];
    char matrix[5][5];
    char plaintext[100];
    int key_len, plaintext_len;

    // Input the key and plaintext
    printf("Enter the key (no spaces, all caps): ");
    scanf("%s", key);
    key_len = strlen(key);

    printf("Enter the plaintext (no spaces, all caps): ");
    scanf("%s", plaintext);
    plaintext_len = strlen(plaintext);

    // Prepare the key
    prepareKey(key, key_len);

    // Initialize the Playfair matrix
    initializeMatrix(key, matrix);

    // Encrypt the plaintext
    printf("Encrypted text: ");
    for (int i = 0; i < plaintext_len; i += 2) {
        if (i + 1 < plaintext_len) {
            if (plaintext[i] == plaintext[i + 1]) {
                plaintext[i + 1] = 'X';
            }
            playfairEncrypt(matrix, plaintext[i], plaintext[i + 1]);
        } else {
            // If the plaintext length is odd, append 'X' to make it even
            playfairEncrypt(matrix, plaintext[i], 'X');
        }
    }
    printf("\n");

    return 0;
}
