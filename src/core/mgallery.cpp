#define _DEBUG

#include "core/mproject.h"
#include "core/mphoto.h"
#include "core/mgallery.h"


namespace core
{
/**
 * constructor
 * @param info
 * @param parent
 */
MGallery::MGallery(MGallery* parent) :
    MObject(parent)
{
    _typeId = TYPEID_GALLERY;

    #ifdef _DEBUG
    std::cout << "Creating new instance of MGallery (" << _info.name() << ")" << std::endl;
    #endif
}

/**
 * constructor
 * @param info
 * @param parent
 */
MGallery::MGallery(MGalleryInfo info, MGallery* parent) :
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
MGallery::~MGallery()
{
    #ifdef _DEBUG
    std::cout << "Deleting contents of MGallery (" << _info.name() << ")" << std::endl;
    #endif    
    std::set<MObject*>::iterator it;
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
MPhoto* MGallery::find(QFileInfo info)
{
    std::set<MObject*>::iterator it;
    MPhoto* photo;
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
MGallery* MGallery::insert(MGalleryInfo info)
{
    MGallery* gallery = new MGallery(info, this);
    _content.insert(gallery);

    return gallery;
}

void MGallery::insert(MGallery* gallery)
{
    _content.insert(gallery);

}

void MGallery::insert(MPhoto* photo)
{
    _content.insert(photo);

}


void MGallery::insert(MObject* object)
{
    _content.insert(object);
}

/**
 * @param info
 * @return
 */
MPhoto* MGallery::insert(MPhotoInfo info)
{
    MPhoto* photo = new MPhoto(info, this);
    _content.insert(photo);

    return photo;
}

} // NAMESPACE core
