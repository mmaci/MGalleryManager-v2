#ifndef MPROJECT_H
#define MPROJECT_H

#include <set>

#include <QFileInfo>


namespace core
{
    class MGallery;
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

	private:
	    MGallery* _base;
	    unsigned int _maxid;
    };
}

#endif // MPROJECT_H
