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

// Alignment masks
template <int Alignment> struct AlignmentMask; // Unsupported alignment
template <> struct AlignmentMask<2>    {enum { Mask = 0x001 };};
template <> struct AlignmentMask<4>    {enum { Mask = 0x003 };};
template <> struct AlignmentMask<8>    {enum { Mask = 0x007 };};
template <> struct AlignmentMask<16>   {enum { Mask = 0x00f };};
template <> struct AlignmentMask<32>   {enum { Mask = 0x01f };};
template <> struct AlignmentMask<64>   {enum { Mask = 0x03f };};
template <> struct AlignmentMask<128>  {enum { Mask = 0x07f };};
template <> struct AlignmentMask<256>  {enum { Mask = 0x0ff };};
template <> struct AlignmentMask<512>  {enum { Mask = 0x1ff };};
template <> struct AlignmentMask<1024> {enum { Mask = 0x3ff };};
template <> struct AlignmentMask<2048> {enum { Mask = 0x7ff };};
template <> struct AlignmentMask<4096> {enum { Mask = 0xfff };};

#endif // TEMPLATETOOLS_H
