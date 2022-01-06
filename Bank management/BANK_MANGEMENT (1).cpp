#include <bits/stdc++.h>
using namespace std;
class Bank;
class Node;

ostream &operator<<(ostream &, const vector<string> &);

class Node
{
public:
    string name, address;
    int pin, balace = 0, transaction_limit = 10000;
    long long account_number, aadhar_number, phn_number;
};
class Bank
{
public:
    // BANK FUNCTIONS
    void create_account();
    void Deposit(long long);
    void withdraw(long long);
    void bank_to_bank_trasfer(long long);
    long long login();
    void lobby();
    void get_money_statement(long long);
    void update_info(long long);

    // SUPPORT FUCNTIONS
    int pin_create();
    void _delet_node(Node *);
    // FILE FUNCTIONS
    void write_to_file(Node *);
    void save_transaction_history(long long c_acc_number, long long r_acc_number, string trasaction_type, string receiver_name, int amount, long long befor_balace);
    bool isEmpty(string);
    long long find_last_acc_no();
    long long read_perticular_column_int(long long, int);
    string read_perticular_column_string(long long, int);
    void long_type_update_file(long long account_number, int index, long long updated_data);
    void string_type_update_file(long long account_number, int index, string updated_data);
    bool find_account(long long);

    void adimin_login();
};

int main()
{
    Bank obj;
    obj.lobby();

    return 0;
}

//----------------------------------------------BANK FUNCTIONS-----------------------------------------------------
void Bank ::lobby()
{

    int choice;
    char ch;
    int exi;
    do
    {
        cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\tEnter 1 To Login :\n";
        cout << "\t\t\t\tEnter 2 To Create Account :\n";
        cout << "\t\t\t\tEnter Your Choice : ";
        cin >> choice;
        while (true)
        {
            if (cin.fail())
            {

                cin.clear();
                cout << "\tINVALID INPUT \n";
                cin.ignore();
                cin >> choice;
            }
            else
            {
                break;
            }
        }
        cout << "\t----------------------------------------------------------------------\n";
        system("CLS");
        cout << "\n";
        if (choice == 1)
        {
            long long c_account_number = login();
            if (c_account_number == -1)
            {
                cout << "\tAccount Not Found\n";
            }
            else
            {
                do
                {
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    cout << "                                                        LOBBY                                                  \n";
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    cout << "\n";
                    cout << "Enter 1. to Deposit Money :\n";
                    cout << "Enter 2. to Withdraw Money :\n";
                    cout << "Enter 3. to Transfer Money :\n";
                    cout << "Enter 4. to Get Moneys tatement :\n";
                    cout << "Enter 5. to Update Information :\n";
                    cout << "Enter 6. to Exit Login Page:\n";
                    cout << "Enter Your Choice : ";
                    cin >> choice;
                    while (true)
                    {
                        if (cin.fail())
                        {

                            cin.clear();
                            cout << "\tINVALID INPUT \n";
                            cin.ignore();
                            cin >> choice;
                        }
                        else
                        {
                            break;
                        }
                    }

                    cout << "\n";
                    switch (choice)
                    {
                    case 1:
                        Deposit(c_account_number);
                        break;
                    case 2:
                        withdraw(c_account_number);
                        break;
                    case 3:
                        bank_to_bank_trasfer(c_account_number);
                        break;
                    case 4:
                        get_money_statement(c_account_number);
                        break;
                    case 5:
                        update_info(c_account_number);
                        break;
                    case 6:
                        goto down;
                        break;
                    default:
                        cout << "INVALID CHOICE\n";
                        break;
                    }
                    system("CLS");

                    cout << "Do You Want To Continue Enter Y  : \n";
                    cin >> ch;

                } while (ch == 'y' || ch == 'Y');
            }
        }
        else if (choice == 2)
        {
            create_account();
        }
        else
        {
            cout << "INVALID CHOICE ! :\n";
        }
    down:
        cout << "Enter 1 To Continue \n";
        cin >> exi;
        while (true)
        {
            if (cin.fail())
            {
                cin.clear();
                cout << "You have entered wrong input\n"
                     << endl;
                cin.ignore(numeric_limits<streamsize>::max());
                cin >> exi;
            }
            else
            {
                break;
            }
        }

    } while (exi == 1);
}
void Bank ::create_account()
{
    Node *temp = new Node();
    long long int temp_acc_no;
    temp_acc_no = find_last_acc_no();
    if (temp_acc_no == -1)
    {
        temp->account_number = 1003456001;
    }
    else
    {
        temp->account_number = temp_acc_no;
    }

    cout << "\tEnter Your Name : ";
    getline(cin >> ws, temp->name);
    cout << "\n";
    cout << "\tEnter Your Adhar Number : ";
    cin >> temp->aadhar_number;
    cout << "\n";
    cout << "\tEnter Your Mobile Number : ";
    cin >> temp->phn_number;
    cout << "\n";
    cout << "\tEnter Your Address : ";
    getline(cin >> ws, temp->address);
    cout << "\n";
    cout << "\tSet Your Pin : \n";
    temp->pin = pin_create();
    cout << "\tYour Trasaction Limit Is 10,000 \n";
    cout << "\tYour Account Number Is " << temp->account_number << " \n";
    write_to_file(temp);
    _delet_node(temp);
}

