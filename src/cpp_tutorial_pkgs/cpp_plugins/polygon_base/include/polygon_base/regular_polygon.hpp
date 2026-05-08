#pragma once

namespace polygon_base
{

class RegularPolygon
{
public:
  // Used to pass parameters to object as a constructor without parameters is required
  virtual void initialize(double side_length) = 0;
  virtual double area() = 0;
  virtual ~RegularPolygon(){}

protected:
  RegularPolygon(){}
};

} // namespace polygon_base
