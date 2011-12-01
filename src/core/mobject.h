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
    class MGridWidgetThumbnail;
    class MGridWidgetViewer;
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
	    gui::MGridWidgetViewer* gridViewer(){ return _gridViewer; }
	    gui::MGridWidgetThumbnail* gridThumbnail(){ return _gridThumbnail; }
	    gui::MTreeWidgetItem* treeWidgetItem(){ return _treeItem; }

	    // set
	    void setGridThumbnail(gui::MGridWidgetThumbnail* thumbnail){ _gridThumbnail = thumbnail; }
	    void setGridViewer(gui::MGridWidgetViewer* viewer){ _gridViewer = viewer; }
	    void setTreeWidgetItem(gui::MTreeWidgetItem* item){ _treeItem = item; }
	    void setFavourite();

	    void destroy();

	protected:	    	    
	    char		    _typeId;

	private:
	    MGallery*		    _parent;
	    gui::MGridWidgetThumbnail* _gridThumbnail;
	    gui::MGridWidgetViewer* _gridViewer;
	    gui::MTreeWidgetItem*   _treeItem;
	    bool		    _favourite;
    };
}

#endif // MOBJECT_H
