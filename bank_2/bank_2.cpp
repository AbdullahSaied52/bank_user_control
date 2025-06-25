#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
//#include<algorithm>
using namespace std;

struct client
{
    string name;
    string pin;
    string phnumber;
    string accbalance;
    string accnumber;
};
struct user
{
    string name;
    string pass;
    string permisions;
};
user used_user_in_login;
vector<string> data_client_fromfile();
vector<client>vector_clientslist(vector<string>vec);
void play(string p);
void manage_user();
void login();
//---------------add client from user to file
client struct_addnewclient()
{
    vector<client>fromfile;
    fromfile = vector_clientslist(data_client_fromfile());
    client val;
    bool q = false;
    cout << "enter account number : ";
    getline(cin >> ws, val.accnumber);
    for (int i = 0; i < fromfile.size(); i++)
    {
        if (val.accnumber == fromfile[i].accnumber)
        {
            q = true;
        }
    }
    if (q == true)
    {
        cout << "it is here " << endl;
        return struct_addnewclient();
    }
    cout << "enter name : ";
    getline(cin, val.name);
    cout << "enter phone number : ";
    getline(cin, val.phnumber);
    cout << "enter pin number : ";
    getline(cin, val.pin);
    cout << "enter account balance : ";
    getline(cin, val.accbalance);
    return val;
}

vector<client>vector_newclients()
{
    vector<client>data;
    data.push_back(struct_addnewclient());

    return data;
}

void data_fromuser_uptofile(vector<client>data, string dil = "#//#")
{
    vector<client>dd;
    dd = data;
    //bool t = false;
    //cout << "enter account number :";
    //string f;
    //getline(cin >> ws, f);

    //for (int s = 0; s < dd.size(); s++)
    //{
    //    if (dd[s].accnumber == f)
    //    {
    //        t = true;
    //    }
    //}
    //if (t = true)
    //{
    //    cout << "already here " << endl;
    //    data_fromuser_uptofile(dd);
    //}
    fstream file;
    string h = "";
    file.open("clientdata.txt", ios::app);
    for (client& n : data)
    {
        h += n.accnumber + dil;
        h += n.name + dil;
        h += n.phnumber + dil;
        h += n.pin + dil;
        h += n.accbalance;
        file << h;
        file << endl;
        h = "";
    }
    file.close();
}
//---------------------------------

//-----------------take data from file
vector<client>vector_clientslist(vector<string>vec)
{
    vector<client>clent;
    client ss;
    int i = 0;
    while (vec.size() > 0)
    {
        ss.accnumber = vec[i];
        ss.name = vec[i + 1];
        ss.phnumber = vec[i + 2];
        ss.pin = vec[i + 3];
        ss.accbalance = vec[i + 4];
        vec.erase(vec.begin() + 0, vec.begin() + 5);
        clent.push_back(ss);
    }
    return clent;
}

vector<string> data_client_fromfile()
{
    string c = "#//#";
    vector<string>clientt;
    fstream file;
    file.open("clientdata.txt", ios::in);
    string data;
    while (getline(file, data))
    {
        string h = "";
        int x = data.find("#//#");
        while (x > 0)
        {
            for (int i = 0; i < x; i++)
            {
                h += data[i];
            }
            clientt.push_back(h);
            h = "";
            data.erase(0, x + c.length());
            x = data.find(c);
        }
        h = data;
        clientt.push_back(h);
    }
    file.close();
    return clientt;
}
//----------------

void update_data_sendtofile(vector<client>vec, string dil = "#//#")
{
    fstream file;
    string h;
    file.open("clientdata.txt", ios::out);
    h += vec[0].accnumber + dil;
    h += vec[0].name + dil;
    h += vec[0].phnumber + dil;
    h += vec[0].pin + dil;
    h += vec[0].accbalance;
    file << h;
    file << endl;
    h = "";
    file.close();
    file.open("clientdata.txt", ios::app);
    for (int i = 1; i < vec.size(); i++)
    {
        h += vec[i].accnumber + dil;
        h += vec[i].name + dil;
        h += vec[i].phnumber + dil;
        h += vec[i].pin + dil;
        h += vec[i].accbalance;
        file << h;
        file << endl;
        h = "";
    }
    file.close();
}

