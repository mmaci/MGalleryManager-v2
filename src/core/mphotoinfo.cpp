#include "mphotoinfo.h"
#include <iostream>

namespace core
{

/**
 * \brief constructor
 */
MPhotoInfo::MPhotoInfo()
{
}

/**
 * \brief constructor
 */
MPhotoInfo::MPhotoInfo(QFileInfo fileInfo)
{
    _fileInfo = fileInfo;
    _name = fileName();
    _description = "not implemented";
    _path = fileInfo.absoluteFilePath().toStdString();

    loadExifData();
}

/**
 * \brief a basic setter for Exif data
 */
void MPhotoInfo::setExif(unsigned int id, std::string content)
{
    if (id >= MAX_EXIF_DATA)
	return;

    _exif[id] = content;
}

/**
 * \brief loads all kinds of Exif data from a file
 */
void MPhotoInfo::loadExifData()
{
    if (ExifData* exifData = exif_data_new_from_file(_path.c_str()))
    {
	ExifIfd ifd;
	ExifTag tag;

	for (int i = 0; i < MAX_EXIF_DATA; ++i)
	{
	    switch (i)
	    {
		case EXIF_ISO:
		    ifd = EXIF_IFD_EXIF;
		    tag = EXIF_TAG_ISO_SPEED_RATINGS;
		    break;

		case EXIF_EXPOSURE_TIME:
		    ifd = EXIF_IFD_EXIF;
		    tag = EXIF_TAG_EXPOSURE_TIME;
		    break;

		case EXIF_FNUMBER:
		    ifd = EXIF_IFD_EXIF;
		    tag = EXIF_TAG_FNUMBER;
		    break;

		case EXIF_CAMERA:
		    ifd = EXIF_IFD_0;
		    tag = EXIF_TAG_MODEL;
		    break;

		case EXIF_FOCAL_LENGTH:
		    ifd = EXIF_IFD_EXIF;
		    tag = EXIF_TAG_FOCAL_LENGTH;
		    break;
	    }

	    std::string data = loadExifDataSpecific(exifData, EXIF_IFD_EXIF, EXIF_TAG_ISO_SPEED_RATINGS);
	    if (data != "")
		setExif(i, data);
	}
	// unloads exif data
	exif_data_unref(exifData);
    }
}

/**
 * \brief trims the buffer when we get an empty char
 */
void MPhotoInfo::trimSpaces(char* buffer)
{
    for (int i = 0; i < 1024; ++i)
    {
	if (buffer[i] == ' ')
	{
	    buffer[i] = 0;
	    break;
	}
    }
}

/**
 * \brief returns specific exif data in an std::string
 */
std::string MPhotoInfo::loadExifDataSpecific(ExifData* exifData, ExifIfd ifd, ExifTag tag)
{
    if (ExifEntry* exifEntry = exif_content_get_entry(exifData->ifd[ifd], tag))
    {
	char buffer[1024];
	exif_entry_get_value(exifEntry, buffer, sizeof(buffer));
	exif_entry_unref(exifEntry);

	trimSpaces(buffer);
	return std::string(buffer);
    }

    return std::string();
}

}
