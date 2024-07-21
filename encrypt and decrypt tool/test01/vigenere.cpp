#include"vigenere.h"

QString VigenereCipher::cleanText(const QString& text) {
    QString cleanedText;
    for (const QChar& c : text) {
        if (c.isLetter()) {
            cleanedText.append(c.toUpper());
        }
    }
    return cleanedText;
}

QString VigenereCipher::encrypt(const QString& plainText, const QString& key) {
    QString cleanedPlainText = cleanText(plainText);
    QString encryptedText;

    int keyLength = key.length();
    int textLength = cleanedPlainText.length();

    for (int i = 0; i < textLength; ++i) {
        QChar plainChar = cleanedPlainText.at(i);
        QChar keyChar = key.at(i % keyLength);

        int plainValue = plainChar.toLatin1() - 'A';
        int keyValue = keyChar.toUpper().toLatin1() - 'A';

        char encryptedChar = ((plainValue + keyValue) % 26) + 'A';
        encryptedText.append(encryptedChar);
    }

    return encryptedText;
}

QString VigenereCipher::decrypt(const QString& cipherText, const QString& key) {
    QString decryptedText;

    int keyLength = key.length();
    int textLength = cipherText.length();

    for (int i = 0; i < textLength; ++i) {
        QChar cipherChar = cipherText.at(i);
        QChar keyChar = key.at(i % keyLength);

        int cipherValue = cipherChar.toUpper().toLatin1() - 'A';
        int keyValue = keyChar.toUpper().toLatin1() - 'A';

        char decryptedChar = (((cipherValue - keyValue) + 26) % 26) + 'A';
        decryptedText.append(decryptedChar);
    }

    return decryptedText;
}
