#include "upload_674.h"
#include "ui_upload_674.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkReply>

#include <QDebug>

/**
 * @brief Upload_674::Upload_674
 * @param parent
 * Constructor
 */
Upload_674::Upload_674(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Upload_674)
{
    ui->setupUi(this);
    // create the QNetworkAccessManager object
    ftp = new QNetworkAccessManager();
    // connect to the appropriate SLOT
    connect(ftp, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    // set the password LineEdit to password mode
    ui->lePass->setEchoMode(QLineEdit::Password);

    ui->lblInfo->setText("Nicht Verbunden");

    // create new Tagmanager to read and perhaps write new mp3 tags
    tagMan = new TagManager();

}
/**
 * @brief Upload_674::~Upload_674
 * Destructor
 */
Upload_674::~Upload_674()
{
    delete ui;
    delete ftp;
}

/**
 * @brief Upload_674::replyFinished
 * @param reply
 *
 */
void Upload_674::replyFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
        QMessageBox::information(this, "Hinweis", "Der Upload war erfolgreich!");
    else {
        QString errorString = "Es gabe einen Fehler beim Upload:\n" + reply->errorString();
        QMessageBox::critical(this, "Fehler", errorString);
    }
}

/**
 * @brief Upload_674::on_btnConnect_clicked
 *
 */
void Upload_674::on_btnConnect_clicked()
{
    if(ui->leHost->text().isEmpty()
            || ui->leUser->text().isEmpty() || ui->lePass->text().isEmpty()) {
        QMessageBox::information(this, "Hinweis",
                                 "Bitte fülle den Host, das Passwort und den Username aus um dich zu verbinden.");
     return;
    }

    host = ui->leHost->text();
    user = ui->leUser->text();
    pass = ui->lePass->text();

    // build request for connection to ftp
    url = QUrl("ftp://" + host);
    url.setUserName(user);
    url.setPassword(pass);
    url.setPort(21);

    req.setUrl(url);
    // no reply gotten here so were not actually connecting

    // TODO label wird immer auf verbunden gesetzt muss das evtl in reply finished verlegen
    // evtl headers holen um
    if(ftp->networkAccessible() == 1)
        ui->lblInfo->setText("Verbunden");
    // TODO hier noch else einfügen und fehler beim verbinden behandeln
}

/**
 * @brief Upload_674::buildUploadFileName
 * @return QString
 * This method builds the filename for the file on the server
 */
QString Upload_674::buildUploadFileName()
{
    if(ui->leShowName->text().isEmpty()) {
        QMessageBox::information(this, "Hinweis","Bitte gib den Namen der Sendung ein, für die der Mix bestimmt ist");
        return "showName not set";
    }

    QString date = ui->dateEdit->text();
    QString showName = ui->leShowName->text();
    // replace slashes of the date with dots
    date.replace("/",".");
    // sanetize the showname
    /**
      * TODO evtl in formular schreiben, dass keine umlaute erlaubt sind
      * evtl QValidator einsetzen wenn nötig
      */
    showName.replace("/",".");
    showName.replace("\\", ".");
    showName.replace(":", ".");
    showName.replace("ä", "a");
    showName.replace("ö", "o");
    showName.replace("ü", "u");

    QString uploadFileName = showName + "_" + date + ".mp3";
    return uploadFileName;
}

/**
 * @brief Upload_674::on_btnSelectFile_clicked
 * Opens a file dialoge, where the user can select .mp3 files
 */
void Upload_674::on_btnSelectFile_clicked()
{
    // dialog for opening a file only MP3 files are permitted
    fileName = QFileDialog::getOpenFileName
            (this, "Datei Öffnen", QDir::currentPath(), "MP3 Dateien (*.mp3)");
    // set the path as text in QLineEdit
    ui->leSelectFile->setText(fileName);
}

/**
 * @brief Upload_674::on_btnUpload_clicked
 * Creates a new QFile, Requests a new name for it
 * and then builds a new request to upload the file
 */
void Upload_674::on_btnUpload_clicked()
{
    // make sure file was selected
    if(ui->leSelectFile->text().isEmpty()) {
        QMessageBox::information(this, "Hinweis",
                                 "Bitte wähle eine Datei zum hochladen aus.");
        ui->leSelectFile->setFocus();
        return;
    }

    // create new QFile from user selection
    file = new QFile(ui->leSelectFile->text());
    // if the file can be opened create a request and upload to server
    if(file->open(QIODevice::ReadOnly)) {
        QString uploadedMixName = buildUploadFileName();
        // cancel the method if no showname was enteres
        if(uploadedMixName == "showName not set") {
            ui->leShowName->setFocus();
            return;
        }
        // build the url again, with uploadFileName to put the file on the server
        url = QUrl("ftp://" + host + "/" + uploadedMixName);
        url.setUserName(user);
        url.setPassword(pass);
        url.setPort(21);
        // build the request
        req.setUrl(url);
        // start the upload
        reply = ftp->put(req,file);
      // else inform the user, that the file could not be opened
    } else {
        QMessageBox::information(this, "Hinweis", "Die gewählte Datei konnte nicht geöffnet werden.");
        ui->leSelectFile->setFocus();
    }
}
/**
 * @brief Upload_674::on_actionVerbinden_triggered
 * connect via the action on the menu bar
 */
void Upload_674::on_actionVerbinden_triggered()
{
    on_btnConnect_clicked();
}