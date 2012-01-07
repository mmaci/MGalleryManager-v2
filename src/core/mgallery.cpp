

#include "core/mproject.h"
#include "core/mphoto.h"
#include "core/mgallery.h"

namespace mcore
{
/**
 * constructor
 * \param info
 * \param parent
 */
MGallery::MGallery(MGallery* parent) :
    MObject(parent)
{
    _typeId = TYPEID_GALLERY;
}

/**
 * constructor
 * \param info
 * \param parent
 */
MGallery::MGallery(MGalleryInfo info, MGallery* parent) :
    MObject(parent)
{
    _info = info;
    _typeId = TYPEID_GALLERY;
}

/**
 * destructor
 */
MGallery::~MGallery()
{     
    std::set<MObject*>::iterator it;    
    while(!_content.empty())
    {	
	it = _content.begin();
	delete *it;
	_content.erase(it);
    }
}

/**
 * \param info
 * \return
 */
MPhoto* MGallery::find(QFileInfo info)
{
    std::set<MObject*>::iterator it;    
    for (it = _content.begin(); it != _content.end(); ++it)
    {
	if (MPhoto* photo = (*it)->toPhoto())
	{
	    if (photo->info()->fileInfo() == info)
		return photo;
	}
    }
    return NULL;
}

/**
 * \param info
 * \return
 */
MGallery* MGallery::insert(MGalleryInfo info)
{
    MGallery* gallery = new MGallery(info, this);
    _content.insert(gallery);

    return gallery;
}

void MGallery::insert(MGallery* gallery)
{
    _content.insert(gallery);
    gallery->setParent(this);

}

void MGallery::insert(MPhoto* photo)
{
    _content.insert(photo);
    photo->setParent(this);

}

void MGallery::insert(MObject* object)
{
    _content.insert(object);
    object->setParent(this);
}

/**
 * \param info
 * \return
 */
MPhoto* MGallery::insert(MPhotoInfo info)
{
    MPhoto* photo = new MPhoto(info, this);
    _content.insert(photo);

    return photo;
}

} // NAMESPACE core
