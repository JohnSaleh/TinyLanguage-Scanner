#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <nana/gui.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define sz(x) (int)x.size()
#define el '\n'

const ll N = 2e5 + 5, mod = 1e9 + 7;

int m[51][128];
string token_name[51];
void pre() {

    for (int i = 0; i < 51; i++)
        for (int j = 0; j < 128; j++)
            m[i][j] = 50;

    for (char i = '0'; i <= '9'; i++)
        m[0][i] = 16;
    for (char i = 'A'; i <= 'Z'; i++)
        m[0][i] = 16;
    for (char i = 'a'; i <= 'z'; i++)
        m[0][i] = 16;

    m[0]['+'] = 1, m[0]['-'] = 2, m[0]['*'] = 3, m[0]['/'] = 4, m[0]['<'] = 5, m[0]['='] = 6;
    m[0][':'] = 7, m[7]['='] = 8;
    m[0][';'] = 9, m[0][','] = 10, m[0]['('] = 11, m[0][')'] = 12;
    for (char i = '0'; i <= '9'; i++)
        m[0][i] = 13, m[13][i] = 13;

    m[0]['i'] = 14, m[14]['f'] = 15;

    m[0]['t'] = 17, m[17]['h'] = 18, m[18]['e'] = 19, m[19]['n'] = 20;

    m[0]['e'] = 21, m[21]['l'] = 22, m[22]['s'] = 24, m[24]['e'] = 25,
        m[21]['n'] = 23, m[23]['d'] = 26;

    m[0]['r'] = 27, m[27]['e'] = 28, m[28]['p'] = 29, m[29]['e'] = 31, m[31]['a'] = 32, m[32]['t'] = 33;
    m[28]['a'] = 30, m[30]['d'] = 34;

    m[0]['u'] = 35, m[35]['n'] = 36, m[36]['t'] = 37, m[37]['i'] = 38, m[38]['l'] = 39;

    m[0]['w'] = 40, m[40]['r'] = 41, m[41]['i'] = 42, m[42]['t'] = 43, m[43]['e'] = 44;

    for (char i = '0'; i <= '9'; i++)
        for (int j = 14; j <= 44; j++)
            m[j][i] = 16;
    for (char i = 'A'; i <= 'Z'; i++)
        for (int j = 14; j <= 44; j++)
            m[j][i] = 16;
    for (char i = 'a'; i <= 'z'; i++)
        for (int j = 14; j <= 44; j++)
            if (m[j][i] == 50)
                m[j][i] = 16;

    m[0]['"'] = 45, m[45]['"'] = 46;
    for (int i = 0; i < 128; i++)
        if (m[45][i] == 50)
            m[45][i] = 45;

    m[0]['{'] = 47, m[47]['}'] = 48;
    for (int i = 0; i < 128; i++)
        if (m[47][i] == 50)
            m[47][i] = 47;

    m[0][' '] = 49, m[49][' '] = 49;

    for (int i = 0; i < 51; i++)
		token_name[i] = "Skip"; // Change to "Error" if you want to show errors instead of skipping

    token_name[1] = "ADD_OP";
    token_name[2] = "SUB_OP";
    token_name[3] = "MUL_OP";
    token_name[4] = "DIV_OP";
    token_name[5] = "LessThan_OP";
    token_name[6] = "Equal_OP";
    token_name[8] = "Assign_OP";
    token_name[9] = "Semi-Colon";
    token_name[10] = "Comma";
    token_name[11] = "Left_parenthesis";
    token_name[12] = "Right_parenthesis";
    token_name[13] = "Integer";

    for (int i = 14; i <= 44; i++)
        token_name[i] = "Identifier";

    token_name[15] = "if_KW";
    token_name[20] = "then_KW";
    token_name[25] = "else_KW";
    token_name[26] = "end_KW";
    token_name[33] = "repeat_KW";
    token_name[34] = "read_KW";
    token_name[39] = "until_KW";
    token_name[44] = "write_KW";

    token_name[46] = "string_literal";

    token_name[48] = "Skip";
    token_name[49] = "Skip";
}



vector<pair<string,string>> tokenization(string code) {
    int cur = 0;
    string cur_word = "";
	vector<pair<string, string>> res;
    for (auto ch : code) {
        if (m[cur][ch] == 50) {
            if (token_name[cur] != "Skip")
                res.push_back({ cur_word,token_name[cur] }); // here the output
            cur = 0;
            cur_word = "";
        }

        cur_word += ch;
        cur = m[cur][ch];
    }
	
    if (token_name[cur] != "Skip")
        res.push_back({ cur_word,token_name[cur] });
    return res;
}



// ---------------------------------------------------------
// MAIN UI LOGIC
// ---------------------------------------------------------
int main()
{
    pre();
    using namespace nana;

    // 1. Create the main window
    form fm;
    fm.caption("TinyLanguage Scanner");

    // 2. Create the Widgets
    // Big Text Field
    textbox txt_input{ fm };
    txt_input.multi_lines(true);   // Allow multiple lines
    txt_input.line_wrapped(true);  // Wrap text so it doesn't scroll offscreen
    txt_input.tip_string("Type text here...");

    // Button
    button btn_process{ fm, "Process Text" };

    // Table (Listbox)
    listbox table{ fm };
    table.append_header("Key", 150);   // Column 1: 150 pixels wide
    table.append_header("Value", 250); // Column 2: 250 pixels wide

    // 3. Define the Layout
    // vert: Stack vertically
    // gap: Space between items
    // weight: How much screen space an item takes up
    fm.div("vert margin=10 gap=10 <txt weight=40%> <btn weight=30> <table>");
    fm["txt"] << txt_input;
    fm["btn"] << btn_process;
    fm["table"] << table;
    fm.collocate();

    // 4. Wire up the Button Click Event
    btn_process.events().click([&txt_input, &table] {

        // Step A: Grab the text from the text box
        std::string rawText = txt_input.caption();

        // Step B: Run it through your function
        std::vector<pair<string, string>> myData = tokenization(rawText);

        // Step C: Clear the old table data (category 0 is the default group)
        table.clear();

        // Step D: Loop through the map and populate the table rows
        for (const auto& pair : myData) {
            // Append a row requiring two columns { Column 1, Column 2 }
            table.at(0).append({ pair.first, pair.second });
        }
        });

    // 5. Show the window and start the loop
    fm.show();
    exec();

    return 0;
}