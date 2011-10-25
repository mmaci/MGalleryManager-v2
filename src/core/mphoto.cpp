#define _DEBUG

#include "core/mphoto.h"
#include "core/mgallery.h"

core::MPhoto::MPhoto(core::MPhotoInfo info, core::MGallery* parent) :
    core::MObject(parent)
{
    _info = info;
    _typeId = TYPEID_PHOTO;

    #ifdef _DEBUG
    std::cout << "Creating new instance of MPhoto (" << _info.fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif
}

core::MPhoto::~MPhoto()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MPhoto (" << _info.fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif
}
