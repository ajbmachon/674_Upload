#ifndef UPLOAD_674_H
#define UPLOAD_674_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

#include "tagmanager.h"

namespace Ui {
class Upload_674;
}

class Upload_674 : public QMainWindow
{
    Q_OBJECT

private:
    TagManager *tagMan;

    Ui::Upload_674 *ui;
    QString fileName;
    QString host;
    QString user;
    QString pass;

    QUrl url;
    QFile *file;
    QNetworkAccessManager *ftp;
    QNetworkRequest req;
    QNetworkReply *reply;

    QString buildUploadFileName();

public:
    explicit Upload_674(QWidget *parent = 0);
    ~Upload_674();

public slots:

private slots:
    void replyFinished(QNetworkReply *reply);

    void on_btnSelectFile_clicked();
    void on_btnUpload_clicked();
};

#endif // UPLOAD_674_H
