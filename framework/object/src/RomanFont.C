/*
 * RomanFont.C
 *
 * Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.
 *
 * -----------------------------------------------------------------------------
 *  $Id: RomanFont.C,v 1.3 1996/04/18 08:42:58 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/RomanFont.h"

/* GENERATED FILE -- DO NOT MODIFY */

/* char: 33 '!' */

static Vector2D RomanChar33Stroke0[] = {
  Vector2D(13.3819, 100),
  Vector2D(13.3819, 33.3333),
};

static Vector2D RomanChar33Stroke1[] = {
  Vector2D(13.3819, 9.5238),
  Vector2D(8.62, 4.7619),
  Vector2D(13.3819, 0),
  Vector2D(18.1438, 4.7619),
  Vector2D(13.3819, 9.5238),
};

static StrokeRec RomanChar33[] = {
   { 2, RomanChar33Stroke0  },
   { 5, RomanChar33Stroke1  },
};

/* char: 34 '"' */

static Vector2D RomanChar34Stroke0[] = {
  Vector2D(4.02, 100),
  Vector2D(4.02, 66.6667),
};

static Vector2D RomanChar34Stroke1[] = {
  Vector2D(42.1152, 100),
  Vector2D(42.1152, 66.6667),
};

static StrokeRec RomanChar34[] = {
   { 2, RomanChar34Stroke0  },
   { 2, RomanChar34Stroke1  },
};

/* char: 35 '#' */

static Vector2D RomanChar35Stroke0[] = {
  Vector2D(41.2952, 119.048),
  Vector2D(7.9619, -33.3333),
};

static Vector2D RomanChar35Stroke1[] = {
  Vector2D(69.8667, 119.048),
  Vector2D(36.5333, -33.3333),
};

static Vector2D RomanChar35Stroke2[] = {
  Vector2D(7.9619, 57.1429),
  Vector2D(74.6286, 57.1429),
};

static Vector2D RomanChar35Stroke3[] = {
  Vector2D(3.2, 28.5714),
  Vector2D(69.8667, 28.5714),
};

static StrokeRec RomanChar35[] = {
   { 2, RomanChar35Stroke0  },
   { 2, RomanChar35Stroke1  },
   { 2, RomanChar35Stroke2  },
   { 2, RomanChar35Stroke3  },
};

/* char: 36 '$' */

static Vector2D RomanChar36Stroke0[] = {
  Vector2D(28.6295, 119.048),
  Vector2D(28.6295, -19.0476),
};

static Vector2D RomanChar36Stroke1[] = {
  Vector2D(47.6771, 119.048),
  Vector2D(47.6771, -19.0476),
};

static Vector2D RomanChar36Stroke2[] = {
  Vector2D(71.4867, 85.7143),
  Vector2D(61.9629, 95.2381),
  Vector2D(47.6771, 100),
  Vector2D(28.6295, 100),
  Vector2D(14.3438, 95.2381),
  Vector2D(4.82, 85.7143),
  Vector2D(4.82, 76.1905),
  Vector2D(9.5819, 66.6667),
  Vector2D(14.3438, 61.9048),
  Vector2D(23.8676, 57.1429),
  Vector2D(52.439, 47.619),
  Vector2D(61.9629, 42.8571),
  Vector2D(66.7248, 38.0952),
  Vector2D(71.4867, 28.5714),
  Vector2D(71.4867, 14.2857),
  Vector2D(61.9629, 4.7619),
  Vector2D(47.6771, 0),
  Vector2D(28.6295, 0),
  Vector2D(14.3438, 4.7619),
  Vector2D(4.82, 14.2857),
};

static StrokeRec RomanChar36[] = {
   { 2, RomanChar36Stroke0  },
   { 2, RomanChar36Stroke1  },
   { 20, RomanChar36Stroke2  },
};

/* char: 37 '%' */

static Vector2D RomanChar37Stroke0[] = {
  Vector2D(92.0743, 100),
  Vector2D(6.36, 0),
};

static Vector2D RomanChar37Stroke1[] = {
  Vector2D(30.1695, 100),
  Vector2D(39.6933, 90.4762),
  Vector2D(39.6933, 80.9524),
  Vector2D(34.9314, 71.4286),
  Vector2D(25.4076, 66.6667),
  Vector2D(15.8838, 66.6667),
  Vector2D(6.36, 76.1905),
  Vector2D(6.36, 85.7143),
  Vector2D(11.1219, 95.2381),
  Vector2D(20.6457, 100),
  Vector2D(30.1695, 100),
  Vector2D(39.6933, 95.2381),
  Vector2D(53.979, 90.4762),
  Vector2D(68.2648, 90.4762),
  Vector2D(82.5505, 95.2381),
  Vector2D(92.0743, 100),
};

static Vector2D RomanChar37Stroke2[] = {
  Vector2D(73.0267, 33.3333),
  Vector2D(63.5029, 28.5714),
  Vector2D(58.741, 19.0476),
  Vector2D(58.741, 9.5238),
  Vector2D(68.2648, 0),
  Vector2D(77.7886, 0),
  Vector2D(87.3124, 4.7619),
  Vector2D(92.0743, 14.2857),
  Vector2D(92.0743, 23.8095),
  Vector2D(82.5505, 33.3333),
  Vector2D(73.0267, 33.3333),
};

static StrokeRec RomanChar37[] = {
   { 2, RomanChar37Stroke0  },
   { 16, RomanChar37Stroke1  },
   { 11, RomanChar37Stroke2  },
};

/* char: 38 '&' */

static Vector2D RomanChar38Stroke0[] = {
  Vector2D(101.218, 57.1429),
  Vector2D(101.218, 61.9048),
  Vector2D(96.4562, 66.6667),
  Vector2D(91.6943, 66.6667),
  Vector2D(86.9324, 61.9048),
  Vector2D(82.1705, 52.381),
  Vector2D(72.6467, 28.5714),
  Vector2D(63.1229, 14.2857),
  Vector2D(53.599, 4.7619),
  Vector2D(44.0752, 0),
  Vector2D(25.0276, 0),
  Vector2D(15.5038, 4.7619),
  Vector2D(10.7419, 9.5238),
  Vector2D(5.98, 19.0476),
  Vector2D(5.98, 28.5714),
  Vector2D(10.7419, 38.0952),
  Vector2D(15.5038, 42.8571),
  Vector2D(48.8371, 61.9048),
  Vector2D(53.599, 66.6667),
  Vector2D(58.361, 76.1905),
  Vector2D(58.361, 85.7143),
  Vector2D(53.599, 95.2381),
  Vector2D(44.0752, 100),
  Vector2D(34.5514, 95.2381),
  Vector2D(29.7895, 85.7143),
  Vector2D(29.7895, 76.1905),
  Vector2D(34.5514, 61.9048),
  Vector2D(44.0752, 47.619),
  Vector2D(67.8848, 14.2857),
  Vector2D(77.4086, 4.7619),
  Vector2D(86.9324, 0),
  Vector2D(96.4562, 0),
  Vector2D(101.218, 4.7619),
  Vector2D(101.218, 9.5238),
};

static StrokeRec RomanChar38[] = {
   { 34, RomanChar38Stroke0  },
};

/* char: 39 ''' */

static Vector2D RomanChar39Stroke0[] = {
  Vector2D(4.44, 100),
  Vector2D(4.44, 66.6667),
};

static StrokeRec RomanChar39[] = {
   { 2, RomanChar39Stroke0  },
};

/* char: 40 '(' */

static Vector2D RomanChar40Stroke0[] = {
  Vector2D(40.9133, 119.048),
  Vector2D(31.3895, 109.524),
  Vector2D(21.8657, 95.2381),
  Vector2D(12.3419, 76.1905),
  Vector2D(7.58, 52.381),
  Vector2D(7.58, 33.3333),
  Vector2D(12.3419, 9.5238),
  Vector2D(21.8657, -9.5238),
  Vector2D(31.3895, -23.8095),
  Vector2D(40.9133, -33.3333),
};

static StrokeRec RomanChar40[] = {
   { 10, RomanChar40Stroke0  },
};

/* char: 41 ')' */

static Vector2D RomanChar41Stroke0[] = {
  Vector2D(5.28, 119.048),
  Vector2D(14.8038, 109.524),
  Vector2D(24.3276, 95.2381),
  Vector2D(33.8514, 76.1905),
  Vector2D(38.6133, 52.381),
  Vector2D(38.6133, 33.3333),
  Vector2D(33.8514, 9.5238),
  Vector2D(24.3276, -9.5238),
  Vector2D(14.8038, -23.8095),
  Vector2D(5.28, -33.3333),
};

static StrokeRec RomanChar41[] = {
   { 10, RomanChar41Stroke0  },
};

/* char: 42 '*' */

static Vector2D RomanChar42Stroke0[] = {
  Vector2D(30.7695, 71.4286),
  Vector2D(30.7695, 14.2857),
};

static Vector2D RomanChar42Stroke1[] = {
  Vector2D(6.96, 57.1429),
  Vector2D(54.579, 28.5714),
};

static Vector2D RomanChar42Stroke2[] = {
  Vector2D(54.579, 57.1429),
  Vector2D(6.96, 28.5714),
};

static StrokeRec RomanChar42[] = {
   { 2, RomanChar42Stroke0  },
   { 2, RomanChar42Stroke1  },
   { 2, RomanChar42Stroke2  },
};

/* char: 43 '+' */

static Vector2D RomanChar43Stroke0[] = {
  Vector2D(48.8371, 85.7143),
  Vector2D(48.8371, 0),
};

static Vector2D RomanChar43Stroke1[] = {
  Vector2D(5.98, 42.8571),
  Vector2D(91.6943, 42.8571),
};

static StrokeRec RomanChar43[] = {
   { 2, RomanChar43Stroke0  },
   { 2, RomanChar43Stroke1  },
};

/* char: 44 ',' */

static Vector2D RomanChar44Stroke0[] = {
  Vector2D(18.2838, 4.7619),
  Vector2D(13.5219, 0),
  Vector2D(8.76, 4.7619),
  Vector2D(13.5219, 9.5238),
  Vector2D(18.2838, 4.7619),
  Vector2D(18.2838, -4.7619),
  Vector2D(13.5219, -14.2857),
  Vector2D(8.76, -19.0476),
};

static StrokeRec RomanChar44[] = {
   { 8, RomanChar44Stroke0  },
};

/* char: 45 '-' */

