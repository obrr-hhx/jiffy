#ifndef ELASTICMEM_KV_MANAGEMENT_RPC_SERVICE_HANDLER_H
#define ELASTICMEM_KV_MANAGEMENT_RPC_SERVICE_HANDLER_H

#include "storage_management_service.h"
#include "../block.h"
#include "../chain_module.h"
#include "../../../../../../../../../../usr/local/Cellar/gcc/7.3.0/include/c++/7.3.0/cstdint"
#include "../../../../../../../../../../usr/local/Cellar/gcc/7.3.0/include/c++/7.3.0/vector"
#include "../../../../../../../../../../usr/local/Cellar/gcc/7.3.0/include/c++/7.3.0/string"

namespace elasticmem {
namespace storage {

class storage_management_service_handler : public storage_management_serviceIf {
 public:
  explicit storage_management_service_handler(std::vector<std::shared_ptr<chain_module>> &blocks);
  void get_path(std::string &_return, int32_t block_id) override;
  void flush(int32_t block_id, const std::string &persistent_store_prefix, const std::string &path) override;
  void load(int32_t block_id, const std::string &persistent_store_prefix, const std::string &path) override;
  void reset(int32_t block_id) override;
  int64_t storage_capacity(int32_t block_id) override;
  int64_t storage_size(int32_t block_id) override;
  void resend_pending(int32_t block_id) override;
  void forward_all(int32_t block_id) override;
  void setup_block(int32_t block_id,
                   const std::string &path,
                   int32_t slot_begin,
                   int32_t slot_end,
                   const std::vector<std::string> &chain,
                   int32_t chain_role,
                   const std::string &next_block_name) override;
  void slot_range(rpc_slot_range &_return, int32_t block_id) override;
  void set_exporting(const int32_t block_id,
                     const std::vector<std::string> &target_block,
                     const int32_t slot_begin,
                     const int32_t slot_end) override;
  void set_importing(const int32_t block_id,
                     const std::string &path,
                     const int32_t slot_begin,
                     const int32_t slot_end,
                     const std::vector<std::string> &chain,
                     const int32_t chain_role,
                     const std::string &next_block_name) override;
  void export_slots(const int32_t block_id) override;
  void set_regular(const int32_t block_id, const int32_t slot_begin, const int32_t slot_end) override;
 private:
  storage_management_exception make_exception(std::exception &e);
  storage_management_exception make_exception(const std::string &msg);
  std::vector<std::shared_ptr<chain_module>> &blocks_;
};

}
}

#endif //ELASTICMEM_KV_MANAGEMENT_RPC_SERVICE_HANDLER_H
