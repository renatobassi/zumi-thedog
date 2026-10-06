#include "zumi.hpp"

#include "frame.hpp"

namespace {

const uint16_t kTrack = 0x39E7;

}  // namespace

void zumi_show(const Display& display, const PetSnapshot& pet, const char* notice) {
  const ZumiFrame frame = zumi_frame(pet);
  display.clear(COLOR_BLACK);

  const SpriteView sprite = sprite_view(frame.pose);
  if (sprite.pixels != 0 && frame.dog_w > 0 && frame.dog_h > 0) {
    display.sprite(frame.dog_x, frame.dog_y, sprite.width, sprite.height, sprite.pixels, kZumiSpriteScale, kSpriteKey);
  }

  for (int i = 0; i < 4; ++i) {
    const int y = frame.track_y + i * frame.track_pitch;
    display.text(frame.bars[i].name, 4, y, 2, COLOR_WHITE);
    display.fill_rect(frame.track_x, y, frame.track_w, frame.track_h, kTrack);
    if (frame.bars[i].fill_px > 0) {
      display.fill_rect(frame.track_x, y, frame.bars[i].fill_px, frame.track_h, COLOR_CARAMEL);
    }
  }

  if (notice != 0 && notice[0] != '\0') {
    display.text(notice, frame.notice_x, frame.notice_y, 2, COLOR_WHITE);
  }

  for (int i = 0; i < 4; ++i) {
    const CareTarget& target = frame.targets[i];
    display.fill_rect(target.x, target.y, target.w, target.h, COLOR_CARAMEL);
    display.text(target.label, target.x + 8, target.y + 18, 2, COLOR_BLACK);
  }
}
