#include "gui/mtreewidget/mtreewidget.h"
#include "gui/mtreewidget/mtreewidgetitem.h"
#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "core/mobject.h"
#include "core/mgallery.h"
#include "core/mphoto.h"

namespace mcore
{

/**
 * \brief   constructor
 * \param   parent    pointer to parent gallery
 */
MObject::MObject(MGallery* parent /* = NULL */)
{
    _typeId	    = TYPEID_OBJECT;
    _parent	    = parent;

    _treeItem	    = NULL;
    _gridThumbnail  = NULL;
    _gridViewer	    = NULL;

    _favourite	    = false;
}

////////////////////////////////////////////////////////////////
// Conversions
////////////////////////////////////////////////////////////////
/**
 * \brief   converts to MGallery
 * \return  pointer to MGallery
 * Calls a static_cast to MGallery or returns a NULL if conversion is not possible.
 * Can be used also as a more expensive check for object type (typeId being the cheaper one).
 */
MGallery* MObject::toGallery()
{
    if (_typeId == TYPEID_PHOTO)
	return NULL;

    return static_cast<MGallery*>(this);
}

/**
 * \brief   converts to MPhoto
 * \return  pointer to MPhoto
 * Calls a static_cast to MPhoto or returns a NULL if conversion is not possible.
 * Can be used also as a more expensive check for object type (typeId being the cheaper one).
 */
MPhoto* MObject::toPhoto()
{
    if (_typeId == TYPEID_GALLERY)
	return NULL;

    return static_cast<MPhoto*>(this);
}

/**
 * \brief   converts to MObject
 * \return  pointer to MObject
 * Used when we need the base for MGallery or MPhoto, dynamic_cast does runetime checking
 * so if it fails, it returns a NULL pointer by itself. It shouldn't be used much, but there
 * might be cases where we don't know the exact type and so we have use the object's base.
 */
MObject* MObject::toObject()
{
    return dynamic_cast<MObject*>(this);
}


////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////
/**
 * \brief   marks the item as favourite
 * \param   apply   if we want to apply or remove favourite
 * also handles displaying favourite in proper widgets
 */
void MObject::setFavourite(bool apply)
{   
    _favourite = apply;

    if (_gridThumbnail)
	_gridThumbnail->setFavourite(apply);

    if (_treeItem)
	_treeItem->setFavourite(apply);
}

/**
 * \brief   deletes all objects and itself
 * deletes everything connected to object itself and calls a destructor
 */
void MObject::destroy()
{
    // MTreeItemWidget
    if (_treeItem)
	_treeItem->destroy();

    // MGridWidgetItem
    if (_gridThumbnail)
	_gridThumbnail->destroy();

    // remove item from gallery container
    // it doesn't call the destructor, just unlinks the object from the gallery, setting its parent to NULL
    // that's because we might want to move a gallery to another gallery
    if (_parent)    
	_parent->remove(this);

    // now we destroy this object
    // in case of galleries wa also delete all their children
    delete this;
}

} // NAMESPACE core