static Vector2D RomanChar45Stroke0[] = {
  Vector2D(7.38, 42.8571),
  Vector2D(93.0943, 42.8571),
};

static StrokeRec RomanChar45[] = {
   { 2, RomanChar45Stroke0  },
};

/* char: 46 '.' */

static Vector2D RomanChar46Stroke0[] = {
  Vector2D(13.1019, 9.5238),
  Vector2D(8.34, 4.7619),
  Vector2D(13.1019, 0),
  Vector2D(17.8638, 4.7619),
  Vector2D(13.1019, 9.5238),
};

static StrokeRec RomanChar46[] = {
   { 5, RomanChar46Stroke0  },
};

/* char: 47 '/' */

static Vector2D RomanChar47Stroke0[] = {
  Vector2D(7.24, -14.2857),
  Vector2D(73.9067, 100),
};

static StrokeRec RomanChar47[] = {
   { 2, RomanChar47Stroke0  },
};

/* char: 48 '0' */

static Vector2D RomanChar48Stroke0[] = {
  Vector2D(33.5514, 100),
  Vector2D(19.2657, 95.2381),
  Vector2D(9.7419, 80.9524),
  Vector2D(4.98, 57.1429),
  Vector2D(4.98, 42.8571),
  Vector2D(9.7419, 19.0476),
  Vector2D(19.2657, 4.7619),
  Vector2D(33.5514, 0),
  Vector2D(43.0752, 0),
  Vector2D(57.361, 4.7619),
  Vector2D(66.8848, 19.0476),
  Vector2D(71.6467, 42.8571),
  Vector2D(71.6467, 57.1429),
  Vector2D(66.8848, 80.9524),
  Vector2D(57.361, 95.2381),
  Vector2D(43.0752, 100),
  Vector2D(33.5514, 100),
};

static StrokeRec RomanChar48[] = {
   { 17, RomanChar48Stroke0  },
};

/* char: 49 '1' */

static Vector2D RomanChar49Stroke0[] = {
  Vector2D(11.82, 80.9524),
  Vector2D(21.3438, 85.7143),
  Vector2D(35.6295, 100),
  Vector2D(35.6295, 0),
};

static StrokeRec RomanChar49[] = {
   { 4, RomanChar49Stroke0  },
};

/* char: 50 '2' */

static Vector2D RomanChar50Stroke0[] = {
  Vector2D(10.1819, 76.1905),
  Vector2D(10.1819, 80.9524),
  Vector2D(14.9438, 90.4762),
  Vector2D(19.7057, 95.2381),
  Vector2D(29.2295, 100),
  Vector2D(48.2771, 100),
  Vector2D(57.801, 95.2381),
  Vector2D(62.5629, 90.4762),
  Vector2D(67.3248, 80.9524),
  Vector2D(67.3248, 71.4286),
  Vector2D(62.5629, 61.9048),
  Vector2D(53.039, 47.619),
  Vector2D(5.42, 0),
  Vector2D(72.0867, 0),
};

static StrokeRec RomanChar50[] = {
   { 14, RomanChar50Stroke0  },
};

/* char: 51 '3' */

static Vector2D RomanChar51Stroke0[] = {
  Vector2D(14.5238, 100),
  Vector2D(66.9048, 100),
  Vector2D(38.3333, 61.9048),
  Vector2D(52.619, 61.9048),
  Vector2D(62.1429, 57.1429),
  Vector2D(66.9048, 52.381),
  Vector2D(71.6667, 38.0952),
  Vector2D(71.6667, 28.5714),
  Vector2D(66.9048, 14.2857),
  Vector2D(57.381, 4.7619),
  Vector2D(43.0952, 0),
  Vector2D(28.8095, 0),
  Vector2D(14.5238, 4.7619),
  Vector2D(9.7619, 9.5238),
  Vector2D(5, 19.0476),
};

static StrokeRec RomanChar51[] = {
   { 15, RomanChar51Stroke0  },
};

/* char: 52 '4' */

static Vector2D RomanChar52Stroke0[] = {
  Vector2D(51.499, 100),
  Vector2D(3.88, 33.3333),
  Vector2D(75.3086, 33.3333),
};

static Vector2D RomanChar52Stroke1[] = {
  Vector2D(51.499, 100),
  Vector2D(51.499, 0),
};

static StrokeRec RomanChar52[] = {
   { 3, RomanChar52Stroke0  },
   { 2, RomanChar52Stroke1  },
};

/* char: 53 '5' */

static Vector2D RomanChar53Stroke0[] = {
  Vector2D(62.0029, 100),
  Vector2D(14.3838, 100),
  Vector2D(9.6219, 57.1429),
  Vector2D(14.3838, 61.9048),
  Vector2D(28.6695, 66.6667),
  Vector2D(42.9552, 66.6667),
  Vector2D(57.241, 61.9048),
  Vector2D(66.7648, 52.381),
  Vector2D(71.5267, 38.0952),
  Vector2D(71.5267, 28.5714),
  Vector2D(66.7648, 14.2857),
  Vector2D(57.241, 4.7619),
  Vector2D(42.9552, 0),
  Vector2D(28.6695, 0),
  Vector2D(14.3838, 4.7619),
  Vector2D(9.6219, 9.5238),
  Vector2D(4.86, 19.0476),
};

static StrokeRec RomanChar53[] = {
   { 17, RomanChar53Stroke0  },
};

/* char: 54 '6' */

static Vector2D RomanChar54Stroke0[] = {
  Vector2D(62.7229, 85.7143),
  Vector2D(57.961, 95.2381),
  Vector2D(43.6752, 100),
  Vector2D(34.1514, 100),
  Vector2D(19.8657, 95.2381),
  Vector2D(10.3419, 80.9524),
  Vector2D(5.58, 57.1429),
  Vector2D(5.58, 33.3333),
  Vector2D(10.3419, 14.2857),
  Vector2D(19.8657, 4.7619),
  Vector2D(34.1514, 0),
  Vector2D(38.9133, 0),
  Vector2D(53.199, 4.7619),
  Vector2D(62.7229, 14.2857),
  Vector2D(67.4848, 28.5714),
  Vector2D(67.4848, 33.3333),
  Vector2D(62.7229, 47.619),
  Vector2D(53.199, 57.1429),
  Vector2D(38.9133, 61.9048),
  Vector2D(34.1514, 61.9048),
  Vector2D(19.8657, 57.1429),
  Vector2D(10.3419, 47.619),
  Vector2D(5.58, 33.3333),
};

static StrokeRec RomanChar54[] = {
   { 23, RomanChar54Stroke0  },
};

/* char: 55 '7' */

static Vector2D RomanChar55Stroke0[] = {
  Vector2D(72.2267, 100),
  Vector2D(24.6076, 0),
};

static Vector2D RomanChar55Stroke1[] = {
  Vector2D(5.56, 100),
  Vector2D(72.2267, 100),
};

static StrokeRec RomanChar55[] = {
   { 2, RomanChar55Stroke0  },
   { 2, RomanChar55Stroke1  },
};

/* char: 56 '8' */

static Vector2D RomanChar56Stroke0[] = {
  Vector2D(29.4095, 100),
  Vector2D(15.1238, 95.2381),
  Vector2D(10.3619, 85.7143),
  Vector2D(10.3619, 76.1905),
  Vector2D(15.1238, 66.6667),
  Vector2D(24.6476, 61.9048),
  Vector2D(43.6952, 57.1429),
  Vector2D(57.981, 52.381),
  Vector2D(67.5048, 42.8571),
  Vector2D(72.2667, 33.3333),
  Vector2D(72.2667, 19.0476),
  Vector2D(67.5048, 9.5238),
  Vector2D(62.7429, 4.7619),
  Vector2D(48.4571, 0),
  Vector2D(29.4095, 0),
  Vector2D(15.1238, 4.7619),
  Vector2D(10.3619, 9.5238),
  Vector2D(5.6, 19.0476),
  Vector2D(5.6, 33.3333),
  Vector2D(10.3619, 42.8571),
  Vector2D(19.8857, 52.381),
  Vector2D(34.1714, 57.1429),
  Vector2D(53.219, 61.9048),
  Vector2D(62.7429, 66.6667),
  Vector2D(67.5048, 76.1905),
  Vector2D(67.5048, 85.7143),
  Vector2D(62.7429, 95.2381),
  Vector2D(48.4571, 100),
  Vector2D(29.4095, 100),
};

static StrokeRec RomanChar56[] = {
   { 29, RomanChar56Stroke0  },
};

/* char: 57 '9' */

static Vector2D RomanChar57Stroke0[] = {
  Vector2D(68.5048, 66.6667),
  Vector2D(63.7429, 52.381),
  Vector2D(54.219, 42.8571),
  Vector2D(39.9333, 38.0952),
  Vector2D(35.1714, 38.0952),
  Vector2D(20.8857, 42.8571),
  Vector2D(11.3619, 52.381),
  Vector2D(6.6, 66.6667),
  Vector2D(6.6, 71.4286),
  Vector2D(11.3619, 85.7143),
  Vector2D(20.8857, 95.2381),
  Vector2D(35.1714, 100),
  Vector2D(39.9333, 100),
  Vector2D(54.219, 95.2381),
  Vector2D(63.7429, 85.7143),
  Vector2D(68.5048, 66.6667),
  Vector2D(68.5048, 42.8571),
  Vector2D(63.7429, 19.0476),
  Vector2D(54.219, 4.7619),
  Vector2D(39.9333, 0),
  Vector2D(30.4095, 0),
  Vector2D(16.1238, 4.7619),
  Vector2D(11.3619, 14.2857),
};

static StrokeRec RomanChar57[] = {
   { 23, RomanChar57Stroke0  },
};

/* char: 58 ':' */

static Vector2D RomanChar58Stroke0[] = {
  Vector2D(14.0819, 66.6667),
  Vector2D(9.32, 61.9048),
  Vector2D(14.0819, 57.1429),
  Vector2D(18.8438, 61.9048),
  Vector2D(14.0819, 66.6667),
};

static Vector2D RomanChar58Stroke1[] = {
  Vector2D(14.0819, 9.5238),
  Vector2D(9.32, 4.7619),
  Vector2D(14.0819, 0),
  Vector2D(18.8438, 4.7619),
  Vector2D(14.0819, 9.5238),
};

static StrokeRec RomanChar58[] = {
   { 5, RomanChar58Stroke0  },
   { 5, RomanChar58Stroke1  },
};

/* char: 59 ';' */

