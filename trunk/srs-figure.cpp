#include "SRSClient.h"
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    cout<<"srs-figure begins to run"<<endl;
    SRSClient client;
    client.beginToConnect();
    while(getchar() != 'q') {}
    client.closeConnection();
    return 0;
}
