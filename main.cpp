#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pixel.h"

#define HEIGHT 256

void average_colors(std::vector<Pixel> &pixel_list)
{
  float sum_r = 0, sum_g = 0, sum_b = 0;

  for (int i = 0; i < pixel_list.size(); i++)
  {
    sum_r += pixel_list[i].r;
    sum_g += pixel_list[i].g;
    sum_b += pixel_list[i].b;
  }

  std::cout << "Average r: " << sum_r / pixel_list.size() << std::endl;
  std::cout << "Average g: " << sum_g / pixel_list.size() << std::endl;
  std::cout << "Average b: " << sum_b / pixel_list.size() << std::endl;
}

void flip_vertically(std::vector<Pixel> &pixel_list)
{
  // x and y stay in place, only the colors swap between y and HEIGHT-1-y
  // pixel index = x * HEIGHT + y
  int width = pixel_list.size() / HEIGHT;

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < HEIGHT / 2; y++)
    {
      int top = x * HEIGHT + y;
      int bottom = x * HEIGHT + (HEIGHT - 1 - y);

      Pixel temp = pixel_list[top];
      pixel_list[top].r = pixel_list[bottom].r;
      pixel_list[top].g = pixel_list[bottom].g;
      pixel_list[top].b = pixel_list[bottom].b;
      pixel_list[bottom].r = temp.r;
      pixel_list[bottom].g = temp.g;
      pixel_list[bottom].b = temp.b;
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: ./main pixels.dat" << std::endl;
    return 1;
  }

  std::vector<Pixel> pixel_list;
  std::ifstream fin(argv[1]);

  if (!fin.is_open())
  {
    std::cout << "Could not open file" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(fin, line))
  {
    if (line.empty())
      continue;

    // find each comma, then use substr to grab the text between them
    int c1 = line.find(',');
    int c2 = line.find(',', c1 + 1);
    int c3 = line.find(',', c2 + 1);
    int c4 = line.find(',', c3 + 1);

    Pixel p;
    p.x = std::stoi(line.substr(0, c1));
    p.y = std::stoi(line.substr(c1 + 1, c2 - c1 - 1));
    p.r = std::stof(line.substr(c2 + 1, c3 - c2 - 1));
    p.g = std::stof(line.substr(c3 + 1, c4 - c3 - 1));
    p.b = std::stof(line.substr(c4 + 1));

    pixel_list.push_back(p);
  }
  fin.close();

  std::cout << "Pixels read: " << pixel_list.size() << std::endl;

  average_colors(pixel_list);
  flip_vertically(pixel_list);

  std::ofstream fout("flipped.dat");
  for (int i = 0; i < pixel_list.size(); i++)
  {
    fout << pixel_list[i].x << "," << pixel_list[i].y << ","
         << pixel_list[i].r << "," << pixel_list[i].g << ","
         << pixel_list[i].b << "\n";
  }
  fout.close();

  return 0;
}
