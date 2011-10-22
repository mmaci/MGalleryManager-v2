#ifndef MOBJECT_H
#define MOBJECT_H

#include <string>
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
	    ~MObject();

	    // conversions
	    MGallery* toGallery();
	    MPhoto* toPhoto();
	    MObject* toObject();

	    char typeId(){ return _typeId; }

	protected:
	    char _typeId;

	private:	    	   
	    MGallery* _parent;	    
    };
}

#endif // MOBJECT_H
