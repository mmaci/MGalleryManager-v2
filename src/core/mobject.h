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

namespace gui
{
    class MGridItem;
    class MTreeWidgetItem;
}

namespace core
{

    class MGallery;    
    class MPhoto;
    struct MPhotoInfo;

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

	    void remove();

	    void setGridWidgetItem(gui::MGridItem* item){ _gridItem = item; }
	    void setTreeWidgetItem(gui::MTreeWidgetItem* item){ _treeItem = item; }

	protected:
	    char _typeId;
	    MGallery* _parent;

	private:
	    gui::MGridItem* _gridItem;
	    gui::MTreeWidgetItem* _treeItem;
    };
}

#endif // MOBJECT_H
