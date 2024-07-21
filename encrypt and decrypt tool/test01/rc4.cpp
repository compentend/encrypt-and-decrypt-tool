#include "rc4.h"

RC4Cipher::RC4Cipher(QObject *parent) : QObject(parent), i_(0), j_(0) {}

void RC4Cipher::ksa(const QVector<quint8> &key) {
    s_.resize(256);
    int keyLength = key.size();
    int j = 0;

    for (int i = 0; i < 256; ++i) {
        s_[i] = static_cast<quint8>(i);
    }

    for (int i = 0; i < 256; ++i) {
        j = (j + s_[i] + key[i % keyLength]) % 256;
        swap(s_, i, j);
    }
}

void RC4Cipher::swap(QVector<quint8> &s, int i, int j) {
    quint8 temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

QVector<quint8> RC4Cipher::encrypt(const QVector<quint8> &plaintext, const QVector<quint8> &key) {
    QVector<quint8> ciphertext;
    int n = plaintext.size();

    s_ = QVector<quint8>(256);
    i_ = 0;
    j_ = 0;

    ksa(key);

    for (int k = 0; k < n; ++k) {
        i_ = (i_ + 1) % 256;
        j_ = (j_ + s_[i_]) % 256;
        swap(s_, i_, j_);

        quint8 keyStream = s_[(s_[i_] + s_[j_]) % 256];
        ciphertext.push_back(plaintext[k] ^ keyStream);
    }

    return ciphertext;
}

QVector<quint8> RC4Cipher::decrypt(const QVector<quint8> &ciphertext, const QVector<quint8> &key) {
    // RC4加密和解密使用相同的算法
    return encrypt(ciphertext, key);
}
