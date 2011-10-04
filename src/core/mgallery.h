#ifndef MGALLERY_H
#define MGALLERY_H

#include <core/mobject.h>

namespace core
{
    class MDatabase;
    class MPhoto;
    class MGallery : MObject
    {
	public:
	    MGallery();
	    MGallery(MDatabase* parent);
	    MGallery(MGallery* parent);
	    ~MGallery();

	    void add(MGallery* gallery);
	    void add(unsigned int id, MPhoto* photo);

	    MDatabase* const getParentDatabase(){ return _parentDatabase; }
	    MGallery* const getParentGallery(){ return _parentGallery; }

	private:
	    std::map<unsigned int, MGallery*> _galleries;
	    std::map<unsigned int, MPhoto*> _photos;
	    MDatabase* _parentDatabase;
	    MGallery* _parentGallery;

	    unsigned int count;
    };
}

#endif // MGALLERY_H
