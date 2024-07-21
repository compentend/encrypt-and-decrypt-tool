#include "des.h"
#include"QString"
#include"QVector"
#include <QBitArray>
#include"des.h"
QString des_StrToBitStr(const QString& str);
des::des()
{

}


QString desKeys[20];

QVector<QVector<int>> T1 = {
    {58, 50, 42, 34, 26, 18, 10, 2},
    {60, 52, 44, 36, 28, 20, 12, 4},
    {62, 54, 46, 38, 30, 22, 14, 6},
    {64, 56, 48, 40, 32, 24, 16, 8},
    {57, 49, 41, 33, 25, 17, 9, 1},
    {59, 51, 43, 35, 27, 19, 11, 3},
    {61, 53, 45, 37, 29, 21, 13, 5},
    {63, 55, 47, 39, 31, 23, 15, 7}
};


/**
 * 密钥置换表
 */
QVector<QVector<int>> T2 = {
    {57, 49, 41, 33, 25, 17, 9},
    {1, 58, 50, 42, 34, 26, 18},
    {10, 2, 59, 51, 43, 35, 27},
    {19, 11, 3, 60, 52, 44, 36},
    {3, 55, 47, 39, 31, 23, 15},
    {7, 62, 54, 46, 38, 30, 22},
    {14, 6, 61, 53, 45, 37, 29},
    {21, 13, 5, 28, 20, 12, 4}
};

/**
 * 密钥循环左移位数表
 */
QVector<int> T3 = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

/**
 * 密钥压缩置换表
 */
QVector<QVector<int>> T4 = {
    {14, 17, 11, 24, 1, 5},
    {3, 28, 15, 6, 21, 10},
    {23, 19, 12, 4, 26, 8},
    {16, 7, 27, 20, 13, 2},
    {41, 52, 31, 37, 47, 55},
    {30, 40, 51, 45, 33, 48},
    {44, 49, 39, 56, 34, 53},
    {46, 42, 50, 36, 29, 32}
};
QVector<QVector<int>> T5 ={
    { 32,1,2,3,4,5,
     4,5,6,7,8,9,
     8,9,10,11,12,13,
     12,13,14,15,16,17,
     16,17,18,19,20,21,
     20,21,22,23,24,25,
     24,25,26,27,28,29,
     28,29,30,31,32,1 }
};
QVector<QVector<QVector<int>>> S = {
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};
QVector<QVector<int>> P = {
    {16, 7, 20, 21},
    {29, 12, 28, 17},
    {1, 15, 23, 26},
    {5, 18, 31, 10},
    {2, 8, 24, 14},
    {32, 27, 3, 9},
    {19, 13, 30, 6},
    {22, 11, 4, 25}
};

/**
 * 最终置换表
 */
QVector<QVector<int>> T6 = {
    {40, 8, 48, 16, 56, 24, 64, 32},
    {39, 7, 47, 15, 55, 23, 63, 31},
    {38, 6, 46, 14, 54, 22, 62, 30},
    {37, 5, 45, 13, 53, 21, 61, 29},
    {36, 4, 44, 12, 52, 20, 60, 28},
    {35, 3, 43, 11, 51, 19, 59, 27},
    {34, 2, 42, 10, 50, 18, 58, 26},
    {33, 1, 41, 9, 49, 17, 57, 25}
};
QString final_permutation(const QString& s)
{
    QString rs;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            rs += s[T6[i][j] - 1];
        }
    }
    return rs;
}
QString P_box(const QString& s)
{
    QString rs;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            rs += s[P[i][j] - 1];
        }
    }
    return rs;
}


QString S_box(const QString& s)
{
    QString rs;
    QString s1;
    int k1, k2;  // S盒的行号和列号
    int h = 1;   // 决定使用那个S盒

    for (int i = 0; i <= 42; i = i + 6, h++)
    {
        k1 = (s[i].digitValue()) * 2 + (s[i + 5].digitValue()) * 1;
        k2 = (s[i + 1].digitValue()) * 8 + (s[i + 2].digitValue()) * 4 + (s[i + 3].digitValue()) * 2 + (s[i + 4].digitValue()) * 1;

        int x = S[h - 1][k1][k2];
        s1 = "";

        for (int j = 3; j >= 0; j--)
        {
            s1 += QString::number((x >> j) & 1);  // 从高位到低位取每一位的值
        }

        rs += s1;
    }
    return rs;
}


