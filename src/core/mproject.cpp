#include "core/mproject.h"
#include "core/mgallery.h"
#include "core/mobject.h"
#include "core/mphoto.h"

namespace core
{

MProject::MProject()
{    
    _base = new MGallery();
}

void MProject::setBase(MGallery* base)
{
    delete _base;
    _base = base;
}

/**
 * \brief destructor deleting all database content
 */
MProject::~MProject()
{
    // delete all photos
    std::set<MObject*>::iterator it;
    while(!_base->content().empty())
    {
	it = _base->content().begin();
	delete *it;

	_base->content().erase(it);
    }
}

/**
 * \brief generates a unique photo id
 * rbegin contains the last photo in the map (ordered by id), which is then incremented by 1
 */
unsigned int const MProject::generateId()
{
    if (_base->content().empty())
	return 0;

    return ++_maxid;
}

void MProject::insert(MObject* obj)
{
    _base->insert(obj);
}

MPhoto* MProject::find(QFileInfo fileInfo)
{
    std::set<MObject*>::iterator it;
    for (it = _base->content().begin(); it != _base->content().end(); ++it)
    {
	if (MPhoto* photo = (*it)->toPhoto())
	{
	    if (photo->info()->fileInfo() == fileInfo)
		return photo;
	}
    }
    return NULL;
}

}
