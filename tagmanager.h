#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <QString>

using namespace TagLib;

class TagManager
{
public:
    TagManager();
    TagManager(QString);
    void setFile(QString filePath);


    QString getTitle() const;
    void setTitle(const QString &value);

    QString getArtist() const;
    void setArtist(const QString &value);

private:
    FileRef *file;
    QString title;
    QString artist;

};

#endif // TAGMANAGER_H
