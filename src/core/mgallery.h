#ifndef MGALLERY_H
#define MGALLERY_H

#include <set>
#include <string>

#include "core/mphoto.h"

namespace core
{  
    struct MGalleryInfo
    {
	public:
	    MGalleryInfo(){ };
	    MGalleryInfo(std::string name, std::string description = ""){ _name = name; _description = description;}

	    // set
	    void setName(std::string name){ _name = name; }
	    void setDescription(std::string description){ _description = description; }

	    // get
	    std::string name() const { return _name; }
	    std::string description() const { return _description; }

	private:
	    std::string _name;
	    std::string _description;
    };

    class MGallery : public MObject
    {
	public:
	    // constructors/destructors
	    MGallery();
	    MGallery(MGalleryInfo info, MGallery* parent = NULL);
	    ~MGallery();

	    // modify data
	    MGallery* insert(MGalleryInfo info);
	    MPhoto* insert(MPhotoInfo info);
	    MPhoto* find(QFileInfo info);
	    void remove(MObject* object){ _content.erase(object); }

	    // GET
	    // information about gallery
	    /**
	     * Inherited info from MObject:
	     * - favourite
	     * - GPS info
	     */
	    int		count() const { return _content.size(); }
	    std::string name() const { return _info.name(); }
	    std::string description() const { return _info.description(); }
	    bool	empty() const { return _content.empty(); }
	    // content
	    std::set<MObject*> content() const { return _content; }

	    // SET
	    // methods used to set information
	    void setName(std::string name){ _info.setName(name); }
	    void setDescription(std::string description){ _info.setDescription(description); }

	    // !!!
	    // information holder, shouldn't be used, atm just a temporary class to access whole info
	    MGalleryInfo info() { return _info; }

	private:
	    std::set<MObject*> _content;
	    MGalleryInfo _info;
    };
}

#endif // MGALLERY_H
