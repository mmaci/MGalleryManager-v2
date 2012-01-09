#include "core/mproject.h"
#include "core/mphoto.h"
#include "core/mgallery.h"

namespace mcore
{
/**
 * \brief   constructor
 * \param   parent  parent gallery
 */
MGallery::MGallery(MGallery* parent /* = NULL */) :
    MObject(parent)
{
    _typeId = TYPEID_GALLERY;
}

/**
 * constructor
 * \param   info    create a gallery with setting appropriate fileinfo beforehand
 * \param   parent  parent gallery
 */
MGallery::MGallery(MGalleryInfo info, MGallery* parent /* = NULL */) :
    MObject(parent)
{
    _typeId = TYPEID_GALLERY;
    _info = info;    
}

/**
 * \brief   constructor
 * \param   name    name of the gallery
 * \param   description description of the gallery
 * \param   parent  parent gallery
 */
MGallery::MGallery(std::string name, std::string description /* = std::string() */, MGallery* parent /* = NULL */) :
    MObject(parent)
{
    _typeId = TYPEID_GALLERY;
    _info.setName(name);
    _info.setDescription(description);
}

/**
 * \brief   destructor
 * This also destroys all children and even their widgets.
 */
MGallery::~MGallery()
{     
    std::vector<MObject*>::iterator it;
    while(!_content.empty())
    {	
	it = _content.begin();

	// we destroy every child and instances bound to it
	(*it)->destroy();
	_content.erase(it);
    }
}

/**
 * \brief   inserts an object inside the gallery
 * \param   object  pointer to the object
 * \return  true or false when succeeded/failed
 * Also checks for duplicites.
 * Same objects cannot be inserted more times and the same applies to
 * gallery names and files.
 */
bool MGallery::insert(MObject* object)
{
    // don't contain duplicite items
    if (_search(object))
	return false;

    switch (object->typeId())
    {
	// in case of inserting galleries we check for duplicite names
	case TYPEID_GALLERY:
	{
	    if (searchGallery(object->name()))
		return false;
	    break;
	}

	// in case of inserting photos we check for duplicite file infos
	// there might be more photos with the same name in a gallery
	case TYPEID_PHOTO:
	{
	    if (searchPhoto(object->toPhoto()->info()->fileInfo()))
		return false;
	    break;
	}

    }
    _content.push_back(object);
    return true;
}

/**
 * \brief   removes an object from a gallery
 * \param   object  pointer to an object, which we remove
 * \return  true or false when succeeded/failed
 * removes the item from the gallery and sets parent to NULL
 */
bool MGallery::remove(MObject* object)
{
    std::vector<MObject*>::iterator it;
    for (it = _content.begin(); it != _content.end(); ++it)
    {
	if (object == *it)
	{
	    (*it)->setParent(NULL);
	    _content.erase(it);
	    return true;
	}
    }
    return false;
}

/**
 * \brief   removes a gallery from a gallery
 * \param   name    name of the gallery
 * \return  true or false when succeeded/failed
 * removes a gallery based on its name, gallery names are unique
 */
bool MGallery::removeGallery(std::string name)
{
    std::vector<MObject*>::iterator it = _searchGallery(name);
    if (it == _content.end())
	return false;

    (*it)->setParent(NULL);
    _content.erase(it);
    return true;
}

/**
 * \brief   removes a photo from a gallery
 * \param   info    file info
 * \return  found photo or NULL
 * removes a photo based on its file info
 */
MPhoto* MGallery::searchPhoto(QFileInfo info)
{
    std::vector<MObject*>::iterator it;
    for (it = _content.begin(); it != _content.end(); ++it)
    {
	if ((*it)->typeId() != TYPEID_PHOTO)
	    continue;

	if ((*it)->toPhoto()->info()->fileInfo() == info)
	    return (*it)->toPhoto();
    }
    return NULL;
}

/**
 * \brief   searches for a gallery based on its name
 * \param   name  name of the gallery
 * \return  found gallery or NULL
 * Also checks for duplicites.
 * Same objects cannot be inserted more times and the same applies to
 * gallery names and files.
 */
MGallery* MGallery::searchGallery(std::string name)
{
    std::vector<MObject*>::iterator it;
    for (it = _content.begin(); it != _content.end(); ++it)
    {
	if ((*it)->typeId() != TYPEID_GALLERY)
	    continue;

	if ((*it)->name() == name)
	    return (*it)->toGallery();
    }
    return NULL;
}

/**
 * \brief   searches for an object within content
 * \param   object  pointer to the object
 * \return  found object or NULL
 * a private method to check if the object doesn't already exist inside content
 */
MObject* MGallery::_search(MObject* object)
{
    std::vector<MObject*>::iterator it;
    for (it = _content.begin(); it != _content.end(); ++it)
    {
	if (object == *it)
	    return *it;
    }
    return NULL;
}

/**
 * \brief   searches for a gallery based on its name
 * \param   name  name of the gallery
 * \return  iterator to the gallery, returns std::end() when none found
 * a private method to simplify searches within gallery
 */
std::vector<MObject*>::iterator MGallery::_searchGallery(std::string name)
{
    std::vector<MObject*>::iterator it;
    for (it = _content.begin(); it != _content.end(); ++it)
    {
	if ((*it)->typeId() != TYPEID_GALLERY)
	    continue;

	if (name == (*it)->name())
	    break;
    }
    return it;
}

} // NAMESPACE core
