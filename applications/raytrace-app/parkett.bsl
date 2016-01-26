surface parkett()
{
  string sname = "wood.bsl";
  real f11 = .7;
  real f12 = 1.2;
  color c11 = [.5,.3,.21];
  color c12 = [.2,.06,.03];
  
  real f21 = .57;
  real f22 = 2;

  real x,y,z;
  real n1,n2,n3;

  x = getx(TPos);
  y = gety(TPos);
  z = getz(TPos);

  n1 = .125;
  n2 = .175;
  n3 = .625;
  
  if (n1*x - floor(n1*x) <=  0.5)
    if (n2*y - floor(n2*y) <= 0.5)
      if (n3*z - floor(n3*z) <= 0.5)
        shader(sname, f11, f12, c11, c12);
      else
        shader(sname, f21, f22);
    else
      if (n3*z - floor(n3*z) <= 0.5)
        shader(sname, f21, f22);
      else
        shader(sname, f11, f12, c11, c12);
  else
    if (n2*y - floor(n2*y) <= 0.5)
      if (n3*z - floor(n3*z) <= 0.5)
        shader(sname, f21, f22);
      else
        shader(sname, f11, f12, c11, c12);
    else
      if (n3*z - floor(n3*z) <= 0.5)
        shader(sname, f11, f12, c11, c12);
      else
        shader(sname, f21, f22);
}