// DEPOSITE FUNCTION
void Bank ::Deposit(long long account_number)
{
    system("CLS");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                                        DEPOSITE                                                  \n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    int amount;
    long long current_balace, new_balace;
    if (isEmpty("database_bank_pro.csv"))
    {
        cout << "\tYou dont Have An Account /n";
    }
    else
    {
        cout << "\tEnter Amount : ";
        cin >> amount;
        current_balace = read_perticular_column_int(account_number, 4);
        new_balace = current_balace + amount;
        long_type_update_file(account_number, 4, new_balace);
        cout << "\t Transaction completed Your Current Balance Is " << new_balace << "\n";
        save_transaction_history(account_number, 0, "DEPOSITE", "0", amount, current_balace);
    }
    system("PAUSE");
}

// WITHDRAW FUNCTION

void Bank ::withdraw(long long account_number)
{

    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                                        WITHDRAW                                                  \n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";

    long long current_balalce = read_perticular_column_int(account_number, 4);
    long long transation_limit = read_perticular_column_int(account_number, 5);
    int amount;
    cout << "\tEnter The Amount : ";
    cin >> amount;
    if (current_balalce == 0)
    {
        cout << "\t You Have 0rs is In Your Account Please Deposite First.\n";
    }
    else if (amount > transation_limit)
    {
        cout << "\tTransaction Limit Exceeded\n";
        cout << "\tYour Current Trasaction Limit is " << transation_limit << "\n";
        cout << "\t Update Transaction Limit \n";
    }
    else if (current_balalce - amount < 0)
    {
        cout << "\tINSUFFICIENT BALANCE\n";
        cout << "\tYour Current Trasaction Limit is " << transation_limit << "\n";
    }

    else
    {
        int new_balance = current_balalce - amount;
        long_type_update_file(account_number, 4, new_balance);
        save_transaction_history(account_number, 0, "WITHDRAW", "0", amount, current_balalce);
        cout << "\tTransaction Complete Your Current Balanace is " << new_balance << ".\n";
    }
    system("PAUSE");
    system("CLS");
}

long long Bank ::login()
{

    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                                       LOGIN PAGE                                                  \n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";

    long long account_number;
    int pin, count = 3;
    cout << "\tEnter Your Account Number :";
    cin >> account_number;
    bool ans = find_account(account_number);
    if (ans == true)
    {
        cout << "\n";
    wrong_pin:
        cout << "\tEnter Your Pin :";
        cin >> pin;
        cout << "\n";

        long long check_pin = read_perticular_column_int(account_number, 3);

        if (check_pin == pin)
        {
            system("CLS");
            return account_number;
        }
        else
        {
            count--;
            if (count > 0)
            {
                cout << "\tWRONG PIN " << count << " ATTEMPT REMAINING\n";
                goto wrong_pin;
            }
            else
            {
                cout << "\t You Have Been Kicked Out \n ";
                return -1;
            }
        }
    }
    else
    {
        cout << "ACCOUNT NOT FOUND!!\n";
    }
    system("CLS");
}
// WRITEING TRASACTION HISTORY TO FILE
void Bank ::save_transaction_history(long long c_acc_num, long long r_acc_num, string trasaction_type, string receiver_name, int amount, long long befor_balace)
{

    time_t tim; // argument for function time()
    struct tm *ti;
    time(&tim);
    ti = localtime(&tim);
    string time = asctime(ti);
    fstream save_history;
    save_history.open("history_bank_database.csv", ios::out | ios ::app);
    long long current_balance = read_perticular_column_int(c_acc_num, 4);
    save_history << c_acc_num << "," << trasaction_type << "," << amount << "," << r_acc_num << "," << receiver_name << "," << current_balance << "," << befor_balace << "," << time << "\n";
    save_history.close();
}

