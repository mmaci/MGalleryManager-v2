#include "core/mdatabase.h"

core::MDatabase::MDatabase()
{
}

unsigned int const core::MDatabase::generatePhotoId()
{
    if (photos.empty())
	return 0;

    std::map<unsigned int, MPhoto*>::iterator it;
    it = photos.end(); --it;
    return (*it).first;
}
