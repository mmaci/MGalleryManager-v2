#ifndef MNUMERIC_H
#define MNUMERIC_H

namespace mnumeric
{

const double PI = 4.0*atan(1.0);

template <typename Num>
Num mod(Num num, Num modulo)
{
    int tmp = num / modulo;
    return num - static_cast<Num>(tmp * modulo);
}

template <typename Num, typename PctNum>
Num addPct(Num num, PctNum pct)
{
    return num + num * static_cast<Num>(pct / 100.0);
}

template <typename Num>
Num setRange(Num number, Num from, Num to)
{
    if (number > to)
	number = to;
    else
    if (number < from)
	number = from;

    return number;
}

} // NAMESPACE mnumeric

#endif // MNUMERIC_H
