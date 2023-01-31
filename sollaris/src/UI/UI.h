#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include "../util/common.h"
#include "../physics/PhysicsEngine.h"
#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_button_clicked();
  
  //Child widgets:
  Gtk::Box m_VBox_Main, m_VBox;
  Gtk::Box m_HBox;
  Gtk::Frame m_Frame_Horizontal, m_Frame_Vertical;
  Gtk::Label m_mass;
  //Gtk::GLArea panel;

  std::shared_ptr<std::vector<PlanetPosition>> position;
  std::shared_ptr<std::vector<PlanetData>> data;
  double updateInterval, jumpInterval;
  PhysicsEngine* PE;
  //IO IO;
};

class myWindow : public Gtk::Window
{
public:
  myWindow(std::shared_ptr<std::vector<PlanetPosition>> p,
  std::shared_ptr<std::vector<PlanetData>> d);

  myWindow(std::shared_ptr<std::vector<PlanetPosition>> p,
  std::shared_ptr<std::vector<PlanetData>> d, std::string x);

  virtual ~myWindow();

protected:
  int index = 0;

  //Child widgets:
  Gtk::Box m_VBox_Main, m_VBox;
  Gtk::Box m_Ent, p_Ent;
  Gtk::Label m_mass, m_radius, m_empty, m_name;
  Gtk::Label m_colorL;
  Gtk::Label m_x, p_x;
  Gtk::Entry m_massE, m_radiusE;
  Gtk::Entry m_xE, m_yE, m_zE;
  Gtk::Entry p_xE, p_yE, p_zE;
  Gtk::Button m_change, m_remove, m_add;
  Gtk::Button m_start, m_stop;
  Gtk::Grid m_grid;
  void change_parameters();
  void remove_planet();
  void add_planet();
  void on_combo_changed();
  std::shared_ptr<std::vector<PlanetPosition>> position;
  std::shared_ptr<std::vector<PlanetData>> data;
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    {add(m_col_id);}

    Gtk::TreeModelColumn<int> m_col_id;
  };

  ModelColumns m_Columns;

  Gtk::ComboBox m_Combo;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;


  void on_color_button_color_set();
  void on_button_dialog_clicked();
  Gtk::ColorButton m_ColorButton;
  Gtk::Button m_Button_Dialog;
  Gdk::RGBA m_Color;

};


class ExampleButtonBox : public Gtk::Frame
{
public:
  ExampleButtonBox(bool horizontal,
       const Glib::ustring& title,
       gint spacing,
       Gtk::ButtonBoxStyle layout,
       double interval,
       PhysicsEngine* pe,
       std::shared_ptr<std::vector<PlanetPosition>> pos,
       std::shared_ptr<std::vector<PlanetData>> d);

protected:
  std::shared_ptr<std::vector<PlanetPosition>> position;
  std::shared_ptr<std::vector<PlanetData>> data;
  void on_button_clicked(Glib::ustring data);
  void myWinClose(); 
  Gtk::Button m_Button_Parameters, m_Button_Add_Planet;
  Gtk::Button m_Button_Start, m_Button_Stop;
  myWindow* window;
  double updateInterval;
  int timeoutId;
  PhysicsEngine* PE;
  gboolean (*GSourceFunc) (gpointer user_data);
  static gboolean MyCallBack(void* data);  
  bool started = 0;
};

#endif //GTKMM_EXAMPLEWINDOW_H








