#ifndef MPHOTO_H
#define MPHOTO_H

#include <QFileInfo>

#include <core/mobject.h>

namespace core
{    
    struct MPhotoInfo
    {
	public:
	    MPhotoInfo(){ };
	    MPhotoInfo(QFileInfo fileInfo){ _fileInfo = fileInfo; }
	    QFileInfo fileInfo(){ return _fileInfo; }

	private:
	    QFileInfo _fileInfo;

    };

    class MPhoto : public MObject
    {
	public:	    
	    MPhoto(MPhotoInfo info, MGallery* parent /* = NULL */); // defaulty must have a parent gallery !
	    ~MPhoto();
	    MPhotoInfo info() const { return _info; }

	private:
	    MPhotoInfo _info;
    };
}

#endif // MPHOTO_H
