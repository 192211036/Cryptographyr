#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    used['J' - 'A'] = 1; // Treat 'I' and 'J' as the same
    int index = 0;

    // Add key to matrix
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            matrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }

    // Fill remaining letters
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[index / SIZE][index % SIZE] = ch;
            index++;
        }
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'I' and 'J' as the same
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char matrix[SIZE][SIZE], char a, char b, char *encA, char *encB) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);

    if (row1 == row2) { // Same row
        *encA = matrix[row1][(col1 + 1) % SIZE];
        *encB = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) { // Same column
        *encA = matrix[(row1 + 1) % SIZE][col1];
        *encB = matrix[(row2 + 1) % SIZE][col2];
    } else { // Rectangle
        *encA = matrix[row1][col2];
        *encB = matrix[row2][col1];
    }
}

void playfairEncrypt(char text[], char key[], char encrypted[]) {
    char matrix[SIZE][SIZE];
    createMatrix(key, matrix);

    int len = strlen(text);
    char cleanedText[100];
    int cleanIndex = 0;

    // Clean text and make pairs
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            char ch = toupper(text[i]);
            if (cleanIndex > 0 && cleanedText[cleanIndex - 1] == ch) {
                cleanedText[cleanIndex++] = 'X'; // Add padding if repeated
            }
            cleanedText[cleanIndex++] = ch;
        }
    }

    if (cleanIndex % 2 != 0) {
        cleanedText[cleanIndex++] = 'X'; // Add padding if odd length
    }
    cleanedText[cleanIndex] = '\0';

    // Encrypt pairs
    int encIndex = 0;
    for (int i = 0; i < cleanIndex; i += 2) {
        char encA, encB;
        encryptPair(matrix, cleanedText[i], cleanedText[i + 1], &encA, &encB);
        encrypted[encIndex++] = encA;
        encrypted[encIndex++] = encB;
    }
    encrypted[encIndex] = '\0';
}

int main() {
    char text[100], key[100], encrypted[100];

    printf("Enter the keyword: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", text);

    playfairEncrypt(text, key, encrypted);

    printf("Encrypted text: %s\n", encrypted);
    return 0;
}

