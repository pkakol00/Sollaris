#include "UI.h"
#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

ExampleWindow::ExampleWindow()
: m_VBox_Main(Gtk::ORIENTATION_VERTICAL),
  m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Frame_Horizontal(),
  position{},
  data{},
  updateInterval(5.2),
  jumpInterval(604800.0),
  PE{}
{
  position = std::make_shared<std::vector<PlanetPosition>>(std::initializer_list<PlanetPosition>{});
  data = std::make_shared<std::vector<PlanetData>>(std::initializer_list<PlanetData>{});
  PE = new PhysicsEngine(position, data, jumpInterval);
  set_title("GUI");
  add(m_VBox_Main);

  m_VBox_Main.pack_start(m_Frame_Horizontal, Gtk::PACK_EXPAND_PADDING, 10);

  m_Frame_Horizontal.add(m_VBox);

  m_VBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (true, "", 30, Gtk::BUTTONBOX_SPREAD, updateInterval, PE, position, data),
    Gtk::PACK_EXPAND_PADDING);

  show_all_children();
  
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
  hide();
}

gboolean ExampleButtonBox::MyCallBack(void* data) {
  PhysicsEngine* PE = (PhysicsEngine*) data;
  PE->update();
  return true;
}

ExampleButtonBox::ExampleButtonBox(bool horizontal,
       const Glib::ustring& title,
       gint spacing,
       Gtk::ButtonBoxStyle layout,
       double interval,
       PhysicsEngine* pe,
       std::shared_ptr<std::vector<PlanetPosition>> pos,
       std::shared_ptr<std::vector<PlanetData>> d)
: Gtk::Frame(""),
  m_Button_Parameters("Change parameters"),
  m_Button_Add_Planet("Add planet"),
  m_Button_Start("Start"),
  m_Button_Stop("Stop"),
  updateInterval(interval),
  timeoutId(-1),
  PE(pe),
  position(pos),
  data(d)
{
  /*
  PlanetPosition ap; ap.planet_id = 0; ap.positions.push_back({0.000000000001,   0.000000000001, 0.000000000001});
  PlanetPosition bp; bp.planet_id = 1; bp.positions.push_back({3'000.000000000001, 0.000000000001, 0.000000000001});
  PlanetData ad {1e26, 1, {10, 20, 30}, {0.1, 0.2, 0.9}, 0};
  PlanetData bd {1e26, 1, {0,  40, 0},  {0.9, 0.2, 0.3}, 1};
  position = std::make_shared<std::vector<PlanetPosition>>(std::initializer_list<PlanetPosition>{ap, bp});
  data = std::make_shared<std::vector<PlanetData>>(std::initializer_list<PlanetData>{ad, bd});*/
  Gtk::ButtonBox* bbox = nullptr;

  if(horizontal)
    bbox = Gtk::make_managed<Gtk::ButtonBox>(Gtk::ORIENTATION_HORIZONTAL);
  else
    bbox = Gtk::make_managed<Gtk::ButtonBox>(Gtk::ORIENTATION_VERTICAL);

  bbox->set_border_width(5);

  add(*bbox);

  /* Set the appearance of the Button Box */
  bbox->set_layout(layout);
  bbox->set_spacing(spacing);

  m_Button_Parameters.signal_clicked().connect(sigc::bind<Glib::ustring>(
    sigc::mem_fun(*this, &ExampleButtonBox::on_button_clicked), "Change parameters"));
  m_Button_Add_Planet.signal_clicked().connect(sigc::bind<Glib::ustring>(
    sigc::mem_fun(*this, &ExampleButtonBox::on_button_clicked), "Add planet"));
  m_Button_Start.signal_clicked().connect(sigc::bind<Glib::ustring>(
    sigc::mem_fun(*this, &ExampleButtonBox::on_button_clicked), "Start"));
  m_Button_Stop.signal_clicked().connect(sigc::bind<Glib::ustring>(
    sigc::mem_fun(*this, &ExampleButtonBox::on_button_clicked), "Stop"));
  bbox->add(m_Button_Parameters);
  bbox->add(m_Button_Add_Planet);
  bbox->add(m_Button_Start);
  bbox->add(m_Button_Stop);
}

