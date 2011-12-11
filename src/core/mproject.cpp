#include "core/mproject.h"
#include "core/mgallery.h"
#include "core/mobject.h"
#include "core/mphoto.h"

core::MProject::MProject()
{
    _base = new core::MGallery();
}

/**
 * @brief destructor deleting all database content
 */
core::MProject::~MProject()
{
    // delete all photos
    std::set<core::MObject*>::iterator it;
    while(!_base->content().empty())
    {
	it = _base->content().begin();
	delete *it;

	_base->content().erase(it);
    }
}

/**
 * @brief generates a unique photo id
 * rbegin contains the last photo in the map (ordered by id), which is then incremented by 1
 */
unsigned int const core::MProject::generateId()
{
    if (_base->content().empty())
	return 0;

    return ++_maxid;
}

void core::MProject::insert(core::MObject* obj)
{
    _base->insert(obj);
}

core::MPhoto* core::MProject::find(QFileInfo fileInfo)
{
    std::set<core::MObject*>::iterator it;
    for (it = _base->content().begin(); it != _base->content().end(); ++it)
    {
	if (core::MPhoto* photo = (*it)->toPhoto())
	{
	    if (photo->info().fileInfo() == fileInfo)
		return photo;
	}
    }
    return NULL;
}
