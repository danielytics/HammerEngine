#ifndef TEMPLATETOOLS_H
#define TEMPLATETOOLS_H

// Compile-time if-statement
template <bool Condition, class Then, class Else> struct static_if
{
    typedef Then Type;
};
template <class Then, class Else> struct static_if<false, Then, Else>
{
    typedef Else Type;
};

// Type wrapper for numeric values
template <int Number> struct value_type
{
    enum { Value = Number };
};

#define CONCAT_X_Y(x,y) x##y

// Generate a compile error
template <typename TMPL, typename MSG> struct invalid_template_type;
#define invalid_template(tmpl, message) invalid_template_type<tmpl, struct CONCAT_X_Y(ERROR___,message)>
template<int,typename MSG> struct compile_error_type { enum { Value=0}; typedef void Type;};
template<typename MSG> struct compile_error_type <true,MSG> : invalid_template_type<MSG,MSG> { enum { Value=0}; typedef void Type;};
#define compile_error(condition,message) compile_error_type<(condition), struct CONCAT_X_Y(ERROR___,message)>

#endif // TEMPLATETOOLS_H
