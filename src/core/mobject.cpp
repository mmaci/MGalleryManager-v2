#include "mobject.h"
#include "mgallery.h"
#include "mdatabase.h"

core::MObject::MObject(core::MGallery* parent)
{
    _parentGallery = parent;
    if (parent)
	_parentDatabase = parent->getParentDatabase();
}

core::MObject::~MObject()
{
    if (_parentGallery)
	_parentGallery->remove(this);

    if (_parentDatabase)
	_parentDatabase->remove(this);
}
