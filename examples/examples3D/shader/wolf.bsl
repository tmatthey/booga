surface wolf(vector uP = [.06,.42,1], vector vP = [.325,.675,1])
{
  // this shader uses the "booga" pixmap as a mask. When the original
  // font is black, it will be evaluated as gold, otherwise the object
  // is transparent. uP and vP determine where the font is placed.
  
  real specPow, ctest;
  vector uv;
  
  specPow = 12;
  uP = [0.06,.42,1];
  vP = [0.1,0.9,1];
  uv = getuv(TPos, uP, vP);
  ctest = texturemap("wolfc64.ppm", uv);      // ctest will be black or white
  if (getx(ctest) < 0.2)                    // it is black
    Col = trace(WPos, RDir);                // -> transparent
  else
    Col = diffuse(ctest);

}
