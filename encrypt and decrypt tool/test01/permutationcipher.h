// permutationcipher.h

#ifndef PERMUTATIONCIPHER_H
#define PERMUTATIONCIPHER_H

#include <QString>

class PermutationCipher {
public:
    PermutationCipher(const QString& keyword);

    QString encrypt(const QString& plaintext);
    QString decrypt(const QString& ciphertext);


    QString keyword;
};

#endif // PERMUTATIONCIPHER_H
