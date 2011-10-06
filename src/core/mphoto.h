#ifndef MPHOTO_H
#define MPHOTO_H

#include <QFileInfo>

#include <core/mobject.h>

namespace core
{    
    class MPhoto : public MObject
    {
	public:	    
	    MPhoto(QFileInfo fileInfo, MDatabase* database = 0, MGallery* gallery = 0);
	    QFileInfo fileInfo(){ return _fileInfo; }

	private:
	    QFileInfo _fileInfo;
    };
}

#endif // MPHOTO_H
