#include "upload_674.h"
#include "ui_upload_674.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkReply>
//#include <QDialog>
//#include <QFormLayout>
//#include <QDialogButtonBox>
#include <QInputDialog>

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
 * TODO maybee file size on Server after upload to file size
 */
void Upload_674::replyFinished(QNetworkReply *reply)
{
    // TODO this gets called even when no upload is done because for instance
    // show name was not set

    // check if NetworkAccessManager::Operation was "put" aka upload
    if(reply->operation() == 3) {
        // if there are no errors
        if(reply->error() == QNetworkReply::NoError)
            QMessageBox::information(this, "Hinweis", "Der Upload war erfolgreich!");
        else {
            QString errorString = "Es hat folgenden Fehler gegeben:\n"
                    + reply->errorString();
            QMessageBox::warning(this, "Fehler", errorString);
        }
    }
}

/**
 * @brief Upload_674::buildUploadFileName
 * @return QString
 * This method builds the filename for the file on the server
 */
QString Upload_674::buildUploadFileName()
{
    QString date = ui->dateEdit->text();
    QString showName = ui->leShowName->text();
    // delte slashes to confirm with file naming conventions
    date.replace("/","");
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
    QString newName = ui->leSelectFile->text();

    // cancel the method if no showname was entered
    if(newName.isEmpty()) {
        ui->leShowName->setFocus();
        return;
    }

    if(ui->leShowName->text().isEmpty()) {
        QMessageBox::information(this, "Hinweis","Bitte gib den Namen der Sendung ein, für die der Mix bestimmt ist");
        ui->leShowName->setFocus();
        return;
    }

    // make sure all fields have been filled out
    if(ui->leHost->text().isEmpty()
            || ui->leUser->text().isEmpty() || ui->lePass->text().isEmpty()) {
        QMessageBox::information(this, "Hinweis",
                                 "Bitte fülle den Host, das Passwort und den Username aus um dich zu verbinden.");
     return;
    }

    // make sure file was selected
    if(ui->leSelectFile->text().isEmpty()) {
        QMessageBox::information(this, "Hinweis",
                                 "Bitte wähle eine Datei zum hochladen aus.");
        ui->leSelectFile->setFocus();
        return;
    }

    // create new QFile from user selection
    tagMan->setFile(newName);
    file = new QFile(newName);

    // if the file can be opened create a request and upload to server
    if(file->open(QIODevice::ReadOnly)) {
        // set mp3 tags for upload file
        // set "title" to the name of the show
        tagMan->setTitle(ui->leShowName->text());

        // if artist mp3 tag ist empty we make a dialoge to set it
        QString artist = tagMan->getArtist();
        if(artist.isEmpty()) {
            bool ok;
            QString text = QInputDialog::getText(
                        this, tr("Bitte gib deinen Arist Namen ein"),
                        tr("mp3 tag Artist:"), QLineEdit::Normal,
                        "", &ok);
            if (ok && !text.isEmpty())
                tagMan->setArtist(text);
            // upload button has to be clicked again if artist had to be set
            return;
        }

        // build the url with uploadedMixName to put the file on the server
        QString uploadedMixName = buildUploadFileName();
        host = ui->leHost->text();
        user = ui->leUser->text();
        pass = ui->lePass->text();

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
