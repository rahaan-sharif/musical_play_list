#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <random>
using namespace std;
#define start_pl tmp1->start

class play_list; // prototype

class input_file // checked***
{
private:
    int id;
    string main_str;
    input_file *next;

public:
    input_file(int i, string s)
    {
        id = i;
        main_str = s;
        next = NULL;
    }
    void create_node(input_file *&start, string s)
    {
        if (start == NULL)
        {
            start = new input_file(0, s);
            return;
        }
        else
        {
            input_file *tmp = start;
            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = new input_file(tmp->id + 1, s);
            return;
        }
    }
    void show(input_file *start)
    {
        while (start != NULL)
        {
            cout << start->id << "\t\t" << start->main_str << endl
                 << endl;
            start = start->next;
        }
    }
    string get_music(input_file *start, int i)
    {
        while (start != NULL)
        {
            if (start->id == i)
            {
                return start->main_str;
            }
            else
            {
                start = start->next;
            }
        }
        cout << "error! there is no music with given id.\n";
        return NULL;
    }
};

class ap // all play lists           checked***
{
public:
    int id;
    string name;
    play_list *start;
    ap *next;

    ap(int i, string n)
    {
        start = NULL;
        name = n;
        id = i;
        next = NULL;
    }
    void add_pl(ap *&start, string n)
    {
        if (start == NULL)
        {
            start = new ap(0, n);
            return;
        }
        else
        {
            ap *tmp = start;
            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = new ap(tmp->id + 1, n);
            return;
        }
    }
    void delete_pl(ap *&start, int i)
    {
        if (start == NULL)
        {
            cout << "error! there is no play list to remove.\n";
            return;
        }
        else if (start->id == i)
        {
            ap *tmp = start;
            start = start->next;
            delete tmp;
            return;
        }
        else
        {
            ap *tmp = start;
            while (tmp->next != NULL)
            {
                if (tmp->next->id == i)
                {
                    ap *tt = tmp->next;
                    tmp->next = tmp->next->next;
                    delete tt;
                    return;
                }
                tmp = tmp->next;
            }
            return;
        }
    }
    void show(ap *start)
    {
        cout << "number\t\tid\t\tname\n";
        int number = 0;

        while (start != NULL)
        {
            cout << number++ << "\t\t" << start->id << "\t\t" << start->name << endl;
            start = start->next;
        }
        cout << endl
             << endl;
    }
    play_list*& get_pl(ap *start, int i)
    {
        while (start != NULL)
        {
            if (start->id == i)
            {
                return start->start;
            }
            start = start->next;
        }

        cout << "error! no such play list\n";
        play_list* tmp_pl=NULL;
        return tmp_pl;
    }
};

class play_list // checked ***
{
private:
    int count;
    int id;
    string name;
    string address;
    play_list *next;
    play_list *prev;

public:
    int idd;
    play_list(int i, string n, string a)
    {
        count = -1;
        id = i;
        idd=id;
        name = n;
        address = a;
        next = NULL;
        prev = NULL;
    }
    void add(play_list *&start, string n, string a)
    {
        if (start == NULL)
        {
            start = new play_list(0, n, a);
            start->prev = NULL;
            return;
        }
        else
        {
            play_list *tmp = start;
            while (tmp->next != NULL && tmp->name != n)
                tmp = tmp->next;
            if (tmp->name == n)
                return;
            tmp->next = new play_list(tmp->id + 1, n, a);
            tmp->next->prev = tmp;
        }
    }
    void remove(play_list *&start, int i)
    {
        if (start == NULL)
        {
            cout << "error! play list is empty.\n";
            return;
        }
        else if(start->next==NULL && start->id==i)
        {
            play_list* tmp=start;
            start=NULL;
            delete tmp;
            return;
        }
        else if (i == start->id)
        {
            play_list *tmp = start;
            start->next->prev = NULL;
            start = start->next;
            delete tmp;
            return;
        }
        else
        {
            play_list *tmp = start;
            while (tmp->next->id != i)
            {
                tmp = tmp->next;
                if (tmp == NULL)
                {
                    cout << "error! invalid id.\n";
                    return;
                }
            }
            play_list *tt = tmp->next;
            tmp->next->next->prev = tmp;
            tmp->next = tmp->next->next;
            delete tt;
        }
    }
    void show(play_list *start)
    {
        if(start==NULL)
        {
            cout<<"empty\n";
            return;
        }
        cout << "number\t\tid\t\tname\n";
        int number = 1;

        while (start != NULL)
        {
            cout << number++ << "\t\t" << start->id << "\t\t" << start->name << endl;
            start = start->next;
        }
    }
    void random_play(play_list *start)
    {
        int count = 0;
        play_list *tmp = start;
        while (tmp != NULL)
        {
            count += 1;
            tmp = tmp->next;
        }
        int rand_id = rand() % count;
        start->es_play(start, rand_id);
    }
    void loop_play(play_list *start)
    {
        play_list *tmp = start;
        while (tmp != NULL)
        {
            cout << "\tplaying music:  " << tmp->name << endl;
            tmp = tmp->next;
        }
        tmp = start;
        while (tmp != NULL)
        {
            cout << "\tplaying music:  " << tmp->name << endl;
            tmp = tmp->next;
        }
    }
    void es_play(play_list *start, int i)
    {
        if (start == NULL)
        {
            cout << "error! no music to play!\n";
            return;
        }
        else
        {
            play_list *tmp = start;
            while (tmp != NULL)
            {
                if (tmp->id == i)
                {
                    cout << "\tplaying music: " << tmp->name << endl;
                    cout << "\tchoose:\n";
                    cout << "\t1- previous music music\n";
                    cout << "\t2- next music\n";
                    cout << "\t0- exit\n";
                    cout << "\t-> ";
                    int operation = -1;
                    cin >> operation;
                    if (operation == 1)
                        start->es_play(start, i - 1);
                    else if (operation == 2)
                        start->es_play(start, i + 1);
                    else if (operation == 0)
                        return;
                    return;
                }
                tmp = tmp->next;
            }
            cout << "error! no such music to play.\n";
        }
    }
};

