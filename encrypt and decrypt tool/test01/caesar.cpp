// caesarcipher.cpp


#include"caesar.h"

CaesarCipher::CaesarCipher()
{
    // 构造函数中可以进行一些初始化操作
}

QChar CaesarCipher::shiftChar(const QChar &ch, int shift)
{
    // 处理大写字母
    if (ch.isUpper()) {
        return QChar(((ch.toLatin1() - 'A' + shift) % 26) + 'A');
    }
    // 处理小写字母
    else if (ch.isLower()) {
        return QChar(((ch.toLatin1() - 'a' + shift) % 26) + 'a');
    }
    // 非字母字符不变
    else {
        return ch;
    }
}

QString CaesarCipher::encrypt(const QString &plainText, int shift)
{
    QString encryptedText;

    // 对每个字符进行加密
    for (const QChar &ch : plainText) {
        encryptedText.append(shiftChar(ch, shift));
    }

    return encryptedText;
}

QString CaesarCipher::decrypt(const QString &cipherText, int shift)
{
    // 解密实际上就是加密的逆过程，只需要将shift取反即可
    return encrypt(cipherText, -shift);
}
