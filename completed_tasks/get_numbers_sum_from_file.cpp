#include "std_lib_facilities.h"
/*
void skip_to_int();


int get_int()
{
    int n = 0;
    while (true) {
        if (cin >> n) { return n; }
        cout << "This isn't a number; try again" << '\n';
        skip_to_int();
    }
}

int get_int(int low, int high)
{
    cout << "Entrer a number from "
         << low << " to " << high << " (including):" << '\n';
    while (true) {
        int n = get_int();
        if (low <= n && n <= high) {return n;}
        cout << "Sorry, " << n
             << " is out of given range (["
             << low << ":" << high << ")]; try again" << '\n';
    }
}

int get_int(int low, int high,
            const string& greeting,
            const string& sorry)
{
    cout << greeting << ": [" << low << ":" << high << "]" << "\n";
    while (true) {
        int n = get_int();
        if (low <= n && n <= high) { return n; }
        cout << sorry << ": [" << low << ':' << high << '\n';
    }
}
*/

string get_file_name()
{
    string fname;
    while (true) {
        if (cin >> fname) {
            return fname;
        }
        if (cin.eof() || cin.bad()) { error("No input"); }

        cout << "Unable to get file name; try again" << '\n';
        cin.clear();
    }
}

void set_ifstream(ifstream& ifst)
{
    cout << "Enter input file name: ";
    string iname = get_file_name();

    ifst.open(iname);
    if (!ifst) { error("Unable to open given file: ", iname); }
}

void set_ofstream(ofstream& ofst)
{
    cout << "Enter output file name: ";
    string oname = get_file_name();

    ofst.open(oname);
    if (!ofst) error("Unable to open given file: ", oname);
}


void skip_to_double(istream& ist)
{
    if (ist.fail()) {
        ist.clear();
        for (char ch; ist >> ch;) {
            if (isdigit(ch) || ch == '-' || ch == '.'){
                ist.unget();

                return;
            }
        }
    }
    if (cin.bad()) { error("Input stream critical error: unable to fix data reading"); }
    // If func gets here, than why are you using
    // this func: there is no Error to start skipping!
}

vector<double> get_vetor_from_ist(istream& ist)
{
    vector<double> double_vect;
    double i;

    while (true) {
        if (ist >> i) {
            double_vect.push_back(i);
        }
        else if (ist.eof()) {
            return double_vect;
        }
        else if (ist.fail()) {
            cout << '!' << "\n"
                 << "something is wrong with data" << '\n'
                 << "trying to continue..." << '\n'
                 << '!' << '\n';
            skip_to_double(ist);
        }
        else {
            error("Input stream critical error: unable to get numbers");
        }

    }
}


int main()
{
    ifstream ist; set_ifstream(ist);
    // ofstream ost; set_ofstream(ost);

    vector<double> numbers = get_vetor_from_ist(ist);

    int sum = 0;
    for (double i: numbers) {
        if (i - int(i) < 0.000001) {sum += i;}
    }

    cout << "The final sum of numbers in file is: " << sum << '\n';
}
