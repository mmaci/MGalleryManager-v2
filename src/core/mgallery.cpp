#include "core/mdatabase.h"
#include "core/mphoto.h"

core::MGallery::MGallery(std::string name, MDatabase* database, MGallery* gallery) :
    MObject(name, database, gallery)
{
}

core::MGallery::~MGallery()
{
}

