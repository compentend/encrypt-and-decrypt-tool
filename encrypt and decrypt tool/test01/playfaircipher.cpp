#include "playfaircipher.h"
#include "cctype"
#include"QString"
#include"QPair"
#include"QDebug"
#include <iostream>
#include"QRegularExpression"
#include"QCoreApplication"

// playfaircipher.cpp

// playfaircipher.cpp

#include "playfaircipher.h"
#include <QStringList>
#include <QSet>

PlayfairCipher::PlayfairCipher() {}

QString PlayfairCipher::encrypt(const QString& plaintext, const QString& key) {
    QString processedText = preprocessText(plaintext);
    generateKeySquare(key);
    return processText(processedText, key, true);
}

QString PlayfairCipher::decrypt(const QString& ciphertext, const QString& key) {
    QString processedText = preprocessText(ciphertext);
    generateKeySquare(key);
    return processText(processedText, key, false);
}

QString PlayfairCipher::preprocessText(const QString& text) {
    // Remove spaces and non-alphabetic characters, convert to uppercase
    QString processedText = text.toUpper().remove(' ');
    int len = processedText.length();
    for (int i = 1; i < len; ++i) {
        if (processedText[i] == processedText[i - 1]) {
            processedText.insert(i, 'X');
            len++;
        }
    }
    if (len % 2 != 0) {
        processedText.append('X');
    }
    return processedText;
}

void PlayfairCipher::generateKeySquare(const QString& key) {
    QString tempKey = key.toUpper() + "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    QSet<QChar> keySet;
    int index = 0;

    for (QChar ch : tempKey) {
        if (ch != 'J') {
            if (!keySet.contains(ch)) {
                keySet.insert(ch);
                keySquare[index / 5][index % 5] = ch;
                index++;
            }
        }
    }
}

QString PlayfairCipher::processText(const QString& text, const QString& key, bool encrypt) {
    QString result;
    int len = text.length();
    for (int i = 0; i < len; i += 2) {
        QChar a = text[i];
        QChar b = text[i + 1];
        QString processedPair;
        if (encrypt) {
            processedPair = encryptPair(a, b);
        } else {
            processedPair = decryptPair(a, b);
        }
        result.append(processedPair);
    }
    return result;
}

QChar* PlayfairCipher::findPosition(QChar ch, const QString& key) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (keySquare[i][j] == ch) {
                return &keySquare[i][j];
            }
        }
    }
    return nullptr;
}

QString PlayfairCipher::encryptPair(QChar a, QChar b) {
    int row1, col1, row2, col2;
    QChar* pos1 = findPosition(a, QString::fromRawData(&keySquare[0][0], 25));
    QChar* pos2 = findPosition(b, QString::fromRawData(&keySquare[0][0], 25));

    if (pos1 == nullptr || pos2 == nullptr) {
        return "";
    }

    if (pos1 == pos2) {
        return "";
    }

    row1 = (pos1 - &keySquare[0][0]) / 5;
    col1 = (pos1 - &keySquare[0][0]) % 5;
    row2 = (pos2 - &keySquare[0][0]) / 5;
    col2 = (pos2 - &keySquare[0][0]) % 5;

    if (row1 == row2) {
        return QString("%1%2").arg(keySquare[row1][(col1 + 1) % 5]).arg(keySquare[row2][(col2 + 1) % 5]);
    } else if (col1 == col2) {
        return QString("%1%2").arg(keySquare[(row1 + 1) % 5][col1]).arg(keySquare[(row2 + 1) % 5][col2]);
    } else {
        return QString("%1%2").arg(keySquare[row1][col2]).arg(keySquare[row2][col1]);
    }
}

QString PlayfairCipher::decryptPair(QChar a, QChar b) {
    int row1, col1, row2, col2;
    QChar* pos1 = findPosition(a, QString::fromRawData(&keySquare[0][0], 25));
    QChar* pos2 = findPosition(b, QString::fromRawData(&keySquare[0][0], 25));

    if (pos1 == nullptr || pos2 == nullptr) {
        return "";
    }

    if (pos1 == pos2) {
        return "";
    }

    row1 = (pos1 - &keySquare[0][0]) / 5;
    col1 = (pos1 - &keySquare[0][0]) % 5;
    row2 = (pos2 - &keySquare[0][0]) / 5;
    col2 = (pos2 - &keySquare[0][0]) % 5;

    if (row1 == row2) {
        return QString("%1%2").arg(keySquare[row1][(col1 + 4) % 5]).arg(keySquare[row2][(col2 + 4) % 5]);
    } else if (col1 == col2) {
        return QString("%1%2").arg(keySquare[(row1 + 4) % 5][col1]).arg(keySquare[(row2 + 4) % 5][col2]);
    } else {
        return QString("%1%2").arg(keySquare[row1][col2]).arg(keySquare[row2][col1]);
    }
}