static Vector2D RomanChar59Stroke0[] = {
  Vector2D(12.9619, 66.6667),
  Vector2D(8.2, 61.9048),
  Vector2D(12.9619, 57.1429),
  Vector2D(17.7238, 61.9048),
  Vector2D(12.9619, 66.6667),
};

static Vector2D RomanChar59Stroke1[] = {
  Vector2D(17.7238, 4.7619),
  Vector2D(12.9619, 0),
  Vector2D(8.2, 4.7619),
  Vector2D(12.9619, 9.5238),
  Vector2D(17.7238, 4.7619),
  Vector2D(17.7238, -4.7619),
  Vector2D(12.9619, -14.2857),
  Vector2D(8.2, -19.0476),
};

static StrokeRec RomanChar59[] = {
   { 5, RomanChar59Stroke0  },
   { 8, RomanChar59Stroke1  },
};

/* char: 60 '<' */

static Vector2D RomanChar60Stroke0[] = {
  Vector2D(79.2505, 85.7143),
  Vector2D(3.06, 42.8571),
  Vector2D(79.2505, 0),
};

static StrokeRec RomanChar60[] = {
   { 3, RomanChar60Stroke0  },
};

/* char: 61 '=' */

static Vector2D RomanChar61Stroke0[] = {
  Vector2D(5.7, 57.1429),
  Vector2D(91.4143, 57.1429),
};

static Vector2D RomanChar61Stroke1[] = {
  Vector2D(5.7, 28.5714),
  Vector2D(91.4143, 28.5714),
};

static StrokeRec RomanChar61[] = {
   { 2, RomanChar61Stroke0  },
   { 2, RomanChar61Stroke1  },
};

/* char: 62 '>' */

static Vector2D RomanChar62Stroke0[] = {
  Vector2D(2.78, 85.7143),
  Vector2D(78.9705, 42.8571),
  Vector2D(2.78, 0),
};

static StrokeRec RomanChar62[] = {
   { 3, RomanChar62Stroke0  },
};

/* char: 63 '?' */

static Vector2D RomanChar63Stroke0[] = {
  Vector2D(8.42, 76.1905),
  Vector2D(8.42, 80.9524),
  Vector2D(13.1819, 90.4762),
  Vector2D(17.9438, 95.2381),
  Vector2D(27.4676, 100),
  Vector2D(46.5152, 100),
  Vector2D(56.039, 95.2381),
  Vector2D(60.801, 90.4762),
  Vector2D(65.5629, 80.9524),
  Vector2D(65.5629, 71.4286),
  Vector2D(60.801, 61.9048),
  Vector2D(56.039, 57.1429),
  Vector2D(36.9914, 47.619),
  Vector2D(36.9914, 33.3333),
};

static Vector2D RomanChar63Stroke1[] = {
  Vector2D(36.9914, 9.5238),
  Vector2D(32.2295, 4.7619),
  Vector2D(36.9914, 0),
  Vector2D(41.7533, 4.7619),
  Vector2D(36.9914, 9.5238),
};

static StrokeRec RomanChar63[] = {
   { 14, RomanChar63Stroke0  },
   { 5, RomanChar63Stroke1  },
};

/* char: 64 '@' */

static Vector2D RomanChar64Stroke0[] = {
  Vector2D(49.2171, 52.381),
  Vector2D(39.6933, 57.1429),
  Vector2D(30.1695, 57.1429),
  Vector2D(25.4076, 47.619),
  Vector2D(25.4076, 42.8571),
  Vector2D(30.1695, 33.3333),
  Vector2D(39.6933, 33.3333),
  Vector2D(49.2171, 38.0952),
};

static Vector2D RomanChar64Stroke1[] = {
  Vector2D(49.2171, 57.1429),
  Vector2D(49.2171, 38.0952),
  Vector2D(53.979, 33.3333),
  Vector2D(63.5029, 33.3333),
  Vector2D(68.2648, 42.8571),
  Vector2D(68.2648, 47.619),
  Vector2D(63.5029, 61.9048),
  Vector2D(53.979, 71.4286),
  Vector2D(39.6933, 76.1905),
  Vector2D(34.9314, 76.1905),
  Vector2D(20.6457, 71.4286),
  Vector2D(11.1219, 61.9048),
  Vector2D(6.36, 47.619),
  Vector2D(6.36, 42.8571),
  Vector2D(11.1219, 28.5714),
  Vector2D(20.6457, 19.0476),
  Vector2D(34.9314, 14.2857),
  Vector2D(39.6933, 14.2857),
  Vector2D(53.979, 19.0476),
};

static StrokeRec RomanChar64[] = {
   { 8, RomanChar64Stroke0  },
   { 19, RomanChar64Stroke1  },
};

/* char: 65 'A' */

static Vector2D RomanChar65Stroke0[] = {
  Vector2D(40.5952, 100),
  Vector2D(2.5, 0),
};

static Vector2D RomanChar65Stroke1[] = {
  Vector2D(40.5952, 100),
  Vector2D(78.6905, 0),
};

static Vector2D RomanChar65Stroke2[] = {
  Vector2D(16.7857, 33.3333),
  Vector2D(64.4048, 33.3333),
};

static StrokeRec RomanChar65[] = {
   { 2, RomanChar65Stroke0  },
   { 2, RomanChar65Stroke1  },
   { 2, RomanChar65Stroke2  },
};

/* char: 66 'B' */

static Vector2D RomanChar66Stroke0[] = {
  Vector2D(11.42, 100),
  Vector2D(11.42, 0),
};

static Vector2D RomanChar66Stroke1[] = {
  Vector2D(11.42, 100),
  Vector2D(54.2771, 100),
  Vector2D(68.5629, 95.2381),
  Vector2D(73.3248, 90.4762),
  Vector2D(78.0867, 80.9524),
  Vector2D(78.0867, 71.4286),
  Vector2D(73.3248, 61.9048),
  Vector2D(68.5629, 57.1429),
  Vector2D(54.2771, 52.381),
};

static Vector2D RomanChar66Stroke2[] = {
  Vector2D(11.42, 52.381),
  Vector2D(54.2771, 52.381),
  Vector2D(68.5629, 47.619),
  Vector2D(73.3248, 42.8571),
  Vector2D(78.0867, 33.3333),
  Vector2D(78.0867, 19.0476),
  Vector2D(73.3248, 9.5238),
  Vector2D(68.5629, 4.7619),
  Vector2D(54.2771, 0),
  Vector2D(11.42, 0),
};

static StrokeRec RomanChar66[] = {
   { 2, RomanChar66Stroke0  },
   { 9, RomanChar66Stroke1  },
   { 10, RomanChar66Stroke2  },
};

/* char: 67 'C' */

static Vector2D RomanChar67Stroke0[] = {
  Vector2D(78.0886, 76.1905),
  Vector2D(73.3267, 85.7143),
  Vector2D(63.8029, 95.2381),
  Vector2D(54.279, 100),
  Vector2D(35.2314, 100),
  Vector2D(25.7076, 95.2381),
  Vector2D(16.1838, 85.7143),
  Vector2D(11.4219, 76.1905),
  Vector2D(6.66, 61.9048),
  Vector2D(6.66, 38.0952),
  Vector2D(11.4219, 23.8095),
  Vector2D(16.1838, 14.2857),
  Vector2D(25.7076, 4.7619),
  Vector2D(35.2314, 0),
  Vector2D(54.279, 0),
  Vector2D(63.8029, 4.7619),
  Vector2D(73.3267, 14.2857),
  Vector2D(78.0886, 23.8095),
};

static StrokeRec RomanChar67[] = {
   { 18, RomanChar67Stroke0  },
};

/* char: 68 'D' */

static Vector2D RomanChar68Stroke0[] = {
  Vector2D(11.96, 100),
  Vector2D(11.96, 0),
};

static Vector2D RomanChar68Stroke1[] = {
  Vector2D(11.96, 100),
  Vector2D(45.2933, 100),
  Vector2D(59.579, 95.2381),
  Vector2D(69.1029, 85.7143),
  Vector2D(73.8648, 76.1905),
  Vector2D(78.6267, 61.9048),
  Vector2D(78.6267, 38.0952),
  Vector2D(73.8648, 23.8095),
  Vector2D(69.1029, 14.2857),
  Vector2D(59.579, 4.7619),
  Vector2D(45.2933, 0),
  Vector2D(11.96, 0),
};

static StrokeRec RomanChar68[] = {
   { 2, RomanChar68Stroke0  },
   { 12, RomanChar68Stroke1  },
};

/* char: 69 'E' */

static Vector2D RomanChar69Stroke0[] = {
  Vector2D(11.42, 100),
  Vector2D(11.42, 0),
};

static Vector2D RomanChar69Stroke1[] = {
  Vector2D(11.42, 100),
  Vector2D(73.3248, 100),
};

static Vector2D RomanChar69Stroke2[] = {
  Vector2D(11.42, 52.381),
  Vector2D(49.5152, 52.381),
};

static Vector2D RomanChar69Stroke3[] = {
  Vector2D(11.42, 0),
  Vector2D(73.3248, 0),
};

static StrokeRec RomanChar69[] = {
   { 2, RomanChar69Stroke0  },
   { 2, RomanChar69Stroke1  },
   { 2, RomanChar69Stroke2  },
   { 2, RomanChar69Stroke3  },
};

/* char: 70 'F' */

static Vector2D RomanChar70Stroke0[] = {
  Vector2D(11.42, 100),
  Vector2D(11.42, 0),
};

static Vector2D RomanChar70Stroke1[] = {
  Vector2D(11.42, 100),
  Vector2D(73.3248, 100),
};

static Vector2D RomanChar70Stroke2[] = {
  Vector2D(11.42, 52.381),
  Vector2D(49.5152, 52.381),
};

static StrokeRec RomanChar70[] = {
   { 2, RomanChar70Stroke0  },
   { 2, RomanChar70Stroke1  },
   { 2, RomanChar70Stroke2  },
};

/* char: 71 'G' */

static Vector2D RomanChar71Stroke0[] = {
  Vector2D(78.4886, 76.1905),
  Vector2D(73.7267, 85.7143),
  Vector2D(64.2029, 95.2381),
  Vector2D(54.679, 100),
  Vector2D(35.6314, 100),
  Vector2D(26.1076, 95.2381),
  Vector2D(16.5838, 85.7143),
  Vector2D(11.8219, 76.1905),
  Vector2D(7.06, 61.9048),
  Vector2D(7.06, 38.0952),
  Vector2D(11.8219, 23.8095),
  Vector2D(16.5838, 14.2857),
  Vector2D(26.1076, 4.7619),
  Vector2D(35.6314, 0),
  Vector2D(54.679, 0),
  Vector2D(64.2029, 4.7619),
  Vector2D(73.7267, 14.2857),
  Vector2D(78.4886, 23.8095),
  Vector2D(78.4886, 38.0952),
};

