#ifndef AUTOKEYCIPHER_H
#define AUTOKEYCIPHER_H

#include <QString>

class AutokeyCipher {
public:
    static QString encrypt(const QString& plainText, const QString& key);
    static QString decrypt(const QString& cipherText, const QString& key);


    static QString generateAutokey(const QString& key, int length);
    static QString cleanText(const QString& text);
};

#endif // AUTOKEYCIPHER_H
