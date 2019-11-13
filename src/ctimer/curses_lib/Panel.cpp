#include "Panel.h"

namespace y44::curses_lib {
  Panel::Panel(const size panel_size, const position panel_pos) :
  m_pos(panel_pos),
  m_size(panel_size) {
  ncurses_panel = std::make_unique<NCursesPanel>(m_size.height, m_size.width, m_pos.y, m_pos.x);
  ncurses_panel->box();
  }

  Panel::Panel(Panel& other) :
    m_pos(other.get_pos()),
    m_size(other.get_size()) {
    ncurses_panel = std::make_unique<NCursesPanel>(m_size.height, m_size.width, m_pos.y, m_pos.x);
    ncurses_panel->box();

    auto [tl, bl] = other.get_label();
    set_labels(tl, bl);
    ncurses_panel->redraw();
  }

  void Panel::on_key(const uint /*key_code*/) {
  }

  void Panel::clear_row(const size_t row) {

    // save cursor pos
    int oldx;
    int oldy;
    ncurses_panel->getyx(oldy, oldx);

    // save border chars 
    auto leftBorder = ncurses_panel->inch(row, 0);
    auto rightBorder = ncurses_panel->inch(row, ncurses_panel->maxx());
    
    // clear row
    ncurses_panel->move(row, 0);
    ncurses_panel->clrtoeol();
    
    // restore border
    ncurses_panel->addch(row, 0, leftBorder);
    ncurses_panel->addch(row, ncurses_panel->maxx(), rightBorder);
    
    // restore cursor pos
    ncurses_panel->move(oldy, oldx);
  }


  void Panel::move(const position new_pos, const bool move_absolute) {
    //position old_pos = m_pos;
    if(!move_absolute) {
      m_pos.x = m_pos.x + new_pos.x;
      m_pos.y = m_pos.y + new_pos.y;
    } else {
      m_pos = new_pos;
    }
 
    auto screen_height = static_cast<size_t>(ncurses_panel->lines());
    auto screen_width = static_cast<size_t>(ncurses_panel->cols());

    // bail if panel outside screen. TODO throw error? 
    if(m_pos.x > (screen_width - m_size.width)) {
      //m_pos = old_pos;
      //return;
      m_pos.x = screen_width - m_size.width;
    }
    if(m_pos.y > (screen_height - m_size.height)) {
      //m_pos = old_pos;
      //return;
      m_pos.y = screen_height - m_size.height;
    }

    ncurses_panel->mvwin(m_pos.y, m_pos.x);
    ncurses_panel->redraw();
  }

  void Panel::set_labels(const std::string& top_label, const std::string& bottom_label) {
    clear_row(0);
    clear_row(ncurses_panel->maxy());
    ncurses_panel->box();

    m_top_label = top_label;
    m_bottom_label = bottom_label;

    auto max_len = static_cast<size_t>(ncurses_panel->maxx()) - (LABEL_VMARGIN + LABEL_RMARGIN + 2);

    std::string tlabel;
    if(m_top_label.length() > max_len) {
      tlabel = " " + top_label.substr(0, max_len - 3) + "... ";
    }
    else if(m_top_label.length() > 0) {
      tlabel = " " + top_label + " ";
    }
    ncurses_panel->printw(0, LABEL_VMARGIN, "%s", tlabel.c_str());

    std::string blabel;
    if(m_bottom_label.length() > max_len) {
      blabel = " " + bottom_label.substr(0, max_len - 3) + "... ";
    
    }
    else if(m_bottom_label.length() > 0) {
      blabel = " " + bottom_label + " ";
    }
    auto blabel_xpos = ncurses_panel->maxx() - blabel.length() - LABEL_RMARGIN;
    auto blabel_ypos = ncurses_panel->maxy();
    ncurses_panel->printw(static_cast<int>(blabel_ypos), static_cast<int>(blabel_xpos), "%s", blabel.c_str());
    
    ncurses_panel->redraw();
  }

  std::pair<std::string, std::string> Panel::get_label() const {
    return std::make_pair(m_top_label, m_bottom_label);
  }
}; // namespace y44::curses_lib

