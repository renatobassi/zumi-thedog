#include "nvs_store.hpp"

#include <Preferences.h>

#include "record.hpp"

namespace {

constexpr char kNamespace[] = "zumi";
constexpr char kKey[] = "pet";
constexpr size_t kMaxRecord = 64;

bool nvs_load(void* ctx, PetSnapshot* out) {
  (void)ctx;
  if (out == nullptr) {
    return false;
  }

  Preferences prefs;
  if (!prefs.begin(kNamespace, true)) {
    return false;
  }
  const size_t len = prefs.getBytesLength(kKey);
  if (len == 0 || len > kMaxRecord) {
    prefs.end();
    return false;
  }

  uint8_t buf[kMaxRecord];
  const size_t got = prefs.getBytes(kKey, buf, len);
  prefs.end();
  if (got != len) {
    return false;
  }
  return pet_record_decode(buf, got, out);
}

bool nvs_save(void* ctx, const PetSnapshot* snap) {
  (void)ctx;
  if (snap == nullptr) {
    return false;
  }

  uint8_t buf[kMaxRecord];
  size_t written = 0;
  if (!pet_record_encode(*snap, buf, sizeof buf, &written)) {
    return false;
  }

  Preferences prefs;
  if (!prefs.begin(kNamespace, false)) {
    return false;
  }
  const size_t put = prefs.putBytes(kKey, buf, written);
  prefs.end();
  return put == written;
}

}  // namespace

PetStore nvs_pet_store() {
  PetStore store;
  store.ctx = nullptr;
  store.load = nvs_load;
  store.save = nvs_save;
  return store;
}
