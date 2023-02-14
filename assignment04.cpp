#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

/**
 * @brief A class that will store all identifiers for a variable or function
 */
class Identifier_List {
private:
    Identifier_List() = delete;  // default constructor (never used)
public:
    string name;       // the name of the variable or function
    bool is_variable;  // true if this object represents a variable, false if a function
    string type;       // the data type of the variable, or data type returned by the function

    Identifier_List(string n, bool iv, string t);
    void display();
};

Identifier_List::Identifier_List(string n, bool iv, string t) {
    name = n;
    is_variable = iv;
    type = t;
}

void Identifier_List::display() {
    cout << "[ " << name << " | " << is_variable << " | " << type << " ] ";
}

class Hash_Table {
private:
    int capacity;                         // the capacity of the table
    vector<list<Identifier_List>> table;  // the table itself
    Hash_Table() = delete;                // default constructor (never used)
public:
    Hash_Table(int initial_capacity);
    void insert(Identifier_List id_list);
    void delete_this(string name_to_delete);
    bool search(string name_to_search);
    int hash(string name);
    void display();
};

Hash_Table::Hash_Table(int initial_capacity) {
    capacity = initial_capacity;
    // Initialize the hash table by pushing empty lists into it:
    for (int i = 0; i < capacity; i++) {
        table.push_back(list<Identifier_List>());
    }
}

void Hash_Table::insert(Identifier_List id_list) {
    //
}

void Hash_Table::delete_this(string name_to_delete) {
    //
}

bool Hash_Table::search(string name_to_search) {
    //
}

int Hash_Table::hash(string name) {
    int hash_value = 0;
    for (char c : name) {
        hash_value += (int) c;
    }
    return hash_value % capacity;
}

void Hash_Table::display() {
    for (int i = 0; i < capacity; i++) {
        cout << "index " << i << ": ";
        list<Identifier_List> this_list = table[i];
        for (auto id_list : this_list) {
            id_list.display();
        }
        cout << endl;
    }
}

/**
 * @brief Reads a series of inputs from the given file and builds a hash table
 * @param file_name: the .txt file that serves as the source of the input for the hash table
 * @param initial_capacity: the number of index spots initially available in the hash table
 */
void build_from_file(string filename) {
    ifstream the_file(filename);

    if(!the_file.is_open()){
        cout << "File not found: " << filename << endl;
        throw invalid_argument("File not found: " + filename);
    }

    string x;
    the_file >> x;    // reads "initial_capacity" and ignores

    int initial_capacity;
    the_file >> initial_capacity;

    string y;
    the_file >> y;    // reads "num_identifiers" and ignores

    int num_identifiers;
    the_file >> num_identifiers;

    Hash_Table ht(initial_capacity);

    string name;
    bool is_variable;
    string type;

    for(int i = 0; i < num_identifiers; i++)  {
        the_file >> name;
        the_file >> is_variable;
        the_file >> type;
        Identifier_List id_list(name, is_variable, type);
        ht.insert(id_list);
    }
    ht.display();

    string operation, operand, has_type;
    bool is_var;

    while (the_file >> operation) {
        the_file >> operand;

        if (operation == "delete") {
            cout << "\n>>> Delete: " << operand << endl;
            ht.delete_this(operand);
        } else if (operation == "insert") {
            cout << "\n>>> Insert: " << operand << endl;
            bool is_var;
            string has_type;
            the_file >> is_var >> has_type;
            Identifier_List id_list(operand, is_var, has_type);
            ht.insert(id_list);
            ht.display();
        } else if (operation == "search") {
            cout << "\n>>> Search: " << operand << " - ";
            bool found = ht.search(operand);
            string s = found ? "found!" : "not found!";
            cout << s << endl;
        }
    }
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        cout << "Please try again!" << endl
             << "Correct usage: " << argv[0] << " <filename.txt>" 
             << endl;
        exit(1);
    }
    string filename = argv[1];
    build_from_file(filename);
}
