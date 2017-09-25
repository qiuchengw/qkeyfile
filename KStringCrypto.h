#pragma once

#include <QString>

// 只针对字符串加解密！
namespace KStringCrypto
{
    enum EnumCrypto
    {
        Crypto_None = 1,
        Crypto_secretbox_easy,
    };

    /*
     *	字符串加密，最终依然是字符串的形式
     */
    QString Crypt(const QString& s_src);

    /*
     *	字符串解密
     */
    QString Decrypt(const QString& s_encypted);
}