int main(void)
{
    srand(time(0));

    input_file *istart = NULL;

    ifstream f("../names.txt");
    string in_string;
    getline(f, in_string);
    while (!f.eof())
    {
        istart->create_node(istart, in_string);
        getline(f, in_string);
    }
    f.close();

    // the program is ok to here.

    ap *start_ap = NULL;
    //play_list *start_pl = NULL;

    string greeting[6];
    greeting[0] = "choose your operation:\n";
    greeting[1] = "1- enter an existing play list\n";
    greeting[2] = "2- delete a play list\n";
    greeting[3] = "3- create a play list\n";
    greeting[4] = "4- show play lists\n";
    greeting[5] = "0- exit the program\n";

    cout << greeting[0] << greeting[1] << greeting[2]
         << greeting[3] << greeting[4] << greeting[5];
    int operation = -1;
    cin >> operation;

    while (operation != 0)
    {
        // state 1 is not working properly.
        if (operation == 1)
        {
            if (start_ap == NULL)
            {
                cout << "error! no play list.\n\n";
            }
            else
            {
                cout << "play lists:\n";
                start_ap->show(start_ap);
                cout << "\n\n";

                cout << "enter play list id:  ";
                int tmp_id = -1;
                cin >> tmp_id;
                //start_pl = start_ap->get_pl(start_ap, tmp_id);
                ap* tmp1=start_ap;
                while(tmp1!=NULL)
                {
                    if(tmp1->id==tmp_id)
                    {
                        break;
                    }
                    tmp1=tmp1->next;
                }
                if(tmp1==NULL)
                    cout<<"error! no such play list.\n";
                cout<<"chosen play list:  "<<tmp1->name<<endl;


                cout << "\twhat do you want to do?\n";
                cout << "0- add music" << endl;
                cout << "1- remove music" << endl;
                cout << "2- show musics" << endl;
                cout << "3- random play music" << endl;
                cout << "4- play loop" << endl;
                cout << "5- play especial music" << endl
                     << endl;

                int operation = -1;
                cin >> operation;

                if (operation == 0)
                {
                    cout << "all musics:\n";
                    istart->show(istart);
                    cout << "choose music id:  ";
                    int music_id = -1;
                    cin >> music_id;

                    string am ; // address of music
                    am.assign(istart->get_music(istart, music_id));
                    cout<<"chosen music:\t"<<am<<endl;
                    if (!am.empty())
                    {
                            start_pl->add(start_pl, am, am);
                            start_pl->show(start_pl);
                    }
                    else
                        cout << "error! no music\n";
                }
                else if (operation == 1)
                {
                    cout << "musics: \n";
                    start_pl->show(start_pl);
                    cout << endl
                         << "choose music id:  ";

                    int music_id = -1;
                    cin >> music_id;

                    start_pl->remove(start_pl, music_id);
                }
                else if (operation == 2)
                {
                    cout << "musics:\n";
                    start_pl->show(start_pl);
                }
                else if(operation == 3)
                {
                    start_pl->random_play(start_pl);
                }
                else if (operation == 4)
                {
                    start_pl->loop_play(start_pl);
                }
                else if (operation == 5)
                {
                    cout << "musics:\n";
                    start_pl->show(start_pl);

                    int music_id = -1;
                    cout << "which music id: ";
                    cin >> music_id;
                    start_pl->es_play(start_pl, music_id);
                }
                else
                {
                    cout << "error! invalid input\n";
                }
            }
        }
        else if (operation == 2)
        {
            cout << "play lists: " << endl;
            start_ap->show(start_ap);
            cout << "enter play list id: ";
            int pid = -1;
            cin >> pid;

            start_ap->delete_pl(start_ap, pid);
        }
        else if (operation == 3)
        {
            cout << "choose a name:  ";
            string name;
            char ch_tmp;
            cin>>ch_tmp;
            getline(cin, name);
            name.insert(name.begin(), ch_tmp);
            start_ap->add_pl(start_ap, name);
        }
        else if(operation ==4) 
        {
            cout<<"play lists:"<<endl;
            start_ap->show(start_ap);
        }

        cout<<"--------------\n";
        cout << greeting[0] << greeting[1] << greeting[2]
             << greeting[3] << greeting[4] << greeting[5];
        cin>>operation;

    }


    cout<<"\n\n   all play lists:\n";
    while(start_ap!=NULL)
    {
        cout<<"-*-*-*\n";
        cout<<start_ap->name<<": \n";
        start_ap->start->show(start_ap->start);
        start_ap=start_ap->next;
    }

    cout << "\n\nthis program is designed by amirhossein moradi.";
    cout<<"\nall rights reserved.\n\n";
    return 0;
}