void ExampleButtonBox::on_button_clicked(Glib::ustring data)
{
  if (data.compare("Change parameters") == 0) {
    window = new myWindow(this->position, this->data);
    window->signal_hide().connect(sigc::mem_fun(*this, &ExampleButtonBox::myWinClose));
    window->show();

  }
  else if (data.compare("Add planet") == 0) {
    window = new myWindow(this->position, this->data, "add");
    window->signal_hide().connect(sigc::mem_fun(*this, &ExampleButtonBox::myWinClose));
    window->show();
  }
  else if (data.compare("Start") == 0) {
    if (!started) {
      LOG("Started");
      timeoutId = g_timeout_add_seconds(updateInterval, MyCallBack, PE);
      started = true;
    }
    else 
      LOG("Already started");

  }
  else if (data.compare("Stop") == 0) {
    if (started) {
      LOG("Stopped");
      g_source_remove(timeoutId);
      started = false;
    }
    else
      LOG("Already stopped");

  }
  else {
    LOG("Not implemented yet");    
  }
}

void ExampleButtonBox::myWinClose()
{
    window = 0;
}


myWindow::myWindow(std::shared_ptr<std::vector<PlanetPosition>> p,
  std::shared_ptr<std::vector<PlanetData>> d)
: m_VBox_Main(Gtk::ORIENTATION_VERTICAL),
  m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Ent(Gtk::ORIENTATION_HORIZONTAL),
  m_name("Planet ID"), m_mass("Mass"), m_radius("Radius"), m_colorL("Colour"),
  m_x("Velocity"), p_x("Position"),
  m_empty(""),
  m_change("Change"), m_remove("Remove"),
  position(p), data(d)
{
  set_size_request(300, 300);
  set_title("Change parameters");
  m_VBox_Main.pack_start(m_grid, Gtk::PACK_EXPAND_PADDING, 10);
  add(m_VBox_Main);

  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_Combo.set_model(m_refTreeModel);
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  for (int i = 0; i < data->size(); i++) {
    if (i == 0) {
      row[m_Columns.m_col_id] = data->at(i).planet_id;
      m_Combo.set_active(row);
      m_Combo.pack_start(m_Columns.m_col_id);
    }
    else {
      row = *(m_refTreeModel->append());
      row[m_Columns.m_col_id] = data->at(i).planet_id;
    }
  }
  if (data->size() > 0) {
    std::ostringstream s;
    s << this->data->at(0).mass;
    m_massE.set_text(s.str());
    s.str(std::string());
    s << this->data->at(0).radious;
    m_radiusE.set_text(s.str());
    s.str(std::string());
    s << this->data->at(0).velocity.x;
    m_xE.set_text(s.str());
    s.str(std::string());
    s << this->data->at(0).velocity.y;
    m_yE.set_text(s.str());
    s.str(std::string());
    s << this->data->at(0).velocity.z;
    m_zE.set_text(s.str());
    s.str(std::string());
    s << this->position->at(0).positions.front().x;
    p_xE.set_text(s.str());
    s.str(std::string());
    s << this->position->at(0).positions.front().y;
    p_yE.set_text(s.str());
    s.str(std::string());
    s << this->position->at(0).positions.front().z;
    p_zE.set_text(s.str());
    s.str(std::string());
  
  
    m_Color.set_red(this->data->at(0).colour.x);
    m_Color.set_green(this->data->at(0).colour.y);
    m_Color.set_blue(this->data->at(0).colour.z);
    m_Color.set_alpha(1.0); //opaque
    m_ColorButton.set_rgba(m_Color);
  }
  
  m_name.set_margin_top(15);
  m_Combo.set_margin_top(15);
  m_name.set_margin_left(20);
  m_mass.set_margin_left(20);
  m_radius.set_margin_left(20);
  m_colorL.set_margin_left(20);
  m_x.set_margin_left(20);
  p_x.set_margin_left(20);


  m_Combo.set_margin_right(20);
  m_massE.set_margin_right(20);
  m_radiusE.set_margin_right(20);
  m_ColorButton.set_margin_right(20);
  m_xE.set_margin_right(20);
  m_yE.set_margin_right(20);
  m_zE.set_margin_right(20);
  p_xE.set_margin_right(20);
  p_yE.set_margin_right(20);
  p_zE.set_margin_right(20);

  m_grid.attach(m_name, 0, 1, 2, 1);
  m_grid.attach(m_Combo, 5, 1, 2, 1);
  m_name.set_xalign(0.0);
  
  m_grid.attach(m_mass, 0, 3, 2, 1);
  m_grid.attach(m_massE, 5, 3, 2, 1);
  m_mass.set_xalign(0.0);

  m_grid.attach(m_radius, 0, 4, 2, 1);
  m_grid.attach(m_radiusE, 5, 4, 2, 1);
  m_radius.set_xalign(0.0);

  m_grid.attach(m_colorL, 0, 5, 2, 1);
  m_grid.attach(m_ColorButton, 5, 5, 2, 1);
  m_colorL.set_xalign(0.0);

  m_ColorButton.signal_color_set().connect(sigc::mem_fun(*this,
  &myWindow::on_color_button_color_set) );
  m_Ent.set_spacing(1);
  m_Ent.pack_start(m_xE, Gtk::PACK_EXPAND_PADDING, 1);
  m_Ent.pack_start(m_yE, Gtk::PACK_EXPAND_PADDING, 1);
  m_Ent.pack_start(m_zE, Gtk::PACK_EXPAND_PADDING, 1);

  m_grid.attach(m_x, 0, 6, 2, 1);
  m_grid.attach(m_Ent, 5, 6, 2, 1);

  m_x.set_xalign(0.0);

  p_Ent.set_spacing(1);
  p_Ent.pack_start(p_xE, Gtk::PACK_EXPAND_PADDING, 1);
  p_Ent.pack_start(p_yE, Gtk::PACK_EXPAND_PADDING, 1);
  p_Ent.pack_start(p_zE, Gtk::PACK_EXPAND_PADDING, 1);

  m_grid.attach(p_x, 0, 7, 2, 1);
  m_grid.attach(p_Ent, 5, 7, 2, 1);

  p_x.set_xalign(0.0);


  m_grid.attach(m_change, 1, 10, 2, 1);
  m_grid.attach(m_remove, 4, 10, 2, 1);
  m_change.set_margin_bottom(15);
  m_remove.set_margin_bottom(15);
  m_change.set_margin_right(20);
  m_remove.set_margin_left(20);

  m_grid.set_column_homogeneous(true);
  m_grid.set_row_spacing(15);

  m_massE.set_width_chars(1);
  m_radiusE.set_width_chars(1);
  m_xE.set_width_chars(5);
  m_yE.set_width_chars(5);
  m_zE.set_width_chars(5);
  p_xE.set_width_chars(5);
  p_yE.set_width_chars(5);
  p_zE.set_width_chars(5);

  m_Combo.signal_changed().connect( sigc::mem_fun(*this, &myWindow::on_combo_changed) );

  m_change.signal_clicked().connect( sigc::mem_fun(*this, &myWindow::change_parameters));
  m_remove.signal_clicked().connect( sigc::mem_fun(*this, &myWindow::remove_planet));

  show_all_children();

}






