#include "core/mphoto.h"
#include <core/mgallery.h>

core::MPhoto::MPhoto(core::MPhotoInfo info, core::MGallery* parent) :
    core::MObject(parent)
{
    _info = info;
    _typeId = TYPEID_PHOTO;
}

core::MPhoto::~MPhoto()
{
    _parent->remove(this);
}
