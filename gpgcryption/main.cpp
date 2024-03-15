#include <QCoreApplication>
#include <QProcess>
#include <QString>
#include <QDebug>

QString inputfile = "/home/seher/Desktop/cry/input.txt";
QString encfile = "/home/seher/Desktop/cry/enc.txt";
QString outputfile = "/home/seher/Desktop/cry/output.txt";

QString password = "\"12345678\"";
void crpytdata(){
    QProcess process;
    process.setProgram("gpg");
    QStringList arguments;
    arguments << "--symmetric" << "--batch" << "--cipher-algo" << "AES256";
    arguments << "--passphrase" << password;
    arguments << "-o" << encfile  <<inputfile;
    process.setArguments(arguments);

    process.start();
    process.waitForFinished();

    if (process.exitCode() == 0) {
        qDebug() << "Encryption successful!";
    } else {
        qDebug() << "Error during encryption: " << process.exitCode() << process.readAllStandardError();
        QByteArray errorData = process.readAllStandardError();
        // Check for error messages in standard error (optional)
    }
}

void decrpytdata(){
//    gpg --decrypt --batch --output outdata.txt encrypted.txt
    QProcess process;
    process.setProgram("gpg");
    QStringList arguments;
    arguments << "--decrypt" << "--batch";
    arguments << "--passphrase" << password;
    arguments << "-o" << outputfile << encfile;
    process.setArguments(arguments);

    process.start();
    process.waitForFinished();

    if (process.exitCode() == 0) {
        qDebug() << "Decryption successful!";
    } else {
        qDebug() << "Error during decryption: " << process.exitCode() << process.readAllStandardError();;
    }
}
void remove(QString &input){
    QProcess process;
    process.setProgram("rm");
    QStringList arguments;
    arguments << input;
    process.setArguments(arguments);

    process.start();
    process.waitForFinished();

    if (process.exitCode() == 0) {
        qDebug() << "removing successful!";
    } else {
        qDebug() << "Error during moving file: " << process.exitCode() << process.readAllStandardError();;
        QByteArray errorData = process.readAllStandardError();
        // Check for error messages in standard error (optional)
    }
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    remove (encfile);
    crpytdata();
    remove (outputfile);
    decrpytdata ();
    return a.exec();
}
