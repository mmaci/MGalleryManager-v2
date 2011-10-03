#include "core/mgallery.h"

core::MGallery::MGallery()
{
    parentDatabase = NULL;
    parentGallery = NULL;
}

core::MGallery::MGallery(core::MDatabase* parent)
{
    parentDatabase = parent;
    parentGallery = NULL;
}

core::MGallery::MGallery(MGallery* parent)
{
    parentDatabase = parent->getParentDatabase();
    parentGallery = parent;
}

void core::MGallery::add(MGallery *gallery)
{
    galleries.insert(std::make_pair(parentDatabase->generatePhotoId(), gallery));
}

void core::MGallery::add(core::MPhoto *photo)
{
    photos.insert(std::make_pair(parentDatabase->generatePhotoId(), photo));
}
