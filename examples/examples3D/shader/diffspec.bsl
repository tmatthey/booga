surface diffspec(real specPow = 30, color specCol = [.8,.8,.8])
{
  Col = diffuse(Col) + specular(specCol, specPow);
}