static Vector2D RomanChar71Stroke1[] = {
  Vector2D(54.679, 38.0952),
  Vector2D(78.4886, 38.0952),
};

static StrokeRec RomanChar71[] = {
   { 19, RomanChar71Stroke0  },
   { 2, RomanChar71Stroke1  },
};

/* char: 72 'H' */

static Vector2D RomanChar72Stroke0[] = {
  Vector2D(11.42, 100),
  Vector2D(11.42, 0),
};

static Vector2D RomanChar72Stroke1[] = {
  Vector2D(78.0867, 100),
  Vector2D(78.0867, 0),
};

static Vector2D RomanChar72Stroke2[] = {
  Vector2D(11.42, 52.381),
  Vector2D(78.0867, 52.381),
};

static StrokeRec RomanChar72[] = {
   { 2, RomanChar72Stroke0  },
   { 2, RomanChar72Stroke1  },
   { 2, RomanChar72Stroke2  },
};

/* char: 73 'I' */

static Vector2D RomanChar73Stroke0[] = {
  Vector2D(10.86, 100),
  Vector2D(10.86, 0),
};

static StrokeRec RomanChar73[] = {
   { 2, RomanChar73Stroke0  },
};

/* char: 74 'J' */

static Vector2D RomanChar74Stroke0[] = {
  Vector2D(50.119, 100),
  Vector2D(50.119, 23.8095),
  Vector2D(45.3571, 9.5238),
  Vector2D(40.5952, 4.7619),
  Vector2D(31.0714, 0),
  Vector2D(21.5476, 0),
  Vector2D(12.0238, 4.7619),
  Vector2D(7.2619, 9.5238),
  Vector2D(2.5, 23.8095),
  Vector2D(2.5, 33.3333),
};

static StrokeRec RomanChar74[] = {
   { 10, RomanChar74Stroke0  },
};

/* char: 75 'K' */

static Vector2D RomanChar75Stroke0[] = {
  Vector2D(11.28, 100),
  Vector2D(11.28, 0),
};

static Vector2D RomanChar75Stroke1[] = {
  Vector2D(77.9467, 100),
  Vector2D(11.28, 33.3333),
};

static Vector2D RomanChar75Stroke2[] = {
  Vector2D(35.0895, 57.1429),
  Vector2D(77.9467, 0),
};

static StrokeRec RomanChar75[] = {
   { 2, RomanChar75Stroke0  },
   { 2, RomanChar75Stroke1  },
   { 2, RomanChar75Stroke2  },
};

/* char: 76 'L' */

static Vector2D RomanChar76Stroke0[] = {
  Vector2D(11.68, 100),
  Vector2D(11.68, 0),
};

static Vector2D RomanChar76Stroke1[] = {
  Vector2D(11.68, 0),
  Vector2D(68.8229, 0),
};

static StrokeRec RomanChar76[] = {
   { 2, RomanChar76Stroke0  },
   { 2, RomanChar76Stroke1  },
};

/* char: 77 'M' */

static Vector2D RomanChar77Stroke0[] = {
  Vector2D(10.86, 100),
  Vector2D(10.86, 0),
};

static Vector2D RomanChar77Stroke1[] = {
  Vector2D(10.86, 100),
  Vector2D(48.9552, 0),
};

static Vector2D RomanChar77Stroke2[] = {
  Vector2D(87.0505, 100),
  Vector2D(48.9552, 0),
};

static Vector2D RomanChar77Stroke3[] = {
  Vector2D(87.0505, 100),
  Vector2D(87.0505, 0),
};

static StrokeRec RomanChar77[] = {
   { 2, RomanChar77Stroke0  },
   { 2, RomanChar77Stroke1  },
   { 2, RomanChar77Stroke2  },
   { 2, RomanChar77Stroke3  },
};

/* char: 78 'N' */

static Vector2D RomanChar78Stroke0[] = {
  Vector2D(11.14, 100),
  Vector2D(11.14, 0),
};

static Vector2D RomanChar78Stroke1[] = {
  Vector2D(11.14, 100),
  Vector2D(77.8067, 0),
};

static Vector2D RomanChar78Stroke2[] = {
  Vector2D(77.8067, 100),
  Vector2D(77.8067, 0),
};

static StrokeRec RomanChar78[] = {
   { 2, RomanChar78Stroke0  },
   { 2, RomanChar78Stroke1  },
   { 2, RomanChar78Stroke2  },
};

/* char: 79 'O' */

static Vector2D RomanChar79Stroke0[] = {
  Vector2D(34.8114, 100),
  Vector2D(25.2876, 95.2381),
  Vector2D(15.7638, 85.7143),
  Vector2D(11.0019, 76.1905),
  Vector2D(6.24, 61.9048),
  Vector2D(6.24, 38.0952),
  Vector2D(11.0019, 23.8095),
  Vector2D(15.7638, 14.2857),
  Vector2D(25.2876, 4.7619),
  Vector2D(34.8114, 0),
  Vector2D(53.859, 0),
  Vector2D(63.3829, 4.7619),
  Vector2D(72.9067, 14.2857),
  Vector2D(77.6686, 23.8095),
  Vector2D(82.4305, 38.0952),
  Vector2D(82.4305, 61.9048),
  Vector2D(77.6686, 76.1905),
  Vector2D(72.9067, 85.7143),
  Vector2D(63.3829, 95.2381),
  Vector2D(53.859, 100),
  Vector2D(34.8114, 100),
};

static StrokeRec RomanChar79[] = {
   { 21, RomanChar79Stroke0  },
};

/* char: 80 'P' */

static Vector2D RomanChar80Stroke0[] = {
  Vector2D(12.1, 100),
  Vector2D(12.1, 0),
};

static Vector2D RomanChar80Stroke1[] = {
  Vector2D(12.1, 100),
  Vector2D(54.9571, 100),
  Vector2D(69.2429, 95.2381),
  Vector2D(74.0048, 90.4762),
  Vector2D(78.7667, 80.9524),
  Vector2D(78.7667, 66.6667),
  Vector2D(74.0048, 57.1429),
  Vector2D(69.2429, 52.381),
  Vector2D(54.9571, 47.619),
  Vector2D(12.1, 47.619),
};

static StrokeRec RomanChar80[] = {
   { 2, RomanChar80Stroke0  },
   { 10, RomanChar80Stroke1  },
};

/* char: 81 'Q' */

static Vector2D RomanChar81Stroke0[] = {
  Vector2D(33.8714, 100),
  Vector2D(24.3476, 95.2381),
  Vector2D(14.8238, 85.7143),
  Vector2D(10.0619, 76.1905),
  Vector2D(5.3, 61.9048),
  Vector2D(5.3, 38.0952),
  Vector2D(10.0619, 23.8095),
  Vector2D(14.8238, 14.2857),
  Vector2D(24.3476, 4.7619),
  Vector2D(33.8714, 0),
  Vector2D(52.919, 0),
  Vector2D(62.4429, 4.7619),
  Vector2D(71.9667, 14.2857),
  Vector2D(76.7286, 23.8095),
  Vector2D(81.4905, 38.0952),
  Vector2D(81.4905, 61.9048),
  Vector2D(76.7286, 76.1905),
  Vector2D(71.9667, 85.7143),
  Vector2D(62.4429, 95.2381),
  Vector2D(52.919, 100),
  Vector2D(33.8714, 100),
};

static Vector2D RomanChar81Stroke1[] = {
  Vector2D(48.1571, 19.0476),
  Vector2D(76.7286, -9.5238),
};

static StrokeRec RomanChar81[] = {
   { 21, RomanChar81Stroke0  },
   { 2, RomanChar81Stroke1  },
};

/* char: 82 'R' */

static Vector2D RomanChar82Stroke0[] = {
  Vector2D(11.68, 100),
  Vector2D(11.68, 0),
};

static Vector2D RomanChar82Stroke1[] = {
  Vector2D(11.68, 100),
  Vector2D(54.5371, 100),
  Vector2D(68.8229, 95.2381),
  Vector2D(73.5848, 90.4762),
  Vector2D(78.3467, 80.9524),
  Vector2D(78.3467, 71.4286),
  Vector2D(73.5848, 61.9048),
  Vector2D(68.8229, 57.1429),
  Vector2D(54.5371, 52.381),
  Vector2D(11.68, 52.381),
};

static Vector2D RomanChar82Stroke2[] = {
  Vector2D(45.0133, 52.381),
  Vector2D(78.3467, 0),
};

static StrokeRec RomanChar82[] = {
   { 2, RomanChar82Stroke0  },
   { 10, RomanChar82Stroke1  },
   { 2, RomanChar82Stroke2  },
};

/* char: 83 'S' */

static Vector2D RomanChar83Stroke0[] = {
  Vector2D(74.6667, 85.7143),
  Vector2D(65.1429, 95.2381),
  Vector2D(50.8571, 100),
  Vector2D(31.8095, 100),
  Vector2D(17.5238, 95.2381),
  Vector2D(8, 85.7143),
  Vector2D(8, 76.1905),
  Vector2D(12.7619, 66.6667),
  Vector2D(17.5238, 61.9048),
  Vector2D(27.0476, 57.1429),
  Vector2D(55.619, 47.619),
  Vector2D(65.1429, 42.8571),
  Vector2D(69.9048, 38.0952),
  Vector2D(74.6667, 28.5714),
  Vector2D(74.6667, 14.2857),
  Vector2D(65.1429, 4.7619),
  Vector2D(50.8571, 0),
  Vector2D(31.8095, 0),
  Vector2D(17.5238, 4.7619),
  Vector2D(8, 14.2857),
};

static StrokeRec RomanChar83[] = {
   { 20, RomanChar83Stroke0  },
};

/* char: 84 'T' */

static Vector2D RomanChar84Stroke0[] = {
  Vector2D(35.6933, 100),
  Vector2D(35.6933, 0),
};

static Vector2D RomanChar84Stroke1[] = {
  Vector2D(2.36, 100),
  Vector2D(69.0267, 100),
};

static StrokeRec RomanChar84[] = {
   { 2, RomanChar84Stroke0  },
   { 2, RomanChar84Stroke1  },
};

/* char: 85 'U' */