myWindow::myWindow(std::shared_ptr<std::vector<PlanetPosition>> p,
  std::shared_ptr<std::vector<PlanetData>> d, std::string x)
: m_VBox_Main(Gtk::ORIENTATION_VERTICAL),
  m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Ent(Gtk::ORIENTATION_HORIZONTAL),
  m_mass("Mass"), m_radius("Radius"), m_colorL("Colour"),
  m_x("Velocity"), p_x("Position"),
  m_empty(""),
  m_add("Add"),
  position(p), data(d)
{
  set_size_request(300, 300);
  set_title("Add planet");
  m_VBox_Main.pack_start(m_grid, Gtk::PACK_EXPAND_PADDING, 10);
  add(m_VBox_Main);


  m_mass.set_margin_left(20);
  m_radius.set_margin_left(20);
  m_colorL.set_margin_left(20);
  m_x.set_margin_left(20);
  p_x.set_margin_left(20);

  m_Combo.set_margin_right(20);
  m_massE.set_margin_right(20);
  m_radiusE.set_margin_right(20);
  m_ColorButton.set_margin_right(20);
  m_xE.set_margin_right(20);
  m_yE.set_margin_right(20);
  m_zE.set_margin_right(20);
  p_xE.set_margin_right(20);
  p_yE.set_margin_right(20);
  p_zE.set_margin_right(20);

  m_grid.attach(m_mass, 0, 3, 2, 1);
  m_grid.attach(m_massE, 3, 3, 2, 1);
  m_mass.set_xalign(0.0);

  m_grid.attach(m_radius, 0, 4, 2, 1);
  m_grid.attach(m_radiusE, 3, 4, 2, 1);
  m_radius.set_xalign(0.0);

  m_grid.attach(m_colorL, 0, 5, 2, 1);
  m_grid.attach(m_ColorButton, 3, 5, 2, 1);
  m_colorL.set_xalign(0.0);

  m_ColorButton.signal_color_set().connect(sigc::mem_fun(*this,
  &myWindow::on_color_button_color_set) );
  m_Ent.set_spacing(1);
  m_Ent.pack_start(m_xE, Gtk::PACK_EXPAND_PADDING, 1);
  m_Ent.pack_start(m_yE, Gtk::PACK_EXPAND_PADDING, 1);
  m_Ent.pack_start(m_zE, Gtk::PACK_EXPAND_PADDING, 1);

  m_grid.attach(m_x, 0, 6, 2, 1);
  m_grid.attach(m_Ent, 3, 6, 2, 1);
  m_x.set_xalign(0.0);

  p_Ent.set_spacing(1);
  p_Ent.pack_start(p_xE, Gtk::PACK_EXPAND_PADDING, 1);
  p_Ent.pack_start(p_yE, Gtk::PACK_EXPAND_PADDING, 1);
  p_Ent.pack_start(p_zE, Gtk::PACK_EXPAND_PADDING, 1);

  m_grid.attach(p_x, 0, 7, 2, 1);
  m_grid.attach(p_Ent, 3, 7, 2, 1);

  p_x.set_xalign(0.0);

  m_grid.attach(m_add, 2, 10, 1, 1);

  m_grid.set_column_homogeneous(true);
  m_grid.set_row_spacing(15);

  m_massE.set_width_chars(1);
  m_radiusE.set_width_chars(1);
  m_xE.set_width_chars(5);
  m_yE.set_width_chars(5);
  m_zE.set_width_chars(5);
  p_xE.set_width_chars(5);
  p_yE.set_width_chars(5);
  p_zE.set_width_chars(5);


  m_add.signal_clicked().connect( sigc::mem_fun(*this, &myWindow::add_planet));

  show_all_children();

}




