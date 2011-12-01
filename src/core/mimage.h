#ifndef MCOLOR_H
#define MCOLOR_H

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>

namespace mextension
{
namespace image
{

/**
 * \brief RGB structure
 * subtractive color structure
 */
struct RGB
{
    RGB(int r, int g, int b)
    {
	red = r;
	green = g;
	blue = b;
    };
    RGB(const RGB& color)
    {
	red = color.red;
	green = color.green;
	blue = color.blue;
    }
    RGB& operator=(const RGB& color)
    {
	red = color.red;
	green = color.green;
	blue = color.blue;
	return *this;
    }

    int red;
    int green;
    int blue;
};

/**
 * \brief CMYK structure
 * additive color structure
 */
struct CMYK
{
    CMYK(int c, int m, int y, int k)
    {
	cyan = c;
	magenta = m;
	yellow = y;
	black = k;
    };
    CMYK(const CMYK& color)
    {
	cyan = color.cyan;
	magenta = color.magenta;
	yellow = color.yellow;
	black = color.black;
    }
    CMYK& operator=(const CMYK& color)
    {
	cyan = color.cyan;
	magenta = color.magenta;
	yellow = color.yellow;
	black = color.black;
	return *this;
    }

    int cyan;
    int magenta;
    int yellow;
    int black;
};

inline double getLuminance(image::RGB color)
{
    return  0.2126*static_cast<double>(color.red) +
	    0.7152*static_cast<double>(color.green) +
	    0.0722*static_cast<double>(color.blue);
}

inline RGB normalizeRGB(RGB color)
{
    double coef;
    if (color.red > 255)
    {
	coef = static_cast<double>(color.red) / 255.0;
	color.red = 255.0;
	color.green /= coef;
	color.blue /= coef;
    }
    if (color.green > 255)
    {
	coef = static_cast<double>(color.green) / 255.0;
	color.red /= coef;
	color.green /= 255.0;
	color.blue /= coef;
    }
    if (color.blue > 255)
    {
	coef = static_cast<double>(color.blue) / 255.0;
	color.red /= coef;
	color.green /= coef;
	color.blue = 255.0;
    }
    return color;
}

class ColorHistogram
{
    public:
	ColorHistogram()
	{
	    for (int i = 0; i < 255; ++i)
	    {
		red[i] = 0;
		green[i] = 0;
		blue[i] = 0;
	    }
	}

	void incRed(int i){ ++red[i]; }
	void incGreen(int i){ ++green[i]; }
	void incBlue(int i){ ++blue[i]; }

	double calcRedMean()
	{
	    double result = 0.0;
	    for (int i = 0; i < 255; ++i)
		result += (i+1)*red[i];

	    return (result / 255.0)-1;
	}
	double calcGreenMean()
	{
	    double result = 0.0;
	    for (int i = 0; i < 255; ++i)
		result += (i+1)*green[i];

	    return (result / 255.0)-1;
	}
	double calcBlueMean()
	{
	    double result = 0.0;
	    for (int i = 0; i < 255; ++i)
		result += (i+1)*blue[i];

	    return (result / 255.0)-1;
	}

    private:
	int red[255];
	int green[255];
	int blue[255];
};

template <typename SourceView>
inline ColorHistogram genHistogram(const SourceView& source)
{
    ColorHistogram histogram();
    for (int y = 0; y < source.height(); ++y)
    {
	typename SourceView::x_iterator source_it = source.row_begin(y);
	for (int x = 0; x < source.width(); ++x)
	{
	    BOOST_ASSERT_MSG(source_it[x][0] <= 255 && source_it[x][0] >= 0, "Red is out of bounds.");
	    BOOST_ASSERT_MSG(source_it[x][1] <= 255 && source_it[x][0] >= 0, "Green is out of bounds.");
	    BOOST_ASSERT_MSG(source_it[x][2] <= 255 && source_it[x][0] >= 0, "Blue is out of bounds.");

	    histogram.incRed(source_it[x][0]);
	    histogram.incGreen(source_it[x][1]);
	    histogram.incBlue(source_it[x][2]);
	}
    }
    return histogram;
}

} // NAMESPACE image
} // NAMESPACE extension

#endif // MCOLOR_H
