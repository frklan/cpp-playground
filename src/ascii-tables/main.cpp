//#include "../../libs/libfort/lib/fort.hpp"
#include <fort.hpp>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
  std::clog << "<-- ASCII tables -->\n";

  fort::char_table table;
  table.set_border_style(FT_DOUBLE2_STYLE);

  table << fort::header
    << "N" << "Driver" << "Time" << "Avg Speed" << fort::endr
    << "1" << "Ricciardo" << "1:25.945" << "47.362" << fort::endr
    << "2" << "Hamilton" << "1:26.373" << "35.02" << fort::endr
    << "3" << "Verstappen" << "1:26.469" << "29.78" << fort::endr;
    

  table.row(0).set_cell_text_align(fort::text_align::center);
  //table.column(1).set_cell_text_align(fort::text_align::center);
  //table.column(3).set_cell_text_align(fort::text_align::center);



    std::cout << table.to_string() << std::endl;
  return 0;
}
