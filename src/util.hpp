#ifndef UTIL_HPP
#define UTIL_HPP

#include <iomanip>
#include <sstream>

inline std::string to_string(const long double &_Val, const streamsize& precision)
{	// convert long double to string

    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << _Val;
    return out.str();
}

inline std::string to_string(const std::tm& tm, const char* format="%4d-%02d-%02d")
{
    std::tm _default = std::tm();
    if(difftime(mktime((std::tm*)&tm), mktime(&_default)) == 0)
        return "";

    char buffer[100];
    sprintf(buffer, format, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);

    return buffer;
}

inline std::tm strtotm(const std::string& str, string format="%Y-%m-%d")
{
    struct std::tm tm = {0};
    if(strptime(str.c_str(), format.c_str(), &tm) == NULL)
        tm = {0};
    return tm;
}

#if _MSC_VER || __MINGW32__
#	define makedir(x) mkdir(x)
#else
#	define makedir(x) mkdir(x, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

#endif // UTIL_HPP
