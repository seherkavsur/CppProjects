#include <QCoreApplication>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
QByteArray key = "123456";

QString inputFile = "/home/seher/Desktop/cry/c_input.json";
QString outputFile = "/home/seher/Desktop/cry/c_out_d_in.enc";
QString output2File = "/home/seher/Desktop/cry/d_out.json";

void crypting(){

    QJsonObject jsonData;
    jsonData["key1"] = "value1";
    jsonData["key2"] = 123;
    jsonData["key3"] = true;



    QFile jsonFile(inputFile);
    if (!jsonFile.open(QIODevice::WriteOnly)) {
        qCritical() << "JSON dosyası açılamadı:" << jsonFile.errorString();
        return;
    }

    QJsonDocument jsonDocument(jsonData);
    jsonFile.write(jsonDocument.toJson());
    jsonFile.close();

    QStringList args;
    args << "enc";
    args << "-aes-256-cbc";
    args << "-in";
    args << inputFile;
    args << "-out";
    args << outputFile;
    args << "-pass";
    QByteArray password = "pass:\"";
    password.append (key + "\"");
    args << password;

    QProcess process;
    QString program("openssl");
    process.setArguments(args);
    process.setWorkingDirectory("/home/seher/Desktop/cry");
    process.start(program,args);

    process.waitForFinished();

    int exitcode = process.exitCode();
    if (exitcode != 0) {
        qCritical() << "OpenSSL hatası:" << process.errorString() << process.readAllStandardError();
        return;
    }

    QFile::remove(inputFile);

    qDebug() << "Şifreli dosya:" << outputFile;
}
void decrypting(){
    QStringList args;
    args << "enc";
    args << "-d";
    args << "-aes-256-cbc";
    args << "-in";
    args << outputFile;
    args << "-out";
    args << output2File;
    args << "-pass";
    QByteArray password = "pass:\"";
    password.append (key + "\"");
    args << password;

    QProcess process;
    QString program("openssl");
    process.setArguments(args);
    process.setWorkingDirectory("/home/seher/Desktop/cry");
    process.start(program,args);
    process.waitForFinished();

            // Hata kontrolü
    if (process.exitCode() != 0) {
        qCritical() << "OpenSSL error:" << process.errorString() << process.readAllStandardError();
        return;
    }
    qDebug() << "decrypted file:" << outputFile;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    crypting ();
    decrypting ();
    return a.exec();
}