myWindow::~myWindow(){}

void myWindow::change_parameters() {
  int id = 0;
  Gtk::TreeModel::iterator iter = m_Combo.get_active();
  if(iter) {
    Gtk::TreeModel::Row row = *iter;
    if(row)
    {
      id = row[m_Columns.m_col_id];
      LOG("Zmiana parametrów planety: ", id);
    }
  }
  else
    LOG("Invalid iter");

  this->data->at(id).mass       = atof(m_massE.get_text().c_str());
  this->data->at(id).radious    = atof(m_radiusE.get_text().c_str());
  this->data->at(id).colour.x   = m_Color.get_red();
  this->data->at(id).colour.y   = m_Color.get_green();
  this->data->at(id).colour.z   = m_Color.get_blue();
  this->data->at(id).velocity.x = atof(m_xE.get_text().c_str()); 
  this->data->at(id).velocity.y = atof(m_yE.get_text().c_str()); 
  this->data->at(id).velocity.z = atof(m_zE.get_text().c_str()); 

  std::deque<Vec3> newQueue;
  newQueue.push_back({atof(p_xE.get_text().c_str()),
                      atof(p_yE.get_text().c_str()),
                      atof(p_zE.get_text().c_str())});
  this->position->at(id).positions = newQueue;

}

void myWindow::remove_planet() {



  int id = 0;
  Gtk::TreeModel::iterator iter = m_Combo.get_active();
  if(iter) {
    Gtk::TreeModel::Row row = *iter;
    if(row)
    {
      id = row[m_Columns.m_col_id];
      LOG("Usuwanie planety: ", id);

      for (auto it = this->data->begin(); it != this->data->end(); ++it) {
        if (it->planet_id == id) {
          this->data->erase(it);
          break;
        }
      }

      for (auto it = this->position->begin(); it != this->position->end(); ++it) {
        if (it->planet_id == id) {
          this->position->erase(it);
          break;
        }
      }
    }
  }
  else
    LOG("Invalid iter: ");
}


