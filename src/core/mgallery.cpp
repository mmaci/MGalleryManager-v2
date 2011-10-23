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
    std::cout << "deleting gallery" << std::endl;
    std::set<core::MObject*>::iterator it;
    while(!_content.empty())
    {
	it = _content.begin();
	delete *it;
	_content.erase(it);
    }
}

core::MPhoto* core::MGallery::find(QFileInfo info)
{
    std::set<core::MObject*>::iterator it;
    core::MPhoto* photo;
    for (it = _content.begin(); it != _content.end(); ++it)
    {
	if (photo = (*it)->toPhoto())
	{
	    if (photo->info().fileInfo() == info)
		return photo;
	}
    }
    return NULL;
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
