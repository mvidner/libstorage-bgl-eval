

#include <iostream>

#include "storage/Devicegraph.h"


using namespace std;
using namespace storage;


int
main()
{
    Devicegraph devicegraph;

    devicegraph.load("load1.xml");

    cout << "num_devices: " << devicegraph.num_devices() << endl;
    cout << "num_holders: " << devicegraph.num_holders() << endl;

    cout << endl;

    devicegraph.check();

    cout << devicegraph << endl;

    devicegraph.write_graphviz("load1.gv");
}
