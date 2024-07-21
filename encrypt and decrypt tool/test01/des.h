// des.h
#ifndef DES_H
#define DES_H

#include "QString"

class des {
public:
    des();
    QString des_encrypt(QString  str1, QString  str2);

    QString des_decrypt( QString ciphertext);
};

#endif // DES_H
