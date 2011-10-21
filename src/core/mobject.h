#ifndef MOBJECT_H
#define MOBJECT_H

#include <string>
#include <QFileInfo>

namespace core
{

    class MGallery;
    class MDatabase;
    class MPhoto;

    class MObject
    {
	public:
	    MObject(MGallery* parent = NULL);
	    ~MObject();

	    // conversions
	    MGallery* toGallery();
	    MPhoto* toPhoto();
	    MObject* toObject();

	private:	    	   
	    MGallery* _parent;
    };
}

#endif // MOBJECT_H