static Vector2D RomanChar85Stroke0[] = {
  Vector2D(11.54, 100),
  Vector2D(11.54, 28.5714),
  Vector2D(16.3019, 14.2857),
  Vector2D(25.8257, 4.7619),
  Vector2D(40.1114, 0),
  Vector2D(49.6352, 0),
  Vector2D(63.921, 4.7619),
  Vector2D(73.4448, 14.2857),
  Vector2D(78.2067, 28.5714),
  Vector2D(78.2067, 100),
};

static StrokeRec RomanChar85[] = {
   { 10, RomanChar85Stroke0  },
};

/* char: 86 'V' */

static Vector2D RomanChar86Stroke0[] = {
  Vector2D(2.36, 100),
  Vector2D(40.4552, 0),
};

static Vector2D RomanChar86Stroke1[] = {
  Vector2D(78.5505, 100),
  Vector2D(40.4552, 0),
};

static StrokeRec RomanChar86[] = {
   { 2, RomanChar86Stroke0  },
   { 2, RomanChar86Stroke1  },
};

/* char: 87 'W' */

static Vector2D RomanChar87Stroke0[] = {
  Vector2D(2.22, 100),
  Vector2D(26.0295, 0),
};

static Vector2D RomanChar87Stroke1[] = {
  Vector2D(49.839, 100),
  Vector2D(26.0295, 0),
};

static Vector2D RomanChar87Stroke2[] = {
  Vector2D(49.839, 100),
  Vector2D(73.6486, 0),
};

static Vector2D RomanChar87Stroke3[] = {
  Vector2D(97.4581, 100),
  Vector2D(73.6486, 0),
};

static StrokeRec RomanChar87[] = {
   { 2, RomanChar87Stroke0  },
   { 2, RomanChar87Stroke1  },
   { 2, RomanChar87Stroke2  },
   { 2, RomanChar87Stroke3  },
};

/* char: 88 'X' */

static Vector2D RomanChar88Stroke0[] = {
  Vector2D(2.5, 100),
  Vector2D(69.1667, 0),
};

static Vector2D RomanChar88Stroke1[] = {
  Vector2D(69.1667, 100),
  Vector2D(2.5, 0),
};

static StrokeRec RomanChar88[] = {
   { 2, RomanChar88Stroke0  },
   { 2, RomanChar88Stroke1  },
};

/* char: 89 'Y' */

static Vector2D RomanChar89Stroke0[] = {
  Vector2D(1.52, 100),
  Vector2D(39.6152, 52.381),
  Vector2D(39.6152, 0),
};

static Vector2D RomanChar89Stroke1[] = {
  Vector2D(77.7105, 100),
  Vector2D(39.6152, 52.381),
};

static StrokeRec RomanChar89[] = {
   { 3, RomanChar89Stroke0  },
   { 2, RomanChar89Stroke1  },
};

/* char: 90 'Z' */

static Vector2D RomanChar90Stroke0[] = {
  Vector2D(69.1667, 100),
  Vector2D(2.5, 0),
};

static Vector2D RomanChar90Stroke1[] = {
  Vector2D(2.5, 100),
  Vector2D(69.1667, 100),
};

static Vector2D RomanChar90Stroke2[] = {
  Vector2D(2.5, 0),
  Vector2D(69.1667, 0),
};

static StrokeRec RomanChar90[] = {
   { 2, RomanChar90Stroke0  },
   { 2, RomanChar90Stroke1  },
   { 2, RomanChar90Stroke2  },
};

/* char: 91 '[' */

static Vector2D RomanChar91Stroke0[] = {
  Vector2D(7.78, 119.048),
  Vector2D(7.78, -33.3333),
};

static Vector2D RomanChar91Stroke1[] = {
  Vector2D(12.5419, 119.048),
  Vector2D(12.5419, -33.3333),
};

static Vector2D RomanChar91Stroke2[] = {
  Vector2D(7.78, 119.048),
  Vector2D(41.1133, 119.048),
};

static Vector2D RomanChar91Stroke3[] = {
  Vector2D(7.78, -33.3333),
  Vector2D(41.1133, -33.3333),
};

static StrokeRec RomanChar91[] = {
   { 2, RomanChar91Stroke0  },
   { 2, RomanChar91Stroke1  },
   { 2, RomanChar91Stroke2  },
   { 2, RomanChar91Stroke3  },
};

/* char: 92 '\' */

static Vector2D RomanChar92Stroke0[] = {
  Vector2D(5.84, 100),
  Vector2D(72.5067, -14.2857),
};

static StrokeRec RomanChar92[] = {
   { 2, RomanChar92Stroke0  },
};

/* char: 93 ']' */

static Vector2D RomanChar93Stroke0[] = {
  Vector2D(33.0114, 119.048),
  Vector2D(33.0114, -33.3333),
};

static Vector2D RomanChar93Stroke1[] = {
  Vector2D(37.7733, 119.048),
  Vector2D(37.7733, -33.3333),
};

static Vector2D RomanChar93Stroke2[] = {
  Vector2D(4.44, 119.048),
  Vector2D(37.7733, 119.048),
};

static Vector2D RomanChar93Stroke3[] = {
  Vector2D(4.44, -33.3333),
  Vector2D(37.7733, -33.3333),
};

static StrokeRec RomanChar93[] = {
   { 2, RomanChar93Stroke0  },
   { 2, RomanChar93Stroke1  },
   { 2, RomanChar93Stroke2  },
   { 2, RomanChar93Stroke3  },
};

/* char: 94 '^' */

static Vector2D RomanChar94Stroke0[] = {
  Vector2D(44.0752, 109.524),
  Vector2D(5.98, 42.8571),
};

static Vector2D RomanChar94Stroke1[] = {
  Vector2D(44.0752, 109.524),
  Vector2D(82.1705, 42.8571),
};

static StrokeRec RomanChar94[] = {
   { 2, RomanChar94Stroke0  },
   { 2, RomanChar94Stroke1  },
};

/* char: 95 '_' */

static Vector2D RomanChar95Stroke0[] = {
  Vector2D(-1.1, -33.3333),
  Vector2D(103.662, -33.3333),
  Vector2D(103.662, -28.5714),
  Vector2D(-1.1, -28.5714),
  Vector2D(-1.1, -33.3333),
};

static StrokeRec RomanChar95[] = {
   { 5, RomanChar95Stroke0  },
};

/* char: 96 '`' */

static Vector2D RomanChar96Stroke0[] = {
  Vector2D(33.0219, 100),
  Vector2D(56.8314, 71.4286),
};

static Vector2D RomanChar96Stroke1[] = {
  Vector2D(33.0219, 100),
  Vector2D(28.26, 95.2381),
  Vector2D(56.8314, 71.4286),
};

static StrokeRec RomanChar96[] = {
   { 2, RomanChar96Stroke0  },
   { 3, RomanChar96Stroke1  },
};

/* char: 97 'a' */

static Vector2D RomanChar97Stroke0[] = {
  Vector2D(63.8229, 66.6667),
  Vector2D(63.8229, 0),
};

static Vector2D RomanChar97Stroke1[] = {
  Vector2D(63.8229, 52.381),
  Vector2D(54.299, 61.9048),
  Vector2D(44.7752, 66.6667),
  Vector2D(30.4895, 66.6667),
  Vector2D(20.9657, 61.9048),
  Vector2D(11.4419, 52.381),
  Vector2D(6.68, 38.0952),
  Vector2D(6.68, 28.5714),
  Vector2D(11.4419, 14.2857),
  Vector2D(20.9657, 4.7619),
  Vector2D(30.4895, 0),
  Vector2D(44.7752, 0),
  Vector2D(54.299, 4.7619),
  Vector2D(63.8229, 14.2857),
};

static StrokeRec RomanChar97[] = {
   { 2, RomanChar97Stroke0  },
   { 14, RomanChar97Stroke1  },
};

/* char: 98 'b' */

static Vector2D RomanChar98Stroke0[] = {
  Vector2D(8.76, 100),
  Vector2D(8.76, 0),
};

static Vector2D RomanChar98Stroke1[] = {
  Vector2D(8.76, 52.381),
  Vector2D(18.2838, 61.9048),
  Vector2D(27.8076, 66.6667),
  Vector2D(42.0933, 66.6667),
  Vector2D(51.6171, 61.9048),
  Vector2D(61.141, 52.381),
  Vector2D(65.9029, 38.0952),
  Vector2D(65.9029, 28.5714),
  Vector2D(61.141, 14.2857),
  Vector2D(51.6171, 4.7619),
  Vector2D(42.0933, 0),
  Vector2D(27.8076, 0),
  Vector2D(18.2838, 4.7619),
  Vector2D(8.76, 14.2857),
};

static StrokeRec RomanChar98[] = {
   { 2, RomanChar98Stroke0  },
   { 14, RomanChar98Stroke1  },
};

/* char: 99 'c' */

static Vector2D RomanChar99Stroke0[] = {
  Vector2D(62.6629, 52.381),
  Vector2D(53.139, 61.9048),
  Vector2D(43.6152, 66.6667),
  Vector2D(29.3295, 66.6667),
  Vector2D(19.8057, 61.9048),
  Vector2D(10.2819, 52.381),
  Vector2D(5.52, 38.0952),
  Vector2D(5.52, 28.5714),
  Vector2D(10.2819, 14.2857),
  Vector2D(19.8057, 4.7619),
  Vector2D(29.3295, 0),
  Vector2D(43.6152, 0),
  Vector2D(53.139, 4.7619),
  Vector2D(62.6629, 14.2857),
};

static StrokeRec RomanChar99[] = {
   { 14, RomanChar99Stroke0  },
};

/* char: 100 'd' */

static Vector2D RomanChar100Stroke0[] = {
  Vector2D(61.7829, 100),
  Vector2D(61.7829, 0),
};

static Vector2D RomanChar100Stroke1[] = {
  Vector2D(61.7829, 52.381),
  Vector2D(52.259, 61.9048),
  Vector2D(42.7352, 66.6667),
  Vector2D(28.4495, 66.6667),
  Vector2D(18.9257, 61.9048),
  Vector2D(9.4019, 52.381),
  Vector2D(4.64, 38.0952),
  Vector2D(4.64, 28.5714),
  Vector2D(9.4019, 14.2857),
  Vector2D(18.9257, 4.7619),
  Vector2D(28.4495, 0),
  Vector2D(42.7352, 0),
  Vector2D(52.259, 4.7619),
  Vector2D(61.7829, 14.2857),
};

