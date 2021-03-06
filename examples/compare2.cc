

#include "storage/Devices/Disk.h"
#include "storage/Devices/Gpt.h"
#include "storage/Devices/Partition.h"
#include "storage/Devices/LvmVg.h"
#include "storage/Devices/LvmLv.h"
#include "storage/Holders/User.h"
#include "storage/Holders/Subdevice.h"
#include "storage/Devicegraph.h"
#include "storage/Actiongraph.h"
#include "storage/Storage.h"
#include "storage/Environment.h"


using namespace storage;


int
main()
{
 storage::Environment environment(true, ProbeMode::NONE, TargetMode::DIRECT);

    Storage storage(environment);

    Devicegraph* lhs = storage.create_devicegraph("lhs");

    Disk* lhs_sda = Disk::create(lhs, "/dev/sda");

    Devicegraph* rhs = storage.copy_devicegraph("lhs", "rhs");

    Disk* rhs_sda = dynamic_cast<Disk*>(rhs->find_device(lhs_sda->get_sid()));

    Gpt* rhs_gpt = Gpt::create(rhs);
    User::create(rhs, rhs_sda, rhs_gpt);

    Partition* rhs_sda1 = Partition::create(rhs, "/dev/sda1", PRIMARY);
    Subdevice::create(rhs, rhs_gpt, rhs_sda1);

    Partition* rhs_sda2 = Partition::create(rhs, "/dev/sda2", PRIMARY);
    Subdevice::create(rhs, rhs_gpt, rhs_sda2);

    LvmVg* rhs_system = LvmVg::create(rhs, "/dev/system");
    User::create(rhs, rhs_sda1, rhs_system);
    User::create(rhs, rhs_sda2, rhs_system);

    LvmLv* rhs_system_swap = LvmLv::create(rhs, "/dev/system/swap");
    Subdevice::create(rhs, rhs_system, rhs_system_swap);

    Actiongraph actiongraph(storage, lhs, rhs);

    actiongraph.write_graphviz("compare2-action.gv", true);
}
