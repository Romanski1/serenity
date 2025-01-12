#include <AK/AKString.h>
#include <AK/StringView.h>

namespace AK {

StringView::StringView(const String& string)
    : m_impl(string.impl())
    , m_characters(string.characters())
    , m_length(string.length())
{
}

Vector<StringView> StringView::split_view(const char separator) const
{
    if (is_empty())
        return {};

    Vector<StringView> v;
    ssize_t substart = 0;
    for (ssize_t i = 0; i < length(); ++i) {
        char ch = characters()[i];
        if (ch == separator) {
            ssize_t sublen = i - substart;
            if (sublen != 0)
                v.append(substring_view(substart, sublen));
            substart = i + 1;
        }
    }
    ssize_t taillen = length() - substart;
    if (taillen != 0)
        v.append(substring_view(substart, taillen));
    if (characters()[length() - 1] == separator)
        v.append(String::empty());
    return v;
}

StringView StringView::substring_view(int start, int length) const
{
    if (!length)
        return {};
    ASSERT(start + length <= m_length);
    return { m_characters + start, length };
}

StringView StringView::substring_view_starting_from_substring(const StringView& substring) const
{
    const char* remaining_characters = substring.characters();
    ASSERT(remaining_characters >= m_characters);
    ASSERT(remaining_characters <= m_characters + m_length);
    int remaining_length = m_length - (remaining_characters - m_characters);
    return { remaining_characters, remaining_length };
}

StringView StringView::substring_view_starting_after_substring(const StringView& substring) const
{
    const char* remaining_characters = substring.characters() + substring.length();
    ASSERT(remaining_characters >= m_characters);
    ASSERT(remaining_characters <= m_characters + m_length);
    int remaining_length = m_length - (remaining_characters - m_characters);
    return { remaining_characters, remaining_length };
}

unsigned StringView::to_uint(bool& ok) const
{
    unsigned value = 0;
    for (ssize_t i = 0; i < length(); ++i) {
        if (characters()[i] < '0' || characters()[i] > '9') {
            ok = false;
            return 0;
        }
        value = value * 10;
        value += characters()[i] - '0';
    }
    ok = true;
    return value;
}

}
