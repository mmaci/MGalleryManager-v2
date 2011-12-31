#include "mhtmlexport.h"

namespace core
{

template <typename T>
std::string MHTMLExport::stdString(T input)
{
    std::stringstream ss;
    ss << input;
    return ss.str();
}

////////////////////////////////////////////////////////////////
// MHTML Export
////////////////////////////////////////////////////////////////

MHTMLExport::MHTMLExport()
{

}

void MHTMLExport::exportHTML(MObject* object, std::string path, bool initial)
{
    QString p = QString(path.c_str());
    if (!QDir(p).exists())
	QDir().mkdir(p);

    if (MGallery* gallery = object->toGallery())
    {
	if (!initial)
	{
	    writeGalleryPage(gallery);
	    openFile(path+gallery->name()+".html");
	    std::vector<MHTMLElementHolder>::iterator ij;
	    for (ij = _content.begin(); ij != _content.end(); ++ij)
		printToCurrentFile(ij->first->string(!ij->second));
	    closeFile();
	}

	std::set<MObject*>::iterator ik;
	std::set<MObject*> content = gallery->content();
	for (ik = content.begin(); ik != content.end(); ++ik)
	{
	    std::string newPath = path + gallery->name();
	    if (!initial)
		newPath.append("/");
	    exportHTML(*ik, newPath);
	}
    }
    else
    if (MPhoto* photo = object->toPhoto())
    {
	writePhotoPage(photo);
	openFile(path+photo->name()+".html");
	std::vector<MHTMLElementHolder>::iterator ij;
	for (ij = _content.begin(); ij != _content.end(); ++ij)
	    printToCurrentFile(ij->first->string(!ij->second));
	closeFile();
    }
}

void MHTMLExport::writeGalleryPage(MGallery* gallery)
{
    writeHTMLHeader();

    writePairTag(TAG_H2);
	writeContent(gallery->name());
    writePairTagEnd();

    writePairTag(TAG_DIV);
	writeAttribute(ATTR_ID, "gallery-content");

    std::set<MObject*> content = gallery->content();
    std::set<MObject*>::iterator it;
    for (it = content.begin(); it != content.end(); ++it)
    {
	writePairTag(TAG_DIV);
	    writeAttribute(ATTR_CLASS, "gallery-object");
	    writePairTag(TAG_H3);
		writePairTag(TAG_A);
		    writeAttribute(ATTR_HREF, "filename");
		    writeContent((*it)->name());
		writePairTagEnd();
	    writePairTagEnd();

	    switch ((*it)->typeId())
	    {
		case TYPEID_GALLERY:
		{
		    writePairTag(TAG_P);
			writeContent(stdString(gallery->count()));
		    writePairTagEnd();
		    break;
		}

		case TYPEID_PHOTO:
		{
		    writeSingleTag(TAG_IMG);
		    writeAttribute(ATTR_SRC, (*it)->toPhoto()->path());
		    break;
		}
	    }

	writePairTagEnd();
    }
    writePairTagEnd();

    writeHTMLFooter();
}

void MHTMLExport::writePhotoPage(MPhoto* photo)
{
    writeHTMLHeader();

    writePairTag(TAG_H2);
	writeContent(photo->name());
    writePairTagEnd();

    writePairTag(TAG_DIV);
	writeAttribute(ATTR_ID, "photo-content");
	writeSingleTag(TAG_IMG);
	    writeAttribute(ATTR_SRC, photo->path());

    writePairTagEnd();

    writeHTMLFooter();
}

void MHTMLExport::printToCurrentFile(std::string output)
{
    output.append("\n");

    _fileStream << output;
}

bool MHTMLExport::openFile(std::string file)
{
    _filePath = file;
    _fileStream.open(_filePath.c_str());

    return true;
}

void MHTMLExport::closeFile()
{
    _content.clear();
    _fileStream.close();
}

void MHTMLExport::writeHTMLHeader()
{
    writePairTag(TAG_HTML);
    writePairTag(TAG_HEAD);
	writePairTag(TAG_TITLE);
	    writeContent("title");
	writePairTagEnd(); // </title>
    writePairTagEnd(); // </head>
    writePairTag(TAG_BODY);
}

void MHTMLExport::writeHTMLFooter()
{
    writePairTagEnd(); // </body>
    writePairTagEnd(); // </html>
}

void MHTMLExport::writePairTag(std::string tag)
{
    MHTMLElement* tmp = new MHTMLElement(tag, true);

    _tags.push_back(tmp);
    _tag = _tags.back();
    _content.push_back(std::make_pair(_tag, true));
}

void MHTMLExport::writePairTagEnd()
{
    // change tag to stack top if it's single (we can't just pop single tags due to attribute addition)
    if (!_tag->isPair())
	_tag = _tags.back();

    _content.push_back(std::make_pair(_tag, false));
    _tags.pop_back();
    _tag = _tags.back();
}

void MHTMLExport::writeSingleTag(std::string tag)
{
    _tag = new MHTMLElement(tag, false);
    _content.push_back(std::make_pair(_tag, true)); // single tag is considered as a start tag, otherwise it would crash on assert
}

void MHTMLExport::writeContent(std::string content)
{
    BOOST_ASSERT_MSG(_tag->isPair(), "Attempted to write content after a non-pair tag.");

    MHTMLElement* tmp = new MHTMLElement(CONTENT, false);
    tmp->addContent(content);

    _content.push_back(std::make_pair(tmp, true));
}

/**
 * \brief writes an attribute to the current tag
 * \param name	attribute name
 * \param value attribute value
 */
void MHTMLExport::writeAttribute(std::string name, std::string value)
{
    BOOST_ASSERT_MSG(_tag, "No tag selected.");

    _tag->addAttribute(name, value);
}

////////////////////////////////////////////////////////////////
// MHTML Tag
////////////////////////////////////////////////////////////////

MHTMLElement::MHTMLElement(std::string name, bool pair)
{
    _name = name;
    _pair = pair;
}

/**
 * \brief adds an attribute
 * \param name	attribute name
 * \param value attribute value
 */
void MHTMLElement::addAttribute(std::string name, std::string value)
{
    MHTMLAttribute attribute;
	attribute.first = name;
	attribute.second = value;

    _attributes.push_back(attribute);
}

void MHTMLElement::addContent(std::string content)
{
    _content = content;
}

/**
 * \brief creates string from a tag
 * \param end	makes the tag start or end
 * based on the name, attributes, parity, we generate an std::string
 */
std::string MHTMLElement::string(bool end)
{
    if (_name.compare(CONTENT) == 0)
	return _content;

    std::string output;

    if (end)
    {
	//BOOST_ASSERT_MSG(_pair, "Attempted to generate an end tag while being non-pair.");

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
