#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <tag.h>
#include <fileref.h>
#include <tstring.h>
#include <QString>

using namespace TagLib;

class TagManager
{
public:
    TagManager();
    TagManager(const QString filePath);
    void setFile(const QString filePath);

    QString getTitle() const;
    void setTitle(const QString &value);
    QString getArtist() const;
    void setArtist(const QString &value);

    QString getGenre() const;
    void setGenre(const String &value);

private:
    FileRef *file;
    String title;
    String artist;
    String genre;
    FileName name;

};

#endif // TAGMANAGER_H
