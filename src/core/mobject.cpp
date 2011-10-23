#include "mobject.h"
#include "mgallery.h"
#include "mphoto.h"
#include "mdatabase.h"

core::MObject::MObject(core::MGallery* gallery)
{
    _parent = gallery;
    _typeId = TYPEID_OBJECT;
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
