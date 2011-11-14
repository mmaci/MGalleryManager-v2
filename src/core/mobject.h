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

// forward declarations
namespace gui
{
    class MGridWidgetItem;
    class MTreeWidgetItem;
}

namespace core
{
    struct MGPSInfo
    {
	// TODO: struct holding geographical data
    };

    // forward declarations
    class MGallery;    
    class MPhoto;    
    class MObject
    {
	public:
	    // constructor/destructor
	    MObject(MGallery* parent = NULL);
	    virtual ~MObject(){ };

	    // conversions
	    MGallery* toGallery();
	    MPhoto* toPhoto();
	    MObject* toObject();

	    // get
	    char typeId() const { return _typeId; }
	    MGallery* parent() { return _parent; }
	    gui::MGridWidgetItem* gridItem(){ return _gridItem; }
	    gui::MTreeWidgetItem* treeWidgetItem(){ return _treeItem; }

	    // set
	    void setGridWidgetItem(gui::MGridWidgetItem* item){ _gridItem = item; }
	    void setTreeWidgetItem(gui::MTreeWidgetItem* item){ _treeItem = item; }
	    void setFavourite();

	    void destroy();

	protected:	    	    
	    char		    _typeId;

	private:
	    MGallery*		    _parent;
	    gui::MGridWidgetItem*   _gridItem;
	    gui::MTreeWidgetItem*   _treeItem;
	    bool		    _favourite;
    };
}

#endif // MOBJECT_H
