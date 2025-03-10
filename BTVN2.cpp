#include <iostream>
#include <string>

using namespace std;

class RC4 {
private:
    unsigned char S[256]; 
    int i, j; 

    // Khởi tạo S-box với khóa mật
    void KSA(const string& key) {
        int key_length = key.size();
        for (int i = 0; i < 256; i++) S[i] = i;

        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + S[i] + key[i % key_length]) % 256;
            swap(S[i], S[j]); // Trao đổi giá trị 
        }
        i = j = 0;
    }

    // Sinh byte keystream từ S-box
    unsigned char PRGA() {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        return S[(S[i] + S[j]) % 256];
    }

public:
    // Hàm khởi tạo với khóa mật
    RC4(const string& key) {
        KSA(key);
    }

    // Hàm mã hóa bằng RC4
    void encrypt(const string& plaintext, unsigned char* ciphertext) {
        for (size_t k = 0; k < plaintext.size(); k++) {
            unsigned char keystream_byte = PRGA(); 
            ciphertext[k] = plaintext[k] ^ keystream_byte; 
            cout << hex << (int)keystream_byte << " "; 
        }
        cout << endl;
    }
};

// Hàm in dữ liệu dưới dạng hex
void printHex(const unsigned char* data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        cout << hex << (int)data[i] << " ";
    }
    cout << endl;
}

int main() {
    string key = "mysecretkey"; // Khóa mật tự định nghĩa
    string plaintext = "Hanoi University of Science and Technology";
    unsigned char ciphertext[plaintext.size()];

    RC4 rc4(key);
    cout << "Keystream: ";
    rc4.encrypt(plaintext, ciphertext);

    cout << "Ciphertext: ";
    printHex(ciphertext, plaintext.size());
    return 0;
}
