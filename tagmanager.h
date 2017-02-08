#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <taglib/tag.h>
#include <taglib/fileref.h>

using namespace TagLib;

class TagManager
{
public:
    TagManager();

private:
    FileRef *file;

};

#endif // TAGMANAGER_H
