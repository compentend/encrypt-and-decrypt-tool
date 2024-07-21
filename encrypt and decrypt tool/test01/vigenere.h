#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <QString>

class VigenereCipher {
public:
    static QString encrypt(const QString& plainText, const QString& key);
    static QString decrypt(const QString& cipherText, const QString& key);

private:
    static QString cleanText(const QString& text);
};

#endif // VIGENERECIPHER_H