// GET MONEYSTATEMENT

void Bank ::get_money_statement(long long account_number)
{

    fstream get_statement;
    get_statement.open("history_bank_database.csv", ios ::in);

    string line, word;
    int count = 1;
    vector<string> row_get_satement;
    cout << "-------------------------------------------------------------------------------------------------\n";
    cout << "                                                           MONEY STATEMENT                       \n";
    cout << "-------------------------------------------------------------------------------------------------\n";

    while (!get_statement.eof())
    {
        row_get_satement.clear();
        getline(get_statement, line, '\n');
        if (line.length() != 0)
        {
            long long acc = stol(line, nullptr, 10);
            if (acc == account_number)
            {
                stringstream statement(line);
                while (getline(statement, word, ','))
                {
                    row_get_satement.push_back(word);
                }
                cout << "\t";
                cout << count++ << "\n";
                cout << row_get_satement;
            }
        }
    }
    system("PAUSE");
    system("CLS");
    cout << "\n";
}

// BANK TO BANK TRASFER FUNCTION

void Bank ::bank_to_bank_trasfer(long long account_number)
{
    int r_current_balance;
    long long r_acc_no;
    int amount;
    cout << "\tEnter Receiver's Account Number : ";
    cin >> r_acc_no;
    bool ans = find_account(r_acc_no);
    string c_name = read_perticular_column_string(account_number, 6);
    if (ans == true)
    {
        cout << "\tEnter The Amount To Transfer : ";
        cin >> amount;
        int c_current_balance = read_perticular_column_int(account_number, 4);
        if (c_current_balance < 0 || c_current_balance - amount < 0)
        {
            cout << "\tINSUFFICIENT BALANCE\n";
            cout << "\tYour Current Balance Is " << c_current_balance << "\n";
        }
        else
        {
            cout << '\n';
            r_current_balance = read_perticular_column_int(r_acc_no, 4);
            int r_new_balance = r_current_balance + amount;
            long_type_update_file(r_acc_no, 4, r_new_balance);
            long_type_update_file(account_number, 4, c_current_balance - amount);
        }
        string r_name = read_perticular_column_string(r_acc_no, 6);
        save_transaction_history(account_number, r_acc_no, "FUND TRASFER", r_name, amount, c_current_balance);
        save_transaction_history(r_acc_no, account_number, "FUND RECEIVE", c_name, amount, r_current_balance);
    }
    system("PAUSE");
}

// UPDATE INFORMATION

void Bank ::update_info(long long account_number)
{
    // phone number
    // pin
    // addresss
    system("CLS");
    cout << "-------------------------------------------------------------------------------------------------\n";
    cout << "                                                           UPDATE INFO                      \n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    int input;
    long long l_new_data;
    string s_new_data;
    cout << "Enter 1 To Change Phone Number :\n";
    cout << "Enter 2 To Change Pin          :\n";
    cout << "Enter 3 To Change Address      :\n";
    cin >> input;
    while (true)
    {
        if (cin.fail())
        {
            cout << "INVALIDE INPUT!! ENTER AGAIN :";
            cin.clear();
            cin >> input;
        }
        else
        {
            break;
        }
    }

    if (input == 1)
    {
        cout << "Enter Your New Phone Number :";
        cin >> l_new_data;
        cout << '\n';
        long_type_update_file(account_number, 2, l_new_data);
    }
    else if (input == 2)
    {
        cout << "Enter Your New Pin :";
        cin >> l_new_data;
        cout << "\n";
        long_type_update_file(account_number, 3, l_new_data);
    }
    else if (input == 3)
    {
        cout << "Enter Your New Name :";
        cin >> s_new_data;
        cout << "\n";
        string_type_update_file(account_number, 6, s_new_data);
    }
    else
    {
        cout << "INVALID INPUT !";
    }
}
//----------------------------------------------FILE FUNCTIONS-----------------------------------------------------

// WRITE TO FILE FUNCTION
void Bank ::write_to_file(Node *temp)
{
    // account no
    // aadhar card
    // phone number
    // pin
    // balace
    // transaction limit
    // name
    // address
    fstream file;
    file.open("database_bank_pro.csv", ios ::out | ios::app);
    file << temp->account_number << "," << temp->aadhar_number << "," << temp->phn_number << "," << temp->pin << "," << temp->balace << "," << temp->transaction_limit << "," << temp->name << "," << temp->address << "\n";
    file.close();
}

