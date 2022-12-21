// Draw a two-dimensional house seen from the front, the way a child would:
// with a door, two windows, and a roof with a chimney. Feel free to add
// details; maybe have “smoke” come out of the chimney.

#include <iostream>
#include <exception>

#include <Graph_lib/Simple_window.h>
#include <Graph_lib/Graph.h>

using namespace Graph_lib;


Point ray (Point s, double r, double phi)
{
  constexpr int a = 3;   // amplitude
  constexpr int l = 10;  // wave length

  double dr = a * sin(pi*r/l);
  r = sqrt (r*r + dr*dr);
  double dphi = asin (dr/r);

  int x = round (r * cos(pi*phi/180. + dphi));
  int y = round (r * sin(pi*phi/180. + dphi));

  return Point{ s.x + x, s.y + y };
}


int main ()
try
{
  constexpr int win_w = 600;  // window width for the drawing
  constexpr int win_h = 400;  // and height
  Line_style style{ Line_style::solid, 2 };

  Simple_window win{ Point{ 100, 100 }, win_w + 70, win_h, "Canvas" };


  constexpr int sky_h = 250;  // horizon position

  Rectangle sky{ Point{ 0, 0 }, win_w, sky_h };
  sky.set_color (Color::blue);
  sky.set_fill_color (Color::blue);
  win.attach (sky);

  Point s{ 50, 50 };     // sun center
  constexpr int r = 25;  // and radius

  Circle sun{ s, r };
  sun.set_color (Color::yellow);
  sun.set_fill_color (Color::yellow);
  win.attach (sun);

  Open_polyline ray1, ray2, ray3, ray4, ray5;
  ray1.set_color (Color::yellow),  ray1.set_style (style);
  ray2.set_color (Color::yellow),  ray2.set_style (style);
  ray3.set_color (Color::yellow),  ray3.set_style (style);
  ray4.set_color (Color::yellow),  ray4.set_style (style);
  ray5.set_color (Color::yellow),  ray5.set_style (style);
  for (int t = r; t <= r + 40; t += 2)
  {
    ray1.add (ray(s, t, -30));
    ray2.add (ray(s, t,  10));
    ray3.add (ray(s, t,  50));
    ray4.add (ray(s, t,  90));
    ray5.add (ray(s, t, 130));
  }
  win.attach (ray1);
  win.attach (ray2);
  win.attach (ray3);
  win.attach (ray4);
  win.attach (ray5);

  Rectangle grass{ Point{ 0, sky_h }, win_w, win_h - sky_h };
  grass.set_color (Color::green);
  grass.set_fill_color (Color::green);
  win.attach (grass);


  constexpr int hw = 360;   // house width
  constexpr int hh = hw/2;  // one floor height
  Point h{ 120, 380 };      // bottom left corner of the house

  Open_polyline house;
  house.add (Point{ h.x, h.y - hh });
  house.add (Point{ h.x, h.y });
  house.add (Point{ h.x + hw, h.y });
  house.add (Point{ h.x + hw, h.y - hh });
  house.add (Point{ h.x, h.y - hh });
  house.add (Point{ h.x + hw/2, h.y - 2*hh });
  house.add (Point{ h.x + hw, h.y - hh });
  house.set_style (style);
  house.set_fill_color (Color::dark_red);
  win.attach (house);

  constexpr int dw = 60;    // door width
  constexpr int dh = 2*dw;  // and height

  Rectangle door{ Point{ h.x + hw/2 - dw/2, h.y - dh }, dw, dh };
  door.set_style (style);
  door.set_fill_color (Color::black);
  win.attach (door);

  constexpr int ww = 60;  // window width
  constexpr int wm = 40;  // and marging from the house left corner

  Rectangle left_win{ Point{ h.x + wm, h.y - dh }, ww, ww };
  left_win.set_style (style);
  left_win.set_fill_color (Color::dark_yellow);
  win.attach (left_win);

  Rectangle right_win{ Point{ h.x + hw - ww - wm, h.y - dh }, ww, ww };
  right_win.set_style (style);
  right_win.set_fill_color (Color::dark_yellow);
  win.attach (right_win);

  constexpr int cw = 40;           // chimney width,
  constexpr int ch = 3*cw/2;       // height
  Point c{ h.x + 3*hw/4 - cw/2,
           h.y - 3*hh/2 - cw/2 };  // and left bottom point

  Closed_polyline chimney;
  chimney.add (c);
  chimney.add (Point{ c.x, c.y - ch });
  chimney.add (Point{ c.x + cw, c.y - ch });
  chimney.add (Point{ c.x + cw, c.y + cw });
  chimney.set_style (style);
  chimney.set_fill_color (Color::dark_red);
  win.attach (chimney);

  s = Point{ c.x, c.y - ch };  // smoke box bottom left corner
  Open_polyline smoke1, smoke2, smoke3;
  smoke1.set_style (style);
  smoke2.set_style (style);
  smoke3.set_style (style);
  for (int t = 0; t < 40; t += 2)
  {
    smoke1.add (ray(Point{ s.x + 10, s.y }, t, -90));
    smoke2.add (ray(Point{ s.x + 20, s.y }, t, -90));
    smoke3.add (ray(Point{ s.x + 30, s.y }, t, -90));
  }
  win.attach (smoke1);
  win.attach (smoke2);
  win.attach (smoke3);

  win.wait_for_button();
}
catch (std::exception & e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr <<"Oops, something went wrong..."<< std::endl;
  return 2;
}
