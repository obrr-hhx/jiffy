#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "storage_management_client.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

namespace elasticmem {
namespace storage {

storage_management_client::~storage_management_client() {
  if (transport_ != nullptr)
    disconnect();
}

storage_management_client::storage_management_client(const std::string &host, int port) {
  connect(host, port);
}

void storage_management_client::connect(const std::string &host, int port) {
  socket_ = std::make_shared<TSocket>(host, port);
  transport_ = std::shared_ptr<TTransport>(new TBufferedTransport(socket_));
  protocol_ = std::shared_ptr<TProtocol>(new TBinaryProtocol(transport_));
  client_ = std::make_shared<thrift_client>(protocol_);
  transport_->open();
}

void storage_management_client::disconnect() {
  if (transport_->isOpen()) {
    transport_->close();
  }
  if (transport_->isOpen()) {
    transport_->close();
  }
}

void storage_management_client::setup_block(int32_t block_id,
                                            const std::string &path,
                                            int32_t role,
                                            const std::string &next_block_name) {
  client_->setup_block(block_id, path, role, next_block_name);
}

std::string storage_management_client::path(int32_t block_id) {
  std::string path;
  client_->get_path(path, block_id);
  return path;
}

void storage_management_client::flush(const int32_t block_id,
                                      const std::string &persistent_store_prefix,
                                      const std::string &path) {
  client_->flush(block_id, persistent_store_prefix, path);
}

void storage_management_client::load(const int32_t block_id,
                                     const std::string &persistent_store_prefix,
                                     const std::string &path) {
  client_->load(block_id, persistent_store_prefix, path);
}

void storage_management_client::reset(const int32_t block_id) {
  client_->reset(block_id);
}

int64_t storage_management_client::storage_capacity(const int32_t block_id) {
  return client_->storage_capacity(block_id);
}

int64_t storage_management_client::storage_size(const int32_t block_id) {
  return client_->storage_size(block_id);
}

void storage_management_client::resend_pending(int32_t block_id) {
  client_->resend_pending(block_id);
}

}
}