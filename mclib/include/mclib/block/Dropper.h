#ifndef MCLIB_BLOCK_DROPPER_H_
#define MCLIB_BLOCK_DROPPER_H_

#include <mclib/common/Nameable.h>
#include <mclib/block/BlockEntity.h>
#include <mclib/block/InventoryBlock.h>

#include <unordered_map>

namespace mc {
namespace block {

class Dropper : public BlockEntity, public InventoryBlock, public Nameable {
public:
    MCLIB_API Dropper(BlockEntityType type, Vector3i position) : BlockEntity(type, position) { }
    MCLIB_API bool ImportNBT(nbt::NBT* nbt);
};

} // ns block
} // ns mc

#endif