vector<client>delete_client(vector<client>vecc)
{
    vector<client>dc;
    string fin;
    bool t = false;
    while (t == false)
    {
        cout << "enter account number of client: ";
        cin >> fin;
        for (int i = 0; i < vecc.size(); i++)
        {
            if (fin == vecc[i].accnumber)
            {
                t = true;
                continue;
            }
            else
            {
                dc.push_back(vecc[i]);
            }
        }
        if (t == false)
        {
            cout << "not here " << endl;
        }
    }
    update_data_sendtofile(dc);
    return dc;
}

client struct_update_client(string ss)
{
    client val;
    val.accnumber = ss;
    cout << "enter name : ";
    getline(cin >> ws, val.name);
    cout << "enter phone number : ";
    getline(cin, val.phnumber);
    cout << "enter pin number : ";
    getline(cin, val.pin);
    cout << "enter account balance : ";
    getline(cin, val.accbalance);
    return val;
}

vector<client>update_client(vector<client>vecc)
{
    vector<client>up;
    vector<client>old;
    old = vecc;
    bool t = false;
    cout << "enter account number of client :";
    string n;
    cin >> n;
    for (int i = 0; i < vecc.size(); i++)
    {
        if (vecc[i].accnumber == n)
        {
            t = true;
            for (client& s : vecc)
            {
                if (s.accnumber == n)
                {
                    up.push_back(struct_update_client(n));
                }
                else
                    up.push_back(s);
            }
            update_data_sendtofile(up);
        }
    }
    if (t == false)
    {
        cout << "not here" << endl;
        return update_client(old);
    }
    return up;
}

void showclients_list()
{
    vector<string>data;
    vector<client>st_vectordata;
    data = data_client_fromfile();
    st_vectordata = vector_clientslist(data);

    printf("                  clients list (%d) client", st_vectordata.size());
    cout << endl;
    cout << endl;
    cout << left << setw(15) << "|name" << setw(20) << "|account number"
        << setw(15) << "|phone number" << setw(15) << "|pin code" <<
        setw(15) << "|account balance";
    cout << endl;

    for (int i = 0; i < st_vectordata.size(); i++)
    {
        cout << left << setw(15) << st_vectordata[i].name << setw(20) << st_vectordata[i].accnumber
            << setw(15) << st_vectordata[i].phnumber << setw(15) << st_vectordata[i].pin <<
            setw(15) << st_vectordata[i].accbalance;
        cout << endl;
    }
}

void deposit()
{
    bool t = true;
    string acc;
    int s;
    int sac;
    cout << "enter account number :";
    cin >> acc;
    vector<client>data;
    data = vector_clientslist(data_client_fromfile());
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].accnumber == acc)
        {
            cout << " there are client details " << endl;
            cout << "account number :" << data[i].accnumber << endl;
            cout << "name :" << data[i].name << endl;
            cout << "pin code :" << data[i].pin << endl;
            cout << "phone number :" << data[i].phnumber << endl;
            cout << "account balance :" << data[i].accbalance << endl;
            cout << "enter deposit amount : ";
            cin >> s;
            sac = stoi(data[i].accbalance);
            data[i].accbalance = to_string(sac + s);
            t = true;
            break;
        }
        else
            t = false;
    }
    if (t == false)
    {
        cout << "not here " << endl;
        deposit();
    }
    update_data_sendtofile(data);
}

void withdraw()
{
    bool t = true;
    string acc;
    int s;
    int sac;
    cout << "enter account number :";
    cin >> acc;
    vector<client>data;
    data = vector_clientslist(data_client_fromfile());
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].accnumber == acc)
        {
            cout << " there are client details " << endl;
            cout << "account number :" << data[i].accnumber << endl;
            cout << "name :" << data[i].name << endl;
            cout << "pin code :" << data[i].pin << endl;
            cout << "phone number :" << data[i].phnumber << endl;
            cout << "account balance :" << data[i].accbalance << endl;


            sac = stoi(data[i].accbalance);
            int nn = 1;
            while (nn > 0)
            {
                cout << "enter withdraw amount : ";
                cin >> s;
                if (s < sac)
                {
                    data[i].accbalance = to_string(sac - s);
                    nn = -1;
                }
                else
                {
                    cout << "amount exceeds the balance , you can draw up to " << sac << endl;
                }
            }
            t = true;
            break;
        }
        else
            t = false;
    }
    if (t == false)
    {
        cout << "not here " << endl;
        deposit();
    }
    update_data_sendtofile(data);
}

