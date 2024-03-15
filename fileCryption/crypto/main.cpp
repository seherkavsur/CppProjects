#include <QCoreApplication>
#include <QCryptographicHash>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
// 16 byte IV
// 32 byte AES-256 KEY
QByteArray key = "12345678901234567890123456789012";
QString outputFilePath = "/home/seher/Desktop/encrypted.json";


QByteArray encryptData(const QByteArray& data, const QByteArray& key) {
    // creating QCryptographicHash object (SHA-256)
    QCryptographicHash hash(QCryptographicHash::Sha256);
    // creating a hash value from the key
    QByteArray hashedKey = hash.hash(key, QCryptographicHash::Sha256);
    // creating 16 byte IV for AES-256-CBC
    QByteArray iv = hashedKey.left(16);
    // creating OpenSSL AES context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        qDebug() << "Error: OpenSSL context creation error!";
        return QByteArray();
    }
    // Starting the encryption process (AES-256-CBC)
    int result = EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)hashedKey.data(), (unsigned char*)iv.data());
    if (!result) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }
    // crypting to data
    int outLen1, outLen2;
    QByteArray encryptedData;
    encryptedData.resize(data.size() + AES_BLOCK_SIZE);

    result = EVP_EncryptUpdate(ctx, (unsigned char*)encryptedData.data(), &outLen1, (const unsigned char*)data.data(), data.size());
    if (!result) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }

    result = EVP_EncryptFinal_ex(ctx, (unsigned char*)encryptedData.data() + outLen1, &outLen2);
    if (!result) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }
    encryptedData.resize(outLen1 + outLen2);
    // cleaning OpenSSL context
    EVP_CIPHER_CTX_free(ctx);
    return encryptedData;
}

void writeEncryptedJsonToFile(const QJsonObject& jsonData, const QString& outputFilePath) {
    // converting JSON object to QByteArray
    QJsonDocument jsonDocument(jsonData);
    QByteArray jsonDataBytes = jsonDocument.toJson();
    // crypting to data
    QByteArray encryptedData = encryptData(jsonDataBytes, key);
    //Writing crypted data to file
    QFile file(outputFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "ERR: File can not open!" << file.errorString();
        return;
    }
    file.write(encryptedData);
    file.close();
}
void readfile(){
    //Reading crypted data to file
    QFile file(outputFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERR: File can not open!" << file.errorString();
                                                return;
    }
    QByteArray encryptedData = file.readAll();

    // creating QCryptographicHash object (SHA-256)
    QCryptographicHash hash(QCryptographicHash::Sha256);
    // creating a hash value from the key
    QByteArray hashedKey = hash.hash(key, QCryptographicHash::Sha256);
    // creating 16 byte IV for AES-256-CBC
    QByteArray iv = hashedKey.left(16);
    // creating OpenSSL AES context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        qDebug() << "Error: OpenSSL context creation error!";
        return;
    }
    // Starting the decryption process (AES-256-CBC)
    int result = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)hashedKey.data(), (unsigned char*)iv.data());
    if (!result) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return;
    }

    //Decrypting data
    int outLen1, outLen2;
    QByteArray decryptedData;
    decryptedData.resize(encryptedData.size() + AES_BLOCK_SIZE);

    result = EVP_DecryptUpdate(ctx, (unsigned char*)decryptedData.data(), &outLen1, (const unsigned char*)encryptedData.data(), encryptedData.size());
    if (!result) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return ;
    }

    result = EVP_DecryptFinal_ex(ctx, (unsigned char*)decryptedData.data() + outLen1, &outLen2);
    if (!result) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return ;
    }

    decryptedData.resize(outLen1 + outLen2);

    // cleaning OpenSSL context
    EVP_CIPHER_CTX_free(ctx);

    // Use the decryptedData to create QJsonDocument object
    QJsonDocument decryptedJsonDocument = QJsonDocument::fromJson (decryptedData);

    // Take the object from the file to convert JSON object to QJsonObject
    QJsonObject decryptedJsonObject = decryptedJsonDocument.object();
    QString name = decryptedJsonObject["name"].toString ();
    QString surname = decryptedJsonObject["surname"].toString ();
    int age = decryptedJsonObject["age"].toInt ();
    qWarning() << name << surname << age;
}
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    // JSON data example
    QJsonObject jsonData;
    jsonData["name"] = "seher";
    jsonData["surname"] = "kavsur";
    jsonData["age"] = 27;
    writeEncryptedJsonToFile(jsonData, outputFilePath);
    readfile ();
    return a.exec();
}
