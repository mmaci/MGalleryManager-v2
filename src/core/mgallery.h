#ifndef MGALLERY_H
#define MGALLERY_H

#include <vector>
#include <string>

#include "core/mphoto.h"

namespace mcore
{  
    struct MGalleryInfo
    {
	public:
	    MGalleryInfo(){ };
	    MGalleryInfo(std::string name, std::string description = ""){ _name = name; _description = description;}

	    // setters
	    void setName(std::string name){ _name = name; }
	    void setDescription(std::string description){ _description = description; }

	    // getters
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
	    MGallery(MGallery* parent = NULL);
	    MGallery(MGalleryInfo info, MGallery* parent = NULL);
	    MGallery(std::string name, std::string description = std::string(), MGallery* parent = NULL);
	    ~MGallery();

	    // modify data
	    bool insert(MObject* object);
	    bool remove(MObject *object);
	    bool removeGallery(std::string name);

	    // find	    
	    MPhoto* searchPhoto(QFileInfo info);
	    MGallery* searchGallery(std::string name);

	    // getters
	    // also inherits gps info from MObject
	    std::string name() const { return _info.name(); }
	    std::string description() const { return _info.description(); }

	    int	size() const { return _content.size(); }
	    bool isEmpty() const { return _content.empty(); }

	    std::vector<MObject*> content() { return _content; }

	    // setters
	    // methods used to set information
	    void setName(std::string name){ _info.setName(name); }
	    void setDescription(std::string description){ _info.setDescription(description); }

	    MGalleryInfo info() { return _info; }

	private:
	    std::vector<MObject*>::iterator _searchGallery(std::string name);
	    MObject* _search(MObject* object);

	    std::vector<MObject*> _content;
	    MGalleryInfo _info;
    };
}

#endif // MGALLERY_H
