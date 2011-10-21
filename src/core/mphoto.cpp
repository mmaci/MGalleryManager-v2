#include "core/mphoto.h"

core::MPhoto::MPhoto(core::MPhotoInfo info, core::MGallery* parent) :
    core::MObject(parent)
{
    _info = info;
}
