#ifndef MGALLERY_H
#define MGALLERY_H

#include <map>

#include <core/mphoto.h>
#include <core/mdatabase.h>

namespace core
{
    class MDatabase;

    class MGallery
    {
	public:
	    MGallery();
	    MGallery(MDatabase* parent);
	    MGallery(MGallery* parent);
	    ~MGallery();

	    void add(MGallery* gallery);
	    void add(MPhoto* photo);

	    MDatabase* const getParentDatabase(){ return parentDatabase; }

	private:
	    std::map<unsigned int, MGallery*> galleries;
	    std::map<unsigned int, MPhoto*> photos;
	    MDatabase* parentDatabase;
	    MGallery* parentGallery;

	    unsigned int count;
    };
}

#endif // MGALLERY_H
