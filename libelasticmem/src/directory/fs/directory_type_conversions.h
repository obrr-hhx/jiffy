#ifndef ELASTICMEM_DIRECTORY_TYPE_CONVERSIONS_H
#define ELASTICMEM_DIRECTORY_TYPE_CONVERSIONS_H

#include "directory_service_types.h"
#include "../directory_ops.h"

namespace elasticmem {
namespace directory {

class directory_type_conversions {
 public:
  static rpc_data_status to_rpc(const data_status &status) {
    rpc_data_status rpc;
    rpc.storage_mode = (rpc_storage_mode) status.mode();
    rpc.persistent_store_prefix = status.persistent_store_prefix();
    rpc.chain_length = static_cast<int32_t>(status.chain_length());
    for (auto blk: status.data_blocks()) {
      rpc_block_chain chain;
      chain.block_names = blk.block_names;
      rpc.data_blocks.push_back(chain);
    }
    return rpc;
  }

  static rpc_file_status to_rpc(const file_status &status) {
    rpc_file_status rpc;
    rpc.type = (rpc_file_type) status.type();
    rpc.last_write_time = status.last_write_time();
    rpc.permissions = status.permissions()();
    return rpc;
  }

  static rpc_dir_entry to_rpc(const directory_entry &entry) {
    rpc_dir_entry rpc;
    rpc.name = entry.name();
    rpc.status.permissions = entry.permissions()();
    rpc.status.type = (rpc_file_type) entry.type();
    rpc.status.last_write_time = entry.last_write_time();
    return rpc;
  }

  static data_status from_rpc(const rpc_data_status &rpc) {
    std::vector<block_chain> data_blocks;
    for (auto blk: rpc.data_blocks) {
      data_blocks.push_back(block_chain{blk.block_names});
    }
    return data_status(static_cast<storage_mode>(rpc.storage_mode),
                       rpc.persistent_store_prefix,
                       static_cast<size_t>(rpc.chain_length),
                       data_blocks);
  }

  static file_status from_rpc(const rpc_file_status &rpc) {
    return file_status(static_cast<file_type>(rpc.type),
                       perms(static_cast<uint16_t>(rpc.permissions)),
                       static_cast<uint64_t>(rpc.last_write_time));
  }

  static directory_entry from_rpc(const rpc_dir_entry &rpc) {
    return directory_entry(rpc.name, from_rpc(rpc.status));
  }
};

}
}

#endif //ELASTICMEM_DIRECTORY_TYPE_CONVERSIONS_H
