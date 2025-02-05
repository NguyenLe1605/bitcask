#include <gtest/gtest.h>
#include <libkvs/kvs_store.hpp>

using kvs::KvsStore;

TEST(KvsStoreTest, GetStoredValue) {
  auto store = KvsStore::Create();
  ASSERT_TRUE(store);
  store->Set("key1", "value1");
  store->Set("key2", "value2");

  ASSERT_EQ(store->Get("key1").value(), "value1");
  ASSERT_EQ(store->Get("key2").value(), "value2");
}

TEST(KvsStoreTest, OverwriteValue) {
  auto store = KvsStore::Create();
  ASSERT_TRUE(store);
  store->Set("key1", "value1");
  ASSERT_EQ(store->Get("key1").value(), "value1");

  store->Set("key1", "value2");
  ASSERT_EQ(store->Get("key1").value(), "value2");
}

TEST(KvsStoreTest, GetNonExistentValue) {
  auto store = KvsStore::Create();
  ASSERT_TRUE(store);
  store->Set("key1", "value1");
  ASSERT_FALSE(store->Get("key2").has_value());
}

TEST(KvsStoreTest, RemoveKey) {
  auto store = KvsStore::Create();
  ASSERT_TRUE(store);
  store->Set("key1", "value1");
  store->Remove("key1");
  ASSERT_FALSE(store->Get("key1").has_value());
}
