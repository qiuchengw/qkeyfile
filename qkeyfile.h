#ifndef QKEYFILE_H
#define QKEYFILE_H

#include <qglobal.h>
#include <QByteArray>
#include <QString>

// #ifdef QKEYFILE_LIB
// #define QKEYFILE_EXPORT Q_DECL_EXPORT
// #else
// #define QKEYFILE_EXPORT Q_DECL_IMPORT
// #endif

#define QKEYFILE_EXPORT

// 以c++的方式导出
namespace qkeyfile
{
    /*
     *	随机文件，大小：n_kb
     *  
     *      原来的文件将被覆盖掉！
     */
    QKEYFILE_EXPORT bool GenerateRandomFile(const QString& file_path, int n_kb);

    /*
     *	读取机密信息
     */
//    QKEYFILE_EXPORT QByteArray ReadKey(const QString& file_path);

    /*
     *	写机密信息
     */
//    QKEYFILE_EXPORT bool WriteKey(const QString& file_path, const QByteArray &key);

    /*
     *	解密
     */
    QKEYFILE_EXPORT QByteArray DecryptBuf(const char* buf, int len, const char* key);

    /*
     *	加密内存字符串
     */
    QKEYFILE_EXPORT QString EncryptString(const QString& str);

    /*
     *	解密字符串
     */
    QKEYFILE_EXPORT QString DecryptString(const QString& data);
}

#endif // QKEYFILE_H
