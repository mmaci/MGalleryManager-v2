#ifndef MGALLERY_H
#define MGALLERY_H

#include <set>

#include <core/mobject.h>

namespace core
{
    class MDatabase;
    class MPhoto;    
    class MGallery : public MObject
    {
	public:
	    MGallery();
	    MGallery(MDatabase* parent);
	    MGallery(MGallery* parent);
	    ~MGallery();

	    void add(MGallery* gallery);
	    void add(unsigned int id, MPhoto* photo);
	    void remove(MObject* obj){ _content.erase(obj); }

	    MDatabase* const getParentDatabase(){ return _parentDatabase; }
	    MGallery* const getParentGallery(){ return _parentGallery; }

	private:
	    std::set<MObject*> _content;
	    MDatabase* _parentDatabase;
	    MGallery* _parentGallery;

	    unsigned int _size;
    };
}

#endif // MGALLERY_H
