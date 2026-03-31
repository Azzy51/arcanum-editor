// editor.h - The Arcanum Editor
// Assignment 2, Second Semester

#ifndef ARCANUM_EDITOR_H
#define ARCANUM_EDITOR_H

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>

// Utility functions and generic containers.
// No standard library string or math functions are used here.
// All string operations are hand-written.



// Character classification functions
bool is_alpha(wchar_t c);
bool is_digit(wchar_t c);
bool is_space(wchar_t c);
bool is_upper(wchar_t c);
bool is_lower(wchar_t c);
bool is_punctuation(wchar_t c);
bool is_sentence_end(wchar_t c);   // period, question mark, exclamation



// Character conversion functions
wchar_t to_lower(wchar_t c);
wchar_t to_upper(wchar_t c);



// Wide string functions
int str_len(const wchar_t* s);
void str_cpy(wchar_t* dest, const wchar_t* src);
void str_ncpy(wchar_t* dest, const wchar_t* src, int n);
void str_cat(wchar_t* dest, const wchar_t* src);
int str_cmp(const wchar_t* a, const wchar_t* b);
int str_cmp_i(const wchar_t* a, const wchar_t* b);
int str_ncmp(const wchar_t* a, const wchar_t* b, int n);
int str_ncmp_i(const wchar_t* a, const wchar_t* b, int n);

// find needle inside haystack, return index or -1
int str_find(const wchar_t* haystack, const wchar_t* needle);
int str_find_i(const wchar_t* haystack, const wchar_t* needle);



// Narrow string functions
int str_len_a(const char* s);
void str_cpy_a(char* dest, const char* src);
int str_cmp_a(const char* a, const char* b);
int str_cmp_ia(const char* a, const char* b);

// convert narrow string to wide string
void narrow_to_wide(const char* src, wchar_t* dest, int max_len);
// convert wide string to narrow string
void wide_to_narrow(const wchar_t* src, char* dest, int max_len);



// Numeric conversion functions
int str_to_int(const wchar_t* s);
void int_to_str(int value, wchar_t* buffer);



// Memory functions
void mem_set(void* dest, unsigned char value, int byte_count);
void mem_cpy(void* dest, const void* src, int byte_count);


// checks if a word matches common stop words (was, is, and, or, the)
bool is_stop_word(const wchar_t* word);


// Alignment modes for text formatting


// Text alignment modes
enum AlignmentMode {
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER,
    ALIGN_JUSTIFIED
};

// Line -- a single line within a column.
// Holds a fixed-capacity char buffer.


// A single line of text within a column
class Line {
private:
    wchar_t* m_text;
    int m_length;
    int m_max_chars;
    int m_raw_offset;  // where this line starts in the raw text buffer

public:
    Line();
    Line(int max_chars);
    ~Line();
    Line(const Line& other);
    Line& operator=(const Line& other);

    void init(int max_chars);
    void set_text(const wchar_t* text, int len);
    void clear();

    const wchar_t* get_text() const;
    int get_length() const;
    int get_max_chars() const;
    wchar_t get_char(int index) const;

    // raw text offset tracking
    void set_raw_offset(int offset);
    int get_raw_offset() const;
};

// LineArray -- growable array of Line objects


// Dynamic array of Line objects
class LineArray {
private:
    Line* m_data;
    int m_count;
    int m_capacity;

    void grow() {
        int new_cap = (m_capacity == 0) ? 4 : m_capacity * 2;
        Line* new_buf = new Line[new_cap];
        for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
        delete[] m_data;
        m_data = new_buf;
        m_capacity = new_cap;
    }

public:
    LineArray() : m_data(nullptr), m_count(0), m_capacity(0) {}
    ~LineArray() { delete[] m_data; }

    LineArray(const LineArray& other)
        : m_data(nullptr), m_count(0), m_capacity(0) {
        if (other.m_count > 0) {
            m_capacity = other.m_capacity;
            m_count = other.m_count;
            m_data = new Line[m_capacity];
            for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
        }
    }

