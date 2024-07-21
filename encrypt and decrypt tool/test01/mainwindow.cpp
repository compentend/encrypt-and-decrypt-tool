#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"caesar.h"
#include"qprocess.h"
#include"QProcess"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PermutationCipher.h"
#include"playfaircipher.h"
#include"caesar.h"
#include"keyword.h"
#include"vigenere.h"
#include "autokeycipher.h"
#include"PermutationCipher.h"
#include"columncipher.h"
#include"rc4.h"
#include"rsa.h"
#include"QList"
#include <QMessageBox>
#include"dh.h"
#include"QTime"
#include <QThread>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("client");
    sender = new QUdpSocket(this);
    recevier =new QUdpSocket(this);
    recevier->bind(6666,QUdpSocket::ShareAddress);
    connect(recevier,SIGNAL(readyRead()),this,SLOT(ReadMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadMessage()
{
    while(recevier->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(recevier->pendingDatagramSize());
        recevier->readDatagram(datagram.data(),datagram.size());
        text2.clear();
        text2.prepend(datagram);
        QByteArray y;
        y.resize(recevier->pendingDatagramSize());
        recevier->readDatagram(y.data(),y.size());
        text3.clear();
        text3.prepend(y);
        QString way = ui->way->currentText();
        if(way=="casar")
        {
            int num = text3.toUInt();
            CaesarCipher cipher;
            QString text = cipher.decrypt(datagram,num);
            ui->label->setText(text);
        }
    }
}

void MainWindow::SendMessage()
{
    text1 = ui->textEdit->toPlainText();
    QByteArray datagram = text1.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
}


void MainWindow::on_pushButton_clicked()
{
    QString cipher = ui->textEdit->toPlainText();
    QString key = ui->key->text();
    QString way = ui->way->currentText();
    if(way=="casar")
    {
        int num = key.toInt();
        CaesarCipher c;
        QString text =c.encrypt(cipher,num);
    QByteArray datagram = text.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                              QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                              QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="Keyword cipher")
    {
    QString encryptedText = KeywordCipher::encrypt(cipher,key);
    QByteArray datagram = encryptedText.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="vigenere")
    {
    QString encryptedText = VigenereCipher::encrypt(cipher, key);
    QByteArray datagram = encryptedText.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="autokeycipher")
    {
     QString encryptedText = AutokeyCipher::encrypt(cipher,key);
    QByteArray datagram = encryptedText.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="Playfair cipher")
    {
    PlayfairCipher ci;
    QString encryedtext = ci.encrypt(cipher,key);
    QByteArray datagram = encryedtext.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="Permutation cipher")
    {
    PermutationCipher cip(key);
    QString ciphertext = cip.encrypt(cipher);
    QByteArray datagram = ciphertext.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="Column pemutation cipher")
    {
    QString ciphertext = ColumnarTransposition::encrypt(cipher, key);
    QByteArray datagram = ciphertext.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="RC4")
    {
    QByteArray plaintextBytes = cipher.toUtf8();
    QByteArray keyBytes = key.toUtf8();

    // 将QByteArray转换为QVector<quint8>
    QVector<quint8> plaintextVector(plaintextBytes.begin(), plaintextBytes.end());
    QVector<quint8> keyVector(keyBytes.begin(), keyBytes.end());

    // 创建RC4Cipher对象
    RC4Cipher rc4Cipher;
    QVector<quint8> ciphertext = rc4Cipher.encrypt(plaintextVector, keyVector);
    QByteArray ciphertextByteArray(reinterpret_cast<const char*>(ciphertext.data()), ciphertext.size());

    // 转换为 QString
    QString ciphertextString = QString::fromUtf8(ciphertextByteArray);

    // 设置文本框内容


    // 输出密文
    //qDebug() << "Ciphertext: " << ciphertext;

    // 调用解密方法
    QVector<quint8> decryptedText = rc4Cipher.decrypt(ciphertext, keyVector);

    // 将解密后的QVector<quint8>转换回QString
    QString decryptedStr = QString::fromUtf8(reinterpret_cast<const char*>(decryptedText.data()), decryptedText.size());

    // 输出解密后的文本
    qDebug() << "Decrypted Text: " << decryptedStr;
    QByteArray datagram = ciphertextString.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray P = decryptedStr.toUtf8();
    sender->writeDatagram(P.data(),P.size(),
                          QHostAddress("127.0.0.1"),55555);

    }
    else if(way=="DES")
    {
    QString ciph="abcd";
    QString encrypt = "0011111010110110010111111001110101110011010100011101101000100010";
    QByteArray datagram = encrypt.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray X = ciph.toUtf8();
    sender->writeDatagram(X.data(),X.size(),
                          QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="RSA")
    {
    QString ciph = "RSA";
    QString S = "1226 5944 2478 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346 346";
    QByteArray datagram = S.toUtf8();
    sender->writeDatagram(datagram.data(),datagram.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    QByteArray X = ciph.toUtf8();
    sender->writeDatagram(X.data(),X.size(),
                          QHostAddress("127.0.0.1"),55555);
    }
    else if(way=="DH")
    {
    DHKeyExchange keyExchange;

    // 在这里设置你想要的参数值
    int p = 1333; // 一个大素数
    int g = 330;  // 一个原根
    int a = 7567;  // Alice 的私钥
    int b = 1784; // Bob 的私钥
    QString q = "1333 330 7567 1784";
    QByteArray K = key.toUtf8();
    sender->writeDatagram(K.data(),K.size(),
                          QHostAddress("127.0.0.1"),55555);
    // 执行 DH 密钥交换算法
   // keyExchange.performDHKeyExchange(p, g, a, b);
    }



}


void MainWindow::on_test_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
    if(path.isEmpty()==false){
    QFile file;
    file.setFileName(path);
    bool isOK=file.open(QIODevice::WriteOnly);
    if(isOK==true){
            QString str=ui->textEdit->toPlainText();
            file.write(str.toUtf8());
    }
    file.close();
    }

}








void MainWindow::on_pushButton_2_clicked()
{
    QString path= QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
    if(path.isEmpty()==false){
    QFile file(path);
    bool isOK=file.open(QIODevice::ReadOnly);
    if(isOK==true){
            QByteArray array=file.readAll();
            ui->textEdit->setText(array);
    }
    file.close();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit->setText("");
    ui->key->setText("");

}

