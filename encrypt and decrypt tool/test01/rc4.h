#ifndef RC4CIPHER_H
#define RC4CIPHER_H

#include <QObject>
#include <QVector>

class RC4Cipher : public QObject
{
    Q_OBJECT

public:
    explicit RC4Cipher(QObject *parent = nullptr);
    QVector<quint8> encrypt(const QVector<quint8> &plaintext, const QVector<quint8> &key);
    QVector<quint8> decrypt(const QVector<quint8> &ciphertext, const QVector<quint8> &key);

private:
    void ksa(const QVector<quint8> &key);
    void swap(QVector<quint8> &s, int i, int j);

    QVector<quint8> s_;
    int i_;
    int j_;
};

#endif // RC4CIPHER_H
