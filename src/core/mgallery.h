#ifndef MGALLERY_H
#define MGALLERY_H

#include <set>
#include <string>

#include <core/mobject.h>
#include <core/mphoto.h>

namespace core
{
    struct MGalleryInfo
    {
	public:
	    MGalleryInfo(){ };
	    MGalleryInfo(std::string name){ _name = name; }

	    void setName(std::string name){ _name = name; }

	    std::string name(){ return _name; }

	private:
	    std::string _name;
    };

    class MDatabase;

    class MGallery : public MObject
    {
	public:
	    MGallery();
	    MGallery(MGalleryInfo info, MGallery* parent = NULL);
	    ~MGallery();

	    MGallery* insert(MGalleryInfo info);
	    MPhoto* insert(MPhotoInfo info);

	    void remove(MObject* obj){ _content.erase(obj); }

	    std::string name(){ return _info.name(); }
	    MGalleryInfo info(){ return _info; }

	private:
	    std::set<MObject*> _content;

	    MGalleryInfo _info;
    };
}

#endif // MGALLERY_H
