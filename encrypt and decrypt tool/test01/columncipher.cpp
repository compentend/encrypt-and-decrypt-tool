
#include"QChar"

#include <QMap>
#include"columncipher.h"


QString ColumnarTransposition::encrypt(const QString &plaintext, const QString &key) {
    int columns = key.length();
    int rows = (plaintext.length() + columns - 1) / columns;

    QString matrix[rows][columns];

    // Fill the matrix with the plaintext
    int k = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (k < plaintext.length()) {
                matrix[i][j] = plaintext[k++];
            } else {
                matrix[i][j] = ' ';  // Padding with spaces if needed
            }
        }
    }

    // Create the ciphertext by reading the matrix columns based on the key
    QString ciphertext;
    for (int col = 0; col < columns; ++col) {
        int colIndex = key.indexOf(QChar('1' + col));
        for (int row = 0; row < rows; ++row) {
            ciphertext += matrix[row][colIndex];
        }
    }

    return ciphertext;
}

QString ColumnarTransposition::decrypt(const QString &ciphertext, const QString &key) {
    int columns = key.length();
    int rows = (ciphertext.length() + columns - 1) / columns;

    QString matrix[rows][columns];

    // Fill the matrix with the ciphertext based on the key
    int k = 0;
    for (int col = 0; col < columns; ++col) {
        int colIndex = key.indexOf(QChar('1' + col));
        for (int row = 0; row < rows; ++row) {
            matrix[row][colIndex] = ciphertext[k++];
        }
    }

    // Create the plaintext by reading the matrix row by row
    QString plaintext;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            plaintext += matrix[i][j];
        }
    }

    return plaintext.trimmed();  // Remove any trailing spaces
}
