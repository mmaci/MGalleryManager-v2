#ifndef MDATABASE_H
#define MDATABASE_H

#include <map>

namespace core
{
    class MGallery;
    class MPhoto;
    class MDatabase
    {
	public:
	    MDatabase();

	    void add(MGallery* gallery);

	    unsigned int const generatePhotoId();

	    unsigned int const getCountGalleries(){ return galleries.size(); }
	    unsigned int const getCountPhotos(){ return photos.size(); }

	private:
	    std::map<unsigned int, MGallery*> galleries;
	    std::map<unsigned int, MPhoto*> photos;
    };
}

#endif // MDATABASE_H
