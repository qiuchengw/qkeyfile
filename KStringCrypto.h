#pragma once

#include <QString>

// ֻ����ַ����ӽ��ܣ�
namespace KStringCrypto
{
    enum EnumCrypto
    {
        Crypto_None = 1,
        Crypto_secretbox_easy,
    };

    /*
     *	�ַ������ܣ�������Ȼ���ַ�������ʽ
     */
    QString Crypt(const QString& s_src);

    /*
     *	�ַ�������
     */
    QString Decrypt(const QString& s_encypted);
}

