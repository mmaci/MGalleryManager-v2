#define _DEBUG

#include "gui/mtreewidget/mtreewidget.h"
#include "gui/mtreewidget/mtreewidgetitem.h"
#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "core/mobject.h"
#include "core/mgallery.h"
#include "core/mphoto.h"

namespace core
{

MObject::MObject(MGallery* gallery)
{
    _parent = gallery;
    _typeId = TYPEID_OBJECT;

    _treeItem = NULL;
    _gridThumbnail = NULL;
    _gridViewer = NULL;
    _favourite = false;

    #ifdef _DEBUG
    std::cout << "Creating new instance of MObject" << std::endl;
    #endif
}

// conversions
MGallery* MObject::toGallery()
{
    if (_typeId == TYPEID_PHOTO)
	return NULL;

    return static_cast<MGallery*>(this);
}

MPhoto* MObject::toPhoto()
{
    if (_typeId == TYPEID_GALLERY)
	return NULL;

    return static_cast<MPhoto*>(this);
}

MObject* MObject::toObject()
{
    return dynamic_cast<MObject*>(this);
}

void MObject::setFavourite()
{
    if (_favourite)
    {
	_favourite = false;
	if (_gridThumbnail)
	    _gridThumbnail->showStar(false);
	if (_treeItem)
	    _treeItem->highlight(false);
    }
    else
    {
	_favourite = true;
	if (_gridThumbnail)
	    _gridThumbnail->showStar(true);
	if (_treeItem)
	    _treeItem->highlight(true);
    }
}

void MObject::destroy()
{
    // MTreeItemWidget
    if (_treeItem)
    {
	if (gui::MTreeWidget* widget = _treeItem->widget())
	    widget->remove(_treeItem);
    }

    // MGridWidgetItem
    if (_gridThumbnail)
    {
	if (gui::MGridWidget* widget = _gridThumbnail->widget())
	    widget->remove(_gridThumbnail);
    }

    if (_parent)
    {
	if (MGallery* gallery = _parent->toGallery())
	    gallery->remove(this);
    }

    delete this; // implicit destructor call
}

} // NAMESPACE core
