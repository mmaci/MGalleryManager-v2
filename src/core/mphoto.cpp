#define _DEBUG

#include "core/mphoto.h"
#include "core/mgallery.h"
#include "gui/mgridwidget/mgridwidgetviewer.h"

#include <QColor>

namespace core
{

MPhoto::MPhoto(MGallery* parent) :
    MObject(parent)
{
    _typeId = TYPEID_PHOTO;
}

MPhoto::MPhoto(MPhotoInfo info, MGallery* parent) :
    MObject(parent)
{
    _info = info;
    _typeId = TYPEID_PHOTO;

    // loading an image for processing
    load(info.fileInfo().absoluteFilePath().toStdString());
}

MPhoto::~MPhoto()
{
}

////////////////////////////////////////////////////////////////
// Conversions
////////////////////////////////////////////////////////////////

/**
 * \brief generates a pixmap straight from the file
 * used when creating initial thumbnail, converting a boost::gil view is much more expensive
 * also scales to proper dimensions
 */

QPixmap MPhoto::pixmapFromFile(int maxSize)
{
    QPixmap image(QString(_info.path().c_str()));

    // no need for scaling
    if (!maxSize)
	return image;

    // scaling
    if (image.height() > image.width())
	image = image.scaledToHeight(std::min(maxSize, image.height()));
    else
	image = image.scaledToWidth(std::min(maxSize, image.width()));

    return image;
}

/**
 * \brief converts a boost::gil view to a QImage
 * copies all the RGB values pixel by pixel
 */
template <typename SourceView>
QImage MPhoto::viewToQImage(const SourceView& source)
{
    using namespace boost::gil;
    // only able to convert 3 channel rgbs
    BOOST_ASSERT_MSG(num_channels<SourceView>::value == 3, "Must have 3 channels - RGB.");

    QImage tmpImage(source.width(), source.height(), QImage::Format_RGB16);

    // we iterate through all the pixels and copy the values
    for (int y = 0; y < source.height(); ++y)
    {
	typename SourceView::x_iterator source_it = source.row_begin(y);
	for (int x = 0; x < source.width(); ++x)
	    tmpImage.setPixel(x, y, qRgb(source_it[x][0], source_it[x][1], source_it[x][2]));
    }
    return tmpImage;
}

/**
 * \brief wrapper for creating a pixmap from a boost::gil view
 * calculates proper image size and passes it on
 */
QPixmap MPhoto::pixmapFromView(int maxSize)
{
    // it's better to do all the maths using doubles, not to lose any digits
    double width = static_cast<double>(_image.width());
    double height = static_cast<double>(_image.height());
    // if we have maxSize set, we scale, otherwise we do not
    if (maxSize)
    {
	double max = static_cast<double>(maxSize);
	double coef;
	// vertical image
	if (_image.height() > _image.width())
	{
	    coef = height / max;
	    if (height > max) height = max;
	    width = width / coef;

	}
	// horizontal image
	else
	{
	    coef = width / max;
	    if (width > max) width = max;
	    height = height / coef;
	}
    }
    return pixmapFromView(static_cast<int>(width), static_cast<int>(height));
}

/**
 * \brief creates a pixmap from a view, given proper dimensions
 * creates an image with given dimensions, resizes the original image into it
 * and calls conversion to QImage
 */
QPixmap MPhoto::pixmapFromView(int width, int height)
{
    using namespace boost::gil;

    rgb8_image_t resultImage(width, height);

    if (width != _image.width() || height != _image.height())
	resize(const_view(_image), view(resultImage));
    else
	resultImage = _image;

    return pixmapFromView(viewToQImage(const_view(resultImage)));
}

/**
 * \brief conversion from QImage to QPixmap
 */
QPixmap MPhoto::pixmapFromView(const QImage& image)
{
    return QPixmap::fromImage(image);
}

////////////////////////////////////////////////////////////////
// Rotation
////////////////////////////////////////////////////////////////

/**
 * \brief wrapper for image rotation
 * calculates and creates an image big enough for variable rotation
 * sets an appropriate background and calls rotation itself
 */
void MPhoto::rotate(mimage::RGB background, double angle)
{
    using namespace boost::gil;   

    angle = angle * (mnumeric::PI/180.0);

    double width = _image.width();
    double height = _image.height();

    // canvas size after rotation
    double canvasHeight =   std::fabs(std::sin(angle)*width)	+ std::fabs(std::cos(angle)*height);
    double canvasWidth =    std::fabs(std::sin(angle)*height)	+ std::fabs(std::cos(angle)*width);

    rgb8_image_t resultImage(canvasWidth, canvasHeight);
    fill_pixels(view(resultImage), rgb8_pixel_t(background.red, background.green, background.blue));

    rotate(const_view(_image), view(resultImage), angle);

    // save and add to history   
    pushToHistory(resultImage);
    _image = resultImage;    
}

/**
 * \brief rotation handler
 * able to operate on templated color views
 * basically just applies a matrix transformation onto 2 templated views
 * template allows us to work in multiple color spaces rgb/grayscale - 8b/16b
 */
template <typename SourceView, typename DestView>
void MPhoto::rotate(const SourceView& source, const DestView& dest, double angle)
{
    using namespace boost::gil;

    matrix3x2<double> transformation =	getTranslationMatrix(source, angle) *
					matrix3x2<double>::get_rotate(angle);

    resample_pixels(source, dest, transformation, bilinear_sampler());
}

/**
 * \brief returns a 3x2 translation matrix based on image rotation
 * after an image is rotated it shifts outside of the canvas
 * we have to compute a translation matrix to move the image to fit the canvas
 */
template <typename SourceView>
boost::gil::matrix3x2<double> MPhoto::getTranslationMatrix(const SourceView& source, double angle)
{
    angle = mnumeric::mod(angle, 2*mnumeric::PI);

    std::pair<double, double> result = std::make_pair(0.0, 0.0);
    if (angle <= mnumeric::PI/2)
	result = std::make_pair(0.0, source.width()*std::sin(angle));
    else
    if (angle <= mnumeric::PI)
	result = std::make_pair(-std::cos(angle)*source.width(), std::sin(angle)*source.width() - std::cos(angle)*source.height());
    else
    if (angle <= 3*mnumeric::PI/2)
	result = std::make_pair(-std::cos(angle)*source.width() - std::sin(angle)*source.height(), -std::cos(angle)*source.height());
    else
    if (angle <= 2*mnumeric::PI)
	result = std::make_pair(-std::sin(angle)*source.height(), 0.0);

    return boost::gil::matrix3x2<double>(1.0, 0.0, 0.0, 1.0, -result.first, -result.second);
}

////////////////////////////////////////////////////////////////
// Resize
////////////////////////////////////////////////////////////////

/**
 * \brief image resize wrapper
 * resizes an image holding scale into maxSize x maxSize image
 * example: maxSize: 200, original image: 300x200, final image 200x(200*(200/300))
 */
void MPhoto::resize(double maxSize)
{
    using namespace boost::gil;

    double width, height;
    // width > height
    if (_image.width() > _image.height())
    {
	width = maxSize;
	height = _image.height() / (_image.width()/maxSize);
    }
    // height >= width
    else
    {
	width = _image.width() / (_image.height()/maxSize);
	height = maxSize;
    }

    rgb8_image_t resultImage(rgb8_image_t::point_t(width, height));

    resize(const_view(_image), view(resultImage));

    // save and add to history
    pushToHistory(resultImage);
    ++_historyIt;
    _image = resultImage;
}

/**
 * \brief image resize wrapper
 * creates a canvas for image resize and calls proper handlers
 */
void MPhoto::resize(double width, double height)
{
    using namespace boost::gil;

    rgb8_image_t resultImage(rgb8_image_t::point_t(width, height));

    resize(const_view(_image), view(resultImage));

    // save and add to history
    pushToHistory(resultImage);
    _image = resultImage;   
}

/**
 * \brief image resize handler
 * scales the original view onto a new canvas
 */
template <typename SourceView, typename DestView>
void MPhoto::resize(const SourceView& source, const DestView& dest)
{
    using namespace boost::gil;

    resize_view(source, dest, bilinear_sampler());
}

////////////////////////////////////////////////////////////////
// Color Change
////////////////////////////////////////////////////////////////

/**
 * \brief
 */
void MPhoto::brightness(double value)
{
    using namespace boost::gil;

    BOOST_ASSERT_MSG(value <= 255.0 && value >= -255.0, "Brightness value must be in range between -100.0 and 100.0.");

    rgb8_image_t resultImage(rgb8_image_t::point_t(_image.width(), _image.height()));

    brightness(const_view(_image), view(resultImage), value);

    // save and add to history
    pushToHistory(resultImage);
    _image = resultImage;
}

/**
 * \brief
 */
template <typename SourceView, typename DestView>
void MPhoto::brightness(const SourceView& source, const DestView& dest, double value)
{
    using namespace boost::gil;

    BOOST_ASSERT_MSG(num_channels<SourceView>::value == 3, "Must have 3 channels - RGB.");

    for (int y = 0; y < source.height(); ++y)
    {
	typename SourceView::x_iterator source_it = source.row_begin(y);
	typename DestView::x_iterator dest_it = dest.row_begin(y);

	for (int x = 0; x < source.width(); ++x)
	{
	    dest_it[x][0] = std::min(source_it[x][0] + value, 255.0);
	    dest_it[x][1] = std::min(source_it[x][1] + value, 255.0);
	    dest_it[x][2] = std::min(source_it[x][2] + value, 255.0);
	}

    }
}

void MPhoto::contrast(double value)
{
    using namespace boost::gil;

    BOOST_ASSERT_MSG(value <= 100.0 && value >= -100.0, "Contrast value must be in range between -100.0 and 100.0.");

    rgb8_image_t resultImage(rgb8_image_t::point_t(_image.width(), _image.height()));

    // rescale the value to <-100,100> range
    value = 1 + value/100.0;
    contrast(const_view(_image), view(resultImage), value);

    // save and add to history
    pushToHistory(resultImage);
    _image = resultImage;
}

template <typename SourceView, typename DestView>
void MPhoto::contrast(const SourceView& source, const DestView& dest, double value)
{
    using namespace boost::gil;

    BOOST_ASSERT_MSG(num_channels<SourceView>::value == 3, "Must have 3 channels - RGB.");

    for (int y = 0; y < source.height(); ++y)
    {
	typename SourceView::x_iterator source_it = source.row_begin(y);
	typename DestView::x_iterator dest_it = dest.row_begin(y);

	for (int x = 0; x < source.width(); ++x)
	{
	    dest_it[x][0] = mnumeric::setRange((source_it[x][0] - 127.0)*value + 127.0, 0.0, 255.0);
	    dest_it[x][1] = mnumeric::setRange((source_it[x][1] - 127.0)*value + 127.0, 0.0, 255.0);
	    dest_it[x][2] = mnumeric::setRange((source_it[x][2] - 127.0)*value + 127.0, 0.0, 255.0);
	}

    }
}

void MPhoto::saturation(double value)
{
    using namespace boost::gil;

    BOOST_ASSERT_MSG(value <= 100.0 && value >= -100.0, "Saturation value must be in range between -100.0 and 100.0.");

    rgb8_image_t resultImage(rgb8_image_t::point_t(_image.width(), _image.height()));

    saturation(const_view(_image), view(resultImage), value);

    // save and add to history
    pushToHistory(resultImage);
    _image = resultImage;
}

template <typename SourceView, typename DestView>
void MPhoto::saturation(const SourceView& source, const DestView& dest, double value)
{
    using namespace boost::gil;

    BOOST_ASSERT_MSG(num_channels<SourceView>::value == 3, "Must have 3 channels - RGB.");

    for (int y = 0; y < source.height(); ++y)
    {
	typename SourceView::x_iterator source_it = source.row_begin(y);
	typename DestView::x_iterator dest_it = dest.row_begin(y);

	for (int x = 0; x < source.width(); ++x)
	{
	    mimage::RGB rgbColor(source_it[x][0], source_it[x][1], source_it[x][2]);
	    mimage::HSV hsvColor = mimage::RGBtoHSV(rgbColor);

	    if (hsvColor.hue != COLOR_UNDEFINED)
		hsvColor.saturation += (value/20.0);

	    if (hsvColor.saturation < 0.0)
		hsvColor.saturation = 0.0;

	    rgbColor = mimage::HSVtoRGB(hsvColor);

	    dest_it[x][0] = mnumeric::setRange(rgbColor.red, 0, 255);
	    dest_it[x][1] = mnumeric::setRange(rgbColor.green, 0, 255);
	    dest_it[x][2] = mnumeric::setRange(rgbColor.blue, 0, 255);
	}

    }
}

void MPhoto::blackandwhite()
{
    saturation(-100.0);
}

////////////////////////////////////////////////////////////////
// Saving & Loading
////////////////////////////////////////////////////////////////

bool MPhoto::load(std::string path)
{
    using namespace boost::gil;

    // we read jpeg
    jpeg_read_image(path, _image);
    // initial step in history
    _historyIt = _history.begin();
    pushToHistory(_image);
    _originalImage = _image;

    return true;
}


bool MPhoto::saveAs(std::string path, bool force)
{
    using namespace boost::gil;

    jpeg_write_view(path, view(_image));

    return true;
}

void MPhoto::pushToHistory(boost::gil::rgb8_image_t image)
{
    ++_historyIt;
    while (_historyIt != _history.end())
	_historyIt = _history.erase(_historyIt);

    _history.push_back(image);
    _historyIt = --_history.end();

    while (_history.size() > HISTORY_SIZE)
	popFromHistory();
}

void MPhoto::popFromHistory()
{
    _history.pop_front();
}

bool MPhoto::backward()
{
    if (_historyIt != _history.begin())
    {
	--_historyIt;
	_image = *_historyIt;
	return true;
    }
    return false;
}
bool MPhoto::forward()
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

} // NAMESPACE core