void totalbalance()
{
    vector<client>data;
    data = vector_clientslist(data_client_fromfile());
    cout << left << setw(15) << "|name" << setw(20) << "|account number" <<
        setw(15) << "|account balance";
    cout << endl;
    for (client& s : data)
    {
        cout << left << setw(15) << s.name << setw(20) << s.accnumber <<
            setw(15) << s.accbalance;
        cout << endl;
    }
}

void goback()
{
    cout << "press to go back" << endl;
    system("pause>0");
    system("cls");
    play(used_user_in_login.permisions);
}
void goback_touser()
{
    cout << "press to go back" << endl;
    system("pause>0");
    system("cls");
    manage_user();
}


void transaction()
{
    cout << "[1] deposit" << endl;
    cout << "[2] withdraw" << endl;
    cout << "[3] total balance" << endl;
    cout << "[4] main menu" << endl;
    int n;
    cin >> n;
    switch (n)
    {
    case(1):system("cls");
        deposit();
        transaction();
        break;
    case(2):system("cls");
        withdraw();
        transaction();
        break;
    case(3):system("cls");
        totalbalance();
        transaction();
        break;
    case(4):system("cls");
        goback();
        break;
    }

}
void find_client()
{
    cout << "enter client account number: ";
    string accnum;
    cin >> accnum;
    vector<string>data;
    vector<client>st_vectordata;
    data = data_client_fromfile();
    st_vectordata = vector_clientslist(data);
    for (int i = 0;i < st_vectordata.size();i++)
    {
        if (st_vectordata[i].accnumber == accnum)
        {
            cout<<"                    client";
            cout << endl;
            cout << endl;
            cout << left << setw(15) << "|name" << setw(20) << "|account number"
                << setw(15) << "|phone number" << setw(15) << "|pin code" <<
                setw(15) << "|account balance";
            cout << endl;
            cout << left << setw(15) << st_vectordata[i].name << setw(20) << st_vectordata[i].accnumber
                << setw(15) << st_vectordata[i].phnumber << setw(15) << st_vectordata[i].pin <<
                setw(15) << st_vectordata[i].accbalance;
            cout << endl;
        }
    }
}
//********************user*************
vector<string> data_user_from_file_to_string()
{
    vector<string>user_data;
    fstream file;
    file.open("users.txt", ios::in);
    string data;
    int x = 0;
    while (getline(file, data))
    {
        string h = "";
        x= data.find("#//#");
        while (x > 0)
        {
            for (int i = 0;i < x;i++)
            {
                h += data[i];
            }
            user_data.push_back(h);
            h = "";
            data.erase(0, x + 4);
            x = data.find("#//#");
        }
        h = data;
        user_data.push_back(h);
    }
    file.close();
    return user_data;
}
vector<user>data_user_from_file_to_struct()
{
    vector<string>d;
    d = data_user_from_file_to_string();
    vector<user>data;
    user temp;
    while (d.size() > 0)
    {
        temp.name = d[0];
        temp.pass = d[1];
        temp.permisions = d[2];
        data.push_back(temp);
        d.erase(d.begin() + 0, d.begin() + 3);
    }
    return data;
}
void list_users()
{
    vector<user>users_data;
    users_data = data_user_from_file_to_struct();
    printf("                  users list (%d) user", users_data.size());
    cout << endl;
    cout << endl;
    cout << left << setw(15) << "|name" << setw(20) << "|passward"
        << setw(15) << "|permissions";
    cout << endl;
    for (int i = 0; i < users_data.size(); i++)
    {
        cout << left << setw(15) << users_data[i].name << setw(20) << users_data[i].pass
            << setw(15) << users_data[i].permisions;
        cout << endl;
    }
    
}
string permessions()
{
    string asks[7] = { "show client list","delete client","update client info",
                "add new client"," transactions","find client","manage users" };
    string asks_2="";
    string y_n;
    cout << "do you want to give access to: " << endl;
    for (int i = 0;i < 7;i++)
    {
        cout << asks[i] << " (y/n):  ";
        cin >> y_n;
        if (y_n == "y")
        {
            asks_2 += "1";
        }
        else
            asks_2+= "0";
        cout << endl;
    }
    return asks_2;
}
user add_new_user_from_console()
{
    user temp;
    vector<user>current_users;
    current_users = data_user_from_file_to_struct();
    cout << "enter user name : ";
    string name,passward;
    string permision;
    cin >> name;
    bool here=false;
    for (int i = 0;i < current_users.size();i++)
    {
        if (name == current_users[i].name)
        {
            here = true;
        }
    }
    if (here)
    {
        cout << "it's here " << endl;
        add_new_user_from_console();
    }
    else
    {
        temp.name = name;
        cout << "enter passward : ";
        cin >> passward;
        cout<< "does he have full permesions(y/n) : ";
        string ask;
        cin >> ask;
        if (ask == "y")
        {
            permision = "-1";
        }
        else
        {
            permision = permessions();
        }
    }
    temp.name = name;
    temp.pass = passward;
    temp.permisions = permision;
    return temp;
}
void send_a_user_info_to_file(user data,string dil="#//#")
{
    int dec_value ;
    /* to convert permissions from string to integer */
    if ((data.permisions) != "-1")
    {
        dec_value = 0;
        int num = stoi(data.permisions);

        int base = 1;

        int temp = num;

        while (temp > 0)
        {
            int last_digit = temp % 10;
            temp = temp / 10;

            dec_value += last_digit * base;

            base = base * 2;
        }
    }
    else
        dec_value = stoi(data.permisions);
    vector<user>dd;
    dd.push_back(data);
    fstream file;
    string h = "";
    
    file.open("users.txt", ios::app);

    h += data.name + dil;
    h += data.pass + dil;
    h += to_string(dec_value);

    file << h;
    file << endl;
    h = "";
    file.close();
}
vector<user>delete_user()
{
    vector<user>users_from_file;
    users_from_file = data_user_from_file_to_struct();
    vector<user>new_data_of_users;
    string name,ask;
    cout << "enter name :";
    cin >> name;
    bool is_here = false;
    for (int i = 0;i < users_from_file.size();i++)
    {
        if (users_from_file[i].name == name)
        {
            is_here = true;
            cout << endl;
            cout << "do you want to delete (y/n) :";
            cin >> ask;
            if (ask == "y")
            {
                cout << "done " << endl;
            }
            else
                new_data_of_users.push_back(users_from_file[i]);
        }
        else
        {
            new_data_of_users.push_back(users_from_file[i]);
        }
    }
    if (!is_here)
    {
        cout << "not here, enter again " << endl;
        delete_user();
    }
    else
    {
        return new_data_of_users;
    }
    
}
void send_vector_users_to_file_and_delete_old_data(vector<user>data_users)
{
    fstream file;
    file.open("users.txt", ios::out);
    file << "";
    file.close();
    for (int i = 0;i < data_users.size();i++)
    {
        send_a_user_info_to_file(data_users[i]);
    }
}
void update_users()
{
    vector<user>data_of_users;
    data_of_users = data_user_from_file_to_struct();
    cout << "enter user name: ";
    string name1;
    cin >> name1;
    bool is_here = false;
    for (int i = 0;i < data_of_users.size();i++)
    {
        if (data_of_users[i].name == name1)
        {
            is_here = true;
            user temp;
            vector<user>current_users;
            current_users = data_user_from_file_to_struct();
            string name, passward;
            string permision;
            name=name1;

            temp.name = name;
            cout << "enter passward : ";
            cin >> passward;
            cout << "does he have full permesions(y/n) : ";
            string ask;
            cin >> ask;
            if (ask == "y")
            {
                permision = "-1";
            }
            else
            {
                permision = permessions();
            }
            
            temp.name = name;
            temp.pass = passward;
            temp.permisions = permision;
            
            cout << "do you want to update (y/n): ";
            string ask2;
            cin >> ask2;
            if (ask2 == "y")
            {
                data_of_users[i] = temp;
                send_vector_users_to_file_and_delete_old_data(data_of_users);
            }
            else
                send_vector_users_to_file_and_delete_old_data(data_of_users);
            
        }
    }
    if (!is_here)
    {
        cout << "not here, enter again " << endl;
        update_users();
    }

}
void find_user()
{
    vector<user>users_data;
    users_data = data_user_from_file_to_struct();
    cout << "enter user name: ";
    string name;
    cin >>name;
    bool is_here = false;
    for (int i = 0; i < users_data.size(); i++)
    {
        if (name == users_data[i].name)
        {
            cout << left << setw(15) << "|name" << setw(20) << "|passward"
                << setw(15) << "|permissions";
            cout << endl;
            cout << left << setw(15) << users_data[i].name << setw(20) << users_data[i].pass
                << setw(15) << users_data[i].permisions;
            cout << endl;
            is_here = true;

        }

    }
        if(!is_here)
        {
            cout << "not here ,enter again" << endl;
            find_user();
        }
}

