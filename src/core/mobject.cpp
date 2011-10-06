#include "mobject.h"
#include "mgallery.h"
#include "mdatabase.h"

core::MObject::MObject(std::string name, core::MDatabase* database, core::MGallery* gallery)
{
    _name = name;
    _parentDatabase = database ? database : 0;
    _parentGallery = gallery ? gallery : 0;
}

core::MObject::~MObject()
{    

    if (_parentGallery)
	_parentGallery->remove(this);

    if (_parentDatabase)
	_parentDatabase->remove(this);
}