static StrokeRec RomanChar100[] = {
   { 2, RomanChar100Stroke0  },
   { 14, RomanChar100Stroke1  },
};

/* char: 101 'e' */

static Vector2D RomanChar101Stroke0[] = {
  Vector2D(5.72, 38.0952),
  Vector2D(62.8629, 38.0952),
  Vector2D(62.8629, 47.619),
  Vector2D(58.101, 57.1429),
  Vector2D(53.339, 61.9048),
  Vector2D(43.8152, 66.6667),
  Vector2D(29.5295, 66.6667),
  Vector2D(20.0057, 61.9048),
  Vector2D(10.4819, 52.381),
  Vector2D(5.72, 38.0952),
  Vector2D(5.72, 28.5714),
  Vector2D(10.4819, 14.2857),
  Vector2D(20.0057, 4.7619),
  Vector2D(29.5295, 0),
  Vector2D(43.8152, 0),
  Vector2D(53.339, 4.7619),
  Vector2D(62.8629, 14.2857),
};

static StrokeRec RomanChar101[] = {
   { 17, RomanChar101Stroke0  },
};

/* char: 102 'f' */

static Vector2D RomanChar102Stroke0[] = {
  Vector2D(38.7752, 100),
  Vector2D(29.2514, 100),
  Vector2D(19.7276, 95.2381),
  Vector2D(14.9657, 80.9524),
  Vector2D(14.9657, 0),
};

static Vector2D RomanChar102Stroke1[] = {
  Vector2D(0.68, 66.6667),
  Vector2D(34.0133, 66.6667),
};

static StrokeRec RomanChar102[] = {
   { 5, RomanChar102Stroke0  },
   { 2, RomanChar102Stroke1  },
};

/* char: 103 'g' */

static Vector2D RomanChar103Stroke0[] = {
  Vector2D(62.5029, 66.6667),
  Vector2D(62.5029, -9.5238),
  Vector2D(57.741, -23.8095),
  Vector2D(52.979, -28.5714),
  Vector2D(43.4552, -33.3333),
  Vector2D(29.1695, -33.3333),
  Vector2D(19.6457, -28.5714),
};

static Vector2D RomanChar103Stroke1[] = {
  Vector2D(62.5029, 52.381),
  Vector2D(52.979, 61.9048),
  Vector2D(43.4552, 66.6667),
  Vector2D(29.1695, 66.6667),
  Vector2D(19.6457, 61.9048),
  Vector2D(10.1219, 52.381),
  Vector2D(5.36, 38.0952),
  Vector2D(5.36, 28.5714),
  Vector2D(10.1219, 14.2857),
  Vector2D(19.6457, 4.7619),
  Vector2D(29.1695, 0),
  Vector2D(43.4552, 0),
  Vector2D(52.979, 4.7619),
  Vector2D(62.5029, 14.2857),
};

static StrokeRec RomanChar103[] = {
   { 7, RomanChar103Stroke0  },
   { 14, RomanChar103Stroke1  },
};

/* char: 104 'h' */

static Vector2D RomanChar104Stroke0[] = {
  Vector2D(9.6, 100),
  Vector2D(9.6, 0),
};

static Vector2D RomanChar104Stroke1[] = {
  Vector2D(9.6, 47.619),
  Vector2D(23.8857, 61.9048),
  Vector2D(33.4095, 66.6667),
  Vector2D(47.6952, 66.6667),
  Vector2D(57.219, 61.9048),
  Vector2D(61.981, 47.619),
  Vector2D(61.981, 0),
};

static StrokeRec RomanChar104[] = {
   { 2, RomanChar104Stroke0  },
   { 7, RomanChar104Stroke1  },
};

/* char: 105 'i' */

static Vector2D RomanChar105Stroke0[] = {
  Vector2D(10.02, 100),
  Vector2D(14.7819, 95.2381),
  Vector2D(19.5438, 100),
  Vector2D(14.7819, 104.762),
  Vector2D(10.02, 100),
};

static Vector2D RomanChar105Stroke1[] = {
  Vector2D(14.7819, 66.6667),
  Vector2D(14.7819, 0),
};

static StrokeRec RomanChar105[] = {
   { 5, RomanChar105Stroke0  },
   { 2, RomanChar105Stroke1  },
};

/* char: 106 'j' */

static Vector2D RomanChar106Stroke0[] = {
  Vector2D(17.3876, 100),
  Vector2D(22.1495, 95.2381),
  Vector2D(26.9114, 100),
  Vector2D(22.1495, 104.762),
  Vector2D(17.3876, 100),
};

static Vector2D RomanChar106Stroke1[] = {
  Vector2D(22.1495, 66.6667),
  Vector2D(22.1495, -14.2857),
  Vector2D(17.3876, -28.5714),
  Vector2D(7.8638, -33.3333),
  Vector2D(-1.66, -33.3333),
};

static StrokeRec RomanChar106[] = {
   { 5, RomanChar106Stroke0  },
   { 5, RomanChar106Stroke1  },
};

/* char: 107 'k' */

static Vector2D RomanChar107Stroke0[] = {
  Vector2D(9.6, 100),
  Vector2D(9.6, 0),
};

static Vector2D RomanChar107Stroke1[] = {
  Vector2D(57.219, 66.6667),
  Vector2D(9.6, 19.0476),
};

static Vector2D RomanChar107Stroke2[] = {
  Vector2D(28.6476, 38.0952),
  Vector2D(61.981, 0),
};

static StrokeRec RomanChar107[] = {
   { 2, RomanChar107Stroke0  },
   { 2, RomanChar107Stroke1  },
   { 2, RomanChar107Stroke2  },
};

/* char: 108 'l' */

static Vector2D RomanChar108Stroke0[] = {
  Vector2D(10.02, 100),
  Vector2D(10.02, 0),
};

static StrokeRec RomanChar108[] = {
   { 2, RomanChar108Stroke0  },
};

/* char: 109 'm' */

static Vector2D RomanChar109Stroke0[] = {
  Vector2D(9.6, 66.6667),
  Vector2D(9.6, 0),
};

static Vector2D RomanChar109Stroke1[] = {
  Vector2D(9.6, 47.619),
  Vector2D(23.8857, 61.9048),
  Vector2D(33.4095, 66.6667),
  Vector2D(47.6952, 66.6667),
  Vector2D(57.219, 61.9048),
  Vector2D(61.981, 47.619),
  Vector2D(61.981, 0),
};

static Vector2D RomanChar109Stroke2[] = {
  Vector2D(61.981, 47.619),
  Vector2D(76.2667, 61.9048),
  Vector2D(85.7905, 66.6667),
  Vector2D(100.076, 66.6667),
  Vector2D(109.6, 61.9048),
  Vector2D(114.362, 47.619),
  Vector2D(114.362, 0),
};

static StrokeRec RomanChar109[] = {
   { 2, RomanChar109Stroke0  },
   { 7, RomanChar109Stroke1  },
   { 7, RomanChar109Stroke2  },
};

/* char: 110 'n' */

static Vector2D RomanChar110Stroke0[] = {
  Vector2D(9.18, 66.6667),
  Vector2D(9.18, 0),
};

static Vector2D RomanChar110Stroke1[] = {
  Vector2D(9.18, 47.619),
  Vector2D(23.4657, 61.9048),
  Vector2D(32.9895, 66.6667),
  Vector2D(47.2752, 66.6667),
  Vector2D(56.799, 61.9048),
  Vector2D(61.561, 47.619),
  Vector2D(61.561, 0),
};

static StrokeRec RomanChar110[] = {
   { 2, RomanChar110Stroke0  },
   { 7, RomanChar110Stroke1  },
};

/* char: 111 'o' */

static Vector2D RomanChar111Stroke0[] = {
  Vector2D(28.7895, 66.6667),
  Vector2D(19.2657, 61.9048),
  Vector2D(9.7419, 52.381),
  Vector2D(4.98, 38.0952),
  Vector2D(4.98, 28.5714),
  Vector2D(9.7419, 14.2857),
  Vector2D(19.2657, 4.7619),
  Vector2D(28.7895, 0),
  Vector2D(43.0752, 0),
  Vector2D(52.599, 4.7619),
  Vector2D(62.1229, 14.2857),
  Vector2D(66.8848, 28.5714),
  Vector2D(66.8848, 38.0952),
  Vector2D(62.1229, 52.381),
  Vector2D(52.599, 61.9048),
  Vector2D(43.0752, 66.6667),
  Vector2D(28.7895, 66.6667),
};

static StrokeRec RomanChar111[] = {
   { 17, RomanChar111Stroke0  },
};

/* char: 112 'p' */

static Vector2D RomanChar112Stroke0[] = {
  Vector2D(9.46, 66.6667),
  Vector2D(9.46, -33.3333),
};

static Vector2D RomanChar112Stroke1[] = {
  Vector2D(9.46, 52.381),
  Vector2D(18.9838, 61.9048),
  Vector2D(28.5076, 66.6667),
  Vector2D(42.7933, 66.6667),
  Vector2D(52.3171, 61.9048),
  Vector2D(61.841, 52.381),
  Vector2D(66.6029, 38.0952),
  Vector2D(66.6029, 28.5714),
  Vector2D(61.841, 14.2857),
  Vector2D(52.3171, 4.7619),
  Vector2D(42.7933, 0),
  Vector2D(28.5076, 0),
  Vector2D(18.9838, 4.7619),
  Vector2D(9.46, 14.2857),
};

static StrokeRec RomanChar112[] = {
   { 2, RomanChar112Stroke0  },
   { 14, RomanChar112Stroke1  },
};

/* char: 113 'q' */

static Vector2D RomanChar113Stroke0[] = {
  Vector2D(61.9829, 66.6667),
  Vector2D(61.9829, -33.3333),
};

static Vector2D RomanChar113Stroke1[] = {
  Vector2D(61.9829, 52.381),
  Vector2D(52.459, 61.9048),
  Vector2D(42.9352, 66.6667),
  Vector2D(28.6495, 66.6667),
  Vector2D(19.1257, 61.9048),
  Vector2D(9.6019, 52.381),
  Vector2D(4.84, 38.0952),
  Vector2D(4.84, 28.5714),
  Vector2D(9.6019, 14.2857),
  Vector2D(19.1257, 4.7619),
  Vector2D(28.6495, 0),
  Vector2D(42.9352, 0),
  Vector2D(52.459, 4.7619),
  Vector2D(61.9829, 14.2857),
};