void manage_user()
{
    cout << "[1] list users" << endl;
    cout << "[2] add new user " << endl;
    cout << "[3] delete user" << endl;
    cout << "[4] update user " << endl;
    cout << "[5] find user" << endl; 
    cout << "[6] main menue" << endl;
    cout << "choose : ";
    int choose;
    cin >> choose;
    system("cls");
    switch (choose)
    {
    case (1):list_users();
        goback_touser();
        break;
    case(2):send_a_user_info_to_file(add_new_user_from_console());
        goback_touser();
        break;
    case(3):send_vector_users_to_file_and_delete_old_data(delete_user());
        goback_touser();
        break;
    case(4):update_users();
        goback_touser();
        break;
    case(5):find_user();
        goback_touser();
        break;
    case(6):play(used_user_in_login.permisions);
        break;
    }
}
//*************************************
void play(string p)
{
    string perm;
    
    if (p != "-1")
    {
        int n = stoi(p);
        string bin = "";
        while (n > 0) {
            // checking the mod 
            int bit = n % 2;
            bin.push_back('0' + bit);
            n /= 2;
        }
        // reverse the string 
        reverse(bin.begin(), bin.end());
        perm = bin;
        if (perm.length() < 7)
        {
            int nn = perm.length();
            for (int i = 0;i <= nn;i++)
            {
                perm = "0" + perm;
            }
        }
    }
    else
    {
        perm = "1111111";
    }

    vector<string>data;
    vector<client>st_vectordata;
    data = data_client_fromfile();
    st_vectordata = vector_clientslist(data);

    int n;
    cout << "[1] show client list " << endl;
    cout << "[2] delete client " << endl;
    cout << "[3] update client info " << endl;
    cout << "[4] add new client " << endl;
    cout << "[5] transactions" << endl;
    cout << "[6] find client" << endl;
    cout << "[7] manage users" << endl;
    cout << "[8] log out" << endl;
    cin >> n;

    system("cls");
    
    if ( n == 8 || perm[n-1] == '1')// stoi(perm) == 1 , because (stoi) convert it to positive integer
    {
        switch (n)
        {
        case(1):showclients_list();
            goback();
            break;
        case(2):delete_client(st_vectordata);
            goback();
            break;
        case(3):update_client(st_vectordata);
            goback();
            break;
        case(4):data_fromuser_uptofile(vector_newclients());
            goback();
            break;
        case(5):transaction();
            goback();
            break;
        case(6): find_client();
            goback();
            break;
        case(7):manage_user();
            break;
        case(8):login();
            break;
        }
    }
    else
    {
        cout << "doesn't have access to this "<<endl;
        system("pause>0");
        system("cls");
        play(p);
    }
}

void login()
{
    vector<user>user_data;
    
    user_data = data_user_from_file_to_struct();
    string user_name;
    string passward;
    cout << "enter user name : ";
    cin >> user_name;
    cout << "enter passward : ";
    cin >> passward;
    bool is_data_correct = false;
    for (int i = 0;i < user_data.size();i++)
    {
        if (user_data[i].name == user_name && user_data[i].pass == passward)
        {
            is_data_correct = true;
            used_user_in_login = user_data[i];
        }
    }
    if (!is_data_correct)
    {
        cout << "not correct , enter again  " << endl;
        login();

    }
    else
    {
        play(used_user_in_login.permisions);
    }
    
}



int main()
{
    
    login();
    return 0;
}