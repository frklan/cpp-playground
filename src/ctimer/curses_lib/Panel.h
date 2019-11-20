#pragma once

#include "Position.h"
#include "Size.h"
#include <iostream>
#include <memory>

#include <ncursesw/cursesp.h>

#include <utility>
#include <string>


namespace y44::curses_lib{
//  struct size {
//    size_t height;
//    size_t width;
//  };

//  struct position {
//    size_t x;
//    size_t y;
//  };

  constexpr int LABEL_VMARGIN = 3;
  constexpr int LABEL_RMARGIN = 3;

  class Panel {
    public:
      Panel() = delete;
      Panel(const Size panel_size, const Position panel_pos);
      Panel(Panel& other);

      virtual ~Panel() = default;

      virtual void on_activate() {}
      virtual void on_deactivate() {}
      virtual void on_key(const int key_code);


      void clear_row(const int row);
      void set_labels(const std::string& top_label = "", const std::string& bottom_label = ""); 
      std::pair<std::string, std::string> get_label() const;
     

      void set_geometry(const Size /*panel_size*/, const Position /*panel_position*/) {}
      [[nodiscard]] std::pair<Size, Position> get_geometry() { return std::make_pair(m_size, m_pos); }

      void set_size(const Size /*panel_size*/) noexcept {}
      [[nodiscard]] Size get_size() const noexcept { return m_size; }
      void set_pos(const Position /*panel_pos*/) noexcept {}
      [[nodiscard]] Position get_pos() const noexcept { return m_pos; }

      void move(Position new_pos, bool move_absolute = true);


    private:
      std::unique_ptr<NCursesPanel> ncurses_panel;
      Position m_pos;
      Size m_size;
      std::string m_bottom_label{""};
      std::string m_top_label{""};

  };
};

