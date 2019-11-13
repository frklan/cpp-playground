#pragma once

#include <iostream>
#include <memory>

#include <ncursesw/cursesp.h>

#include <utility>
#include <string>


namespace y44::curses_lib{
  struct size {
    size_t height;
    size_t width;
  };

  struct position {
    size_t x;
    size_t y;
  };

  constexpr uint8_t LABEL_VMARGIN = 3;
  constexpr uint8_t LABEL_RMARGIN = 3;

  class Panel {
    public:
      Panel(const size panel_size, const position panel_pos);
      Panel(Panel& other);

      virtual ~Panel() = default;

      virtual void on_activate() {}
      virtual void on_deactivate() {}
      virtual void on_key(const uint key_code);


      void clear_row(const size_t row);
      void set_labels(const std::string& top_label = "", const std::string& bottom_label = ""); 
      std::pair<std::string, std::string> get_label() const;

      [[nodiscard]] size get_size() const noexcept { return m_size; }
      [[nodiscard]] position get_pos() const noexcept { return m_pos; }

      void move(position new_pos, bool move_absolute = true);


    private:
      std::unique_ptr<NCursesPanel> ncurses_panel;
      position m_pos;
      size m_size;
      std::string m_bottom_label{""};
      std::string m_top_label{""};

  };
};

