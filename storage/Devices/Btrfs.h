#ifndef BTRFS_H
#define BTRFS_H


#include "storage/Devices/Filesystem.h"


namespace storage
{

    class Btrfs : public Filesystem
    {
    public:

	static Btrfs* create(Devicegraph* devicegraph);
	static Btrfs* load(Devicegraph* devicegraph, const xmlNode* node);

	bool supports_label() const override { return true; }
	unsigned int max_labelsize() const override { return 256; }

	bool supports_uuid() const override { return true; }

    public:

	class Impl;

	Impl& get_impl();
	const Impl& get_impl() const;

	virtual Btrfs* clone() const override;

    protected:

	Btrfs(Impl* impl);

    };


    inline bool
    is_btrfs(const Device* device)
    {
	return dynamic_cast<const Btrfs*>(device) != nullptr;
    }


    inline Btrfs*
    to_btrfs(Device* device)
    {
	return dynamic_cast<Btrfs*>(device);
    }


    inline const Btrfs*
    to_btrfs(const Device* device)
    {
	return dynamic_cast<const Btrfs*>(device);
    }

}

#endif
