#include "tagmanager.h"

#include <iostream>
#include <QDebug>
#include <QByteArray>

TagManager::TagManager()
{

}

TagManager::TagManager(QString filePath)
{
    setFile(filePath);
}

void TagManager::setFile(QString filePath)
{
    // convert our string so we can get a TagLib::FileName
    QByteArray ba = filePath.toLatin1();
    FileName name = ba.data();

    file = new FileRef(name);

    int duration = file->audioProperties()->length();
    // duration seems to be slightly wrong
    qDebug() << duration;


}

QString TagManager::getTitle() const
{
    return title;
}

void TagManager::setTitle(const QString &value)
{
    title = value;
}

QString TagManager::getArtist() const
{
    return artist;
}

void TagManager::setArtist(const QString &value)
{
    artist = value;
}
