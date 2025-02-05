#include <libkvs/kvs_store.hpp>
#include <memory>
#include <optional>

using kvs::KvsStore;

std::unique_ptr<KvsStore> KvsStore::Create() {
  return std::unique_ptr<KvsStore>{new KvsStore()};
}

void KvsStore::Set(const std::string &key, const std::string &value) {
  map_[key] = value;
}

std::optional<std::string> KvsStore::Get(const std::string &key) {
  if (auto search = map_.find(key); search != map_.end()) {
    return search->second;
  } else {
    return std::nullopt;
  }
}

void KvsStore::Remove(const std::string &key) { map_.erase(key); }