static StrokeRec RomanChar113[] = {
   { 2, RomanChar113Stroke0  },
   { 14, RomanChar113Stroke1  },
};

/* char: 114 'r' */

static Vector2D RomanChar114Stroke0[] = {
  Vector2D(9.46, 66.6667),
  Vector2D(9.46, 0),
};

static Vector2D RomanChar114Stroke1[] = {
  Vector2D(9.46, 38.0952),
  Vector2D(14.2219, 52.381),
  Vector2D(23.7457, 61.9048),
  Vector2D(33.2695, 66.6667),
  Vector2D(47.5552, 66.6667),
};

static StrokeRec RomanChar114[] = {
   { 2, RomanChar114Stroke0  },
   { 5, RomanChar114Stroke1  },
};

/* char: 115 's' */

static Vector2D RomanChar115Stroke0[] = {
  Vector2D(57.081, 52.381),
  Vector2D(52.319, 61.9048),
  Vector2D(38.0333, 66.6667),
  Vector2D(23.7476, 66.6667),
  Vector2D(9.4619, 61.9048),
  Vector2D(4.7, 52.381),
  Vector2D(9.4619, 42.8571),
  Vector2D(18.9857, 38.0952),
  Vector2D(42.7952, 33.3333),
  Vector2D(52.319, 28.5714),
  Vector2D(57.081, 19.0476),
  Vector2D(57.081, 14.2857),
  Vector2D(52.319, 4.7619),
  Vector2D(38.0333, 0),
  Vector2D(23.7476, 0),
  Vector2D(9.4619, 4.7619),
  Vector2D(4.7, 14.2857),
};

static StrokeRec RomanChar115[] = {
   { 17, RomanChar115Stroke0  },
};

/* char: 116 't' */

static Vector2D RomanChar116Stroke0[] = {
  Vector2D(14.8257, 100),
  Vector2D(14.8257, 19.0476),
  Vector2D(19.5876, 4.7619),
  Vector2D(29.1114, 0),
  Vector2D(38.6352, 0),
};

static Vector2D RomanChar116Stroke1[] = {
  Vector2D(0.54, 66.6667),
  Vector2D(33.8733, 66.6667),
};

static StrokeRec RomanChar116[] = {
   { 5, RomanChar116Stroke0  },
   { 2, RomanChar116Stroke1  },
};

/* char: 117 'u' */

static Vector2D RomanChar117Stroke0[] = {
  Vector2D(9.46, 66.6667),
  Vector2D(9.46, 19.0476),
  Vector2D(14.2219, 4.7619),
  Vector2D(23.7457, 0),
  Vector2D(38.0314, 0),
  Vector2D(47.5552, 4.7619),
  Vector2D(61.841, 19.0476),
};

static Vector2D RomanChar117Stroke1[] = {
  Vector2D(61.841, 66.6667),
  Vector2D(61.841, 0),
};

static StrokeRec RomanChar117[] = {
   { 7, RomanChar117Stroke0  },
   { 2, RomanChar117Stroke1  },
};

/* char: 118 'v' */

static Vector2D RomanChar118Stroke0[] = {
  Vector2D(1.8, 66.6667),
  Vector2D(30.3714, 0),
};

static Vector2D RomanChar118Stroke1[] = {
  Vector2D(58.9429, 66.6667),
  Vector2D(30.3714, 0),
};

static StrokeRec RomanChar118[] = {
   { 2, RomanChar118Stroke0  },
   { 2, RomanChar118Stroke1  },
};

/* char: 119 'w' */

static Vector2D RomanChar119Stroke0[] = {
  Vector2D(2.5, 66.6667),
  Vector2D(21.5476, 0),
};

static Vector2D RomanChar119Stroke1[] = {
  Vector2D(40.5952, 66.6667),
  Vector2D(21.5476, 0),
};

static Vector2D RomanChar119Stroke2[] = {
  Vector2D(40.5952, 66.6667),
  Vector2D(59.6429, 0),
};

static Vector2D RomanChar119Stroke3[] = {
  Vector2D(78.6905, 66.6667),
  Vector2D(59.6429, 0),
};

static StrokeRec RomanChar119[] = {
   { 2, RomanChar119Stroke0  },
   { 2, RomanChar119Stroke1  },
   { 2, RomanChar119Stroke2  },
   { 2, RomanChar119Stroke3  },
};

/* char: 120 'x' */

static Vector2D RomanChar120Stroke0[] = {
  Vector2D(1.66, 66.6667),
  Vector2D(54.041, 0),
};

static Vector2D RomanChar120Stroke1[] = {
  Vector2D(54.041, 66.6667),
  Vector2D(1.66, 0),
};

static StrokeRec RomanChar120[] = {
   { 2, RomanChar120Stroke0  },
   { 2, RomanChar120Stroke1  },
};

/* char: 121 'y' */

static Vector2D RomanChar121Stroke0[] = {
  Vector2D(6.5619, 66.6667),
  Vector2D(35.1333, 0),
};

static Vector2D RomanChar121Stroke1[] = {
  Vector2D(63.7048, 66.6667),
  Vector2D(35.1333, 0),
  Vector2D(25.6095, -19.0476),
  Vector2D(16.0857, -28.5714),
  Vector2D(6.5619, -33.3333),
  Vector2D(1.8, -33.3333),
};

static StrokeRec RomanChar121[] = {
   { 2, RomanChar121Stroke0  },
   { 6, RomanChar121Stroke1  },
};

/* char: 122 'z' */

static Vector2D RomanChar122Stroke0[] = {
  Vector2D(56.821, 66.6667),
  Vector2D(4.44, 0),
};

static Vector2D RomanChar122Stroke1[] = {
  Vector2D(4.44, 66.6667),
  Vector2D(56.821, 66.6667),
};

static Vector2D RomanChar122Stroke2[] = {
  Vector2D(4.44, 0),
  Vector2D(56.821, 0),
};

static StrokeRec RomanChar122[] = {
   { 2, RomanChar122Stroke0  },
   { 2, RomanChar122Stroke1  },
   { 2, RomanChar122Stroke2  },
};

/* char: 123 '{' */

static Vector2D RomanChar123Stroke0[] = {
  Vector2D(31.1895, 119.048),
  Vector2D(21.6657, 114.286),
  Vector2D(16.9038, 109.524),
  Vector2D(12.1419, 100),
  Vector2D(12.1419, 90.4762),
  Vector2D(16.9038, 80.9524),
  Vector2D(21.6657, 76.1905),
  Vector2D(26.4276, 66.6667),
  Vector2D(26.4276, 57.1429),
  Vector2D(16.9038, 47.619),
};

static Vector2D RomanChar123Stroke1[] = {
  Vector2D(21.6657, 114.286),
  Vector2D(16.9038, 104.762),
  Vector2D(16.9038, 95.2381),
  Vector2D(21.6657, 85.7143),
  Vector2D(26.4276, 80.9524),
  Vector2D(31.1895, 71.4286),
  Vector2D(31.1895, 61.9048),
  Vector2D(26.4276, 52.381),
  Vector2D(7.38, 42.8571),
  Vector2D(26.4276, 33.3333),
  Vector2D(31.1895, 23.8095),
  Vector2D(31.1895, 14.2857),
  Vector2D(26.4276, 4.7619),
  Vector2D(21.6657, 0),
  Vector2D(16.9038, -9.5238),
  Vector2D(16.9038, -19.0476),
  Vector2D(21.6657, -28.5714),
};

static Vector2D RomanChar123Stroke2[] = {
  Vector2D(16.9038, 38.0952),
  Vector2D(26.4276, 28.5714),
  Vector2D(26.4276, 19.0476),
  Vector2D(21.6657, 9.5238),
  Vector2D(16.9038, 4.7619),
  Vector2D(12.1419, -4.7619),
  Vector2D(12.1419, -14.2857),
  Vector2D(16.9038, -23.8095),
  Vector2D(21.6657, -28.5714),
  Vector2D(31.1895, -33.3333),
};

static StrokeRec RomanChar123[] = {
   { 10, RomanChar123Stroke0  },
   { 17, RomanChar123Stroke1  },
   { 10, RomanChar123Stroke2  },
};

/* char: 124 '|' */

static Vector2D RomanChar124Stroke0[] = {
  Vector2D(11.54, 119.048),
  Vector2D(11.54, -33.3333),
};

static StrokeRec RomanChar124[] = {
   { 2, RomanChar124Stroke0  },
};

/* char: 125 '}' */

static Vector2D RomanChar125Stroke0[] = {
  Vector2D(9.18, 119.048),
  Vector2D(18.7038, 114.286),
  Vector2D(23.4657, 109.524),
  Vector2D(28.2276, 100),
  Vector2D(28.2276, 90.4762),
  Vector2D(23.4657, 80.9524),
  Vector2D(18.7038, 76.1905),
  Vector2D(13.9419, 66.6667),
  Vector2D(13.9419, 57.1429),
  Vector2D(23.4657, 47.619),
};

static Vector2D RomanChar125Stroke1[] = {
  Vector2D(18.7038, 114.286),
  Vector2D(23.4657, 104.762),
  Vector2D(23.4657, 95.2381),
  Vector2D(18.7038, 85.7143),
  Vector2D(13.9419, 80.9524),
  Vector2D(9.18, 71.4286),
  Vector2D(9.18, 61.9048),
  Vector2D(13.9419, 52.381),
  Vector2D(32.9895, 42.8571),
  Vector2D(13.9419, 33.3333),
  Vector2D(9.18, 23.8095),
  Vector2D(9.18, 14.2857),
  Vector2D(13.9419, 4.7619),
  Vector2D(18.7038, 0),
  Vector2D(23.4657, -9.5238),
  Vector2D(23.4657, -19.0476),
  Vector2D(18.7038, -28.5714),
};

static Vector2D RomanChar125Stroke2[] = {
  Vector2D(23.4657, 38.0952),
  Vector2D(13.9419, 28.5714),
  Vector2D(13.9419, 19.0476),
  Vector2D(18.7038, 9.5238),
  Vector2D(23.4657, 4.7619),
  Vector2D(28.2276, -4.7619),
  Vector2D(28.2276, -14.2857),
  Vector2D(23.4657, -23.8095),
  Vector2D(18.7038, -28.5714),
  Vector2D(9.18, -33.3333),
};

static StrokeRec RomanChar125[] = {
   { 10, RomanChar125Stroke0  },
   { 17, RomanChar125Stroke1  },
   { 10, RomanChar125Stroke2  },
};

/* char: 126 '~' */

