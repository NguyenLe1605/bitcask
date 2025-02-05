#pragma once

#include <memory>
#include <optional>
#include <string>

namespace kvs {
class KvsStore {
public:
  // delete the default and copy constructor to ensure the uniqueness of the
  // store
  KvsStore() = delete;
  KvsStore(const KvsStore &other) = delete;
  KvsStore operator=(const KvsStore &other) = delete;

  static std::unique_ptr<KvsStore> Create();

  // TODO: remove the clone string duplication with string_view and benchmark.
  void Set(const std::string &key, const std::string &value);
  std::optional<std::string> Get(const std::string &key);
  void Remove(const std::string &key);
};
} // namespace kvs