// FIND NEW ACCOUNT NUMBER FOR ACCOUNT CREATION
long long Bank::find_last_acc_no()
{
    long long acc_no;
    string temp;
    fstream find_acc_no;
    find_acc_no.open("database_bank_pro.csv", ios ::in);

    if (isEmpty("database_bank_pro.csv"))
    {
        find_acc_no.close();
        return -1;
    }
    else
    {
        while (!find_acc_no.eof())
        {
            getline(find_acc_no, temp, '\n');
            if (temp.length() != 0) // this skips blanck lines in thd file(if read blank line then stol will throw error)
            {
                acc_no = stol(temp);
            }
        }

        find_acc_no.close();
        acc_no++;
        return acc_no;
    }
}

// (is_Empty) IS FILE IS EMPTY OR NOT FUNCTION

bool Bank ::isEmpty(string file_name)
{
    int length;
    fstream isem;
    isem.open(file_name, ios ::in);
    isem.seekg(0, ios::end); // put the "cursor" at the end of the file
    length = isem.tellg();   // find the position of the cursor
    isem.close();            // have to close close your file

    if (length == 0 || length == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// READ PERTICULAR COLUMN FUNCTION
long long Bank ::read_perticular_column_int(long long account_number, int index)
{
    fstream read_col;
    string line, word;
    vector<string> row1; // ALWAYS USE DIFFRENT NAME FOR VECTORS IN SAME PROGRAM
    long long acc, current_data;
    read_col.open("database_bank_pro.csv", ios ::in);
    while (!read_col.eof())
    {
        getline(read_col, line, '\n');
        if (line.length() != 0)
        {
            row1.clear();
            acc = stol(line, nullptr, 10);
            if (account_number == acc)
            {
                stringstream info(line);
                while (getline(info, word, ','))
                {
                    row1.push_back(word);
                }
                current_data = stol(row1[index]);
                return current_data;
            }
        }
    }
}

// (update_file) UPDATE FILE OR COUSTOMER DATA WHEN DEPOSITE OR WITHDRAW OR CHANGE PHONE NUMBER FUNCTION CALLED

void Bank ::long_type_update_file(long long account_number, int index, long long updated_data)
{
    fstream open_existing_file;
    fstream create_new_file;
    vector<string> row_up_file;
    string line, word;
    open_existing_file.open("database_bank_pro.csv", ios ::in);
    create_new_file.open("new_database_bank_pro.csv", ios ::out);
    long long acc_no;

    while (!open_existing_file.eof())
    {
        row_up_file.clear();
        getline(open_existing_file, line);
        if (line.length() != 0)
        {
            stringstream spr(line);
            while (getline(spr, word, ','))
            {
                row_up_file.push_back(word);
            }
            acc_no = stol(row_up_file[0]);
            int row_size = row_up_file.size();
            if (acc_no == account_number)
            {
                stringstream conver;
                conver << updated_data;
                row_up_file[index] = conver.str();
                if (!open_existing_file.eof())
                {
                    for (int i = 0; i < row_size - 1; i++)
                    {
                        create_new_file << row_up_file[i] << ",";
                    }
                    create_new_file << row_up_file[row_size - 1] << "\n";
                }
            }
            else
            {
                if (!open_existing_file.eof())
                {
                    for (int i = 0; i < row_size - 1; i++)
                    {
                        create_new_file << row_up_file[i] << ",";
                    }
                    create_new_file << row_up_file[row_size - 1] << "\n";
                }
            }
        }
    }
    open_existing_file.close();
    create_new_file.close();
    remove("database_bank_pro.csv");
    rename("new_database_bank_pro.csv", "database_bank_pro.csv");
}

// FIND ACCOUNT FUNCTION
bool Bank ::find_account(long long account_number)
{
    fstream find_acc_no;
    find_acc_no.open("database_bank_pro.csv", ios ::in);
    string line;

    while (!find_acc_no.eof())
    {
        getline(find_acc_no, line, '\n');
        if (line.length() != 0)
        {
            long long check_r_acc_no = stol(line, nullptr, 10);
            if (check_r_acc_no == account_number)
            {
                find_acc_no.close();
                return true;
            }
        }
    }
    find_acc_no.close();
    return false;
}
// READ STRING DATA ONLY FUNCTION
string Bank ::read_perticular_column_string(long long account_number, int index)
{
    fstream read_col_str;
    read_col_str.open("database_bank_pro.csv", ios ::in);
    string line, word;
    vector<string> row_str_col;
    long long check_acc_no;
    string data_to_return;
    while (!read_col_str.eof())
    {
        getline(read_col_str, line, '\n');
        if (line.length() != 0)
        {
            row_str_col.clear();
            check_acc_no = stol(line, nullptr, 10);
            if (account_number == check_acc_no)
            {
                stringstream str_data(line);
                while (getline(str_data, word, ','))
                {
                    row_str_col.push_back(word);
                }
                data_to_return = row_str_col[index];
                row_str_col.clear();
                return data_to_return;
            }
        }
    }

    read_col_str.close();
}
// UPDATE STRING DATA
void Bank ::string_type_update_file(long long account_number, int index, string updated_data)
{
    fstream open_existing_file;
    fstream create_new_file;
    vector<string> row_up_file;
    string line, word;
    open_existing_file.open("database_bank_pro.csv", ios ::in);
    create_new_file.open("new_database_bank_pro.csv", ios ::out);
    long long acc_no;

    while (!open_existing_file.eof())
    {
        row_up_file.clear();
        getline(open_existing_file, line);
        if (line.length() != 0)
        {
            stringstream spr(line);
            while (getline(spr, word, ','))
            {
                row_up_file.push_back(word);
            }
            acc_no = stol(row_up_file[0]);
            int row_size = row_up_file.size();
            if (acc_no == account_number)
            {
                stringstream conver;
                conver << updated_data;
                row_up_file[index] = conver.str();
                if (!open_existing_file.eof())
                {
                    for (int i = 0; i < row_size - 1; i++)
                    {
                        create_new_file << row_up_file[i] << ",";
                    }
                    create_new_file << row_up_file[row_size - 1] << "\n";
                }
            }
            else
            {
                if (!open_existing_file.eof())
                {
                    for (int i = 0; i < row_size - 1; i++)
                    {
                        create_new_file << row_up_file[i] << ",";
                    }
                    create_new_file << row_up_file[row_size - 1] << "\n";
                }
            }
        }
    }
    open_existing_file.close();
    create_new_file.close();
    remove("database_bank_pro.csv");
    rename("new_database_bank_pro.csv", "database_bank_pro.csv");
}
//----------------------------------------------SUPPORT FUNCTIONS-----------------------------------------------------

// PIN CREATION FUNCTION
int Bank ::pin_create()
{

    int pin;
    cout << "\t-----------------Pin Creation-------------------- \n\n";
    cout << "\tEnter Only Four Digit  Pin : ";
    cin >> pin;
    cout << "\n";
    do
    {
        if (pin > 1000 && pin < 9999)
        {
            return pin;
        }
        else
        {
            cout << "\tINVALID PIN ( ENTER FOUR DIGIT ONLY) \n";
            cin >> pin;
        }
    } while (pin < 1000 || pin > 9999);
}

// DELETE NODE FUNCTION
void Bank ::_delet_node(Node *temp)
{
    delete temp;
}

// << OVERLOADING

ostream &operator<<(ostream &os, const vector<string> &v)
{

    os << "\tYOUR ACCOUNT NUMBER :- ";
    os << v[0];
    os << "\n";
    os << "\tTRANSACTION TYPE :- " << v[1] << "\n";
    if (v[1] == "DEPOSITE" || v[1] == "WITHDRAW")
    {
        if (v[1] == "Deposite")
        {
            os << "\t\tTrasacation Date & Time : " << v[7] << " .\n";
            os << "\t\tYour Balace Before Trasaction Was " << v[6] << " .\n";
            os << "\t\tDeposited Amount Is " << v[2] << " .\n";
            os << "\t\tYour Balace After Trascation Is " << v[5] << " .\n";
        }
        else
        {
            os << "\t\tTrasacation Date & Time : " << v[7] << " .\n";
            os << "\t\tYour Balace Before Trasaction Was " << v[6] << ".\n";
            os << "\t\tWithdrawn Amount Is " << v[2] << "\n";
            os << "\t\tYour Balace After Trascation Is " << v[5] << ".\n";
        }
        os << "\n\n";
    }
    else
    {

        os << "\t\tTrasacation Date & Time : " << v[7] << " .\n";
        os << "\t\tAccount Number Of Receiver Is " << v[3] << ".\n";
        os << "\t\tReceiver's Name  Is " << v[4] << "\n";
        os << "\t\tYour Balace Before Trasaction Was " << v[6] << ".\n";
        os << "\t\tTransfred Amount Is " << v[2] << "\n";
        os << "\t\tYour Balace After Trascation Is " << v[5] << ".\n";
        os << "\t\n\n";
    }
    return os;
}

void Bank ::adimin_login()
{
}