static Vector2D RomanChar126Stroke0[] = {
  Vector2D(2.92, 28.5714),
  Vector2D(2.92, 38.0952),
  Vector2D(7.6819, 52.381),
  Vector2D(17.2057, 57.1429),
  Vector2D(26.7295, 57.1429),
  Vector2D(36.2533, 52.381),
  Vector2D(55.301, 38.0952),
  Vector2D(64.8248, 33.3333),
  Vector2D(74.3486, 33.3333),
  Vector2D(83.8724, 38.0952),
  Vector2D(88.6343, 47.619),
};

static Vector2D RomanChar126Stroke1[] = {
  Vector2D(2.92, 38.0952),
  Vector2D(7.6819, 47.619),
  Vector2D(17.2057, 52.381),
  Vector2D(26.7295, 52.381),
  Vector2D(36.2533, 47.619),
  Vector2D(55.301, 33.3333),
  Vector2D(64.8248, 28.5714),
  Vector2D(74.3486, 28.5714),
  Vector2D(83.8724, 33.3333),
  Vector2D(88.6343, 47.619),
  Vector2D(88.6343, 57.1429),
};

static StrokeRec RomanChar126[] = {
   { 11, RomanChar126Stroke0  },
   { 11, RomanChar126Stroke1  },
};

/* char: 127 */

static Vector2D RomanChar127Stroke0[] = {
  Vector2D(52.381, 100),
  Vector2D(14.2857, -33.3333),
};

static Vector2D RomanChar127Stroke1[] = {
  Vector2D(28.5714, 66.6667),
  Vector2D(14.2857, 61.9048),
  Vector2D(4.7619, 52.381),
  Vector2D(0, 38.0952),
  Vector2D(0, 23.8095),
  Vector2D(4.7619, 14.2857),
  Vector2D(14.2857, 4.7619),
  Vector2D(28.5714, 0),
  Vector2D(38.0952, 0),
  Vector2D(52.381, 4.7619),
  Vector2D(61.9048, 14.2857),
  Vector2D(66.6667, 28.5714),
  Vector2D(66.6667, 42.8571),
  Vector2D(61.9048, 52.381),
  Vector2D(52.381, 61.9048),
  Vector2D(38.0952, 66.6667),
  Vector2D(28.5714, 66.6667),
};

static StrokeRec RomanChar127[] = {
   { 2, RomanChar127Stroke0  },
   { 17, RomanChar127Stroke1  },
};

static CharRec RomanChars[] = {
    { 0, /* char0 */ 0, 0, 0 },
    { 0, /* char1 */ 0, 0, 0 },
    { 0, /* char2 */ 0, 0, 0 },
    { 0, /* char3 */ 0, 0, 0 },
    { 0, /* char4 */ 0, 0, 0 },
    { 0, /* char5 */ 0, 0, 0 },
    { 0, /* char6 */ 0, 0, 0 },
    { 0, /* char7 */ 0, 0, 0 },
    { 0, /* char8 */ 0, 0, 0 },
    { 0, /* char9 */ 0, 0, 0 },
    { 0, /* char10 */ 0, 0, 0 },
    { 0, /* char11 */ 0, 0, 0 },
    { 0, /* char12 */ 0, 0, 0 },
    { 0, /* char13 */ 0, 0, 0 },
    { 0, /* char14 */ 0, 0, 0 },
    { 0, /* char15 */ 0, 0, 0 },
    { 0, /* char16 */ 0, 0, 0 },
    { 0, /* char17 */ 0, 0, 0 },
    { 0, /* char18 */ 0, 0, 0 },
    { 0, /* char19 */ 0, 0, 0 },
    { 0, /* char20 */ 0, 0, 0 },
    { 0, /* char21 */ 0, 0, 0 },
    { 0, /* char22 */ 0, 0, 0 },
    { 0, /* char23 */ 0, 0, 0 },
    { 0, /* char24 */ 0, 0, 0 },
    { 0, /* char25 */ 0, 0, 0 },
    { 0, /* char26 */ 0, 0, 0 },
    { 0, /* char27 */ 0, 0, 0 },
    { 0, /* char28 */ 0, 0, 0 },
    { 0, /* char29 */ 0, 0, 0 },
    { 0, /* char30 */ 0, 0, 0 },
    { 0, /* char31 */ 0, 0, 0 },
    { 0, /* char32 */ 0, 52.381, 104.762 },
    { 2, RomanChar33, 13.3819, 26.6238 },
    { 2, RomanChar34, 23.0676, 51.4352 },
    { 4, RomanChar35, 36.5333, 79.4886 },
    { 3, RomanChar36, 38.1533, 76.2067 },
    { 3, RomanChar37, 49.2171, 96.5743 },
    { 1, RomanChar38, 53.599, 101.758 },
    { 1, RomanChar39, 4.44, 13.62 },
    { 1, RomanChar40, 21.8657, 47.1733 },
    { 1, RomanChar41, 24.3276, 47.5333 },
    { 3, RomanChar42, 30.7695, 59.439 },
    { 2, RomanChar43, 48.8371, 97.2543 },
    { 1, RomanChar44, 13.5219, 26.0638 },
    { 1, RomanChar45, 50.2371, 100.754 },
    { 1, RomanChar46, 13.1019, 26.4838 },
    { 1, RomanChar47, 40.5733, 82.1067 },
    { 1, RomanChar48, 38.3133, 77.0667 },
    { 1, RomanChar49, 30.8676, 66.5295 },
    { 1, RomanChar50, 38.7533, 77.6467 },
    { 1, RomanChar51, 38.3333, 77.0467 },
    { 2, RomanChar52, 37.2133, 80.1686 },
    { 1, RomanChar53, 38.1933, 77.6867 },
    { 1, RomanChar54, 34.1514, 73.8048 },
    { 2, RomanChar55, 38.8933, 77.2267 },
    { 1, RomanChar56, 38.9333, 77.6667 },
    { 1, RomanChar57, 39.9333, 74.0648 },
    { 2, RomanChar58, 14.0819, 26.2238 },
    { 2, RomanChar59, 12.9619, 26.3038 },
    { 1, RomanChar60, 41.1552, 81.6105 },
    { 2, RomanChar61, 48.5571, 97.2543 },
    { 1, RomanChar62, 40.8752, 81.6105 },
    { 2, RomanChar63, 36.9914, 73.9029 },
    { 2, RomanChar64, 34.9314, 74.3648 },
    { 3, RomanChar65, 40.5952, 80.4905 },
    { 3, RomanChar66, 44.7533, 83.6267 },
    { 1, RomanChar67, 39.9933, 84.4886 },
    { 2, RomanChar68, 45.2933, 85.2867 },
    { 4, RomanChar69, 39.9914, 78.1848 },
    { 3, RomanChar70, 39.9914, 78.7448 },
    { 2, RomanChar71, 40.3933, 89.7686 },
    { 3, RomanChar72, 44.7533, 89.0867 },
    { 1, RomanChar73, 10.86, 21.3 },
    { 1, RomanChar74, 31.0714, 59.999 },
    { 3, RomanChar75, 44.6133, 79.3267 },
    { 2, RomanChar76, 40.2514, 71.3229 },
    { 4, RomanChar77, 48.9552, 97.2105 },
    { 3, RomanChar78, 44.4733, 88.8067 },
    { 1, RomanChar79, 44.3352, 88.8305 },
    { 2, RomanChar80, 45.4333, 85.6667 },
    { 2, RomanChar81, 43.3952, 88.0905 },
    { 3, RomanChar82, 45.0133, 82.3667 },
    { 1, RomanChar83, 41.3333, 80.8267 },
    { 2, RomanChar84, 35.6933, 71.9467 },
    { 1, RomanChar85, 44.8733, 89.4867 },
    { 2, RomanChar86, 40.4552, 81.6105 },
    { 4, RomanChar87, 49.839, 100.518 },
    { 2, RomanChar88, 35.8333, 72.3667 },
    { 2, RomanChar89, 39.6152, 79.6505 },
    { 3, RomanChar90, 35.8333, 73.7467 },
    { 4, RomanChar91, 22.0657, 46.1133 },
    { 1, RomanChar92, 39.1733, 78.2067 },
    { 4, RomanChar93, 23.4876, 46.3933 },
    { 2, RomanChar94, 44.0752, 90.2305 },
    { 1, RomanChar95, 51.281, 104.062 },
    { 2, RomanChar96, 42.5457, 83.5714 },
    { 2, RomanChar97, 35.2514, 66.6029 },
    { 2, RomanChar98, 37.3314, 70.4629 },
    { 1, RomanChar99, 34.0914, 68.9229 },
    { 2, RomanChar100, 33.2114, 70.2629 },
    { 1, RomanChar101, 34.2914, 68.5229 },
    { 2, RomanChar102, 14.9657, 38.6552 },
    { 2, RomanChar103, 33.9314, 70.9829 },
    { 2, RomanChar104, 33.4095, 71.021 },
    { 2, RomanChar105, 14.7819, 28.8638 },
    { 2, RomanChar106, 17.3876, 36.2314 },
    { 3, RomanChar107, 33.4095, 62.521 },
    { 1, RomanChar108, 10.02, 19.34 },
    { 3, RomanChar109, 61.981, 123.962 },
    { 2, RomanChar110, 32.9895, 70.881 },
    { 1, RomanChar111, 33.5514, 71.7448 },
    { 2, RomanChar112, 38.0314, 70.8029 },
    { 2, RomanChar113, 33.4114, 70.7429 },
    { 2, RomanChar114, 23.7457, 49.4952 },
    { 1, RomanChar115, 28.5095, 62.321 },
    { 2, RomanChar116, 14.8257, 39.3152 },
    { 2, RomanChar117, 33.2695, 71.161 },
    { 2, RomanChar118, 30.3714, 60.6029 },
    { 4, RomanChar119, 40.5952, 80.4905 },
    { 2, RomanChar120, 25.4695, 56.401 },
    { 2, RomanChar121, 35.1333, 66.0648 },
    { 3, RomanChar122, 28.2495, 61.821 },
    { 3, RomanChar123, 21.6657, 41.6295 },
    { 1, RomanChar124, 11.54, 23.78 },
    { 3, RomanChar125, 18.7038, 41.4695 },
    { 2, RomanChar126, 45.7771, 91.2743 },
    { 2, RomanChar127, 33.3333, 66.6667 },
};

const StrokeFont ROMAN_FONT("ROMAN", 128,  RomanChars, 119.048, -33.3333);

