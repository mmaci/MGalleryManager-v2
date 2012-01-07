#ifndef MPROJECT_H
#define MPROJECT_H

#include <set>
#include <memory>

#include <QFileInfo>

#include "core/mgallery.h"

namespace mcore
{    
    class MPhoto;
    class MObject;
    class MProject
    {
	public:
	    MProject();
	    ~MProject();

	    void insert(MObject* obj);

	    unsigned int const generateId();

	    MPhoto* find(QFileInfo fileInfo);
	    MGallery* base() const { return _base; }
	    std::string path() const { return _path; }
	    void setPath(std::string path){ _path = path; }
	    void setBase(MGallery* base);

	private:
	    MGallery* _base;
	    unsigned int _maxid;
	    std::string _path;
    };
}

#endif // MPROJECT_H
