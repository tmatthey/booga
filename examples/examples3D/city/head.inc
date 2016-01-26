using 3D;
define col phong {
  diffuse [0.4, 0.1, 0.1];
  ambient [0.2, 0.2, 0.2];
};

using 3D;

camera {
  on;
  background [0.3, 0.3, 0.3];
  perspective {
    eye [0, -2000, 1000];
    lookat [0, -800, 0];
    up [0, 0, 1];
    eyesep 1;
    resolution (600, 400);
    fov 70;
  };
};
pointLight (2, [1, 1, 1]) {
  on;
  position [50, -1000, 1500];
};
