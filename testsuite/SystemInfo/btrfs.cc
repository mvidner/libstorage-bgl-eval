
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE libstorage

#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string.hpp>

#include "storage/SystemInfo/CmdBtrfs.h"
#include "storage/Utils/Mockup.h"
#include "storage/Utils/SystemCmd.h"
#include "storage/Utils/StorageDefines.h"


using namespace std;
using namespace storage;


void
check(const vector<string>& input, const vector<string>& output)
{
    Mockup::set_mode(Mockup::Mode::PLAYBACK);
    Mockup::set_command(BTRFSBIN " filesystem show", input);

    CmdBtrfsShow cmdbtrfsshow;

    ostringstream parsed;
    parsed.setf(std::ios::boolalpha);
    parsed << cmdbtrfsshow;

    string lhs = parsed.str();
    string rhs = boost::join(output, "\n") + "\n";

    BOOST_CHECK_EQUAL(lhs, rhs);
}


BOOST_AUTO_TEST_CASE(parse1)
{
    vector<string> input = {
	"Label: none  uuid: ea108250-d02c-41dd-b4d8-d4a707a5c649",
	"        Total devices 1 FS bytes used 28.00KiB",
	"        devid    1 size 1.00GiB used 138.38MiB path /dev/mapper/system-test",
	"",
	"Label: none  uuid: d82229f2-f9e4-40fd-b15f-84e2d42e6d0d",
	"        Total devices 1 FS bytes used 420.00KiB",
	"        devid    1 size 2.00GiB used 240.75MiB path /dev/mapper/system-testsuite",
	"",
	"Label: none  uuid: 653764e0-7ea2-4dbe-9fa1-866f3f7783c9",
	"        Total devices 1 FS bytes used 316.00KiB",
	"        devid    1 size 5.00GiB used 548.00MiB path /dev/mapper/system-btrfs",
	"",
	"Btrfs v3.12+20131125"
    };

    vector<string> output = {
	"data[653764e0-7ea2-4dbe-9fa1-866f3f7783c9] -> </dev/mapper/system-btrfs>",
	"data[d82229f2-f9e4-40fd-b15f-84e2d42e6d0d] -> </dev/mapper/system-testsuite>",
	"data[ea108250-d02c-41dd-b4d8-d4a707a5c649] -> </dev/mapper/system-test>"
    };

    check(input, output);
}
