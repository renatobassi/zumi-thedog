#include "record.hpp"

namespace {

constexpr uint8_t kMagic0 = 'Z';
constexpr uint8_t kMagic1 = 'U';
constexpr uint8_t kMagic2 = 'M';
constexpr uint8_t kMagic3 = 'I';
constexpr uint8_t kVersion1 = 1;
constexpr size_t kHeader = 6;
constexpr size_t kV1Payload = 10;
constexpr size_t kCrc = 2;

uint16_t crc16(const uint8_t* data, size_t len) {
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; ++i) {
    crc ^= static_cast<uint16_t>(data[i]) << 8;
    for (int bit = 0; bit < 8; ++bit) {
      if ((crc & 0x8000) != 0) {
        crc = static_cast<uint16_t>((crc << 1) ^ 0x1021);
      } else {
        crc = static_cast<uint16_t>(crc << 1);
      }
    }
  }
  return crc;
}

void write_u32(uint8_t* dest, uint32_t value) {
  dest[0] = static_cast<uint8_t>(value);
  dest[1] = static_cast<uint8_t>(value >> 8);
  dest[2] = static_cast<uint8_t>(value >> 16);
  dest[3] = static_cast<uint8_t>(value >> 24);
}

uint32_t read_u32(const uint8_t* src) {
  return static_cast<uint32_t>(src[0]) | (static_cast<uint32_t>(src[1]) << 8) |
         (static_cast<uint32_t>(src[2]) << 16) | (static_cast<uint32_t>(src[3]) << 24);
}

}  // namespace

bool pet_snapshot_can_persist(const PetSnapshot& snap) {
  if (snap.phase > PHASE_ADULT) {
    return false;
  }
  if (snap.bars.hunger > 100 || snap.bars.energy > 100 || snap.bars.fun > 100 || snap.bars.hygiene > 100) {
    return false;
  }
  return true;
}

bool pet_record_encode(const PetSnapshot& snap, uint8_t* dest, size_t cap, size_t* written) {
  if (dest == nullptr || written == nullptr || cap < kPetRecordV1Size || !pet_snapshot_can_persist(snap)) {
    return false;
  }

  dest[0] = kMagic0;
  dest[1] = kMagic1;
  dest[2] = kMagic2;
  dest[3] = kMagic3;
  dest[4] = kVersion1;
  dest[5] = static_cast<uint8_t>(kV1Payload);
  dest[6] = static_cast<uint8_t>(snap.phase);
  dest[7] = snap.bars.hunger;
  dest[8] = snap.bars.energy;
  dest[9] = snap.bars.fun;
  dest[10] = snap.bars.hygiene;
  dest[11] = snap.asleep ? 1 : 0;
  write_u32(dest + 12, snap.last_tick_ms);

  const uint16_t crc = crc16(dest, kHeader + kV1Payload);
  dest[16] = static_cast<uint8_t>(crc);
  dest[17] = static_cast<uint8_t>(crc >> 8);
  *written = kPetRecordV1Size;
  return true;
}

bool pet_record_decode(const uint8_t* bytes, size_t len, PetSnapshot* out) {
  if (bytes == nullptr || out == nullptr || len < kHeader + kCrc) {
    return false;
  }
  if (bytes[0] != kMagic0 || bytes[1] != kMagic1 || bytes[2] != kMagic2 || bytes[3] != kMagic3) {
    return false;
  }

  const uint8_t version = bytes[4];
  const uint8_t payload_len = bytes[5];
  const size_t total = kHeader + static_cast<size_t>(payload_len) + kCrc;
  if (len != total) {
    return false;
  }

  const uint16_t expected = crc16(bytes, kHeader + payload_len);
  const uint16_t actual = static_cast<uint16_t>(bytes[kHeader + payload_len]) |
                          (static_cast<uint16_t>(bytes[kHeader + payload_len + 1]) << 8);
  if (expected != actual) {
    return false;
  }

  // Valor inicial de cada campo. A versão só substitui o que ela conhece.
  PetSnapshot snap = pet_snapshot_newborn(0);
  if (version == kVersion1) {
    if (payload_len < kV1Payload) {
      return false;
    }
    const uint8_t* payload = bytes + kHeader;
    snap.phase = static_cast<Phase>(payload[0]);
    snap.bars.hunger = payload[1];
    snap.bars.energy = payload[2];
    snap.bars.fun = payload[3];
    snap.bars.hygiene = payload[4];
    if (payload[5] > 1) {
      return false;
    }
    snap.asleep = payload[5] == 1;
    snap.last_tick_ms = read_u32(payload + 6);
    if (!pet_snapshot_can_persist(snap)) {
      return false;
    }
    *out = snap;
    return true;
  }

  return false;
}
