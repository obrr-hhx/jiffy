#ifndef MMUX_DIRECTORY_CLIENT_H
#define MMUX_DIRECTORY_CLIENT_H

#include <thrift/transport/TSocket.h>
#include "../directory_ops.h"
#include "../fs/directory_service.h"

namespace mmux {
namespace directory {

/* Directory client class, inherited from directory_interface */

class directory_client : public directory_interface {
 public:
  typedef directory_serviceClient thrift_client;

  directory_client() = default;

  /**
   * @brief Destructor
   */

  ~directory_client() override;

  /**
   * @brief Constructor
   * @param host Service host
   * @param port Service port number
   */

  directory_client(const std::string &hostname, int port);

  /**
   * @brief Connect service
   * @param host Service host
   * @param port Service port number
   */

  void connect(const std::string &hostname, int port);

  /**
   * @brief Disconnect service
   */

  void disconnect();

  /**
   * @brief Create directory
   * @param path Directory path
   */

  void create_directory(const std::string &path) override;

  /**
   * @brief Create directories
   * @param path Directory paths
   */

  void create_directories(const std::string &path) override;

  /**
   * @brief Open file
   * @param path File path
   * @return Data status
   */

  data_status open(const std::string &path) override;

  /**
   * @brief Create a file
   * @param path File path
   * @param backing_path File backing path
   * @param num_blocks Number of blocks
   * @param chain_length Replication chain length
   * @param flags Flag arguments
   * @param permissions Permissions
   * @param tags Tag arguments
   * @return Data status
   */

  data_status create(const std::string &path,
                     const std::string &backing_path = "",
                     std::size_t num_blocks = 1,
                     std::size_t chain_length = 1,
                     std::int32_t flags = 0,
                     std::int32_t permissions = perms::all(),
                     const std::map<std::string, std::string> &tags = {}) override;

  /**
   * @brief Open if exist, otherwise create
   * @param path File path
   * @param backing_path Backing_path
   * @param num_blocks Number of blocks
   * @param chain_length Replication chain length
   * @param flags Flag arguments
   * @param permissions Permissions
   * @param tags Tag arguments
   * @return Data status
   */

  data_status open_or_create(const std::string &path,
                             const std::string &backing_path = "",
                             std::size_t num_blocks = 1,
                             std::size_t chain_length = 1,
                             std::int32_t flags = 0,
                             std::int32_t permissions = perms::all(),
                             const std::map<std::string, std::string> &tags = {}) override;

  /**
   * @brief Check if the file exists
   * @param path File path
   * @return Bool value
   */

  bool exists(const std::string &path) const override;

  /**
   * @brief Fetch last write time of file
   * @param path File path
   * @return Last write time
   */

  std::uint64_t last_write_time(const std::string &path) const override;

  /**
   * @brief Fetch permission of a file
   * @param path File path
   * @return Permission
   */

  perms permissions(const std::string &path) override;

  /**
   * @brief Set permissions
   * @param path File path
   * @param prms Permissions
   * @param opts Permission options
   */

  void permissions(const std::string &path, const perms &prms, perm_options opts) override;

  /**
   * @brief Remove file
   * @param path File path
   */

  void remove(const std::string &path) override;

  /**
   * @brief Remove all files under given directory
   * @param path Directory path
   */

  void remove_all(const std::string &path) override;

  /**
   * @brief Write all dirty blocks back to persistent storage
   * @param path File path
   * @param backing_path File backing path
   */

  void sync(const std::string &path, const std::string &backing_path) override;

  /**
   * @brief Rename a file
   * @param old_path Original file path
   * @param new_path New file path
   */

  void rename(const std::string &old_path, const std::string &new_path) override;

  /**
   * @brief Fetch file status
   * @param path file path
   * @return File status
   */

  file_status status(const std::string &path) const override;

  /**
   * @brief Collect all entries of files in the directory
   * @param path Directory path
   * @return Directory entries
   */

  std::vector<directory_entry> directory_entries(const std::string &path) override;

  /**
   * @brief Collect all entries of files in the directory recursively
   * @param path Directory path
   * @return Directory entries
   */

  std::vector<directory_entry> recursive_directory_entries(const std::string &path) override;

  /**
   * @brief Collect data status
   * @param path File path
   * @return Data status
   */

  data_status dstatus(const std::string &path) override;

  /**
   * @brief Add tags to the file status
   * @param path File path
   * @param tags Tags
   */

  void add_tags(const std::string &path, const std::map<std::string, std::string> &tags) override;

  /**
   * @brief Check if path is regular file
   * @param path File path
   * @return Bool value
   */

  bool is_regular_file(const std::string &path) override;

  /**
   * @brief Check if path is directory
   * @param path Directory path
   * @return Bool value
   */

  bool is_directory(const std::string &path) override;

  // Management Ops
  /**
   * @brief Resolve failures using replication chain
   * @param path File path
   * @param chain Replication chain
   * @return Replication chain
   */

  replica_chain resolve_failures(const std::string &path, const replica_chain &chain) override;

  /**
   * @brief Add a new replication to chain
   * @param path File path
   * @param chain Replication chain
   * @return Replication chain
   */

  replica_chain add_replica_to_chain(const std::string &path, const replica_chain &chain) override;

  /**
   * @brief Add block to file
   * @param path File path
   */

  void add_block_to_file(const std::string &path) override;

  /**
   * @brief Split block hash range
   * @param path File path
   * @param slot_begin Split begin range
   * @param slot_end Split end range
   */

  void split_slot_range(const std::string &path, int32_t slot_begin, int32_t slot_end) override;

  /**
   * @brief Merge slot hash range
   * @param path File path
   * @param slot_begin Merge begin range
   * @param slot_end Merge end range
   */

  void merge_slot_range(const std::string &path, int32_t slot_begin, int32_t slot_end) override;

  /**
   * @brief Write all dirty blocks back to persistent storage and clear the block
   * @param path File path
   * @param backing_path File backing path
   */

  void dump(const std::string &path, const std::string &backing_path) override;

  /**
   * @brief Load blocks from persistent storage
   * @param path File path
   * @param backing_path File backing path
   */

  void load(const std::string &path, const std::string &backing_path) override;

  /**
   * @brief Touch -> unsupported operation
   */

  virtual void touch(const std::string &path) override;

  /**
   * @brief Handle lease expiry -> unsupported operation
   */

  virtual void handle_lease_expiry(const std::string &path) override;

 private:
  /* Socket */
  std::shared_ptr<apache::thrift::transport::TSocket> socket_{};
  /* Transport */
  std::shared_ptr<apache::thrift::transport::TTransport> transport_{};
  /* Protocol */
  std::shared_ptr<apache::thrift::protocol::TProtocol> protocol_{};
  /* Client */
  std::shared_ptr<thrift_client> client_{};
};

}
}

#endif //MMUX_DIRECTORY_CLIENT_H
