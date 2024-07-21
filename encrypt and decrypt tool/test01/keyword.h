// keywordcipher.h
#ifndef KEYWORDCIPHER_H
#define KEYWORDCIPHER_H

#include <QString>

class KeywordCipher {
public:
    static QString encrypt(const QString& plaintext, const QString& keyword);
    static QString decrypt(const QString& ciphertext, const QString& keyword);
    static QString generateKeywordAlphabet(const QString& keyword);
};

#endif // KEYWORDCIPHER_H
