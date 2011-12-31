#ifndef MXMLHANDLER_H
#define MXMLHANDLER_H
#define _DEBUG

#include <set>
#include <memory>

#include <core/mgallery.h>
#include <core/mobject.h>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamNamespaceDeclaration>
#include <QIODevice>
#include <QFile>

const QString ELEM_PATH = "path";
const QString ELEM_GALLERY = "mgallery";
const QString ELEM_PHOTO = "mphoto";
const QString ELEM_CONTENT = "content";
const QString ELEM_NAME = "name";
const QString ELEM_DESCRIPTION = "description";
const QString ELEM_UNDEFINED = "undefined";

const QString NAMESPACE = "mgalmanager";
const QString NAMESPACE_GALLERY = "mgallery";
const QString NAMESPACE_PHOTO = "mphoto";

namespace core
{
    class MXMLHandler
    {
	public:
	    MXMLHandler();	    	    

	    MGallery* loadProject(std::string path);
	    bool saveProject(MGallery* project);
	    bool saveProjectAs(std::string path, MGallery* baseGallery);

	private:
	    // creates a new project based on XML input
	    void readFile(QIODevice* device);
	    void readXML();
	    // generates XML from an existing project
	    bool writeToFile(QIODevice* device, MGallery* baseGallery);
	    void writeItem(MObject* object);	   

	    QXmlStreamReader	_reader;
	    QXmlStreamWriter	_writer;	    

	    QString		_currentNamespaceUri;

	    std::list<QString>	_currentElements;
	    QString		_currentElement() const { return _currentElements.back(); }

	    std::list<MGallery*> _galleries;
	    MGallery*		_topGallery() const { return _galleries.back(); }
	    MGallery*		_tmpGallery;

	    MPhoto*		_currentPhoto;
	    MGallery*		_currentGallery;
	    MGallery*		_parentGallery;

	    // DEBUG FUNCTIONS
	    #ifdef _DEBUG
	    void printToConsole(MGallery* gallery, int depth = 0);
	    #endif
    };
}

#endif // MXMLHANDLER_H
