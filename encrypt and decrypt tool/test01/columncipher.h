#ifndef COLUMNARTRANSPOSITION_H
#define COLUMNARTRANSPOSITION_H

#include <QString>

class ColumnarTransposition
{
public:
    ColumnarTransposition();

    static QString encrypt(const QString &plaintext, const QString &key);
    static QString decrypt(const QString &ciphertext, const QString &key);
};

#endif // COLUMNARTRANSPOSITION_H
