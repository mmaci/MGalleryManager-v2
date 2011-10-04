#include "core/mdatabase.h"

core::MDatabase::MDatabase()
{
}

/**
 * @brief destructor deleting all database content
 */
core::MDatabase::~MDatabase()
{
    // delete all photos
    std::map<unsigned int, MPhoto*>::iterator it_photo;
    while(!_photos.empty())
    {
	it_photo = _photos.begin();
	delete it_photo->second;

	_photos.erase(it_photo);

    }

    // delete all galleries
    std::map<unsigned int, MGallery*>::iterator it_gal;
    while (!_galleries.empty())
    {
	it_gal = _galleries.begin();
	delete it_gal->second;

	_galleries.erase(it_gal);
    }
}

/**
 * @brief generates a unique photo id
 * rbegin contains the last photo in the map (ordered by id), which is then incremented by 1
 */
unsigned int const core::MDatabase::generatePhotoId()
{
    if (_photos.empty())
	return 0;

    return ((_photos.rbegin())->first)+1;
}

void core::MDatabase::add(unsigned int id, core::MPhoto *photo)
{
    _photos.insert(std::make_pair(id, photo));
}

core::MPhoto* core::MDatabase::find(QFileInfo fileInfo)
{
    std::map<unsigned int, core::MPhoto*>::iterator it;
    core::MPhoto* photo;
    for (it = _photos.begin(); it != _photos.end(); ++it)
    {
	photo = it->second;
	if (photo->fileInfo() == fileInfo)
	    return photo;
    }
    return NULL;
}
