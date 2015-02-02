#!/usr/bin/python

import unittest
from storage import Devicegraph, Disk, Region, GPT, PRIMARY, EXT4


class TestCreate(unittest.TestCase):

    def test_create(self):

        devicegraph = Devicegraph()

        sda = Disk.create(devicegraph, "/dev/sda")
        gpt = sda.create_partition_table(GPT)
        sda1 = gpt.create_partition("/dev/sda1", PRIMARY, Region(0, 100))
        ext4 = sda1.create_filesystem(EXT4)

        self.assertEqual(devicegraph.empty(), False)
        self.assertEqual(devicegraph.num_devices(), 4)

        sda.set_size_k(2**64 - 1)
        self.assertEqual(sda.get_size_k(), 2**64 - 1)

        sda1.set_region(Region(1, 2))
        self.assertEqual(sda1.get_region().get_start(), 1)
        self.assertEqual(sda1.get_region().get_length(), 2)
        self.assertEqual(sda1.get_region(), Region(1, 2))

        ext4.set_label("test-label")
        self.assertEqual(ext4.get_label(), "test-label")

        ext4.add_mountpoint("/test1")
        self.assertEqual(ext4.get_mountpoints().size(), 1)
        self.assertEqual(ext4.get_mountpoints()[0], "/test1")


if __name__ == '__main__':
    unittest.main()
