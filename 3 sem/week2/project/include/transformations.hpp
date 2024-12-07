#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

color gradient_vertical(const color& color_start, const color& color_end);
color gradient_horizontal(const color& color_start, const color& color_end);
color invert_color(const color&);
color color2bw(const color&);

#endif