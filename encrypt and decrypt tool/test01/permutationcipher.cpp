#include "PermutationCipher.h"
#include"permutationcipher.h"
#include"QString"
#include"QDebug"
// permutationcipher.cpp

#include "permutationcipher.h"

PermutationCipher::PermutationCipher(const QString& keyword) : keyword(keyword) {}

QString PermutationCipher::encrypt(const QString& plaintext) {
    QString ciphertext = plaintext;

    for (int i = 0; i < plaintext.length(); ++i) {
        int position = keyword.at(i).digitValue();
        ciphertext[i] = plaintext.at(position - 1);
    }

    return ciphertext;
}

QString PermutationCipher::decrypt(const QString& ciphertext) {
    QString plaintext = ciphertext;

    for (int i = 0; i < ciphertext.length(); ++i) {
        int position = keyword.at(i).digitValue();
        plaintext[position - 1] = ciphertext.at(i);
    }

    return plaintext;
}
