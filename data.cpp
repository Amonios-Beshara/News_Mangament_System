#include "data.h"
map<QString, std::tuple<QString, bool, interests>> usernames={};

vector<QString> CategoryNames = {"Politics","Business","Health", "Science", "Entertainment", "Sports"};

vector<QString> interests::TrueInterests()
{
    vector<QString> output;
    if(politics)
    {
        output.push_back("Politics");
    }
    if(business)
    {
        output.push_back("Business");
    }
    if(healthcare)
    {
        output.push_back("Health");
    }
    if(science)
    {
        output.push_back("Science");
    }
    if(entertainment)
    {
        output.push_back("Entertainment");
    }
    if(sports)
    {
        output.push_back("Sports");
    }
    return output;
}
