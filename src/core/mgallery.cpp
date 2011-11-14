#define _DEBUG

#include "core/mdatabase.h"
#include "core/mphoto.h"
#include "core/mgallery.h"

/**
 * constructor
 * @param info
 * @param parent
 */
core::MGallery::MGallery(core::MGalleryInfo info, core::MGallery* parent) :
    MObject(parent)
{
    _info = info;
    _typeId = TYPEID_GALLERY;

    #ifdef _DEBUG
    std::cout << "Creating new instance of MGallery (" << _info.name() << ")" << std::endl;
    #endif
}

/**
 * destructor
 */
core::MGallery::~MGallery()
{
    #ifdef _DEBUG
    std::cout << "Deleting contents of MGallery (" << _info.name() << ")" << std::endl;
    #endif
    std::set<core::MObject*>::iterator it;
    while(!_content.empty())
    {
	it = _content.begin();
	delete *it;
	_content.erase(it);
    }
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGallery (" << _info.name() << ")" << std::endl;
    #endif
}

/**
 * @param info
 * @return
 */
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

/**
 * @param info
 * @return
 */
core::MGallery* core::MGallery::insert(core::MGalleryInfo info)
{
    MGallery* gallery = new MGallery(info, this);
    _content.insert(gallery);

    return gallery;
}

/**
 * @param info
 * @return
 */
core::MPhoto* core::MGallery::insert(core::MPhotoInfo info)
{
    core::MPhoto* photo = new core::MPhoto(info, this);
    _content.insert(photo);

    return photo;
}
