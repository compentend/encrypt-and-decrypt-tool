// playfaircipher.h

#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include <QString>

class PlayfairCipher {
public:
    PlayfairCipher();
    QString encrypt(const QString& plaintext, const QString& key);
    QString decrypt(const QString& ciphertext, const QString& key);

private:
    QString preprocessText(const QString& text);
    void generateKeySquare(const QString& key);
    QString processText(const QString& text, const QString& key, bool encrypt);
    QChar* findPosition(QChar ch, const QString& key);
    QString encryptPair(QChar a, QChar b);
    QString decryptPair(QChar a, QChar b);

    QChar keySquare[5][5];
};

#endif // PLAYFAIRCIPHER_H
