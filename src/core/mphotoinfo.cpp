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
    ExifData* exifData = exif_data_new_from_file(_path.c_str());
    std::auto_ptr<ExifData> exifDataPtr(exifData);
    if (exifDataPtr.get())
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

	    std::string data = loadExifDataSpecific(exifDataPtr.get(), ifd, tag);
	    if (data != "")
		setExif(i, data);
	}	
    }
}

/**
 * \brief returns specific exif data in an std::string
 */
std::string MPhotoInfo::loadExifDataSpecific(ExifData* exifData, ExifIfd ifd, ExifTag tag)
{
    ExifEntry* exifEntry;
    exifEntry = exif_content_get_entry(exifData->ifd[ifd], tag);
    std::auto_ptr<ExifEntry> exifEntryPtr(exifEntry);

    if (!exifEntryPtr.get())
	return std::string();

    char buffer[1024];
    exif_entry_get_value(exifEntryPtr.get(), buffer, sizeof(buffer));
    trimSpaces(buffer);

    return std::string(buffer);
}

/**
 * \brief trims the buffer when we get an empty char
 */
void MPhotoInfo::trimSpaces(char* buffer)
{
    char *s = buffer-1;
    for (; *buffer; ++buffer)
    {
	if (*buffer != ' ')
	    s = buffer;
    }
    *++s = 0;
}

}
