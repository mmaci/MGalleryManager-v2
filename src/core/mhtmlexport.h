#ifndef MHTMLEXPORT_H
#define MHTMLEXPORT_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <QDir>
#include <boost/assert.hpp>
#include <boost/algorithm/string.hpp>
#include <ctype.h>
#include "core/mobject.h"
#include "core/mgallery.h"

// tags
const std::string TAG_HTML	= "html";
const std::string TAG_TITLE	= "title";
const std::string TAG_HEAD	= "head";
const std::string TAG_BODY	= "body";
const std::string TAG_DIV	= "div";
const std::string TAG_H1	= "h1";
const std::string TAG_H2	= "h2";
const std::string TAG_H3	= "h3";
const std::string TAG_P		= "p";
const std::string TAG_IMG	= "img";
const std::string TAG_A		= "a";
const std::string TAG_UL	= "ul";
const std::string TAG_LI	= "li";
const std::string TAG_LINK	= "link";
const std::string TAG_META	= "meta";

// attributes
const std::string ATTR_ID	= "id";
const std::string ATTR_CLASS	= "class";
const std::string ATTR_SRC	= "src";
const std::string ATTR_HREF	= "href";
const std::string ATTR_REL	= "rel";
const std::string ATTR_CHARSET	= "charset";

// special case, where content is also saved as a tag, with an empty name
const std::string CONTENT	= "";

const std::string DOCTYPE	= "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">";

namespace mcore
{
class MHTMLElement;

typedef std::pair<std::string, std::string> MHTMLAttribute;	// <type, value>
typedef std::pair<MHTMLElement*, bool>	    MHTMLElementHolder; // <element, start tag?>
typedef std::pair<MPhoto*, std::string>	    MPhotoExport;	// <photo, path>
#define MakeHolder(a,b) (std::make_pair(a,b))
#define MakePhotoExport(a,b) (std::make_pair(a,b))

class MHTMLExport
{
    public:
	MHTMLExport();
	void exportHTML(MObject* object, std::string path, bool initial = false, int level = 0);

    private:	
	bool openFile(std::string file);
	void closeFile();

	void writeHTMLHeader(MObject* object, int level = 0);
	void writeHTMLFooter();

	void writePairTag(std::string tag);
	void writePairTagEnd();
	void writeSingleTag(std::string tag);
	void writeAttribute(std::string name, std::string value);
	void writeContent(std::string content);

	void writeGalleryPage(MGallery* gallery, int level = 0);
	void writePhotoPage(MPhoto* photo, int level = 0);

	void printToCurrentFile(std::string output);

	void copyPhoto(MPhoto* photo, std::string path);
	void exportPhotos();

	template <typename T>
	std::string stdString(T input);
	std::string normalizeName(std::string input);

	std::string _filePath;
	std::ofstream _fileStream;

	MHTMLElement* _tag;
	std::vector<MHTMLElement*> _tags;
	std::vector<MHTMLElementHolder> _content;
	std::vector<MPhotoExport> _photos;
};

class MHTMLElement
{
    public:
	MHTMLElement(std::string name, bool pair);

	void addAttribute(std::string name, std::string value);
	void addContent(std::string content);
	std::string string(bool end = false);

	bool isPair() const { return _pair; }
	std::string name() const { return _name; }
	std::string content() const { return _content; }
	std::vector<MHTMLAttribute> attributes() const { return _attributes; }

    private:
	bool _pair;
	std::string _name;
	std::string _content;
	std::vector<MHTMLAttribute> _attributes;
};

}

#endif // MHTMLEXPORT_H
