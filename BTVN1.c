#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Hàm loại bỏ ký tự trùng lặp trong key và tạo ma trận 5x5
void prepareKey(char key[], char matrix[5][5]) {
    int i, j, k, flag = 0;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Bỏ J theo quy tắc Playfair
    char temp[26] = {0};
    k = 0;
    
    // Chuyển key về chữ cái in hoa và loại bỏ ký tự không phải chữ cái
    for(i = 0; key[i] != '\0'; i++) {
        if(isalpha(key[i])) {
            key[i] = toupper(key[i]);
            if(key[i] == 'J') key[i] = 'I'; // Thay J bằng I
            // Kiểm tra ký tự trùng
            for(j = 0; j < k; j++) {
                if(temp[j] == key[i]) {
                    flag = 1;
                    break;
                }
            }
            if(!flag) temp[k++] = key[i];
            flag = 0;
        }
    }
    
    // Thêm các chữ cái còn lại của bảng chữ cái
    for(i = 0; i < 26; i++) {
        for(j = 0; j < k; j++) {
            if(temp[j] == alphabet[i]) {
                flag = 1;
                break;
            }
        }
        if(!flag) temp[k++] = alphabet[i];
        flag = 0;
    }
    
    // Điền vào ma trận 5x5
    k = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            matrix[i][j] = temp[k++];
        }
    }
}

// Hàm tìm vị trí của ký tự trong ma trận
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    int i, j;
    if(ch == 'J') ch = 'I';
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Hàm chuẩn bị bản rõ
void preparePlaintext(char plaintext[], char prepared[]) {
    int i, k = 0;
    // Chuyển về chữ in hoa và chỉ giữ chữ cái
    for(i = 0; plaintext[i] != '\0'; i++) {
        if(isalpha(plaintext[i])) {
            prepared[k] = toupper(plaintext[i]);
            if(prepared[k] == 'J') prepared[k] = 'I';
            k++;
        }
    }
    prepared[k] = '\0';
    
    char temp[100] = {0};
    k = 0;
    for(i = 0; prepared[i] != '\0'; i++) {
        temp[k++] = prepared[i];
        if(prepared[i] == prepared[i+1] && prepared[i+1] != '\0') {
            temp[k++] = 'X';
        }
    }
    if(strlen(temp) % 2 != 0) temp[k++] = 'X';
    temp[k] = '\0';
    strcpy(prepared, temp);
}

// Hàm mã hóa Playfair
void playfairEncrypt(char plaintext[], char key[], char ciphertext[]) {
    char matrix[5][5];
    char prepared[100] = {0};
    int i, row1, col1, row2, col2;
    
    prepareKey(key, matrix);
    preparePlaintext(plaintext, prepared);
    
    // Mã hóa từng cặp ký tự
    for(i = 0; i < strlen(prepared); i += 2) {
        findPosition(matrix, prepared[i], &row1, &col1);
        findPosition(matrix, prepared[i+1], &row2, &col2);
        
        if(row1 == row2) { // Cùng hàng
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i+1] = matrix[row2][(col2 + 1) % 5];
        }
        else if(col1 == col2) { // Cùng cột
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i+1] = matrix[(row2 + 1) % 5][col2];
        }
        else { // Hình chữ nhật
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i+1] = matrix[row2][col1];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[100], key[100], ciphertext[100];
    
    printf("Nhap ban ro: ");
    fgets(plaintext, 100, stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;
    
    printf("Nhap key: ");
    fgets(key, 100, stdin);
    key[strcspn(key, "\n")] = 0;
    
    playfairEncrypt(plaintext, key, ciphertext);
    
    printf("Ban ma: %s\n", ciphertext);
    
    // In ma trận 5x5 để kiểm tra
    char matrix[5][5];
    prepareKey(key, matrix);
    printf("Ma tran Playfair:\n");
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}