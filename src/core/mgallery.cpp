#include "core/mdatabase.h"
#include "core/mphoto.h"

core::MGallery::MGallery()
{
    _parentDatabase = NULL;
    _parentGallery = NULL;
}

core::MGallery::~MGallery()
{
}

core::MGallery::MGallery(core::MDatabase* parent)
{
    _parentDatabase = parent;
    _parentGallery = NULL;
}

core::MGallery::MGallery(MGallery* parent)
{
    _parentDatabase = parent->getParentDatabase();
    _parentGallery = parent;
}
