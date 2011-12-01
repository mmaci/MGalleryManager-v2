#define _DEBUG

#include "core/mphoto.h"
#include "core/mgallery.h"
#include "gui/mgridwidget/mgridwidgetviewer.h"

namespace core
{

MPhoto::MPhoto(MPhotoInfo info, MGallery* parent) :
    MObject(parent)
{
    _info = info;
    _typeId = TYPEID_PHOTO;    

    #ifdef _DEBUG
    std::cout << "Creating new instance of MPhoto (" << _info.fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif
}

MPhoto::~MPhoto()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MPhoto (" << _info.fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif
}

QPixmap MPhoto::generatePixmap(int maxSize)
{
    QPixmap image(_info.fileInfo().absoluteFilePath());
    if (image.height() > image.width())
	image = image.scaledToHeight(std::min(maxSize, image.height()));
    else
	image = image.scaledToWidth(std::min(maxSize, image.width()));

    return image;
}

////////////////////////////////////////////////////////////////
// Rotation
////////////////////////////////////////////////////////////////

/**
 * \brief wrapper for mextension::image rotation
 * calculates and creates an mextension::image big enough for variable rotation
 * sets an appropriate background and calls rotation itself
 */
void MPhoto::rotate(mextension::image::RGB background, double angle)
{
    using namespace boost::gil;   

    angle = angle * (mextension::numeric::PI/180.0);

    double width = _image.width();
    double height = _image.height();

    // canvas size after rotation
    double canvasWidth = std::fabs(height*cos(angle)) + std::fabs(width*sin(angle));
    double canvasHeight = std::fabs(width*cos(angle)) + std::fabs(height*sin(angle));

    rgb8_image_t resultImage(rgb8_image_t::point_t(canvasHeight, canvasWidth));
    fill_pixels(view(resultImage), rgb8_pixel_t(background.red, background.green, background.blue));

    rotate(const_view(_image), view(resultImage), angle);

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

    resample_pixels(source, dest, transformation, nearest_neighbor_sampler());
}

/**
 * \brief returns a 3x2 translation matrix based on mextension::image rotation
 * after an mextension::image is rotated it shifts outside of the canvas
 * we have to compute a translation matrix to move the mextension::image to fit the canvas
 */
template <typename SourceView>
boost::gil::matrix3x2<double> MPhoto::getTranslationMatrix(const SourceView& source, double angle)
{
    angle = mextension::numeric::mod(angle, 2*mextension::numeric::PI);

    std::pair<double, double> result = std::make_pair(0.0, 0.0);
    if (angle <= mextension::numeric::PI/2)
	result = std::make_pair(0.0, source.width()*std::sin(angle));
    else
    if (angle <= mextension::numeric::PI)
	result = std::make_pair(-std::cos(angle)*source.width(), std::sin(angle)*source.width() - std::cos(angle)*source.height());
    else
    if (angle <= 3*mextension::numeric::PI/2)
	result = std::make_pair(-std::cos(angle)*source.width() - std::sin(angle)*source.height(), -std::cos(angle)*source.height());
    else
    if (angle <= 2*mextension::numeric::PI)
	result = std::make_pair(-std::sin(angle)*source.height(), 0.0);

    return boost::gil::matrix3x2<double>(1.0, 0.0, 0.0, 1.0, -result.first, -result.second);
}

////////////////////////////////////////////////////////////////
// Resize
////////////////////////////////////////////////////////////////

/**
 * \brief mextension::image resize wrapper
 * resizes an mextension::image holding scale into maxSize x maxSize mextension::image
 * example: maxSize: 200, original mextension::image: 300x200, final mextension::image 200x(200*(200/300))
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
    _image = resultImage;
}

/**
 * \brief mextension::image resize wrapper
 * creates a canvas for mextension::image resize and calls proper handlers
 */
void MPhoto::resize(double width, double height)
{
    using namespace boost::gil;

    rgb8_image_t resultImage(rgb8_image_t::point_t(width, height));

    resize(const_view(_image), view(resultImage));
    _image = resultImage;
}

/**
 * \brief mextension::image resize handler
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

    contrast(const_view(_image), view(resultImage), value);

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
	    dest_it[x][0] = mextension::numeric::setRange((source_it[x][0] - 127.0)*value + 127.0, 0.0, 255.0);
	    dest_it[x][1] = mextension::numeric::setRange((source_it[x][1] - 127.0)*value + 127.0, 0.0, 255.0);
	    dest_it[x][2] = mextension::numeric::setRange((source_it[x][2] - 127.0)*value + 127.0, 0.0, 255.0);
	}

    }
}

////////////////////////////////////////////////////////////////
// Saving & Loading
////////////////////////////////////////////////////////////////

bool MPhoto::load(std::string path)
{
    using namespace boost::gil;

    jpeg_read_image(path, _image); // we read jpeg

    return true;
}


bool MPhoto::saveAs(std::string path, bool force)
{
    using namespace boost::gil;

    jpeg_write_view(path, view(_image));

    return true;
}

} // NAMESPACE core

