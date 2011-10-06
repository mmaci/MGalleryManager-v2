#include <iostream>

#include "core/mphoto.h"

core::MPhoto::MPhoto(QFileInfo fileInfo, core::MDatabase* database, core::MGallery* gallery) :
    core::MObject(fileInfo.baseName().toStdString(), database, gallery)
{
    _fileInfo = fileInfo;    
}