QString desXOR(const QString& s1, const QString& s2)
{
    QString rs;
    int length = qMin(s1.length(), s2.length());

    for (int i = 0; i < length; i++)
    {
        rs += QChar((s1[i].digitValue() ^ s2[i].digitValue()) + '0');
    }

    return rs;
}


QString plaintext_righthalf_extended_permutation(const QString& s)
{
    QString rs;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            rs += s[T5[i][j] - 1];
        }
    }
    return rs;
}


QString secret_key_compression_replacement(const QString& s)
{
    QString rs;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            rs += s[T4[i][j] - 1];
        }
    }
    return rs;
}

QString secret_ket_left_move(int k, const QString& s)
{
    QString s1 = s.mid(0, 28);
    QString s2 = s.mid(28, 28);

    QString rs = s1.mid(k, 28 - k) + s1.mid(0, k) + s2.mid(k, 28 - k) + s2.mid(0, k);

    return rs;
}


QString secret_key_initial_permutation(const QString& s)
{
    QString rs;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            rs += s[T2[i][j] - 1];
        }
    }

    return rs;
}

QString plaintext_initial_permutation(const QString& s)
{
    QString rs;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            rs += s[T1[i][j] - 1];
        }
    }
    return rs;
}


QString des_H(const QString& s)
{
    QString rs;
    for (int i = 0; i < s.length(); i++)
    {
        int x;
        if (s[i] >= '0' && s[i] <= '9')
        {
            x = s[i].digitValue(); // 使用 digitValue() 获取数字字符的数值
        }
        else
        {
            x = s[i].toLatin1() - 'A' + 10;
        }
        QString s1;
        int y = 8;
        for (int j = 1; j <= 4; j++)
        {
            if (x < y)
            {
                y /= 2;
                s1 += "0";
            }
            else
            {
                s1 += "1";
                x = x % y;
                y = y / 2;
            }
        }
        rs += s1;
    }
    return rs;
}


QString des_G(const QString& str)
{
    QString rs;
    QChar temp;
    for (int i = 0; i <= str.length() - 4; i = i + 4)
    {
        int x = (str[i].digitValue() * 8) + (str[i + 1].digitValue() * 4) + (str[i + 2].digitValue() * 2) + str[i + 3].digitValue();

        if (x >= 10)
        {
            temp = QChar(x - 10 + 'A');
        }
        else
        {
            temp = QChar(x + '0');
        }
        rs += temp;
    }
    return rs;
}


QString des_f(const QString& str1, const QString& str2)
{
    QString expendR = plaintext_righthalf_extended_permutation(str1);
    //cout<<"32位数据扩展为48位结果:"<<expendR<<endl;

    QString rs = desXOR(expendR, str2);
    //cout<<"密钥和扩展数据异或结果:"<<rs<<endl;

    rs = S_box(rs);
    //cout<<"S盒替代结果(48->32):"<<rs<<endl;

    rs = P_box(rs);
    //cout<<"P盒替代结果(32->32):"<<rs<<endl;

    return rs;
}


void des_generateKeys(QString s)
{
    s = secret_key_initial_permutation(s);

    for (int i = 1; i <= 16; i++)
    {
        s = secret_ket_left_move(T3[i - 1], s);
        desKeys[i] = secret_key_compression_replacement(s);
    }
}


QString des_BitStrToStr(const QString& bstr)
{
    QString str = "";
    // 每八位转化成十进制，然后将数字结果转化成字符
    int sum;
    for (int i = 0; i < bstr.size(); i += 8)
    {
        sum = 0;
        for (int j = 0; j < 8; j++)
        {
            if (bstr[i + j] == '1')
                sum = sum * 2 + 1;
            else
                sum = sum * 2;
        }
        str = str + QChar(sum);
    }
    return str;
}


