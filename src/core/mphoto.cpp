#include "core/mphoto.h"
#include <iostream>

core::MPhoto::MPhoto()
{    
}

core::MPhoto::MPhoto(QFileInfo fileInfo)
{
    _fileInfo = fileInfo;    
}
