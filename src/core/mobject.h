#ifndef MOBJECT_H
#define MOBJECT_H

#include <string>
#include <iostream>
#include <QFileInfo>

enum TypeIds
{
    TYPEID_OBJECT,
    TYPEID_GALLERY,
    TYPEID_PHOTO
};

namespace core
{

    class MGallery;
    class MDatabase;
    class MPhoto;

    class MObject
    {
	public:
	    MObject(MGallery* parent = NULL);
	    virtual ~MObject(){ };

	    // conversions
	    MGallery* toGallery();
	    MPhoto* toPhoto();
	    MObject* toObject();

	    char typeId() const { return _typeId; }

	protected:
	    char _typeId;
	    MGallery* _parent;

	private:	    	   

    };
}

#endif // MOBJECT_H
