#include "std_lib_facilities.h"

void fill_vector(istream& ist, vector<int>& v, char terminator)
{
    for (int i; ist >> i;) { v.push_back(i); }
    if (ist.eof()) { return; }

    ist.clear();

    char c; ist >> c;

    if (c != terminator) {
        ist.unget();
        ist.clear(ios_base::failbit);
    }
}

struct Reading{
    int hour;
    double temperaure;
};

void correct_input_v1()
{
    cout << "Enter input file name: ";
    string iname; cin >> iname;
    ifstream ist; ist.open(iname);
    if (!ist) error("Unable to open given file: ", iname);

    cout << "Enter output file name: ";
    string oname; cin >> oname;
    ofstream ost; ost.open(oname);
    if (!ost) error("Unable to open given file: ", oname);

    vector<Reading> temps;
    int hour;
    double temperature;
    while (ist >> hour >> temperature) {
        if (hour < 0 || hour > 23) { error("Incorrect time data"); }
        temps.push_back(Reading{hour, temperature});
    }

    for (int i=0; i < temps.size(); ++i) {
        ost << '(' << temps[i].hour << ','
        << temps[i].temperaure << ")\n";}


}