void myWindow::add_planet() {
  LOG("Dodawanie planety");

  this->data->push_back(PlanetData(
        atof(m_massE.get_text().c_str()),
        atof(m_radiusE.get_text().c_str()),
       {atof(m_xE.get_text().c_str()),
        atof(m_yE.get_text().c_str()),
        atof(m_zE.get_text().c_str())},
       {m_Color.get_red(),
        m_Color.get_green(),
        m_Color.get_blue()},
        index
  ));

  std::deque<Vec3> newQueue;
  newQueue.push_back({atof(p_xE.get_text().c_str()),
                      atof(p_yE.get_text().c_str()),
                      atof(p_zE.get_text().c_str())});

  this->position->push_back(PlanetPosition(newQueue, index));

  index++;
}

void myWindow::on_combo_changed()
{
  Gtk::TreeModel::iterator iter = m_Combo.get_active();
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
    if(row)
    {
      int id = row[m_Columns.m_col_id];
      std::ostringstream s;
      s << this->data->at(id).mass;
      m_massE.set_text(s.str());
      s.str(std::string());
      s << this->data->at(id).radious;
      m_radiusE.set_text(s.str());
      s.str(std::string());
      s << this->data->at(id).velocity.x;
      m_xE.set_text(s.str());
      s.str(std::string());
      s << this->data->at(id).velocity.y;
      m_yE.set_text(s.str());
      s.str(std::string());
      s << this->data->at(id).velocity.z;
      m_zE.set_text(s.str());
      s.str(std::string());

      m_Color.set_red(this->data->at(id).colour.x);
      m_Color.set_green(this->data->at(id).colour.y);
      m_Color.set_blue(this->data->at(id).colour.z);
      m_Color.set_alpha(1.0); //opaque
      m_ColorButton.set_rgba(m_Color);
    }
  }
  else
    LOG("Invalid iter");
}

void myWindow::on_color_button_color_set()
{
  m_Color = m_ColorButton.get_rgba();
}


void myWindow::on_button_dialog_clicked()
{
  Gtk::ColorChooserDialog dialog("Choose a color");
  dialog.set_transient_for(*this);

  dialog.set_rgba(m_Color);

  const int result = dialog.run();

  switch(result)
  {
    case Gtk::RESPONSE_OK:
    {
      m_Color = dialog.get_rgba();
      m_ColorButton.set_rgba(m_Color);
      break;
    }
    case Gtk::RESPONSE_CANCEL:
    {
      LOG("Cancel clicked");      
      break;
    }
    default:
    {
      LOG("Unexpected button clicked: ", result);      
      break;
    }
  }
}
