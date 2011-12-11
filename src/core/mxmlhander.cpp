#include "mxmlhandler.h"

namespace core
{

MXMLHandler::MXMLHandler()
{
    _writer.setAutoFormatting(true);
}

void MXMLHandler::readXML()
{
    while (!_reader.atEnd())
    {
	_reader.readNext();
	// START ELEMENT
	//
	if (_reader.isStartElement())
	{
	    _currentElements.push_back(_reader.name().toString());

	    // <mgallery>
	    if (_currentElement() == ELEM_GALLERY)
	    {
		_tmpGallery = new MGallery(_topGallery());
		_topGallery()->insert(_tmpGallery);
		_galleries.push_back(_tmpGallery);
	    }
	    else
	    // <mphoto>
	    if (_currentElement() == ELEM_PHOTO)
	    {
		_currentPhoto = new MPhoto(_topGallery());
		_topGallery()->insert(_currentPhoto);
	    }
	}
	else
	// END ELEMENT
	//
	if (_reader.isEndElement())
	{
	    // </mgallery>
	    if (_currentElement() == ELEM_GALLERY)
		_galleries.pop_back();

	    // </mphoto>
	    if (_currentElement() == ELEM_PHOTO)
		_currentPhoto = NULL;

	    _currentElements.pop_back();
	}
	else
	// ELEMENT CONTENT
	//
	if (_reader.isCharacters() && !_reader.isWhitespace())
	{
	    // namespace mgallery
	    if (_reader.namespaceUri() == NAMESPACE_GALLERY)
	    {
		// <mgallery::name>
		if (_currentElement() == ELEM_NAME)
		{
		    _topGallery()->setName(_reader.text().toString().toStdString());
		}
		else
		// <mgallery::description>
		if (_currentElement() == ELEM_DESCRIPTION)
		{
		    _topGallery()->setDescription(_reader.text().toString().toStdString());
		}
	    }
	    else
	    // namespace mphoto
	    if (_reader.namespaceUri() == NAMESPACE_PHOTO)
	    {
		BOOST_ASSERT_MSG(_currentPhoto, "No allocated mphoto when inside namespace mphoto.");

		// <mphoto::name>
		if (_currentElement() == ELEM_NAME)
		{
		    _currentPhoto->setName(_reader.text().toString().toStdString());
		}
		else
		// <mphoto::description>
		if (_currentElement() == ELEM_DESCRIPTION)
		{
		    _currentPhoto->setDescription(_reader.text().toString().toStdString());
		}
		else
		// <mphoto::content>
		if (_currentElement() == ELEM_PATH)
		{
		    _currentPhoto->setPath(_reader.text().toString().toStdString());
		}
	    }

	}

	if (_reader.error())
	{
	    // TODO: Error handling class
	    #ifdef _DEBUG
	    std::cerr << "Error: " << _reader.lineNumber() << ": " << _reader.errorString().toStdString() << std::endl;
	    #endif
	}
    }
}

bool MXMLHandler::saveProject(MGallery* project)
{
    return writeToFile(_file, project);
}

bool MXMLHandler::saveProjectAs(std::string path, MGallery* baseGallery)
{
   QFile file(QString(path.c_str()));

    if (!file.open(QFile::WriteOnly | QFile::Text))
	return false;

    return writeToFile(&file, baseGallery);
}

bool MXMLHandler::writeToFile(QIODevice* device, MGallery* baseGallery)
{    
    _writer.setDevice(device);

    _writer.writeNamespace(NAMESPACE_GALLERY, NAMESPACE_GALLERY);
    _writer.writeNamespace(NAMESPACE_PHOTO, NAMESPACE_PHOTO);

    _writer.writeStartDocument();
    _writer.writeDTD("<!DOCTYPE mgallery manager>");
    _writer.writeStartElement("mgallery");
    _writer.writeAttribute("version", "0.2");           

    std::set<core::MObject*>::iterator it;
    std::set<core::MObject*> base = baseGallery->content();

    for (it = base.begin(); it != base.end(); ++it)
	writeItem(*it);

    _writer.writeEndElement();
    _writer.writeEndDocument();

    return true;
}

void MXMLHandler::writeItem(core::MObject* object)
{    
    // startElement
    switch (object->typeId())
    {
	case TYPEID_GALLERY:
	{
	    _writer.writeStartElement(ELEM_GALLERY);
	    core::MGallery* gallery = object->toGallery();
		// name
		_writer.writeStartElement(NAMESPACE_GALLERY, ELEM_NAME);
		    _writer.writeCharacters(QString(gallery->name().c_str()));
		_writer.writeEndElement();

		// description
		_writer.writeStartElement(NAMESPACE_GALLERY, ELEM_DESCRIPTION);
		    _writer.writeCharacters(QString(gallery->description().c_str()));
		_writer.writeEndElement();

		// content
		_writer.writeStartElement(NAMESPACE_GALLERY, ELEM_CONTENT);
		    std::set<core::MObject*>::iterator it;
		    std::set<core::MObject*> base = gallery->content();
		    for (it = base.begin(); it != base.end(); ++it)
			writeItem(*it);
		_writer.writeEndElement();

	    _writer.writeEndElement(); // ELEM_GALLERY

	    break;
	}

	case TYPEID_PHOTO:
	{
	    _writer.writeStartElement(ELEM_PHOTO);
	    core::MPhoto* photo = object->toPhoto();
		// name
		_writer.writeStartElement(NAMESPACE_PHOTO, ELEM_NAME);
		    _writer.writeCharacters(QString(photo->name().c_str()));
		_writer.writeEndElement();

		// description
		_writer.writeStartElement(NAMESPACE_PHOTO, ELEM_DESCRIPTION);
		    _writer.writeCharacters(QString(photo->description().c_str()));
		_writer.writeEndElement();

		// path
		_writer.writeStartElement(NAMESPACE_PHOTO, ELEM_PATH);
		    _writer.writeCharacters(QString(photo->path().c_str()));
		_writer.writeEndElement();

	    _writer.writeEndElement(); // ELEM_PHOTO

	    break;
	}

	case TYPEID_OBJECT:
	{
	    // this should be only temporary and never really happen
	    // we need to decide to throw an error here or just let it go through
	    _writer.writeStartElement(ELEM_UNDEFINED);
	    _writer.writeEndElement();
	    break;
	}
    }
}

} // NAMESPACE core
