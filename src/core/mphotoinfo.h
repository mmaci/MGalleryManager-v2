#ifndef MPHOTOINFO_H
#define MPHOTOINFO_H

#include <string>
#include <memory>
#include <QFileInfo>

#include <libexif/exif-data.h>

enum Exif
{
    EXIF_CAMERA,
    // lens
    EXIF_FOCAL_LENGTH,
    EXIF_ISO,
    EXIF_EXPOSURE_TIME,
    EXIF_FNUMBER,

    MAX_EXIF_DATA
};

namespace mcore
{

class MPhotoInfo
{
    public:
	MPhotoInfo();
	MPhotoInfo(QFileInfo fileInfo);

	QFileInfo fileInfo(){ return _fileInfo; }
	std::string filePath(){ return _fileInfo.absoluteFilePath().toStdString(); }
	std::string fileName(){ return _filename; }

	std::string path() const { return _path; }
	std::string name() const { return _name; }
	std::string description() const { return _description; }

	void setPath(std::string path){ _path = path; }
	void setName(std::string name){ _name = name; }
	void setDescription(std::string description){ _description = description; }

	void setExif(unsigned int id, std::string content);
	std::string getExif(unsigned int id) const { return id < MAX_EXIF_DATA ? _exif[id] : std::string(); }

	void trimSpaces(char* buffer);
	void loadExifData();
	std::string loadExifDataSpecific(ExifData* data, ExifIfd ifd, ExifTag tag);

	void makeFilename();

    private:
	std::string _name;
	std::string _description;
	std::string _path;

	std::string _filename;

	std::string _exif[MAX_EXIF_DATA];

	QFileInfo _fileInfo;
};

} // NAMESPACE core

#endif // MPHOTOINFO_H
