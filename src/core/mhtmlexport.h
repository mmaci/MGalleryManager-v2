#ifndef MHTMLEXPORT_H
#define MHTMLEXPORT_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <QDir>

#include <boost/assert.hpp>

#include "core/mobject.h"
#include "core/mgallery.h"

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

const std::string CONTENT	= "";

const std::string ATTR_ID	= "id";
const std::string ATTR_CLASS	= "class";
const std::string ATTR_SRC	= "src";
const std::string ATTR_HREF	= "href";

namespace core
{
class MHTMLElement;

typedef std::pair<std::string, std::string> MHTMLAttribute;
typedef std::pair<MHTMLElement*, bool> MHTMLElementHolder;

class MHTMLExport
{
    public:
	MHTMLExport();
	void exportHTML(MObject* object, std::string path, bool initial = false);

    private:
	// generates XML from an existing project
	bool openFile(std::string file);
	void closeFile();

	void writeHTMLHeader();
	void writeHTMLFooter();

	void writePairTag(std::string tag);
	void writePairTagEnd();
	void writeSingleTag(std::string tag);
	void writeAttribute(std::string name, std::string value);
	void writeContent(std::string content);

	void writeGalleryPage(MGallery* gallery);
	void writePhotoPage(MPhoto* photo);

	void printToCurrentFile(std::string output);

	std::string		_filePath;
	std::ofstream		_fileStream;

	MHTMLElement*		_tag;
	std::vector<MHTMLElement*>	_tags;
	std::vector<MHTMLElementHolder> _content;

	template <typename T>
	std::string stdString(T input);
};

class MHTMLElement
{
    public:
	MHTMLElement(std::string name, bool pair);
	void addAttribute(std::string name, std::string value);
	void addContent(std::string content);

	bool isPair() const { return _pair; }
	std::string name() const { return _name; }
	std::string content() const { return _content; }
	std::vector<MHTMLAttribute> attributes() const { return _attributes; }

	std::string string(bool end = false);

    private:
	bool			    _pair;
	std::string		    _name;
	std::string		    _content;
	std::vector<MHTMLAttribute> _attributes;
};

}

#endif // MHTMLEXPORT_H
