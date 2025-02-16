#pragma once

#include "element.h"
#include "geometry.h"
#include "timer.h"

namespace esphome::elements {

using display::TextAlign;

enum class ScrollMode {
  NONE,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
  BOTTOM_TO_TOP,
  TOP_TO_BOTTOM,
};

class TextElement : public Element {
 public:
  explicit TextElement(ElementComponent* component, Element* parent)
      : Element(ElementType::TEXT, component, parent) {}

  void set_font(display::BaseFont* font) { font_ = font; }
  void set_color(Color color) { color_ = color; }
  void set_background_color(Color background_color) {
    background_color_ = background_color;
  }
  void set_anchor(Anchor anchor) { anchor_ = anchor; }
  void set_align(TextAlign align) { align_ = align; }

  void set_scroll_mode(ScrollMode scroll_mode) { scroll_mode_ = scroll_mode; }
  void set_scroll_speed(float scroll_speed) { scroll_speed_ = scroll_speed; }
  void set_update_interval(uint32_t update_interval_ms) {
    update_timer_.set_duration(update_interval_ms);
  }

  void set_text(std::string text);
  void set_lambda(std::function<std::string()> lambda);

  void draw(display::Display& display) override;

  void on_show() override;

 protected:
  display::BaseFont* font_ = nullptr;
  Color color_ = Color::WHITE;
  Color background_color_ = Color::BLACK;
  Anchor anchor_;
  TextAlign align_;

  ScrollMode scroll_mode_ = ScrollMode::NONE;
  float scroll_speed_ = 10.0;  // pixel per second
  float scroll_offset_ = 0.0;

  Timer update_timer_ = Timer(250);
  optional<std::string> text_;
  optional<std::function<std::string()>> lambda_;

  uint32_t last_update_ms_;
  bool request_measurement_ = false;
  int bounds_x_, bounds_y_, bounds_w_, bounds_h_;
};

}  // namespace esphome::elements
