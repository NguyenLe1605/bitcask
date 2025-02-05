#include <libkvs/kvs_store.hpp>
#include <optional>

using kvs::KvsStore;

std::unique_ptr<KvsStore> KvsStore::Create() {
  // TODO: impl this
  return nullptr;
}

void KvsStore::Set(const std::string &key, const std::string &value) {
  // TODO: impl this
  return;
}

std::optional<std::string> KvsStore::Get(const std::string &key) {
  // TODO: impl this
  return std::nullopt;
}

void KvsStore::Remove(const std::string &key) {
  // TODO: impl this
  return;
}
