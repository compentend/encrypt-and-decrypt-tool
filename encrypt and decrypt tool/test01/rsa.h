#ifndef RSA_H
#define RSA_H
#include"QString"


class rsa
{
public:
    rsa();
    void RSA_Encrypt();
    void RSA_Decrypt();
    int ProducePrimeNumber(int prime[]);
    static qint64 Power_mul(qint64 a, qint64 b, qint64 c, qint64 n);
};

#endif // RSA_H
