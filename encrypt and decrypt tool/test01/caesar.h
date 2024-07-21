// caesarcipher.h

#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <QString>

class CaesarCipher
{
public:
    // 构造函数
    CaesarCipher();

    // 加密函数
    QString encrypt(const QString &plainText, int shift);

    // 解密函数
    QString decrypt(const QString &cipherText, int shift);

private:
    // 辅助函数，用于对单个字符进行加解密
    QChar shiftChar(const QChar &ch, int shift);
};

#endif // CAESARCIPHER_H
