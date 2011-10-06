#include "core/mdatabase.h"

core::MDatabase::MDatabase()
{
    _maxid = 0;
}

/**
 * @brief destructor deleting all database content
 */
core::MDatabase::~MDatabase()
{
    // delete all photos
    std::set<core::MObject*>::iterator it;
    while(!_content.empty())
    {
	it = _content.begin();
	delete *it;

	_content.erase(it);
    }
}

/**
 * @brief generates a unique photo id
 * rbegin contains the last photo in the map (ordered by id), which is then incremented by 1
 */
unsigned int const core::MDatabase::generateId()
{
    if (_content.empty())
	return 0;

    return ++_maxid;
}

void core::MDatabase::insert(core::MObject* obj)
{
    _content.insert(obj);
}

core::MPhoto* core::MDatabase::find(QFileInfo fileInfo)
{
    std::set<core::MObject*>::iterator it;
    for (it = _content.begin(); it != _content.end(); ++it)
    {
	if (core::MPhoto* photo = static_cast<core::MPhoto*>(*it))
	{
	    if (photo->fileInfo() == fileInfo)
		return photo;
	}
    }
    return NULL;
}
