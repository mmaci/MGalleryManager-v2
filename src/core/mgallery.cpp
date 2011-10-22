#include "core/mdatabase.h"
#include "core/mphoto.h"

core::MGallery::MGallery(core::MGalleryInfo info, core::MGallery* parent) :
    MObject(parent)
{
    _info = info;
    _typeId = TYPEID_GALLERY;
}

core::MGallery::~MGallery()
{
    std::set<core::MObject*>::iterator it;
    while(!_content.empty())
    {
	it = _content.begin();
	delete *it;
	_content.erase(it);
    }
}

core::MGallery* core::MGallery::insert(core::MGalleryInfo info)
{
    MGallery* gallery = new MGallery(info, this);
    _content.insert(gallery);

    return gallery;
}

core::MPhoto* core::MGallery::insert(core::MPhotoInfo info)
{
    core::MPhoto* photo = new core::MPhoto(info, this);
    _content.insert(photo);

    return photo;
}
