#pragma once

#include <ncursesw/cursesp.h>
#include <string>
#include <utility>

class Panel : public NCursesPanel {
  public:
 
    Panel(int nlines, int ncols, int begin_y, int begin_x); 
    
    bool isViewActive() const { return _isViewActive; }
    virtual void onActivate();
    virtual void onDeactivate();
    virtual int onKey(int /*key*/);

    virtual void clearRow(const int row);
    virtual void label(const std::string& topLabel = "", const std::string& bottomLabel = ""); 
    virtual std::pair<std::string, std::string> getLabel() const;  

  private:
    virtual void label(const char*, const char*) override { } 
    void label(const char* topLabel, const int topMargin, const char* bottomLabel, const int bottomMargin) ;
    
    bool _isViewActive = false;
		std::string _bottomLabel = "";
    std::string _topLabel = "";
};