    LineArray& operator=(const LineArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = nullptr;
            m_count = 0;
            m_capacity = 0;
            if (other.m_count > 0) {
                m_capacity = other.m_capacity;
                m_count = other.m_count;
                m_data = new Line[m_capacity];
                for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    void push_back(const Line& item) {
        if (m_count >= m_capacity) grow();
        m_data[m_count++] = item;
    }

    void pop_back() { if (m_count > 0) m_count--; }

    void insert_at(int index, const Line& item) {
        if (index < 0 || index > m_count) return;
        if (m_count >= m_capacity) grow();
        for (int i = m_count; i > index; i--) m_data[i] = m_data[i - 1];
        m_data[index] = item;
        m_count++;
    }

    void remove_at(int index) {
        if (index < 0 || index >= m_count) return;
        for (int i = index; i < m_count - 1; i++) m_data[i] = m_data[i + 1];
        m_count--;
    }

    void clear() { m_count = 0; }

    void resize(int new_count) {
        if (new_count > m_capacity) {
            Line* new_buf = new Line[new_count];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_count;
        }
        m_count = new_count;
    }

    void reserve(int new_cap) {
        if (new_cap > m_capacity) {
            Line* new_buf = new Line[new_cap];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_cap;
        }
    }

    int size() const { return m_count; }
    bool is_empty() const { return m_count == 0; }

    Line& operator[](int index) { return m_data[index]; }
    const Line& operator[](int index) const { return m_data[index]; }

    Line* data() { return m_data; }
    const Line* data() const { return m_data; }

    Line& back() { return m_data[m_count - 1]; }
    const Line& back() const { return m_data[m_count - 1]; }
};

// Column -- a vertical strip on a page.
// Contains a fixed number of lines.


// A vertical column on a page
class Column {
private:
    LineArray m_lines;
    int m_max_lines;
    int m_chars_per_line;

public:
    Column();
    Column(int max_lines, int chars_per_line);
    ~Column();

    void init(int max_lines, int chars_per_line);
    void clear();

    bool is_full() const;
    int get_used_lines() const;
    int get_max_lines() const;

    Line& get_line(int index);
    const Line& get_line(int index) const;

    // add a new line with the given text; returns false if column is full
    bool add_line(const wchar_t* text, int len, int raw_offset = 0);
};

// ColumnArray -- growable array of Column objects


// Dynamic array of Column objects
class ColumnArray {
private:
    Column* m_data;
    int m_count;
    int m_capacity;

    void grow() {
        int new_cap = (m_capacity == 0) ? 4 : m_capacity * 2;
        Column* new_buf = new Column[new_cap];
        for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
        delete[] m_data;
        m_data = new_buf;
        m_capacity = new_cap;
    }

public:
    ColumnArray() : m_data(nullptr), m_count(0), m_capacity(0) {}
    ~ColumnArray() { delete[] m_data; }

    ColumnArray(const ColumnArray& other)
        : m_data(nullptr), m_count(0), m_capacity(0) {
        if (other.m_count > 0) {
            m_capacity = other.m_capacity;
            m_count = other.m_count;
            m_data = new Column[m_capacity];
            for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
        }
    }

    ColumnArray& operator=(const ColumnArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = nullptr;
            m_count = 0;
            m_capacity = 0;
            if (other.m_count > 0) {
                m_capacity = other.m_capacity;
                m_count = other.m_count;
                m_data = new Column[m_capacity];
                for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    void push_back(const Column& item) {
        if (m_count >= m_capacity) grow();
        m_data[m_count++] = item;
    }

    void pop_back() { if (m_count > 0) m_count--; }

    void insert_at(int index, const Column& item) {
        if (index < 0 || index > m_count) return;
        if (m_count >= m_capacity) grow();
        for (int i = m_count; i > index; i--) m_data[i] = m_data[i - 1];
        m_data[index] = item;
        m_count++;
    }

    void remove_at(int index) {
        if (index < 0 || index >= m_count) return;
        for (int i = index; i < m_count - 1; i++) m_data[i] = m_data[i + 1];
        m_count--;
    }

    void clear() { m_count = 0; }

    void resize(int new_count) {
        if (new_count > m_capacity) {
            Column* new_buf = new Column[new_count];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_count;
        }
        m_count = new_count;
    }

    void reserve(int new_cap) {
        if (new_cap > m_capacity) {
            Column* new_buf = new Column[new_cap];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_cap;
        }
    }

    int size() const { return m_count; }
    bool is_empty() const { return m_count == 0; }

    Column& operator[](int index) { return m_data[index]; }
    const Column& operator[](int index) const { return m_data[index]; }

    Column* data() { return m_data; }
    const Column* data() const { return m_data; }

    Column& back() { return m_data[m_count - 1]; }
    const Column& back() const { return m_data[m_count - 1]; }
};

// Page -- holds a set of side-by-side columns.


// A page containing multiple columns
class Page {
private:
    ColumnArray m_columns;
    int m_num_columns;

public:
    Page();
    Page(int num_columns, int lines_per_col, int chars_per_line);
    ~Page();

    void init(int num_columns, int lines_per_col, int chars_per_line);
    void clear();

    int get_num_columns() const;
    Column& get_column(int index);
    const Column& get_column(int index) const;

    bool is_full() const;
};

// PageArray -- growable array of Page objects


// Dynamic array of Page objects
class PageArray {
private:
    Page* m_data;
    int m_count;
    int m_capacity;

    void grow() {
        int new_cap = (m_capacity == 0) ? 4 : m_capacity * 2;
        Page* new_buf = new Page[new_cap];
        for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
        delete[] m_data;
        m_data = new_buf;
        m_capacity = new_cap;
    }

public:
    PageArray() : m_data(nullptr), m_count(0), m_capacity(0) {}
    ~PageArray() { delete[] m_data; }

    PageArray(const PageArray& other)
        : m_data(nullptr), m_count(0), m_capacity(0) {
        if (other.m_count > 0) {
            m_capacity = other.m_capacity;
            m_count = other.m_count;
            m_data = new Page[m_capacity];
            for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
        }
    }

    PageArray& operator=(const PageArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = nullptr;
            m_count = 0;
            m_capacity = 0;
            if (other.m_count > 0) {
                m_capacity = other.m_capacity;
                m_count = other.m_count;
                m_data = new Page[m_capacity];
                for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    void push_back(const Page& item) {
        if (m_count >= m_capacity) grow();
        m_data[m_count++] = item;
    }

    void pop_back() { if (m_count > 0) m_count--; }

    void insert_at(int index, const Page& item) {
        if (index < 0 || index > m_count) return;
        if (m_count >= m_capacity) grow();
        for (int i = m_count; i > index; i--) m_data[i] = m_data[i - 1];
        m_data[index] = item;
        m_count++;
    }

    void remove_at(int index) {
        if (index < 0 || index >= m_count) return;
        for (int i = index; i < m_count - 1; i++) m_data[i] = m_data[i + 1];
        m_count--;
    }

    void clear() { m_count = 0; }

    void resize(int new_count) {
        if (new_count > m_capacity) {
            Page* new_buf = new Page[new_count];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_count;
        }
        m_count = new_count;
    }

    void reserve(int new_cap) {
        if (new_cap > m_capacity) {
            Page* new_buf = new Page[new_cap];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_cap;
        }
    }

    int size() const { return m_count; }
    bool is_empty() const { return m_count == 0; }

    Page& operator[](int index) { return m_data[index]; }
    const Page& operator[](int index) const { return m_data[index]; }

    Page* data() { return m_data; }
    const Page* data() const { return m_data; }

    Page& back() { return m_data[m_count - 1]; }
    const Page& back() const { return m_data[m_count - 1]; }
};

// CursorPosition -- tracks where the user is editing.


// Tracks cursor location in the document
struct CursorPosition {
    int page;
    int column;
    int line;
    int offset;  // character offset within the line

    CursorPosition() : page(0), column(0), line(0), offset(0) {}
};

// SelectionRange -- tracks a highlighted selection.
// Uses absolute offsets into the raw text buffer.


// Represents a text selection range
struct SelectionRange {
    int start;  // index into raw text
    int end;    // index into raw text (exclusive)
    bool active;

    SelectionRange() : start(0), end(0), active(false) {}

    void clear() { start = 0; end = 0; active = false; }
    int length() const { return end - start; }
};

// EditDelta -- records a single insert or delete operation
// for delta-based auto-save. Each mutation to the raw text
// buffer appends one delta to the document's delta log.


// Records a single edit operation for auto-save
struct EditDelta {
    enum DeltaType { DELTA_INSERT, DELTA_DELETE };

    DeltaType type;
    int offset;           // position in raw text where change happened
    wchar_t text[512];    // the inserted or deleted text
    int text_len;         // how many characters

    EditDelta() : type(DELTA_INSERT), offset(0), text_len(0) {
        text[0] = L'\0';
    }
};

// EditDeltaArray -- growable array of EditDelta objects


// Dynamic array of EditDelta objects
class EditDeltaArray {
private:
    EditDelta* m_data;
    int m_count;
    int m_capacity;

    void grow() {
        int new_cap = (m_capacity == 0) ? 4 : m_capacity * 2;
        EditDelta* new_buf = new EditDelta[new_cap];
        for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
        delete[] m_data;
        m_data = new_buf;
        m_capacity = new_cap;
    }

public:
    EditDeltaArray() : m_data(nullptr), m_count(0), m_capacity(0) {}
    ~EditDeltaArray() { delete[] m_data; }

    EditDeltaArray(const EditDeltaArray& other)
        : m_data(nullptr), m_count(0), m_capacity(0) {
        if (other.m_count > 0) {
            m_capacity = other.m_capacity;
            m_count = other.m_count;
            m_data = new EditDelta[m_capacity];
            for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
        }
    }

    EditDeltaArray& operator=(const EditDeltaArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = nullptr;
            m_count = 0;
            m_capacity = 0;
            if (other.m_count > 0) {
                m_capacity = other.m_capacity;
                m_count = other.m_count;
                m_data = new EditDelta[m_capacity];
                for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    void push_back(const EditDelta& item) {
        if (m_count >= m_capacity) grow();
        m_data[m_count++] = item;
    }

    void pop_back() { if (m_count > 0) m_count--; }

    void insert_at(int index, const EditDelta& item) {
        if (index < 0 || index > m_count) return;
        if (m_count >= m_capacity) grow();
        for (int i = m_count; i > index; i--) m_data[i] = m_data[i - 1];
        m_data[index] = item;
        m_count++;
    }

    void remove_at(int index) {
        if (index < 0 || index >= m_count) return;
        for (int i = index; i < m_count - 1; i++) m_data[i] = m_data[i + 1];
        m_count--;
    }

    void clear() { m_count = 0; }

    void resize(int new_count) {
        if (new_count > m_capacity) {
            EditDelta* new_buf = new EditDelta[new_count];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_count;
        }
        m_count = new_count;
    }

    void reserve(int new_cap) {
        if (new_cap > m_capacity) {
            EditDelta* new_buf = new EditDelta[new_cap];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_cap;
        }
    }

    int size() const { return m_count; }
    bool is_empty() const { return m_count == 0; }

    EditDelta& operator[](int index) { return m_data[index]; }
    const EditDelta& operator[](int index) const { return m_data[index]; }

    EditDelta* data() { return m_data; }
    const EditDelta* data() const { return m_data; }

    EditDelta& back() { return m_data[m_count - 1]; }
    const EditDelta& back() const { return m_data[m_count - 1]; }
};

// Document -- the central data model for one manuscript tab.
//
// Stores text in a flat raw buffer, then reflows it into
// pages/columns/lines for display. This makes insertions
// and deletions simple (just modify the buffer and reflow).
//
// Enforces a maximum of 10 simultaneous instances via a
// static counter checked in the constructor.


// Main document class managing text and layout
class Document {
private:
    // --- static tab management ---
    static int s_instance_count;
    static Document* s_instances[10];

    // --- raw text storage ---
    wchar_t* m_raw_text;
    int m_raw_len;
    int m_raw_capacity;

    // --- layout configuration ---
    int m_cols_per_page;
    int m_lines_per_col;
    int m_chars_per_line;

    // --- laid-out pages ---
    PageArray m_pages;

    // --- cursor and selection ---
    CursorPosition m_cursor;
    SelectionRange m_selection;

    // --- alignment ---
    AlignmentMode m_alignment;

    // --- document metadata ---
    wchar_t m_file_path[260];   // MAX_PATH
    wchar_t m_title[128];
    bool m_is_modified;
    int m_tab_index;  // which slot in s_instances this occupies

    // --- delta tracking for delta-based auto-save ---
    EditDeltaArray m_deltas;
    int m_delta_sequence;  // total deltas recorded since creation

    // --- internal helpers ---
    void grow_buffer(int needed);
    void record_delta(EditDelta::DeltaType type, int offset,
        const wchar_t* text, int len);

    // given a raw text offset, figure out which page/col/line/char it maps to
    void offset_to_cursor(int offset, CursorPosition& out) const;

    // given a cursor position, figure out the raw text offset
    int cursor_to_offset(const CursorPosition& pos) const;

public:
    Document();
    ~Document();

    // factory: creates a new document, returns nullptr if 10 tabs full
    static Document* create(int cols_per_page, int lines_per_col, int chars_per_line);

    // close and free a specific document tab
    static void close(Document* doc);

    // access existing instances
    static Document* get_instance(int index);
    static int get_instance_count();

    // --- configuration ---
    void set_layout(int cols_per_page, int lines_per_col, int chars_per_line);
    int get_cols_per_page() const;
    int get_lines_per_col() const;
    int get_chars_per_line() const;

    // --- text operations ---
    void insert_char(wchar_t c);
    void insert_text(const wchar_t* text, int len);
    void delete_char_before();   // backspace
    void delete_char_at();       // delete key

    // get a copy of selected text (caller must delete[] the result)
    wchar_t* get_selected_text() const;
    void delete_selection();

    // --- raw text access ---
    const wchar_t* get_raw_text() const;
    int get_raw_length() const;

    // --- layout ---
    // reflow the raw text into pages, columns, and lines
    void reflow();

    // --- page access ---
    int get_page_count() const;
    const Page& get_page(int index) const;
    Page& get_page(int index);

    // --- cursor ---
    const CursorPosition& get_cursor() const;
    void set_cursor(int page, int col, int line, int offset);
    void move_cursor_left();
    void move_cursor_right();
    void move_cursor_up();
    void move_cursor_down();
    void move_cursor_home();
    void move_cursor_end();
    void move_cursor_page_up();
    void move_cursor_page_down();

    // set cursor from a raw text offset
    void set_cursor_from_offset(int offset);
    // get raw text offset from current cursor
    int get_cursor_offset() const;

    // --- selection ---
    const SelectionRange& get_selection() const;
    void set_selection(int start, int end);
    void clear_selection();
    bool has_selection() const;

    // --- alignment ---
    AlignmentMode get_alignment() const;
    void set_alignment(AlignmentMode mode);

    // --- file metadata ---
    const wchar_t* get_file_path() const;
    void set_file_path(const wchar_t* path);
    const wchar_t* get_title() const;
    void set_title(const wchar_t* title);
    bool is_modified() const;
    void set_modified(bool val);
    int get_tab_index() const;

    // --- delta tracking ---
    const EditDeltaArray& get_deltas() const;
    int get_delta_count() const;
    void clear_deltas();
    int get_delta_sequence() const;

    // prevent copying documents around carelessly
    Document(const Document&) = delete;
    Document& operator=(const Document&) = delete;
};




// TrieNode -- a single node in the dictionary trie.
// Each node has 26 children (a-z) and a flag marking
// whether a complete word ends here.


// Trie node for dictionary lookup
struct TrieNode {
    TrieNode* children[26];
    bool is_word;

    TrieNode() : is_word(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

// SpellChecker -- loads the dictionary into a trie and
// provides fast word lookups for real-time spell checking.

// a misspelled word range within the raw text
struct SpellError {
    int start;  // index into raw text
    int end;    // index into raw text (exclusive)
};

// SpellErrorArray -- growable array of SpellError objects


// Dynamic array of SpellError objects
class SpellErrorArray {
private:
    SpellError* m_data;
    int m_count;
    int m_capacity;

    void grow() {
        int new_cap = (m_capacity == 0) ? 4 : m_capacity * 2;
        SpellError* new_buf = new SpellError[new_cap];
        for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
        delete[] m_data;
        m_data = new_buf;
        m_capacity = new_cap;
    }

public:
    SpellErrorArray() : m_data(nullptr), m_count(0), m_capacity(0) {}
    ~SpellErrorArray() { delete[] m_data; }

    SpellErrorArray(const SpellErrorArray& other)
        : m_data(nullptr), m_count(0), m_capacity(0) {
        if (other.m_count > 0) {
            m_capacity = other.m_capacity;
            m_count = other.m_count;
            m_data = new SpellError[m_capacity];
            for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
        }
    }

    SpellErrorArray& operator=(const SpellErrorArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = nullptr;
            m_count = 0;
            m_capacity = 0;
            if (other.m_count > 0) {
                m_capacity = other.m_capacity;
                m_count = other.m_count;
                m_data = new SpellError[m_capacity];
                for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    void push_back(const SpellError& item) {
        if (m_count >= m_capacity) grow();
        m_data[m_count++] = item;
    }

    void pop_back() { if (m_count > 0) m_count--; }

    void insert_at(int index, const SpellError& item) {
        if (index < 0 || index > m_count) return;
        if (m_count >= m_capacity) grow();
        for (int i = m_count; i > index; i--) m_data[i] = m_data[i - 1];
        m_data[index] = item;
        m_count++;
    }

    void remove_at(int index) {
        if (index < 0 || index >= m_count) return;
        for (int i = index; i < m_count - 1; i++) m_data[i] = m_data[i + 1];
        m_count--;
    }

    void clear() { m_count = 0; }

    void resize(int new_count) {
        if (new_count > m_capacity) {
            SpellError* new_buf = new SpellError[new_count];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_count;
        }
        m_count = new_count;
    }

    void reserve(int new_cap) {
        if (new_cap > m_capacity) {
            SpellError* new_buf = new SpellError[new_cap];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_cap;
        }
    }

    int size() const { return m_count; }
    bool is_empty() const { return m_count == 0; }

    SpellError& operator[](int index) { return m_data[index]; }
    const SpellError& operator[](int index) const { return m_data[index]; }

    SpellError* data() { return m_data; }
    const SpellError* data() const { return m_data; }

    SpellError& back() { return m_data[m_count - 1]; }
    const SpellError& back() const { return m_data[m_count - 1]; }
};


// Spell checker using trie-based dictionary
class SpellChecker {
private:
    TrieNode* m_root;
    SpellErrorArray m_errors;
    bool m_loaded;

    // recursively free the trie
    void free_trie(TrieNode* node);

    // insert a single word into the trie (lowercase only)
    void insert_word(const wchar_t* word, int len);

public:
    SpellChecker();
    ~SpellChecker();

    // load the OPTED-Dictionary.csv file
    // uses WinAPI CreateFileW/ReadFile, extracts just the word column
    bool load_dictionary(const wchar_t* csv_path);

    // check if a word exists in the dictionary
    bool check_word(const wchar_t* word, int len) const;

    // scan the entire raw text and build the error list
    void scan_text(const wchar_t* text, int text_len);

    // get the list of errors for rendering
    const SpellErrorArray& get_errors() const;

    bool is_loaded() const;

    // prevent copying
    SpellChecker(const SpellChecker&) = delete;
    SpellChecker& operator=(const SpellChecker&) = delete;
};




// forward declaration
class Document;

// SearchMatch -- one occurrence of a search term in the text.

struct SearchMatch {
    int raw_offset;   // position in the raw text buffer
    int length;       // length of the matched text
};

// SearchMatchArray -- growable array of SearchMatch objects


// Dynamic array of SearchMatch objects
class SearchMatchArray {
private:
    SearchMatch* m_data;
    int m_count;
    int m_capacity;

    void grow() {
        int new_cap = (m_capacity == 0) ? 4 : m_capacity * 2;
        SearchMatch* new_buf = new SearchMatch[new_cap];
        for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
        delete[] m_data;
        m_data = new_buf;
        m_capacity = new_cap;
    }

public:
    SearchMatchArray() : m_data(nullptr), m_count(0), m_capacity(0) {}
    ~SearchMatchArray() { delete[] m_data; }

    SearchMatchArray(const SearchMatchArray& other)
        : m_data(nullptr), m_count(0), m_capacity(0) {
        if (other.m_count > 0) {
            m_capacity = other.m_capacity;
            m_count = other.m_count;
            m_data = new SearchMatch[m_capacity];
            for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
        }
    }

    SearchMatchArray& operator=(const SearchMatchArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = nullptr;
            m_count = 0;
            m_capacity = 0;
            if (other.m_count > 0) {
                m_capacity = other.m_capacity;
                m_count = other.m_count;
                m_data = new SearchMatch[m_capacity];
                for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    void push_back(const SearchMatch& item) {
        if (m_count >= m_capacity) grow();
        m_data[m_count++] = item;
    }

    void pop_back() { if (m_count > 0) m_count--; }

    void insert_at(int index, const SearchMatch& item) {
        if (index < 0 || index > m_count) return;
        if (m_count >= m_capacity) grow();
        for (int i = m_count; i > index; i--) m_data[i] = m_data[i - 1];
        m_data[index] = item;
        m_count++;
    }

    void remove_at(int index) {
        if (index < 0 || index >= m_count) return;
        for (int i = index; i < m_count - 1; i++) m_data[i] = m_data[i + 1];
        m_count--;
    }

    void clear() { m_count = 0; }

    void resize(int new_count) {
        if (new_count > m_capacity) {
            SearchMatch* new_buf = new SearchMatch[new_count];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_count;
        }
        m_count = new_count;
    }

    void reserve(int new_cap) {
        if (new_cap > m_capacity) {
            SearchMatch* new_buf = new SearchMatch[new_cap];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_cap;
        }
    }

    int size() const { return m_count; }
    bool is_empty() const { return m_count == 0; }

    SearchMatch& operator[](int index) { return m_data[index]; }
    const SearchMatch& operator[](int index) const { return m_data[index]; }

    SearchMatch* data() { return m_data; }
    const SearchMatch* data() const { return m_data; }

    SearchMatch& back() { return m_data[m_count - 1]; }
    const SearchMatch& back() const { return m_data[m_count - 1]; }
};

// SearchHistoryEntry -- stores a past search term and its
// result count. We keep the last 5 unique searches.

struct SearchHistoryEntry {
    wchar_t term[256];
    int match_count;
};

// SearchEngine -- case-insensitive search with highlighting
// and a history of the last 5 queries.


// Text search functionality
class SearchEngine {
private:
    SearchMatchArray m_matches;
    SearchHistoryEntry m_history[5];
    int m_history_count;   // how many entries are filled (max 5)
    wchar_t m_current_term[256];
    bool m_active;

public:
    SearchEngine();
    ~SearchEngine();

    // perform a case-insensitive search on the document's raw text
    void search(const Document* doc, const wchar_t* term);

    // clear current search results
    void clear();

    // check if a given raw text offset falls within any match
    bool is_highlighted(int offset) const;

    // access results
    const SearchMatchArray& get_matches() const;
    int get_match_count() const;

    // access history
    const SearchHistoryEntry* get_history() const;
    int get_history_count() const;

    const wchar_t* get_current_term() const;
    bool is_active() const;
};




// forward declaration
class Document;

// Statistics -- computes real-time text metrics.
// Updated after every document modification.


// Document statistics calculator
class Statistics {
private:
    int m_chars_with_spaces;
    int m_chars_without_spaces;
    int m_word_count;
    int m_sentence_count;
    int m_page_count;
    int m_reading_time_sec;  // estimated at 200 words per minute

public:
    Statistics();
    ~Statistics();

    // recompute all statistics from the document's raw text
    void compute(const Document* doc);

    // accessors
    int get_chars_with_spaces() const;
    int get_chars_without_spaces() const;
    int get_word_count() const;
    int get_sentence_count() const;
    int get_page_count() const;
    int get_reading_time_sec() const;
};




// forward declaration
class Document;

// TocEntry -- one entry in the generated table of contents.

struct TocEntry {
    wchar_t title[256];
    int page_number;    // 1-based
    int column_number;  // 1-based
};

// TocEntryArray -- growable array of TocEntry objects


// Dynamic array of TocEntry objects
class TocEntryArray {
private:
    TocEntry* m_data;
    int m_count;
    int m_capacity;

    void grow() {
        int new_cap = (m_capacity == 0) ? 4 : m_capacity * 2;
        TocEntry* new_buf = new TocEntry[new_cap];
        for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
        delete[] m_data;
        m_data = new_buf;
        m_capacity = new_cap;
    }

public:
    TocEntryArray() : m_data(nullptr), m_count(0), m_capacity(0) {}
    ~TocEntryArray() { delete[] m_data; }

    TocEntryArray(const TocEntryArray& other)
        : m_data(nullptr), m_count(0), m_capacity(0) {
        if (other.m_count > 0) {
            m_capacity = other.m_capacity;
            m_count = other.m_count;
            m_data = new TocEntry[m_capacity];
            for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
        }
    }

    TocEntryArray& operator=(const TocEntryArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = nullptr;
            m_count = 0;
            m_capacity = 0;
            if (other.m_count > 0) {
                m_capacity = other.m_capacity;
                m_count = other.m_count;
                m_data = new TocEntry[m_capacity];
                for (int i = 0; i < m_count; i++) m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    void push_back(const TocEntry& item) {
        if (m_count >= m_capacity) grow();
        m_data[m_count++] = item;
    }

    void pop_back() { if (m_count > 0) m_count--; }

    void insert_at(int index, const TocEntry& item) {
        if (index < 0 || index > m_count) return;
        if (m_count >= m_capacity) grow();
        for (int i = m_count; i > index; i--) m_data[i] = m_data[i - 1];
        m_data[index] = item;
        m_count++;
    }

    void remove_at(int index) {
        if (index < 0 || index >= m_count) return;
        for (int i = index; i < m_count - 1; i++) m_data[i] = m_data[i + 1];
        m_count--;
    }

    void clear() { m_count = 0; }

    void resize(int new_count) {
        if (new_count > m_capacity) {
            TocEntry* new_buf = new TocEntry[new_count];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_count;
        }
        m_count = new_count;
    }

    void reserve(int new_cap) {
        if (new_cap > m_capacity) {
            TocEntry* new_buf = new TocEntry[new_cap];
            for (int i = 0; i < m_count; i++) new_buf[i] = m_data[i];
            delete[] m_data;
            m_data = new_buf;
            m_capacity = new_cap;
        }
    }

    int size() const { return m_count; }
    bool is_empty() const { return m_count == 0; }

    TocEntry& operator[](int index) { return m_data[index]; }
    const TocEntry& operator[](int index) const { return m_data[index]; }

    TocEntry* data() { return m_data; }
    const TocEntry* data() const { return m_data; }

    TocEntry& back() { return m_data[m_count - 1]; }
    const TocEntry& back() const { return m_data[m_count - 1]; }
};

// TableOfContents -- auto-generated from the first paragraph
// of each page using a score-based heuristic.


// Table of contents generator
class TableOfContents {
private:
    TocEntryArray m_entries;

    // scoring criteria for heading detection
    int score_paragraph(const wchar_t* text, int len) const;

    // fallback: take first 4 words, drop trailing stop word, capitalize
    void extract_fallback_title(const wchar_t* text, int len,
        wchar_t* out, int out_size) const;

    // extract the first paragraph from a page's text
    // returns the length of the paragraph, fills out_buf
    int get_first_paragraph(const Document* doc, int page_index,
        wchar_t* out_buf, int buf_size) const;

    // check if a paragraph is preceded by a blank line
    bool is_preceded_by_blank(const Document* doc, int page_index) const;

public:
    TableOfContents();
    ~TableOfContents();

    // scan all pages and generate ToC entries
    void generate(const Document* doc);

    // access entries
    const TocEntryArray& get_entries() const;
    int get_entry_count() const;
};


#include <windows.h>


// forward declaration
class Document;

// AutoSave -- manages periodic saves and maintains the last
// 10 autosave copies on disk. Uses WinAPI file functions
// for writing.


// Auto-save manager with delta tracking
class AutoSave {
private:
    int m_interval_ms;        // save interval in milliseconds (default 60000)
    int m_save_index;         // rotating counter 0-9 for autosave slots
    wchar_t m_base_dir[260];  // directory where autosave files are stored
    bool m_enabled;
    int m_tick_count;         // counts timer ticks, full save every N ticks
    int m_full_save_every;    // do a full snapshot every this many ticks (default 5)

    // build the file path for a given autosave slot
    void build_file_path(int slot, wchar_t* out, int out_size) const;

    // build the delta file path for a given slot
    void build_delta_path(int slot, wchar_t* out, int out_size) const;

public:
    AutoSave();
    ~AutoSave();

    // set up the autosave directory and interval
    void init(const wchar_t* base_dir, int interval_ms);

    // called from WM_TIMER -- saves deltas or full snapshot
    void on_timer(Document* doc);

    // save only the accumulated deltas to a binary file
    void save_deltas(Document* doc);

    // explicit save (full snapshot, resets the autosave chain)
    void full_save(Document* doc, const wchar_t* file_path);

    // load a document from a file path
    bool load_file(Document* doc, const wchar_t* file_path);

    // load a document from a base snapshot plus delta files
    bool load_with_deltas(Document* doc, const wchar_t* base_path,
        const wchar_t* delta_path);

    // getters/setters
    int get_interval() const;
    void set_interval(int ms);
    void set_enabled(bool val);
    bool is_enabled() const;
};


#include <windows.h>

// forward declarations to avoid circular includes
class Document;
class SpellChecker;
class SearchEngine;
class Statistics;

// need the full enum definition for the apply_alignment parameter

// Renderer -- responsible for all GDI painting.
// Draws columns, text, cursor, footer, status bar, etc.


// Handles all GDI drawing operations
class Renderer {
private:
    HFONT m_font;
    int m_char_width;    // pixel width of one character (monospace)
    int m_char_height;   // pixel height of one line
    int m_padding;       // gap between columns and edges

    // colors
    COLORREF m_bg_color;
    COLORREF m_text_color;
    COLORREF m_cursor_color;
    COLORREF m_highlight_color;     // search match background
    COLORREF m_spell_error_color;   // misspelled word foreground
    COLORREF m_selection_bg;        // selected text background
    COLORREF m_footer_color;
    COLORREF m_status_bar_bg;
    COLORREF m_status_bar_fg;
    COLORREF m_col_separator_color;

public:
    Renderer();
    ~Renderer();

    // set up the monospace font and measure character dimensions
    void init(HDC hdc);

    // re-initialize font to fit the given layout within window width
    void init_for_layout(HDC hdc, int window_width, int cols_per_page,
        int chars_per_line);

    // main paint routine, called from WM_PAINT
    void paint(HDC hdc, RECT client_rect, Document* doc,
        SpellChecker* spell, SearchEngine* search,
        Statistics* stats, bool cursor_visible,
        int active_tab, bool search_mode,
        const wchar_t* search_buffer,
        bool showing_toc, void* toc_ptr,
        bool showing_search_history,
        int scroll_y = 0);

    // get font handle for text output
    HFONT get_font() const;
    int get_char_width() const;
    int get_char_height() const;
    int get_padding() const;

    // map a pixel coordinate to a document position
    // returns true if the click is within text, false otherwise
    bool pixel_to_cursor(int px, int py, RECT client_rect,
        Document* doc, int& out_page,
        int& out_col, int& out_line, int& out_offset,
        int scroll_y = 0);

private:
    // helper: draw a single column at the given pixel offset
    void draw_column(HDC hdc, const Document* doc, int page_idx,
        int col_idx, int x_start, int y_start,
        SpellChecker* spell, SearchEngine* search);

    // helper: draw the page footer
    void draw_footer(HDC hdc, int page_number, int total_pages,
        int x_start, int y_pos, int page_width);

    // helper: draw the status bar at the bottom of the window
    void draw_status_bar(HDC hdc, RECT client_rect, Document* doc,
        Statistics* stats, int active_tab,
        bool search_mode, const wchar_t* search_buffer);

    // helper: draw the cursor blinking caret
    void draw_cursor(HDC hdc, Document* doc, int col_x_start,
        int y_start, bool visible);

    // helper: draw table of contents overlay
    void draw_toc(HDC hdc, RECT client_rect, void* toc_ptr);

    // helper: draw search history overlay
    void draw_search_history(HDC hdc, RECT client_rect, void* search_ptr);

    // compute the aligned version of a line's text for display
    void apply_alignment(const wchar_t* text, int text_len,
        int line_width, AlignmentMode mode,
        bool is_last_line_of_paragraph,
        wchar_t* out_buf, int out_buf_size);
};


// THE ARCANUM EDITOR -- master header
// Blackwood & Hargrove, London, 2009
//
// Ties together all subsystems: document model, rendering,
// dictionary, search, table of contents, auto-save, and
// statistics. This file is included by editor.cpp.

// force unicode so all WinAPI calls resolve to their W variants
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif


// Global constants

const int WINDOW_WIDTH = 1440;
const int WINDOW_HEIGHT = 720;

// timer IDs
const int TIMER_AUTOSAVE = 1;
const int TIMER_CURSOR_BLINK = 2;

// default layout values
const int DEFAULT_COLS_PER_PAGE = 2;
const int DEFAULT_LINES_PER_COL = 20;
const int DEFAULT_CHARS_PER_LINE = 80;

// control IDs for the startup config dialog
const int ID_LABEL_COLS = 101;
const int ID_EDIT_COLS = 102;
const int ID_LABEL_LINES = 103;
const int ID_EDIT_LINES = 104;
const int ID_LABEL_CHARS = 105;
const int ID_EDIT_CHARS = 106;
const int ID_BTN_START = 107;
const int ID_LABEL_TITLE = 108;

// context menu item IDs
const int IDM_CUT = 201;
const int IDM_COPY = 202;
const int IDM_PASTE = 203;
const int IDM_SEARCH = 204;
const int IDM_ALIGN_LEFT = 205;
const int IDM_ALIGN_RIGHT = 206;
const int IDM_ALIGN_CENTER = 207;
const int IDM_ALIGN_JUSTIFY = 208;

// EditorState -- the global state that WndProc and friends
// share. Avoids scattering globals everywhere.


// Global editor state and UI controls
struct EditorState {
    // which document tab is currently active
    int active_tab;

    // has the user finished the config dialog and entered editing mode?
    bool editing_mode;

    // cursor blink state (toggles every 500ms)
    bool cursor_visible;

    // is the user currently typing a search query?
    bool search_mode;
    wchar_t search_buffer[256];
    int search_buffer_len;

    // is the table of contents being shown?
    bool showing_toc;

    // is the search history panel being shown?
    bool showing_search_history;

    // mouse drag tracking
    bool mouse_dragging;
    int drag_start_offset;

    // vertical scroll offset (in pixels)
    int scroll_y;

    // the renderer does the painting
    Renderer* renderer;

    // dictionary / spell checker
    SpellChecker* spell_checker;

    // search engine
    SearchEngine* search_engine;

    // table of contents
    TableOfContents* toc;

    // auto-save manager
    AutoSave* auto_save;

    // statistics tracker
    Statistics* stats;

    // window handle (needed for timers and invalidation)
    HWND hwnd;

    // config dialog child window handles
    HWND config_label_title;
    HWND config_edit_cols;
    HWND config_edit_lines;
    HWND config_edit_chars;
    HWND config_btn_start;

    EditorState()
        : active_tab(0)
        , editing_mode(false)
        , cursor_visible(true)
        , search_mode(false)
        , search_buffer_len(0)
        , showing_toc(false)
        , showing_search_history(false)
        , mouse_dragging(false)
        , drag_start_offset(0)
        , scroll_y(0)
        , renderer(nullptr)
        , spell_checker(nullptr)
        , search_engine(nullptr)
        , toc(nullptr)
        , auto_save(nullptr)
        , stats(nullptr)
        , hwnd(nullptr)
        , config_label_title(nullptr)
        , config_edit_cols(nullptr)
        , config_edit_lines(nullptr)
        , config_edit_chars(nullptr)
        , config_btn_start(nullptr) {
        search_buffer[0] = L'\0';
    }
};

// The global state instance -- declared in editor.cpp

extern EditorState g_state;


#endif // ARCANUM_EDITOR_H
