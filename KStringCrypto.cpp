#include "KStringCrypto.h"
#include <memory>
#include <cstring>
#include <cstdlib>
#include <QChar>
#include <QDateTime>
#include "simplecrypt.h"

#define BYTE_4 sizeof(qint32)

namespace KStringCrypto
{

    /*
    *	Crypt
    */
    bool CryptBuf( QByteArray& buf, EnumCrypto c);

    /*
    *	在加密过的数据中写入密钥
    */
    bool _mWrite( QByteArray& data,  const QByteArray& key);
    bool WritePrivate( QByteArray& data, EnumCrypto c,
         const QByteArray& key,  const QByteArray& nonce);

    /*
    *	界面数据区
    *
    *      返回空串，解密失败
    */
    bool _mRead( QByteArray& data,  QByteArray& prv);
    QByteArray DecryptPrivate( QByteArray& data);

    /*
    *	生成随机len长度的缓冲区
    */
    inline QByteArray RandomBuf(size_t len);

    /*
    *	生成随机整数值
    */
    inline qint32 RandomInt(qint32 upper_v);

    /*
    *	解密数据
    */
    QByteArray _mDecrypt( const QByteArray& encrypted_data,
         const QByteArray& key,  const QByteArray& nonce,  int cypt);
}

bool KStringCrypto::CryptBuf( QByteArray& buf, EnumCrypto c)
{
    if (KStringCrypto::Crypto_secretbox_easy == c)
    {
        quint64 key = QDateTime::currentMSecsSinceEpoch();
        SimpleCrypt sc;
        sc.setKey(key);
        buf = sc.encryptToByteArray(buf);

        // 加密
        QByteArray ba_key = QString::number(key).toUtf8(); //((const char*)&key, sizeof(key));// = RandomBuf(crypto_secretbox_KEYBYTES);
        QByteArray ba_nonce = RandomBuf(16);

        return WritePrivate(buf, EnumCrypto::Crypto_secretbox_easy, ba_key, ba_nonce);
    }
    return false;
}

QString KStringCrypto::Crypt(const QString& s_src)
{
    // 1，对称性加密，EnumCrypto::Crypto_secretbox_easy 加密
    QByteArray src = s_src.toUtf8();
    if (CryptBuf(src, Crypto_secretbox_easy) 
        && CryptBuf(src, Crypto_secretbox_easy))
    {
        return src.toBase64();
    }
    return "";
}

QString KStringCrypto::Decrypt(const QString& s_encypted)
{
    QByteArray ba_encrypt = QByteArray::fromBase64(s_encypted.toUtf8());

    return DecryptPrivate(DecryptPrivate(ba_encrypt));
}

QByteArray KStringCrypto::_mDecrypt( const QByteArray& encrypted_data,
     const QByteArray& key,  const QByteArray& nonce,  int cypt)
{
    if (EnumCrypto::Crypto_secretbox_easy == cypt){
        SimpleCrypt sc(key.toLongLong());
        return sc.decryptToByteArray(encrypted_data);
    }
    return "";
}

bool KStringCrypto::_mWrite( QByteArray& data,  const QByteArray& key)
{
    Q_ASSERT(data.length() > 0);

    // 1 ，生成随机位置
    qint32 pos = RandomInt(data.length());

    // 2，写入key
    data.insert(pos, key);

    // 3，写入key长度
    qint32 key_len = key.length();
    data.append((const char*)&key_len, BYTE_4);

    // 4，写入偏移位置
    data.append((const char*)&pos, BYTE_4);

    return true;
}

bool KStringCrypto::WritePrivate( QByteArray& data, EnumCrypto c,
     const QByteArray& key,  const QByteArray& nonce)
{
    if (_mWrite(data, key))
    {
        if (_mWrite(data, nonce))
        {
            // 5，写入加密方式
            data.append((const char*)&c, BYTE_4);

            return true;
        }
    }
    return false;
}

bool KStringCrypto::_mRead( QByteArray& data,  QByteArray& secret)
{
    if (data.length() < 16){
        return false;
    }

    // 1，找到key的偏移位置
    qint32 pos = 0;
    memcpy_s(&pos, BYTE_4, data.right(BYTE_4).constData(), BYTE_4);
    data.chop(BYTE_4);

    // 2，找到key长度
    qint32 key_len = 0;
    memcpy_s(&key_len, BYTE_4, data.right(BYTE_4).constData(), BYTE_4);
    data.chop(BYTE_4);

    // 3，读出key
    secret = data.mid(pos, key_len);
    data.remove(pos, key_len);

    return true;
}

QByteArray KStringCrypto::DecryptPrivate( QByteArray& data)
{
    // 1，找到加密方式
    qint32 cypt = EnumCrypto::Crypto_None;
    memcpy_s(&cypt, BYTE_4, data.right(BYTE_4).constData(), BYTE_4);
    data.chop(BYTE_4);

    // 2, nonce
    QByteArray nonce;
    if (_mRead(data, nonce))
    {
        // 3, key
        QByteArray key;
        if (_mRead(data, key))
        {
            // 4, decrypt
            return _mDecrypt(data, key, nonce, cypt);
        }
    }
    return "";
}

inline qint32 KStringCrypto::RandomInt(qint32 upper_v) 
{
    return qrand() % upper_v;
}

inline QByteArray KStringCrypto::RandomBuf(size_t len)
{
    Q_ASSERT((len >= 2) && (len < 64));

    // 申请len长度内存
    QByteArray buf;
    for (int i = 0; i < len; i++){
        buf.push_back(qrand());
    }
    Q_ASSERT(buf.length() == len);
    return buf;
}

