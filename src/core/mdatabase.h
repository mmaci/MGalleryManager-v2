#ifndef MDATABASE_H
#define MDATABASE_H

#include <map>

#include <core/mgallery.h>
#include <core/mphoto.h>

namespace core
{    
    class MGallery;
    class MDatabase
    {
	public:
	    MDatabase();
	    ~MDatabase();

	    void add(MGallery* gallery);
	    void add(unsigned int id, MPhoto* photo);

	    unsigned int const generatePhotoId();

	    unsigned int const getCountGalleries(){ return _galleries.size(); }
	    unsigned int const getCountPhotos(){ return _photos.size(); }

	    MPhoto* find(QFileInfo fileInfo);

	private:
	    std::map<unsigned int, MGallery*> _galleries;
	    std::map<unsigned int, MPhoto*> _photos;
    };
}

#endif // MDATABASE_H
