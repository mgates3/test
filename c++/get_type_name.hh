// -----------------------------------------------------------------------------
// see https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
#include <type_traits>
#include <typeinfo>
#include <memory>
#include <string>
#include <cstdlib>

// for demangling on non-Microsoft platforms
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif

template <typename T>
std::string get_type_name()
{
    using TR = typename std::remove_reference<T>::type;

    std::unique_ptr< char, void(*)(void*) > own(
        #ifndef _MSC_VER
            abi::__cxa_demangle( typeid(TR).name(), nullptr, nullptr, nullptr ),
        #else
            nullptr,
        #endif
        std::free
    );

    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}
