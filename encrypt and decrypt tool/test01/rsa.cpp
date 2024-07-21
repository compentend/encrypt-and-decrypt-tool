#include "rsa.h"
#include"QString"
#include <QtCore>
#include"math.h"
#include <QTextStream>


rsa::rsa()
{

}
static qint64 gcd(qint64 a, qint64 b) {
    if (a < b) {
        qint64 temp = b;
        b = a;
        a = temp;
    }

    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}
static qint64 ExtendEculid(qint64 n1, qint64 n2, qint64 b1, qint64 b2) {
    qint64 q, r;
    q = n1 / n2;
    r = n1 - q * n2;
    if (r != 0) {
        qint64 temp = b1 - q * b2;
        ExtendEculid(n2, r, b2, temp);
    }
    if (n2 == 1)
        return b2;
}
void Inverse_element() {
    QTextStream cout(stdout);
    QTextStream cin(stdin);

    cout << "u * v == 1(mod n)\n";
    cout << "";

    qint64 u, n, t;
    cout << "请输入u：";
    cin >> u;
    cout << "请输入n：";
    cin >> n;


}
static qint64 Power_mul(qint64 a, qint64 b, qint64 c, qint64 n) {
    // 初始a=x,b=r,c=1
    while (b != 0) {
        while (b % 2 == 0) {
            b /= 2;
            a = (a * a) % n;
        }
        b -= 1;
        c = (c * a) % n;
    }
    return c;
}
int ProducePrimeNumber(int prime[]) {
    int c = 0;
    bool vis[1001];
    memset(vis, 0, sizeof(vis));

    for (int i = 2; i <= 1000; i++)
        if (!vis[i]) {
            prime[c++] = i;
            for (int j = i * i; j <= 1000; j += i)
                vis[j] = true;
        }

    return c;
}
int n, e, d;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int ExtendEculid(int n1, int n2, int b1, int b2) {
    int q, r;
    q = n1 / n2;
    r = n1 - q * n2;
    if (r != 0) {
        int temp = b1 - q * b2;
        ExtendEculid(n2, r, b2, temp);
    }
    if (n2 == 1)
        return b2;
}



void RSA_Initialize() {
    // 取出1000内素数保存在prime[]数组中
    int prime[5000];
    int count_Prime = ProducePrimeNumber(prime);

    // 随机取两个素数p,q
    srand((unsigned)time(NULL));
    int ranNum1 = rand() % count_Prime;
    int ranNum2 = rand() % count_Prime;
    int p = prime[ranNum1], q = prime[ranNum2];

    n = p * q;
    int On = (p - 1) * (q - 1);

    // 用欧几里德扩展算法求e,d
    for (int j = 2; j < On; j += 1331) {
        d = ExtendEculid(On, j, 0, 1);
        if (gcd(On, j) == 1 && d > 0) {
            e = j;
            break;
        }
    }
}
extern int e, n, d; // Assuming these are declared elsewhere

void rsa::RSA_Encrypt() {
    QTextStream cout(stdout);

    //cout << endl;
    //cout << "公钥(e, n) : e = " << e << " n = " << n << "\t";
    //cout << "私钥(d, n) : d = " << d << " n = " << n << endl;

    int Plaintext[100]; // Assuming Plaintext is defined elsewhere
    /*int Ciphertext[100];

    int i = 0;
    for (i = 0; i < 100; i++)
        Ciphertext[i] = Power_mul(Plaintext[i], e, 1, n);

    //cout << endl;
    cout << "用公钥(e, n)加密出的密文如下:";
    for (i = 0; i < 100; i++)
        cout << Ciphertext[i] << " ";
    //cout << endl;*/
}
#include <QtCore>

extern int e, n, d; // Assuming these are declared elsewhere

void rsa::RSA_Decrypt() {
    QTextStream cout(stdout);

    int Ciphertext[100]; // Assuming Ciphertext is defined elsewhere
    /*char Plaintext_C[100];

    int i = 0;
    for (i = 0; i < 100; i++)
        Plaintext_C[i] = static_cast<char>(Power_mul(Ciphertext[i], d, 1, n));

    //cout << endl;
    cout << "用私钥(d, n)解密出的明文如下:";
    for (i = 0; i < 100; i++)
        cout << Plaintext_C[i];
    //cout << endl;*/
}

char Plaintext[100]; // Assuming Plaintext is declared globally

void Initialize() {
    QTextStream cout(stdout);

    QString ch = "I LOVE NEU";
    int counter = ch.length();

    int i, j = 0;
    for (i = 0; i < 100; i++) {
        if (j != counter) {
            Plaintext[i] = ch[j].toLatin1();
            j++;
        } else {
            Plaintext[i] = 32; // 空格
        }
    }

    cout << "明文如下:";
    for (i = 0; i < 100; i++) {
        cout << Plaintext[i];
    }
    //cout << endl;
}

