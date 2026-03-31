// Q7.cpp

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif


#include "Q7.h"

// Character classification

// Check if character is a letter
bool is_alpha(wchar_t c) {
    return (c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z');
}

// Check if character is a digit
bool is_digit(wchar_t c) {
    return c >= L'0' && c <= L'9';
}

// Check if character is whitespace
bool is_space(wchar_t c) {
    return c == L' ' || c == L'\t' || c == L'\n' || c == L'\r';
}

// Check if character is uppercase
bool is_upper(wchar_t c) {
    return c >= L'A' && c <= L'Z';
}

// Check if character is lowercase
bool is_lower(wchar_t c) {
    return c >= L'a' && c <= L'z';
}

// Check if character is punctuation
bool is_punctuation(wchar_t c) {
    // common punctuation marks used in manuscripts
    return c == L'.' || c == L',' || c == L';' || c == L':'
        || c == L'!' || c == L'?' || c == L'\'' || c == L'"'
        || c == L'-' || c == L'(' || c == L')' || c == L'['
        || c == L']' || c == L'{' || c == L'}';
}

// Check if character ends a sentence
bool is_sentence_end(wchar_t c) {
    return c == L'.' || c == L'?' || c == L'!';
}

// Character conversion

// Convert character to lowercase
wchar_t to_lower(wchar_t c) {
    if (c >= L'A' && c <= L'Z') return c + (L'a' - L'A');
    return c;
}

// Convert character to uppercase
wchar_t to_upper(wchar_t c) {
    if (c >= L'a' && c <= L'z') return c - (L'a' - L'A');
    return c;
}

// Wide string functions

// Get length of wide string
int str_len(const wchar_t* s) {
    if (!s) return 0;
    int len = 0;
    while (s[len] != L'\0') {
        len++;
    }
    return len;
}

// Copy source string to destination
void str_cpy(wchar_t* dest, const wchar_t* src) {
    if (!dest || !src) return;
    int i = 0;
    while (src[i] != L'\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = L'\0';
}

// Copy up to n characters from source to destination
void str_ncpy(wchar_t* dest, const wchar_t* src, int n) {
    if (!dest || !src || n <= 0) return;
    int i = 0;
    while (i < n - 1 && src[i] != L'\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = L'\0';
}

// Append source string to destination
void str_cat(wchar_t* dest, const wchar_t* src) {
    if (!dest || !src) return;
    int dest_len = str_len(dest);
    int i = 0;
    while (src[i] != L'\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = L'\0';
}

// Compare two strings, returns 0 if equal
int str_cmp(const wchar_t* a, const wchar_t* b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    int i = 0;
    while (a[i] != L'\0' && b[i] != L'\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == L'\0' && b[i] == L'\0') return 0;
    if (a[i] == L'\0') return -1;
    return 1;
}

// Compare two strings ignoring case
int str_cmp_i(const wchar_t* a, const wchar_t* b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    int i = 0;
    while (a[i] != L'\0' && b[i] != L'\0') {
        wchar_t la = to_lower(a[i]);
        wchar_t lb = to_lower(b[i]);
        if (la < lb) return -1;
        if (la > lb) return 1;
        i++;
    }
    if (a[i] == L'\0' && b[i] == L'\0') return 0;
    if (a[i] == L'\0') return -1;
    return 1;
}

// Compare first n characters
int str_ncmp(const wchar_t* a, const wchar_t* b, int n) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    for (int i = 0; i < n; i++) {
        if (a[i] == L'\0' && b[i] == L'\0') return 0;
        if (a[i] == L'\0') return -1;
        if (b[i] == L'\0') return 1;
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
    }
    return 0;
}

// Compare first n characters ignoring case
int str_ncmp_i(const wchar_t* a, const wchar_t* b, int n) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    for (int i = 0; i < n; i++) {
        if (a[i] == L'\0' && b[i] == L'\0') return 0;
        if (a[i] == L'\0') return -1;
        if (b[i] == L'\0') return 1;
        wchar_t la = to_lower(a[i]);
        wchar_t lb = to_lower(b[i]);
        if (la < lb) return -1;
        if (la > lb) return 1;
    }
    return 0;
}

// find needle in haystack, return starting index or -1
// Find needle in haystack, returns index or -1
int str_find(const wchar_t* haystack, const wchar_t* needle) {
    if (!haystack || !needle) return -1;
    int h_len = str_len(haystack);
    int n_len = str_len(needle);
    if (n_len == 0) return 0;
    if (n_len > h_len) return -1;

    for (int i = 0; i <= h_len - n_len; i++) {
        bool match = true;
        for (int j = 0; j < n_len; j++) {
            if (haystack[i + j] != needle[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

// case-insensitive version
// Find needle in haystack ignoring case
int str_find_i(const wchar_t* haystack, const wchar_t* needle) {
    if (!haystack || !needle) return -1;
    int h_len = str_len(haystack);
    int n_len = str_len(needle);
    if (n_len == 0) return 0;
    if (n_len > h_len) return -1;

    for (int i = 0; i <= h_len - n_len; i++) {
        bool match = true;
        for (int j = 0; j < n_len; j++) {
            if (to_lower(haystack[i + j]) != to_lower(needle[j])) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

// Narrow (char) string helpers -- used for file path handling
// and reading the dictionary CSV

// Get length of narrow string
int str_len_a(const char* s) {
    if (!s) return 0;
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// Copy narrow string
void str_cpy_a(char* dest, const char* src) {
    if (!dest || !src) return;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Compare narrow strings
int str_cmp_a(const char* a, const char* b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
}

// Compare narrow strings ignoring case
int str_cmp_ia(const char* a, const char* b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        char la = (a[i] >= 'A' && a[i] <= 'Z') ? a[i] + 32 : a[i];
        char lb = (b[i] >= 'A' && b[i] <= 'Z') ? b[i] + 32 : b[i];
        if (la < lb) return -1;
        if (la > lb) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
}

// convert a narrow ASCII string to a wide string
// Convert narrow string to wide string
void narrow_to_wide(const char* src, wchar_t* dest, int max_len) {
    if (!src || !dest) return;
    int i = 0;
    while (src[i] != '\0' && i < max_len - 1) {
        dest[i] = (wchar_t)src[i];
        i++;
    }
    dest[i] = L'\0';
}

// convert a wide string back to narrow (ASCII only)
// Convert wide string to narrow string
void wide_to_narrow(const wchar_t* src, char* dest, int max_len) {
    if (!src || !dest) return;
    int i = 0;
    while (src[i] != L'\0' && i < max_len - 1) {
        dest[i] = (char)src[i];
        i++;
    }
    dest[i] = '\0';
}

// Numeric conversions

// Convert string to integer
int str_to_int(const wchar_t* s) {
    if (!s) return 0;
    int result = 0;
    int sign = 1;
    int i = 0;

    // skip leading spaces
    while (s[i] == L' ') i++;

    // handle optional sign
    if (s[i] == L'-') {
        sign = -1;
        i++;
    }
    else if (s[i] == L'+') {
        i++;
    }

    // convert digits
    while (s[i] >= L'0' && s[i] <= L'9') {
        result = result * 10 + (s[i] - L'0');
        i++;
    }

    return result * sign;
}

// Convert integer to string
void int_to_str(int value, wchar_t* buffer) {
    if (!buffer) return;

    // handle zero
    if (value == 0) {
        buffer[0] = L'0';
        buffer[1] = L'\0';
        return;
    }

    // handle negative
    bool negative = false;
    if (value < 0) {
        if (value == -2147483647 - 1) {  // INT_MIN: can't negate safely
            str_cpy(buffer, L"-2147483648");
            return;
        }
        negative = true;
        value = -value;
    }

    // write digits in reverse
    wchar_t temp[32];
    int i = 0;
    while (value > 0) {
        temp[i++] = L'0' + (value % 10);
        value /= 10;
    }

    // copy to buffer in correct order
    int pos = 0;
    if (negative) {
        buffer[pos++] = L'-';
    }
    for (int j = i - 1; j >= 0; j--) {
        buffer[pos++] = temp[j];
    }
    buffer[pos] = L'\0';
}

// Memory helpers

// Set memory block to specified value
void mem_set(void* dest, unsigned char value, int byte_count) {
    unsigned char* p = (unsigned char*)dest;
    for (int i = 0; i < byte_count; i++) {
        p[i] = value;
    }
}

// Copy memory from source to destination
void mem_cpy(void* dest, const void* src, int byte_count) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (int i = 0; i < byte_count; i++) {
        d[i] = s[i];
    }
}

// Stop word detection (for ToC fallback)

// Check if word is a common stop word
bool is_stop_word(const wchar_t* word) {
    // common stop words that get dropped from fallback titles
    const wchar_t* stop_words[] = {
        L"was", L"is", L"and", L"or", L"the",
        L"a", L"an", L"in", L"of", L"to"
    };
    int num_stops = 10;

    for (int i = 0; i < num_stops; i++) {
        if (str_cmp_i(word, stop_words[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Line implementation

// Constructor
Line::Line() : m_text(nullptr), m_length(0), m_max_chars(0), m_raw_offset(0) {}

// Constructor
Line::Line(int max_chars) : m_text(nullptr), m_length(0), m_max_chars(0), m_raw_offset(0) {
    init(max_chars);
}

// Destructor
Line::~Line() {
    delete[] m_text;
}

// Copy constructor
Line::Line(const Line& other) : m_text(nullptr), m_length(0), m_max_chars(0), m_raw_offset(0) {
    if (other.m_max_chars > 0) {
        m_max_chars = other.m_max_chars;
        m_length = other.m_length;
        m_raw_offset = other.m_raw_offset;
        m_text = new wchar_t[m_max_chars + 1];
        for (int i = 0; i < m_length; i++) {
            m_text[i] = other.m_text[i];
        }
        m_text[m_length] = L'\0';
    }
}

// Assignment operator
Line& Line::operator=(const Line& other) {
    if (this != &other) {
        delete[] m_text;
        m_text = nullptr;
        m_length = 0;
        m_max_chars = 0;
        m_raw_offset = 0;

        if (other.m_max_chars > 0) {
            m_max_chars = other.m_max_chars;
            m_length = other.m_length;
            m_raw_offset = other.m_raw_offset;
            m_text = new wchar_t[m_max_chars + 1];
            for (int i = 0; i < m_length; i++) {
                m_text[i] = other.m_text[i];
            }
            m_text[m_length] = L'\0';
        }
    }
    return *this;
}

// Initialize line with specified capacity
void Line::init(int max_chars) {
    delete[] m_text;
    m_max_chars = max_chars;
    m_length = 0;
    m_raw_offset = 0;
    m_text = new wchar_t[m_max_chars + 1];
    m_text[0] = L'\0';
}

// Set the text content of this line
void Line::set_text(const wchar_t* text, int len) {
    if (!m_text) return;
    // clamp length to what we can hold
    if (len > m_max_chars) len = m_max_chars;
    for (int i = 0; i < len; i++) {
        m_text[i] = text[i];
    }
    m_text[len] = L'\0';
    m_length = len;
}

// Clear all text from this line
void Line::clear() {
    if (m_text) {
        m_text[0] = L'\0';
        m_length = 0;
    }
    m_raw_offset = 0;
}

// Get pointer to text buffer
const wchar_t* Line::get_text() const { return m_text ? m_text : L""; }
// Get current text length
int Line::get_length() const { return m_length; }
// Get maximum capacity
int Line::get_max_chars() const { return m_max_chars; }

wchar_t Line::get_char(int index) const {
    if (!m_text || index < 0 || index >= m_length) return L'\0';
    return m_text[index];
}

// Set position in original raw text
void Line::set_raw_offset(int offset) { m_raw_offset = offset; }
// Get position in original raw text
int Line::get_raw_offset() const { return m_raw_offset; }

// Column implementation

// Constructor
Column::Column() : m_max_lines(0), m_chars_per_line(0) {}

// Constructor
Column::Column(int max_lines, int chars_per_line)
    : m_max_lines(0), m_chars_per_line(0) {
    init(max_lines, chars_per_line);
}

// Destructor
Column::~Column() {}

// Initialize column with specified dimensions
void Column::init(int max_lines, int chars_per_line) {
    m_max_lines = max_lines;
    m_chars_per_line = chars_per_line;
    m_lines.clear();
}

// Clear all lines from column
void Column::clear() {
    m_lines.clear();
}

// Check if column has reached max lines
bool Column::is_full() const {
    return m_lines.size() >= m_max_lines;
}

// Get number of lines currently used
int Column::get_used_lines() const {
    return m_lines.size();
}

// Get maximum lines capacity
int Column::get_max_lines() const {
    return m_max_lines;
}

// Get reference to line at index
Line& Column::get_line(int index) {
    return m_lines[index];
}

// Get const reference to line at index
const Line& Column::get_line(int index) const {
    return m_lines[index];
}

// Add a new line to column, returns false if full
bool Column::add_line(const wchar_t* text, int len, int raw_offset) {
    if (is_full()) return false;

    Line new_line(m_chars_per_line);
    new_line.set_text(text, len);
    new_line.set_raw_offset(raw_offset);
    m_lines.push_back(new_line);
    return true;
}

// Page implementation

// Constructor
Page::Page() : m_num_columns(0) {}

// Constructor
Page::Page(int num_columns, int lines_per_col, int chars_per_line)
    : m_num_columns(0) {
    init(num_columns, lines_per_col, chars_per_line);
}

// Destructor
Page::~Page() {}

// Initialize page with specified layout
void Page::init(int num_columns, int lines_per_col, int chars_per_line) {
    m_num_columns = num_columns;
    m_columns.clear();
    for (int i = 0; i < num_columns; i++) {
        Column col(lines_per_col, chars_per_line);
        m_columns.push_back(col);
    }
}

// Clear all columns
void Page::clear() {
    for (int i = 0; i < m_columns.size(); i++) {
        m_columns[i].clear();
    }
}

// Get number of columns
int Page::get_num_columns() const { return m_num_columns; }

// Get reference to column at index
Column& Page::get_column(int index) { return m_columns[index]; }
// Get const reference to column
const Column& Page::get_column(int index) const { return m_columns[index]; }

// Check if all columns are full
bool Page::is_full() const {
    for (int i = 0; i < m_columns.size(); i++) {
        if (!m_columns[i].is_full()) return false;
    }
    return true;
}

// Document -- static members

int Document::s_instance_count = 0;
Document* Document::s_instances[10] = {
    nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr
};

// Document implementation

Document::Document()
    : m_raw_text(nullptr)
    , m_raw_len(0)
    , m_raw_capacity(0)
    , m_cols_per_page(2)
    , m_lines_per_col(20)
    , m_chars_per_line(40)
    , m_alignment(ALIGN_LEFT)
    , m_is_modified(false)
    , m_tab_index(-1)
    , m_delta_sequence(0) {
    m_file_path[0] = L'\0';
    m_title[0] = L'\0';

    // start with a reasonable buffer
    m_raw_capacity = 4096;
    m_raw_text = new wchar_t[m_raw_capacity];
    m_raw_text[0] = L'\0';
}

// Destructor
Document::~Document() {
    delete[] m_raw_text;

    // remove from the static instance list
    if (m_tab_index >= 0 && m_tab_index < 10) {
        s_instances[m_tab_index] = nullptr;
        s_instance_count--;
    }
}

// Create new document instance in static slot
Document* Document::create(int cols_per_page, int lines_per_col, int chars_per_line) {
    // hard limit: no more than 10 documents
    if (s_instance_count >= 10) {
        return nullptr;
    }

    // find an empty slot
    int slot = -1;
    for (int i = 0; i < 10; i++) {
        if (s_instances[i] == nullptr) {
            slot = i;
            break;
        }
    }
    if (slot < 0) return nullptr;

    Document* doc = new Document();
    doc->set_layout(cols_per_page, lines_per_col, chars_per_line);
    doc->m_tab_index = slot;

    // build a default title like "Untitled 1"
    wchar_t num_buf[8];
    int_to_str(slot + 1, num_buf);
    str_cpy(doc->m_title, L"Untitled ");
    str_cat(doc->m_title, num_buf);

    s_instances[slot] = doc;
    s_instance_count++;

    return doc;
}

void Document::close(Document* doc) {
    if (!doc) return;
    delete doc;  // destructor handles the instance tracking
}

// Get document instance from slot
Document* Document::get_instance(int index) {
    if (index < 0 || index >= 10) return nullptr;
    return s_instances[index];
}

// Get number of active documents
int Document::get_instance_count() {
    return s_instance_count;
}

// Configuration

void Document::set_layout(int cols_per_page, int lines_per_col, int chars_per_line) {
    m_cols_per_page = cols_per_page;
    m_lines_per_col = lines_per_col;
    m_chars_per_line = chars_per_line;
    reflow();  // re-layout after config change
    set_cursor_from_offset(get_cursor_offset());  // revalidate cursor
}

// Get columns per page setting
int Document::get_cols_per_page() const { return m_cols_per_page; }
// Get lines per column setting
int Document::get_lines_per_col() const { return m_lines_per_col; }
// Get characters per line setting
int Document::get_chars_per_line() const { return m_chars_per_line; }

// Buffer management

void Document::grow_buffer(int needed) {
    if (needed <= m_raw_capacity) return;
    int new_cap = m_raw_capacity;
    // Double capacity until it fits
    while (new_cap < needed) {
        new_cap *= 2;
    }
    wchar_t* new_buf = new wchar_t[new_cap];
    for (int i = 0; i < m_raw_len; i++) {
        new_buf[i] = m_raw_text[i];
    }
    new_buf[m_raw_len] = L'\0';
    delete[] m_raw_text;
    m_raw_text = new_buf;
    m_raw_capacity = new_cap;
}

// record_delta -- append an edit delta to the log.
// Large edits are split into 512-char chunks.

void Document::record_delta(EditDelta::DeltaType type, int offset,
    const wchar_t* text, int len) {
    int pos = 0;
    while (pos < len) {
        EditDelta d;
        d.type = type;
        d.offset = offset + pos;
        d.text_len = len - pos;
        if (d.text_len > 511) d.text_len = 511;  // leave room for null
        for (int i = 0; i < d.text_len; i++) {
            d.text[i] = text[pos + i];
        }
        d.text[d.text_len] = L'\0';
        m_deltas.push_back(d);
        m_delta_sequence++;
        pos += d.text_len;
    }
}

// Text operations

// Insert character at cursor position
void Document::insert_char(wchar_t c) {
    // if there is a selection, delete it first
    if (m_selection.active) {
        delete_selection();
    }

    int offset = get_cursor_offset();
    grow_buffer(m_raw_len + 2);

    // shift text to the right to make room
    for (int i = m_raw_len; i > offset; i--) {
        m_raw_text[i] = m_raw_text[i - 1];
    }
    m_raw_text[offset] = c;
    m_raw_len++;
    m_raw_text[m_raw_len] = L'\0';

    // record delta for auto-save
    record_delta(EditDelta::DELTA_INSERT, offset, &c, 1);

    m_is_modified = true;

    // reflow and advance cursor past the inserted character
    reflow();
    set_cursor_from_offset(offset + 1);
}

void Document::insert_text(const wchar_t* text, int len) {
    if (!text || len <= 0) return;

    if (m_selection.active) {
        delete_selection();
    }

    int offset = get_cursor_offset();
    grow_buffer(m_raw_len + len + 1);

    // shift existing text right
    for (int i = m_raw_len; i > offset; i--) {
        m_raw_text[i + len - 1] = m_raw_text[i - 1];
    }

    // copy new text in
    for (int i = 0; i < len; i++) {
        m_raw_text[offset + i] = text[i];
    }
    m_raw_len += len;
    m_raw_text[m_raw_len] = L'\0';

    // record delta for auto-save
    record_delta(EditDelta::DELTA_INSERT, offset, text, len);

    m_is_modified = true;
    reflow();
    set_cursor_from_offset(offset + len);
}

void Document::delete_char_before() {
    if (m_selection.active) {
        delete_selection();
        return;
    }

    int offset = get_cursor_offset();
    if (offset <= 0) return;

    // capture the deleted character for delta tracking
    wchar_t deleted = m_raw_text[offset - 1];

    // shift text left by one
    for (int i = offset - 1; i < m_raw_len - 1; i++) {
        m_raw_text[i] = m_raw_text[i + 1];
    }
    m_raw_len--;
    m_raw_text[m_raw_len] = L'\0';

    // record delta for auto-save
    record_delta(EditDelta::DELTA_DELETE, offset - 1, &deleted, 1);

    m_is_modified = true;
    reflow();
    set_cursor_from_offset(offset - 1);
}

void Document::delete_char_at() {
    if (m_selection.active) {
        delete_selection();
        return;
    }

    int offset = get_cursor_offset();
    if (offset >= m_raw_len) return;

    // capture the deleted character for delta tracking
    wchar_t deleted = m_raw_text[offset];

    // shift text left by one
    for (int i = offset; i < m_raw_len - 1; i++) {
        m_raw_text[i] = m_raw_text[i + 1];
    }
    m_raw_len--;
    m_raw_text[m_raw_len] = L'\0';

    // record delta for auto-save
    record_delta(EditDelta::DELTA_DELETE, offset, &deleted, 1);

    m_is_modified = true;
    reflow();
    set_cursor_from_offset(offset);
}

wchar_t* Document::get_selected_text() const {
    if (!m_selection.active) return nullptr;
    int s = m_selection.start;
    int e = m_selection.end;
    // normalize backwards selections
    if (s > e) { int tmp = s; s = e; e = tmp; }
    if (s >= e) return nullptr;
    int len = e - s;
    wchar_t* buf = new wchar_t[len + 1];
    for (int i = 0; i < len; i++) {
        buf[i] = m_raw_text[s + i];
    }
    buf[len] = L'\0';
    return buf;
}

// Delete selected text
void Document::delete_selection() {
    if (!m_selection.active) return;

    int start = m_selection.start;
    int end = m_selection.end;
    if (start > end) {
        // swap if backwards
        int tmp = start;
        start = end;
        end = tmp;
    }

    int del_len = end - start;
    if (del_len <= 0) {
        m_selection.clear();
        return;
    }

    // capture deleted text for delta tracking before overwriting
    record_delta(EditDelta::DELTA_DELETE, start, m_raw_text + start, del_len);

    // shift text left to fill the gap
    for (int i = start; i < m_raw_len - del_len; i++) {
        m_raw_text[i] = m_raw_text[i + del_len];
    }
    m_raw_len -= del_len;
    m_raw_text[m_raw_len] = L'\0';

    m_selection.clear();
    m_is_modified = true;
    reflow();
    set_cursor_from_offset(start);
}

// Get pointer to raw text buffer
const wchar_t* Document::get_raw_text() const { return m_raw_text; }
// Get length of raw text
int Document::get_raw_length() const { return m_raw_len; }

// Reflow -- the heart of the layout engine.
//
// Walks through raw text word by word, placing each word into
// the current line. If a word does not fit, it moves to the
// next line. If the column is full, it moves to the next
// column. If the page is full, a new page is created.
//
// Newlines create paragraph breaks (start a new line).
// Double newlines create blank lines.
// Words are never broken across lines.
//
// Each line stores its raw_offset so we can map cursor positions
// back to raw text offsets without guessing about separators.

void Document::reflow() {
    m_pages.clear();

    if (m_raw_len == 0) {
        // always have at least one page
        Page empty_page(m_cols_per_page, m_lines_per_col, m_chars_per_line);
        m_pages.push_back(empty_page);
        return;
    }

    // create the first page
    Page first_page(m_cols_per_page, m_lines_per_col, m_chars_per_line);
    m_pages.push_back(first_page);

    int cur_page = 0;
    int cur_col = 0;

    // buffer for the current line being built
    wchar_t* line_buf = new wchar_t[m_chars_per_line + 1];
    int line_len = 0;
    int line_raw_start = 0;  // raw text offset where this line begins
    line_buf[0] = L'\0';

    // helper lambda-style: commit the current line to the layout
    // (we use a local approach instead since we can't use lambdas easily)

    int i = 0;
    while (i < m_raw_len) {
        // handle newlines: they flush the current line and start a new one
        if (m_raw_text[i] == L'\n') {
            // commit whatever is on the current line
            if (!m_pages[cur_page].get_column(cur_col).add_line(line_buf, line_len, line_raw_start)) {
                // column full, try next column
                cur_col++;
                    // Move to next page if column limit reached
                if (cur_col >= m_cols_per_page) {
                    // page full, make a new page
                    Page new_page(m_cols_per_page, m_lines_per_col, m_chars_per_line);
                    m_pages.push_back(new_page);
                    cur_page++;
                    cur_col = 0;
                }
                m_pages[cur_page].get_column(cur_col).add_line(line_buf, line_len, line_raw_start);
            }
            line_len = 0;
            line_buf[0] = L'\0';
            i++;
            line_raw_start = i;  // next line starts after the newline
            continue;
        }

        // skip leading spaces at the start of a line
        if (line_len == 0 && m_raw_text[i] == L' ') {
            i++;
            line_raw_start = i;  // adjust: line actually starts after skipped spaces
            continue;
        }

        // extract the next word (sequence of non-space, non-newline chars)
        int word_start = i;
        while (i < m_raw_len && m_raw_text[i] != L' ' && m_raw_text[i] != L'\n') {
            i++;
        }
        int word_len = i - word_start;

        // will this word fit on the current line?
        int needed = line_len + (line_len > 0 ? 1 : 0) + word_len;

        if (needed <= m_chars_per_line) {
            // add a space separator if the line already has content
            if (line_len > 0) {
                line_buf[line_len] = L' ';
                line_len++;
            }
            // copy the word
            for (int j = 0; j < word_len; j++) {
                line_buf[line_len + j] = m_raw_text[word_start + j];
            }
            line_len += word_len;
            line_buf[line_len] = L'\0';
        }
        else {
            // word does not fit -- flush the current line first
            if (line_len > 0) {
                if (!m_pages[cur_page].get_column(cur_col).add_line(line_buf, line_len, line_raw_start)) {
                    cur_col++;
                    // Move to next page if column limit reached
                    if (cur_col >= m_cols_per_page) {
                        Page new_page(m_cols_per_page, m_lines_per_col, m_chars_per_line);
                        m_pages.push_back(new_page);
                        cur_page++;
                        cur_col = 0;
                    }
                    m_pages[cur_page].get_column(cur_col).add_line(line_buf, line_len, line_raw_start);
                }
            }

            // handle a word longer than the line width: split it forcibly
            if (word_len > m_chars_per_line) {
                int pos = 0;
                while (pos < word_len) {
                    int chunk = word_len - pos;
                    if (chunk > m_chars_per_line) chunk = m_chars_per_line;

                    int chunk_raw_start = word_start + pos;

                    // try to add this chunk as a line
                    wchar_t* chunk_buf = new wchar_t[chunk + 1];
                    for (int j = 0; j < chunk; j++) {
                        chunk_buf[j] = m_raw_text[word_start + pos + j];
                    }
                    chunk_buf[chunk] = L'\0';

                    if (!m_pages[cur_page].get_column(cur_col).add_line(chunk_buf, chunk, chunk_raw_start)) {
                        cur_col++;
                    // Move to next page if column limit reached
                        if (cur_col >= m_cols_per_page) {
                            Page new_page(m_cols_per_page, m_lines_per_col, m_chars_per_line);
                            m_pages.push_back(new_page);
                            cur_page++;
                            cur_col = 0;
                        }
                        m_pages[cur_page].get_column(cur_col).add_line(chunk_buf, chunk, chunk_raw_start);
                    }

                    delete[] chunk_buf;
                    pos += chunk;
                }
                line_len = 0;
                line_buf[0] = L'\0';
                // line_raw_start will be set below when we skip the separator
            }
            else {
                // start a new line with this word
                line_raw_start = word_start;
                for (int j = 0; j < word_len; j++) {
                    line_buf[j] = m_raw_text[word_start + j];
                }
                line_len = word_len;
                line_buf[line_len] = L'\0';
            }
        }

        // skip spaces after the word (the separator between words in raw text)
        // We skip ALL consecutive spaces here, not just one.
        if (i < m_raw_len && m_raw_text[i] == L' ') {
            // if the current line is empty (we just flushed a force-split word),
            // the next line_raw_start needs to be set after these spaces
            if (line_len == 0) {
                while (i < m_raw_len && m_raw_text[i] == L' ') {
                    i++;
                }
                line_raw_start = i;
            }
            else {
                // normal case: just skip one space as the word separator
                // (the space between this word and the next on the same line
                //  will be handled by the synthetic space in line_buf)
                i++;
            }
        }
    }

    // flush any remaining text on the last line
    if (line_len > 0) {
        if (!m_pages[cur_page].get_column(cur_col).add_line(line_buf, line_len, line_raw_start)) {
            cur_col++;
                    // Move to next page if column limit reached
            if (cur_col >= m_cols_per_page) {
                Page new_page(m_cols_per_page, m_lines_per_col, m_chars_per_line);
                m_pages.push_back(new_page);
                cur_page++;
                cur_col = 0;
            }
            m_pages[cur_page].get_column(cur_col).add_line(line_buf, line_len, line_raw_start);
        }
    }

    delete[] line_buf;
}

// Page access

// Get total number of pages
int Document::get_page_count() const { return m_pages.size(); }

// Get const reference to page
const Page& Document::get_page(int index) const { return m_pages[index]; }
// Get reference to page at index
Page& Document::get_page(int index) { return m_pages[index]; }

// Cursor-to-offset and offset-to-cursor mapping.
//
// We walk the pages/columns/lines to count characters and
// figure out the raw buffer offset that corresponds to a
// screen position, and vice versa.

int Document::cursor_to_offset(const CursorPosition& pos) const {
    for (int p = 0; p < m_pages.size(); p++) {
        const Page& page = m_pages[p];
        for (int c = 0; c < page.get_num_columns(); c++) {
            const Column& col = page.get_column(c);
            for (int l = 0; l < col.get_used_lines(); l++) {
                if (p == pos.page && c == pos.column && l == pos.line) {
                    const Line& line = col.get_line(l);
                    int char_pos = pos.offset;
                    if (char_pos > line.get_length()) {
                        char_pos = line.get_length();
                    }
                    return line.get_raw_offset() + char_pos;
                }
            }
        }
    }

    // fallback: end of text
    return m_raw_len;
}

void Document::offset_to_cursor(int offset, CursorPosition& out) const {
    // Walk all lines and find which one contains this raw offset.
    // Each line knows its raw_offset and length, so a line covers
    // raw positions [raw_offset, raw_offset + length).
    // We allow offset == raw_offset + length to place the cursor
    // at the end of a line.

    // We need to find the best match: the line whose range includes
    // the offset. If offset falls between lines (e.g. on a separator
    // character), we place the cursor at the start of the next line.

    // first pass: find exact match
    for (int p = 0; p < m_pages.size(); p++) {
        const Page& page = m_pages[p];
        for (int c = 0; c < page.get_num_columns(); c++) {
            const Column& col = page.get_column(c);
            for (int l = 0; l < col.get_used_lines(); l++) {
                const Line& line = col.get_line(l);
                int line_start = line.get_raw_offset();
                int line_end = line_start + line.get_length();

                if (offset >= line_start && offset <= line_end) {
                    out.page = p;
                    out.column = c;
                    out.line = l;
                    out.offset = offset - line_start;
                    return;
                }
            }
        }
    }

    // offset falls after all lines (or between lines) -- put cursor
    // at end of last line on last page
    if (m_pages.size() > 0) {
        int last_page = m_pages.size() - 1;
        const Page& page = m_pages[last_page];
        for (int c = page.get_num_columns() - 1; c >= 0; c--) {
            const Column& col = page.get_column(c);
            if (col.get_used_lines() > 0) {
                int last_line = col.get_used_lines() - 1;
                out.page = last_page;
                out.column = c;
                out.line = last_line;
                out.offset = col.get_line(last_line).get_length();
                return;
            }
        }
        // empty page
        out.page = last_page;
        out.column = 0;
        out.line = 0;
        out.offset = 0;
    }
}

// Cursor movement

const CursorPosition& Document::get_cursor() const { return m_cursor; }

// Set cursor position
void Document::set_cursor(int page, int col, int line, int offset) {
    m_cursor.page = page;
    m_cursor.column = col;
    m_cursor.line = line;
    m_cursor.offset = offset;
}

void Document::set_cursor_from_offset(int offset) {
    if (offset < 0) offset = 0;
    if (offset > m_raw_len) offset = m_raw_len;
    offset_to_cursor(offset, m_cursor);
}

int Document::get_cursor_offset() const {
    return cursor_to_offset(m_cursor);
}

// Move cursor one position left
void Document::move_cursor_left() {
    int offset = get_cursor_offset();
    if (offset > 0) {
        set_cursor_from_offset(offset - 1);
    }
}

// Move cursor one position right
void Document::move_cursor_right() {
    int offset = get_cursor_offset();
    if (offset < m_raw_len) {
        set_cursor_from_offset(offset + 1);
    }
}

// Move cursor up one line
void Document::move_cursor_up() {
    // try to go to the same offset on the previous line
    if (m_cursor.line > 0) {
        m_cursor.line--;
        // clamp offset to the length of the new line
        const Line& line = m_pages[m_cursor.page]
            .get_column(m_cursor.column)
            .get_line(m_cursor.line);
        if (m_cursor.offset > line.get_length()) {
            m_cursor.offset = line.get_length();
        }
    }
    else if (m_cursor.column > 0) {
        // jump to the last line of the previous column
        m_cursor.column--;
        const Column& col = m_pages[m_cursor.page].get_column(m_cursor.column);
        m_cursor.line = col.get_used_lines() > 0 ? col.get_used_lines() - 1 : 0;
        if (col.get_used_lines() > 0) {
            const Line& line = col.get_line(m_cursor.line);
            if (m_cursor.offset > line.get_length()) {
                m_cursor.offset = line.get_length();
            }
        }
    }
    else if (m_cursor.page > 0) {
        // jump to the last line of the last column on the previous page
        m_cursor.page--;
        const Page& page = m_pages[m_cursor.page];
        m_cursor.column = page.get_num_columns() - 1;
        const Column& col = page.get_column(m_cursor.column);
        m_cursor.line = col.get_used_lines() > 0 ? col.get_used_lines() - 1 : 0;
        if (col.get_used_lines() > 0) {
            const Line& line = col.get_line(m_cursor.line);
            if (m_cursor.offset > line.get_length()) {
                m_cursor.offset = line.get_length();
            }
        }
    }
}

// Move cursor down one line
void Document::move_cursor_down() {
    const Page& page = m_pages[m_cursor.page];
    const Column& col = page.get_column(m_cursor.column);
    int last_line = col.get_used_lines() - 1;

    if (m_cursor.line < last_line) {
        m_cursor.line++;
        const Line& line = col.get_line(m_cursor.line);
        if (m_cursor.offset > line.get_length()) {
            m_cursor.offset = line.get_length();
        }
    }
    else if (m_cursor.column < page.get_num_columns() - 1) {
        // jump to the first line of the next column
        m_cursor.column++;
        m_cursor.line = 0;
        const Column& next_col = page.get_column(m_cursor.column);
        if (next_col.get_used_lines() > 0) {
            const Line& line = next_col.get_line(0);
            if (m_cursor.offset > line.get_length()) {
                m_cursor.offset = line.get_length();
            }
        }
        else {
            m_cursor.offset = 0;
        }
    }
    else if (m_cursor.page < m_pages.size() - 1) {
        // jump to the first line of the first column on the next page
        m_cursor.page++;
        m_cursor.column = 0;
        m_cursor.line = 0;
        const Column& next_col = m_pages[m_cursor.page].get_column(0);
        if (next_col.get_used_lines() > 0) {
            const Line& line = next_col.get_line(0);
            if (m_cursor.offset > line.get_length()) {
                m_cursor.offset = line.get_length();
            }
        }
        else {
            m_cursor.offset = 0;
        }
    }
}

void Document::move_cursor_home() {
    m_cursor.offset = 0;
}

void Document::move_cursor_end() {
    if (m_pages.size() == 0) return;
    if (m_cursor.page >= m_pages.size()) return;
    const Page& page = m_pages[m_cursor.page];
    if (m_cursor.column >= page.get_num_columns()) return;
    const Column& col = page.get_column(m_cursor.column);
    if (m_cursor.line >= col.get_used_lines()) return;
    const Line& line = col.get_line(m_cursor.line);
    m_cursor.offset = line.get_length();
}

void Document::move_cursor_page_up() {
    if (m_cursor.page > 0) {
        m_cursor.page--;
        // keep same column/line/offset if possible, clamp if needed
        const Page& page = m_pages[m_cursor.page];
        if (m_cursor.column >= page.get_num_columns()) {
            m_cursor.column = page.get_num_columns() - 1;
        }
        const Column& col = page.get_column(m_cursor.column);
        if (m_cursor.line >= col.get_used_lines()) {
            m_cursor.line = col.get_used_lines() > 0 ? col.get_used_lines() - 1 : 0;
        }
        if (col.get_used_lines() > 0) {
            const Line& line = col.get_line(m_cursor.line);
            if (m_cursor.offset > line.get_length()) {
                m_cursor.offset = line.get_length();
            }
        }
    }
}

void Document::move_cursor_page_down() {
    if (m_cursor.page < m_pages.size() - 1) {
        m_cursor.page++;
        const Page& page = m_pages[m_cursor.page];
        if (m_cursor.column >= page.get_num_columns()) {
            m_cursor.column = page.get_num_columns() - 1;
        }
        const Column& col = page.get_column(m_cursor.column);
        if (m_cursor.line >= col.get_used_lines()) {
            m_cursor.line = col.get_used_lines() > 0 ? col.get_used_lines() - 1 : 0;
        }
        if (col.get_used_lines() > 0) {
            const Line& line = col.get_line(m_cursor.line);
            if (m_cursor.offset > line.get_length()) {
                m_cursor.offset = line.get_length();
            }
        }
    }
}

// Selection

const SelectionRange& Document::get_selection() const { return m_selection; }

// Set selection range
void Document::set_selection(int start, int end) {
    // clamp values to valid range
    if (start < 0) start = 0;
    if (end < 0) end = 0;
    if (start > m_raw_len) start = m_raw_len;
    if (end > m_raw_len) end = m_raw_len;
    m_selection.start = start;
    m_selection.end = end;
    m_selection.active = true;
}

// Clear selection
void Document::clear_selection() {
    m_selection.clear();
}

bool Document::has_selection() const {
    return m_selection.active && m_selection.start != m_selection.end;
}

// Alignment

// Get current alignment mode
AlignmentMode Document::get_alignment() const { return m_alignment; }

// Set text alignment mode
void Document::set_alignment(AlignmentMode mode) {
    m_alignment = mode;
}

// File metadata

const wchar_t* Document::get_file_path() const { return m_file_path; }

void Document::set_file_path(const wchar_t* path) {
    if (path) {
        str_ncpy(m_file_path, path, 259);
    }
}

const wchar_t* Document::get_title() const { return m_title; }

void Document::set_title(const wchar_t* title) {
    if (title) {
        str_ncpy(m_title, title, 127);
    }
}

// Check if document has unsaved changes
bool Document::is_modified() const { return m_is_modified; }
// Mark document as modified or unmodified
void Document::set_modified(bool val) { m_is_modified = val; }
int Document::get_tab_index() const { return m_tab_index; }

// --- delta tracking accessors ---
const EditDeltaArray& Document::get_deltas() const { return m_deltas; }
int Document::get_delta_count() const { return m_deltas.size(); }
void Document::clear_deltas() { m_deltas.clear(); }
int Document::get_delta_sequence() const { return m_delta_sequence; }

// Renderer implementation

// Constructor
Renderer::Renderer()
    : m_font(nullptr)
    , m_char_width(8)
    , m_char_height(16)
    , m_padding(20)
    , m_bg_color(RGB(30, 30, 50))
    , m_text_color(RGB(220, 210, 190))
    , m_cursor_color(RGB(255, 200, 80))
    , m_highlight_color(RGB(80, 80, 30))
    , m_spell_error_color(RGB(255, 80, 80))
    , m_selection_bg(RGB(60, 80, 120))
    , m_footer_color(RGB(150, 140, 120))
    , m_status_bar_bg(RGB(40, 40, 60))
    , m_status_bar_fg(RGB(180, 170, 150))
    , m_col_separator_color(RGB(60, 60, 80)) {
}

// Destructor
Renderer::~Renderer() {
    if (m_font) {
        DeleteObject(m_font);
        m_font = nullptr;
    }
}

// init -- create the monospace font and measure character size

void Renderer::init(HDC hdc) {
    if (m_font) {
        DeleteObject(m_font);
    }

    // create a monospace font for the editor
    m_font = CreateFontW(
        16, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        FIXED_PITCH | FF_MODERN, L"Consolas");

    // measure the character dimensions using this font
    HFONT old_font = (HFONT)SelectObject(hdc, m_font);
    TEXTMETRIC tm;
    GetTextMetrics(hdc, &tm);
    m_char_width = tm.tmAveCharWidth;
    m_char_height = tm.tmHeight + tm.tmExternalLeading;
    SelectObject(hdc, old_font);
}

HFONT Renderer::get_font() const { return m_font; }
int Renderer::get_char_width() const { return m_char_width; }
int Renderer::get_char_height() const { return m_char_height; }
int Renderer::get_padding() const { return m_padding; }

// init_for_layout -- pick a font size that makes one page fit
// within the given window width, then re-measure char dimensions

// Initialize fonts and calculate layout metrics
void Renderer::init_for_layout(HDC hdc, int window_width, int cols_per_page,
    int chars_per_line) {
    // we need: cols_per_page * chars_per_line * char_w + gaps + margins <= window_width
    int total_chars = cols_per_page * chars_per_line;
    if (total_chars <= 0) return;

    // try progressively smaller font heights until it fits
    // use three padding tiers: 20, 10, 2
    int pad_tiers[] = { 20, 10, 2, 0 };
    int num_tiers = 4;

    for (int font_h = 20; font_h >= 4; font_h--) {
        HFONT test_font = CreateFontW(
            font_h, 0, 0, 0,
            FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            FIXED_PITCH | FF_MODERN, L"Consolas");

        HFONT old = (HFONT)SelectObject(hdc, test_font);
        TEXTMETRIC tm;
        GetTextMetrics(hdc, &tm);
        int cw = tm.tmAveCharWidth;
        int ch = tm.tmHeight + tm.tmExternalLeading;
        SelectObject(hdc, old);

        // try each padding tier for this font size
        for (int t = 0; t < num_tiers; t++) {
            int pad = pad_tiers[t];
            int col_pixel_w = chars_per_line * cw;
            int page_w = cols_per_page * col_pixel_w +
                (cols_per_page - 1) * pad + 2 * pad;

            if (page_w <= window_width) {
                // fits -- use this font and padding
                if (m_font) DeleteObject(m_font);
                m_font = test_font;
                m_char_width = cw;
                m_char_height = ch;
                m_padding = pad;
                return;
            }
        }

        DeleteObject(test_font);
    }

    // last resort: use font height 4 with zero padding, even if it overflows
    if (m_font) DeleteObject(m_font);
    m_font = CreateFontW(
        4, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        FIXED_PITCH | FF_MODERN, L"Consolas");

    HFONT old = (HFONT)SelectObject(hdc, m_font);
    TEXTMETRIC tm;
    GetTextMetrics(hdc, &tm);
    m_char_width = tm.tmAveCharWidth;
    m_char_height = tm.tmHeight + tm.tmExternalLeading;
    m_padding = 0;
    SelectObject(hdc, old);
}

// paint -- main paint routine called from WM_PAINT.
// Draws the background, all visible pages/columns, cursor,
// footer, status bar, and any overlays (ToC, search history).

// Main paint function, draws everything to window
// Uses double buffering to eliminate flickering
void Renderer::paint(HDC hdc, RECT client_rect, Document* doc,
    SpellChecker* spell, SearchEngine* search,
    Statistics* stats, bool cursor_visible,
    int active_tab, bool search_mode,
    const wchar_t* search_buffer,
    bool showing_toc, void* toc_ptr,
    bool showing_search_history,
    int scroll_y) {
    if (!doc) return;

    int client_width = client_rect.right - client_rect.left;
    int client_height = client_rect.bottom - client_rect.top;

    // create off-screen buffer for double buffering (no flicker)
    HDC mem_dc = CreateCompatibleDC(hdc);
    HBITMAP mem_bitmap = CreateCompatibleBitmap(hdc, client_width, client_height);
    HBITMAP old_bitmap = (HBITMAP)SelectObject(mem_dc, mem_bitmap);

    // draw everything to the off-screen buffer
    HBRUSH bg_brush = CreateSolidBrush(m_bg_color);
    RECT full_rect = { 0, 0, client_width, client_height };
    FillRect(mem_dc, &full_rect, bg_brush);
    DeleteObject(bg_brush);

    SetBkMode(mem_dc, TRANSPARENT);
    HFONT old_font = (HFONT)SelectObject(mem_dc, m_font);

    // reserve space for the status bar at the bottom
    int status_bar_height = m_char_height + 8;

    // calculate the page layout dimensions
    int cols_per_page = doc->get_cols_per_page();
    int lines_per_col = doc->get_lines_per_col();
    int chars_per_line = doc->get_chars_per_line();

    // each column is chars_per_line characters wide
    int col_pixel_width = chars_per_line * m_char_width;
    // gap between columns
    int col_gap = m_padding;
    // total width of one page
    int page_pixel_width = cols_per_page * col_pixel_width +
        (cols_per_page - 1) * col_gap;

    // footer height
    int footer_height = m_char_height + 4;

    // total page height (text area + footer)
    int page_pixel_height = lines_per_col * m_char_height + footer_height;

    // gap between pages laid out side by side
    int page_gap = m_padding * 2;

    // figure out how many pages fit horizontally
    int available_width = client_width - 2 * m_padding;
    int pages_per_row = 1;
    if (page_pixel_width + page_gap > 0) {
        // try to fit as many pages as possible
        int test = (available_width + page_gap) / (page_pixel_width + page_gap);
        if (test > 1) pages_per_row = test;
    }

    // draw each page
    int total_pages = doc->get_page_count();
    const CursorPosition& cursor = doc->get_cursor();

    for (int p = 0; p < total_pages; p++) {
        // calculate page position (lay out pages left to right, then wrap)
        int page_col = p % pages_per_row;
        int page_row = p / pages_per_row;

        int page_x = m_padding + page_col * (page_pixel_width + page_gap);
        int page_y = m_padding + page_row * (page_pixel_height + page_gap) - scroll_y;

        // skip if this page is entirely above or below the visible area
        if (page_y + page_pixel_height < 0) continue;
        if (page_y > client_height - status_bar_height) continue;

        // draw each column on this page
        for (int c = 0; c < cols_per_page; c++) {
            int col_x = page_x + c * (col_pixel_width + col_gap);
            int col_y = page_y;

            draw_column(mem_dc, doc, p, c, col_x, col_y, spell, search);

            // draw column separator (vertical line between columns)
            if (c < cols_per_page - 1) {
                int sep_x = col_x + col_pixel_width + col_gap / 2;
                HBRUSH sep_brush = CreateSolidBrush(m_col_separator_color);
                RECT sep_rect = { sep_x, col_y,
                                  sep_x + 1,
                                  col_y + lines_per_col * m_char_height };
                FillRect(mem_dc, &sep_rect, sep_brush);
                DeleteObject(sep_brush);
            }
        }

        // draw the cursor if it is on this page
        if (p == cursor.page && cursor_visible) {
            int cursor_col_x = page_x + cursor.column * (col_pixel_width + col_gap);
            draw_cursor(mem_dc, doc, cursor_col_x, page_y, true);
        }

        // draw footer for this page
        int footer_y = page_y + lines_per_col * m_char_height + 2;
        draw_footer(mem_dc, p + 1, total_pages, page_x, footer_y, page_pixel_width);
    }

    // draw the status bar at the very bottom
    draw_status_bar(mem_dc, client_rect, doc, stats,
        active_tab, search_mode, search_buffer);

    // draw overlays on top
    if (showing_toc && toc_ptr) {
        draw_toc(mem_dc, client_rect, toc_ptr);
    }

    if (showing_search_history && search) {
        draw_search_history(mem_dc, client_rect, (void*)search);
    }

    // restore font and copy buffer to screen (single blit = no flicker)
    SelectObject(mem_dc, old_font);
    BitBlt(hdc, 0, 0, client_width, client_height, mem_dc, 0, 0, SRCCOPY);

    // cleanup off-screen buffer
    SelectObject(mem_dc, old_bitmap);
    DeleteObject(mem_bitmap);
    DeleteDC(mem_dc);
}

// draw_column -- render a single column of text.
// Handles spell error coloring and search match highlighting.

void Renderer::draw_column(HDC hdc, const Document* doc, int page_idx,
    int col_idx, int x_start, int y_start,
    SpellChecker* spell, SearchEngine* search) {
    const Page& page = doc->get_page(page_idx);
    if (col_idx >= page.get_num_columns()) return;
    const Column& col = page.get_column(col_idx);

    int chars_per_line = doc->get_chars_per_line();
    AlignmentMode align = doc->get_alignment();

    // we need to track the raw text offset for each character
    // to support spell/search highlighting and selection display.
    // Each line now stores its raw_offset directly, so we don't
    // need to walk through all preceding lines to calculate it.

    // get selection range for highlighting
    const SelectionRange& sel = doc->get_selection();

    for (int l = 0; l < col.get_used_lines(); l++) {
        const Line& line = col.get_line(l);
        int line_len = line.get_length();
        const wchar_t* text = line.get_text();
        int line_raw_offset = line.get_raw_offset();

        int y = y_start + l * m_char_height;

        // determine if this is the last line before a paragraph break
        // (used for justified alignment -- don't justify the last line)
        bool is_last_of_para = false;
        if (l == col.get_used_lines() - 1) {
            is_last_of_para = true;
        }
        else {
            // check if next line starts at a newline boundary in raw text
            int next_line_raw = line_raw_offset + line_len;
            if (next_line_raw < doc->get_raw_length() &&
                doc->get_raw_text()[next_line_raw] == L'\n') {
                is_last_of_para = true;
            }
        }

        // apply alignment to get display text
        wchar_t display_buf[512];
        int display_len = 0;
        int x_offset = 0;  // pixel offset for right/center alignment

        if (align == ALIGN_LEFT || line_len == 0) {
            // just draw the text as-is at x_start
            for (int i = 0; i < line_len && i < 511; i++) {
                display_buf[i] = text[i];
            }
            display_buf[line_len < 511 ? line_len : 511] = L'\0';
            display_len = (line_len < 511) ? line_len : 511;
        }
        else if (align == ALIGN_RIGHT) {
            int pad = chars_per_line - line_len;
            if (pad < 0) pad = 0;
            x_offset = pad * m_char_width;
            for (int i = 0; i < line_len && i < 511; i++) {
                display_buf[i] = text[i];
            }
            display_buf[line_len < 511 ? line_len : 511] = L'\0';
            display_len = (line_len < 511) ? line_len : 511;
        }
        else if (align == ALIGN_CENTER) {
            int pad = (chars_per_line - line_len) / 2;
            if (pad < 0) pad = 0;
            x_offset = pad * m_char_width;
            for (int i = 0; i < line_len && i < 511; i++) {
                display_buf[i] = text[i];
            }
            display_buf[line_len < 511 ? line_len : 511] = L'\0';
            display_len = (line_len < 511) ? line_len : 511;
        }
        else if (align == ALIGN_JUSTIFIED) {
            // justified: only justify if it is not the last line of a paragraph
            if (is_last_of_para || line_len == 0) {
                // don't justify -- just left-align
                for (int i = 0; i < line_len && i < 511; i++) {
                    display_buf[i] = text[i];
                }
                display_buf[line_len < 511 ? line_len : 511] = L'\0';
                display_len = line_len;
            }
            else {
                apply_alignment(text, line_len, chars_per_line, ALIGN_JUSTIFIED,
                    is_last_of_para, display_buf, 512);
                display_len = str_len(display_buf);
            }
        }

        // draw the line character by character to support per-char coloring
        for (int i = 0; i < display_len; i++) {
            int char_raw_offset = line_raw_offset + i;
            // clamp to avoid out of bounds
            if (char_raw_offset >= doc->get_raw_length()) {
                char_raw_offset = doc->get_raw_length() - 1;
            }

            // determine this character's color
            COLORREF fg = m_text_color;

            // check spell errors
            if (spell && spell->is_loaded()) {
                const SpellErrorArray& errors = spell->get_errors();
                for (int e = 0; e < errors.size(); e++) {
                    if (char_raw_offset >= errors[e].start &&
                        char_raw_offset < errors[e].end) {
                        fg = m_spell_error_color;
                        break;
                    }
                }
            }

            // check search highlights
            bool is_search_hit = false;
            if (search && search->is_active()) {
                is_search_hit = search->is_highlighted(char_raw_offset);
            }

            // check selection
            bool is_selected = false;
            if (sel.active && char_raw_offset >= sel.start &&
                char_raw_offset < sel.end) {
                is_selected = true;
            }

            // draw background highlight if needed
            int cx = x_start + x_offset + i * m_char_width;

            if (is_selected) {
                HBRUSH sel_brush = CreateSolidBrush(m_selection_bg);
                RECT char_rect = { cx, y, cx + m_char_width, y + m_char_height };
                FillRect(hdc, &char_rect, sel_brush);
                DeleteObject(sel_brush);
            }
            else if (is_search_hit) {
                HBRUSH hl_brush = CreateSolidBrush(m_highlight_color);
                RECT char_rect = { cx, y, cx + m_char_width, y + m_char_height };
                FillRect(hdc, &char_rect, hl_brush);
                DeleteObject(hl_brush);
            }

            SetTextColor(hdc, fg);
            ExtTextOutW(hdc, cx, y, 0, nullptr, &display_buf[i], 1, nullptr);
        }
    }
}

// draw_footer -- page number at the bottom of each page

void Renderer::draw_footer(HDC hdc, int page_number, int total_pages,
    int x_start, int y_pos, int page_width) {
    // format: "Page X of Y"
    wchar_t footer[64];
    wchar_t num1[16], num2[16];
    int_to_str(page_number, num1);
    int_to_str(total_pages, num2);

    str_cpy(footer, L"Page ");
    str_cat(footer, num1);
    str_cat(footer, L" of ");
    str_cat(footer, num2);

    int len = str_len(footer);

    // center the footer text under the page
    int text_width = len * m_char_width;
    int fx = x_start + (page_width - text_width) / 2;

    SetTextColor(hdc, m_footer_color);
    ExtTextOutW(hdc, fx, y_pos, 0, nullptr, footer, len, nullptr);
}

// draw_status_bar -- information bar at the window bottom.
// Shows tab info, word count, reading time, alignment,
// and search prompt when active.

void Renderer::draw_status_bar(HDC hdc, RECT client_rect, Document* doc,
    Statistics* stats, int active_tab,
    bool search_mode, const wchar_t* search_buffer) {
    int bar_height = m_char_height + 8;
    RECT bar_rect = {
        client_rect.left,
        client_rect.bottom - bar_height,
        client_rect.right,
        client_rect.bottom
    };

    // draw bar background
    HBRUSH bar_brush = CreateSolidBrush(m_status_bar_bg);
    FillRect(hdc, &bar_rect, bar_brush);
    DeleteObject(bar_brush);

    SetTextColor(hdc, m_status_bar_fg);

    int x = bar_rect.left + 10;
    int y = bar_rect.top + 4;

    // show the search prompt if in search mode
    if (search_mode) {
        wchar_t prompt[300];
        str_cpy(prompt, L"Search: ");
        if (search_buffer) {
            str_cat(prompt, search_buffer);
        }
        str_cat(prompt, L"_");
        int len = str_len(prompt);
        ExtTextOutW(hdc, x, y, 0, nullptr, prompt, len, nullptr);
        return;
    }

    // tab indicator
    wchar_t tab_buf[64];
    wchar_t tab_num[8];
    int_to_str(active_tab + 1, tab_num);
    str_cpy(tab_buf, L"Tab ");
    str_cat(tab_buf, tab_num);

    // document title
    if (doc && doc->get_title()[0] != L'\0') {
        str_cat(tab_buf, L": ");
        str_cat(tab_buf, doc->get_title());
    }

    if (doc && doc->is_modified()) {
        str_cat(tab_buf, L" *");
    }

    int tab_len = str_len(tab_buf);
    ExtTextOutW(hdc, x, y, 0, nullptr, tab_buf, tab_len, nullptr);
    x += (tab_len + 3) * m_char_width;

    // separator
    ExtTextOutW(hdc, x, y, 0, nullptr, L"|", 1, nullptr);
    x += 2 * m_char_width;

    // statistics
    if (stats) {
        wchar_t stat_buf[128];
        wchar_t num[16];

        // words
        str_cpy(stat_buf, L"Words: ");
        int_to_str(stats->get_word_count(), num);
        str_cat(stat_buf, num);

        str_cat(stat_buf, L"  Chars: ");
        int_to_str(stats->get_chars_with_spaces(), num);
        str_cat(stat_buf, num);

        str_cat(stat_buf, L"  Pages: ");
        int_to_str(stats->get_page_count(), num);
        str_cat(stat_buf, num);

        str_cat(stat_buf, L"  Read: ");
        int_to_str(stats->get_reading_time_sec(), num);
        str_cat(stat_buf, num);
        str_cat(stat_buf, L"s");

        int stat_len = str_len(stat_buf);
        ExtTextOutW(hdc, x, y, 0, nullptr, stat_buf, stat_len, nullptr);
        x += (stat_len + 3) * m_char_width;
    }

    // separator
    ExtTextOutW(hdc, x, y, 0, nullptr, L"|", 1, nullptr);
    x += 2 * m_char_width;

    // alignment indicator
    if (doc) {
        const wchar_t* align_str = L"Left";
        switch (doc->get_alignment()) {
        case ALIGN_RIGHT:     align_str = L"Right"; break;
        case ALIGN_CENTER:    align_str = L"Center"; break;
        case ALIGN_JUSTIFIED: align_str = L"Justified"; break;
        default: break;
        }
        wchar_t align_buf[32];
        str_cpy(align_buf, L"Align: ");
        str_cat(align_buf, align_str);
        int a_len = str_len(align_buf);
        ExtTextOutW(hdc, x, y, 0, nullptr, align_buf, a_len, nullptr);
    }
}

// draw_cursor -- draw the blinking caret at the cursor position

void Renderer::draw_cursor(HDC hdc, Document* doc, int col_x_start,
    int y_start, bool visible) {
    if (!visible || !doc) return;

    const CursorPosition& cur = doc->get_cursor();

    // figure out the pixel position of the cursor within its column
    int cx = col_x_start + cur.offset * m_char_width;
    int cy = y_start + cur.line * m_char_height;

    // handle alignment offset
    AlignmentMode align = doc->get_alignment();
    int chars_per_line = doc->get_chars_per_line();

    if (cur.page < doc->get_page_count()) {
        const Page& page = doc->get_page(cur.page);
        if (cur.column < page.get_num_columns()) {
            const Column& col = page.get_column(cur.column);
            if (cur.line < col.get_used_lines()) {
                int line_len = col.get_line(cur.line).get_length();

                if (align == ALIGN_RIGHT) {
                    int pad = chars_per_line - line_len;
                    if (pad < 0) pad = 0;
                    cx += pad * m_char_width;
                }
                else if (align == ALIGN_CENTER) {
                    int pad = (chars_per_line - line_len) / 2;
                    if (pad < 0) pad = 0;
                    cx += pad * m_char_width;
                }
            }
        }
    }

    // draw a thin vertical bar for the cursor
    HBRUSH cursor_brush = CreateSolidBrush(m_cursor_color);
    RECT cursor_rect = { cx, cy, cx + 2, cy + m_char_height };
    FillRect(hdc, &cursor_rect, cursor_brush);
    DeleteObject(cursor_brush);
}

// draw_toc -- table of contents overlay

void Renderer::draw_toc(HDC hdc, RECT client_rect, void* toc_ptr) {
    TableOfContents* toc = (TableOfContents*)toc_ptr;
    if (!toc) return;

    // draw a semi-transparent overlay box in the center of the window
    int box_width = 400;
    int box_height = 300;
    int bx = (client_rect.right - client_rect.left - box_width) / 2;
    int by = (client_rect.bottom - client_rect.top - box_height) / 2;

    // draw box background
    HBRUSH box_bg = CreateSolidBrush(RGB(20, 20, 40));
    RECT box_rect = { bx, by, bx + box_width, by + box_height };
    FillRect(hdc, &box_rect, box_bg);
    DeleteObject(box_bg);

    // draw border
    HBRUSH border_brush = CreateSolidBrush(RGB(100, 90, 70));
    RECT top_border = { bx, by, bx + box_width, by + 2 };
    RECT bot_border = { bx, by + box_height - 2, bx + box_width, by + box_height };
    RECT left_border = { bx, by, bx + 2, by + box_height };
    RECT right_border = { bx + box_width - 2, by, bx + box_width, by + box_height };
    FillRect(hdc, &top_border, border_brush);
    FillRect(hdc, &bot_border, border_brush);
    FillRect(hdc, &left_border, border_brush);
    FillRect(hdc, &right_border, border_brush);
    DeleteObject(border_brush);

    // title
    SetTextColor(hdc, RGB(200, 180, 140));
    const wchar_t* title = L"TABLE OF CONTENTS";
    int title_len = str_len(title);
    int title_x = bx + (box_width - title_len * m_char_width) / 2;
    ExtTextOutW(hdc, title_x, by + 10, 0, nullptr, title, title_len, nullptr);

    // draw entries
    SetTextColor(hdc, RGB(180, 170, 150));
    int entry_y = by + 10 + m_char_height + 10;
    int max_entries = (box_height - 40) / m_char_height;

    const TocEntryArray& entries = toc->get_entries();
    for (int i = 0; i < entries.size() && i < max_entries; i++) {
        const TocEntry& entry = entries[i];

        // format: "Title ......... Page X"
        wchar_t line[256];
        str_cpy(line, entry.title);

        wchar_t page_str[32];
        str_cpy(page_str, L"  p.");
        wchar_t num[8];
        int_to_str(entry.page_number, num);
        str_cat(page_str, num);

        // add dots between title and page number
        int title_chars = str_len(line);
        int page_chars = str_len(page_str);
        int avail = (box_width - 20) / m_char_width;
        int dots_needed = avail - title_chars - page_chars;

        if (dots_needed > 2) {
            str_cat(line, L" ");
            for (int d = 0; d < dots_needed - 2; d++) {
                int pos = str_len(line);
                line[pos] = L'.';
                line[pos + 1] = L'\0';
            }
            str_cat(line, L" ");
        }
        str_cat(line, page_str);

        int line_len = str_len(line);
        ExtTextOutW(hdc, bx + 10, entry_y, 0, nullptr, line, line_len, nullptr);
        entry_y += m_char_height;
    }

    if (entries.size() == 0) {
        const wchar_t* empty_msg = L"No entries found.";
        int el = str_len(empty_msg);
        ExtTextOutW(hdc, bx + 10, entry_y, 0, nullptr, empty_msg, el, nullptr);
    }
}

// draw_search_history -- search history overlay

void Renderer::draw_search_history(HDC hdc, RECT client_rect, void* search_ptr) {
    SearchEngine* search = (SearchEngine*)search_ptr;
    if (!search) return;

    // draw a box in the top-right corner
    int box_width = 300;
    int box_height = 180;
    int bx = client_rect.right - box_width - 20;
    int by = 20;

    HBRUSH box_bg = CreateSolidBrush(RGB(20, 20, 40));
    RECT box_rect = { bx, by, bx + box_width, by + box_height };
    FillRect(hdc, &box_rect, box_bg);
    DeleteObject(box_bg);

    // border
    HBRUSH border_brush = CreateSolidBrush(RGB(100, 90, 70));
    RECT top_b = { bx, by, bx + box_width, by + 2 };
    RECT bot_b = { bx, by + box_height - 2, bx + box_width, by + box_height };
    RECT left_b = { bx, by, bx + 2, by + box_height };
    RECT right_b = { bx + box_width - 2, by, bx + box_width, by + box_height };
    FillRect(hdc, &top_b, border_brush);
    FillRect(hdc, &bot_b, border_brush);
    FillRect(hdc, &left_b, border_brush);
    FillRect(hdc, &right_b, border_brush);
    DeleteObject(border_brush);

    // title
    SetTextColor(hdc, RGB(200, 180, 140));
    const wchar_t* title = L"SEARCH HISTORY";
    int tl = str_len(title);
    ExtTextOutW(hdc, bx + 10, by + 10, 0, nullptr, title, tl, nullptr);

    // entries
    SetTextColor(hdc, RGB(180, 170, 150));
    int ey = by + 10 + m_char_height + 8;

    int count = search->get_history_count();
    const SearchHistoryEntry* history = search->get_history();

    if (count == 0) {
        const wchar_t* empty = L"No searches yet.";
        int el = str_len(empty);
        ExtTextOutW(hdc, bx + 10, ey, 0, nullptr, empty, el, nullptr);
    }
    else {
        for (int i = 0; i < count; i++) {
            wchar_t entry_line[300];
            str_cpy(entry_line, L"\"");
            str_cat(entry_line, history[i].term);
            str_cat(entry_line, L"\" - ");
            wchar_t num[16];
            int_to_str(history[i].match_count, num);
            str_cat(entry_line, num);
            str_cat(entry_line, L" matches");

            int el = str_len(entry_line);
            ExtTextOutW(hdc, bx + 10, ey, 0, nullptr, entry_line, el, nullptr);
            ey += m_char_height;
        }
    }
}

// pixel_to_cursor -- map a mouse click to a document position.
// Returns true if the click landed within text area.

// Convert screen coordinates to cursor position
bool Renderer::pixel_to_cursor(int px, int py, RECT client_rect,
    Document* doc, int& out_page,
    int& out_col, int& out_line,
    int& out_offset,
    int scroll_y) {
    if (!doc) return false;

    int cols_per_page = doc->get_cols_per_page();
    int lines_per_col = doc->get_lines_per_col();
    int chars_per_line = doc->get_chars_per_line();

    int col_pixel_width = chars_per_line * m_char_width;
    int col_gap = m_padding;
    int page_pixel_width = cols_per_page * col_pixel_width +
        (cols_per_page - 1) * col_gap;
    int footer_height = m_char_height + 4;
    int page_pixel_height = lines_per_col * m_char_height + footer_height;
    int page_gap = m_padding * 2;

    int client_width = client_rect.right - client_rect.left;
    int available_width = client_width - 2 * m_padding;
    int pages_per_row = 1;
    if (page_pixel_width + page_gap > 0) {
        int test = (available_width + page_gap) / (page_pixel_width + page_gap);
        if (test > 1) pages_per_row = test;
    }

    int total_pages = doc->get_page_count();

    for (int p = 0; p < total_pages; p++) {
        int page_col_idx = p % pages_per_row;
        int page_row_idx = p / pages_per_row;

        int page_x = m_padding + page_col_idx * (page_pixel_width + page_gap);
        int page_y = m_padding + page_row_idx * (page_pixel_height + page_gap) - scroll_y;

        // check if click is within this page's text area
        if (px >= page_x && px < page_x + page_pixel_width &&
            py >= page_y && py < page_y + lines_per_col * m_char_height) {

            // determine which column was clicked
            for (int c = 0; c < cols_per_page; c++) {
                int col_x = page_x + c * (col_pixel_width + col_gap);
                if (px >= col_x && px < col_x + col_pixel_width) {
                    // bounds check: make sure this column exists in the page
                    if (c >= doc->get_page(p).get_num_columns()) continue;

                    // determine the line
                    int line = (py - page_y) / m_char_height;
                    if (line < 0) line = 0;

                    const Column& column = doc->get_page(p).get_column(c);
                    if (line >= column.get_used_lines()) {
                        line = column.get_used_lines() > 0 ?
                            column.get_used_lines() - 1 : 0;
                    }

                    // determine the character offset
                    int rel_x = px - col_x;

                    // account for alignment offset
                    int align_offset_px = 0;
                    if (column.get_used_lines() > 0 && line < column.get_used_lines()) {
                        int line_len = column.get_line(line).get_length();
                        AlignmentMode align = doc->get_alignment();
                        if (align == ALIGN_RIGHT) {
                            int pad = chars_per_line - line_len;
                            if (pad > 0) align_offset_px = pad * m_char_width;
                        }
                        else if (align == ALIGN_CENTER) {
                            int pad = (chars_per_line - line_len) / 2;
                            if (pad > 0) align_offset_px = pad * m_char_width;
                        }
                    }

                    rel_x -= align_offset_px;
                    int offset = rel_x / m_char_width;
                    if (offset < 0) offset = 0;

                    if (column.get_used_lines() > 0 && line < column.get_used_lines()) {
                        if (offset > column.get_line(line).get_length()) {
                            offset = column.get_line(line).get_length();
                        }
                    }
                    else {
                        offset = 0;
                    }

                    out_page = p;
                    out_col = c;
                    out_line = line;
                    out_offset = offset;
                    return true;
                }
            }
        }
    }

    return false;
}

// apply_alignment -- compute justified text by distributing
// extra spaces between words.

void Renderer::apply_alignment(const wchar_t* text, int text_len,
    int line_width, AlignmentMode mode,
    bool is_last_line_of_paragraph,
    wchar_t* out_buf, int out_buf_size) {
    if (mode != ALIGN_JUSTIFIED || is_last_line_of_paragraph ||
        text_len == 0 || text_len >= line_width) {
        // just copy the text as-is
        int copy_len = text_len;
        if (copy_len >= out_buf_size) copy_len = out_buf_size - 1;
        for (int i = 0; i < copy_len; i++) {
            out_buf[i] = text[i];
        }
        out_buf[copy_len] = L'\0';
        return;
    }

    // count the number of spaces (word gaps) in the line
    int space_count = 0;
    for (int i = 0; i < text_len; i++) {
        if (text[i] == L' ') space_count++;
    }

    if (space_count == 0) {
        // single word -- can't justify, just copy
        int copy_len = text_len;
        if (copy_len >= out_buf_size) copy_len = out_buf_size - 1;
        for (int i = 0; i < copy_len; i++) {
            out_buf[i] = text[i];
        }
        out_buf[copy_len] = L'\0';
        return;
    }

    // calculate how many extra spaces to distribute
    int extra_spaces = line_width - text_len;
    int spaces_per_gap = extra_spaces / space_count;
    int remainder = extra_spaces % space_count;

    int out_pos = 0;
    int gap_num = 0;
    for (int i = 0; i < text_len && out_pos < out_buf_size - 1; i++) {
        out_buf[out_pos++] = text[i];
        if (text[i] == L' ') {
            // add extra spaces at this gap
            int extra = spaces_per_gap + (gap_num < remainder ? 1 : 0);
            for (int s = 0; s < extra && out_pos < out_buf_size - 1; s++) {
                out_buf[out_pos++] = L' ';
            }
            gap_num++;
        }
    }
    out_buf[out_pos] = L'\0';
}

// SpellChecker implementation

// Constructor
SpellChecker::SpellChecker()
    : m_root(nullptr)
    , m_loaded(false) {
    m_root = new TrieNode();
}

// Destructor
SpellChecker::~SpellChecker() {
    free_trie(m_root);
    m_root = nullptr;
}

// free_trie -- recursively delete all trie nodes

void SpellChecker::free_trie(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            free_trie(node->children[i]);
        }
    }
    delete node;
}

// insert_word -- add a lowercase word to the trie

void SpellChecker::insert_word(const wchar_t* word, int len) {
    if (!m_root || len <= 0) return;

    TrieNode* current = m_root;
    for (int i = 0; i < len; i++) {
        wchar_t c = to_lower(word[i]);
        // only handle a-z characters
        if (c < L'a' || c > L'z') return;
        int idx = c - L'a';

        if (!current->children[idx]) {
            current->children[idx] = new TrieNode();
        }
        current = current->children[idx];
    }
    current->is_word = true;
}

// load_dictionary -- read OPTED-Dictionary.csv using WinAPI
// CreateFileW/ReadFile. Each line is: Word,Count,POS,Definition
// We only need the Word column (everything before the first comma).

// Load dictionary from CSV file
bool SpellChecker::load_dictionary(const wchar_t* csv_path) {
    // open the file using WinAPI
    HANDLE hFile = CreateFileW(
        csv_path, GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }

    // get the file size
    DWORD file_size = GetFileSize(hFile, nullptr);
    if (file_size == INVALID_FILE_SIZE || file_size == 0) {
        CloseHandle(hFile);
        return false;
    }

    // read entire file into a buffer (narrow chars -- CSV is ASCII)
    char* buf = new char[file_size + 1];
    DWORD bytes_read = 0;
    BOOL ok = ReadFile(hFile, buf, file_size, &bytes_read, nullptr);
    CloseHandle(hFile);

    if (!ok || bytes_read == 0) {
        delete[] buf;
        return false;
    }
    buf[bytes_read] = '\0';

    // parse line by line manually
    bool first_line = true;
    int pos = 0;

    while (pos < (int)bytes_read) {
        // find the end of this line
        int line_start = pos;
        while (pos < (int)bytes_read && buf[pos] != '\n' && buf[pos] != '\r') {
            pos++;
        }
        int line_end = pos;

        // skip the newline characters (\r\n or \n)
        if (pos < (int)bytes_read && buf[pos] == '\r') pos++;
        if (pos < (int)bytes_read && buf[pos] == '\n') pos++;

        // skip the header line if there is one
        if (first_line) {
            first_line = false;
            if (line_end - line_start >= 4 &&
                (buf[line_start] == 'W' || buf[line_start] == 'w') &&
                (buf[line_start + 1] == 'o' || buf[line_start + 1] == 'O') &&
                (buf[line_start + 2] == 'r' || buf[line_start + 2] == 'R') &&
                (buf[line_start + 3] == 'd' || buf[line_start + 3] == 'D')) {
                continue;
            }
        }

        // extract the word: everything before the first comma
        int word_len = 0;
        while (line_start + word_len < line_end &&
            buf[line_start + word_len] != ',') {
            word_len++;
        }

        if (word_len == 0 || word_len > 100) continue;

        // check that the word contains only alphabetic characters
        bool valid = true;
        for (int i = 0; i < word_len; i++) {
            char c = buf[line_start + i];
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        // convert narrow word to wide
        wchar_t wide_word[128];
        for (int i = 0; i < word_len; i++) {
            wide_word[i] = (wchar_t)buf[line_start + i];
        }
        wide_word[word_len] = L'\0';

        insert_word(wide_word, word_len);
    }

    delete[] buf;
    m_loaded = true;
    return true;
}

// check_word -- look up a word in the trie.
// The word is converted to lowercase during the traversal.

// Check if word is spelled correctly
bool SpellChecker::check_word(const wchar_t* word, int len) const {
    if (!m_root || !m_loaded || len <= 0) return true;  // assume OK if not loaded

    const TrieNode* current = m_root;
    for (int i = 0; i < len; i++) {
        wchar_t c = to_lower(word[i]);
        if (c < L'a' || c > L'z') return true;  // non-alpha chars -> pass
        int idx = c - L'a';

        if (!current->children[idx]) {
            return false;  // word not in dictionary
        }
        current = current->children[idx];
    }
    return current->is_word;
}

// scan_text -- walk through the raw text and identify all
// misspelled words. Builds the error list used by the renderer.

void SpellChecker::scan_text(const wchar_t* text, int text_len) {
    m_errors.clear();

    if (!m_loaded || !text || text_len <= 0) return;

    int i = 0;
    while (i < text_len) {
        // skip non-alpha characters
        if (!is_alpha(text[i])) {
            i++;
            continue;
        }

        // found the start of a word
        int word_start = i;
        while (i < text_len && is_alpha(text[i])) {
            i++;
        }
        int word_len = i - word_start;

        // skip very short words (1-2 chars) like "I", "a", "an"
        if (word_len <= 2) continue;

        // check if this word is in the dictionary
        if (!check_word(text + word_start, word_len)) {
            SpellError err;
            err.start = word_start;
            err.end = word_start + word_len;
            m_errors.push_back(err);
        }
    }
}

// Accessors

const SpellErrorArray& SpellChecker::get_errors() const {
    return m_errors;
}

bool SpellChecker::is_loaded() const {
    return m_loaded;
}

// SearchEngine implementation

// Constructor
SearchEngine::SearchEngine()
    : m_history_count(0)
    , m_active(false) {
    m_current_term[0] = L'\0';
}

// Destructor
SearchEngine::~SearchEngine() {}

// search -- perform a case-insensitive search through the
// document's raw text. Stores all matches and updates history.

// Search for query in document text
void SearchEngine::search(const Document* doc, const wchar_t* term) {
    m_matches.clear();
    m_active = false;

    if (!doc || !term) return;

    int term_len = str_len(term);
    if (term_len == 0) return;

    // save the search term
    str_ncpy(m_current_term, term, 255);
    m_current_term[255] = L'\0';

    const wchar_t* text = doc->get_raw_text();
    int text_len = doc->get_raw_length();

    // do a case-insensitive scan for all occurrences
    for (int i = 0; i <= text_len - term_len; i++) {
        bool match = true;
        for (int j = 0; j < term_len; j++) {
            if (to_lower(text[i + j]) != to_lower(term[j])) {
                match = false;
                break;
            }
        }
        if (match) {
            SearchMatch m;
            m.raw_offset = i;
            m.length = term_len;
            m_matches.push_back(m);
        }
    }

    m_active = true;

    // update the search history
    // first check if this term is already in history
    bool found_in_history = false;
    for (int i = 0; i < m_history_count; i++) {
        if (str_cmp_i(m_history[i].term, term) == 0) {
            // update the match count
            m_history[i].match_count = m_matches.size();
            found_in_history = true;
            break;
        }
    }

    if (!found_in_history) {
        if (m_history_count < 5) {
            // add a new entry
            str_ncpy(m_history[m_history_count].term, term, 255);
            m_history[m_history_count].term[255] = L'\0';
            m_history[m_history_count].match_count = m_matches.size();
            m_history_count++;
        }
        else {
            // shift older entries out and add at the end
            for (int i = 0; i < 4; i++) {
                str_cpy(m_history[i].term, m_history[i + 1].term);
                m_history[i].match_count = m_history[i + 1].match_count;
            }
            str_ncpy(m_history[4].term, term, 255);
            m_history[4].term[255] = L'\0';
            m_history[4].match_count = m_matches.size();
        }
    }
}

// clear -- remove all active search highlights

// Clear search results
void SearchEngine::clear() {
    m_matches.clear();
    m_active = false;
    m_current_term[0] = L'\0';
}

// is_highlighted -- check if a raw text offset falls within
// any of the current search matches

bool SearchEngine::is_highlighted(int offset) const {
    if (!m_active) return false;
    for (int i = 0; i < m_matches.size(); i++) {
        if (offset >= m_matches[i].raw_offset &&
            offset < m_matches[i].raw_offset + m_matches[i].length) {
            return true;
        }
    }
    return false;
}

// Accessors

const SearchMatchArray& SearchEngine::get_matches() const {
    return m_matches;
}

// Get number of matches found
int SearchEngine::get_match_count() const {
    return m_matches.size();
}

const SearchHistoryEntry* SearchEngine::get_history() const {
    return m_history;
}

int SearchEngine::get_history_count() const {
    return m_history_count;
}

const wchar_t* SearchEngine::get_current_term() const {
    return m_current_term;
}

bool SearchEngine::is_active() const {
    return m_active;
}

// Statistics implementation

// Constructor
Statistics::Statistics()
    : m_chars_with_spaces(0)
    , m_chars_without_spaces(0)
    , m_word_count(0)
    , m_sentence_count(0)
    , m_page_count(0)
    , m_reading_time_sec(0) {
}

// Destructor
Statistics::~Statistics() {}

// compute -- scan the document's raw text buffer and calculate
// all statistics from scratch. Called after every edit.

// Calculate statistics for document
void Statistics::compute(const Document* doc) {
    // reset everything
    m_chars_with_spaces = 0;
    m_chars_without_spaces = 0;
    m_word_count = 0;
    m_sentence_count = 0;
    m_page_count = 0;
    m_reading_time_sec = 0;

    if (!doc) return;

    const wchar_t* text = doc->get_raw_text();
    int len = doc->get_raw_length();

    m_chars_with_spaces = len;
    m_page_count = doc->get_page_count();

    bool in_word = false;

    for (int i = 0; i < len; i++) {
        wchar_t c = text[i];

        // characters without spaces
        if (!is_space(c)) {
            m_chars_without_spaces++;
        }

        // word counting: a word starts when we transition from
        // non-alpha to alpha (or from space/newline to non-space)
        if (is_alpha(c) || is_digit(c)) {
            if (!in_word) {
                m_word_count++;
                in_word = true;
            }
        }
        else {
            in_word = false;
        }

        // sentence counting: count sentence-ending punctuation
        // (period, question mark, exclamation) but only if followed
        // by a space, newline, or end of text -- avoids counting
        // abbreviations like "Mr." in the middle of text
        if (is_sentence_end(c)) {
            // check the next non-space character
            bool end_of_sentence = false;
            if (i + 1 >= len) {
                end_of_sentence = true;
            }
            else if (is_space(text[i + 1]) || text[i + 1] == L'\n') {
                end_of_sentence = true;
            }
            if (end_of_sentence) {
                m_sentence_count++;
            }
        }
    }

    // estimated reading time at 200 words per minute
    if (m_word_count > 0) {
        // time in seconds = (words / 200) * 60
        m_reading_time_sec = (m_word_count * 60) / 200;
        if (m_reading_time_sec == 0 && m_word_count > 0) {
            m_reading_time_sec = 1;  // at least 1 second if there are words
        }
    }
}

// Accessors

int Statistics::get_chars_with_spaces() const { return m_chars_with_spaces; }
int Statistics::get_chars_without_spaces() const { return m_chars_without_spaces; }
// Get word count
int Statistics::get_word_count() const { return m_word_count; }
// Get sentence count
int Statistics::get_sentence_count() const { return m_sentence_count; }
int Statistics::get_page_count() const { return m_page_count; }
int Statistics::get_reading_time_sec() const { return m_reading_time_sec; }

// TableOfContents implementation

// Constructor
TableOfContents::TableOfContents() {}
// Destructor
TableOfContents::~TableOfContents() {}

// score_paragraph -- heuristic scoring for heading detection.
//
// Higher scores indicate a stronger likelihood that the
// paragraph is a heading/chapter title. Criteria:
//   +3 if all-caps or title case
//   +2 if starts with "chapter" or a roman numeral
//   +2 if text is short (under 60 chars)
//   +1 if preceded by blank line (checked separately)
//   -2 if contains sentence-ending punctuation mid-text

int TableOfContents::score_paragraph(const wchar_t* text, int len) const {
    if (len == 0) return 0;

    int score = 0;

    // check if all-caps
    bool all_caps = true;
    int alpha_count = 0;
    for (int i = 0; i < len; i++) {
        if (is_alpha(text[i])) {
            alpha_count++;
            if (!is_upper(text[i])) {
                all_caps = false;
            }
        }
    }
    if (all_caps && alpha_count > 0) score += 3;

    // check title case (first letter of each word is uppercase)
    bool title_case = true;
    bool word_start = true;
    for (int i = 0; i < len; i++) {
        if (is_alpha(text[i])) {
            if (word_start && !is_upper(text[i])) {
                // allow lowercase for short words (articles, prepositions)
                wchar_t word_buf[16];
                int wl = 0;
                for (int j = i; j < len && is_alpha(text[j]) && wl < 15; j++) {
                    word_buf[wl++] = text[j];
                }
                word_buf[wl] = L'\0';
                if (!is_stop_word(word_buf)) {
                    title_case = false;
                }
            }
            word_start = false;
        }
        else {
            word_start = true;
        }
    }
    if (title_case && !all_caps && alpha_count > 0) score += 2;

    // check for "chapter" or "CHAPTER" at the start
    if (len >= 7) {
        wchar_t prefix[8];
        for (int i = 0; i < 7; i++) {
            prefix[i] = to_lower(text[i]);
        }
        prefix[7] = L'\0';
        if (str_cmp(prefix, L"chapter") == 0) {
            score += 2;
        }
    }

    // check for roman numeral pattern at start (I, II, III, IV, V, etc.)
    if (len >= 1) {
        int ri = 0;
        while (ri < len && (text[ri] == L'I' || text[ri] == L'V' ||
            text[ri] == L'X' || text[ri] == L'L' ||
            text[ri] == L'C' || text[ri] == L'D' ||
            text[ri] == L'M')) {
            ri++;
        }
        // if the first part is all roman numeral chars and ends with
        // space or period, count it
        if (ri > 0 && ri < len && (text[ri] == L' ' || text[ri] == L'.')) {
            score += 2;
        }
    }

    // short text is more likely a heading
    if (len < 60) score += 2;
    if (len < 30) score += 1;

    // penalize if it contains sentence-ending punctuation
    // (headings usually don't have periods mid-text)
    for (int i = 0; i < len - 1; i++) {
        if (is_sentence_end(text[i]) && is_space(text[i + 1])) {
            score -= 2;
            break;
        }
    }

    return score;
}

// extract_fallback_title -- take first 4 words, drop trailing
// stop words, and capitalize the first letter of each word.

void TableOfContents::extract_fallback_title(const wchar_t* text, int len,
    wchar_t* out, int out_size) const {
    // extract up to 4 words
    int word_count = 0;
    int out_pos = 0;
    int i = 0;

    while (i < len && word_count < 4) {
        // skip spaces
        while (i < len && is_space(text[i])) i++;
        if (i >= len) break;

        // start of a word
        int word_start = i;
        while (i < len && !is_space(text[i])) i++;
        int word_len = i - word_start;

        // add space before word (except first)
        if (word_count > 0 && out_pos < out_size - 1) {
            out[out_pos++] = L' ';
        }

        // copy the word with first letter capitalized
        for (int j = 0; j < word_len && out_pos < out_size - 1; j++) {
            if (j == 0) {
                out[out_pos++] = to_upper(text[word_start + j]);
            }
            else {
                out[out_pos++] = text[word_start + j];
            }
        }

        word_count++;
    }
    out[out_pos] = L'\0';

    // remove trailing stop words
    // work backwards to find the last space, check the last word
    while (out_pos > 0) {
        // find the last word
        int last_space = -1;
        for (int k = out_pos - 1; k >= 0; k--) {
            if (out[k] == L' ') {
                last_space = k;
                break;
            }
        }

        const wchar_t* last_word = (last_space >= 0) ? &out[last_space + 1] : out;
        if (is_stop_word(last_word)) {
            if (last_space >= 0) {
                out[last_space] = L'\0';
                out_pos = last_space;
            }
            else {
                // the entire output is a stop word -- keep it
                break;
            }
        }
        else {
            break;
        }
    }
}

// get_first_paragraph -- extract the first line(s) of text
// from a page's first column as the candidate heading text.

int TableOfContents::get_first_paragraph(const Document* doc, int page_index,
    wchar_t* out_buf, int buf_size) const {
    if (!doc || page_index < 0 || page_index >= doc->get_page_count()) {
        out_buf[0] = L'\0';
        return 0;
    }

    const Page& page = doc->get_page(page_index);
    if (page.get_num_columns() == 0) {
        out_buf[0] = L'\0';
        return 0;
    }

    const Column& col = page.get_column(0);
    if (col.get_used_lines() == 0) {
        out_buf[0] = L'\0';
        return 0;
    }

    // take the first line as the paragraph candidate
    const Line& first_line = col.get_line(0);
    int len = first_line.get_length();
    if (len >= buf_size) len = buf_size - 1;

    const wchar_t* text = first_line.get_text();
    for (int i = 0; i < len; i++) {
        out_buf[i] = text[i];
    }
    out_buf[len] = L'\0';
    return len;
}

// is_preceded_by_blank -- check if the first line of a page
// would have been preceded by a blank line. This is an
// approximation: we check if the last line of the previous
// page's last column is empty or very short.

bool TableOfContents::is_preceded_by_blank(const Document* doc,
    int page_index) const {
    if (page_index <= 0 || !doc) return true;  // first page counts as "preceded"

    // check the previous page's last column's last line
    const Page& prev_page = doc->get_page(page_index - 1);
    if (prev_page.get_num_columns() == 0) return true;
    int last_col = prev_page.get_num_columns() - 1;
    const Column& col = prev_page.get_column(last_col);

    if (col.get_used_lines() == 0) return true;

    // if the column isn't fully used, there is likely whitespace
    if (col.get_used_lines() < col.get_max_lines()) return true;

    return false;
}

// generate -- scan all pages and build ToC entries using
// the scoring heuristic.

// Generate table of contents from document
void TableOfContents::generate(const Document* doc) {
    m_entries.clear();

    if (!doc) return;

    int total_pages = doc->get_page_count();
    int score_threshold = 2;  // minimum score to be considered a heading

    for (int p = 0; p < total_pages; p++) {
        wchar_t para_buf[512];
        int para_len = get_first_paragraph(doc, p, para_buf, 512);

        if (para_len == 0) continue;

        int score = score_paragraph(para_buf, para_len);

        // bonus for being preceded by a blank line
        if (is_preceded_by_blank(doc, p)) {
            score += 1;
        }

        if (score >= score_threshold) {
            TocEntry entry;
            entry.page_number = p + 1;
            entry.column_number = 1;

            // if the score is high, use the paragraph text directly
            if (score >= 4) {
                // use the text as-is (truncate if needed)
                int copy_len = para_len;
                if (copy_len > 255) copy_len = 255;
                for (int i = 0; i < copy_len; i++) {
                    entry.title[i] = para_buf[i];
                }
                entry.title[copy_len] = L'\0';
            }
            else {
                // use the fallback title extraction
                extract_fallback_title(para_buf, para_len, entry.title, 256);
            }

            m_entries.push_back(entry);
        }
    }

    // if no entries were found, create a default entry for page 1
    if (m_entries.size() == 0 && total_pages > 0) {
        TocEntry entry;
        entry.page_number = 1;
        entry.column_number = 1;

        wchar_t para_buf[512];
        int para_len = get_first_paragraph(doc, 0, para_buf, 512);
        if (para_len > 0) {
            extract_fallback_title(para_buf, para_len, entry.title, 256);
        }
        else {
            str_cpy(entry.title, L"Untitled");
        }

        m_entries.push_back(entry);
    }
}

// Accessors

const TocEntryArray& TableOfContents::get_entries() const {
    return m_entries;
}

// Get number of TOC entries
int TableOfContents::get_entry_count() const {
    return m_entries.size();
}

// AutoSave implementation

// Constructor
AutoSave::AutoSave()
    : m_interval_ms(60000)
    , m_save_index(0)
    , m_enabled(false)
    , m_tick_count(0)
    , m_full_save_every(5) {
    m_base_dir[0] = L'\0';
}

// Destructor
AutoSave::~AutoSave() {}

// init -- set the autosave directory and interval

void AutoSave::init(const wchar_t* base_dir, int interval_ms) {
    if (base_dir) {
        str_ncpy(m_base_dir, base_dir, 259);
        m_base_dir[259] = L'\0';
    }
    m_interval_ms = interval_ms;
    m_enabled = true;
    m_save_index = 0;
    m_tick_count = 0;
}

// build_file_path -- construct a path like "autosave\save_03.txt"
// for the given rotating slot number (full snapshot).

void AutoSave::build_file_path(int slot, wchar_t* out, int out_size) const {
    str_cpy(out, m_base_dir);
    str_cat(out, L"\\save_");

    wchar_t num[4];
    if (slot < 10) {
        num[0] = L'0';
        int_to_str(slot, &num[1]);
    }
    else {
        int_to_str(slot, num);
    }
    str_cat(out, num);
    str_cat(out, L".txt");
}

// build_delta_path -- construct a path like "autosave\delta_03.bin"
// for the given rotating slot number (delta file).

void AutoSave::build_delta_path(int slot, wchar_t* out, int out_size) const {
    str_cpy(out, m_base_dir);
    str_cat(out, L"\\delta_");

    wchar_t num[4];
    if (slot < 10) {
        num[0] = L'0';
        int_to_str(slot, &num[1]);
    }
    else {
        int_to_str(slot, num);
    }
    str_cat(out, num);
    str_cat(out, L".bin");
}

// on_timer -- called from WM_TIMER. Alternates between delta
// saves and full snapshots. Every m_full_save_every ticks,
// a full snapshot is written; otherwise only deltas are saved.

void AutoSave::on_timer(Document* doc) {
    if (!m_enabled || !doc || !doc->is_modified()) return;

    m_tick_count++;

    // every Nth tick, do a full snapshot to keep things recoverable
    if (m_tick_count % m_full_save_every == 0) {
        // full snapshot to rotating slot
        wchar_t path[300];
        build_file_path(m_save_index, path, 300);

        const wchar_t* text = doc->get_raw_text();
        int text_len = doc->get_raw_length();

        HANDLE hFile = CreateFileW(
            path, GENERIC_WRITE, 0, nullptr,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

        if (hFile != INVALID_HANDLE_VALUE) {
            unsigned char bom[2] = { 0xFF, 0xFE };
            DWORD written = 0;
            WriteFile(hFile, bom, 2, &written, nullptr);

            DWORD bytes_to_write = text_len * sizeof(wchar_t);
            WriteFile(hFile, text, bytes_to_write, &written, nullptr);
            CloseHandle(hFile);
        }

        // clear the delta log since we have a fresh full snapshot
        doc->clear_deltas();

        m_save_index = (m_save_index + 1) % 10;
    }
    else {
        // delta save -- only write the changes since last save
        save_deltas(doc);
    }
}

// save_deltas -- write the accumulated edit deltas to a binary
// file. Each delta records the operation type, offset, and
// the text that was inserted or deleted.
//
// Binary format:
//   [4 bytes] delta_count (int)
//   For each delta:
//     [1 byte]  type (0 = INSERT, 1 = DELETE)
//     [4 bytes] offset (int)
//     [4 bytes] text_len (int)
//     [text_len * 2 bytes] wchar_t text data

void AutoSave::save_deltas(Document* doc) {
    if (!doc) return;

    const EditDeltaArray& deltas = doc->get_deltas();
    int count = deltas.size();

    // nothing to save if no edits happened
    if (count == 0) return;

    wchar_t path[300];
    build_delta_path(m_save_index, path, 300);

    HANDLE hFile = CreateFileW(
        path, GENERIC_WRITE, 0, nullptr,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE) return;

    DWORD written = 0;

    // write delta count
    WriteFile(hFile, &count, sizeof(int), &written, nullptr);

    // write each delta
    for (int i = 0; i < count; i++) {
        const EditDelta& d = deltas[i];

        // type: 1 byte (0=INSERT, 1=DELETE)
        unsigned char type_byte = (d.type == EditDelta::DELTA_INSERT) ? 0 : 1;
        WriteFile(hFile, &type_byte, 1, &written, nullptr);

        // offset: 4 bytes
        WriteFile(hFile, &d.offset, sizeof(int), &written, nullptr);

        // text_len: 4 bytes
        WriteFile(hFile, &d.text_len, sizeof(int), &written, nullptr);

        // text data: text_len * sizeof(wchar_t) bytes
        DWORD text_bytes = d.text_len * sizeof(wchar_t);
        WriteFile(hFile, d.text, text_bytes, &written, nullptr);
    }

    CloseHandle(hFile);

    // clear deltas after saving them -- they are now on disk
    doc->clear_deltas();

    m_save_index = (m_save_index + 1) % 10;
}

// full_save -- explicit save to a specific file path.
// Writes the entire document content and clears the delta log.

void AutoSave::full_save(Document* doc, const wchar_t* file_path) {
    if (!doc || !file_path) return;

    const wchar_t* text = doc->get_raw_text();
    int text_len = doc->get_raw_length();

    HANDLE hFile = CreateFileW(
        file_path, GENERIC_WRITE, 0, nullptr,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile != INVALID_HANDLE_VALUE) {
        unsigned char bom[2] = { 0xFF, 0xFE };
        DWORD written = 0;
        WriteFile(hFile, bom, 2, &written, nullptr);

        DWORD bytes_to_write = text_len * sizeof(wchar_t);
        WriteFile(hFile, text, bytes_to_write, &written, nullptr);

        CloseHandle(hFile);
    }

    // full save resets the delta log -- we have a clean baseline
    doc->clear_deltas();
    doc->set_modified(false);
}

// load_file -- read a file's contents into a document.
// Uses WinAPI CreateFileW/ReadFile.

bool AutoSave::load_file(Document* doc, const wchar_t* file_path) {
    if (!doc || !file_path) return false;

    HANDLE hFile = CreateFileW(
        file_path, GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE) return false;

    DWORD file_size = GetFileSize(hFile, nullptr);
    if (file_size == INVALID_FILE_SIZE || file_size == 0) {
        CloseHandle(hFile);
        return false;
    }

    unsigned char* raw_bytes = new unsigned char[file_size];
    DWORD bytes_read = 0;
    BOOL ok = ReadFile(hFile, raw_bytes, file_size, &bytes_read, nullptr);
    CloseHandle(hFile);

    if (!ok || bytes_read == 0) {
        delete[] raw_bytes;
        return false;
    }

    // check for UTF-16 BOM (FF FE)
    int offset = 0;
    if (bytes_read >= 2 && raw_bytes[0] == 0xFF && raw_bytes[1] == 0xFE) {
        offset = 2;
    }

    int wchar_count = (bytes_read - offset) / sizeof(wchar_t);
    if (wchar_count <= 0) {
        delete[] raw_bytes;
        return false;
    }

    const wchar_t* wide_data = (const wchar_t*)(raw_bytes + offset);
    doc->insert_text(wide_data, wchar_count);

    delete[] raw_bytes;

    doc->set_file_path(file_path);
    doc->set_modified(false);
    doc->clear_deltas();  // loading is not an "edit" -- clear any deltas from insert_text
    doc->reflow();

    return true;
}

// load_with_deltas -- reconstruct a document from a base
// snapshot file plus a delta file. Reads the base text first,
// then replays each delta (insert/delete) in order.

bool AutoSave::load_with_deltas(Document* doc, const wchar_t* base_path,
    const wchar_t* delta_path) {
    if (!doc || !base_path) return false;

    // step 1: load the base snapshot
    if (!load_file(doc, base_path)) return false;

    // step 2: if no delta file, we are done
    if (!delta_path) return true;

    HANDLE hFile = CreateFileW(
        delta_path, GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE) {
        // no delta file is ok -- just use the base snapshot
        return true;
    }

    DWORD file_size = GetFileSize(hFile, nullptr);
    if (file_size == INVALID_FILE_SIZE || file_size < sizeof(int)) {
        CloseHandle(hFile);
        return true;  // empty or corrupt delta file, use base only
    }

    // read entire delta file into memory
    unsigned char* buf = new unsigned char[file_size];
    DWORD bytes_read = 0;
    BOOL ok = ReadFile(hFile, buf, file_size, &bytes_read, nullptr);
    CloseHandle(hFile);

    if (!ok || bytes_read < sizeof(int)) {
        delete[] buf;
        return true;
    }

    // parse the delta file
    int pos = 0;

    // read delta count
    int delta_count = 0;
    for (int b = 0; b < 4 && pos < (int)bytes_read; b++) {
        ((unsigned char*)&delta_count)[b] = buf[pos++];
    }

    // replay each delta
    for (int i = 0; i < delta_count && pos < (int)bytes_read; i++) {
        // type: 1 byte
        unsigned char type_byte = buf[pos++];

        // offset: 4 bytes
        int d_offset = 0;
        for (int b = 0; b < 4 && pos < (int)bytes_read; b++) {
            ((unsigned char*)&d_offset)[b] = buf[pos++];
        }

        // text_len: 4 bytes
        int d_len = 0;
        for (int b = 0; b < 4 && pos < (int)bytes_read; b++) {
            ((unsigned char*)&d_len)[b] = buf[pos++];
        }

        // text data: d_len * sizeof(wchar_t) bytes
        if (d_len <= 0 || d_len > 100000) break;  // sanity check

        int text_bytes = d_len * (int)sizeof(wchar_t);
        if (pos + text_bytes > (int)bytes_read) break;

        // copy text with proper alignment (buf may not be wchar_t-aligned)
        wchar_t* d_text = new wchar_t[d_len + 1];
        for (int j = 0; j < d_len; j++) {
            unsigned char lo = buf[pos + j * 2];
            unsigned char hi = buf[pos + j * 2 + 1];
            d_text[j] = (wchar_t)(lo | (hi << 8));
        }
        d_text[d_len] = L'\0';
        pos += text_bytes;

        // apply the delta to reconstruct the document state
        if (type_byte == 0) {
            // INSERT: place cursor at offset and insert text
            doc->set_cursor_from_offset(d_offset);
            doc->insert_text(d_text, d_len);
        }
        else {
            // DELETE: select the range and delete
            doc->set_selection(d_offset, d_offset + d_len);
            doc->delete_selection();
        }

        delete[] d_text;
    }

    delete[] buf;

    // clear deltas generated by the replay -- they are not real edits
    doc->clear_deltas();
    doc->set_modified(false);
    doc->reflow();

    return true;
}

// Accessors

int AutoSave::get_interval() const { return m_interval_ms; }
void AutoSave::set_interval(int ms) { m_interval_ms = ms; }
void AutoSave::set_enabled(bool val) { m_enabled = val; }
bool AutoSave::is_enabled() const { return m_enabled; }
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif


// The one global state object shared across the application

EditorState g_state;

// Helper: get the currently active document (or nullptr)

static Document* get_active_doc() {
    return Document::get_instance(g_state.active_tab);
}

// Create the startup configuration dialog controls.
// These are child windows of the main window, shown before
// the user enters editing mode.

static void create_config_controls(HWND hwnd, HINSTANCE hInstance) {
    // calculate center based on actual window size
    RECT rc;
    GetClientRect(hwnd, &rc);
    int center_x = (rc.right - rc.left) / 2;
    int cy = 280;  // start y position (more space below title)

    // label+input group dimensions for centering
    int label_width = 180;
    int input_width = 80;
    int group_gap = 12;
    int group_width = label_width + group_gap + input_width;
    int group_x = center_x - group_width / 2;

    // title label
    g_state.config_label_title = CreateWindowExW(
        0, L"STATIC", L"THE ARCANUM EDITOR",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        center_x - 200, cy - 180, 400, 40,
        hwnd, (HMENU)ID_LABEL_TITLE, hInstance, nullptr);

    // subtitle
    CreateWindowExW(
        0, L"STATIC", L"Configure your manuscript layout:",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        center_x - 200, cy - 125, 400, 25,
        hwnd, nullptr, hInstance, nullptr);

    // columns per page - labels left-aligned
    CreateWindowExW(
        0, L"STATIC", L"Columns per page:",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        group_x, cy, label_width, 25,
        hwnd, (HMENU)ID_LABEL_COLS, hInstance, nullptr);

    g_state.config_edit_cols = CreateWindowExW(
        WS_EX_CLIENTEDGE, L"EDIT", L"2",
        WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER,
        group_x + label_width + group_gap, cy, input_width, 25,
        hwnd, (HMENU)ID_EDIT_COLS, hInstance, nullptr);

    // lines per column
    CreateWindowExW(
        0, L"STATIC", L"Lines per column:",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        group_x, cy + 50, label_width, 25,
        hwnd, (HMENU)ID_LABEL_LINES, hInstance, nullptr);

    g_state.config_edit_lines = CreateWindowExW(
        WS_EX_CLIENTEDGE, L"EDIT", L"20",
        WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER,
        group_x + label_width + group_gap, cy + 50, input_width, 25,
        hwnd, (HMENU)ID_EDIT_LINES, hInstance, nullptr);

    // characters per line
    CreateWindowExW(
        0, L"STATIC", L"Characters per line:",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        group_x, cy + 100, label_width, 25,
        hwnd, (HMENU)ID_LABEL_CHARS, hInstance, nullptr);

    g_state.config_edit_chars = CreateWindowExW(
        WS_EX_CLIENTEDGE, L"EDIT", L"80",
        WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER,
        group_x + label_width + group_gap, cy + 100, input_width, 25,
        hwnd, (HMENU)ID_EDIT_CHARS, hInstance, nullptr);

    // start button - centered independently
    g_state.config_btn_start = CreateWindowExW(
        0, L"BUTTON", L"Start Editing",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        center_x - 65, cy + 170, 130, 40,
        hwnd, (HMENU)ID_BTN_START, hInstance, nullptr);
}

// Read config values and enter editing mode.
// Called when the user clicks "Start Editing".

static void enter_editing_mode(HWND hwnd) {
    // read values from the edit controls
    wchar_t buf[16];
    int cols = DEFAULT_COLS_PER_PAGE;
    int lines = DEFAULT_LINES_PER_COL;
    int chars = DEFAULT_CHARS_PER_LINE;

    // GetWindowTextW is not in our allowed list, so we use
    // SendMessage with WM_GETTEXT which is always available
    SendMessageW(g_state.config_edit_cols, WM_GETTEXT, 16, (LPARAM)buf);
    int val = str_to_int(buf);
    if (val >= 1 && val <= 10) cols = val;

    SendMessageW(g_state.config_edit_lines, WM_GETTEXT, 16, (LPARAM)buf);
    val = str_to_int(buf);
    if (val >= 5 && val <= 100) lines = val;

    SendMessageW(g_state.config_edit_chars, WM_GETTEXT, 16, (LPARAM)buf);
    val = str_to_int(buf);
    if (val >= 10 && val <= 200) chars = val;

    // destroy config controls -- we are done with them
    DestroyWindow(g_state.config_label_title);
    DestroyWindow(g_state.config_edit_cols);
    DestroyWindow(g_state.config_edit_lines);
    DestroyWindow(g_state.config_edit_chars);
    DestroyWindow(g_state.config_btn_start);

    // also destroy the labels and subtitle (enumerate child windows
    // is overkill -- we just hide them by destroying known IDs)
    HWND child = nullptr;
    // destroy all remaining STATIC children from config
    while ((child = FindWindowExW(hwnd, nullptr, L"STATIC", nullptr)) != nullptr) {
        DestroyWindow(child);
    }

    // create the first document
    Document* doc = Document::create(cols, lines, chars);
    if (!doc) return;  // should never fail on first create

    g_state.active_tab = doc->get_tab_index();
    g_state.editing_mode = true;

    // initialize subsystems
    g_state.renderer = new Renderer();
    g_state.spell_checker = new SpellChecker();
    g_state.search_engine = new SearchEngine();
    g_state.toc = new TableOfContents();
    g_state.auto_save = new AutoSave();
    g_state.stats = new Statistics();

    // set up the renderer's font -- scale to fit the page layout
    HDC hdc = GetDC(hwnd);
    RECT client_rect;
    GetClientRect(hwnd, &client_rect);
    int win_width = client_rect.right - client_rect.left;
    g_state.renderer->init_for_layout(hdc, win_width, cols, chars);
    ReleaseDC(hwnd, hdc);

    // reset scroll position
    g_state.scroll_y = 0;

    // load the dictionary in the background
    g_state.spell_checker->load_dictionary(L"OPTED-Dictionary.csv");

    // start the auto-save timer (default 60 seconds)
    g_state.auto_save->init(L"autosave", 60000);
    SetTimer(hwnd, TIMER_AUTOSAVE, 60000, nullptr);

    // start cursor blink timer (500ms)
    SetTimer(hwnd, TIMER_CURSOR_BLINK, 500, nullptr);

    // initial reflow and stats
    doc->reflow();
    g_state.stats->compute(doc);

    // repaint everything
    InvalidateRect(hwnd, nullptr, FALSE);
}

// Handle clipboard operations

static void handle_copy(HWND hwnd) {
    Document* doc = get_active_doc();
    if (!doc || !doc->has_selection()) return;

    wchar_t* text = doc->get_selected_text();
    if (!text) return;

    int len = str_len(text);
    if (len == 0) {
        delete[] text;
        return;
    }

    // put text on the clipboard using the allowed WinAPI calls
    if (OpenClipboard(hwnd)) {
        EmptyClipboard();

        // allocate global memory for the text
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (len + 1) * sizeof(wchar_t));
        if (hMem) {
            wchar_t* pMem = (wchar_t*)GlobalLock(hMem);
            if (pMem) {
                str_cpy(pMem, text);
                GlobalUnlock(hMem);
                SetClipboardData(CF_UNICODETEXT, hMem);
            }
        }
        CloseClipboard();
    }

    delete[] text;
}

static void handle_paste(HWND hwnd) {
    Document* doc = get_active_doc();
    if (!doc) return;

    if (OpenClipboard(hwnd)) {
        HGLOBAL hMem = GetClipboardData(CF_UNICODETEXT);
        if (hMem) {
            wchar_t* pMem = (wchar_t*)GlobalLock(hMem);
            if (pMem) {
                int len = str_len(pMem);
                doc->insert_text(pMem, len);
                g_state.stats->compute(doc);
                g_state.spell_checker->scan_text(
                    doc->get_raw_text(), doc->get_raw_length());
            }
            GlobalUnlock(hMem);
        }
        CloseClipboard();
    }

    InvalidateRect(hwnd, nullptr, FALSE);
}

static void handle_cut(HWND hwnd) {
    handle_copy(hwnd);
    Document* doc = get_active_doc();
    if (doc && doc->has_selection()) {
        doc->delete_selection();
        g_state.stats->compute(doc);
        g_state.spell_checker->scan_text(
            doc->get_raw_text(), doc->get_raw_length());
        InvalidateRect(hwnd, nullptr, FALSE);
    }
}

// Show right-click context menu

static void show_context_menu(HWND hwnd, int x, int y) {
    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, IDM_CUT, L"Cut\tCtrl+X");
    AppendMenuW(menu, MF_STRING, IDM_COPY, L"Copy\tCtrl+C");
    AppendMenuW(menu, MF_STRING, IDM_PASTE, L"Paste\tCtrl+V");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, IDM_SEARCH, L"Search\tCtrl+F");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, IDM_ALIGN_LEFT, L"Align Left\tCtrl+L");
    AppendMenuW(menu, MF_STRING, IDM_ALIGN_RIGHT, L"Align Right\tCtrl+R");
    AppendMenuW(menu, MF_STRING, IDM_ALIGN_CENTER, L"Align Center\tCtrl+E");
    AppendMenuW(menu, MF_STRING, IDM_ALIGN_JUSTIFY, L"Justify\tCtrl+J");

    // convert client coordinates to screen coordinates
    POINT pt = { x, y };
    ClientToScreen(hwnd, &pt);

    TrackPopupMenu(menu, TPM_LEFTALIGN | TPM_TOPALIGN,
        pt.x, pt.y, 0, hwnd, nullptr);
    DestroyMenu(menu);
}

// Handle tab switching (Ctrl+Tab / Ctrl+Shift+Tab)

static void switch_tab(bool forward) {
    int count = Document::get_instance_count();
    if (count <= 1) return;

    int current = g_state.active_tab;
    int direction = forward ? 1 : -1;

    // search for the next occupied slot
    for (int i = 1; i <= 10; i++) {
        int next = (current + direction * i + 10) % 10;
        if (Document::get_instance(next) != nullptr) {
            g_state.active_tab = next;
            break;
        }
    }

    // reset scroll position when switching tabs
    g_state.scroll_y = 0;

    InvalidateRect(g_state.hwnd, nullptr, FALSE);
}

// WndProc -- the main window message handler

// Main window message handler
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

        // ---- painting ----
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);

        if (!g_state.editing_mode) {
            // draw the config screen background
            HBRUSH bg = CreateSolidBrush(RGB(20, 20, 40));
            FillRect(hdc, &rect, bg);
            DeleteObject(bg);

            // draw the title text
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(200, 180, 140));
            HFONT title_font = CreateFont(
                36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Consolas");
            HFONT old_font = (HFONT)SelectObject(hdc, title_font);

            RECT title_rect = rect;
            title_rect.bottom = title_rect.top + 80;
            int window_width = rect.right - rect.left;
            ExtTextOutW(hdc, rect.left + window_width / 2 - 180,
                50, 0, nullptr,
                L"Blackwood & Hargrove", 20, nullptr);

            SelectObject(hdc, old_font);
            DeleteObject(title_font);
        }
        else {
            // delegate to the renderer
            Document* doc = get_active_doc();
            if (doc && g_state.renderer) {
                g_state.renderer->paint(
                    hdc, rect, doc,
                    g_state.spell_checker,
                    g_state.search_engine,
                    g_state.stats,
                    g_state.cursor_visible,
                    g_state.active_tab,
                    g_state.search_mode,
                    g_state.search_buffer,
                    g_state.showing_toc,
                    g_state.toc,
                    g_state.showing_search_history,
                    g_state.scroll_y);
            }
        }

        EndPaint(hwnd, &ps);
        return 0;
    }

                 // ---- prevent default background erase to reduce flicker ----
    case WM_ERASEBKGND:
        return 1;

        // ---- button clicks and menu commands ----
    case WM_COMMAND: {
        int cmd = LOWORD(wParam);

        if (cmd == ID_BTN_START) {
            enter_editing_mode(hwnd);
            return 0;
        }

        // context menu commands
        Document* doc = get_active_doc();
        switch (cmd) {
        case IDM_CUT:    handle_cut(hwnd); break;
        case IDM_COPY:   handle_copy(hwnd); break;
        case IDM_PASTE:  handle_paste(hwnd); break;
        case IDM_SEARCH:
            g_state.search_mode = true;
            g_state.search_buffer_len = 0;
            g_state.search_buffer[0] = L'\0';
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        case IDM_ALIGN_LEFT:
            if (doc) doc->set_alignment(ALIGN_LEFT);
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        case IDM_ALIGN_RIGHT:
            if (doc) doc->set_alignment(ALIGN_RIGHT);
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        case IDM_ALIGN_CENTER:
            if (doc) doc->set_alignment(ALIGN_CENTER);
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        case IDM_ALIGN_JUSTIFY:
            if (doc) doc->set_alignment(ALIGN_JUSTIFIED);
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        }
        return 0;
    }

                   // ---- keyboard: character input ----
    case WM_CHAR: {
        if (!g_state.editing_mode) return 0;

        wchar_t ch = (wchar_t)wParam;
        Document* doc = get_active_doc();
        if (!doc) return 0;

        // if in search mode, route keypresses to the search buffer
        if (g_state.search_mode) {
            if (ch == 27) {
                // escape: exit search mode
                g_state.search_mode = false;
                g_state.search_engine->clear();
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            else if (ch == 13) {
                // enter: perform the search
                g_state.search_engine->search(doc, g_state.search_buffer);
                g_state.search_mode = false;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            else if (ch == 8) {
                // backspace in search buffer
                if (g_state.search_buffer_len > 0) {
                    g_state.search_buffer_len--;
                    g_state.search_buffer[g_state.search_buffer_len] = L'\0';
                }
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            else if (ch >= 32 && g_state.search_buffer_len < 254) {
                // add character to search buffer
                g_state.search_buffer[g_state.search_buffer_len++] = ch;
                g_state.search_buffer[g_state.search_buffer_len] = L'\0';
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }

        // normal editing: printable characters and enter
        if (ch == 8) {
            // backspace -- but not if Ctrl is held (Ctrl+H generates ch==8)
            if (!(GetKeyState(VK_CONTROL) & 0x8000)) {
                doc->delete_char_before();
            }
            else {
                return 0;  // Ctrl+H already handled in WM_KEYDOWN
            }
        }
        else if (ch == 13) {
            // enter key -> newline
            doc->insert_char(L'\n');
        }
        else if (ch == 27) {
            // escape: close any overlays
            g_state.showing_toc = false;
            g_state.showing_search_history = false;
            g_state.search_engine->clear();
        }
        else if (ch >= 32) {
            // printable character
            doc->insert_char(ch);
        }
        else {
            return 0;  // ignore other control chars
        }

        // update stats and spell check after edit
        g_state.stats->compute(doc);
        if (g_state.spell_checker->is_loaded()) {
            g_state.spell_checker->scan_text(
                doc->get_raw_text(), doc->get_raw_length());
        }

        g_state.cursor_visible = true;  // always show cursor after typing
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }

                // ---- keyboard: virtual key handling ----
    case WM_KEYDOWN: {
        if (!g_state.editing_mode) return 0;

        Document* doc = get_active_doc();
        if (!doc) return 0;

        bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;

        // if in search mode, only handle escape and enter (via WM_CHAR)
        if (g_state.search_mode) return 0;

        switch (wParam) {
        case VK_LEFT:
            doc->clear_selection();
            doc->move_cursor_left();
            break;
        case VK_RIGHT:
            doc->clear_selection();
            doc->move_cursor_right();
            break;
        case VK_UP:
            doc->clear_selection();
            doc->move_cursor_up();
            break;
        case VK_DOWN:
            doc->clear_selection();
            doc->move_cursor_down();
            break;
        case VK_HOME:
            doc->move_cursor_home();
            break;
        case VK_END:
            doc->move_cursor_end();
            break;
        case VK_PRIOR:  // page up
            doc->move_cursor_page_up();
            break;
        case VK_NEXT:   // page down
            doc->move_cursor_page_down();
            break;
        case VK_DELETE:
            doc->delete_char_at();
            g_state.stats->compute(doc);
            if (g_state.spell_checker->is_loaded()) {
                g_state.spell_checker->scan_text(
                    doc->get_raw_text(), doc->get_raw_length());
            }
            break;
        case VK_TAB:
            if (ctrl && shift) {
                switch_tab(false);  // backward
            }
            else if (ctrl) {
                switch_tab(true);   // forward
            }
            else {
                // insert tab as spaces (4 spaces)
                doc->insert_text(L"    ", 4);
                g_state.stats->compute(doc);
            }
            break;

            // Ctrl key shortcuts
        default:
            if (ctrl) {
                switch (wParam) {
                case 'S':  // Ctrl+S: save
                    if (doc->get_file_path()[0] != L'\0') {
                        g_state.auto_save->full_save(doc, doc->get_file_path());
                    }
                    else {
                        // save to a default path
                        g_state.auto_save->full_save(doc, L"manuscript.txt");
                        doc->set_file_path(L"manuscript.txt");
                    }
                    doc->set_modified(false);
                    break;

                case 'N': {  // Ctrl+N: new tab
                    Document* active = get_active_doc();
                    int cols = active ? active->get_cols_per_page() : DEFAULT_COLS_PER_PAGE;
                    int lines = active ? active->get_lines_per_col() : DEFAULT_LINES_PER_COL;
                    int chars = active ? active->get_chars_per_line() : DEFAULT_CHARS_PER_LINE;
                    Document* new_doc = Document::create(cols, lines, chars);
                    if (new_doc) {
                        g_state.active_tab = new_doc->get_tab_index();
                        g_state.stats->compute(new_doc);
                    }
                    break;
                }

                case 'W':  // Ctrl+W: close tab
                    if (Document::get_instance_count() > 1) {
                        Document::close(doc);
                        // switch to another open tab
                        for (int i = 0; i < 10; i++) {
                            if (Document::get_instance(i)) {
                                g_state.active_tab = i;
                                break;
                            }
                        }
                        Document* new_active = get_active_doc();
                        if (new_active) g_state.stats->compute(new_active);
                    }
                    break;

                case 'F':  // Ctrl+F: search
                    g_state.search_mode = true;
                    g_state.search_buffer_len = 0;
                    g_state.search_buffer[0] = L'\0';
                    break;

                case 'H':  // Ctrl+H: show search history
                    g_state.showing_search_history = !g_state.showing_search_history;
                    g_state.showing_toc = false;
                    break;

                case 'T':  // Ctrl+T: show table of contents
                    g_state.toc->generate(doc);
                    g_state.showing_toc = !g_state.showing_toc;
                    g_state.showing_search_history = false;
                    break;

                case 'L':  // Ctrl+L: left align
                    doc->set_alignment(ALIGN_LEFT);
                    break;

                case 'R':  // Ctrl+R: right align
                    doc->set_alignment(ALIGN_RIGHT);
                    break;

                case 'E':  // Ctrl+E: center align
                    doc->set_alignment(ALIGN_CENTER);
                    break;

                case 'J':  // Ctrl+J: justified
                    doc->set_alignment(ALIGN_JUSTIFIED);
                    break;

                case 'C':  // Ctrl+C: copy
                    handle_copy(hwnd);
                    break;

                case 'V':  // Ctrl+V: paste
                    handle_paste(hwnd);
                    break;

                case 'X':  // Ctrl+X: cut
                    handle_cut(hwnd);
                    break;

                case 'A': {  // Ctrl+A: select all
                    doc->set_selection(0, doc->get_raw_length());
                    break;
                }
                }
            }
            break;
        }

        g_state.cursor_visible = true;
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }

                   // ---- mouse: left button down ----
    case WM_LBUTTONDOWN: {
        if (!g_state.editing_mode) return 0;

        Document* doc = get_active_doc();
        if (!doc || !g_state.renderer) return 0;

        int px = LOWORD(lParam);
        int py = HIWORD(lParam);

        RECT rect;
        GetClientRect(hwnd, &rect);

        int page, col, line, offset;
        if (g_state.renderer->pixel_to_cursor(
            px, py, rect, doc, page, col, line, offset,
            g_state.scroll_y)) {
            doc->set_cursor(page, col, line, offset);
            doc->clear_selection();

            // start tracking for drag selection
            g_state.mouse_dragging = true;
            g_state.drag_start_offset = doc->get_cursor_offset();

            g_state.cursor_visible = true;
            InvalidateRect(hwnd, nullptr, FALSE);
        }
        return 0;
    }

                       // ---- mouse: movement (drag to select) ----
    case WM_MOUSEMOVE: {
        if (!g_state.editing_mode || !g_state.mouse_dragging) return 0;

        // only track if left button is still held
        if (!(wParam & MK_LBUTTON)) {
            g_state.mouse_dragging = false;
            return 0;
        }

        Document* doc = get_active_doc();
        if (!doc || !g_state.renderer) return 0;

        int px = LOWORD(lParam);
        int py = HIWORD(lParam);

        RECT rect;
        GetClientRect(hwnd, &rect);

        int page, col, line, offset;
        if (g_state.renderer->pixel_to_cursor(
            px, py, rect, doc, page, col, line, offset,
            g_state.scroll_y)) {
            doc->set_cursor(page, col, line, offset);
            int current_offset = doc->get_cursor_offset();

            // update selection range
            int sel_start = g_state.drag_start_offset;
            int sel_end = current_offset;
            if (sel_start > sel_end) {
                int tmp = sel_start;
                sel_start = sel_end;
                sel_end = tmp;
            }
            doc->set_selection(sel_start, sel_end);

            InvalidateRect(hwnd, nullptr, FALSE);
        }
        return 0;
    }

                     // ---- mouse: left button up ----
    case WM_LBUTTONUP: {
        g_state.mouse_dragging = false;
        return 0;
    }

                     // ---- mouse: right button down (context menu) ----
    case WM_RBUTTONDOWN: {
        if (!g_state.editing_mode) return 0;
        int px = LOWORD(lParam);
        int py = HIWORD(lParam);
        show_context_menu(hwnd, px, py);
        return 0;
    }

                       // ---- timer events ----
    case WM_TIMER: {
        if (wParam == TIMER_CURSOR_BLINK) {
            g_state.cursor_visible = !g_state.cursor_visible;
            InvalidateRect(hwnd, nullptr, FALSE);
        }
        else if (wParam == TIMER_AUTOSAVE) {
            Document* doc = get_active_doc();
            if (doc && doc->is_modified() && g_state.auto_save) {
                g_state.auto_save->on_timer(doc);
            }
        }
        return 0;
    }

                 // ---- mouse wheel: vertical scrolling ----
    case WM_MOUSEWHEEL: {
        if (!g_state.editing_mode) return 0;

        // GET_WHEEL_DELTA_WPARAM gives positive for scroll up, negative for down
        short delta = (short)HIWORD(wParam);
        int scroll_step = 40;  // pixels per notch (one notch = 120 delta)
        g_state.scroll_y -= (delta / 120) * scroll_step;

        // clamp: don't scroll above the top
        if (g_state.scroll_y < 0) g_state.scroll_y = 0;

        // clamp: don't scroll past the bottom
        // calculate total content height
        Document* doc = get_active_doc();
        if (doc && g_state.renderer) {
            int cols_per_page = doc->get_cols_per_page();
            int lines_per_col = doc->get_lines_per_col();
            int chars_per_line = doc->get_chars_per_line();

            int cw = g_state.renderer->get_char_width();
            int ch = g_state.renderer->get_char_height();
            int pad = g_state.renderer->get_padding();

            int col_pixel_w = chars_per_line * cw;
            int col_gap = pad;
            int page_w = cols_per_page * col_pixel_w + (cols_per_page - 1) * col_gap;
            int page_h = lines_per_col * ch + ch + 4;
            int page_gap = pad * 2;

            RECT rect;
            GetClientRect(hwnd, &rect);
            int client_w = rect.right - rect.left;
            int client_h = rect.bottom - rect.top;

            int available_w = client_w - 2 * pad;
            int pages_per_row = 1;
            if (page_w + page_gap > 0) {
                int test = (available_w + page_gap) / (page_w + page_gap);
                if (test > 1) pages_per_row = test;
            }

            int total_pages = doc->get_page_count();
            int total_rows = (total_pages + pages_per_row - 1) / pages_per_row;
            int total_height = pad + total_rows * (page_h + page_gap);

            int status_bar_h = ch + 8;
            int max_scroll = total_height - (client_h - status_bar_h);
            if (max_scroll < 0) max_scroll = 0;
            if (g_state.scroll_y > max_scroll) g_state.scroll_y = max_scroll;
        }

        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }

                      // ---- window resize: re-scale font to fit new width ----
    case WM_SIZE: {
        if (!g_state.editing_mode || !g_state.renderer) return 0;

        Document* doc = get_active_doc();
        if (doc) {
            HDC hdc = GetDC(hwnd);
            int new_width = LOWORD(lParam);
            g_state.renderer->init_for_layout(
                hdc, new_width,
                doc->get_cols_per_page(),
                doc->get_chars_per_line());
            ReleaseDC(hwnd, hdc);

            // clamp scroll_y to new content bounds instead of resetting
            int ch = g_state.renderer->get_char_height();
            int pad = g_state.renderer->get_padding();
            int cw = g_state.renderer->get_char_width();
            int cols_per_page = doc->get_cols_per_page();
            int lines_per_col = doc->get_lines_per_col();
            int chars_per_line = doc->get_chars_per_line();

            int col_pixel_w = chars_per_line * cw;
            int page_w = cols_per_page * col_pixel_w + (cols_per_page - 1) * pad;
            int page_h = lines_per_col * ch + ch + 4;
            int page_gap = pad * 2;

            RECT rect;
            GetClientRect(hwnd, &rect);
            int client_w = rect.right - rect.left;
            int client_h = rect.bottom - rect.top;

            int available_w = client_w - 2 * pad;
            int pages_per_row = 1;
            if (page_w + page_gap > 0) {
                int test = (available_w + page_gap) / (page_w + page_gap);
                if (test > 1) pages_per_row = test;
            }

            int total_pages = doc->get_page_count();
            int total_rows = (total_pages + pages_per_row - 1) / pages_per_row;
            int total_height = pad + total_rows * (page_h + page_gap);

            int status_bar_h = ch + 8;
            int max_scroll = total_height - (client_h - status_bar_h);
            if (max_scroll < 0) max_scroll = 0;
            if (g_state.scroll_y > max_scroll) g_state.scroll_y = max_scroll;
        }

        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }

                // ---- window creation ----
    case WM_CREATE: {
        // store window handle
        g_state.hwnd = hwnd;

        // create the startup config controls
        HINSTANCE hInstance = ((CREATESTRUCT*)lParam)->hInstance;
        create_config_controls(hwnd, hInstance);
        return 0;
    }

                  // ---- cleanup on destroy ----
    case WM_DESTROY: {
        KillTimer(hwnd, TIMER_AUTOSAVE);
        KillTimer(hwnd, TIMER_CURSOR_BLINK);

        // free all documents
        for (int i = 0; i < 10; i++) {
            Document* doc = Document::get_instance(i);
            if (doc) Document::close(doc);
        }

        // free subsystems
        delete g_state.renderer;
        delete g_state.spell_checker;
        delete g_state.search_engine;
        delete g_state.toc;
        delete g_state.auto_save;
        delete g_state.stats;

        g_state.renderer = nullptr;
        g_state.spell_checker = nullptr;
        g_state.search_engine = nullptr;
        g_state.toc = nullptr;
        g_state.auto_save = nullptr;
        g_state.stats = nullptr;

        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// WinMain -- application entry point

// Application entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"ArcanumEditorWindow";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(nullptr, IDC_IBEAM);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"The Arcanum Editor - Blackwood & Hargrove",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
