#ifndef MCOLOR_H
#define MCOLOR_H

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>

#define COLOR_UNDEFINED -1

namespace mimage
{

/**
 * \brief RGB structure
 * subtractive color structure
 */
struct RGB
{
    RGB()
    {
	red = 0;
	green = 0;
	blue = 0;
    }
    RGB(int r, int g, int b)
    {
	red = r;
	green = g;
	blue = b;
    }
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
    CMYK()
    {
	cyan = 0;
	magenta = 0;
	yellow = 0;
	black = 0;
    }

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

struct HSV
{
    HSV()
    {
	hue = 0;
	saturation = 0;
	value = 0;
    }

    HSV(int h, int s, int v)
    {
	hue = h;
	saturation = s;
	value = v;
    }

    HSV(const HSV& color)
    {
	hue = color.hue;
	saturation = color.saturation;
	value = color.value;
    }
    HSV& operator=(const HSV& color)
    {
	hue = color.hue;
	saturation = color.saturation;
	value = color.value;
	return *this;
    }

    double hue;
    double saturation;
    double value;
};

inline HSV RGBtoHSV(RGB color)
{
    double min, max, d;
    HSV result;

    min = std::min(static_cast<double>(color.red), static_cast<double>(color.green));
    min = std::min(min, static_cast<double>(color.blue));

    max = std::max(static_cast<double>(color.red), static_cast<double>(color.green));
    max = std::max(max, static_cast<double>(color.blue));

    result.value = max;
    result.saturation = (max-min)/max;

    if (result.saturation == 0.0)
	result.hue = COLOR_UNDEFINED;
    else
    {
	d = max - min;
	if (max == color.red)
	{
	    result.hue = static_cast<double>(color.green - color.blue) / d;
	}
	else
	if (max == color.green)
	{
	    result.hue = 2.0 + (static_cast<double>(color.blue - color.red) / d);
	}
	else
	if (max == color.blue)
	{
	    result.hue = 4.0 + (static_cast<double>(color.red - color.green) / d);
	}
	result.hue *= 60.0;
	if (result.hue < 0)
	    result.hue += 360.0;
    }
    return result;
}

inline RGB HSVtoRGB(HSV color)
{
    int sextant;
    double fract, p, q, t;

    if (color.saturation == 0.0)
    {
	return RGB(static_cast<int>(color.value), static_cast<int>(color.value), static_cast<int>(color.value));
    }
    else
    {
	if (color.hue == 360)
	    color.hue = 0;
	else
	    color.hue /= 60;

	sextant = static_cast<int>(std::floor(color.hue));
	fract = color.hue - static_cast<double>(sextant);

	p = color.value*(1- color.saturation);
	q = color.value*(1-(color.saturation*fract));
	t = color.value*(1-(color.saturation*(1-fract)));

	int val = static_cast<int>(color.value);
	int pt = static_cast<int>(p);
	int tt = static_cast<int>(t);
	int qt = static_cast<int>(q);

	switch (sextant)
	{
	    case 0:
		return RGB(val, tt, pt);
	    case 1:
		return RGB(qt, val, pt);
	    case 2:
		return RGB(pt, val, tt);
	    case 3:
		return RGB(pt, qt, val);
	    case 4:
		return RGB(tt, pt, val);
	    case 5:
		return RGB(val, pt, qt);
	}
    }
    // ERROR
    return RGB(COLOR_UNDEFINED, COLOR_UNDEFINED, COLOR_UNDEFINED);
}


inline double getLuminance(RGB color)
{
    return  0.2126*static_cast<double>(color.red) +
	    0.7152*static_cast<double>(color.green) +
	    0.0722*static_cast<double>(color.blue);
}


/**
 * \brief chroma
 * colorfulness relative to the brightness of another color that appears white under similar viewing conditions
 */
inline int getChroma(RGB color)
{
    int max = std::max(color.red, color.green);
    max = std::max(max, color.blue);

    int min = std::min(color.red, color.green);
    min = std::min(min, color.blue);

    return max - min;
}

inline double getHSVSaturation(RGB color)
{
    int max = std::max(color.red, color.green);
    max = std::max(max, color.blue);

    return static_cast<double>(getChroma(color)) / static_cast<double>(max);
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
inline ColorHistogram getHistogram(const SourceView& source)
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

} // NAMESPACE mimage

#endif // MCOLOR_H
