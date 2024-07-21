// keywordcipher.cpp
#include "keyword.h"

QString KeywordCipher::generateKeywordAlphabet(const QString& keyword) {
    QString uniqueKeyword;
    for (const QChar& c : keyword) {
        if (!uniqueKeyword.contains(c, Qt::CaseInsensitive)) {
            uniqueKeyword += c.toUpper();
        }
    }

    QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString keywordAlphabet = uniqueKeyword;

    for (const QChar& c : alphabet) {
        if (!keywordAlphabet.contains(c)) {
            keywordAlphabet += c;
        }
    }

    return keywordAlphabet;
}

QString KeywordCipher::encrypt(const QString& plaintext, const QString& keyword) {
    QString encryptedText;

    QString keywordAlphabet = generateKeywordAlphabet(keyword);

    for (const QChar& c : plaintext) {
        if (c.isLetter()) {
            bool isUpperCase = c.isUpper();
            QChar letter = c.toUpper();

            int index = letter.toLatin1() - 'A';
            QChar encryptedChar = keywordAlphabet.at(index);

            encryptedText += isUpperCase ? encryptedChar : encryptedChar.toLower();
        } else {
            encryptedText += c;
        }
    }

    return encryptedText;
}

QString KeywordCipher::decrypt(const QString& ciphertext, const QString& keyword) {
    QString decryptedText;

    QString keywordAlphabet = generateKeywordAlphabet(keyword);
    QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (const QChar& c : ciphertext) {
        if (c.isLetter()) {
            bool isUpperCase = c.isUpper();
            QChar letter = c.toUpper();

            int index = keywordAlphabet.indexOf(letter);
            QChar decryptedChar = alphabet.at(index);

            decryptedText += isUpperCase ? decryptedChar : decryptedChar.toLower();
        } else {
            decryptedText += c;
        }
    }

    return decryptedText;
}
