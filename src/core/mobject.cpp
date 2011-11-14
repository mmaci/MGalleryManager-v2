#define _DEBUG

#include "gui/mtreewidget.h"
#include "gui/mtreewidgetitem.h"
#include "gui/mgridwidget.h"
#include "gui/mgridwidgetitem.h"
#include "core/mobject.h"
#include "core/mgallery.h"
#include "core/mphoto.h"

core::MObject::MObject(core::MGallery* gallery)
{
    _parent = gallery;
    _typeId = TYPEID_OBJECT;

    _treeItem = NULL;
    _gridItem = NULL;
    _favourite = false;
}

// conversions
core::MGallery* core::MObject::toGallery()
{
    if (_typeId == TYPEID_PHOTO)
	return NULL;

    return static_cast<core::MGallery*>(this);
}

core::MPhoto* core::MObject::toPhoto()
{
    if (_typeId == TYPEID_GALLERY)
	return NULL;

    return static_cast<core::MPhoto*>(this);
}

core::MObject* core::MObject::toObject()
{
    return dynamic_cast<core::MObject*>(this);
}

void core::MObject::setFavourite()
{
    if (_favourite)
    {
	_favourite = false;
	if (_gridItem)
	    _gridItem->showStar(false);
	if (_treeItem)
	    _treeItem->highlight(false);
    }
    else
    {
	_favourite = true;
	if (_gridItem)
	    _gridItem->showStar(true);
	if (_treeItem)
	    _treeItem->highlight(true);
    }
}

void core::MObject::destroy()
{
    // MTreeItemWidget
    if (_treeItem)
    {
	if (gui::MTreeWidget* widget = _treeItem->widget())
	    widget->remove(_treeItem);
    }

    // MGridWidgetItem
    if (_gridItem)
    {
	if (gui::MGridWidget* widget = _gridItem->widget())
	    widget->remove(_gridItem);
    }

    if (_parent)
    {
	if (core::MGallery* gallery = _parent->toGallery())
	    gallery->remove(this);
    }

    delete this; // implicit destructor call
}
