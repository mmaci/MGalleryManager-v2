#include "core/mdatabase.h"
#include "core/mphoto.h"

core::MGallery::MGallery(core::MGalleryInfo info, core::MGallery* parent) :
    MObject(parent)
{
    _info = info;
}

core::MGallery* core::MGallery::insert(core::MGalleryInfo info)
{
    MGallery* gallery = new MGallery(info, this);
    insert(gallery);

    return gallery;
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

void core::MGallery::insert(core::MGallery* gallery)
{
    _content.insert(gallery);
}

void core::MGallery::insert(core::MPhoto* photo)
{
    _content.insert(photo);
}

core::MPhoto* core::MGallery::insert(core::MPhotoInfo info)
{
    core::MPhoto* photo = new core::MPhoto(info, this);
    insert(photo);

    return photo;
}
