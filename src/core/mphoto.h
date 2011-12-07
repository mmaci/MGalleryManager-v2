#ifndef MPHOTO_H
#define MPHOTO_H

#include <list>

#include <QFileInfo>
#include <QPixmap>
#include <QImage>
#include <QLabel>

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/assert.hpp>

#include "core/mobject.h"

#include "core/mimage.h"
#include "core/mnumeric.h"

namespace gui
{
    class MGridWidgetViewer;
}

namespace core
{                
    class MGallery;

    struct MPhotoInfo
    {
	public:
	    MPhotoInfo(){ };
	    MPhotoInfo(QFileInfo fileInfo){ _fileInfo = fileInfo; }
	    QFileInfo fileInfo(){ return _fileInfo; }
	    std::string filepath(){ return _fileInfo.absoluteFilePath().toStdString(); }
	    std::string filename(){ return _fileInfo.baseName().toStdString(); }

	private:
	    QFileInfo _fileInfo;

    };

    class MPhoto : public MObject
    {
	public:	    
	    MPhoto(MPhotoInfo info, MGallery* parent /* = NULL */); // defaulty must have a parent gallery !
	    ~MPhoto();

	    // set and get
	    MPhotoInfo info(){ return _info; } // when we want access to the whole info
	    std::string filePath(){ return _info.fileInfo().absoluteFilePath().toStdString(); }

	    // gui helpers
	    // we use these to generate different gui features like thumbnails
	    QPixmap pixmapFromView(const QImage& image);
	    QPixmap pixmapFromView(int width, int height);
	    QPixmap pixmapFromView(int maxSize);
	    QPixmap pixmapFromFile(int maxSize);
	    template <typename SourceView>
	    QImage viewToQImage(const SourceView& source);

	    // transforms
	    // rotation
	    void rotate(mimage::RGB background, double angle);
	    template <typename SourceView, typename DestView>
	    void rotate(const SourceView& source, const DestView& dest, double angle);
	    template <typename SourceView>
	    boost::gil::matrix3x2<double> getTranslationMatrix(const SourceView& source, double angle);

	    // resize
	    void resize(double width, double height);
	    void resize(double maxSize);
	    template <typename SourceView, typename DestView>
	    void resize(const SourceView& source, const DestView& dest);

	    // color change
	    // value ranges from -255.0 to 255.0
	    void brightness(double value);
	    template <typename SourceView, typename DestView>
	    void brightness(const SourceView& source, const DestView& dest, double value);

	    void contrast(double value);
	    template <typename SourceView, typename DestView>
	    void contrast(const SourceView& source, const DestView& dest, double value);


	    void saturate(double value);
	    void blackandwhite();

	    bool load(std::string path);

	    bool save(bool force = false);
	    bool saveAs(std::string path, bool force = false);

	    bool backward()
	    {
		if (_historyIt != _history.begin())
		{
		    --_historyIt;
		    _image = *_historyIt;
		    return true;
		}
		return false;
	    }

	    bool forward()
	    {
		++_historyIt;

		if (_historyIt != _history.end())
		{
		    _image = *_historyIt;
		    return true;
		}

		--_historyIt;
		return false;
	    }

	private:
	    // fileinfo about the original file
	    // contains all kinds of metadata, filepath, ...
	    MPhotoInfo	    _info;

	    // color and image representations
	    boost::gil::rgb8_image_t _image;
	    std::list<boost::gil::rgb8_image_t> _history;
	    std::list<boost::gil::rgb8_image_t>::iterator _historyIt;
    };
}

#endif // MPHOTO_H
