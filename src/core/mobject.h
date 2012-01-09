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
namespace mgui
{
    class MGridWidgetItem;
    class MGridWidgetThumbnail;
    class MGridWidgetViewer;
    class MTreeWidgetItem;
}

namespace mcore
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
	    virtual ~MObject(){ /* empty */ };

	    // conversions
	    MGallery* toGallery();
	    MPhoto* toPhoto();
	    MObject* toObject();

	    // getters
	    char typeId() const { return _typeId; }
	    MGallery* parent() { return _parent; }
	    mgui::MGridWidgetViewer* gridViewer(){ return _gridViewer; }
	    mgui::MGridWidgetThumbnail* gridThumbnail(){ return _gridThumbnail; }
	    mgui::MTreeWidgetItem* treeWidgetItem(){ return _treeItem; }
	    bool isFavourite() const { return _favourite; }

	    // setters
	    void setThumbnail(mgui::MGridWidgetThumbnail* thumbnail){ _gridThumbnail = thumbnail; }
	    void setGridViewer(mgui::MGridWidgetViewer* viewer){ _gridViewer = viewer; }
	    void setTreeWidgetItem(mgui::MTreeWidgetItem* item){ _treeItem = item; }	    
	    void setParent(MGallery* parent){ _parent = parent; }

	    void setFavourite(bool apply);

	    // destroys all gui related objects and calls a destructor
	    void destroy();

	    // pure virtual functions
	    // every gallery or photo has this info in their info structures
	    virtual std::string name() const = 0;
	    virtual std::string description() const = 0;

	protected:	    	    
	    char			_typeId;

	private:
	    MGallery*			_parent;
	    mgui::MGridWidgetThumbnail* _gridThumbnail;
	    mgui::MGridWidgetViewer*	_gridViewer;
	    mgui::MTreeWidgetItem*	_treeItem;

	    bool			_favourite;
    };
}

#endif // MOBJECT_H
