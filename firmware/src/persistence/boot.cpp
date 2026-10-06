#include "boot.hpp"

#include "record.hpp"

PetSnapshot pet_restore(const PetStore& store, uint32_t now_ms) {
  PetSnapshot loaded;
  if (store.load != nullptr && store.load(store.ctx, &loaded) && pet_snapshot_can_persist(loaded)) {
    loaded.last_tick_ms = now_ms;
    return loaded;
  }
  return pet_snapshot_newborn(now_ms);
}

bool pet_commit(const PetStore& store, const PetSnapshot& snap) {
  if (store.save == nullptr || !pet_snapshot_can_persist(snap)) {
    return false;
  }
  return store.save(store.ctx, &snap);
}