QString chardeel(const QString& str1, QString& str2) {
    QString temp_str = "";
    int divi_times = (str1.size() % 8 ? str1.size() / 8 + 1 : str1.size() / 8); // 计算分组个数
    for (int i = 0; i < divi_times; ++i) {                                     // 每个分组单独转换成二进制串
        QString str1_temp = str1.mid(8 * i, 8);  // 使用mid(start, len)来代替substr(start,len)

        bool jude = false;
        int addchar = 0;
        if (str1_temp.size() % 8) {
            jude = true;
            addchar = 8 - str1_temp.size() % 8;
        }
        int sub = str1_temp.size() * 8;
        if (jude) {
            for (int i = 0; i < addchar; ++i) {
                str1_temp += 'a';  // 注意这里添加的字符是否合适
            }
        }
        str1_temp = des_StrToBitStr(str1_temp);
        if (jude) {
            for (int i = 0; i < addchar * 8; ++i) {
                str1_temp[sub + i] = '0';
            }
        }
        temp_str += str1_temp;
    }
    str2 = des_H(str2);
    return temp_str;
}



QString des_StrToBitStr(const QString& str)
{
    QBitArray bstr(64);

    for (int i = 0; i < 8; i++)
    {
        QBitArray bits(8);
        for (int j = 0; j < 8; j++)
        {
            bits.setBit(j, (str[i].toLatin1() >> (7 - j)) & 1);
        }

        for (int j = 0; j < 8; j++)
        {
            bstr.setBit(i * 8 + j, bits.testBit(7 - j));
        }
    }

    QString s;
    for (int i = 0; i < 64; i++)
    {
        s += bstr.testBit(i) ? '1' : '0';
    }

    // 添加一个翻转操作
    std::reverse(s.begin(), s.end());

    return s;
}
/*QString des::des_encrypt(QString const& input, QString const& key) {
    // 实现加密逻辑
    // ...
    return encryptedText;
}*/

QString des::des_encrypt(QString  str1, QString  str2)
{
    str1 = chardeel(str1, str2);  // 明文分组和填充，返回01字符串

    des_generateKeys(str2);  // 生成16个子密钥

    int divi_times = str1.size() / 64;  // 分成多少组去进行des
    QString rs_temp = "";

    for (int i = 0; i < divi_times; ++i) {
        QString str1_temp = str1.mid(i * 64, 64);

        // 第一步:明文初始置换 64->64
        str1_temp = plaintext_initial_permutation(str1_temp);

        // 第二步:数据分组
        QString left = str1_temp.mid(0, 32);
        QString right = str1_temp.mid(32, 32);
        QString newleft;

        // 第三步:16轮迭代
        for (int j = 1; j <= 16; j++)
        {
            newleft = right;
            right = desXOR(left, des_f(right, desKeys[j]));
            left = newleft;
        }

        // 第四步:合并数据 注意位R16L16
        QString rs = right + left;

        // 结尾置换
        rs = final_permutation(rs);
        rs_temp = rs_temp + rs;
    }

    return rs_temp;
}
QString des::des_decrypt(QString str)
{
    int divi_times = str.size() / 64;  // 分成多少组去进行des
    QString rs_temp = "";

    for (int i = 0; i < divi_times; ++i) {
        QString str_temp = str.mid(i * 64, 64);
        // 把密文当作明文进行初始明文置换
        str_temp = plaintext_initial_permutation(str_temp);

        // 左右分组
        QString left = str_temp.mid(0, 32);
        QString right = str_temp.mid(32, 32);

        QString newleft;

        // 逆序的子密钥使用 16轮迭代
        for (int j = 16; j >= 1; j--)
        {
            newleft = right;
            right = desXOR(left, des_f(right, desKeys[j]));
            left = newleft;
        }

        // 合并
        QString rs = right + left;

        // 最后置换
        rs = final_permutation(rs);
        rs_temp = rs_temp + rs;
    }
    rs_temp = des_BitStrToStr(rs_temp);
    return rs_temp;
}


