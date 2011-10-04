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

void core::MGallery::add(MGallery *gallery)
{
    _galleries.insert(std::make_pair(_parentDatabase->generatePhotoId(), gallery));
}

void core::MGallery::add(unsigned int id, core::MPhoto *photo)
{    
    _photos.insert(std::make_pair(id, photo));
    _parentDatabase->add(id, photo);
}
