#include <iostream>
#include "gtest/gtest.h"
#include <vector>
#include "../src/io/IO.h"
#include "../src/util/common.h"
#include <cmath>


// TEST(IOTest, SavesAndLoads) {
//   IO io;
//   std::vector<PlanetData> data;
//   PlanetData input;
//   input.mass = 1.0;
//   input.radious = 2.0;
//   input.velocity = Vec3(3.0,4.0,5.0);
//   input.colour = Vec3(6.0,7.0,8.0);
//   input.planet_id = 0;
//   data.push_back(input);
//   input.mass = 5.6;
//   input.planet_id = 1;
//   data.push_back(input);
//   io.write_event(data,"save.space");
//   std::vector<PlanetData> new_data;
//   new_data = io.read_event("save.space");
//   EXPECT_EQ(data[0].mass, new_data[0].mass);
//   EXPECT_EQ(data[1].radious, new_data[1].radious);
//   EXPECT_EQ(data[1].velocity.x, new_data[1].velocity.x);
// }

TEST(IOTest, WebParse) {

std::string data = "*******************************************************************************\n Revised: April 12, 2021             Mercury                            199 / 1\n\n PHYSICAL DATA (updated 2021-Apr-12):\n  Vol. Mean Radius (km) =  2440+-1        Density (g cm^-3)     = 5.427\n  Mass x10^23 (kg)      =     3.302       Volume (x10^10 km^3)  = 6.085  \n  Sidereal rot. period  =    58.6463 d    Sid. rot. rate (rad/s)= 0.00000124001\n  Mean solar day        =   175.9421 d    Core radius (km)      = ~1600 \n  Geometric Albedo      =     0.106       Surface emissivity    = 0.77+-0.06\n  GM (km^3/s^2)         = 22031.86855     Equatorial radius, Re = 2440 km\n  GM 1-sigma (km^3/s^2) =                 Mass ratio (Sun/plnt) = 6023682\n  Mom. of Inertia       =     0.33        Equ. gravity  m/s^2   = 3.701     \n  Atmos. pressure (bar) = < 5x10^-15      Max. angular diam.    = 11.0\"   \n  Mean Temperature (K)  = 440             Visual mag. V(1,0)    = -0.42 \n  Obliquity to orbit[1] =  2.11' +/- 0.1' Hill's sphere rad. Rp = 94.4 \n  Sidereal orb. per.    =  0.2408467 y    Mean Orbit vel.  km/s = 47.362 \n  Sidereal orb. per.    = 87.969257  d    Escape vel. km/s      =  4.435\n                                 Perihelion  Aphelion    Mean\n  Solar Constant (W/m^2)         14462       6278        9126\n  Maximum Planetary IR (W/m^2)   12700       5500        8000\n  Minimum Planetary IR (W/m^2)   6           6           6\n*******************************************************************************\n\n\n*******************************************************************************\nEphemeris / API_USER Sun Jan 29 03:41:55 2023 Pasadena, USA      / Horizons\n*******************************************************************************\nTarget body name: Mercury Barycenter (199)        {source: DE441}\nCenter body name: Solar System Barycenter (0)     {source: DE441}\nCenter-site name: BODY CENTER\n*******************************************************************************\nStart time      : A.D. 2023-Jan-25 00:00:00.0000 TDB\nStop  time      : A.D. 2023-Jan-25 12:00:00.0000 TDB\nStep-size       : 1440 minutes\n*******************************************************************************\nCenter geodetic : 0.00000000,0.00000000,0.0000000 {E-lon(deg),Lat(deg),Alt(km)}\nCenter cylindric: 0.00000000,0.00000000,0.0000000 {E-lon(deg),Dxy(km),Dz(km)}\nCenter radii    : (undefined)                                                  \nOutput units    : KM-S\nOutput type     : GEOMETRIC cartesian states\nOutput format   : 2 (position and velocity)\nReference frame : Ecliptic of J2000.0\n*******************************************************************************\nJDTDB\n   X     Y     Z\n   VX    VY    VZ\n*******************************************************************************\n$$SOE\n2459969.500000000 = A.D. 2023-Jan-25 00:00:00.0000 TDB \n X =-6.045266445302831E+07 Y =-1.175699805087866E+07 Z = 4.493415946603902E+06\n VX=-6.289921873965062E-01 VY=-4.570185694812506E+01 VZ=-3.675523487391896E+00\n$$EOE\n*******************************************************************************\n \nTIME\n\n  Barycentric Dynamical Time (\"TDB\" or T_eph) output was requested. This\ncontinuous relativistic coordinate time is equivalent to the relativistic\nproper time of a clock at rest in a reference frame comoving with the\nsolar system barycenter but outside the system's gravity well. It is the\nindependent variable in the solar system relativistic equations of motion.\n\n  TDB runs at a uniform rate of one SI second per second and is independent\nof irregularities in Earth's rotation.\n\n  Calendar dates prior to 1582-Oct-15 are in the Julian calendar system.\nLater calendar dates are in the Gregorian system.\n\nREFERENCE FRAME AND COORDINATES\n\n  Ecliptic at the standard reference epoch\n\n    Reference epoch: J2000.0\n    X-Y plane: adopted Earth orbital plane at the reference epoch\n               Note: IAU76 obliquity of 84381.448 arcseconds wrt ICRF X-Y plane\n    X-axis   : ICRF\n    Z-axis   : perpendicular to the X-Y plane in the directional (+ or -) sense\n               of Earth's north pole at the reference epoch.\n\n  Symbol meaning:\n\n    JDTDB    Julian Day Number, Barycentric Dynamical Time\n      X      X-component of position vector (km)\n      Y      Y-component of position vector (km)\n      Z      Z-component of position vector (km)\n      VX     X-component of velocity vector (km/sec)                           \n      VY     Y-component of velocity vector (km/sec)                           \n      VZ     Z-component of velocity vector (km/sec)                           \n\nABERRATIONS AND CORRECTIONS\n\n Geometric state vectors have NO corrections or aberrations applied.\n\nComputations by ...\n\n    Solar System Dynamics Group, Horizons On-Line Ephemeris System\n    4800 Oak Grove Drive, Jet Propulsion Laboratory\n    Pasadena, CA  91109   USA\n\n    General site: https://ssd.jpl.nasa.gov/\n    Mailing list: https://ssd.jpl.nasa.gov/email_list.html\n    System news : https://ssd.jpl.nasa.gov/horizons/news.html\n    User Guide  : https://ssd.jpl.nasa.gov/horizons/manual.html\n    Connect     : browser        https://ssd.jpl.nasa.gov/horizons/app.html#/x\n                  API            https://ssd-api.jpl.nasa.gov/doc/horizons.html\n                  command-line   telnet ssd.jpl.nasa.gov 6775\n                  e-mail/batch   https://ssd.jpl.nasa.gov/ftp/ssd/hrzn_batch.txt\n                  scripts        https://ssd.jpl.nasa.gov/ftp/ssd/SCRIPTS\n    Author      : Jon.D.Giorgini@jpl.nasa.gov\n*******************************************************************************\n";

  IO io;
  PlanetData planet = io.parse_web(data);
  double VX=-6.289921873965062E-01; //km/s
  double VY=-4.570185694812506E+01;
  double VZ=-3.675523487391896E+00;
  double mass = 3.302 * pow(10,23);
  double radious = 2440;
  EXPECT_DOUBLE_EQ(planet.velocity.x, VX);
  EXPECT_DOUBLE_EQ(planet.velocity.y, VY);
  EXPECT_DOUBLE_EQ(planet.velocity.z, VZ);
  EXPECT_DOUBLE_EQ(planet.mass, mass); //kg
  EXPECT_DOUBLE_EQ(planet.radious, radious); //km
}

TEST(IOTest, WebDownloadAndParse) {
  IO io;
  std::vector<PlanetData> data;
  data = io.read_event("http://");
}