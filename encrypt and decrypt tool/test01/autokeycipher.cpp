#include "AutokeyCipher.h"
#include"autokeycipher.h"
#include <QString>
#include"autokeycipher.h"

QString AutokeyCipher::cleanText(const QString& text) {
    QString cleanedText;
    for (const QChar& c : text) {
        if (c.isLetter()) {
            cleanedText.append(c.toUpper());
        }
    }
    return cleanedText;
}

QString AutokeyCipher::encrypt(const QString& plainText, const QString& key) {
    QString cleanedPlainText = cleanText(plainText);
    QString cleanedKey = cleanText(key);

    // 将明文追加到关键字后形成密钥
    QString fullKey = cleanedKey + cleanedPlainText;
    QString encryptedText;

    for (int i = 0; i < cleanedPlainText.length(); ++i) {
        QChar plainChar = cleanedPlainText.at(i);
        QChar keyChar = fullKey.at(i);

        int plainValue = plainChar.toLatin1() - 'A';
        int keyValue = keyChar.toLatin1() - 'A';

        char encryptedChar = ((plainValue + keyValue) % 26) + 'A';
        encryptedText.append(encryptedChar);
    }

    return encryptedText;
}

QString AutokeyCipher::decrypt(const QString& cipherText, const QString& key) {
    QString cleanedKey = cleanText(key);
    QString decryptedText;

    for (int i = 0; i < cipherText.length(); ++i) {
        QChar cipherChar = cipherText.at(i);
        QChar keyChar = cleanedKey.at(i);

        int cipherValue = cipherChar.toLatin1() - 'A';
        int keyValue = keyChar.toLatin1() - 'A';

        char decryptedChar = (((cipherValue - keyValue) + 26) % 26) + 'A';
        decryptedText.append(decryptedChar);

        // 更新关键字
        cleanedKey.append(decryptedChar);
    }

    return decryptedText;
}
