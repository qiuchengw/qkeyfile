#include "qkeyfile.h"
#include <random>
#include <QFile>
#include "KStringCrypto.h"


namespace qkeyfile
{
//    bool _readKey(__in KBuffer& bufEncrypt, __out KBuffer& bufData)
//    {
//        quint32 dwPicSize = bufEncrypt.GetBufferLen();
//        if (dwPicSize < 2048)
//        {
//            return false;
//        }

//        // 最后写入20个字节，顺序如下
//        // 密钥在图像数据中的偏移
//        quint32 dwOffset;
//        bufEncrypt.ReadLast((BYTE*)&dwOffset, sizeof(quint32));
//        // 密钥长度
//        quint32 dwKeyLen;
//        bufEncrypt.ReadLast((BYTE*)&dwKeyLen, sizeof(quint32));
//        // 图像大小
//        bufEncrypt.ReadLast((BYTE*)&dwPicSize, sizeof(quint32));
//        // 加密后的数据长度
//        quint32 dwEncrypDataLen;
//        bufEncrypt.ReadLast((BYTE*)&dwEncrypDataLen, sizeof(quint32));
//        // 原始数据长度
//        quint32 dwOriginLen;
//        bufEncrypt.ReadLast((BYTE*)&dwOriginLen, sizeof(quint32));

//        if (!bufData.AllocBuffer(dwEncrypDataLen))
//        {
//            return false;
//        }
//        if (!bufData.Write(bufEncrypt.GetBuffer(dwPicSize), dwEncrypDataLen))
//        {
//            // eInfo.SetText(L"读取数据错误");
//            return false;
//        }

//        QDataEnDe ende;
//        if (!ende.SetCodeData(bufEncrypt.GetBuffer(dwOffset), dwKeyLen))
//        {
//            return false;
//            // eInfo.SetText(L"设置密码数据失败");
//        }
//        if (!ende.DecryptData(bufData))
//        {
//            // eInfo.SetText(L"解密数据失败!");
//            return false;
//        }

//        // eInfo.SetText(L"全部搞定啦！已经保存为：" + sFileName);
//        return true;
//    }

//    bool _writeKey(QString seed_path, const QByteArray& to_encrypt, QString save_path)
//    {
//        Q_ASSERT(!seed_path.isEmpty() && !save_path.isEmpty());

//        KBuffer bufPic;
//        if (!bufPic.FileRead(seed_path))
//        {
//            return false;
//        }

//        quint32 dwPicSize = bufPic.GetBufferLen();
//        if (dwPicSize < 2048)
//        {
//            return false;
//        }

//        // 读取文件夹下的所有文件
//        // 并创建压缩文件
//        KBuffer bufData;
//        bufData.Write(to_encrypt.constData());

//        quint32 dwOriginLen = bufData.GetBufferLen();
//        quint32 dwOffset = 505;
//        quint32 dwKeyLen = 404;
//        QDataEnDe ende;
//        if (!ende.SetCodeData(bufPic.GetBuffer(dwOffset), dwKeyLen))
//        {
//            return false;
//        }
//        if (!ende.EncryptData(bufData))
//        {
//            return false;
//        }
//        quint32 dwEncrypDataLen = bufData.GetBufferLen();

//        if (!bufPic.Write(bufData.GetBuffer(), dwEncrypDataLen))
//        {
//            return false;
//        }
//        // 最后写入20个字节，顺序如下
//        // 原始数据长度
//        bufPic.Write((BYTE*)&dwOriginLen, sizeof(quint32));
//        // 加密后的数据长度
//        bufPic.Write((BYTE*)&dwEncrypDataLen, sizeof(quint32));
//        // 图像大小
//        bufPic.Write((BYTE*)&dwPicSize, sizeof(quint32));
//        // 密钥长度
//        bufPic.Write((BYTE*)&dwKeyLen, sizeof(quint32));
//        // 密钥在图像数据中的偏移
//        bufPic.Write((BYTE*)&dwOffset, sizeof(quint32));

//        if (!bufPic.FileWrite(save_path))
//        {
//            return false;
//        }
//        return true;
//    }

    bool GenerateRandomFile(const QString& file_path, int n_kb)
    {
        QFile f(file_path);
        if (f.open(QFile::ReadWrite | QFile::Truncate))
        {
            if (n_kb > 1024)
            {
                Q_ASSERT(false);
                n_kb = 1024;
            }

            std::random_device rd;
            std::mt19937_64 gen(rd());
            __int64 n = n_kb * 128;
            for (__int64 i = 0; i < n; ++i)
            {
                auto d = gen();
                f.write((const char*)&d, 8);
            }
            f.flush();
            f.close();
            return true;
        }
        return false;
    }

//    QByteArray ReadKey(const QString& file_path)
//    {
//        if (!QFile::exists(file_path))
//        {
//            Q_ASSERT(false);
//            return QByteArray();
//        }

//        KBuffer buf_in;
//        if (buf_in.FileRead(file_path))
//        {
//            KBuffer buf_out;
//            if (_readKey(buf_in, buf_out))
//            {
//                return QByteArray((const char*)buf_out.GetBuffer(), buf_out.GetBufferLen());
//            }
//        }
//        return QByteArray();
//    }

//    bool WriteKey(const QString& file_path, const QByteArray &key)
//    {
//        if (!QFile::exists(file_path))
//        {
//            if (GenerateRandomFile(file_path, 256))
//            {
//                return _writeKey(file_path, key, file_path);
//            }
//        }
//        return false;
//    }

//    QByteArray DecryptBuf(const char* b, int len, const char* key)
//    {
//        KBuffer buf;
//        buf.Write((const BYTE*)b, len);
//        if (QDataEnDe(key).DecryptData(buf))
//        {
//            return QByteArray((const char*)buf.GetBuffer(), buf.GetBufferLen());
//        }
//        return QByteArray();
//    }

    QString EncryptString(const QString& str)
    {
        return KStringCrypto::Crypt(str);
    }

    QString DecryptString(const QString& data)
    {
        return KStringCrypto::Decrypt(data);
    }
}
