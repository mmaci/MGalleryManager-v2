#include "mhtmlexport.h"

namespace mcore
{

////////////////////////////////////////////////////////////////
// MHTML Export
////////////////////////////////////////////////////////////////

/// \brief  a constructor
MHTMLExport::MHTMLExport()
{
}

/**
 * \brief   converts anything to std::string
 * \param   input   input parameter
 * \return  an std::string output
 * loads basically anything into a stringstream, which is then converted to an std::string
 */
// TODO: implement this as an inline function, atm it's needed just here
template <typename T>
std::string MHTMLExport::stdString(T input)
{
    std::stringstream ss;
    ss << input;
    return ss.str();
}

/**
 * \brief   exports an object to an HTML gallery
 * \param   object  object we want to export
 * \param   path    destination path, where we want to create an export
 * \param   initial default: false, if set to true, skips writing html
 * A handler which recursivelly exports all objects (photos and galleries into html).
 * It should be started with initial set to true, because the whole project is an untitled gallery
 */
void MHTMLExport::exportHTML(MObject* object, std::string path, bool initial, int level)
{    
    // create a folder if it doesn't exist already
    QString p = QString(path.c_str());
    if (!QDir(p).exists())
	QDir().mkdir(p);

    // gallery
    if (MGallery* gallery = object->toGallery())
    {
	if (!initial)
	{
	    writeGalleryPage(gallery, level);
	    if (openFile(path+normalizeName(gallery->name())+".html"))
	    {
		std::vector<MHTMLElementHolder>::iterator ij;
		for (ij = _content.begin(); ij != _content.end(); ++ij)
		    printToCurrentFile(ij->first->string(!ij->second));

		closeFile();
	    }
	    ++level;
	}		    

	std::vector<MObject*>::iterator ik;
	std::vector<MObject*> content = gallery->content();
	for (ik = content.begin(); ik != content.end(); ++ik)
	{
	    std::string newPath = path+normalizeName(gallery->name());
	    if (!initial)
		newPath.append("\\");

	    exportHTML(*ik, newPath, false, level);
	}
    }
    else
    // photo
    if (MPhoto* photo = object->toPhoto())
    {	
	if (openFile(path+normalizeName(photo->name())+".html"))
	{
	    writePhotoPage(photo, level);

	    copyPhoto(photo, path+normalizeName(photo->name()));
	    std::vector<MHTMLElementHolder>::iterator ij;
	    int i = 0;
	    for (ij = _content.begin(); ij != _content.end(); ++ij, ++i)
		printToCurrentFile(ij->first->string(!ij->second));

	    closeFile();
	}
    }

    exportPhotos();
}

/**
 * \brief   converts a string to a valid filename
 * \param   input string
 * \return  a formatted string
 */
std::string MHTMLExport::normalizeName(std::string input)
{
    std::string result;
    boost::algorithm::to_lower(input);
    for (std::string::iterator it = input.begin(); it != input.end(); ++it)
    {
	if (isalnum(*it))
	    result += *it;
    }
    return result;
}

/**
 * \brief   resaves all used photos
 */
void MHTMLExport::exportPhotos()
{
    std::vector<MPhotoExport>::iterator it;
    for (it = _photos.begin(); it != _photos.end(); ++it)
    {
	std::string path = it->second;
	MPhoto* photo = it->first;
	photo->saveAs(path+"_thumb.jpg", 200);
	photo->saveAs(path+".jpg", 800);
    }
}

/**
 * \brief   generates an HTML gallery page
 * \param   gallery   input gallery
 * takes a gallery an generates an std::list with html tags prepared to being exported into HTML
 */
void MHTMLExport::writeGalleryPage(MGallery* gallery, int level)
{
    writeHTMLHeader(gallery->toObject(), level);

    writePairTag(TAG_H2);
	writeContent(gallery->name());
    writePairTagEnd();

    writePairTag(TAG_P);
	writeAttribute(ATTR_CLASS, "descr");
	writeContent(gallery->description());
    writePairTagEnd();

    writePairTag(TAG_DIV);
	writeAttribute(ATTR_ID, "gallery-content");

    std::vector<MObject*> content = gallery->content();
    std::vector<MObject*>::iterator it;
    for (it = content.begin(); it != content.end(); ++it)
    {
	writePairTag(TAG_DIV);
	    writeAttribute(ATTR_CLASS, "gallery-object");
	    writePairTag(TAG_H3);
		writePairTag(TAG_A);
		    writeAttribute(ATTR_HREF, normalizeName(gallery->name())+"/"+normalizeName((*it)->name())+".html");
		    writeContent((*it)->name());
		writePairTagEnd();
	    writePairTagEnd();

	    switch ((*it)->typeId())
	    {
		case TYPEID_GALLERY:
		{
		    writePairTag(TAG_P);
		    writePairTagEnd();
		    break;
		}

		case TYPEID_PHOTO:
		{
		    writeSingleTag(TAG_IMG);		    
		    writeAttribute(ATTR_SRC, normalizeName(gallery->name())+"/"+normalizeName((*it)->toPhoto()->name())+"_thumb.jpg");
		    break;
		}
	    }

	writePairTagEnd();
    }
    writePairTagEnd();

    writeHTMLFooter();
}

/**
 * \brief   adds a photo to the photo export list
 */
void MHTMLExport::copyPhoto(MPhoto *photo, std::string path)
{
    _photos.push_back(MakePhotoExport(photo, path));
}

/**
 * \brief   generates an HTML photo page
 * \param   photo   input photo
 * takes a photo an generates an std::list with html tags prepared to being exported into HTML
 */
void MHTMLExport::writePhotoPage(MPhoto* photo, int level)
{
    writeHTMLHeader(photo->toObject(), level);

    writePairTag(TAG_H2);
	writeContent(photo->name());
    writePairTagEnd();

    writePairTag(TAG_P);
	writeAttribute(ATTR_CLASS, "descr");
	writeContent(photo->description());
    writePairTagEnd();

    writePairTag(TAG_DIV);
	writeAttribute(ATTR_ID, "photo-content");
	writeSingleTag(TAG_IMG);
	    writeAttribute(ATTR_SRC, normalizeName(photo->name())+".jpg");

    writePairTagEnd();

    writePairTag(TAG_UL);
	writeAttribute(ATTR_ID, "photo-exif");
	for (int i = EXIF_CAMERA; i < MAX_EXIF_DATA; ++i)
	{
	    writePairTag(TAG_LI);
		writeAttribute(ATTR_CLASS, "photo-exif-specific");
		writeContent(photo->info()->getExif(i));
	    writePairTagEnd();
	}
    writePairTagEnd();

    writeHTMLFooter();
}

/**
 * \brief inserts std::string into std::fstream
 * \param output    string we are printing into the file
 * Takes a single std::string and prints it into std::fstream. Used mainly for formatting each
 * string separately and maybe some security reasons in the future.
 */
void MHTMLExport::printToCurrentFile(std::string output)
{
    output.append("\n");

    _fileStream << output;
}

/**
 * \brief   opens a filestream
 * \param   file	name of the file to open a filestream for
 * \return  true if we succeeded
 */
bool MHTMLExport::openFile(std::string file)
{
    _filePath = file;
    _fileStream.open(_filePath.c_str());

    return _fileStream.good();
}

/**
 * \brief   closes a filestream
 * Also clears an std::list used as a buffer for storing HTML tags for printing.
 */
void MHTMLExport::closeFile()
{
    _content.clear();
    _fileStream.close();
}

/**
 * \brief   generates an HTML header
 * \param   object  based on it's values we set tags in the header
 * creates an HTML header all the way until <body> tag (included)
 */
void MHTMLExport::writeHTMLHeader(MObject* object, int level)
{
    writeContent(DOCTYPE);
    writePairTag(TAG_HTML);
    writePairTag(TAG_HEAD);
	writeSingleTag(TAG_META);
	    writeAttribute(ATTR_CHARSET, "iso-8859-2");

	writeSingleTag(TAG_LINK);
	    writeAttribute(ATTR_REL, "stylesheet");
	    std::string l;
	    for (int i = 0; i < level; ++i)
		l.append("../");
	    writeAttribute(ATTR_HREF, l+"default.css");

	writePairTag(TAG_TITLE);
	    writeContent(object->name());
	writePairTagEnd(); // </title>
    writePairTagEnd(); // </head>
    writePairTag(TAG_BODY);
}

/**
 * \brief generates an HTML footer
 */
void MHTMLExport::writeHTMLFooter()
{
    writePairTagEnd(); // </body>
    writePairTagEnd(); // </html>
}

/**
 * \brief   generates a par tag
 * \param   tag	name of the tag
 * Calls an object constructor for a pair tag, sets it's name and changes the pointer
 * to the current tag for adding attributes. Object is also pushed onto 2 lists. One of
 * them being a stack with currently active tags, the second one being a list used for
 * exporting tags into HTML.
 */
void MHTMLExport::writePairTag(std::string tag)
{
    MHTMLElement* tmp = new MHTMLElement(tag, true);

    _tags.push_back(tmp);
    _tag = _tags.back();
    _content.push_back(MakeHolder(_tag, true)); // MHTMLElementHolder
}

/**
 * \brief   generates an end tag
 * Generates an end tag for the current tag, if it's a pair tag. There might be a single tag in the tag
 * pointer, so we take the last element in the pair tag stack. Single tags don't get inserted into the
 * stack, but have to be added into the tag pointer, because we add attributes to them in the same
 * manner we do with pair tags. Therefore we have to change the tag pointer to the last open pair tag.
 */
void MHTMLExport::writePairTagEnd()
{
    // change tag to stack top if it's single (we can't ignore single tags due to attribute addition)
    if (!_tag->isPair())
	_tag = _tags.back();

    _content.push_back(MakeHolder(_tag, false));
    _tags.pop_back();
    _tag = _tags.back();
}

/**
 * \brief   generates a single tag
 * \param   tag	name of the tag
 * Generates a single tag and pushes it into the list used for export into HTML.
 */
void MHTMLExport::writeSingleTag(std::string tag)
{
    _tag = new MHTMLElement(tag, false);
    _content.push_back(MakeHolder(_tag, true)); // single tag is considered as a start tag, otherwise it would crash on assert
}

/**
 * \brief   generates content
 * \param   content text to be printed
 * Content of a pair tag is considered to be another tag with the name CONTENT. It's only pushed into
 * the export list and crashes when we want to insert it after a single tag. We always must have a
 * double tag opened.
 */
void MHTMLExport::writeContent(std::string content)
{
    MHTMLElement* tmp = new MHTMLElement(CONTENT, false);
    tmp->addContent(content);

    _content.push_back(MakeHolder(tmp, true));
}

/**
 * \brief   writes an attribute to the current tag
 * \param   name	attribute name
 * \param   value attribute value
 */
void MHTMLExport::writeAttribute(std::string name, std::string value)
{
    BOOST_ASSERT_MSG(_tag, "No tag selected.");

    _tag->addAttribute(name, value);
}

////////////////////////////////////////////////////////////////
// MHTML Tag
////////////////////////////////////////////////////////////////

/**
 * \brief   a constructor
 * \param   name    name of the element
 * \param   pair    pair tag or single tag
 */
MHTMLElement::MHTMLElement(std::string name, bool pair)
{
    _name = name;
    _pair = pair;
}

/**
 * \brief   adds an attribute
 * \param   name    attribute name
 * \param   value   attribute value
 * Values are passed from a setter in MHTMLExport.
 */
void MHTMLElement::addAttribute(std::string name, std::string value)
{
    MHTMLAttribute attribute;
	attribute.first = name;
	attribute.second = value;

    _attributes.push_back(attribute);
}

/**
 * \brief   sets    content
 * \param   content text to be set
 * Content is a special tag with the name CONTENT and not having content empty.
 */
void MHTMLElement::addContent(std::string content)
{
    _content = content;
}

/**
 * \brief   creates string from a tag
 * \param   end	    makes the tag start or end
 * Based on the name, attributes, parity, we generate an std::string. The method gets
 * called by an iterator iterating through a finished list of tags.
 */
std::string MHTMLElement::string(bool end)
{
    if (_name.compare(CONTENT) == 0)
	return _content;

    std::string output;

    if (end)
    {
	BOOST_ASSERT_MSG(_pair, "Attempted to generate an end tag while being non-pair.");

	output.append("</");
	output.append(_name);
	output.append(">");
    }
    else
    {
	// '<tag'
	output.append("<");
	output.append(_name);

	std::vector<MHTMLAttribute>::iterator it;
	for (it = _attributes.begin(); it != _attributes.end(); ++it)
	{
	    // ' attribute="value"'
	    output.append(" "); // space
	    output.append(it->first); // attribute name
	    output.append("=\"");
	    output.append(it->second); // attribute value
	    output.append("\"");
	}

	// '/>' or '>'
	if (_pair)
	    output.append(">");
	else
	    output.append(" />");
    }

    return output;
}

} // NAMESPACE core
