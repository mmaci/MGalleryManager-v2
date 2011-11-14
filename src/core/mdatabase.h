#ifndef MDATABASE_H
#define MDATABASE_H

#include <set>

#include <QFileInfo>

namespace core
{
    class MPhoto;
    class MObject;

    class MDatabase
    {
	public:
	    MDatabase();
	    ~MDatabase();

	    void insert(MObject* obj);

	    unsigned int const generateId();
	    unsigned int const size(){ return _content.size(); }

	    MPhoto* find(QFileInfo fileInfo);
	    void remove(MObject* obj){ _content.erase(obj); }

	private:
	    std::set<MObject*> _content;
	    unsigned int _maxid;
    };
}

#endif // MDATABASE_H
