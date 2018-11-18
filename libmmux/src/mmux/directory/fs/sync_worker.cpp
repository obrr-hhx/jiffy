#include "sync_worker.h"

namespace mmux {
namespace directory {

using namespace utils;

/**
 * @brief Construction function
 * @param tree directory tree
 * @param sync_period_ms synchronization worker working period
 */

sync_worker::sync_worker(std::shared_ptr<directory_tree> tree, uint64_t sync_period_ms)
    : tree_(tree), sync_period_(sync_period_ms), stop_(false), num_epochs_(0) {}

sync_worker::~sync_worker() {
  stop();
}

/**
 * @brief Start synchronization worker
 * Check if any node needs sychronization, then sleep for period time
 */

void sync_worker::start() {
  worker_ = std::thread([&] {
    while (!stop_.load()) {
      LOG(trace) << "Looking for mapped files to synchronize...";
      auto start = std::chrono::steady_clock::now();
      try {
        sync_nodes();
      } catch (std::exception &e) {
        LOG(error) << "Exception: " << e.what();
      }
      ++num_epochs_;
      auto end = std::chrono::steady_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      auto time_to_wait = std::chrono::duration_cast<std::chrono::milliseconds>(sync_period_ - elapsed);
      if (time_to_wait > std::chrono::milliseconds::zero()) {
        std::this_thread::sleep_for(time_to_wait);
      }
    }
  });
}

/**
 * @brief Stop synchronization worker
 */

void sync_worker::stop() {
  stop_.store(true);
  if (worker_.joinable())
    worker_.join();
}

/**
 * @brief Sychronization starting from root directory node
 */

void sync_worker::sync_nodes() {
  namespace ts = std::chrono;
  auto cur_epoch = ts::duration_cast<ts::milliseconds>(ts::system_clock::now().time_since_epoch()).count();
  auto node = std::dynamic_pointer_cast<ds_dir_node>(tree_->root_);
  std::string parent_path;
  for (const auto &cname: node->children()) {
    sync_nodes(node, parent_path, cname, static_cast<uint64_t>(cur_epoch));
  }
}

/**
 * @brief Synchronization of nodes recursively
 * @param parent parent directory node
 * @param parent_path  parent path
 * @param child_name child node name
 * @param epoch time epoch
 */

void sync_worker::sync_nodes(std::shared_ptr<ds_dir_node> parent,
                             const std::string &parent_path,
                             const std::string &child_name,
                             std::uint64_t epoch) {
  auto child_path = parent_path;
  directory_utils::push_path_element(child_path, child_name);
  auto child = parent->get_child(child_name);
  if (child == nullptr) {
    return;
  }
  if (child->is_regular_file()) {
    // Remove child since its lease has expired
    auto s = tree_->dstatus(child_path);
    if (s.is_mapped()) {
      LOG(info) << "Syncing file " << child_path << " with " << s.backing_path() << "...";
      tree_->sync(child_path, s.backing_path());
    }
  } else if (child->is_directory()) {
    auto node = std::dynamic_pointer_cast<ds_dir_node>(child);
    for (const auto &cname: node->children()) {
      sync_nodes(node, child_path, cname, epoch);
    }
  }
}

/**
 * @brief Fetch time epoch of worker
 * @return num_epochs
 */

size_t sync_worker::num_epochs() const {
  return num_epochs_.load();
}

}
}