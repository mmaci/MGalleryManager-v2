#include "mobject.h"
#include "mgallery.h"
#include "mphoto.h"
#include "mdatabase.h"

core::MObject::MObject(core::MGallery* gallery)
{
    _parent = gallery;
}

// conversions
core::MGallery* core::MObject::toGallery(){ return static_cast<core::MGallery*>(this); }
core::MPhoto* core::MObject::toPhoto(){ return static_cast<core::MPhoto*>(this); }
core::MObject* core::MObject::toObject(){ return dynamic_cast<core::MObject*>(this); }

core::MObject::~MObject()
{    

    if (_parent)
	_parent->remove(this);
}
