#include "tagmanager.h"

#include <iostream>
#include <QDebug>
#include <QByteArray>
#include <QFile>

TagManager::TagManager()
{

}

TagManager::TagManager(const QString filePath)
{
    setFile(filePath);
}

void TagManager::setFile(const QString filePath)
{
    /**
      *The FileRef constructor accepts a FileName object (not String!),
      * which can be either char* or wchar_t* string.
      * On Windows you can assume that both wchar_t and QChar have 16-bits,
      * so you can simply pass it filePath.constData().
      *
      * Note that if you are planning to run the code on non-Windows platform,
      * you need to have an #ifdef check around the FileRef object creation,
      * because on other platforms it only accepts char* strings
      * and you should use QFile::encodeName(filePath).constData().
      */
    file = new FileRef(QFile::encodeName(filePath).constData());
    // duration seems to be slightly wrong
    // TODO fix duration
    int seconds = file->audioProperties()->length() % 60;
    int minutes = (file->audioProperties()->length() - seconds) / 60;
    qDebug() << minutes;
    // set artist and title from mp3 tags
    Tag *t = file->tag();

    artist = file->tag()->artist();
    title = file->tag()->title();
    genre = file->tag()->genre();

    // TODO set tile with value of showname
//    file->tag()->setArtist("Test Artist");

}

QString TagManager::getTitle() const
{
    // convert from TagLib::String into QString and return
    QString qTitle = QString::fromUtf8(title.toCString());
    return qTitle;
}

void TagManager::setTitle(const QString &value)
{
    String newTitle = value.toStdString();
    title = newTitle;
    file->tag()->setTitle(title);
    file->save();
}

QString TagManager::getArtist() const
{
    QString qArtist = QString::fromUtf8(artist.toCString());
    return qArtist;
}

void TagManager::setArtist(const QString &value)
{
    String newArtist = value.toStdString();
    artist = newArtist;
    file->tag()->setArtist(newArtist);
    file->save();
}

QString TagManager::getGenre() const
{
    QString qGenre = QString::fromUtf8(genre.toCString());
    return qGenre;
}

void TagManager::setGenre(const String &value)
{
    genre = value;
}
