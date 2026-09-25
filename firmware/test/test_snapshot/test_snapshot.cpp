#include <unity.h>

#include "domain/pet_snapshot.hpp"

void test_newborn_is_blanket_and_full(void) {
  PetSnapshot snap = pet_snapshot_newborn(1000);
  TEST_ASSERT_EQUAL(PHASE_BLANKET, snap.phase);
  TEST_ASSERT_EQUAL_UINT8(100, snap.bars.hunger);
  TEST_ASSERT_EQUAL_UINT8(100, snap.bars.energy);
  TEST_ASSERT_EQUAL_UINT8(100, snap.bars.fun);
  TEST_ASSERT_EQUAL_UINT8(100, snap.bars.hygiene);
  TEST_ASSERT_EQUAL_UINT32(1000, snap.last_tick_ms);
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_newborn_is_blanket_and_full);
  return UNITY_END();
}
