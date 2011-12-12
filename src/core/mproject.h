#ifndef MPROJECT_H
#define MPROJECT_H

#include <set>

#include <QFileInfo>

#include "core/mgallery.h"

namespace core
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
	    MGallery* base(){ return _base; }
	    void setBase(MGallery* base)
	    {
		delete _base;
		_base = base;
	    }

	private:
	    MGallery* _base;
	    unsigned int _maxid;
    };
}

#endif // MPROJECT_H
