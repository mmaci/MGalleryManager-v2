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
	    MGallery(std::string name = "", MDatabase* database = 0, MGallery* gallery = 0);
	    ~MGallery();

	    void add(MGallery* gallery);
	    void add(unsigned int id, MPhoto* photo);
	    void remove(MObject* obj){ _content.erase(obj); }

	private:
	    std::set<MObject*> _content;

	    unsigned int _size;
    };
}

#endif // MGALLERY_H
