#include "dh.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include"QDebug"
#include <QMessageBox>
DHKeyExchange::DHKeyExchange(QObject *parent) : QObject(parent)
{
    srand(time(nullptr)); // 设置随机种子
}

// 判断一个数是否为素数
bool DHKeyExchange::isPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    if (n <= 3)
    {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6)
    { // 除了2和3之外，所有的素数都可以表示为6k±1的形式
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

// 生成一个随机的大素数
int DHKeyExchange::generatePrime(int min, int max)
{
    int p;
    do
    {
        p = rand() % (max - min + 1) + min;
    } while (!isPrime(p));
    return p;
}

// 计算幂运算与模运算
int DHKeyExchange::modPow(int base, int exponent, int modulus)
{
    int result = 1;
    base = base % modulus;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

// DH密钥交换
void DHKeyExchange::performDHKeyExchange(int p, int g, int a, int b)
{
    // 计算 A = g^a mod p
    int A = modPow(g, a, p);
    // 计算 B = g^b mod p
    int B = modPow(g, b, p);
    // 计算共享密钥 K = B^a mod p
    int K1 = modPow(B, a, p);
    // 计算共享密钥 K = A^b mod p
    int K2 = modPow(A, b, p);
    // 输出结果
    QMessageBox msgBox;

    // 设置信息框的标题
    msgBox.setWindowTitle("DH密钥交换");

    // 设置信息框的文本内容
    QString message = QString("Alice发送的A：%1\nBob发送的B：%2\nAlice计算的共享密钥K：%3\nBob计算的共享密钥K：%4")
                          .arg(A)
                          .arg(B)
                          .arg(K1)
                          .arg(K2);

    // 设置信息框的文本内容
    msgBox.setText(message);
    msgBox.exec();
    /* qDebug()<<A;
    qDebug()<<B;
    qDebug()<<K1;
    qDebug()<<K2;
    std::cout << "Alice发送的A：" << A << std::endl;
            std::cout << "Bob发送的B：" << B << std::endl;
                     std::cout << "Alice计算的共享密钥K：" << K1 << std::endl;
        std::cout << "Bob计算的共享密钥K：" << K2 << std::endl;*/
}
