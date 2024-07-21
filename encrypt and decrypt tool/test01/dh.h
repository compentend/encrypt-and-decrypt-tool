#ifndef DHKEYEXCHANGE_H
#define DHKEYEXCHANGE_H

#include <QObject>

class DHKeyExchange : public QObject
{
    Q_OBJECT

public:
    explicit DHKeyExchange(QObject *parent = nullptr);

    // 判断一个数是否为素数
    bool isPrime(int n);

    // 生成一个随机的大素数
    int generatePrime(int min, int max);

    // 计算幂运算与模运算
    int modPow(int base, int exponent, int modulus);

    // DH密钥交换
    void performDHKeyExchange(int p, int g, int a, int b);

signals:

public slots:
};

#endif // DHKEYEXCHANGE_H
